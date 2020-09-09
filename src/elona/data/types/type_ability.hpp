#pragma once

#include "../base_database.hpp"



namespace elona
{

struct AbilityData
{
    data::InstanceId id;
    int integer_id;
    int related_basic_attribute;
    int ability_type;
    int cost;
    int range;
    int difficulty;
};



ELONA_DEFINE_LUA_DB(AbilityDB, AbilityData, "core.ability")



extern AbilityDB the_ability_db;

} // namespace elona
