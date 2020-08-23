#pragma once

#include <unordered_map>

#include "filesystem.hpp"



namespace elona
{


enum class FileOperation
{
    map_read,
    map_write,
    custom_map_read,
    custom_map_write,
    save_game_delete,
    temp_dir_delete,
    map_delete,
    map_delete_preserve_items,
    temp_dir_delete_area,
    gene_write,
    gene_read,
    map_load_map_obj_files,
    map_home_upgrade,
};



enum class FileOperation2
{
    map_items_read,
    map_items_write,
    global_read,
    global_write,
    deck_write,
    deck_read,
};



void ctrl_file(FileOperation file_operation);
void ctrl_file(FileOperation2 file_operation, const fs::path& filepath);

void ctrl_file_tmp_inv_read(const fs::path& file_name);
void ctrl_file_tmp_inv_write(const fs::path& file_name);

} // namespace elona
