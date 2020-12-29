use anyhow::{format_err, Result};

pub trait SdlError<T> {
    fn sdl_error(self) -> Result<T>;
}

impl<T> SdlError<T> for Result<T, String> {
    fn sdl_error(self) -> Result<T> {
        self.map_err(|msg| format_err!(msg))
    }
}
