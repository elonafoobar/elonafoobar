#include "profile_manager.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"


namespace
{

void write_default_config(const fs::path& location)
{
    std::ofstream out{location.native(), std::ios::binary};
    out << "config {\n}" << std::endl;
}

} // namespace


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

    filesystem::dir::set_profile_directory(get_dir_for(profile_id));
}



ProfileManager& ProfileManager::instance()
{
    static ProfileManager the_instance;
    return the_instance;
}



void ProfileManager::create(const ProfileId& new_profile_id)
{
    ELONA_LOG("profile") << "Create '" << new_profile_id << "'.";

    const auto to = get_dir_for(new_profile_id);
    fs::create_directory(to);

    auto script_dir = to / "script";
    fs::create_directory(script_dir.native());

    auto console_script = script_dir / "console.lua";
    std::ofstream out(console_script.native());
    out << "-- Code here will be executed in the console on startup.\n";
    out.close();
}



ProfileId ProfileManager::generate_new_id()
{
    for (int i = 1;; ++i)
    {
        const auto id = "profile_" + std::to_string(i);
        const auto dir = get_dir_for(id);
        if (!fs::exists(dir))
        {
            return id;
        }
    }
}



void ProfileManager::delete_(const ProfileId& profile_id)
{
    const auto dir = get_dir_for(profile_id);
    fs::remove_all(dir);
}

} // namespace profile
} // namespace elona
