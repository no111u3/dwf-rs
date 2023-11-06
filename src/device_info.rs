use crate::dwf;
use crate::{check_call, Result};

use std::ffi::{c_char, c_int, CStr};
use std::mem;
pub trait DeviceId {
    fn get_device_id(&self) -> c_int;
}

pub trait DeviceInfo: DeviceId {
    fn get_device_name(&self) -> Result<String> {
        let mut name = [0 as c_char; 32];
        unsafe {
            check_call(dwf::FDwfEnumDeviceName(
                self.get_device_id(),
                name.as_mut_ptr(),
            ))?;

            Ok(CStr::from_ptr(mem::transmute(name.as_mut_ptr()))
                .to_str()
                .unwrap()
                .to_owned())
        }
    }

    fn get_device_serial(&self) -> Result<String> {
        let mut serial = [0 as c_char; 32];
        unsafe {
            check_call(dwf::FDwfEnumSN(self.get_device_id(), serial.as_mut_ptr()))?;

            Ok(CStr::from_ptr(mem::transmute(serial.as_mut_ptr()))
                .to_str()
                .unwrap()
                .to_owned())
        }
    }

    fn device_is_use(&self) -> Result<bool> {
        unsafe {
            let mut in_use = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfEnumDeviceIsOpened(
                self.get_device_id(),
                in_use.as_mut_ptr() as *mut dwf::BOOL,
            ))?;

            in_use.assume_init()
        }
    }
}
