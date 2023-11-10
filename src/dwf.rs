#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
pub type BOOL = ::std::os::raw::c_int;
pub type BYTE = ::std::os::raw::c_uchar;

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));

pub fn to_c_bool(v: bool) -> BOOL {
    if v {
        true_ as BOOL
    } else {
        false_ as BOOL
    }
}

pub fn from_c_bool(v: BOOL) -> bool {
    v == true_ as i32 as BOOL
}

#[derive(PartialEq, Debug)]
pub enum DwfError {
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

impl From<DWFERC> for DwfError {
    fn from(error: DWFERC) -> Self {
        use DwfError::*;

        match error {
            dwfercNoErc => NoError,
            dwfercUnknownError => Unknown,
            dwfercApiLockTimeout => ApiLockTimeout,
            dwfercAlreadyOpened => AlreadyOpened,
            dwfercNotSupported => NotSupported,
            dwfercInvalidParameter0 => InvalidParameter0,
            dwfercInvalidParameter1 => InvalidParameter1,
            dwfercInvalidParameter2 => InvalidParameter2,
            dwfercInvalidParameter3 => InvalidParameter3,
            dwfercInvalidParameter4 => InvalidParameter4,
            _ => Unknown,
        }
    }
}
