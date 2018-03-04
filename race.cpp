#include "race.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace
{



int define(lua_State* L, std::unordered_map<std::string, race_data>& storage)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

#define FIELD_I(name, default_value) \
    lua_getfield(L, -1, #name); \
    int name = lua_isnil(L, -1) ? (default_value) : luaL_checkinteger(L, -1); \
    lua_pop(L, 1);
#define FIELD_S(name, default_value) \
    lua_getfield(L, -1, #name); \
    const char* name = \
        lua_isnil(L, -1) ? (default_value) : luaL_checkstring(L, -1); \
    lua_pop(L, 1);
#define FIELD_B(name, default_value) \
    lua_getfield(L, -1, #name); \
    bool name = lua_isnil(L, -1) ? (default_value) : lua_toboolean(L, -1); \
    lua_pop(L, 1);

    FIELD_B(is_extra, true);
    FIELD_I(ordering, 30000);
    FIELD_I(male_image, 174);
    FIELD_I(female_image, 174);
    FIELD_I(breed_power, 500);
    FIELD_I(min_age, 1);
    FIELD_I(max_age, 1);
    FIELD_I(height, 2);
    FIELD_I(male_ratio, 50);
    FIELD_B(is_made_of_rock, false);
    FIELD_I(melee_attack_type, 0);
    FIELD_I(special_attack_type, 0);
    FIELD_I(dv_correction, 100);
    FIELD_I(pv_correction, 100);

    std::vector<int> body_parts;
    lua_getfield(L, -1, u8"body_parts");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int v = luaL_checkinteger(L, -1);
            body_parts.push_back(v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    std::unordered_map<int, int> skills;
    lua_getfield(L, -1, u8"skills");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int k = std::stoi(luaL_checkstring(L, -2) + 1);
            int v = luaL_checkinteger(L, -1);
            skills.emplace(k, v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

    std::unordered_map<int, int> resistances;
    lua_getfield(L, -1, u8"resistances");
    if (!lua_isnil(L, -1))
    {
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int k = std::stoi(luaL_checkstring(L, -2) + 1);
            int v = luaL_checkinteger(L, -1);
            resistances.emplace(k, v);
            lua_pop(L, 1);
        }
    }
    lua_pop(L, 1);

#undef FIELD_I
#undef FIELD_S
#undef FIELD_B

    storage.emplace(
        id,
        race_data{
            id,
            is_extra,
            ordering,
            male_image,
            female_image,
            breed_power,
            min_age,
            max_age,
            height,
            male_ratio,
            is_made_of_rock,
            melee_attack_type,
            special_attack_type,
            dv_correction,
            pv_correction,
            body_parts,
            skills,
            resistances,
        });

    return 0;
}


} // namespace



namespace elona
{



void race_db::initialize()
{
    cat::global.load(fs::u8path(u8"../data/race.lua"));

    lua_getglobal(cat::global.ptr(), u8"race");
    lua_getfield(cat::global.ptr(), -1, u8"__storage__");
    lua_pushnil(cat::global.ptr());
    while (lua_next(cat::global.ptr(), -2))
    {
        define(cat::global.ptr(), storage);
        lua_pop(cat::global.ptr(), 1);
    }
    lua_pop(cat::global.ptr(), 2);
}



optional_ref<race_data> race_db::operator[](const std::string& id) const
{
    const auto itr = storage.find(id);
    if (itr == std::end(storage))
        return std::nullopt;
    else
        return itr->second;
}



std::vector<std::reference_wrapper<const race_data>>
race_db::get_available_races(bool is_extra_race) const
{
    std::vector<std::reference_wrapper<const race_data>> ret;
    for (const auto& [_, race] : storage)
    {
        if (race.is_extra == is_extra_race)
        {
            ret.emplace_back(race);
        }
    }
    range::sort(ret, [](const auto& a, const auto& b) {
        return a.get().ordering < b.get().ordering;
    });
    return ret;
}



int access_race_info(int dbmode, const std::string& dbidn)
{
    auto data = the_race_db[dbidn];
    if (!data)
        return 0;

    switch (dbmode)
    {
    case 3: break;
    case 11:
        buff = i18n::_(u8"race", dbidn, u8"description");
        ref1 = data->male_image;
        ref2 = data->female_image;
        return 0;
    default: assert(0);
    }

    cdatan(2, rc) = dbidn;
    cdata[rc].melee_attack_type = data->melee_attack_type;
    cdata[rc].special_attack_type = data->special_attack_type;
    cdata[rc].dv_correction_value = data->dv_correction;
    cdata[rc].pv_correction_value = data->pv_correction;

    cdata[rc].birth_year =
        gdata_year - (rnd(data->max_age - data->min_age + 1) + data->min_age);
    cdata[rc].height = data->height;
    if (mode == 1)
    {
        cdata[rc].sex = cmsex;
    }
    else
    {
        if (rnd(100) < data->male_ratio)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
    }

    if (cdata[rc].sex == 0)
    {
        cdata[rc].image = data->male_image;
    }
    else
    {
        cdata[rc].image = data->female_image;
    }

    if (data->is_made_of_rock)
    {
        cbitmod(983, rc, 1);
    }

    {
        size_t i{};
        for (const auto& p : data->body_parts)
        {
            cdata_body_part(rc, i) = p * 10'000;
            ++i;
        }
        cdata_body_part(rc, i) = 10 * 10'000;
        ++i;
        cdata_body_part(rc, i) = 11 * 10'000;
        ++i;
    }
    for (const auto& [k, v] : data->skills)
    {
        skillinit(k, rc, v);
    }
    for (const auto& [k, v] : data->resistances)
    {
        sdata(k, rc) = v;
    }

    return 0;
}



} // namespace elona
