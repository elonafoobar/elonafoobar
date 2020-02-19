#pragma once
#include "../base_database.hpp"



namespace elona
{

struct GodData
{
    data::InstanceId id;
    int legacy_id;
};



ELONA_DEFINE_LUA_DB(GodDB, GodData, "core.god")



extern GodDB the_god_db;

} // namespace elona
