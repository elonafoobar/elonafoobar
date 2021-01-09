use crate::api::class_rngs::DefaultGenerator;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.random module");
    lua.bind_module("random", |lua| -> Result<()> {
        lua.set_userdata_metatable("DefaultGenerator", DefaultGenerator::NAME)?;
        Ok(())
    })
}
