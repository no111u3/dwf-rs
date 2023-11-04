use crate::dwf;
use crate::{check_call, Result};
use std::ffi::c_int;

use std::mem;

pub struct Device {
    handle: dwf::HDWF,
}

impl Device {
    pub fn open(index: i32) -> Result<Device> {
        unsafe {
            let mut handle = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfDeviceOpen(index as c_int, handle.as_mut_ptr()))?;
            let handle = handle.assume_init();
            Ok(Device { handle })
        }
    }

    pub fn reset(&self) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfDeviceReset(self.handle as dwf::HDWF))?;
        }
        Ok(())
    }
}

impl Default for Device {
    fn default() -> Self {
        Device::open(-1).unwrap()
    }
}

impl Drop for Device {
    fn drop(&mut self) {
        unsafe {
            check_call(dwf::FDwfDeviceClose(self.handle as c_int)).unwrap();
        }
    }
}