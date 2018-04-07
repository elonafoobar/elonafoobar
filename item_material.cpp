#include "item_material.hpp"

using namespace elona;


namespace
{


std::vector<std::vector<int>> leather_table = {
    {
        3,
        1,
        19,
        27,
        17,
    },

    {
        2,
        4,
        26,
        32,
        28,
    },

    {
        16,
        5,
        22,
        14,
        15,
    },

    {
        18,
        20,
        7,
        24,
        8,
    },
};


std::vector<std::vector<int>> metal_table = {
    {
        12,
        10,
        9,
        30,
        29,
    },

    {
        34,
        25,
        26,
        11,
        13,
    },

    {
        21,
        5,
        22,
        23,
        15,
    },

    {
        33,
        20,
        7,
        31,
        8,
    },
};


} // namespace



namespace elona
{


item_material_db the_item_material_db;


void item_material_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

    ELONA_CAT_DB_FIELD_INTEGER(weight, 0);
    ELONA_CAT_DB_FIELD_INTEGER(value, 0);
    ELONA_CAT_DB_FIELD_INTEGER(hit_bonus, 0);
    ELONA_CAT_DB_FIELD_INTEGER(damage_bonus, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dv, 0);
    ELONA_CAT_DB_FIELD_INTEGER(pv, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dice_y, 0);
    ELONA_CAT_DB_FIELD_INTEGER(color, 0);

    ELONA_CAT_DB_FIELD_BOOLEAN(fireproof, false);
    ELONA_CAT_DB_FIELD_BOOLEAN(acidproof, false);

    std::vector<enc_t> enchantments;
    lua_getfield(L, -1, u8"enchantments");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int k = std::stoi(luaL_checkstring(L, -2) + 1);
            int v = luaL_checkinteger(L, -1);
            enchantments.emplace_back(enc_t{k, v});
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    storage.emplace(
        std::stoi(id), // TODO
        item_material_data{
            std::stoi(id),
            weight,
            value,
            hit_bonus,
            damage_bonus,
            dv,
            pv,
            dice_y,
            color,
            enchantments,
            fireproof,
            acidproof,
        });
}



int item_material_db::lookup_leather(int x, int y)
{
    return leather_table[x][y];
}



int item_material_db::lookup_metal(int x, int y)
{
    return metal_table[x][y];
}



} // namespace elona
