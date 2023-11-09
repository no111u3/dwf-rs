use std::env;
use std::path::PathBuf;
fn main() {
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    // TODO: implement this for other platforms
    if cfg!(target_os = "macos") {
        println!("cargo:rustc-link-lib=framework=/Library/Frameworks/dwf.framework/dwf");
        println!("cargo:rustc-link-arg=-Wl,-rpath,/Library/Frameworks");
    } else {
        unimplemented!("Mac OS is supported");
    }

    let bindings = bindgen::Builder::default()
        .header("wrapper.h")
        .clang_arg("-I/Library/Frameworks/dwf.framework/Headers")
        .generate()
        .expect("Unable to generate bindings");

    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
