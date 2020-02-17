#pragma once

#include <unordered_map>

#include "../util/noncopyable.hpp"
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



class Save : public lib::noncopyable
{
public:
    static Save& instance();


    void clear();
    void add(const fs::path& filename);
    void remove(const fs::path& filename);

    void save(const fs::path& save_dir);


private:
    Save() = default;

    std::unordered_map<fs::path, bool> saved_files;
};



void ctrl_file(FileOperation file_operation);
void ctrl_file(FileOperation2 file_operation, const fs::path& filepath);
void tmpload(const fs::path& filename);
bool writeloadedbuff(const fs::path& filename);
void writeloadedbuff_clear();


} // namespace elona
