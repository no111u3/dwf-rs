use dwf;
use dwf::analog::analog_in::AnalogAcquisitionStatus;
use dwf::device_info::DeviceInfo;

const FREQ: f64 = 10f64;
const RANGE: f64 = 2f64;
const NUM_SAMPLES: usize = 10 * FREQ as usize;

fn main() {
    let device = dwf::device::Device::default();

    device.reset().unwrap();

    println!("Device name: {}", device.get_device_name().unwrap());
    println!("Device serial: {}", device.get_device_serial().unwrap());
    println!("Device in use: {}", device.device_is_use().unwrap());

    let analog_in = device.analog_in();
    let analog_channel0 = analog_in.channel(0);

    analog_channel0.enable().unwrap();
    analog_channel0.set_range(RANGE).unwrap();
    analog_in.set_record_mode().unwrap();
    analog_in.set_frequency(FREQ).unwrap();
    analog_in
        .set_record_length((NUM_SAMPLES / FREQ as usize) as f64)
        .unwrap();

    println!("Starting oscilloscope");
    analog_in.start().unwrap();

    let mut samples = 0;
    let mut has_lost = false;
    let mut has_corrupted = false;
    let mut fetched_samples = Vec::new();

    while samples < NUM_SAMPLES {
        let status = analog_in.get_status().unwrap();
        match status {
            AnalogAcquisitionStatus::Config
            | AnalogAcquisitionStatus::Prefill
            | AnalogAcquisitionStatus::Armed => continue,
            AnalogAcquisitionStatus::Done => break,
            _ => {}
        }

        let (mut available, lost, corrupted) = analog_in.get_record_status().unwrap();

        samples += lost as usize;
        if lost != 0 {
            has_lost = true;
        }
        if corrupted != 0 {
            has_corrupted = true;
        }

        if available == 0 {
            continue;
        }

        if samples + available as usize > NUM_SAMPLES {
            available = (NUM_SAMPLES - samples) as i32;
        }

        analog_channel0
            .fetch_samples(&mut fetched_samples, available)
            .unwrap();
        samples += available as usize;
        println!("{} of {}", samples, NUM_SAMPLES);
    }

    println!("Recording done");
    if has_lost {
        println!("Samples were lost! Reduce frequency");
    }
    if has_corrupted {
        println!("Samples could be corrupted! Reduce frequency");
    }

    println!("Got samples: {:?}", fetched_samples);
}
