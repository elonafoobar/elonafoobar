use crate::cli::CliOptions;
use crate::profile::ProfileId;
use anyhow::Result;
use serde::Deserialize;
use std::io::ErrorKind as IoErrorKind;
use std::path::Path;
use std::str::FromStr;

#[derive(Debug, Default, Deserialize)]
pub struct PreinitGlobalConfig {
    pub default_profile: Option<String>,
}

impl PreinitGlobalConfig {
    pub fn from_file(path: &Path) -> Result<PreinitGlobalConfig> {
        match std::fs::read_to_string(path) {
            Ok(json5_source) => json5_source.parse().map_err(Into::into),
            Err(err) if err.kind() == IoErrorKind::NotFound => {
                // It is not error, returns default value.
                Ok(PreinitGlobalConfig::default())
            }
            Err(err) => Err(err.into()),
        }
    }
}

impl FromStr for PreinitGlobalConfig {
    type Err = json5::Error;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut cfg: Self = json5::from_str(s)?;

        // Convert an empty string to None.
        if cfg.default_profile.as_deref() == Some("") {
            cfg.default_profile = None;
        }
        Ok(cfg)
    }
}

#[derive(Debug, Default, Deserialize)]
pub struct PreinitLocalConfig {
    pub fullscreen: Option<String>,
    pub display_mode: Option<String>,
}

// `PreinitLocalConfig` is actually nested JSON5 value like this:
//
// {
//   core: {
//     screen: {
//       ...
//     }
//   }
// }
//
// To extract json["core"]["screen"], wrap `PreinitLocalConfig` with two types.
// TODO: does any good way exist?
#[derive(Default, Deserialize)]
struct WrappedPreinitLocalConfig {
    #[serde(default)]
    screen: PreinitLocalConfig,
}

#[derive(Deserialize)]
struct DoubleWrappedPreinitLocalConfig {
    #[serde(default)]
    core: WrappedPreinitLocalConfig,
}

impl PreinitLocalConfig {
    pub fn from_file(path: &Path) -> Result<PreinitLocalConfig> {
        match std::fs::read_to_string(path) {
            Ok(json5_source) => json5_source.parse().map_err(Into::into),
            Err(err) if err.kind() == IoErrorKind::NotFound => {
                // It is not error, returns default value.
                Ok(PreinitLocalConfig::default())
            }
            Err(err) => Err(err.into()),
        }
    }
}

impl std::str::FromStr for PreinitLocalConfig {
    type Err = json5::Error;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let double_wrapped: DoubleWrappedPreinitLocalConfig = json5::from_str(s)?;

        // Convert an empty string to None.
        let mut cfg = double_wrapped.core.screen;
        if cfg.fullscreen.as_deref() == Some("") {
            cfg.fullscreen = None;
        }
        if cfg.display_mode.as_deref() == Some("") {
            cfg.display_mode = None;
        }
        Ok(cfg)
    }
}

#[derive(Debug)]
pub struct Config {
    pub profile: ProfileId,
    pub headless: bool,
    pub fullscreen: Option<String>,
    pub display_mode: Option<String>,
    pub fps: f64,
}

impl Config {
    pub fn merge(
        cli_options: CliOptions,
        _global_cfg: PreinitGlobalConfig,
        local_cfg: PreinitLocalConfig,
        profile: ProfileId,
    ) -> Config {
        Config {
            profile,
            headless: cli_options.headless,
            fullscreen: local_cfg.fullscreen,
            display_mode: local_cfg.display_mode,
            fps: 60.0, /* TODO */
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    // Tests for PreinitGlobalConfig
    #[test]
    fn test_preinit_global_config_valid() {
        let parse = |s| PreinitGlobalConfig::from_str(s).unwrap();

        let cfg = parse(r#"{ default_profile: "foo" }"#);
        assert_eq!(cfg.default_profile.as_deref(), Some("foo"));

        let cfg = parse(r#"{ default_profile: "bar_baz" }"#);
        assert_eq!(cfg.default_profile.as_deref(), Some("bar_baz"));

        let cfg = parse(r#"{ default_profile: "profile", another_field: 123 }"#);
        assert_eq!(cfg.default_profile.as_deref(), Some("profile"));

        let cfg = parse(r#"{ default_profile: "!!!" }"#);
        assert_eq!(cfg.default_profile.as_deref(), Some("!!!"));
    }

    #[test]
    fn test_preinit_global_config_absent() {
        let parse = |s| PreinitGlobalConfig::from_str(s).unwrap();

        let cfg = parse(r#"{}"#);
        assert!(cfg.default_profile.is_none());

        let cfg = parse(r#"{ default_profile: null }"#);
        assert!(cfg.default_profile.is_none());

        let cfg = parse(r#"{ default_profile: "" }"#);
        assert!(cfg.default_profile.is_none());
    }

    #[test]
    fn test_preinit_global_config_invalid() {
        let parse = |s| PreinitGlobalConfig::from_str(s);

        assert!(parse(r#"&&&"#).is_err());
        assert!(parse(r#""#).is_err());
        assert!(parse(r#"{{]]"#).is_err());
        assert!(parse(r#"{ default_profile: 123 }"#).is_err());
    }

    // Tests for PreinitLocalConfig
    #[test]
    fn test_preinit_local_config_valid() {
        let parse = |s| PreinitLocalConfig::from_str(s).unwrap();

        let cfg = parse(r#"{ core: { screen: { fullscreen: "f", display_mode: "d" } } }"#);
        assert_eq!(cfg.fullscreen.as_deref(), Some("f"));
        assert_eq!(cfg.display_mode.as_deref(), Some("d"));
    }

    #[test]
    fn test_preinit_local_config_absent() {
        let parse = |s| PreinitLocalConfig::from_str(s).unwrap();

        let cfg = parse(r#"{}"#);
        assert!(cfg.fullscreen.is_none());
        assert!(cfg.display_mode.is_none());

        let cfg = parse(r#"{ core: {} }"#);
        assert!(cfg.fullscreen.is_none());
        assert!(cfg.display_mode.is_none());

        let cfg = parse(r#"{ core: { screen: {} } }"#);
        assert!(cfg.fullscreen.is_none());
        assert!(cfg.display_mode.is_none());

        let cfg = parse(r#"{ core: { screen: { fullscreen: null, display_mode: "" } } }"#);
        assert!(cfg.fullscreen.is_none());
        assert!(cfg.display_mode.is_none());

        let cfg = parse(r#"{ core: { screen: { fullscreen: "a", display_mode: "" } } }"#);
        assert_eq!(cfg.fullscreen.as_deref(), Some("a"));
        assert!(cfg.display_mode.is_none());

        let cfg = parse(r#"{ core: { screen: { fullscreen: null, display_mode: "a" } } }"#);
        assert!(cfg.fullscreen.is_none());
        assert_eq!(cfg.display_mode.as_deref(), Some("a"));

        let cfg = parse(r#"{ core: { screen: { display_mode: "a" } } }"#);
        assert!(cfg.fullscreen.is_none());
        assert_eq!(cfg.display_mode.as_deref(), Some("a"));
    }

    #[test]
    fn test_preinit_local_config_invalid() {
        let parse = |s| PreinitLocalConfig::from_str(s);

        assert!(parse(r#"&&&"#).is_err());
        assert!(parse(r#""#).is_err());
        assert!(parse(r#"{{]]"#).is_err());
        assert!(parse(r#"{ core: { screen: { fullscreen: 123 } } }"#).is_err());
        assert!(parse(r#"{ core: "foo" }"#).is_err());
        assert!(parse(r#"{ core: { screen: 42 } }"#).is_err());
    }
}
