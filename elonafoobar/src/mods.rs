use crate::fs::{dirs, files};
use crate::profile::ProfileId;
use crate::version::{MOD_CORE_MAJOR, MOD_CORE_MINOR, MOD_CORE_PATCH};
use anyhow::Result;
use elonafoobar_log::debug;
pub use semver::{Version, VersionReq};
use std::path::{Path, PathBuf};

pub mod id;
pub mod manifest;
pub mod resolve;

pub use id::Id as ModId;
pub use manifest::Manifest as ModManifest;
pub use resolve::{ModIndex, ModList, ModLock, ResolvedModList};

pub fn resolve(profile_id: &ProfileId) -> Result<ResolvedModList> {
    let list = {
        let mut list = ModList::from_file(&files::mod_list(profile_id))?;
        list.add(
            ModId::core(),
            VersionReq::exact(&Version::new(
                MOD_CORE_MAJOR.into(),
                MOD_CORE_MINOR.into(),
                MOD_CORE_PATCH.into(),
            )),
        );
        list
    };
    let lock = ModLock {};
    let index = ModIndex::traverse(&dirs::mod_())?;

    let resolved_mod_list = resolve::resolve(&list, &lock, &index)?;
    debug!("{:?}", list);
    debug!("{:?}", lock);
    debug!("{:?}", index);
    debug!("{:?}", resolved_mod_list);

    Ok(resolved_mod_list)
}

pub fn iter_mod_dirs(mod_root_dir: &Path) -> impl Iterator<Item = PathBuf> {
    std::fs::read_dir(mod_root_dir)
        .into_iter()
        .flatten()
        .flat_map(|entry| entry.map(|e| e.path()))
        .filter(|path| is_mod_dir(&path))
}

fn is_mod_dir(path: &Path) -> bool {
    has_manifest_file(path) && is_valid_dir_name(path)
}

fn has_manifest_file(path: &Path) -> bool {
    path.join("mod.json").exists()
}

fn is_valid_dir_name(path: &Path) -> bool {
    fn check(path: &Path) -> Option<bool> {
        // Does it has file name part?
        let dir_name = path.file_name()?;
        // Is it valid UTF-8?
        let dir_name = dir_name.to_str()?;
        // Can it be split into two parts by '@' sign?
        let (mod_id, version_id) = dir_name.split_once('@')?;
        // Are the two valid as mod ID and semver?
        Some(ModId::is_valid_id(mod_id) && Version::parse(version_id).is_ok())
    }

    check(path) == Some(true)
}
