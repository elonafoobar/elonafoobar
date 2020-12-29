use crate::cli::{self, ParseResult};
use crate::init;
use anyhow::Result;

pub fn run() -> Result<()> {
    cli::print_args();
    let options = match cli::parse_args() {
        ParseResult::Ok(options) => options,
        ParseResult::Err(err) => return Err(err.into()),
        ParseResult::Help | ParseResult::Version => return Ok(()),
    };

    let engine = init::init(options)?;
    engine.run()?;
    Ok(())
}
