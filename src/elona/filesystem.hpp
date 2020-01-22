#pragma once

#include <functional>
#include <regex>
#include "../util/filepathutil.hpp"



namespace fs = boost::filesystem;



namespace std
{

template <>
struct hash<fs::path>
{
    size_t operator()(const fs::path& key) const
    {
        return hash<fs::path::string_type>()(key.native());
    }
};

} // namespace std



namespace elona
{
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
fs::path for_mod(const std::string& mod_id);
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

} // namespace files



fs::path path(const std::string&);
fs::path resolve_path_for_mod(const std::string& mod_local_path);



namespace detail
{

template <typename F>
std::vector<fs::path> glob_entries_internal(
    const fs::path& base_dir,
    const std::regex& pattern,
    F predicate)
{
    std::vector<fs::path> ret;
    for (auto itr = fs::directory_iterator{base_dir},
              end = fs::directory_iterator{};
         itr != end;
         ++itr)
    {
        if (fs::exists(itr->path()) && predicate(itr->path()) &&
            std::regex_match(
                filepathutil::to_utf8_path(itr->path().filename()), pattern))
        {
            ret.push_back(itr->path());
        }
    }
    return ret;
}

} // namespace detail



inline std::vector<fs::path> glob_entries(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const auto&) { return true; });
}



inline std::vector<fs::path> glob_files(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const auto& path) {
            return fs::is_regular_file(path);
        });
}



inline std::vector<fs::path> glob_dirs(
    const fs::path& base_dir,
    const std::regex& pattern = std::regex{u8".*"})
{
    return detail::glob_entries_internal(
        base_dir, pattern, [](const auto& path) {
            return fs::is_directory(path);
        });
}



// Emulates std::filesystem::copy_options::recursive in C++17.
void copy_recursively(const fs::path& source, const fs::path& destination);

} // namespace filesystem
} // namespace elona
