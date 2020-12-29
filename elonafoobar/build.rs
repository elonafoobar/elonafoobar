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
