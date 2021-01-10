use crate::api::class_color::Color;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Graphics module");
    lua.bind_module("Graphics", |lua| -> Result<()> {
        lua.set_userdata_metatable("Color", Color::NAME)?;
        Ok(())
    })
}
