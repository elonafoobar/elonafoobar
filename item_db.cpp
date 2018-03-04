#include "item_db.hpp"
#include <string>
#include "cat.hpp"

using namespace elona;


namespace
{



int define(lua_State* L, std::unordered_map<int, item_data>& storage)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(L, -1, #name); \
    int name = luaL_checkinteger(L, -1); \
    lua_pop(L, 1);
#define FIELD_S(name) \
    lua_getfield(L, -1, #name); \
    const char* name = luaL_checkstring(L, -1); \
    lua_pop(L, 1);
#define FIELD_B(name) \
    lua_getfield(L, -1, #name); \
    bool name = lua_toboolean(L, -1); \
    lua_pop(L, 1);

    FIELD_I(image);
    FIELD_I(value);
    FIELD_I(weight);
    FIELD_I(dice_x);
    FIELD_I(dice_y);
    FIELD_I(hit_bonus);
    FIELD_I(damage_bonus);
    FIELD_I(pv);
    FIELD_I(dv);
    FIELD_I(material);
    FIELD_I(chargelevel);

    FIELD_S(description_jp_0);
    FIELD_S(description_jp_1);
    FIELD_S(description_jp_2);
    FIELD_S(description_jp_3);
    FIELD_S(description_en);

    FIELD_I(is_readable);
    FIELD_I(is_zappable);
    FIELD_I(is_drinkable);
    FIELD_I(is_cargo);
    FIELD_I(is_usable);
    FIELD_I(appearance);
    FIELD_I(expiration_date);
    FIELD_I(level);
    FIELD_I(fltselect);
    FIELD_I(category);
    FIELD_I(subcategory);
    FIELD_I(rarity);
    FIELD_I(coefficient);

    FIELD_I(light);
    FIELD_S(katakana_name);
    FIELD_S(original_name_jp);
    FIELD_S(original_name_en);
    FIELD_S(originalnameref2);
    FIELD_B(has_random_name);

    FIELD_S(filter);
    FIELD_S(rffilter);

#undef FIELD_I
#undef FIELD_S

    storage.emplace(
        std::stoi(id), // TODO
        item_data{
            std::stoi(id),
            image,
            value,
            weight,
            dice_x,
            dice_y,
            hit_bonus,
            damage_bonus,
            pv,
            dv,
            material,
            chargelevel,

            {
                description_jp_0,
                description_jp_1,
                description_jp_2,
                description_jp_3,
            },
            description_en,

            is_readable,
            is_zappable,
            is_drinkable,
            is_cargo,
            is_usable,
            appearance,
            expiration_date,
            level,
            fltselect,
            category,
            subcategory,
            rarity,
            coefficient,
            light,
            katakana_name,
            original_name_jp,
            original_name_en,
            originalnameref2,
            has_random_name,

            filter,
            rffilter,
        });

    return 0;
}


} // namespace



namespace elona
{



void item_db::initialize()
{
    cat::global.load(fs::u8path(u8"../data/item.lua"));

    lua_getglobal(cat::global.ptr(), u8"item");
    lua_getfield(cat::global.ptr(), -1, u8"__storage__");
    lua_pushnil(cat::global.ptr());
    while (lua_next(cat::global.ptr(), -2))
    {
        define(cat::global.ptr(), storage);
        lua_pop(cat::global.ptr(), 1);
    }
    lua_pop(cat::global.ptr(), 2);
}



optional_ref<item_data> item_db::operator[](int id) const
{
    const auto itr = storage.find(id);
    if (itr == std::end(storage))
        return std::nullopt;
    else
        return itr->second;
}



} // namespace elona
