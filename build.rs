fn main() {
    println!("cargo:rustc-link-lib=framework=/Library/Frameworks/dwf.framework/dwf");
    println!("cargo:rustc-link-arg=-Wl,-rpath,/Library/Frameworks");
}