#pragma once

#include "../lua_lazy_cache.hpp"



namespace elona
{

struct AbilityData
{
    SharedId id;
    int legacy_id;
    int related_basic_attribute;
    int ability_type;
    int cost;
    int range;
    int difficulty;
};



ELONA_DEFINE_LUA_DB(AbilityDB, AbilityData, "core.ability")



inline AbilityDB the_ability_db;

} // namespace elona
