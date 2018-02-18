#include "race.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "variables.hpp"


namespace
{


// FIXME: DO NOT USE A GLOBAL VARIABLE!
std::unordered_map<std::string, race_data>* storage_ptr;


int define(lua_State* state)
{
    int argc = lua_gettop(state);
    if (argc != 2)
        throw 0;

    const char* id = luaL_checklstring(state, 1, nullptr);
    if (!id)
        throw 0;

#define FIELD_I(name, default_value) \
    lua_getfield(state, 2, #name); \
    int name = \
        lua_isnil(state, -1) ? (default_value) : luaL_checkinteger(state, -1); \
    lua_pop(state, 1);
#define FIELD_S(name, default_value) \
    lua_getfield(state, 2, #name); \
    const char* name = \
        lua_isnil(state, -1) ? (default_value) : luaL_checkstring(state, -1); \
    lua_pop(state, 1);
#define FIELD_B(name, default_value) \
    lua_getfield(state, 2, #name); \
    bool name = \
        lua_isnil(state, -1) ? (default_value) : lua_toboolean(state, -1); \
    lua_pop(state, 1);

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
    lua_getfield(state, 2, u8"body_parts");
    if (!lua_isnil(state, -1))
    {
        lua_pushnil(state);
        while (lua_next(state, -2))
        {
            int v = luaL_checkinteger(state, -1);
            body_parts.push_back(v);
            lua_pop(state, 1);
        }
    }
    std::unordered_map<int, int> skills;
    lua_getfield(state, 2, u8"skills");
    if (!lua_isnil(state, -1))
    {
        lua_pushnil(state);
        while (lua_next(state, -2))
        {
            int k = std::stoi(luaL_checkstring(state, -2) + 1);
            int v = luaL_checkinteger(state, -1);
            skills.emplace(k, v);
            lua_pop(state, 1);
        }
    }
    std::unordered_map<int, int> resistances;
    lua_getfield(state, 2, u8"resistances");
    if (!lua_isnil(state, -1))
    {
        lua_pushnil(state);
        while (lua_next(state, -2))
        {
            int k = std::stoi(luaL_checkstring(state, -2) + 1);
            int v = luaL_checkinteger(state, -1);
            resistances.emplace(k, v);
            lua_pop(state, 1);
        }
    }

#undef FIELD_I
#undef FIELD_S
#undef FIELD_B

    storage_ptr->emplace(
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
    cat::global.register_function("Race", &define);
    storage_ptr = &storage;
    cat::global.load(fs::u8path(u8"../data/race.lua"));
    storage_ptr = nullptr;
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
