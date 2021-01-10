use crate::api::class_mods::Mods;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Mods module");
    lua.bind_module("Mods", |lua| -> Result<()> {
        lua.set_userdata_metatable("Mods", Mods::NAME)?;
        Ok(())
    })
}
