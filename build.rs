use std::env;
use std::path::{Path, PathBuf};
fn main() {
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    let mut include_path;
    if cfg!(target_os = "macos") {
        println!("cargo:rustc-link-lib=framework=/Library/Frameworks/dwf.framework/dwf");
        println!("cargo:rustc-link-arg=-Wl,-rpath,/Library/Frameworks");
        include_path = "/Library/Frameworks/dwf.framework/Headers";
    } else if cfg!(target_os = "windows") {
        println!("cargo:rustc-link-lib=dylib=dwf.dll");
        include_path = "C:\\Program Files (x86)\\Digilent\\WaveFormsSDK\\inc"
    } else if cfg!(target_os = "linux") {
        println!("cargo:rustc-link-lib=dylib=libdwf.so");
        include_path = "/usr/include/digilent/waveforms"
    } else {
        unimplemented!("Only Linux, Mac OS and Windows are supported");
    }

    if !Path::new(&include_path).exists() {
        include_path = "includes"
    }

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .clang_arg(format!("-I{}", include_path))
        .generate()
        .expect("Unable to generate bindings");

    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
