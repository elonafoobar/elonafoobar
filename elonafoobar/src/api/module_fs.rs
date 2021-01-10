use crate::fs::{dirs, files};
use crate::mods::{ModId, Version};
use anyhow::bail;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::Lua;
use elonafoobar_utils as utils;
use std::convert::{TryFrom, TryInto};
use std::path::{Path, PathBuf};

const MODULE_NAME: &str = "fs";

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

#[lua_function]
fn lua_exists(path: &Path) -> bool {
    path.exists()
}

#[lua_function]
fn lua_get_bundled_font_path() -> PathBuf {
    files::bundled_font()
}

#[lua_function]
fn lua_get_config_file_path(profile_id: &str) -> Result<PathBuf> {
    let profile_id = profile_id.to_owned().try_into()?;
    Ok(files::local_config(&profile_id))
}

#[lua_function]
fn lua_get_lua_full_path(mod_id: &str, version: &str, file_name: &str) -> Result<PathBuf> {
    let mod_id = ModId::try_from(mod_id.to_owned())?;
    let version = Version::parse(version)?;
    Ok(dirs::mod_of(&mod_id, &version).join(file_name))
}

#[lua_function]
fn lua_resolve_path_for_mod(path: &str) -> Result<String> {
    // TODO
    let path = path.replace("<_vanilla_>", utils::path::path_to_str(&dirs::root()));
    // TODO
    let path = path.replace(
        "<core>",
        utils::path::path_to_str(&dirs::root().join("mod").join("core@0.3.0")),
    );
    Ok(path)
}

#[lua_function]
fn lua_resolve_relative_path(
    lua: &mut Lua,
    mod_id: &str,
    version: &str,
    file_path: &str,
) -> Result<PathBuf> {
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
