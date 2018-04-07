#include "race.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"



namespace elona
{


void race_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw 0;

    ELONA_CAT_DB_FIELD_BOOLEAN(is_extra, true);
    ELONA_CAT_DB_FIELD_INTEGER(ordering, 30000);
    ELONA_CAT_DB_FIELD_INTEGER(male_image, 174);
    ELONA_CAT_DB_FIELD_INTEGER(female_image, 174);
    ELONA_CAT_DB_FIELD_INTEGER(breed_power, 500);
    ELONA_CAT_DB_FIELD_INTEGER(min_age, 1);
    ELONA_CAT_DB_FIELD_INTEGER(max_age, 1);
    ELONA_CAT_DB_FIELD_INTEGER(height, 2);
    ELONA_CAT_DB_FIELD_INTEGER(male_ratio, 50);
    ELONA_CAT_DB_FIELD_BOOLEAN(is_made_of_rock, false);
    ELONA_CAT_DB_FIELD_INTEGER(melee_attack_type, 0);
    ELONA_CAT_DB_FIELD_INTEGER(special_attack_type, 0);
    ELONA_CAT_DB_FIELD_INTEGER(dv_correction, 100);
    ELONA_CAT_DB_FIELD_INTEGER(pv_correction, 100);

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
}


std::vector<std::reference_wrapper<const race_data>>
race_db::get_available_races(bool is_extra_race) const
{
    std::vector<std::reference_wrapper<const race_data>> ret;
    for (const auto& pair : storage)
    {
        if (pair.second.is_extra == is_extra_race)
        {
            ret.emplace_back(pair.second);
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
    for (const auto& pair : data->skills)
    {
        skillinit(pair.first, rc, pair.second);
    }
    for (const auto& pair : data->resistances)
    {
        sdata(pair.first, rc) = pair.second;
    }

    return 0;
}



} // namespace elona
