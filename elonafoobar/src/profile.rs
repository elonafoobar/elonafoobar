use anyhow::{bail, Result};
use elonafoobar_log::info;
use elonafoobar_lua::{self as lua, utils::IdentifierCheck};
use elonafoobar_utils as utils;
use std::convert::{TryFrom, TryInto};
use std::path::Path;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ProfileId(String);

impl ProfileId {
    pub fn is_valid_id(s: &str) -> bool {
        lua::utils::is_valid_identifier(
            s,
            IdentifierCheck::ALLOW_KEYWORD | IdentifierCheck::ALLOW_RESERVED,
        ) && utils::path::is_portable_name(Path::new(s))
    }

    pub fn default_id() -> ProfileId {
        ProfileId("default".to_owned())
    }

    pub fn to_path(&self) -> &Path {
        Path::new(&self.0)
    }
}

impl std::fmt::Display for ProfileId {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.0)
    }
}

impl TryFrom<String> for ProfileId {
    type Error = anyhow::Error;

    fn try_from(s: String) -> Result<ProfileId> {
        if ProfileId::is_valid_id(&s) {
            Ok(ProfileId(s))
        } else {
            bail!("Profile '{}' is invalid", s)
        }
    }
}

pub fn resolve_from_config(profile: Option<&str>) -> Result<ProfileId> {
    match profile.map(ToOwned::to_owned).map(TryInto::try_into) {
        Some(Ok(profile)) => Ok(profile),
        Some(Err(err)) => {
            bail!(err)
        }
        None => {
            info!(
                "Profile is not given, fallbacking to '{}'",
                ProfileId::default_id()
            );
            Ok(ProfileId::default_id())
        }
    }
}
