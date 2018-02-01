#pragma once

#include <array>
#include <optional>
#include <unordered_map>
#include "optional_ref.hpp"



namespace elona
{


struct item_data
{
    int id;
    int value;
    int weight;
    int dice_x;
    int dice_y;
    int hit_bonus;
    int damage_bonus;
    int pv;
    int dv;
    int material;
    int chargelevel;
    const char* infilterref;
    std::array<const char*, 4> description_jp;
    const char* description_en;
    int dbspec2;
    int dbspec3;
    int dbspec4;
    int dbspec5;
    int dbspec7;
    int dbspec8;
    int dbspec9;
    int dbspec10;
    int dbspec11;
    int dbspec18;
    int dbspec19;
    int dbspec20;
};



class item_db
{
public:
    item_db();

    optional_ref<item_data> operator[](int id) const;

private:
    std::unordered_map<int, item_data> data;
};



inline item_db the_item_db;


} // namespace elona
