use anyhow::Result;
use elonafoobar::{fs, run, version::VARIANT_LONG_STRING};
use elonafoobar_log::{info, Level};

fn main() -> Result<()> {
    let log_filter = std::env::var("ELONAFOOBAR_LOG")
        .ok()
        .and_then(|level| match level.as_str() {
            "ERROR" | "error" => Some(Level::Error),
            "WARN" | "warn" => Some(Level::Warn),
            "INFO" | "info" => Some(Level::Info),
            "DEBUG" | "debug" => Some(Level::Debug),
            "TRACE" | "trace" => Some(Level::Trace),
            _ => None,
        })
        .unwrap_or(Level::Info);

    std::fs::create_dir_all(fs::dirs::log())?;
    elonafoobar_log::init(fs::dirs::log(), log_filter)?;
    info!("{}", VARIANT_LONG_STRING);

    let result = run::run();
    elonafoobar_log::flush();
    result
}
