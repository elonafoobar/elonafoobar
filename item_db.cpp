#include "item_db.hpp"
#include <string>
#include "cat.hpp"

using namespace elona;


namespace
{


// FIXME: DO NOT USE A GLOBAL VARIABLE!
std::unordered_map<int, item_data>* storage_ptr;


int define(lua_State* state)
{
    int argc = lua_gettop(state);
    if (argc != 2)
        throw 0;

    const char* id = luaL_checklstring(state, 1, nullptr);
    if (!id)
        throw 0;

#define FIELD_I(name) \
    lua_getfield(state, 2, #name); \
    int name = luaL_checkinteger(state, -1);
#define FIELD_S(name) \
    lua_getfield(state, 2, #name); \
    const char* name = luaL_checkstring(state, -1);

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

    FIELD_S(infilterref);
    FIELD_S(description_jp_0);
    FIELD_S(description_jp_1);
    FIELD_S(description_jp_2);
    FIELD_S(description_jp_3);
    FIELD_S(description_en);

    FIELD_I(dbspec2);
    FIELD_I(dbspec3);
    FIELD_I(dbspec4);
    FIELD_I(dbspec7);
    FIELD_I(dbspec8);
    FIELD_I(dbspec9);
    FIELD_I(dbspec10);
    FIELD_I(dbspec11);
    FIELD_I(dbspec18);
    FIELD_I(dbspec19);
    FIELD_I(dbspec20);
    FIELD_I(level);
    FIELD_I(fltselect);
    FIELD_I(category);
    FIELD_I(subcategory);
    FIELD_I(rarity);
    FIELD_I(coefficient);

#undef FIELD_I
#undef FIELD_S

    storage_ptr->emplace(
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

            infilterref,
            {
                description_jp_0,
                description_jp_1,
                description_jp_2,
                description_jp_3,
            },
            description_en,

            dbspec2,
            dbspec3,
            dbspec4,
            dbspec7,
            dbspec8,
            dbspec9,
            dbspec10,
            dbspec11,
            dbspec18,
            dbspec19,
            dbspec20,
            level,
            fltselect,
            category,
            subcategory,
            rarity,
            coefficient,
        });

    return 0;
}


} // namespace



namespace elona
{



item_db::item_db()
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    cat::register_function(state, "define", &define);
    storage_ptr = &storage;
    cat::load(state, fs::u8path(u8"../data/item.lua"));
    storage_ptr = nullptr;
    lua_close(state);
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
