#pragma once

#include "filesystem.hpp"



namespace elona
{

void save_fs_clear();
bool save_fs_exists(const fs::path& filename);
void save_fs_add(const fs::path& filename);
void save_fs_remove(const fs::path& filename);
void save_fs_save(const fs::path& save_dir);

} // namespace elona
