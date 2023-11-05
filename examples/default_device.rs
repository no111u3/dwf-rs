use dwf;
use dwf::device_info::DeviceInfo;

fn main() {
    let device = dwf::device::Device::default();

    device.reset().unwrap();

    println!("Device name: {}", device.get_device_name().unwrap());
    println!("Device serial: {}", device.get_device_serial().unwrap());
    println!("Device in use: {}", device.device_is_use().unwrap());
}
