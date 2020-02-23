#pragma once

#include <array>
#include <unordered_map>

#include "../../enums.hpp"
#include "../../optional.hpp"
#include "../lua_lazy_cache.hpp"



namespace elona
{

using I18NKey = std::string;



struct ItemData
{
    SharedId id;
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
    int material;
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
    int category;
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



inline ItemDB the_item_db;

} // namespace elona
