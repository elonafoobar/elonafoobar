#pragma once

#include <functional>
#include <string>
#include <vector>
#include "data/types/type_race.hpp"



namespace elona
{

std::vector<std::reference_wrapper<const RaceData>> race_get_available(
    bool is_extra_race);
int access_race_info(int dbmode, const std::string& dbidn);

} // namespace elona
