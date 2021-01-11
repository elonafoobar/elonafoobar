use anyhow::Result;
use elonafoobar_gui::Color as GuiColor;
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::{LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;

const MODULE_NAME: &str = "graphics.Color";

#[derive(Debug, Clone)]
pub struct Color(pub(super) GuiColor);

impl LuaUserdata for Color {
    const NAME: &'static str = "__native.graphics.Color";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", Color::NAME);
    lua.bind_class::<Color, _>(|lua| -> Result<()> {
        lua.set_function("rgb", lua_rgb)?;
        lua.set_function("rgba", lua_rgba)?;
        Ok(())
    })
}

#[lua_function]
fn lua_rgb(r: LuaInt, g: LuaInt, b: LuaInt) -> Color {
    Color(GuiColor::RGB(clamp(r), clamp(g), clamp(b)))
}

#[lua_function]
fn lua_rgba(r: LuaInt, g: LuaInt, b: LuaInt, a: LuaInt) -> Color {
    Color(GuiColor::RGBA(clamp(r), clamp(g), clamp(b), clamp(a)))
}
