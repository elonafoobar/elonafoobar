use crate::fs;
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
    type Error = String;

    fn try_from(s: String) -> Result<ProfileId, String> {
        if ProfileId::is_valid_id(&s) {
            Ok(ProfileId(s))
        } else {
            Err(format!("Profile '{}' is invalid", s))
        }
    }
}

pub fn try_set_profile(profile: Option<String>) -> Result<()> {
    match profile.map(TryInto::try_into) {
        Some(Ok(profile)) => {
            set_profile_internal(profile);
            Ok(())
        }
        Some(Err(err)) => {
            bail!(err);
        }
        None => {
            info!(
                "Profile is not given, fallbacking to '{}'",
                ProfileId::default_id()
            );
            set_profile_internal(ProfileId::default_id());
            Ok(())
        }
    }
}

fn set_profile_internal(profile: ProfileId) {
    info!("Set profile: '{}'", profile);
    fs::dirs::set_current_profile(profile);
}
