use crate::audio::Audio;
use crate::error::SdlError;
use crate::font_cache::FontCache;
use crate::image::{Image, ImageContext};
use anyhow::{format_err, Result};
use sdl2::event::Event;
use sdl2::pixels::Color;
use sdl2::rect::{Point, Rect};
use sdl2::render::{Texture, WindowCanvas};
use sdl2::ttf::FontStyle;
use sdl2::video::{DisplayMode, FullscreenType};
use sdl2::{EventPump, Sdl, VideoSubsystem};
use std::path::Path;
use std::time::Duration;

// SDL context and its subsystems are dropped in a proper order within `sdl2` library. We don't
// need to manually handle drop order.
pub struct App {
    #[allow(dead_code)]
    sdl: Sdl,
    #[allow(dead_code)]
    video: VideoSubsystem,
    event_pump: EventPump,
    canvas: WindowCanvas,
    font_cache: FontCache,
    text_alignment: TextAlignment,
    text_baseline: TextBaseline,
    #[allow(dead_code)]
    image_context: ImageContext,
    audio: Audio,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TextAlignment {
    Left,
    Center,
    Right,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TextBaseline {
    Top,
    Middle,
    Bottom,
}

impl App {
    pub fn new(title: &str, display_mode: &str, fullscreen: FullscreenType) -> Result<App> {
        let sdl = sdl2::init().sdl_error()?;
        let video = sdl.video().sdl_error()?;
        let event_pump = sdl.event_pump().sdl_error()?;
        let font_cache = FontCache::new()?;
        let image_context = ImageContext::new()?;
        let audio = Audio::new()?;

        let display_mode = find_display_mode_by_name(&video, display_mode, 800, 600)?;
        // This `as u32` casting is safe because SDL should return positive value.
        let mut window = video
            .window(title, display_mode.w as u32, display_mode.h as u32)
            .build()?;
        window.set_display_mode(display_mode).sdl_error()?;
        window.set_fullscreen(fullscreen).sdl_error()?;

        let canvas = window.into_canvas().accelerated().present_vsync().build()?;

        video.text_input().start();
        // video.text_input().set_rect(TODO);

        Ok(App {
            sdl,
            video,
            event_pump,
            canvas,
            font_cache,
            text_alignment: TextAlignment::Left,
            text_baseline: TextBaseline::Middle,
            image_context,
            audio,
        })
    }

    pub fn update(&mut self) -> bool {
        self.canvas.present();

        // TODO: fps
        std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 60));

        for event in self.event_pump.poll_iter() {
            if let Event::Quit { .. } = event {
                return false;
            }
        }

        self.canvas.clear();
        true
    }

    pub fn screen_width(&self) -> u32 {
        self.canvas.window().size().0
    }

    pub fn screen_height(&self) -> u32 {
        self.canvas.window().size().1
    }

    pub fn clear(&mut self, color: Color) {
        self.canvas.set_draw_color(color);
        self.canvas.clear();
    }

    pub fn draw_line(&mut self, start: Point, end: Point, color: Color) -> Result<()> {
        self.canvas.set_draw_color(color);
        self.canvas.draw_line(start, end).sdl_error()?;
        Ok(())
    }

    pub fn fill_rect(&mut self, rect: Rect, color: Color) -> Result<()> {
        self.canvas.set_draw_color(color);
        self.canvas.fill_rect(rect).sdl_error()?;
        Ok(())
    }

    pub fn load_image(&mut self, path: &Path, color: Option<Color>) -> Result<Image> {
        Image::load_file(&self.canvas.texture_creator(), path, color)
    }

    pub fn draw_image(&mut self, image: &Image, src: Rect, dst: Rect) -> Result<()> {
        self.canvas.copy(image.as_texture(), src, dst).sdl_error()
    }

    pub fn draw_text(&mut self, text: &str, pos: Point, color: Color) -> Result<Rect> {
        if text.is_empty() {
            return Ok(Rect::new(pos.x(), pos.y(), 0, 0));
        }

        let text = truncate_long_text(text);
        self.draw_text_internal(text, pos, color, |canvas, texture, region_to_copy| {
            canvas.copy(&texture, None, region_to_copy).sdl_error()
        })
    }

    pub fn draw_text_with_shadow(
        &mut self,
        text: &str,
        pos: Point,
        text_color: Color,
        shadow_color: Color,
    ) -> Result<Rect> {
        if text.is_empty() {
            return Ok(Rect::new(pos.x(), pos.y(), 0, 0));
        }

        let text = truncate_long_text(text);

        // Shadow
        self.draw_text_internal(
            text,
            pos,
            shadow_color,
            |canvas, texture, region_to_copy| {
                for dy in &[-1, 0, 1] {
                    for dx in &[-1, 0, 1] {
                        if *dx == 0 && *dy == 0 {
                            continue;
                        }
                        let region_to_copy = Rect::new(
                            region_to_copy.x() + dx,
                            region_to_copy.y() + dy,
                            region_to_copy.width(),
                            region_to_copy.height(),
                        );
                        canvas.copy(&texture, None, region_to_copy).sdl_error()?;
                    }
                }
                Ok(())
            },
        )?;

        // Text
        self.draw_text(text, pos, text_color)
    }

    pub fn load_font(&mut self, path: &Path, point_size: u16, style: FontStyle) -> Result<()> {
        self.font_cache.load_font(path, point_size, style)
    }

    pub fn enable_blended_text_rendering(&mut self) {
        self.font_cache.set_blended_rendering(true);
    }

    pub fn disable_blended_text_rendering(&mut self) {
        self.font_cache.set_blended_rendering(false);
    }

    pub fn set_text_alignment(&mut self, alignment: TextAlignment) {
        self.text_alignment = alignment;
    }

    pub fn set_text_baseline(&mut self, baseline: TextBaseline) {
        self.text_baseline = baseline;
    }

    pub fn get_music_decoders(&self) -> Vec<String> {
        self.audio.get_music_decoders()
    }

    pub fn load_music(&mut self, path: &Path) -> Result<()> {
        self.audio.load_music(path)
    }

    pub fn play_music(&mut self, loops: i32) -> Result<()> {
        self.audio.play_music(loops)
    }

    pub fn stop_music(&self) {
        self.audio.stop_music();
    }

    pub fn get_music_volume(&self) -> u8 {
        self.audio.get_music_volume()
    }

    pub fn set_music_volume(&self, volume: u8) {
        self.audio.set_music_volume(volume);
    }

    fn draw_text_internal<F>(
        &mut self,
        text: &str,
        pos: Point,
        color: Color,
        draw: F,
    ) -> Result<Rect>
    where
        F: Fn(&mut WindowCanvas, &Texture, Rect) -> Result<()>,
    {
        let surface = self.font_cache.draw_text(text, color)?;
        let texture_creator = self.canvas.texture_creator();
        let mut texture = surface.as_texture(&texture_creator)?;
        texture.set_alpha_mod(color.a);

        let x = pos.x();
        let y = pos.y();
        let w = surface.width();
        let h = surface.height();
        // `as i32` casting is safe because surface width/height is small enough.
        let x = match self.text_alignment {
            TextAlignment::Left => x,
            TextAlignment::Center => x - (w as i32) / 2,
            TextAlignment::Right => x - (w as i32),
        };
        let y = match self.text_baseline {
            TextBaseline::Top => y,
            TextBaseline::Middle => y - (h as i32) / 2,
            TextBaseline::Bottom => y - (h as i32),
        };

        let region_to_copy = Rect::new(x, y, w, h);
        draw(&mut self.canvas, &texture, region_to_copy)?;
        Ok(region_to_copy)
    }
}

fn truncate_long_text(text: &str) -> &str {
    if text.len() >= 300 {
        // too long, truncate
        // TODO: the limit is proper or not?
        match text.char_indices().nth(100) {
            None => text,
            Some((idx, _)) => &text[..idx],
        }
    } else {
        text
    }
}

fn find_display_mode_by_name(
    video: &VideoSubsystem,
    display_mode_name: &str,
    min_screen_width: i32,
    min_screen_height: i32,
) -> Result<DisplayMode> {
    let modes = get_display_modes(video, min_screen_width, min_screen_height)?;

    for mode in &modes {
        if mode.0 == display_mode_name {
            return Ok(mode.1);
        }
    }

    get_default_display_mode(&modes, min_screen_width, min_screen_height)
}

fn get_display_modes(
    video: &VideoSubsystem,
    min_screen_width: i32,
    min_screen_height: i32,
) -> Result<Vec<(String, DisplayMode)>> {
    // Assume the first display is being used.
    // TODO: Is it always true?
    const DISPLAY_INDEX_IN_USE: i32 = 0;

    let mut modes = Vec::new();
    let num_display_modes = video.num_display_modes(DISPLAY_INDEX_IN_USE).sdl_error()?;
    for mode_index in 0..num_display_modes {
        let mode = video
            .display_mode(DISPLAY_INDEX_IN_USE, mode_index)
            .sdl_error()?;
        if mode.w < min_screen_width || mode.h < min_screen_height {
            continue;
        }
        let mode_descriptor = format!("{}x{}@{}Hz", mode.w, mode.h, mode.refresh_rate);
        modes.push((mode_descriptor, mode));
    }
    Ok(modes)
}

fn get_default_display_mode(
    modes: &[(String, DisplayMode)],
    min_screen_width: i32,
    min_screen_height: i32,
) -> Result<DisplayMode> {
    for mode in modes {
        if mode.1.w == min_screen_width && mode.1.h == min_screen_height {
            return Ok(mode.1);
        }
    }
    modes
        .iter()
        .next()
        .map(|m| m.1)
        .ok_or_else(|| format_err!("No display modes available"))
}
