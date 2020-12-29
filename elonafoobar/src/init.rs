use crate::cli::CliOptions;
use crate::config::{PreinitGlobalConfig, PreinitLocalConfig};
use crate::engine::Engine;
use crate::fs::{self, files};
use crate::profile;
use anyhow::Result;

pub fn init(cli_options: CliOptions) -> Result<Engine> {
    let global_cfg = PreinitGlobalConfig::from_file(&files::global_config())?;
    profile::try_set_profile(cli_options.profile.or(global_cfg.default_profile))?;

    let local_cfg = PreinitLocalConfig::from_file(&files::local_config())?;

    let mut engine = Engine::new(local_cfg)?;

    fs::create_directories()?;

    engine.open_builtin_libraries()?;
    engine.bind_native_libraries()?;

    Ok(engine)
}
