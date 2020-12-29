use anyhow::Result;
use elonafoobar_lua::Lua;

mod class_app;
mod class_color;
mod class_mods;
mod module_fs;
mod module_graphics;
mod module_i18n;
mod module_log;
mod module_mods;
mod module_random;

pub use class_app::App;

pub fn bind(lua: &mut Lua) -> Result<()> {
    lua.bind_toplevel_module("native", |lua| -> Result<()> {
        // Classes
        class_app::bind(lua)?;
        class_color::bind(lua)?;
        class_mods::bind(lua)?;

        // Modules
        module_fs::bind(lua)?;
        module_graphics::bind(lua)?;
        module_i18n::bind(lua)?;
        module_log::bind(lua)?;
        module_mods::bind(lua)?;
        module_random::bind(lua)?;

        Ok(())
    })
}
