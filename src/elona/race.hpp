#pragma once

#include <functional>
#include <string>
#include <vector>

#include "data/types/type_race.hpp"



namespace elona
{

struct Character;



void race_init_chara(Character& chara, data::InstanceId race_id);
std::vector<std::reference_wrapper<const RaceData>> race_get_available(
    bool is_extra_race);

} // namespace elona
