#include "save_fs.hpp"

#include <iostream>
#include <unordered_map>

#include "log.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

enum class FileStatus
{
    unknown,
    copied,
    added,
    removed,
};



std::unordered_map<fs::path, FileStatus> files;



bool try_copy(const fs::path& filename)
{
    if (fs::exists(filesystem::dirs::save(playerid) / filename))
    {
        fs::copy_file(
            filesystem::dirs::save(playerid) / filename,
            filesystem::dirs::tmp() / filename,
            fs::copy_option::overwrite_if_exists);
        ELONA_LOG("save") << "Copy " << filename.to_u8string();
        return true;
    }
    else
    {
        return false;
    }
}

} // namespace



void save_fs_clear()
{
    files.clear();
}



bool save_fs_exists(const fs::path& filename)
{
    switch (files[filename])
    {
    case FileStatus::unknown: {
        const auto exists = try_copy(filename);
        if (exists)
        {
            files[filename] = FileStatus::copied;
        }
        return exists;
    }
    case FileStatus::copied: return true;
    case FileStatus::added: return true;
    case FileStatus::removed: return false;
    default: assert(0); return false;
    }
}



void save_fs_add(const fs::path& filename)
{
    files[filename] = FileStatus::added;
    ELONA_LOG("save") << "Add " << filename.to_u8string();
}



void save_fs_remove(const fs::path& filename)
{
    files[filename] = FileStatus::removed;
    ELONA_LOG("save") << "Remove " << filename.to_u8string();
}



void save_fs_save(const fs::path& save_dir)
{
    for (const auto& [filename, status] : files)
    {
        switch (status)
        {
        case FileStatus::added:
            fs::copy_file(
                filesystem::dirs::tmp() / filename,
                save_dir / filename,
                fs::copy_option::overwrite_if_exists);
            break;
        case FileStatus::removed: fs::remove_all(save_dir / filename); break;
        default: break;
        }
    }
}

} // namespace elona
