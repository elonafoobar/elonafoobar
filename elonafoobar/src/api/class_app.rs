use crate::api::class_color::Color;
use crate::api::class_image::Image;
use anyhow::Result;
use elonafoobar_gui::{
    App as GuiApp, FontStyle, FullscreenType, Point, Rect, TextAlignment, TextBaseline,
};
use elonafoobar_log::trace;
use elonafoobar_lua::macros::lua_function;
use elonafoobar_lua::types::{LuaInt, LuaUserdata, Warn};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;
use std::path::Path;

const MODULE_NAME: &str = "app.App";

pub struct App(GuiApp);

impl App {
    pub fn new(title: &str, display_mode: &str, fullscreen: FullscreenType) -> Result<App> {
        Ok(App(GuiApp::new(title, display_mode, fullscreen)?))
    }
}

impl LuaUserdata for App {
    const NAME: &'static str = "__native.app.App";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", App::NAME);
    lua.bind_class::<App, _>(|lua| -> Result<()> {
        lua.set_function("is_headless", lua_is_headless)?;
        lua.set_function("update", lua_update)?;
        lua.set_function("reset_graphic_context", lua_reset_graphic_context)?;
        lua.set_function("clear", lua_clear)?;
        lua.set_function("draw_line", lua_draw_line)?;
        lua.set_function("fill_rect", lua_fill_rect)?;
        lua.set_function("screen_width", lua_screen_width)?;
        lua.set_function("screen_height", lua_screen_height)?;
        lua.set_function("load_image", lua_load_image)?;
        lua.set_function("draw_image", lua_draw_image)?;
        lua.set_function("load_font", lua_load_font)?;
        lua.set_function("calculate_text_size", lua_calculate_text_size)?;
        lua.set_function("set_text_alignment", lua_set_text_alignment)?;
        lua.set_function("set_text_baseline", lua_set_text_baseline)?;
        lua.set_function("draw_text", lua_draw_text)?;
        lua.set_function("draw_text_with_shadow", lua_draw_text_with_shadow)?;
        lua.set_function("load_music", lua_load_music)?;
        lua.set_function("play_music", lua_play_music)?;
        lua.set_function("stop_music", lua_stop_music)?;
        lua.set_function("get_music_volume", lua_get_music_volume)?;
        lua.set_function("set_music_volume", lua_set_music_volume)?;
        Ok(())
    })
}

#[lua_function]
fn lua_is_headless(_self_: &App) -> bool {
    false
}

#[lua_function]
fn lua_update(self_: &mut App) -> bool {
    self_.0.update()
}

#[lua_function]
fn lua_reset_graphic_context(_self_: &mut App) {
    // TODO
}

#[lua_function]
fn lua_clear(self_: &mut App, color: &Color) {
    self_.0.clear(color.0);
}

#[lua_function]
fn lua_draw_line(
    self_: &mut App,
    x1: LuaInt,
    y1: LuaInt,
    x2: LuaInt,
    y2: LuaInt,
    color: &Color,
) -> Warn<()> {
    self_
        .0
        .draw_line(
            Point::new(clamp(x1), clamp(y1)),
            Point::new(clamp(x2), clamp(y2)),
            color.0,
        )
        .into()
}

#[lua_function]
fn lua_fill_rect(
    self_: &mut App,
    x: LuaInt,
    y: LuaInt,
    w: LuaInt,
    h: LuaInt,
    color: &Color,
) -> Warn<()> {
    self_
        .0
        .fill_rect(Rect::new(clamp(x), clamp(y), clamp(w), clamp(h)), color.0)
        .into()
}

#[lua_function]
fn lua_screen_width(self_: &App) -> LuaInt {
    self_.0.screen_width().into()
}

#[lua_function]
fn lua_screen_height(self_: &App) -> LuaInt {
    self_.0.screen_height().into()
}

#[lua_function]
fn lua_load_image(self_: &mut App, path: &Path, key_color: Option<&Color>) -> Result<Image> {
    self_.0.load_image(path, key_color.map(|x| x.0)).map(Image)
}

#[lua_function]
#[allow(clippy::too_many_arguments)]
fn lua_draw_image(
    self_: &mut App,
    image: &Image,
    src_x: LuaInt,
    src_y: LuaInt,
    src_width: LuaInt,
    src_height: LuaInt,
    dst_x: LuaInt,
    dst_y: LuaInt,
    dst_width: LuaInt,
    dst_height: LuaInt,
) -> Warn<()> {
    self_
        .0
        .draw_image(
            &image.0,
            Rect::new(
                clamp(src_x),
                clamp(src_y),
                clamp(src_width),
                clamp(src_height),
            ),
            Rect::new(
                clamp(dst_x),
                clamp(dst_y),
                clamp(dst_width),
                clamp(dst_height),
            ),
        )
        .into()
}

#[lua_function]
fn lua_load_font(self_: &mut App, path: &Path, point_size: LuaInt, style: LuaInt) -> Result<()> {
    let style = FontStyle::from_bits_truncate(style as _);
    self_.0.load_font(path, clamp(point_size), style)
}

#[lua_function]
fn lua_calculate_text_size(self_: &App, text: &str) -> Warn<(LuaInt, LuaInt)> {
    let result = self_.0.calculate_text_size(text);
    match result {
        Ok(size) => Warn::success((size.0.into(), size.1.into())),
        Err(err) => Warn::with_warning(
            (10 * (text.len() as LuaInt), 10), // estimate size (best effort)
            err,
        ),
    }
}

#[lua_function]
fn lua_set_text_alignment(self_: &mut App, alignment: LuaInt) -> Warn<()> {
    let alignment = match alignment {
        0 => TextAlignment::Left,
        1 => TextAlignment::Center,
        2 => TextAlignment::Right,
        _ => return Warn::with_warning((), format!("unknown text alignment: {}", alignment)),
    };
    self_.0.set_text_alignment(alignment);
    Warn::success(())
}

#[lua_function]
fn lua_set_text_baseline(self_: &mut App, baseline: LuaInt) -> Warn<()> {
    let baseline = match baseline {
        0 => TextBaseline::Top,
        1 => TextBaseline::Middle,
        2 => TextBaseline::Bottom,
        _ => return Warn::with_warning((), format!("unknown text baseline: {}", baseline)),
    };
    self_.0.set_text_baseline(baseline);
    Warn::success(())
}

#[lua_function]
fn lua_draw_text(self_: &mut App, text: &str, x: LuaInt, y: LuaInt, color: &Color) -> Warn<()> {
    let result = self_
        .0
        .draw_text(text, Point::new(clamp(x), clamp(y)), color.0);
    match result {
        Ok(_region) => Warn::success(()), // TODO: returns `region`
        Err(err) => Warn::with_warning((), err),
    }
}

#[lua_function]
fn lua_draw_text_with_shadow(
    self_: &mut App,
    text: &str,
    x: LuaInt,
    y: LuaInt,
    text_color: &Color,
    shadow_color: &Color,
) -> Warn<()> {
    let result = self_.0.draw_text_with_shadow(
        text,
        Point::new(clamp(x), clamp(y)),
        text_color.0,
        shadow_color.0,
    );
    match result {
        Ok(_region) => Warn::success(()), // TODO: returns `region`
        Err(err) => Warn::with_warning((), err),
    }
}

#[lua_function]
fn lua_load_music(self_: &mut App, path: &Path) -> Result<()> {
    self_.0.load_music(path)
}

#[lua_function]
fn lua_play_music(self_: &mut App, loops: LuaInt) -> Warn<()> {
    self_.0.play_music(clamp(loops)).into()
}

#[lua_function]
fn lua_stop_music(self_: &App) {
    self_.0.stop_music();
}

#[lua_function]
fn lua_get_music_volume(self_: &App) -> LuaInt {
    self_.0.get_music_volume().into()
}

#[lua_function]
fn lua_set_music_volume(self_: &App, volume: LuaInt) {
    self_.0.set_music_volume(clamp(volume));
}
