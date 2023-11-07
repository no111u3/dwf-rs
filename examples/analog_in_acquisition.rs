use dwf;
use dwf::analog::analog_in::{AnalogAcquisitionStatus, AnalogFilter};
use gnuplot::*;

const FREQ: f64 = 20000000.0f64;
const RANGE: f64 = 5f64;
const NUM_SAMPLES: usize = 4000;
fn main() {
    println!("DWF Version: {}", dwf::get_version().unwrap());

    println!("Opening first device");
    let device = dwf::device::Device::default();
    let analog_in = device.analog_in();
    let analog_channel0 = analog_in.channel(0);

    println!(
        "Device buffer size: {}",
        analog_in.get_buffer_size().unwrap()
    );

    analog_in.set_frequency(FREQ).unwrap();
    analog_in.set_buffer_size(NUM_SAMPLES as i32).unwrap();
    analog_channel0.enable().unwrap();
    analog_channel0.set_range(RANGE).unwrap();
    analog_channel0.set_filter(AnalogFilter::Decimate).unwrap();

    println!("Starting oscilloscope");
    analog_in.start().unwrap();

    while analog_in.get_status().unwrap() != AnalogAcquisitionStatus::Done {}
    println!("Acquisition done");

    let mut samples = Vec::new();
    analog_channel0
        .fetch_samples(&mut samples, NUM_SAMPLES as i32)
        .unwrap();
    let dc = samples.iter().sum::<f64>() / samples.len() as f64;
    println!("DC: {}V", dc);
    let mut fg = Figure::new();
    fg.axes2d().lines(1..NUM_SAMPLES, samples.iter(), &[]);
    fg.show().unwrap();
}
