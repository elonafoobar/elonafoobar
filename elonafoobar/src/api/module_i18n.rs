use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaInt;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.I18n module");
    lua.bind_module("I18n", |lua| -> Result<()> {
        lua.set_function("parse_fmt", lua_parse_fmt)?;
        Ok(())
    })
}

fn lua_parse_fmt(args: &str) -> Result<(LuaInt, Option<String>)> {
    trace!("native.I18n.parse_fmt()");

    let fmt = args;
    let _ = fmt;
    Ok((0, None))
}
