use anyhow::Result;
use elonafoobar::{fs, run, version::latest_version};
use elonafoobar_log::{info, Level};

fn main() -> Result<()> {
    let log_filter = std::env::var("ELONAFOOBAR_LOG")
        .ok()
        .and_then(|level| match level.as_str() {
            "ERROR" => Some(Level::Error),
            "WARN" => Some(Level::Warn),
            "INFO" => Some(Level::Info),
            "DEBUG" => Some(Level::Debug),
            "TRACE" => Some(Level::Trace),
            _ => None,
        })
        .unwrap_or(Level::Info);

    std::fs::create_dir_all(fs::dirs::log())?;
    elonafoobar_log::init(fs::dirs::log(), log_filter)?;
    info!("{}", latest_version().long_string());

    let result = run::run();
    elonafoobar_log::flush();
    result
}
