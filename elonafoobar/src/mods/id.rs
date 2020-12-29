use anyhow::format_err;
use elonafoobar_lua::{self as lua, utils::IdentifierCheck};
use elonafoobar_utils as utils;
use serde::Deserialize;
use std::convert::{TryFrom, TryInto};
use std::path::Path;

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord, Deserialize, Hash)]
#[serde(transparent)]
pub struct Id(String);

impl Id {
    pub fn is_valid_id(s: &str) -> bool {
        lua::utils::is_valid_identifier(
            s,
            IdentifierCheck::ALLOW_KEYWORD | IdentifierCheck::ALLOW_RESERVED,
        ) && utils::path::is_portable_name(Path::new(s))
    }

    pub fn to_path(&self) -> &Path {
        Path::new(&self.0)
    }

    pub fn core() -> Id {
        "core".to_owned().try_into().unwrap()
    }
}

impl std::fmt::Display for Id {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl TryFrom<String> for Id {
    type Error = anyhow::Error;

    fn try_from(s: String) -> Result<Id, anyhow::Error> {
        if Id::is_valid_id(&s) {
            Ok(Id(s))
        } else {
            Err(format_err!("Mod ID '{}' is invalid", s))
        }
    }
}
