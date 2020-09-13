#pragma once

#include "filesystem.hpp"



namespace elona
{

void ctrl_file_global_read(const fs::path& save_dir);
void ctrl_file_global_write(const fs::path& save_dir);

void ctrl_file_map_read();
void ctrl_file_map_write();

void ctrl_file_map_items_read(const fs::path& filename);
void ctrl_file_map_items_write(const fs::path& filename);

void ctrl_file_custom_map_read(const fs::path& filename_base);
void ctrl_file_map_load_map_obj_files(const fs::path& filename_base);

void ctrl_file_save_game_delete();
void ctrl_file_temp_dir_delete();

void ctrl_file_map_delete();
void ctrl_file_map_delete_preserve_items();

void ctrl_file_temp_dir_delete_area();

void ctrl_file_map_home_upgrade();

void ctrl_file_deck_read(const fs::path& filename);
void ctrl_file_deck_write(const fs::path& filename);

void ctrl_file_tmp_inv_read(const fs::path& filename);
void ctrl_file_tmp_inv_write(const fs::path& filename);

} // namespace elona
