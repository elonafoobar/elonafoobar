#pragma once

#include <string>
#include "../filesystem.hpp"



namespace elona
{
namespace profile
{

using ProfileId = std::string;



constexpr const char* default_base_profile_id = u8"_";
constexpr const char* default_profile_id = u8"default";



bool is_valid_id(const ProfileId& profile_id);
bool is_reserved_id(const ProfileId& profile_id);
bool exists(const ProfileId& profile_id);
fs::path get_dir_for(const ProfileId& profile_id);

} // namespace profile
} // namespace elona
