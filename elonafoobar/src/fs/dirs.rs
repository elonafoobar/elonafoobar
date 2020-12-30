use crate::mods::{ModId, Version};
use crate::profile::ProfileId;
use lazy_static::lazy_static;
use std::path::PathBuf;

lazy_static! {
    static ref ROOT_CACHE: PathBuf = get_exe_path();
}

fn get_exe_path() -> PathBuf {
    std::env::current_exe()
        .ok()
        .and_then(|path| path.parent().map(|p| p.to_owned()))
        .expect("failed to get executable path")
}

/// "/"
pub fn root() -> PathBuf {
    ROOT_CACHE.clone()
}

/// "/data"
pub fn data() -> PathBuf {
    root().join("data")
}

/// "/data/script"
pub fn script() -> PathBuf {
    data().join("script")
}

/// "/data/font"
pub fn font() -> PathBuf {
    data().join("font")
}

/// "/log"
pub fn log() -> PathBuf {
    root().join("log")
}

/// "/mod"
pub fn mod_() -> PathBuf {
    root().join("mod")
}

/// "/mod/<mod>"
pub fn mod_of(mod_id: &ModId, version: &Version) -> PathBuf {
    mod_().join(format!("{}@{}", mod_id, version))
}

/// "/profile"
pub fn profile() -> PathBuf {
    root().join("profile")
}

/// "/profile/<profile>"
pub fn profile_of(profile_id: &ProfileId) -> PathBuf {
    profile().join(profile_id.to_path())
}

/// "/tmp"
pub fn tmp() -> PathBuf {
    root().join("tmp")
}

/// "/profile/<profile>/save"
pub fn save(profile_id: &ProfileId) -> PathBuf {
    profile_of(profile_id).join("save")
}
