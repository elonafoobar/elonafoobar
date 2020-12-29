use crate::error::SdlError;
use anyhow::{Context, Result};
use sdl2::pixels::Color;
use sdl2::surface::Surface;
use sdl2::ttf::{Font, FontStyle, Sdl2TtfContext as TtfContext};
use std::collections::hash_map::{Entry as HashMapEntry, HashMap};
use std::path::{Path, PathBuf};
use std::pin::Pin;
use std::rc::Rc;

#[derive(PartialEq, Eq, Hash)]
struct FontKey {
    path: PathBuf,
    point_size: u16,
    style: FontStyle,
}

// # Invariants for memory safety
//
// 1. `ttf` must live longer than `cache` and `current_font`.
// 2. All `Rc` instances in `cache` and `current_font` must be dropped before `ttf` is dropped.
// 3. All `Rc` instances must be shared only in `Self`.
// 4. `current_font` must be `None` or one of `cache`'s entries.
pub struct FontCache {
    current_font: Option<Rc<Font<'static, 'static>>>,
    cache: HashMap<FontKey, Rc<Font<'static, 'static>>>,
    ttf: Pin<Box<TtfContext>>,
    blended: bool,
}

impl FontCache {
    pub fn new() -> Result<FontCache> {
        let ttf = sdl2::ttf::init()?;

        Ok(FontCache {
            current_font: None,
            cache: HashMap::new(),
            ttf: Box::pin(ttf),
            blended: true,
        })
    }

    pub fn set_blended_rendering(&mut self, blended: bool) {
        self.blended = blended;
    }

    pub fn load_font(&mut self, path: &Path, point_size: u16, style: FontStyle) -> Result<()> {
        let key = FontKey {
            path: path.to_owned(),
            point_size,
            style,
        };
        self.current_font = Some(match self.cache.entry(key) {
            HashMapEntry::Occupied(entry) => {
                // Cache hit: just switch the current font to it.
                entry.get().clone()
            }
            HashMapEntry::Vacant(entry) => {
                let mut loaded_font = self.ttf.load_font(path, point_size).sdl_error()?;
                loaded_font.set_style(style);
                let loaded_font: Font<'static, 'static> =
                    unsafe { std::mem::transmute(loaded_font) };
                entry.insert(Rc::new(loaded_font)).clone()
            }
        });
        Ok(())
    }

    pub fn draw_text<'a>(&self, text: &str, color: Color) -> Result<Surface<'a>> {
        let font = self
            .current_font
            .as_ref()
            .context("Load a font before drawing text")?;
        Ok(if self.blended {
            font.render(text).blended(color)?
        } else {
            font.render(text).solid(color)?
        })
    }
}
