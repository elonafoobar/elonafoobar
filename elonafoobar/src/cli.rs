use crate::version::latest_version;
use clap::{App, Arg};
use elonafoobar_log::info;

#[derive(Debug)]
pub struct CliOptions {
    pub profile: Option<String>,
}

#[derive(Debug)]
pub enum ParseResult {
    Ok(CliOptions),
    Err(clap::Error),
    Help,    // -h or --help
    Version, // -v or --version
}

// Log given command line arguments.
pub fn print_args() {
    for (i, arg) in std::env::args_os().enumerate() {
        info!("argv[{}] = {}", i, arg.to_string_lossy());
    }
}

// Parse command line arguments.
pub fn parse_args() -> ParseResult {
    let version = latest_version().short_string();
    let long_version = latest_version().long_string();

    let matches = make_arg_parser(&version, &long_version).get_matches_safe();
    match matches {
        Ok(matches) => ParseResult::Ok(CliOptions {
            profile: matches.value_of("profile").map(|s| s.to_owned()),
        }),
        Err(err) if err.kind == clap::ErrorKind::HelpDisplayed => {
            println!("{}", err.message); // Output help message, which is not output by clap.
            ParseResult::Help
        }
        Err(err) if err.kind == clap::ErrorKind::VersionDisplayed => {
            println!(); // Append a new line at the end, which is not output by clap.
            ParseResult::Version
        }
        Err(err) => ParseResult::Err(err),
    }
}

fn make_arg_parser<'a, 'b>(version: &'b str, long_version: &'b str) -> App<'a, 'b> {
    App::new("Elona foobar")
        .version(version)
        .long_version(long_version)
        .version_short("v")
        .about("Yet another Elona variant to build your own Elona")
        .arg(
            Arg::with_name("profile")
                .short("p")
                .long("profile")
                .value_name("PROFILE")
                .help("Sets a profile"),
        )
}
