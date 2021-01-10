use anyhow::format_err;
use anyhow::Result;
use elonafoobar_log::{log, trace, Level as LogLevel};
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::LuaInt;
use elonafoobar_lua::{AsLuaInt, FromLuaInt, IntoLuaInt, Lua};

const MODULE_NAME: &str = "log";

struct Level(LogLevel);

impl FromLuaInt for Level {
    fn from_lua_int(value: LuaInt) -> Result<Level> {
        match value {
            5 => Ok(Level(LogLevel::Error)),
            4 => Ok(Level(LogLevel::Warn)),
            3 => Ok(Level(LogLevel::Info)),
            2 => Ok(Level(LogLevel::Debug)),
            1 => Ok(Level(LogLevel::Trace)),
            n => Err(format_err!("invalid Log.Level: {}", n)),
        }
    }
}

impl IntoLuaInt for Level {
    fn into_lua_int(self) -> Result<LuaInt> {
        match self.0 {
            LogLevel::Error => Ok(5),
            LogLevel::Warn => Ok(4),
            LogLevel::Info => Ok(3),
            LogLevel::Debug => Ok(2),
            LogLevel::Trace => Ok(1),
        }
    }
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind native.Log module");
    lua.bind_module("Log", |lua| -> Result<()> {
        lua.set_function("log", lua_log)?;
        lua.set_function("level", lua_level)?;
        lua.set_function("set_level", lua_set_level)?;
        Ok(())
    })
}

#[lua_function(log = false)]
fn lua_log(level: AsLuaInt<Level>, mod_name: &str, message: &str) {
    log(mod_name, (level.0).0, message);
}

#[lua_function]
fn lua_level() -> AsLuaInt<Level> {
    AsLuaInt(Level(elonafoobar_log::level()))
}

#[lua_function]
fn lua_set_level(level: AsLuaInt<Level>) {
    elonafoobar_log::set_level((level.0).0);
}
