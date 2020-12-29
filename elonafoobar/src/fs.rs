pub mod dirs;
pub mod files;

pub fn create_directories() -> std::io::Result<()> {
    for dir in &[dirs::tmp(), dirs::save()] {
        std::fs::create_dir_all(dir)?;
    }
    Ok(())
}
