use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaInt;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Random module");
    lua.bind_module("Random", |lua| -> Result<()> {
        lua.set_function("rnd", lua_rnd)?;
        Ok(())
    })
}

fn lua_rnd(_args: LuaInt) -> Result<LuaInt> {
    trace!("native.Random.rnd()");

    // TODO
    Ok(0)
}
