use crate::device::Device;
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

    pub fn reconfigure_start(&self) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInConfigure(
                self.device.get_handle(),
                to_c_bool(true),
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

    pub fn set_trigger_source(&self, trigger_source: TriggerSource) -> Result<()> {
        let trigger_source = match trigger_source {
            TriggerSource::None => dwf::trigsrcNone,
            TriggerSource::PC => dwf::trigsrcPC,
            TriggerSource::AnalogIn => dwf::trigsrcAnalogIn,
            TriggerSource::DigitalIn => dwf::trigsrcDigitalIn,
            TriggerSource::DigitalOut => dwf::trigsrcDigitalOut,
            TriggerSource::AnalogOut1 => dwf::trigsrcAnalogOut1,
            TriggerSource::AnalogOut2 => dwf::trigsrcAnalogOut2,
            TriggerSource::AnalogOut3 => dwf::trigsrcAnalogOut3,
            TriggerSource::AnalogOut4 => dwf::trigsrcAnalogOut4,
            TriggerSource::External1 => dwf::trigsrcExternal1,
            TriggerSource::External2 => dwf::trigsrcExternal2,
            TriggerSource::External3 => dwf::trigsrcExternal3,
            TriggerSource::External4 => dwf::trigsrcExternal4,
            TriggerSource::High => dwf::trigsrcHigh,
            TriggerSource::Low => dwf::trigsrcLow,
            TriggerSource::Clock => dwf::trigsrcClock,
        };
        unsafe {
            check_call(dwf::FDwfAnalogInTriggerSourceSet(
                self.device.get_handle(),
                trigger_source,
            ))?;
        }
        Ok(())
    }

    pub fn set_trigger_type(&self, trigger_type: TriggerType) -> Result<()> {
        let trigger_type = match trigger_type {
            TriggerType::Edge => dwf::trigtypeEdge,
            TriggerType::Pulse => dwf::trigtypePulse,
            TriggerType::Transition => dwf::trigtypeTransition,
            TriggerType::Window => dwf::trigtypeWindow,
        };
        unsafe {
            check_call(dwf::FDwfAnalogInTriggerTypeSet(
                self.device.get_handle(),
                trigger_type,
            ))?;
        }
        Ok(())
    }

    pub fn set_trigger_channel(&self, channel: i32) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInTriggerChannelSet(
                self.device.get_handle(),
                channel,
            ))?;
        }
        Ok(())
    }

    pub fn set_trigger_level(&self, level: f64) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInTriggerLevelSet(
                self.device.get_handle(),
                level,
            ))?;
        }
        Ok(())
    }

    pub fn set_trigger_slope(&self, slope: TriggerSlope) -> Result<()> {
        let slope = match slope {
            TriggerSlope::Rise => dwf::DwfTriggerSlopeRise,
            TriggerSlope::Fall => dwf::DwfTriggerSlopeFall,
            TriggerSlope::Either => dwf::DwfTriggerSlopeEither,
        };
        unsafe {
            check_call(dwf::FDwfAnalogInTriggerConditionSet(
                self.device.get_handle(),
                slope,
            ))?
        }
        Ok(())
    }

    pub fn set_buffer_size(&self, size: i32) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInBufferSizeSet(
                self.device.get_handle(),
                size,
            ))?;
        }
        Ok(())
    }

    pub fn get_buffer_size(&self) -> Result<i32> {
        unsafe {
            let mut size = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfAnalogInBufferSizeGet(
                self.device.get_handle(),
                size.as_mut_ptr(),
            ))?;

            Ok(size.assume_init())
        }
    }

    pub fn set_counter_timeout(&self, timeout: f64) -> Result<()> {
        unsafe {
            check_call(dwf::FDwfAnalogInCounterSet(
                self.device.get_handle(),
                timeout,
            ))?
        }
        Ok(())
    }
    pub fn get_counter_info(&self) -> Result<(f64, f64)> {
        unsafe {
            let mut count_max = mem::MaybeUninit::uninit();
            let mut time_max = mem::MaybeUninit::uninit();
            check_call(dwf::FDwfAnalogInCounterInfo(
                self.device.get_handle(),
                count_max.as_mut_ptr(),
                time_max.as_mut_ptr(),
            ))?;

            Ok((count_max.assume_init(), time_max.assume_init()))
        }
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
            input: self,
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

#[derive(Eq, PartialEq, Debug)]
pub enum TriggerSource {
    None,
    PC,
    AnalogIn,
    DigitalIn,
    DigitalOut,
    AnalogOut1,
    AnalogOut2,
    AnalogOut3,
    AnalogOut4,
    External1,
    External2,
    External3,
    External4,
    High,
    Low,
    Clock,
}

#[derive(Eq, PartialEq, Debug)]
pub enum TriggerType {
    Edge,
    Pulse,
    Transition,
    Window,
}

#[derive(Eq, PartialEq, Debug)]
pub enum TriggerSlope {
    Rise,
    Fall,
    Either,
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

    pub fn set_filter(&self, filter: AnalogFilter) -> Result<()> {
        unsafe {
            let filter = {
                match filter {
                    AnalogFilter::Average => dwf::filterAverage,
                    AnalogFilter::Decimate => dwf::filterDecimate,
                    AnalogFilter::MinMax => dwf::filterMinMax,
                }
            };
            check_call(dwf::FDwfAnalogInChannelFilterSet(
                self.input.device.get_handle(),
                self.ix,
                filter,
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
            let remaining = dest.spare_capacity_mut();
            check_call(dwf::FDwfAnalogInStatusData(
                self.input.device.get_handle(),
                self.ix,
                remaining.as_mut_ptr() as *mut f64,
                available,
            ))?;
            dest.set_len(original_len + available as usize);
        }
        Ok(())
    }
}

pub enum AnalogFilter {
    Decimate,
    Average,
    MinMax,
}
