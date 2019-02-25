#pragma once

#include "../../util/noncopyable.hpp"
#include "profile.hpp"



namespace elona
{
namespace profile
{

class ProfileManager : lib::noncopyable
{
public:
    static ProfileManager& instance();

    void init(const ProfileId& profile_id);
    void load(const ProfileId& profile_id);

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
