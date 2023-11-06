#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

pub const __bool_true_false_are_defined: u32 = 1;
pub const true_: u32 = 1;
pub const false_: u32 = 0;
pub type BOOL = ::std::os::raw::c_int;
pub type BYTE = ::std::os::raw::c_uchar;

include!("dwf_bind.rs");

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
