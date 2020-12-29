/*
 * Elona foobar's log library
 *
 * Log format: elapsedtime LEVEL [mod] Message
 * - The elapsed time is recorded in second.
 * - There are 5 severity level: trace, debug, info, warn and error.
 * - "mod" shows the mod which outputs the log line. E.g., "core".
 *
 * Example: 1.234 ERROR [core] Failed to load mod "api_nuts".
 *
 * Log files are saved in "/path/to/elonafoobar/log". These files are rotated
 * (https://en.wikipedia.org/wiki/Log_rotation) on every launching, and
 * "log/0.log" is the latest. The larger the digit is, the older the log file
 * is. Currently, Elona foobar stores up to 10 logs, including the latest.
 */

use ansi_term::Color as AnsiColor;
use log::{Metadata, Record};
use std::fs::File;
use std::io::BufWriter;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::sync::Arc;
use std::sync::Mutex;
use std::time::Instant;
use thiserror::Error;

// Re-exports
pub use log::Level;

pub mod macros;
pub use macros::*;

const MAX_LOG_FILES: u8 = 10;
const LOG_FILE_EXTENSION: &str = "log";

#[derive(Error, Debug)]
pub enum InitLoggerError {
    #[error("failed to rotate log files")]
    Rotate(#[from] std::io::Error),
    #[error("failed to create log file")]
    CreateNew(#[source] std::io::Error),
    #[error("failed to set logger")]
    SetLogger(#[from] log::SetLoggerError),
}

pub type InitLoggerResult = Result<(), InitLoggerError>;

pub fn init(log_root_dir: impl AsRef<Path>, filter: Level) -> InitLoggerResult {
    rotate_log_files(log_root_dir.as_ref())?;
    let file = File::create(log_file_path(log_root_dir.as_ref(), 0))
        .map_err(InitLoggerError::CreateNew)?;
    log::set_boxed_logger(Box::new(Logger::with_file(file)))?;
    log::set_max_level(filter.to_level_filter());
    Ok(())
}

pub fn flush() {
    log::logger().flush();
}

pub fn log(target: &str, level: Level, message: impl std::fmt::Display) {
    ::log::log!(target: target, level, "{}", message);
}

pub fn level() -> Level {
    log::max_level().to_level().unwrap_or(Level::Error)
}

pub fn set_level(level: Level) {
    log::set_max_level(level.to_level_filter());
}

struct Logger {
    start_time: Instant,
    writer: Arc<Mutex<BufWriter<File>>>,
}

impl Logger {
    fn with_file(file: File) -> Self {
        let writer = Arc::new(Mutex::new(BufWriter::new(file)));
        Self {
            start_time: Instant::now(),
            writer,
        }
    }
}

impl log::Log for Logger {
    fn enabled(&self, _metadata: &Metadata) -> bool {
        true
    }

    fn log(&self, record: &Record) {
        if !self.enabled(record.metadata()) {
            return;
        }

        let mut w = self
            .writer
            .lock()
            .expect("Logger: failed to get shared file writer");
        let elapsed_time = Instant::now() - self.start_time;
        writeln!(
            w,
            "{:.3} {} [{}] {}",
            elapsed_time.as_secs_f64(),
            level_to_string(record.level()),
            record.target(),
            record.args()
        )
        .expect("Logger: failed to write");

        if atty::is(atty::Stream::Stderr) {
            eprintln!(
                "{:.3} {} [{}] {}",
                elapsed_time.as_secs_f64(),
                level_to_string_with_color(record.level()),
                record.target(),
                record.args()
            );
        }
    }

    fn flush(&self) {
        let mut w = self
            .writer
            .lock()
            .expect("Logger: failed to get shared file writer");
        w.flush().expect("Logger: failed to flush");
    }
}

fn rotate_log_files(root_dir: &Path) -> std::io::Result<()> {
    let oldest = MAX_LOG_FILES - 1;
    remove_file(&log_file_path(root_dir, oldest))?;

    for nth in (0..oldest).rev() {
        let src = log_file_path(root_dir, nth);
        let dst = log_file_path(root_dir, nth + 1);
        rename(&src, &dst)?;
    }
    Ok(())
}

fn remove_file(path: &Path) -> std::io::Result<()> {
    if path.exists() {
        std::fs::remove_file(path)
    } else {
        Ok(())
    }
}

fn rename(from: &Path, to: &Path) -> std::io::Result<()> {
    if from.exists() {
        std::fs::rename(from, to)
    } else {
        Ok(())
    }
}

// {root_dir}/{nth}.log.
fn log_file_path(root_dir: &Path, nth: u8) -> PathBuf {
    let file_name = format!("{}.{}", nth, LOG_FILE_EXTENSION);
    root_dir.join(file_name)
}

fn level_to_string(level: Level) -> &'static str {
    match level {
        Level::Error => "ERROR",
        Level::Warn => "WARN ",
        Level::Info => "INFO ",
        Level::Debug => "DEBUG",
        Level::Trace => "TRACE",
    }
}

// for stderr
fn level_to_string_with_color(level: Level) -> String {
    match level {
        Level::Error => AnsiColor::Red.paint("ERROR").to_string(),
        Level::Warn => AnsiColor::Yellow.paint("WARN ").to_string(),
        Level::Info => "INFO ".to_string(),
        Level::Debug => "DEBUG".to_string(),
        Level::Trace => "TRACE".to_string(),
    }
}
