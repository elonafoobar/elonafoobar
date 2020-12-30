use crate::fs::{dirs, files};
use crate::profile::ProfileId;
use anyhow::Result;
use elonafoobar_log::debug;
pub use semver::{Version, VersionReq};

pub mod id;
pub mod manifest;
pub mod resolve;

pub use id::Id as ModId;
pub use manifest::Manifest as ModManifest;
pub use resolve::{ModIndex, ModList, ModLock, ResolvedModList};

pub fn resolve(profile_id: &ProfileId) -> Result<ResolvedModList> {
    let list = {
        let mut list = ModList::from_file(&files::mod_list(profile_id))?;
        // TODO
        list.add(ModId::core(), VersionReq::any());
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
