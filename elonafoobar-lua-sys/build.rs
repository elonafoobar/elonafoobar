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

    cc::Build::new()
        .files(&[
            // Core
            "lua/lapi.c",
            "lua/lcode.c",
            "lua/lctype.c",
            "lua/ldebug.c",
            "lua/ldo.c",
            "lua/ldump.c",
            "lua/lfunc.c",
            "lua/lgc.c",
            "lua/llex.c",
            "lua/lmem.c",
            "lua/lobject.c",
            "lua/lopcodes.c",
            "lua/lparser.c",
            "lua/lstate.c",
            "lua/lstring.c",
            "lua/ltable.c",
            "lua/ltm.c",
            "lua/lundump.c",
            "lua/lvm.c",
            "lua/lzio.c",
            // "lua/ltests.c", // testing only
            "lua/lauxlib.c",
            // Libraries
            "lua/lbaselib.c",
            "lua/ldblib.c",
            "lua/liolib.c",
            "lua/lmathlib.c",
            "lua/loslib.c",
            "lua/ltablib.c",
            "lua/lstrlib.c",
            "lua/lutf8lib.c",
            "lua/loadlib.c",
            "lua/lcorolib.c",
            "lua/linit.c",
        ])
        .compile("lua");
}
