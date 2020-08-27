#pragma once

#include <array>
#include <unordered_map>

#include "../../enums.hpp"
#include "../../optional.hpp"
#include "../base_database.hpp"



namespace elona
{

using I18NKey = std::string;



struct ItemData
{
    data::InstanceId id;
    int legacy_id;
    int image;
    int value;
    int weight;
    int dice_x;
    int dice_y;
    int hit_bonus;
    int damage_bonus;
    int pv;
    int dv;
    data::InstanceId material;
    int chargelevel;
    bool is_readable;
    bool is_zappable;
    bool is_drinkable;
    bool is_cargo;
    bool is_usable;
    int appearance;
    int expiration_date;
    int level;
    int fltselect;
    ItemCategory category;
    int subcategory;
    int rarity;
    int coefficient;
    int light;
    std::string originalnameref2;
    bool has_random_name;
    ColorIndex color;
    std::string filter;
    std::string rffilter;
    I18NKey locale_key_prefix;
    optional<std::string> on_use_callback;
};



ELONA_DEFINE_LUA_DB(ItemDB, ItemData, "core.item")



extern ItemDB the_item_db;

} // namespace elona
