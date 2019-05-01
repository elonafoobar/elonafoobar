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

    void create(const ProfileId& new_profile_id);
    void delete_(const ProfileId& profile_id);

    ProfileId generate_new_id();


private:
    ProfileManager() = default;
};

} // namespace profile
} // namespace elona
