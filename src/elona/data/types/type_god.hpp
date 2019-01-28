#pragma once
#include <unordered_set>
#include "../../lua_env/wrapped_function.hpp"
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct GodData
{
    int id;
    optional<std::string> wish_name;
    optional<SharedId> summon_id;
    sol::table items;
    SharedId servant_id;
    std::unordered_map<int, lua::WrappedFunction> skills;
    SharedId artifact_id;
    std::unordered_set<SharedId> offerings;
};



ELONA_DEFINE_LUA_DB(GodDB, GodData, true, "core.god")



extern GodDB the_god_db;

} // namespace elona
