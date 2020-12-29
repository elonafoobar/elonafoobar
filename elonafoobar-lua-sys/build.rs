use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rustc-link-lib=lua");

    let bindings = bindgen::Builder::default()
        .header("lua/lua.h")
        .header("lua/lauxlib.h")
        .header("lua/lualib.h")
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        .generate()
        .expect("`bindgen` failed to generate bindings.");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("`bindgen` failed to write generated bindings.");
}
