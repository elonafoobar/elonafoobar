#pragma once

#include "cat.hpp"
#include "item.hpp"


namespace elona
{


struct item_material_data
{
    int id;
    int weight;
    int value;
    int hit_bonus;
    int damage_bonus;
    int dv;
    int pv;
    int dice_y;
    int color;
    std::vector<enc_t> enchantments;
    bool fireproof;
    bool acidproof;
};


class ItemMaterialDB;


namespace cat
{

template <>
struct cat_db_traits<ItemMaterialDB>
{
    using id_type = int;
    using data_type = item_material_data;
    static constexpr const char* filename = u8"item_material.lua";
    static constexpr const char* table_name = u8"item_material";
};

} // namespace cat



class ItemMaterialDB : public cat::CatDB<ItemMaterialDB>
{
public:
    ItemMaterialDB() = default;

    int lookup_leather(int x, int y);
    int lookup_metal(int x, int y);

    std::vector<int> get_material_ids();

    void define(lua_State* L);
};


extern ItemMaterialDB the_item_material_db;



} // namespace elona
