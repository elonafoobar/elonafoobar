use anyhow::{format_err, Result};
use fs_extra::dir::CopyOptions;
use regex::Regex;
use std::env;
use std::fs;
use std::path::Path;
use vergen::{generate_cargo_keys, ConstantsFlags};

fn main() -> Result<()> {
    output_cargo_flags()?;
    copy_runtime_dir()?;
    rename_mod_dir()?;
    output_mod_core_version()?;
    Ok(())
}

// Generate the 'cargo:' key output for src/version.rs.
fn output_cargo_flags() -> Result<()> {
    let flags = ConstantsFlags::SHA_SHORT
        | ConstantsFlags::TARGET_TRIPLE
        | ConstantsFlags::REBUILD_ON_HEAD_CHANGE;
    generate_cargo_keys(flags).map_err(|err| format_err!(err.to_string()))
}

// Copy whole contents in `runtime` directory to the build directory.
fn copy_runtime_dir() -> Result<()> {
    // TODO: better way to get these paths?
    let runtime_dir = Path::new("../runtime");
    let exe_dir = Path::new("../target").join(env::var("PROFILE").unwrap());
    let copy_options = CopyOptions {
        overwrite: true,
        content_only: true,
        ..CopyOptions::default()
    };
    fs_extra::dir::copy(runtime_dir, exe_dir, &copy_options)?;
    Ok(())
}

fn rename_mod_dir() -> Result<()> {
    let version_pattern = Regex::new(r#"version: "(.+?)""#).unwrap();

    // TODO: better way to get these paths?
    let mod_root_dir = Path::new("../runtime/mod");
    let exe_dir = Path::new("../target").join(env::var("PROFILE").unwrap());
    for entry in fs::read_dir(mod_root_dir)? {
        let entry = entry?;
        let mod_dir = entry.path();
        let mod_name = entry
            .file_name()
            .into_string()
            .expect("mod directory name must be valid UTF-8");

        // Extract version identifier from manifest file.
        // Note: it is found by simple regex match, not complete JSON5 parsing.
        let manifest = fs::read_to_string(mod_dir.join("mod.json"))?;
        let version = version_pattern
            .captures(&manifest)
            .and_then(|captures| captures.get(1))
            .expect("failed to parse manifest file")
            .as_str();

        let from = exe_dir.join("mod").join(&mod_name);
        let to = exe_dir
            .join("mod")
            .join(format!("{}@{}", &mod_name, version));
        let copy_options = CopyOptions {
            overwrite: true,
            content_only: true,
            ..CopyOptions::default()
        };
        fs_extra::dir::move_dir(from, to, &copy_options)?;
    }
    Ok(())
}

// Generate mod 'core' version for src/version.rs.
fn output_mod_core_version() -> Result<()> {
    // TODO: better way to get these paths?
    let mod_root_dir = Path::new("../runtime/mod");
    let core_manifest_path = mod_root_dir.join("core").join("mod.json");

    println!(
        "cargo:rerun-if-changed={}",
        core_manifest_path.to_string_lossy()
    );

    let manifest = fs::read_to_string(core_manifest_path)?;
    let version_digits = Regex::new(r#"version: "(\d+)\.(\d+)\.(\d+)""#)
        .unwrap()
        .captures(&manifest)
        .expect("failed to parse version ID from core/mod.json");

    let core_major = version_digits.get(1).unwrap().as_str();
    let core_minor = version_digits.get(2).unwrap().as_str();
    let core_patch = version_digits.get(3).unwrap().as_str();

    println!("cargo:rustc-env=ELONAFOOBAR_MOD_CORE_MAJOR={}", core_major);
    println!("cargo:rustc-env=ELONAFOOBAR_MOD_CORE_MINOR={}", core_minor);
    println!("cargo:rustc-env=ELONAFOOBAR_MOD_CORE_PATCH={}", core_patch);

    Ok(())
}
