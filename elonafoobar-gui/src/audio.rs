use crate::error::SdlError;
use anyhow::{bail, Result};
use sdl2::mixer::{InitFlag, Music, Sdl2MixerContext as MixerContext};
use std::path::Path;

pub struct Audio {
    // `playing_music` must die before `mixer` dies. It is guaranteed by Rust's Drop order.
    playing_music: Option<Music<'static>>,
    #[allow(dead_code)]
    mixer: MixerContext,
}

impl Audio {
    pub fn new() -> Result<Audio> {
        let mixer = sdl2::mixer::init(InitFlag::MID /*TODO support more*/).sdl_error()?;

        sdl2::mixer::open_audio(
            44100,
            sdl2::mixer::DEFAULT_FORMAT,
            sdl2::mixer::DEFAULT_CHANNELS,
            256,
        )
        .sdl_error()?;

        Ok(Audio {
            playing_music: None,
            mixer,
        })
    }

    pub fn get_music_decoders(&self) -> Vec<String> {
        use sdl2::mixer::{get_music_decoder, get_music_decoders_number};

        let mut decoders = Vec::new();
        for decoder_index in 0..get_music_decoders_number() {
            decoders.push(get_music_decoder(decoder_index));
        }
        decoders
    }

    pub fn load_music(&mut self, path: &Path) -> Result<()> {
        self.stop_music();
        self.playing_music = Some(Music::from_file(path).sdl_error()?);
        Ok(())
    }

    pub fn play_music(&mut self, loops: i32) -> Result<()> {
        if let Some(ref music) = self.playing_music {
            music.play(loops).sdl_error()
        } else {
            bail!("Audio::play_music(): load music file by Audio::load_music().")
        }
    }

    pub fn stop_music(&self) {
        Music::halt();
    }

    pub fn get_music_volume(&self) -> u8 {
        // `Mix_VolumeMusic()` returns 0-128.
        Music::get_volume() as u8
    }

    pub fn set_music_volume(&self, volume: u8) {
        Music::set_volume(volume.into());
    }
}
