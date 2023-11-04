use crate::dwf;
use crate::{check_call, Result};

use std::ffi::{c_char, c_int, CStr};
use std::mem;
pub trait DeviceId {
    fn get_device_id(&self) -> i32;
}

pub trait DeviceInfo: DeviceId {
    fn get_device_name(&self) -> Result<String> {
        let mut name = [0 as c_char; 32];
        unsafe {
            check_call(dwf::FDwfEnumDeviceName(
                self.get_device_id() as c_int,
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
            check_call(dwf::FDwfEnumSN(
                self.get_device_id() as c_int,
                serial.as_mut_ptr(),
            ))?;

            Ok(CStr::from_ptr(mem::transmute(serial.as_mut_ptr()))
                .to_str()
                .unwrap()
                .to_owned())
        }
    }
}
