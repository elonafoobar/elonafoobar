use crate::api::class_color::Color;
use anyhow::Result;
use elonafoobar_gui::Image as GuiImage;
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::{LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;

const MODULE_NAME: &str = "graphics.Image";

pub struct Image(pub(super) GuiImage);

impl LuaUserdata for Image {
    const NAME: &'static str = "__native.graphics.Image";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", Image::NAME);
    lua.bind_class::<Image, _>(|lua| -> Result<()> {
        lua.set_function("set_alpha_mod", lua_set_alpha_mod)?;
        lua.set_function("set_color_mod", lua_set_color_mod)?;
        Ok(())
    })
}

#[lua_function]
fn lua_set_alpha_mod(self_: &mut Image, alpha: LuaInt) {
    self_.0.set_alpha_mod(clamp(alpha));
}

#[lua_function]
fn lua_set_color_mod(self_: &mut Image, color: &Color) {
    self_.0.set_color_mod(color.0);
}
