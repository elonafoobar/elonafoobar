#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct FishData
{
    int id;
    bool no_generate;
    int rank;
    int rarity;
    int difficulty;
    int weight;
    int value;
    int item_id;
};



ELONA_DEFINE_LUA_DB(FishDB, FishData, true, "core.fish")



extern FishDB the_fish_db;

} // namespace elona
