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

#define FIELD_I(name) \
    lua_getfield(state, 2, #name); \
    int name = luaL_checkinteger(state, -1);
#define FIELD_S(name) \
    lua_getfield(state, 2, #name); \
    const char* name = luaL_checkstring(state, -1);
#define FIELD_B(name) \
    lua_getfield(state, 2, #name); \
    bool name = lua_toboolean(state, -1);

    FIELD_B(is_extra);
    FIELD_I(ordering);
    FIELD_I(male_image);
    FIELD_I(female_image);
    FIELD_I(breed_power);
    FIELD_I(min_age);
    FIELD_I(max_age);
    FIELD_I(height);
    FIELD_I(male_ratio);

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
        });

    return 0;
}


} // namespace



namespace elona
{



race_db::race_db()
{
    lua_State* state = luaL_newstate();
    luaL_openlibs(state);
    cat::register_function(state, "define", &define);
    storage_ptr = &storage;
    cat::load(state, fs::u8path(u8"../data/race.lua"));
    storage_ptr = nullptr;
    lua_close(state);
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
    case 2: cpicref = data->male_image; return 0;
    case 3: break;
    case 11:
        buff = i18n::_(u8"race", dbidn, u8"description");
        ref1 = data->male_image;
        ref2 = data->female_image;
        return 0;
    default: assert(0);
    }

    // Common initialization
    cdatan(2, rc) = dbidn;
    cdata[rc].melee_attack_type = 0; // Default
    cdata[rc].special_attack_type = 0; // Default
    cdata[rc].dv_correction_value = 100; // Default
    cdata[rc].pv_correction_value = 100; // Default

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

    if (false)
    {
    }
    else if (dbidn == u8"kobolt")
    {
        skillinit(2, rc, 90);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 6);
        skillinit(12, rc, 5);
        skillinit(13, rc, 3);
        skillinit(14, rc, 2);
        skillinit(15, rc, 2);
        skillinit(16, rc, 4);
        skillinit(17, rc, 2);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(300, rc, 3);
        skillinit(157, rc, 2);
        skillinit(174, rc, 3);
        s(1) = u8"HD|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"orc")
    {
        skillinit(2, rc, 130);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 6);
        skillinit(12, rc, 3);
        skillinit(13, rc, 2);
        skillinit(14, rc, 2);
        skillinit(15, rc, 3);
        skillinit(16, rc, 4);
        skillinit(17, rc, 2);
        skillinit(18, rc, 70);
        skillinit(106, rc, 1);
        skillinit(154, rc, 3);
        skillinit(169, rc, 3);
        skillinit(168, rc, 3);
        s(1) = u8"HD|BD|BK|HA|HA|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"troll")
    {
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 90);
        skillinit(3, rc, 80);
        skillinit(10, rc, 10);
        skillinit(11, rc, 9);
        skillinit(12, rc, 1);
        skillinit(13, rc, 2);
        skillinit(14, rc, 2);
        skillinit(15, rc, 2);
        skillinit(16, rc, 3);
        skillinit(17, rc, 3);
        skillinit(18, rc, 60);
        skillinit(106, rc, 3);
        skillinit(154, rc, 40);
        s(1) = u8"HD|BD|BK|HA|HA|A_|W_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"lizardman")
    {
        cdata[rc].dv_correction_value = 120;
        skillinit(2, rc, 120);
        skillinit(3, rc, 70);
        skillinit(10, rc, 7);
        skillinit(11, rc, 5);
        skillinit(12, rc, 6);
        skillinit(13, rc, 7);
        skillinit(14, rc, 4);
        skillinit(15, rc, 4);
        skillinit(16, rc, 5);
        skillinit(17, rc, 3);
        skillinit(18, rc, 80);
        skillinit(106, rc, 2);
        skillinit(104, rc, 3);
        skillinit(168, rc, 3);
        skillinit(173, rc, 2);
        s(1) = u8"HD|BD|BK|HA|HA|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"minotaur")
    {
        skillinit(2, rc, 160);
        skillinit(3, rc, 60);
        skillinit(10, rc, 12);
        skillinit(11, rc, 8);
        skillinit(12, rc, 3);
        skillinit(13, rc, 4);
        skillinit(14, rc, 3);
        skillinit(15, rc, 4);
        skillinit(16, rc, 7);
        skillinit(17, rc, 4);
        skillinit(18, rc, 65);
        skillinit(106, rc, 3);
        skillinit(152, rc, 4);
        skillinit(186, rc, 3);
        s(1) = u8"HD|BD|HA|HA|R_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"yerles")
    {
        skillinit(2, rc, 110);
        skillinit(3, rc, 90);
        skillinit(10, rc, 7);
        skillinit(11, rc, 8);
        skillinit(12, rc, 8);
        skillinit(13, rc, 8);
        skillinit(14, rc, 12);
        skillinit(15, rc, 8);
        skillinit(16, rc, 8);
        skillinit(17, rc, 7);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(110, rc, 5);
        skillinit(150, rc, 3);
        skillinit(156, rc, 2);
        skillinit(111, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"norland")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 90);
        skillinit(10, rc, 8);
        skillinit(11, rc, 8);
        skillinit(12, rc, 6);
        skillinit(13, rc, 6);
        skillinit(14, rc, 7);
        skillinit(15, rc, 9);
        skillinit(16, rc, 7);
        skillinit(17, rc, 6);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(172, rc, 3);
        skillinit(152, rc, 3);
        skillinit(167, rc, 3);
        skillinit(188, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"eulderna")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 100);
        skillinit(10, rc, 6);
        skillinit(11, rc, 7);
        skillinit(12, rc, 7);
        skillinit(13, rc, 10);
        skillinit(14, rc, 8);
        skillinit(15, rc, 10);
        skillinit(16, rc, 12);
        skillinit(17, rc, 8);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(172, rc, 5);
        skillinit(150, rc, 3);
        skillinit(174, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"fairy")
    {
        sdata(60, rc) = 200;
        sdata(53, rc) = 200;
        sdata(58, rc) = 200;
        sdata(56, rc) = 200;
        sdata(54, rc) = 200;
        sdata(57, rc) = 200;
        sdata(59, rc) = 200;
        cdata[rc].dv_correction_value = 250;
        skillinit(2, rc, 40);
        skillinit(3, rc, 130);
        skillinit(10, rc, 3);
        skillinit(11, rc, 4);
        skillinit(12, rc, 9);
        skillinit(13, rc, 10);
        skillinit(14, rc, 8);
        skillinit(15, rc, 8);
        skillinit(16, rc, 13);
        skillinit(17, rc, 12);
        skillinit(18, rc, 120);
        skillinit(106, rc, 1);
        skillinit(172, rc, 5);
        skillinit(300, rc, 3);
        skillinit(171, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"asura")
    {
        cdata[rc].dv_correction_value = 200;
        skillinit(2, rc, 90);
        skillinit(3, rc, 70);
        skillinit(10, rc, 11);
        skillinit(11, rc, 9);
        skillinit(12, rc, 14);
        skillinit(13, rc, 6);
        skillinit(14, rc, 4);
        skillinit(15, rc, 4);
        skillinit(16, rc, 5);
        skillinit(17, rc, 5);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(166, rc, 30);
        skillinit(187, rc, 6);
        skillinit(161, rc, 4);
        s(1) = u8"HA|HA|HA|HA|N_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"slime")
    {
        cdata[rc].special_attack_type = 2;
        skillinit(2, rc, 80);
        skillinit(3, rc, 100);
        skillinit(10, rc, 4);
        skillinit(11, rc, 5);
        skillinit(12, rc, 7);
        skillinit(13, rc, 5);
        skillinit(14, rc, 6);
        skillinit(15, rc, 8);
        skillinit(16, rc, 4);
        skillinit(17, rc, 13);
        skillinit(18, rc, 55);
        skillinit(106, rc, 2);
        skillinit(173, rc, 2);
        skillinit(183, rc, 3);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"wolf")
    {
        cdata[rc].dv_correction_value = 140;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 8);
        skillinit(12, rc, 6);
        skillinit(13, rc, 11);
        skillinit(14, rc, 7);
        skillinit(15, rc, 8);
        skillinit(16, rc, 4);
        skillinit(17, rc, 6);
        skillinit(18, rc, 80);
        skillinit(106, rc, 2);
        skillinit(173, rc, 2);
        skillinit(187, rc, 2);
        s(1) = u8"HD|N_|BD|BK|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"dwarf")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 100);
        skillinit(10, rc, 10);
        skillinit(11, rc, 11);
        skillinit(12, rc, 8);
        skillinit(13, rc, 6);
        skillinit(14, rc, 6);
        skillinit(15, rc, 7);
        skillinit(16, rc, 6);
        skillinit(17, rc, 6);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(184, rc, 4);
        skillinit(179, rc, 3);
        skillinit(163, rc, 4);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"juere")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 100);
        skillinit(10, rc, 7);
        skillinit(11, rc, 8);
        skillinit(12, rc, 12);
        skillinit(13, rc, 10);
        skillinit(14, rc, 10);
        skillinit(15, rc, 8);
        skillinit(16, rc, 8);
        skillinit(17, rc, 11);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(183, rc, 4);
        skillinit(158, rc, 2);
        skillinit(156, rc, 2);
        skillinit(111, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"zombie")
    {
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        skillinit(2, rc, 120);
        skillinit(3, rc, 100);
        skillinit(10, rc, 10);
        skillinit(11, rc, 8);
        skillinit(12, rc, 2);
        skillinit(13, rc, 2);
        skillinit(14, rc, 1);
        skillinit(15, rc, 6);
        skillinit(16, rc, 6);
        skillinit(17, rc, 2);
        skillinit(18, rc, 45);
        skillinit(106, rc, 3);
        skillinit(184, rc, 3);
        skillinit(185, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|R_|A_|W_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"elea")
    {
        skillinit(2, rc, 90);
        skillinit(3, rc, 110);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 8);
        skillinit(13, rc, 8);
        skillinit(14, rc, 8);
        skillinit(15, rc, 12);
        skillinit(16, rc, 13);
        skillinit(17, rc, 10);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(164, rc, 5);
        skillinit(172, rc, 2);
        skillinit(165, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"rabbit")
    {
        skillinit(2, rc, 90);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 4);
        skillinit(12, rc, 6);
        skillinit(13, rc, 11);
        skillinit(14, rc, 5);
        skillinit(15, rc, 4);
        skillinit(16, rc, 4);
        skillinit(17, rc, 10);
        skillinit(18, rc, 100);
        skillinit(106, rc, 1);
        skillinit(301, rc, 3);
        s(1) = u8"HD|N_|BD|BK|A_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"sheep")
    {
        skillinit(2, rc, 130);
        skillinit(3, rc, 80);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 5);
        skillinit(13, rc, 6);
        skillinit(14, rc, 4);
        skillinit(15, rc, 5);
        skillinit(16, rc, 4);
        skillinit(17, rc, 8);
        skillinit(18, rc, 60);
        skillinit(106, rc, 1);
        skillinit(154, rc, 3);
        skillinit(161, rc, 3);
        s(1) = u8"HD|N_|BD|BK|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"frog")
    {
        skillinit(2, rc, 80);
        skillinit(3, rc, 80);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 6);
        skillinit(13, rc, 8);
        skillinit(14, rc, 5);
        skillinit(15, rc, 5);
        skillinit(16, rc, 5);
        skillinit(17, rc, 6);
        skillinit(18, rc, 60);
        skillinit(106, rc, 1);
        skillinit(183, rc, 3);
        skillinit(160, rc, 2);
        s(1) = u8"BD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"centipede")
    {
        skillinit(2, rc, 90);
        skillinit(3, rc, 80);
        skillinit(10, rc, 6);
        skillinit(11, rc, 5);
        skillinit(12, rc, 5);
        skillinit(13, rc, 6);
        skillinit(14, rc, 3);
        skillinit(15, rc, 2);
        skillinit(16, rc, 2);
        skillinit(17, rc, 2);
        skillinit(18, rc, 70);
        skillinit(106, rc, 1);
        skillinit(186, rc, 3);
        s(1) = u8"BK|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"snail")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 4);
        skillinit(11, rc, 5);
        skillinit(12, rc, 3);
        skillinit(13, rc, 6);
        skillinit(14, rc, 3);
        skillinit(15, rc, 4);
        skillinit(16, rc, 2);
        skillinit(17, rc, 4);
        skillinit(18, rc, 25);
        skillinit(106, rc, 1);
        skillinit(111, rc, 5);
        s(1) = u8"BK|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"mandrake")
    {
        skillinit(2, rc, 70);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 6);
        skillinit(12, rc, 5);
        skillinit(13, rc, 10);
        skillinit(14, rc, 8);
        skillinit(15, rc, 8);
        skillinit(16, rc, 10);
        skillinit(17, rc, 4);
        skillinit(18, rc, 60);
        skillinit(106, rc, 2);
        skillinit(165, rc, 3);
        skillinit(150, rc, 2);
        skillinit(164, rc, 3);
        s(1) = u8"HD|BK|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"beetle")
    {
        cdata[rc].pv_correction_value = 140;
        skillinit(2, rc, 80);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 6);
        skillinit(12, rc, 5);
        skillinit(13, rc, 7);
        skillinit(14, rc, 4);
        skillinit(15, rc, 5);
        skillinit(16, rc, 4);
        skillinit(17, rc, 3);
        skillinit(18, rc, 75);
        skillinit(106, rc, 2);
        skillinit(159, rc, 3);
        skillinit(157, rc, 3);
        s(1) = u8"N_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"mushroom")
    {
        cdata[rc].melee_attack_type = 7;
        cdata[rc].special_attack_type = 5;
        skillinit(2, rc, 50);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 7);
        skillinit(12, rc, 4);
        skillinit(13, rc, 8);
        skillinit(14, rc, 4);
        skillinit(15, rc, 8);
        skillinit(16, rc, 10);
        skillinit(17, rc, 4);
        skillinit(18, rc, 60);
        skillinit(106, rc, 1);
        skillinit(177, rc, 3);
        skillinit(178, rc, 2);
        s(1) = u8"HD|N_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"bat")
    {
        cdata[rc].melee_attack_type = 3;
        cdata[rc].dv_correction_value = 320;
        skillinit(2, rc, 10);
        skillinit(3, rc, 80);
        skillinit(10, rc, 3);
        skillinit(11, rc, 5);
        skillinit(12, rc, 9);
        skillinit(13, rc, 9);
        skillinit(14, rc, 4);
        skillinit(15, rc, 3);
        skillinit(16, rc, 6);
        skillinit(17, rc, 2);
        skillinit(18, rc, 140);
        skillinit(106, rc, 2);
        skillinit(187, rc, 3);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"ent")
    {
        skillinit(2, rc, 170);
        skillinit(3, rc, 80);
        skillinit(10, rc, 9);
        skillinit(11, rc, 12);
        skillinit(12, rc, 4);
        skillinit(13, rc, 6);
        skillinit(14, rc, 2);
        skillinit(15, rc, 3);
        skillinit(16, rc, 6);
        skillinit(17, rc, 2);
        skillinit(18, rc, 50);
        skillinit(106, rc, 3);
        skillinit(154, rc, 2);
        skillinit(176, rc, 4);
        s(1) = u8"HA|R_|R_|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"lich")
    {
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 190;
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 80);
        skillinit(3, rc, 140);
        skillinit(10, rc, 5);
        skillinit(11, rc, 8);
        skillinit(12, rc, 7);
        skillinit(13, rc, 10);
        skillinit(14, rc, 10);
        skillinit(15, rc, 13);
        skillinit(16, rc, 15);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 3);
        skillinit(155, rc, 5);
        skillinit(174, rc, 3);
        skillinit(172, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"hound")
    {
        cdata[rc].melee_attack_type = 3;
        cdata[rc].dv_correction_value = 120;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 9);
        skillinit(12, rc, 11);
        skillinit(13, rc, 10);
        skillinit(14, rc, 5);
        skillinit(15, rc, 4);
        skillinit(16, rc, 3);
        skillinit(17, rc, 3);
        skillinit(18, rc, 90);
        skillinit(106, rc, 2);
        skillinit(159, rc, 4);
        skillinit(183, rc, 2);
        s(1) = u8"HD|N_|BD|BK|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"ghost")
    {
        cdata[rc].melee_attack_type = 6;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 160;
        skillinit(2, rc, 60);
        skillinit(3, rc, 80);
        skillinit(10, rc, 4);
        skillinit(11, rc, 8);
        skillinit(12, rc, 6);
        skillinit(13, rc, 14);
        skillinit(14, rc, 7);
        skillinit(15, rc, 6);
        skillinit(16, rc, 11);
        skillinit(17, rc, 11);
        skillinit(18, rc, 60);
        skillinit(106, rc, 2);
        skillinit(164, rc, 4);
        skillinit(174, rc, 2);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"spirit")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 9);
        skillinit(12, rc, 5);
        skillinit(13, rc, 7);
        skillinit(14, rc, 8);
        skillinit(15, rc, 10);
        skillinit(16, rc, 13);
        skillinit(17, rc, 4);
        skillinit(18, rc, 60);
        skillinit(106, rc, 2);
        skillinit(172, rc, 3);
        skillinit(188, rc, 2);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"eye")
    {
        cdata[rc].melee_attack_type = 4;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 3);
        skillinit(11, rc, 9);
        skillinit(12, rc, 4);
        skillinit(13, rc, 6);
        skillinit(14, rc, 4);
        skillinit(15, rc, 7);
        skillinit(16, rc, 10);
        skillinit(17, rc, 4);
        skillinit(18, rc, 25);
        skillinit(106, rc, 2);
        skillinit(159, rc, 3);
        skillinit(161, rc, 3);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"wyvern")
    {
        cdata[rc].melee_attack_type = 1;
        skillinit(2, rc, 190);
        skillinit(3, rc, 80);
        skillinit(10, rc, 11);
        skillinit(11, rc, 13);
        skillinit(12, rc, 8);
        skillinit(13, rc, 9);
        skillinit(14, rc, 5);
        skillinit(15, rc, 7);
        skillinit(16, rc, 8);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 3);
        skillinit(150, rc, 3);
        skillinit(182, rc, 3);
        s(1) = u8"N_|BD|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"wasp")
    {
        cdata[rc].melee_attack_type = 5;
        cdata[rc].dv_correction_value = 220;
        skillinit(2, rc, 50);
        skillinit(3, rc, 80);
        skillinit(10, rc, 7);
        skillinit(11, rc, 6);
        skillinit(12, rc, 13);
        skillinit(13, rc, 11);
        skillinit(14, rc, 4);
        skillinit(15, rc, 6);
        skillinit(16, rc, 3);
        skillinit(17, rc, 2);
        skillinit(18, rc, 100);
        skillinit(106, rc, 2);
        skillinit(187, rc, 2);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"giant")
    {
        skillinit(2, rc, 200);
        skillinit(3, rc, 80);
        skillinit(10, rc, 12);
        skillinit(11, rc, 14);
        skillinit(12, rc, 9);
        skillinit(13, rc, 4);
        skillinit(14, rc, 8);
        skillinit(15, rc, 5);
        skillinit(16, rc, 6);
        skillinit(17, rc, 3);
        skillinit(18, rc, 60);
        skillinit(106, rc, 4);
        skillinit(161, rc, 3);
        skillinit(174, rc, 2);
        skillinit(176, rc, 3);
        s(1) = u8"BD|BK|HA|HA|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"imp")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].dv_correction_value = 200;
        skillinit(2, rc, 70);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 6);
        skillinit(12, rc, 8);
        skillinit(13, rc, 8);
        skillinit(14, rc, 8);
        skillinit(15, rc, 4);
        skillinit(16, rc, 7);
        skillinit(17, rc, 3);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(165, rc, 3);
        skillinit(188, rc, 3);
        s(1) = u8"N_|BD|HA|HA|R_|R_R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"hand")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 9);
        skillinit(12, rc, 9);
        skillinit(13, rc, 4);
        skillinit(14, rc, 8);
        skillinit(15, rc, 6);
        skillinit(16, rc, 5);
        skillinit(17, rc, 2);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(186, rc, 4);
        s(1) = u8"HA|HA|R_|R_|A_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"snake")
    {
        cdata[rc].melee_attack_type = 3;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 6);
        skillinit(11, rc, 9);
        skillinit(12, rc, 8);
        skillinit(13, rc, 10);
        skillinit(14, rc, 4);
        skillinit(15, rc, 6);
        skillinit(16, rc, 6);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(157, rc, 4);
        s(1) = u8"BD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"drake")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].pv_correction_value = 120;
        skillinit(2, rc, 160);
        skillinit(3, rc, 80);
        skillinit(10, rc, 11);
        skillinit(11, rc, 12);
        skillinit(12, rc, 11);
        skillinit(13, rc, 8);
        skillinit(14, rc, 6);
        skillinit(15, rc, 9);
        skillinit(16, rc, 8);
        skillinit(17, rc, 7);
        skillinit(18, rc, 85);
        skillinit(106, rc, 3);
        skillinit(182, rc, 3);
        skillinit(185, rc, 2);
        s(1) = u8"N_|BD|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"goblin")
    {
        skillinit(2, rc, 110);
        skillinit(3, rc, 90);
        skillinit(10, rc, 8);
        skillinit(11, rc, 8);
        skillinit(12, rc, 5);
        skillinit(13, rc, 5);
        skillinit(14, rc, 8);
        skillinit(15, rc, 7);
        skillinit(16, rc, 7);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(154, rc, 5);
        skillinit(185, rc, 2);
        skillinit(163, rc, 2);
        skillinit(186, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"bear")
    {
        cdata[rc].melee_attack_type = 1;
        skillinit(2, rc, 160);
        skillinit(3, rc, 80);
        skillinit(10, rc, 9);
        skillinit(11, rc, 10);
        skillinit(12, rc, 5);
        skillinit(13, rc, 6);
        skillinit(14, rc, 6);
        skillinit(15, rc, 6);
        skillinit(16, rc, 3);
        skillinit(17, rc, 5);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(154, rc, 3);
        skillinit(183, rc, 2);
        skillinit(186, rc, 3);
        s(1) = u8"HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"armor")
    {
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 300;
        skillinit(2, rc, 40);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 4);
        skillinit(12, rc, 7);
        skillinit(13, rc, 5);
        skillinit(14, rc, 6);
        skillinit(15, rc, 6);
        skillinit(16, rc, 7);
        skillinit(17, rc, 4);
        skillinit(18, rc, 50);
        skillinit(106, rc, 2);
        skillinit(158, rc, 3);
        skillinit(174, rc, 2);
        s(1) = u8"HD|N_|BD|BK|HA|HA|A_|W_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"medusa")
    {
        cdata[rc].dv_correction_value = 140;
        skillinit(2, rc, 100);
        skillinit(3, rc, 110);
        skillinit(10, rc, 7);
        skillinit(11, rc, 6);
        skillinit(12, rc, 8);
        skillinit(13, rc, 7);
        skillinit(14, rc, 7);
        skillinit(15, rc, 9);
        skillinit(16, rc, 11);
        skillinit(17, rc, 5);
        skillinit(18, rc, 70);
        skillinit(106, rc, 3);
        skillinit(164, rc, 3);
        skillinit(188, rc, 3);
        s(1) = u8"BD|HA|HA|R_|R_|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"cupid")
    {
        cdata[rc].dv_correction_value = 200;
        skillinit(2, rc, 80);
        skillinit(3, rc, 130);
        skillinit(10, rc, 6);
        skillinit(11, rc, 7);
        skillinit(12, rc, 9);
        skillinit(13, rc, 8);
        skillinit(14, rc, 8);
        skillinit(15, rc, 7);
        skillinit(16, rc, 12);
        skillinit(17, rc, 8);
        skillinit(18, rc, 80);
        skillinit(106, rc, 2);
        skillinit(150, rc, 4);
        skillinit(188, rc, 3);
        s(1) = u8"N_|BD|HA|HA|R_|R_|A_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"phantom")
    {
        cbitmod(983, rc, 1);
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].pv_correction_value = 200;
        skillinit(2, rc, 60);
        skillinit(3, rc, 90);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 8);
        skillinit(13, rc, 7);
        skillinit(14, rc, 6);
        skillinit(15, rc, 6);
        skillinit(16, rc, 9);
        skillinit(17, rc, 4);
        skillinit(18, rc, 85);
        skillinit(106, rc, 2);
        skillinit(157, rc, 3);
        skillinit(175, rc, 3);
        s(1) = u8"N_|BD|HA|HA|R_|R_|A_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"harpy")
    {
        cdata[rc].dv_correction_value = 150;
        skillinit(2, rc, 90);
        skillinit(3, rc, 100);
        skillinit(10, rc, 8);
        skillinit(11, rc, 6);
        skillinit(12, rc, 9);
        skillinit(13, rc, 9);
        skillinit(14, rc, 6);
        skillinit(15, rc, 8);
        skillinit(16, rc, 9);
        skillinit(17, rc, 4);
        skillinit(18, rc, 80);
        skillinit(106, rc, 2);
        skillinit(164, rc, 3);
        skillinit(174, rc, 2);
        s(1) = u8"N_|HA|HA|R_|R_|A_|L_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"dragon")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].pv_correction_value = 120;
        skillinit(2, rc, 220);
        skillinit(3, rc, 80);
        skillinit(10, rc, 13);
        skillinit(11, rc, 15);
        skillinit(12, rc, 10);
        skillinit(13, rc, 9);
        skillinit(14, rc, 10);
        skillinit(15, rc, 9);
        skillinit(16, rc, 13);
        skillinit(17, rc, 9);
        skillinit(18, rc, 70);
        skillinit(106, rc, 3);
        skillinit(182, rc, 3);
        skillinit(179, rc, 3);
        s(1) = u8"N_|BD|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"dinosaur")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].pv_correction_value = 120;
        skillinit(2, rc, 140);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 10);
        skillinit(12, rc, 6);
        skillinit(13, rc, 5);
        skillinit(14, rc, 4);
        skillinit(15, rc, 5);
        skillinit(16, rc, 6);
        skillinit(17, rc, 5);
        skillinit(18, rc, 120);
        skillinit(106, rc, 4);
        skillinit(182, rc, 3);
        skillinit(187, rc, 2);
        s(1) = u8"N_|BD|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"cerberus")
    {
        cdata[rc].melee_attack_type = 1;
        skillinit(2, rc, 160);
        skillinit(3, rc, 80);
        skillinit(10, rc, 11);
        skillinit(11, rc, 9);
        skillinit(12, rc, 10);
        skillinit(13, rc, 11);
        skillinit(14, rc, 6);
        skillinit(15, rc, 8);
        skillinit(16, rc, 7);
        skillinit(17, rc, 4);
        skillinit(18, rc, 85);
        skillinit(106, rc, 3);
        skillinit(159, rc, 3);
        skillinit(177, rc, 3);
        s(1) = u8"HD|N_|BD|BK|A_|L_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"spider")
    {
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 1;
        cdata[rc].dv_correction_value = 170;
        skillinit(2, rc, 50);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 5);
        skillinit(12, rc, 9);
        skillinit(13, rc, 12);
        skillinit(14, rc, 5);
        skillinit(15, rc, 6);
        skillinit(16, rc, 8);
        skillinit(17, rc, 4);
        skillinit(18, rc, 120);
        skillinit(106, rc, 2);
        skillinit(157, rc, 3);
        skillinit(161, rc, 5);
        s(1) = u8"R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"golem")
    {
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 140;
        skillinit(2, rc, 150);
        skillinit(3, rc, 70);
        skillinit(10, rc, 10);
        skillinit(11, rc, 14);
        skillinit(12, rc, 4);
        skillinit(13, rc, 5);
        skillinit(14, rc, 4);
        skillinit(15, rc, 9);
        skillinit(16, rc, 6);
        skillinit(17, rc, 3);
        skillinit(18, rc, 45);
        skillinit(106, rc, 4);
        skillinit(153, rc, 5);
        skillinit(163, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"rock")
    {
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 200;
        skillinit(2, rc, 40);
        skillinit(3, rc, 50);
        skillinit(10, rc, 8);
        skillinit(11, rc, 22);
        skillinit(12, rc, 3);
        skillinit(13, rc, 8);
        skillinit(14, rc, 2);
        skillinit(15, rc, 3);
        skillinit(16, rc, 4);
        skillinit(17, rc, 10);
        skillinit(18, rc, 70);
        skillinit(106, rc, 1);
        skillinit(153, rc, 3);
        skillinit(163, rc, 3);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"crab")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 60);
        skillinit(3, rc, 80);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 7);
        skillinit(13, rc, 7);
        skillinit(14, rc, 3);
        skillinit(15, rc, 4);
        skillinit(16, rc, 4);
        skillinit(17, rc, 3);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(175, rc, 2);
        skillinit(168, rc, 3);
        s(1) = u8"BK|HA|HA|R_|R_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"skeleton")
    {
        cbitmod(983, rc, 1);
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 8);
        skillinit(11, rc, 7);
        skillinit(12, rc, 8);
        skillinit(13, rc, 6);
        skillinit(14, rc, 4);
        skillinit(15, rc, 6);
        skillinit(16, rc, 9);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(100, rc, 3);
        skillinit(168, rc, 2);
        skillinit(158, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"piece")
    {
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 120);
        skillinit(3, rc, 80);
        skillinit(10, rc, 9);
        skillinit(11, rc, 7);
        skillinit(12, rc, 6);
        skillinit(13, rc, 4);
        skillinit(14, rc, 5);
        skillinit(15, rc, 9);
        skillinit(16, rc, 10);
        skillinit(17, rc, 4);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(164, rc, 2);
        skillinit(150, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"cat")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 4;
        skillinit(2, rc, 120);
        skillinit(3, rc, 120);
        skillinit(10, rc, 6);
        skillinit(11, rc, 7);
        skillinit(12, rc, 7);
        skillinit(13, rc, 7);
        skillinit(14, rc, 4);
        skillinit(15, rc, 4);
        skillinit(16, rc, 7);
        skillinit(17, rc, 12);
        skillinit(18, rc, 110);
        skillinit(106, rc, 2);
        skillinit(183, rc, 2);
        skillinit(187, rc, 3);
        skillinit(173, rc, 2);
        s(1) = u8"HD|N_|BD|BK|HA|L_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"dog")
    {
        cdata[rc].melee_attack_type = 3;
        skillinit(2, rc, 120);
        skillinit(3, rc, 80);
        skillinit(10, rc, 7);
        skillinit(11, rc, 8);
        skillinit(12, rc, 7);
        skillinit(13, rc, 7);
        skillinit(14, rc, 8);
        skillinit(15, rc, 7);
        skillinit(16, rc, 7);
        skillinit(17, rc, 7);
        skillinit(18, rc, 85);
        skillinit(106, rc, 2);
        skillinit(153, rc, 3);
        skillinit(183, rc, 2);
        skillinit(159, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|L_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"roran")
    {
        cdata[rc].dv_correction_value = 150;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 4);
        skillinit(11, rc, 6);
        skillinit(12, rc, 5);
        skillinit(13, rc, 7);
        skillinit(14, rc, 7);
        skillinit(15, rc, 6);
        skillinit(16, rc, 7);
        skillinit(17, rc, 10);
        skillinit(18, rc, 95);
        skillinit(106, rc, 2);
        skillinit(155, rc, 3);
        skillinit(150, rc, 4);
        skillinit(160, rc, 2);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"rat")
    {
        cdata[rc].melee_attack_type = 3;
        skillinit(2, rc, 80);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 4);
        skillinit(12, rc, 8);
        skillinit(13, rc, 10);
        skillinit(14, rc, 3);
        skillinit(15, rc, 3);
        skillinit(16, rc, 2);
        skillinit(17, rc, 3);
        skillinit(18, rc, 75);
        skillinit(106, rc, 1);
        skillinit(157, rc, 3);
        skillinit(161, rc, 2);
        s(1) = u8"BK|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"shell")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].pv_correction_value = 340;
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 7);
        skillinit(11, rc, 7);
        skillinit(12, rc, 5);
        skillinit(13, rc, 4);
        skillinit(14, rc, 4);
        skillinit(15, rc, 5);
        skillinit(16, rc, 3);
        skillinit(17, rc, 4);
        skillinit(18, rc, 20);
        skillinit(106, rc, 1);
        skillinit(155, rc, 3);
        skillinit(162, rc, 3);
        s(1) = u8"L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"catgod")
    {
        cdata[rc].melee_attack_type = 1;
        cdata[rc].dv_correction_value = 250;
        skillinit(2, rc, 120);
        skillinit(3, rc, 80);
        skillinit(10, rc, 12);
        skillinit(11, rc, 13);
        skillinit(12, rc, 21);
        skillinit(13, rc, 28);
        skillinit(14, rc, 8);
        skillinit(15, rc, 13);
        skillinit(16, rc, 12);
        skillinit(17, rc, 25);
        skillinit(18, rc, 500);
        skillinit(106, rc, 3);
        skillinit(173, rc, 3);
        skillinit(187, rc, 3);
        skillinit(186, rc, 2);
        s(1) = u8"HD|N_|BD|HA|R_|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"machinegod")
    {
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 200);
        skillinit(3, rc, 80);
        skillinit(10, rc, 15);
        skillinit(11, rc, 14);
        skillinit(12, rc, 11);
        skillinit(13, rc, 24);
        skillinit(14, rc, 12);
        skillinit(15, rc, 15);
        skillinit(16, rc, 8);
        skillinit(17, rc, 10);
        skillinit(18, rc, 70);
        skillinit(106, rc, 5);
        skillinit(110, rc, 30);
        s(1) = u8"HD|BD|BK|HA|HA|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"undeadgod")
    {
        skillinit(2, rc, 150);
        skillinit(3, rc, 500);
        skillinit(10, rc, 10);
        skillinit(11, rc, 13);
        skillinit(12, rc, 14);
        skillinit(13, rc, 18);
        skillinit(14, rc, 16);
        skillinit(15, rc, 18);
        skillinit(16, rc, 28);
        skillinit(17, rc, 7);
        skillinit(18, rc, 110);
        skillinit(106, rc, 4);
        skillinit(188, rc, 3);
        skillinit(164, rc, 5);
        s(1) = u8"N_|BD|BK|HA|HA|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"machine")
    {
        cdata[rc].special_attack_type = 6;
        cbitmod(983, rc, 1);
        skillinit(2, rc, 100);
        skillinit(3, rc, 80);
        skillinit(10, rc, 7);
        skillinit(11, rc, 10);
        skillinit(12, rc, 7);
        skillinit(13, rc, 9);
        skillinit(14, rc, 5);
        skillinit(15, rc, 12);
        skillinit(16, rc, 5);
        skillinit(17, rc, 6);
        skillinit(18, rc, 65);
        skillinit(106, rc, 2);
        skillinit(155, rc, 3);
        skillinit(158, rc, 3);
        skillinit(175, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"wisp")
    {
        cdata[rc].melee_attack_type = 4;
        skillinit(2, rc, 150);
        skillinit(3, rc, 150);
        skillinit(10, rc, 5);
        skillinit(11, rc, 10);
        skillinit(12, rc, 10);
        skillinit(13, rc, 20);
        skillinit(14, rc, 10);
        skillinit(15, rc, 15);
        skillinit(16, rc, 15);
        skillinit(17, rc, 4);
        skillinit(18, rc, 35);
        skillinit(106, rc, 1);
        skillinit(188, rc, 3);
        skillinit(164, rc, 5);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"chicken")
    {
        cdata[rc].melee_attack_type = 3;
        skillinit(2, rc, 80);
        skillinit(3, rc, 80);
        skillinit(10, rc, 5);
        skillinit(11, rc, 8);
        skillinit(12, rc, 10);
        skillinit(13, rc, 11);
        skillinit(14, rc, 4);
        skillinit(15, rc, 4);
        skillinit(16, rc, 5);
        skillinit(17, rc, 7);
        skillinit(18, rc, 60);
        skillinit(106, rc, 1);
        skillinit(161, rc, 3);
        skillinit(155, rc, 3);
        s(1) = u8"HD|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"stalker")
    {
        cdata[rc].melee_attack_type = 1;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 130;
        skillinit(2, rc, 120);
        skillinit(3, rc, 140);
        skillinit(10, rc, 9);
        skillinit(11, rc, 8);
        skillinit(12, rc, 5);
        skillinit(13, rc, 11);
        skillinit(14, rc, 7);
        skillinit(15, rc, 6);
        skillinit(16, rc, 9);
        skillinit(17, rc, 3);
        skillinit(18, rc, 100);
        skillinit(106, rc, 2);
        skillinit(186, rc, 3);
        skillinit(157, rc, 4);
        s(1) = u8"N_|HA|HA|R_|R_|A_||";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"catsister")
    {
        cdata[rc].melee_attack_type = 1;
        skillinit(2, rc, 30);
        skillinit(3, rc, 100);
        skillinit(10, rc, 7);
        skillinit(11, rc, 5);
        skillinit(12, rc, 13);
        skillinit(13, rc, 15);
        skillinit(14, rc, 8);
        skillinit(15, rc, 10);
        skillinit(16, rc, 13);
        skillinit(17, rc, 22);
        skillinit(18, rc, 200);
        skillinit(106, rc, 4);
        skillinit(167, rc, 6);
        skillinit(152, rc, 4);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"mutant")
    {
        skillinit(2, rc, 100);
        skillinit(3, rc, 100);
        skillinit(10, rc, 9);
        skillinit(11, rc, 5);
        skillinit(12, rc, 5);
        skillinit(13, rc, 7);
        skillinit(14, rc, 7);
        skillinit(15, rc, 9);
        skillinit(16, rc, 7);
        skillinit(17, rc, 1);
        skillinit(18, rc, 70);
        skillinit(106, rc, 2);
        skillinit(164, rc, 3);
        skillinit(154, rc, 4);
        s(1) = u8"BD|HA|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"yeek")
    {
        skillinit(2, rc, 80);
        skillinit(3, rc, 90);
        skillinit(10, rc, 4);
        skillinit(11, rc, 7);
        skillinit(12, rc, 6);
        skillinit(13, rc, 7);
        skillinit(14, rc, 6);
        skillinit(15, rc, 4);
        skillinit(16, rc, 6);
        skillinit(17, rc, 6);
        skillinit(18, rc, 90);
        skillinit(106, rc, 1);
        skillinit(155, rc, 3);
        skillinit(156, rc, 4);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"yith")
    {
        cdata[rc].melee_attack_type = 6;
        cdata[rc].special_attack_type = 3;
        skillinit(2, rc, 150);
        skillinit(3, rc, 200);
        skillinit(10, rc, 13);
        skillinit(11, rc, 14);
        skillinit(12, rc, 9);
        skillinit(13, rc, 15);
        skillinit(14, rc, 6);
        skillinit(15, rc, 5);
        skillinit(16, rc, 11);
        skillinit(17, rc, 11);
        skillinit(18, rc, 70);
        skillinit(106, rc, 3);
        skillinit(188, rc, 4);
        skillinit(155, rc, 3);
        skillinit(181, rc, 4);
        s(1) = u8"HA|HA|HA|HA|R_|R_|R_|R_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"servant")
    {
        skillinit(2, rc, 90);
        skillinit(3, rc, 150);
        skillinit(10, rc, 6);
        skillinit(11, rc, 6);
        skillinit(12, rc, 6);
        skillinit(13, rc, 6);
        skillinit(14, rc, 6);
        skillinit(15, rc, 6);
        skillinit(16, rc, 6);
        skillinit(17, rc, 6);
        skillinit(18, rc, 100);
        skillinit(106, rc, 3);
        skillinit(152, rc, 3);
        skillinit(172, rc, 4);
        skillinit(156, rc, 3);
        skillinit(111, rc, 3);
        skillinit(166, rc, 4);
        skillinit(110, rc, 4);
        skillinit(167, rc, 3);
        s(1) = u8"HD|N_|BD|BK|HA|HA|R_|R_|A_|W_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"horse")
    {
        cdata[rc].melee_attack_type = 3;
        skillinit(2, rc, 150);
        skillinit(3, rc, 50);
        skillinit(10, rc, 9);
        skillinit(11, rc, 8);
        skillinit(12, rc, 4);
        skillinit(13, rc, 5);
        skillinit(14, rc, 4);
        skillinit(15, rc, 4);
        skillinit(16, rc, 3);
        skillinit(17, rc, 6);
        skillinit(18, rc, 125);
        skillinit(106, rc, 1);
        skillinit(154, rc, 4);
        s(1) = u8"BD|L_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"god")
    {
        cdata[rc].dv_correction_value = 300;
        cdata[rc].pv_correction_value = 200;
        skillinit(2, rc, 200);
        skillinit(3, rc, 100);
        skillinit(10, rc, 17);
        skillinit(11, rc, 13);
        skillinit(12, rc, 19);
        skillinit(13, rc, 17);
        skillinit(14, rc, 16);
        skillinit(15, rc, 25);
        skillinit(16, rc, 24);
        skillinit(17, rc, 21);
        skillinit(18, rc, 150);
        skillinit(106, rc, 6);
        skillinit(173, rc, 3);
        skillinit(187, rc, 3);
        skillinit(186, rc, 2);
        skillinit(110, rc, 8);
        skillinit(108, rc, 7);
        skillinit(166, rc, 7);
        skillinit(167, rc, 5);
        skillinit(152, rc, 7);
        s(1) = u8"HA|HA|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"quickling")
    {
        sdata(60, rc) = 500;
        cdata[rc].dv_correction_value = 550;
        skillinit(2, rc, 3);
        skillinit(3, rc, 40);
        skillinit(10, rc, 2);
        skillinit(11, rc, 4);
        skillinit(12, rc, 18);
        skillinit(13, rc, 16);
        skillinit(14, rc, 5);
        skillinit(15, rc, 8);
        skillinit(16, rc, 9);
        skillinit(17, rc, 7);
        skillinit(18, rc, 750);
        skillinit(106, rc, 1);
        skillinit(157, rc, 3);
        skillinit(173, rc, 7);
        skillinit(187, rc, 6);
        s(1) = u8"HD|BD|BK|HA|HA|R_|R_|A_|L_|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"metal")
    {
        cdata[rc].melee_attack_type = 3;
        sdata(60, rc) = 500;
        cdata[rc].dv_correction_value = 150;
        cdata[rc].pv_correction_value = 1000;
        skillinit(2, rc, 1);
        skillinit(3, rc, 100);
        skillinit(10, rc, 4);
        skillinit(11, rc, 1);
        skillinit(12, rc, 3);
        skillinit(13, rc, 32);
        skillinit(14, rc, 2);
        skillinit(15, rc, 4);
        skillinit(16, rc, 4);
        skillinit(17, rc, 16);
        skillinit(18, rc, 640);
        skillinit(106, rc, 1);
        skillinit(164, rc, 4);
        skillinit(187, rc, 6);
        s(1) = u8"HD|BD|BK|";
        initialize_body_parts_by_string();
    }
    else if (dbidn == u8"bike")
    {
        cdata[rc].special_attack_type = 6;
        cbitmod(983, rc, 1);
        cdata[rc].pv_correction_value = 150;
        skillinit(2, rc, 170);
        skillinit(3, rc, 60);
        skillinit(10, rc, 11);
        skillinit(11, rc, 13);
        skillinit(12, rc, 4);
        skillinit(13, rc, 3);
        skillinit(14, rc, 4);
        skillinit(15, rc, 5);
        skillinit(16, rc, 3);
        skillinit(17, rc, 11);
        skillinit(18, rc, 155);
        skillinit(106, rc, 2);
        skillinit(173, rc, 11);
        skillinit(158, rc, 3);
        skillinit(175, rc, 3);
        s(1) = u8"HD|BD|BK|HA|HA|W_|L_|L_";
        initialize_body_parts_by_string();
    }

    return 0;
}



} // namespace elona
