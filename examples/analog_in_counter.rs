use dwf;
use dwf::analog::analog_in::{TriggerSlope, TriggerSource, TriggerType};

const FREQ: f64 = 100000000.0f64;
const TRIG_LEVEL: f64 = 0.0f64;
const TIMEOUT: f64 = 1.0f64;
fn main() {
    println!("DWF Version: {}", dwf::get_version().unwrap());

    println!("Opening first device");
    let device = dwf::device::Device::default();
    let analog_in = device.analog_in();

    analog_in.set_frequency(FREQ).unwrap();
    analog_in
        .set_trigger_source(TriggerSource::AnalogIn)
        .unwrap();
    analog_in.set_trigger_type(TriggerType::Edge).unwrap();
    analog_in.set_trigger_channel(0).unwrap();
    analog_in.set_trigger_level(TRIG_LEVEL).unwrap();
    analog_in.set_trigger_slope(TriggerSlope::Rise).unwrap();

    let (count_max, time_max) = analog_in.get_counter_info().unwrap();
    analog_in.set_counter_timeout(TIMEOUT).unwrap();
    println!("Max-Count: {count_max} Timeout: {time_max}s  Timeout: {TIMEOUT}s");

    analog_in.reconfigure_start().unwrap();

    // TODO: Original code doesn't work, needs to update
}
