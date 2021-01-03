use crate::fs::{dirs, files};
use crate::mods::{ModId, Version};
use anyhow::bail;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::Lua;
use elonafoobar_utils as utils;
use std::convert::{TryFrom, TryInto};
use std::path::{Path, PathBuf};

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Fs module");
    lua.bind_module("Fs", |lua| -> Result<()> {
        lua.set_function("exists", lua_exists)?;
        lua.set_function("get_bundled_font_path", lua_get_bundled_font_path)?;
        lua.set_function("get_config_file_path", lua_get_config_file_path)?;
        lua.set_function("get_lua_full_path", lua_get_lua_full_path)?;
        lua.set_function("resolve_path_for_mod", lua_resolve_path_for_mod)?;
        lua.set_function_with_state("resolve_relative_path", lua_resolve_relative_path)?;
        Ok(())
    })
}

fn lua_exists(args: &str) -> Result<bool> {
    trace!("native.Fs.exists()");

    let path = args;

    Ok(Path::new(path).exists())
}

fn lua_get_bundled_font_path(_args: ()) -> Result<PathBuf> {
    trace!("native.Fs.get_bundled_font_path()");

    Ok(files::bundled_font())
}

fn lua_get_config_file_path(args: &str) -> Result<PathBuf> {
    trace!("native.Fs.get_config_file_path()");

    let profile_id = args;

    Ok(files::local_config(&profile_id.to_owned().try_into()?))
}

fn lua_get_lua_full_path(args: (&str, &str, &str)) -> Result<PathBuf> {
    trace!("native.Fs.get_lua_full_path()");

    let (mod_id, version, file_name) = args;
    let mod_id = ModId::try_from(mod_id.to_owned())?;
    let version = Version::parse(version)?;

    Ok(dirs::mod_of(&mod_id, &version).join(file_name))
}

fn lua_resolve_path_for_mod(args: &str) -> Result<String> {
    trace!("native.Fs.resolve_path_for_mod()");

    let path = args;

    // TODO
    let path = path.replace("<_vanilla_>", utils::path::path_to_str(&dirs::root()));
    // TODO
    let path = path.replace(
        "<core>",
        utils::path::path_to_str(&dirs::root().join("mod").join("core@0.3.0")),
    );
    Ok(path)
}

fn lua_resolve_relative_path(lua: &mut Lua, args: (&str, &str, &str)) -> Result<PathBuf> {
    trace!("native.Fs.resolve_relative_path()");

    let (mod_id, version, file_path) = args;
    let mod_id = ModId::try_from(mod_id.to_owned())?;
    let version = Version::parse(version)?;

    if file_path.is_empty() {
        bail!("require(): invalid file path");
    }
    if file_path.as_bytes()[0] == b'/' {
        // '[0]' is safe because `file_path` is not empty here.
        // Relative path from the root directory of the mod.
        let file_path = std::str::from_utf8(&file_path.as_bytes()[1..])?; // trim the leading '/'
        let full_path = dirs::mod_of(&mod_id, &version).join(file_path);
        return Ok(full_path);
    }

    // Get the source file where the caller is defined.
    let caller_path = lua.get_caller_path()?;
    Ok(caller_path
        .parent()
        .expect("some fatal error in Lua runtime")
        .join(file_path))
}
