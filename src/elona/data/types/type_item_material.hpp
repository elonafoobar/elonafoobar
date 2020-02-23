#pragma once
#include "../lua_lazy_cache.hpp"



namespace elona
{

struct ItemMaterialData
{
    SharedId id;
    int legacy_id;
    int weight;
    int value;
    int hit_bonus;
    int damage_bonus;
    int dv;
    int pv;
    int dice_y;
    int color;
    std::unordered_map<int, int> enchantments;
    bool fireproof;
    bool acidproof;
};



ELONA_DEFINE_LUA_DB(ItemMaterialDB, ItemMaterialData, "core.item_material")



inline ItemMaterialDB the_item_material_db;

} // namespace elona
