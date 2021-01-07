use crate::error::SdlError;
use anyhow::Result;
use sdl2::image::{self, InitFlag, LoadSurface, Sdl2ImageContext};
use sdl2::pixels::Color;
use sdl2::render::{Texture, TextureCreator};
use sdl2::surface::Surface;
use std::path::Path;
use std::rc::Rc;

pub struct ImageContext(Sdl2ImageContext);

impl ImageContext {
    pub fn new() -> Result<ImageContext> {
        let ctx = image::init(InitFlag::JPG | InitFlag::PNG).sdl_error()?;
        Ok(ImageContext(ctx))
    }
}

pub struct Image {
    texture: Rc<Texture<'static>>,
}

impl Image {
    pub fn load_file<Ctx>(
        texture_creator: &TextureCreator<Ctx>,
        path: &Path,
        color: Option<Color>,
    ) -> Result<Image> {
        let mut surface = Surface::from_file(path).sdl_error()?;
        if let Some(color) = color {
            surface.set_color_key(true, color).sdl_error()?;
        }
        let texture = texture_creator.create_texture_from_surface(surface)?;
        let texture = unsafe { std::mem::transmute(texture) };
        Ok(Image {
            texture: Rc::new(texture),
        })
    }

    pub fn set_alpha_mod(&mut self, alpha: u8) {
        self.as_texture_mut().set_alpha_mod(alpha);
    }

    pub fn set_color_mod(&mut self, color: Color) {
        let (r, g, b) = color.rgb();
        self.as_texture_mut().set_color_mod(r, g, b);
    }

    pub(crate) fn as_texture(&self) -> &Texture {
        self.texture.as_ref()
    }

    fn as_texture_mut(&mut self) -> &mut Texture<'static> {
        Rc::get_mut(&mut self.texture).unwrap()
    }
}
