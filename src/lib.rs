use crate::Error::FailToGetErrorMessage;
use std::ffi::CStr;
use std::mem;

pub mod device;
pub mod dwf;

pub type Result<T> = std::result::Result<T, Error>;

#[derive(PartialEq, Debug)]
pub enum LibError {
    NoError,
    Unknown,
    ApiLockTimeout,
    AlreadyOpened,
    NotSupported,
    InvalidParameter0,
    InvalidParameter1,
    InvalidParameter2,
    InvalidParameter3,
    InvalidParameter4,
}

impl From<dwf::DWFERC> for LibError {
    fn from(error: dwf::DWFERC) -> Self {
        use LibError::*;

        match error {
            dwf::dwfercNoErc => NoError,
            dwf::dwfercUnknownError => Unknown,
            dwf::dwfercApiLockTimeout => ApiLockTimeout,
            dwf::dwfercAlreadyOpened => AlreadyOpened,
            dwf::dwfercNotSupported => NotSupported,
            dwf::dwfercInvalidParameter0 => InvalidParameter0,
            dwf::dwfercInvalidParameter1 => InvalidParameter1,
            dwf::dwfercInvalidParameter2 => InvalidParameter2,
            dwf::dwfercInvalidParameter3 => InvalidParameter3,
            dwf::dwfercInvalidParameter4 => InvalidParameter4,
            _ => Unknown,
        }
    }
}

#[derive(PartialEq, Debug)]
pub enum Error {
    FailToRun,
    FailToGetErrorCode,
    FailToGetErrorMessage,
    FailWithErrorCode(LibError),
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
            let error = LibError::from(error_code);
            if error == LibError::NoError {
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
