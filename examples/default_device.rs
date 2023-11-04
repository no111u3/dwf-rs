use dwf;

fn main() {
    let device = dwf::device::Device::default();

    device.reset().unwrap();
}
