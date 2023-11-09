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
