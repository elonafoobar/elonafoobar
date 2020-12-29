use crate::fs::files;
use crate::mods::{self, ModId, ModManifest, ResolvedModList};
use anyhow::format_err;
use anyhow::Result;
use elonafoobar_log::{debug, trace};
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;
use std::collections::HashMap;

pub struct Mods {
    resolved_mod_list: Option<ResolvedModList>,
    mods: Option<HashMap<ModId, ModManifest>>,
}

impl LuaUserdata for Mods {
    const NAME: &'static str = "_native_.Mods.Mods";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", Mods::NAME);
    lua.bind_class::<Mods, _>(|lua| -> Result<()> {
        lua.set_function("new", lua_new)?;
        lua.set_function("resolve_versions", lua_resolve_versions)?;
        lua.set_function("install", lua_install)?;
        lua.set_function("scan_metadata", lua_scan_metadata)?;
        lua.set_function("get_resolved_mod_list", lua_get_resolved_mod_list)?;
        Ok(())
    })
}

pub fn lua_new(_args: ()) -> Result<Mods> {
    trace!("native.Mods.Mods.new()");

    Ok(Mods {
        resolved_mod_list: None,
        mods: None,
    })
}

fn lua_resolve_versions(args: &mut Mods) -> Result<()> {
    trace!("native.Mods.Mods:resolve_versions()");

    let self_ = args;
    self_.resolved_mod_list = Some(mods::resolve()?);
    Ok(())
}

fn lua_install(_args: &mut Mods) -> Result<()> {
    trace!("native.Mods.Mods:install()");
    // TODO
    Ok(())
}

fn lua_scan_metadata(args: &mut Mods) -> Result<()> {
    trace!("native.Mods.Mods:scan_metadata()");

    let self_ = args;

    let resolved_mod_list = self_.resolved_mod_list.as_ref().ok_or_else(|| {
        format_err!("Call `Mods:resolve_versions() before calling `Mods:scan_metadata()`")
    })?;

    let mut mods = HashMap::new();
    for mod_id in &resolved_mod_list.sorted_mods {
        let version = resolved_mod_list
            .versions
            .get(mod_id)
            .expect("ResolvedModList must have the entry");
        let manifest = ModManifest::from_file(&files::manifest_of(mod_id, version))?;
        mods.insert(mod_id.clone(), manifest);
    }
    debug!("{:?}", mods);
    self_.mods = Some(mods);
    Ok(())
}

fn lua_get_resolved_mod_list(args: &mut Mods) -> Result<Vec<Vec<String>>> {
    trace!("native.Mods.Mods:get_resolved_mod_list()");

    let self_ = args;

    let resolved_mod_list = self_.resolved_mod_list.as_ref().ok_or_else(|| {
        format_err!("Call `Mods:resolve_versions() before calling `Mods:get_resolved_mod_list()`")
    })?;

    let mut mods = Vec::new();
    for mod_id in &resolved_mod_list.sorted_mods {
        let version = resolved_mod_list
            .versions
            .get(mod_id)
            .expect("ResolvedModList must have the entry");
        mods.push(vec![mod_id.to_string(), version.to_string()]);
    }

    Ok(mods)
}
