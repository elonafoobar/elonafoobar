#pragma once

#include <functional>
#include <regex>

#include "../util/filesystem.hpp"



namespace fs = lib::filesystem;



namespace elona
{

namespace semver
{
struct Version;
}


namespace filesystem
{

// Pre-defined directories.
namespace dirs
{

fs::path exe();
fs::path data();
fs::path graphic();
fs::path locale();
fs::path log();
fs::path map();
fs::path mod();
fs::path for_mod(const std::string& id, const semver::Version& version);
fs::path profile_root();
fs::path current_profile();
fs::path save();
fs::path save(const std::string& player_id);
fs::path screenshot();
fs::path sound();
fs::path tmp();
fs::path user();
fs::path user_script();

void set_current_profile_directory(const fs::path& current_profile_dir);
void set_base_save_directory(const fs::path& base_save_dir);
void set_base_user_directory(const fs::path& base_user_dir);
void set_profile_directory(const fs::path& profile_dir);

} // namespace dirs



// Pre-defined files.
namespace files
{

fs::path profile_local_config();
fs::path keybinding_config();
fs::path mod_list();

} // namespace files



fs::path path(const std::string&);



inline auto glob_entries(const fs::path& base_dir, const std::regex& pattern)
{
    return fs::iter_dir(base_dir, [&](const auto& p) {
        return std::regex_match(p.filename().to_u8string(), pattern);
    });
}



inline auto glob_entries(const fs::path& base_dir)
{
    return fs::iter_dir(base_dir);
}



inline auto glob_files(const fs::path& base_dir, const std::regex& pattern)
{
    return fs::iter_dir(base_dir, [&](const auto& p) {
        return fs::is_regular_file(p) &&
            std::regex_match(p.filename().to_u8string(), pattern);
    });
}



inline auto glob_files(const fs::path& base_dir)
{
    return fs::iter_dir(
        base_dir, [](const auto& p) { return fs::is_regular_file(p); });
}



inline auto glob_dirs(const fs::path& base_dir, const std::regex& pattern)
{
    return fs::iter_dir(base_dir, [&](const auto& p) {
        return fs::is_directory(p) &&
            std::regex_match(p.filename().to_u8string(), pattern);
    });
}



inline auto glob_dirs(const fs::path& base_dir)
{
    return fs::iter_dir(
        base_dir, [](const auto& p) { return fs::is_directory(p); });
}

} // namespace filesystem
} // namespace elona
