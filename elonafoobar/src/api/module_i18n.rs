use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::LuaInt;
use elonafoobar_lua::Lua;

const MODULE_NAME: &str = "i18n";

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.I18n module");
    lua.bind_module("i18n", |lua| -> Result<()> {
        lua.set_function("parse_fmt", lua_parse_fmt)?;
        Ok(())
    })
}

#[lua_function]
fn lua_parse_fmt(fmt: &str) -> Result<LuaInt> {
    // TODO
    let _ = fmt;
    Ok(0)
}
