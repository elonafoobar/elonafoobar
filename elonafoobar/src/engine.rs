use crate::api::{self, App};
use crate::config::Config;
use crate::fs::{dirs, files};
use crate::version::VARIANT_SHORT_STRING;
use anyhow::Result;
use elonafoobar_gui::FullscreenType;
use elonafoobar_lua::Lua;

pub struct Engine {
    lua: Lua,
    cfg: Config,
}

impl Engine {
    pub fn new(cfg: Config) -> Result<Engine> {
        Ok(Engine {
            lua: Lua::new()?,
            cfg,
        })
    }

    pub fn open_builtin_libraries(&mut self) -> Result<()> {
        self.lua.open_builtin_libraries();
        Ok(())
    }

    pub fn bind_native_libraries(&mut self) -> Result<()> {
        api::bind(&mut self.lua)
    }

    pub fn run(mut self) -> Result<()> {
        let app = self.create_new_app()?;
        self.lua.set_load_path(&dirs::script())?;
        self.lua.load(&files::entry_point())?;
        self.lua.call((app, self.cfg.profile.to_string()))?;
        Ok(())
    }

    fn create_new_app(&self) -> Result<App> {
        let title = format!("Elona foobar version {}", VARIANT_SHORT_STRING);
        let display_mode = self.cfg.display_mode.as_deref().unwrap_or("");
        let fullscreen = match self.cfg.fullscreen.as_deref() {
            Some("windowed") => FullscreenType::Off,
            Some("fullscreen") => FullscreenType::True,
            Some("fullscreen_windowed") => FullscreenType::Desktop,
            _ => FullscreenType::Off,
        };

        App::new(&title, display_mode, fullscreen)
    }
}
