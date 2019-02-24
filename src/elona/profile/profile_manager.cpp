#include "profile_manager.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"



namespace elona
{
namespace profile
{

void ProfileManager::init(const ProfileId& profile_id)
{
    ELONA_LOG("profile") << "Initialize with '" << profile_id << "'.";

    if (!exists(profile_id))
    {
        ELONA_LOG("profile") << "Not found '" << profile_id << "'.";
        create(profile_id);
    }

    load(profile_id);
}



void ProfileManager::load(const ProfileId& profile_id)
{
    ELONA_LOG("profile") << "Load '" << profile_id << "'.";
    // TODO
}



bool ProfileManager::is_valid_id(const ProfileId& profile_id)
{
    const std::regex pattern{u8"[0-9A-Za-z_]+"};
    return std::regex_match(profile_id, pattern);
}



bool ProfileManager::is_reserved_id(const ProfileId& profile_id)
{
    return profile_id == default_profile_id ||
        profile_id == default_base_profile_id;
}



bool ProfileManager::exists(const ProfileId& profile_id)
{
    const auto dir = get_dir_for(profile_id);
    return fs::exists(dir) && fs::is_directory(dir);
}



fs::path ProfileManager::get_dir_for(const ProfileId& profile_id)
{
    assert(is_valid_id(profile_id));
    return filesystem::dir::profiles() / filepathutil::u8path(profile_id);
}



ProfileManager& ProfileManager::instance()
{
    static ProfileManager the_instance;
    return the_instance;
}



void ProfileManager::create(
    const ProfileName& new_profile_name,
    const ProfileId& new_profile_id,
    const ProfileId& base_profile_id)
{
    ELONA_LOG("profile") << "Create '" << new_profile_name << "' ("
                         << new_profile_id << ") from '" << base_profile_id
                         << "'.";

    const auto from = get_dir_for(base_profile_id);
    const auto to = get_dir_for(new_profile_id);
    // filesystem::copy_recursively(from, to);
}



void ProfileManager::create(
    const ProfileId& new_profile_id,
    const ProfileId& base_profile_id)
{
    create(new_profile_id, new_profile_id, base_profile_id);
}



void ProfileManager::delete_(const ProfileId& profile_id)
{
    (void)profile_id;
    // TODO
}

} // namespace profile
} // namespace elona
