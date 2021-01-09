use crate::api::class_app::App;
use anyhow::Result;
use elonafoobar_log::trace;
use elonafoobar_lua::types::LuaUserdata;
use elonafoobar_lua::Lua;

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.App module");
    lua.bind_module("App", |lua| -> Result<()> {
        lua.set_userdata_metatable("App", App::NAME)?;
        Ok(())
    })
}
