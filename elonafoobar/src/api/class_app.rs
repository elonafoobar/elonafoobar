use crate::api::class_color::Color;
use anyhow::bail;
use anyhow::Result;
use elonafoobar_gui::{
    App as GuiApp, FontStyle, FullscreenType, Point, Rect, TextAlignment, TextBaseline,
};
use elonafoobar_log::trace;
use elonafoobar_lua::types::{LuaInt, LuaUserdata};
use elonafoobar_lua::Lua;
use elonafoobar_utils::math::clamp;
use std::path::Path;

pub struct App(GuiApp);

impl App {
    pub fn new(title: &str, display_mode: &str, fullscreen: FullscreenType) -> Result<App> {
        Ok(App(GuiApp::new(title, display_mode, fullscreen)?))
    }
}

impl LuaUserdata for App {
    const NAME: &'static str = "_native_.App.App";
}

pub fn bind(lua: &mut Lua) -> Result<()> {
    trace!("Bind {} class", App::NAME);
    lua.bind_class::<App, _>(|lua| -> Result<()> {
        lua.set_function("update", lua_update)?;
        lua.set_function("reset_graphic_context", lua_reset_graphic_context)?;
        lua.set_function("clear", lua_clear)?;
        lua.set_function("draw_line", lua_draw_line)?;
        lua.set_function("fill_rect", lua_fill_rect)?;
        lua.set_function("screen_width", lua_screen_width)?;
        lua.set_function("screen_height", lua_screen_height)?;
        lua.set_function("load_font", lua_load_font)?;
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

fn lua_update(args: &mut App) -> Result<bool> {
    trace!("native.App.App:update()");

    let app = args;
    Ok(app.0.update())
}

fn lua_reset_graphic_context(args: &mut App) -> Result<()> {
    trace!("native.App.App:reset_graphic_context()");

    let self_ = args;
    let _ = self_;
    // TODO

    Ok(())
}

fn lua_clear(args: (&mut App, &Color)) -> Result<()> {
    trace!("native.App.App:clear()");

    let (self_, color) = args;
    self_.0.clear(color.0);

    Ok(())
}

fn lua_draw_line(args: (&mut App, LuaInt, LuaInt, LuaInt, LuaInt, &Color)) -> Result<()> {
    trace!("native.App.App:draw_line()");

    let (self_, x1, y1, x2, y2, color) = args;
    self_.0.draw_line(
        Point::new(clamp(x1), clamp(y1)),
        Point::new(clamp(x2), clamp(y2)),
        color.0,
    )?;

    Ok(())
}

fn lua_fill_rect(args: (&mut App, LuaInt, LuaInt, LuaInt, LuaInt, &Color)) -> Result<()> {
    trace!("native.App.App:fill_rect()");

    let (self_, x, y, w, h, color) = args;
    self_
        .0
        .fill_rect(Rect::new(clamp(x), clamp(y), clamp(w), clamp(h)), color.0)?;

    Ok(())
}

fn lua_screen_width(args: &App) -> Result<LuaInt> {
    trace!("native.App.App:screen_width()");

    let app = args;
    Ok(app.0.screen_width().into())
}

fn lua_screen_height(args: &App) -> Result<LuaInt> {
    trace!("native.App.App:screen_height()");

    let app = args;
    Ok(app.0.screen_height().into())
}

fn lua_load_font(args: (&mut App, &str, LuaInt)) -> Result<()> {
    trace!("native.App.App:load_font()");

    let (self_, path, point_size) = args;
    self_
        .0
        .load_font(&Path::new(path), clamp(point_size), FontStyle::NORMAL)?;

    Ok(())
}

fn lua_set_text_alignment(args: (&mut App, LuaInt)) -> Result<()> {
    trace!("native.App.App:set_text_alignment()");

    let (self_, alignment) = args;
    let alignment = match alignment {
        0 => TextAlignment::Left,
        1 => TextAlignment::Center,
        2 => TextAlignment::Right,
        _ => bail!("unknown text alignment: {}", alignment),
    };
    self_.0.set_text_alignment(alignment);

    Ok(())
}

fn lua_set_text_baseline(args: (&mut App, LuaInt)) -> Result<()> {
    trace!("native.App.App:set_text_baseline()");

    let (self_, baseline) = args;
    let baseline = match baseline {
        0 => TextBaseline::Top,
        1 => TextBaseline::Middle,
        2 => TextBaseline::Bottom,
        _ => bail!("unknown text alignment: {}", baseline),
    };
    self_.0.set_text_baseline(baseline);

    Ok(())
}

fn lua_draw_text(args: (&mut App, &str, LuaInt, LuaInt, &Color)) -> Result<()> {
    trace!("native.App.App:draw_text()");

    let (self_, text, x, y, color) = args;
    self_
        .0
        .draw_text(text, Point::new(clamp(x), clamp(y)), color.0)?;

    Ok(())
}

fn lua_draw_text_with_shadow(args: (&mut App, &str, LuaInt, LuaInt, &Color, &Color)) -> Result<()> {
    trace!("native.App.App:draw_text_with_shadow()");

    let (self_, text, x, y, text_color, shadow_color) = args;
    self_.0.draw_text_with_shadow(
        text,
        Point::new(clamp(x), clamp(y)),
        text_color.0,
        shadow_color.0,
    )?;

    Ok(())
}

fn lua_load_music(args: (&mut App, &str)) -> Result<()> {
    trace!("native.App.App:load_music()");

    let (self_, path) = args;
    self_.0.load_music(&Path::new(path))?;

    Ok(())
}

fn lua_play_music(args: (&mut App, LuaInt)) -> Result<()> {
    trace!("native.App.App:play_music()");

    let (self_, loops) = args;
    self_.0.play_music(clamp(loops))?;

    Ok(())
}

fn lua_stop_music(args: &App) -> Result<()> {
    trace!("native.App.App:stop_music()");

    let self_ = args;
    self_.0.stop_music();

    Ok(())
}

fn lua_get_music_volume(args: &App) -> Result<LuaInt> {
    trace!("native.App.App:get_music_volume()");

    let self_ = args;
    Ok(self_.0.get_music_volume().into())
}

fn lua_set_music_volume(args: (&App, LuaInt)) -> Result<()> {
    trace!("native.App.App:set_music_volume()");

    let (self_, volume) = args;
    self_.0.set_music_volume(clamp(volume));

    Ok(())
}
