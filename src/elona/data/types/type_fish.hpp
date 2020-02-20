#pragma once
#include "../base_database.hpp"



namespace elona
{

struct FishData
{
    SharedId id;
    int legacy_id;
    bool no_generate;
    int rank;
    int rarity;
    int difficulty;
    int weight;
    int value;
    int item_id;
};



ELONA_DEFINE_LUA_DB(FishDB, FishData, "core.fish")



extern FishDB the_fish_db;

} // namespace elona
