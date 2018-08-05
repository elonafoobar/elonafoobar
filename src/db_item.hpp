#pragma once

#include <array>
#include <unordered_map>
#include "cat.hpp"
#include "lion.hpp"
#include "optional.hpp"



namespace elona
{


struct item_data
{
    int id;
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
    std::array<std::string, 4> description_jp;
    std::string description_en;
    int is_readable;
    int is_zappable;
    int is_drinkable;
    int is_cargo;
    int is_usable;
    int appearance;
    int expiration_date;
    int level;
    int fltselect;
    int category;
    int subcategory;
    int rarity;
    int coefficient;
    int light;
    std::string katakana_name;
    std::string original_name_jp;
    std::string original_name_en;
    std::string originalnameref2;
    bool has_random_name;
    std::string filter;
    std::string rffilter;
};



class item_db_ex;


namespace lion
{

template <>
struct lion_db_traits<item_db_ex>
{
    using data_type = item_data;
    using legacy_id_type = int;
    static constexpr const char* datatype_name = u8"item";
};

} // namespace lion



class item_db_ex : public lion::lion_db<item_db_ex>
{
public:
    item_db_ex() = default;

    item_data convert(const std::string&, const sol::table&, lua::lua_env&);
};


extern item_db_ex the_item_db;


} // namespace elona
