use crate::api::class_color::Color;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Graphics module");
    lua.bind_module("Graphics", |lua| -> Result<()> {
        lua.set_userdata_metatable("Color", Color::NAME)?;

        lua.set_integer("TEXT_ALIGNMENT_LEFT", 0)?;
        lua.set_integer("TEXT_ALIGNMENT_CENTER", 1)?;
        lua.set_integer("TEXT_ALIGNMENT_RIGHT", 2)?;

        lua.set_integer("TEXT_BASELINE_TOP", 0)?;
        lua.set_integer("TEXT_BASELINE_MIDDLE", 1)?;
        lua.set_integer("TEXT_BASELINE_BOTTOM", 2)?;
        Ok(())
    })
}
