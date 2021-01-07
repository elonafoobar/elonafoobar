use crate::api::class_color::Color;
use anyhow::Result;
use elonafoobar_gui::Image as GuiImage;
use elonafoobar_log::trace;
use elonafoobar_lua::types::{LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;

pub struct Image(pub(super) GuiImage);

impl LuaUserdata for Image {
    const NAME: &'static str = "_native_.Graphics.Image";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", Image::NAME);
    lua.bind_class::<Image, _>(|lua| -> Result<()> {
        lua.set_function("set_alpha_mod", lua_set_alpha_mod)?;
        lua.set_function("set_color_mod", lua_set_color_mod)?;
        Ok(())
    })
}

fn lua_set_alpha_mod(args: (&mut Image, LuaInt)) -> Result<()> {
    trace!("native.Graphics.Image:set_alpha_mod()");

    let (self_, alpha) = args;
    self_.0.set_alpha_mod(clamp(alpha));
    Ok(())
}

fn lua_set_color_mod(args: (&mut Image, &Color)) -> Result<()> {
    trace!("native.Graphics.Image:set_color_mod()");

    let (self_, color) = args;
    self_.0.set_color_mod(color.0);
    Ok(())
}
