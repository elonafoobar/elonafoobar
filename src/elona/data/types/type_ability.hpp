#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct AbilityData
{
    int id;
    int related_basic_attribute;
    int ability_type;
    int cost;
    int range;
    int difficulty;
};



ELONA_DEFINE_LUA_DB(AbilityDB, AbilityData, true, "core.ability")



extern AbilityDB the_ability_db;

} // namespace elona
