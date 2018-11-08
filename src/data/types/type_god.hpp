#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct GodData
{
    int id;
};



ELONA_DEFINE_LUA_DB(GodDB, GodData, true, "core.god")



extern GodDB the_god_db;

} // namespace elona
