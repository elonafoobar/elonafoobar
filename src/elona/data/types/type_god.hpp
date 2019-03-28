#pragma once
#include <unordered_set>
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct GodSkillBonus
{
    int factor;
    int max;
};

struct GodData
{
    SharedId id;
    int legacy_id;
    optional<std::string> wish_name;
    optional<SharedId> summon_id;
    sol::table items;
    SharedId servant_id;
    std::unordered_map<int, GodSkillBonus> skills;
    SharedId artifact_id;
    std::unordered_set<SharedId> offerings;
};



ELONA_DEFINE_LUA_DB(GodDB, GodData, true, "core.god")



extern GodDB the_god_db;

} // namespace elona
