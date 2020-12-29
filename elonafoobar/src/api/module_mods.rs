use crate::api::class_mods::{self, Mods};
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Mods module");
    lua.bind_module("Mods", |lua| -> Result<()> {
        lua.set_userdata_metatable("Mods", Mods::NAME)?;
        lua.set_function("new", class_mods::lua_new)?;
        Ok(())
    })
}
