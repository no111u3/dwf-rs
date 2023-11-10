use crate::dwf::DwfError;
use crate::Error::FailToGetErrorMessage;
use std::ffi::CStr;
use std::mem;

pub mod analog;
pub mod device;
pub mod device_info;
pub mod dwf;

pub type Result<T> = std::result::Result<T, Error>;

#[derive(PartialEq, Debug)]
pub enum Error {
    FailToRun,
    FailToGetErrorCode,
    FailToGetErrorMessage,
    FailWithErrorCode(DwfError),
}

impl Error {
    pub fn get_error_message(&self) -> Result<String> {
        unsafe {
            let mut error_message = [0i8; 512];
            if dwf::from_c_bool(dwf::FDwfGetLastErrorMsg(error_message.as_mut_ptr())) {
                Ok(CStr::from_ptr(mem::transmute(error_message.as_mut_ptr()))
                    .to_str()
                    .unwrap()
                    .to_owned())
            } else {
                Err(FailToGetErrorMessage)
            }
        }
    }
}

fn check_call(status: dwf::BOOL) -> Result<()> {
    if dwf::from_c_bool(status) {
        Ok(())
    } else {
        Err(get_error_code())
    }
}

fn get_error_code() -> Error {
    unsafe {
        let mut error_code = mem::MaybeUninit::uninit();
        if dwf::from_c_bool(dwf::FDwfGetLastError(
            (error_code.as_mut_ptr()) as *mut dwf::DWFERC,
        )) {
            let error_code = error_code.assume_init();
            let error = DwfError::from(error_code);
            if error == DwfError::NoError {
                Error::FailToRun
            } else {
                Error::FailWithErrorCode(error)
            }
        } else {
            Error::FailToGetErrorCode
        }
    }
}

pub fn get_version() -> Result<String> {
    let mut version = [0i8; 32];
    unsafe {
        check_call(dwf::FDwfGetVersion(version.as_mut_ptr()))?;

        Ok(CStr::from_ptr(mem::transmute(version.as_mut_ptr()))
            .to_str()
            .unwrap()
            .to_owned())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn check_version() {
        let version = get_version().unwrap();
        // TODO: library bindgen generated from current version of dwf.h (3.20.1), need to update in
        // TODO: future as changed
        assert_eq!(version, "3.20.1".to_string());
    }

    #[test]
    fn check_error_code() {
        let error = get_error_code();

        assert_eq!(error, Error::FailToRun);
        assert_eq!(error.get_error_message(), Ok("".to_string()));
    }
}
