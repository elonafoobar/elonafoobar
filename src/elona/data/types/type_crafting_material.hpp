#pragma once

#include "../base_database.hpp"



namespace elona
{

struct CraftingMaterialData
{
    data::InstanceId id;
    int integer_id;
    int level;
    int rarity;
    int icon;
    std::vector<int> spots;
};



ELONA_DEFINE_LUA_DB(
    CraftingMaterialDB,
    CraftingMaterialData,
    "core.crafting_material")



extern CraftingMaterialDB the_crafting_material_db;

} // namespace elona
