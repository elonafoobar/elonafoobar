use anyhow::format_err;
use anyhow::Result;
use elonafoobar_log::{log, trace, Level as LogLevel};
use elonafoobar_lua::types::LuaInt;
use elonafoobar_lua::{AsLuaInt, FromLuaInt, Lua, ToLuaInt};

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

impl ToLuaInt for Level {
    fn to_lua_int(self) -> Result<LuaInt> {
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

fn lua_log(args: (AsLuaInt<Level>, &str, &str)) -> Result<()> {
    trace!("native.Log.log()");

    let (level, mod_name, message) = args;
    log(mod_name, (level.0).0, message);
    Ok(())
}

fn lua_level(_args: ()) -> Result<AsLuaInt<Level>> {
    trace!("native.Log.level()");

    Ok(AsLuaInt(Level(elonafoobar_log::level())))
}

fn lua_set_level(args: AsLuaInt<Level>) -> Result<()> {
    trace!("native.Log.set_level()");

    let level = args;
    elonafoobar_log::set_level((level.0).0);
    Ok(())
}
