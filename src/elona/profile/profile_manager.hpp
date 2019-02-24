#pragma once

#include <string>
#include "../../util/noncopyable.hpp"
#include "../filesystem.hpp"



namespace elona
{
namespace profile
{

using ProfileName = std::string;

using ProfileId = std::string;
constexpr const char* default_base_profile_id = u8"_";
constexpr const char* default_profile_id = u8"default";



class ProfileManager : lib::noncopyable
{
public:
    static ProfileManager& instance();

    void init(const ProfileId& profile_id);
    void load(const ProfileId& profile_id);

    bool is_valid_id(const ProfileId& profile_id);
    bool is_reserved_id(const ProfileId& profile_id);
    bool exists(const ProfileId& profile_id);
    fs::path get_dir_for(const ProfileId& profile_id);

    void create(
        const ProfileName& new_profile_name,
        const ProfileId& new_profile_id,
        const ProfileId& base_profile_id = default_base_profile_id);
    void create(
        const ProfileId& new_profile_id,
        const ProfileId& base_profile_id = default_base_profile_id);
    void delete_(const ProfileId& profile_id);


private:
    ProfileManager() = default;
};

} // namespace profile
} // namespace elona
