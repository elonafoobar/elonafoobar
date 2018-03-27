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


class item_material_db;


namespace cat
{

template <>
struct cat_db_traits<item_material_db>
{
    using id_type = int;
    using data_type = item_material_data;
    static constexpr const char* filename = u8"item_material.lua";
    static constexpr const char* table_name = u8"item_material";
};

} // namespace cat



class item_material_db : public cat::cat_db<item_material_db>
{
public:
    item_material_db() = default;

    int lookup_leather(int x, int y);
    int lookup_metal(int x, int y);

    void define(lua_State* L);
};


inline item_material_db the_item_material_db;



} // namespace elona
