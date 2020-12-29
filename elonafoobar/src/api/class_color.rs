use anyhow::Result;
use elonafoobar_gui::Color as GuiColor;
use elonafoobar_log::trace;
use elonafoobar_lua::types::{LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;

#[derive(Debug, Clone)]
pub struct Color(pub(super) GuiColor);

impl LuaUserdata for Color {
    const NAME: &'static str = "_native_.Graphics.Color";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", Color::NAME);
    lua.bind_class::<Color, _>(|lua| -> Result<()> {
        lua.set_function("rgb", lua_rgb)?;
        Ok(())
    })
}

fn lua_rgb(args: (LuaInt, LuaInt, LuaInt)) -> Result<Color> {
    trace!("native.Graphics.Color.rgb()");

    let (r, g, b) = args;
    Ok(Color(GuiColor::RGB(clamp(r), clamp(g), clamp(b))))
}
