use crate::cli::CliOptions;
use crate::config::{Config, PreinitGlobalConfig, PreinitLocalConfig};
use crate::engine::Engine;
use crate::fs::{self, files};
use crate::profile;
use anyhow::Result;
use elonafoobar_log::info;

pub fn init(cli_options: CliOptions) -> Result<Engine> {
    let global_cfg = PreinitGlobalConfig::from_file(&files::global_config())?;
    let resolved_profile = profile::resolve_from_config(
        cli_options
            .profile
            .as_deref()
            .or_else(|| global_cfg.default_profile.as_deref()),
    )?;
    info!("Set profile: '{}'", &resolved_profile);
    let local_cfg = PreinitLocalConfig::from_file(&files::local_config(&resolved_profile))?;

    let cfg = Config::merge(cli_options, global_cfg, local_cfg, resolved_profile.clone());

    let mut engine = Engine::new(cfg)?;

    fs::create_directories(&resolved_profile)?;

    engine.open_builtin_libraries()?;
    engine.bind_native_libraries()?;

    Ok(engine)
}
