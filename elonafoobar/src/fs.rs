use crate::profile::ProfileId;

pub mod dirs;
pub mod files;

pub fn create_directories(profile_id: &ProfileId) -> std::io::Result<()> {
    for dir in &[dirs::tmp(), dirs::save(profile_id)] {
        std::fs::create_dir_all(dir)?;
    }
    Ok(())
}
