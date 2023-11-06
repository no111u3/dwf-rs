use crate::device::Device;
use crate::device_info::DeviceId;
use crate::dwf;
use crate::dwf::to_c_bool;
use crate::{check_call, Result};
use std::ffi::c_int;
use std::mem;

pub struct AnalogIn<'a> {
    device: &'a Device,
}

impl<'a> AnalogIn<'a> {
    pub fn new(device: &'a Device) -> AnalogIn<'a> {
        Self { device }
    }
    pub fn start(&self) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInConfigure(
                self.device.get_handle(),
                to_c_bool(false),
                to_c_bool(true),
            ))?;
        }
        Ok(())
    }

    pub fn set_frequency(&self, freq: f64) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInFrequencySet(
                self.device.get_handle(),
                freq,
            ))?;
        }
        Ok(())
    }

    pub fn set_record_mode(&self) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInAcquisitionModeSet(
                self.device.get_handle(),
                dwf::acqmodeRecord,
            ))?;
        }
        Ok(())
    }

    pub fn set_record_length(&self, length: f64) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInRecordLengthSet(
                self.device.get_handle(),
                length,
            ))?;
        }
        Ok(())
    }

    pub fn get_status(&self) -> Result<AnalogAcquisitionStatus> {
        unsafe {
            let mut state = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfAnalogInStatus(
                self.device.get_handle(),
                to_c_bool(true),
                state.as_mut_ptr(),
            ))?;
            let state = state.assume_init();
            Ok(match state {
                dwf::DwfStateReady => AnalogAcquisitionStatus::Ready,
                dwf::DwfStateConfig => AnalogAcquisitionStatus::Config,
                dwf::DwfStatePrefill => AnalogAcquisitionStatus::Prefill,
                dwf::DwfStateArmed => AnalogAcquisitionStatus::Armed,
                dwf::DwfStateWait => AnalogAcquisitionStatus::Waiting,
                dwf::DwfStateRunning => AnalogAcquisitionStatus::Running,
                dwf::DwfStateDone => AnalogAcquisitionStatus::Done,
                // TODO: change to error code
                _ => panic!("Unknown state: {}", state),
            })
        }
    }

    pub fn get_record_status(&self) -> Result<(i32, i32, i32)> {
        unsafe {
            let mut available = mem::MaybeUninit::uninit();
            let mut lost = mem::MaybeUninit::uninit();
            let mut corrupted = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfAnalogInStatusRecord(
                self.device.get_handle(),
                available.as_mut_ptr(),
                lost.as_mut_ptr(),
                corrupted.as_mut_ptr(),
            ))?;
            Ok((
                available.assume_init(),
                lost.assume_init(),
                corrupted.assume_init(),
            ))
        }
    }

    // TODO: Rework to check channel index
    pub fn channel(&self, ix: i32) -> AnalogInChannel {
        AnalogInChannel {
            input: &self,
            ix: ix as c_int,
        }
    }
}

#[derive(Eq, PartialEq, Debug)]
pub enum AnalogAcquisitionStatus {
    Ready,
    Config,
    Prefill,
    Armed,
    Waiting,
    Running,
    Done,
}

pub struct AnalogInChannel<'a> {
    input: &'a AnalogIn<'a>,
    ix: c_int,
}

impl<'a> AnalogInChannel<'a> {
    pub fn set_range(&self, range: f64) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInChannelRangeSet(
                self.input.device.get_handle(),
                self.ix,
                range,
            ))?;
        }
        Ok(())
    }

    pub fn enable(&self) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInChannelEnableSet(
                self.input.device.get_handle(),
                self.ix,
                to_c_bool(true),
            ))?;
        }
        Ok(())
    }

    pub fn fetch_samples(&self, dest: &mut Vec<f64>, available: i32) -> Result<()> {
        unsafe {
            let original_len = dest.len();
            dest.reserve(available as usize);
            dest.set_len(original_len + available as usize);
            check_call(dwf::FDwfAnalogInStatusData(
                self.input.device.get_handle(),
                self.ix,
                dest.as_mut_ptr().offset(original_len as isize),
                available,
            ))?;
        }
        Ok(())
    }
}
