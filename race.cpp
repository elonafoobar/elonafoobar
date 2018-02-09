#include "race.hpp"
#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "elona.hpp"
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

    FIELD_S(name_en);
    FIELD_S(name_jp);
    FIELD_S(description_en);
    FIELD_S(description_jp);

    FIELD_I(male_image);
    FIELD_I(female_image);
    FIELD_I(dbspec9);

#undef FIELD_I
#undef FIELD_S

    storage_ptr->emplace(
        id,
        race_data{
            id,
            name_en,
            name_jp,
            description_en,
            description_jp,
            male_image,
            female_image,
            dbspec9,
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



#define RACE(name) \
    do \
    { \
        listn(1, listmax) = (name); \
        list(0, listmax) = int(is_extra_race); \
        ++listmax; \
    } while (0)


void get_race_list(bool is_extra_race)
{
    if (is_extra_race)
    {
        RACE(u8"kobolt");
        RACE(u8"orc");
        RACE(u8"troll");
        RACE(u8"lizardman");
        RACE(u8"minotaur");
        RACE(u8"norland");
        RACE(u8"asura");
        RACE(u8"slime");
        RACE(u8"wolf");
        RACE(u8"zombie");
        RACE(u8"rabbit");
        RACE(u8"sheep");
        RACE(u8"frog");
        RACE(u8"centipede");
        RACE(u8"mandrake");
        RACE(u8"beetle");
        RACE(u8"mushroom");
        RACE(u8"bat");
        RACE(u8"ent");
        RACE(u8"hound");
        RACE(u8"ghost");
        RACE(u8"spirit");
        RACE(u8"eye");
        RACE(u8"wyvern");
        RACE(u8"wasp");
        RACE(u8"giant");
        RACE(u8"imp");
        RACE(u8"hand");
        RACE(u8"snake");
        RACE(u8"drake");
        RACE(u8"bear");
        RACE(u8"armor");
        RACE(u8"medusa");
        RACE(u8"cupid");
        RACE(u8"phantom");
        RACE(u8"harpy");
        RACE(u8"dragon");
        RACE(u8"dinosaur");
        RACE(u8"cerberus");
        RACE(u8"spider");
        RACE(u8"rock");
        RACE(u8"crab");
        RACE(u8"skeleton");
        RACE(u8"piece");
        RACE(u8"cat");
        RACE(u8"dog");
        RACE(u8"roran");
        RACE(u8"rat");
        RACE(u8"shell");
        RACE(u8"catgod");
        RACE(u8"machinegod");
        RACE(u8"undeadgod");
        RACE(u8"machine");
        RACE(u8"wisp");
        RACE(u8"chicken");
        RACE(u8"stalker");
        RACE(u8"catsister");
        RACE(u8"yeek");
        RACE(u8"yith");
        RACE(u8"servant");
        RACE(u8"horse");
        RACE(u8"god");
        RACE(u8"quickling");
        RACE(u8"metal");
        RACE(u8"bike");
    }
    else
    {
        RACE(u8"yerles");
        RACE(u8"eulderna");
        RACE(u8"fairy");
        RACE(u8"dwarf");
        RACE(u8"juere");
        RACE(u8"elea");
        RACE(u8"snail");
        RACE(u8"lich");
        RACE(u8"goblin");
        RACE(u8"golem");
        RACE(u8"mutant");
    }
}



#define DBMODE16(s, ret) \
    do \
    { \
        if (dbspec == s) \
            return ret; \
    } while (0)




int access_race_info(int dbmode, const std::string& dbidn)
{
    auto info = the_race_db[dbidn];
    if (!info)
        return 0;

    switch (dbmode)
    {
    case 2:
        racename = lang(info->name_jp, info->name_en);
        cpicref = info->male_image;
        return 0;
    case 3: break;
    case 11:
        buff = lang(info->description_jp, info->description_en);
        ref1 = info->male_image;
        ref2 = info->female_image;
        return 0;
    case 16:
        switch (dbspec)
        {
        case 9: return info->dbspec9;
        default: assert(0);
        }
    default: assert(0);
    }


    if (false)
    {
    }
    else if (dbidn == u8"kobolt")
    {
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 1;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 150;
        if (rnd(100) < 50)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 171;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 2;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 150;
        if (rnd(100) < 51)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 165;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 3;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 400;
        if (rnd(100) < 51)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 391;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 4;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 240;
        if (rnd(100) < 51)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 397;
        cdata[rc].dv_correction_value = 120;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 5;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 350;
        if (rnd(100) < 51)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 398;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 6;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(20) + 15);
        cdata[rc].height = 165;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 1;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 2;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 7;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(20) + 15);
        cdata[rc].height = 170;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 1;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 2;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 8;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(20) + 16);
        cdata[rc].height = 175;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 5;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 6;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 9;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(100) + 5);
        cdata[rc].height = 50;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 390;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 390;
        }
        sdata(60, rc) = 200;
        sdata(53, rc) = 200;
        sdata(58, rc) = 200;
        sdata(56, rc) = 200;
        sdata(54, rc) = 200;
        sdata(57, rc) = 200;
        sdata(59, rc) = 200;
        cdata[rc].dv_correction_value = 250;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 10;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(20) + 15);
        cdata[rc].height = 220;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 405;
        cdata[rc].dv_correction_value = 200;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 11;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 2;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 1);
        cdata[rc].height = 40;
        if (rnd(100) < 54)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 168;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 12;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 2);
        cdata[rc].height = 100;
        if (rnd(100) < 55)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 254;
        cdata[rc].dv_correction_value = 140;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 13;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(60) + 20);
        cdata[rc].height = 100;
        if (rnd(100) < 56)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 66;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 14;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 165;
        if (rnd(100) < 50)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 9;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 10;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 15;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(200) + 10);
        cdata[rc].height = 160;
        if (rnd(100) < 50)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 167;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 16;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(200) + 10);
        cdata[rc].height = 180;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 3;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 4;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 17;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(5) + 2);
        cdata[rc].height = 40;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 169;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 18;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(5) + 2);
        cdata[rc].height = 150;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 170;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 19;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(5) + 2);
        cdata[rc].height = 10;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 172;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 20;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 10;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 173;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 21;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 8;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 174;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 22;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 25;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 175;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 23;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 10;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 176;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 24;
        cdata[rc].melee_attack_type = 7;
        cdata[rc].special_attack_type = 5;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 20;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 177;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 25;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 70;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 200;
        cdata[rc].dv_correction_value = 320;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 26;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1500;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 201;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 27;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 180;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 202;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 28;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 160;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 203;
        cdata[rc].dv_correction_value = 120;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 29;
        cdata[rc].melee_attack_type = 6;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 180;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 205;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 160;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 30;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 100;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 206;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 31;
        cdata[rc].melee_attack_type = 4;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 40;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 207;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 32;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1600;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 235;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 33;
        cdata[rc].melee_attack_type = 5;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 80;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 210;
        cdata[rc].dv_correction_value = 220;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 34;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1800;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 232;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 35;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 80;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 212;
        cdata[rc].dv_correction_value = 200;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 36;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 70;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 213;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 37;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 50;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 216;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 38;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1400;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 233;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 39;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 140;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 220;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 40;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 280;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 222;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 41;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 550;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 223;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 42;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 160;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 224;
        cdata[rc].dv_correction_value = 140;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 43;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 120;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 225;
        cdata[rc].dv_correction_value = 200;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 44;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 450;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 226;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 45;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 140;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 227;
        cdata[rc].dv_correction_value = 150;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 46;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 2400;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 228;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 47;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 2000;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 389;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 48;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1200;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 229;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 49;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 1;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 60;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 230;
        cdata[rc].dv_correction_value = 170;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 50;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 700;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 231;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 51;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 500;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 386;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 52;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 50;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 237;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 53;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 160;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 241;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 54;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 750;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 244;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 55;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 4;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 60;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 253;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 56;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 80;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 254;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 57;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 150;
        if (rnd(100) < 0)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 4;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 4;
        }
        cdata[rc].dv_correction_value = 150;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 58;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 30;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 255;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 59;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 120;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 256;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 60;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 120;
        if (rnd(100) < 0)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 199;
        cdata[rc].dv_correction_value = 250;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 61;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 3000;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 349;
        cdata[rc].dv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 62;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 1500;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 350;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 63;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 6;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 240;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 270;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 64;
        cdata[rc].melee_attack_type = 4;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 40;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 272;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 65;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 40;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 274;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 66;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 180;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 276;
        sdata(53, rc) = 500;
        sdata(58, rc) = 500;
        sdata(56, rc) = 500;
        sdata(50, rc) = 80;
        cdata[rc].dv_correction_value = 130;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 67;
        cdata[rc].melee_attack_type = 1;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (10 + rnd(4));
        cdata[rc].height = 140;
        if (rnd(100) < 0)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 354;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 68;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(50) + 25);
        cdata[rc].height = 180;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 3;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 4;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 69;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(30) + 15);
        cdata[rc].height = 90;
        if (rnd(100) < 50)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 378;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 70;
        cdata[rc].melee_attack_type = 6;
        cdata[rc].special_attack_type = 3;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 950;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 429;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 71;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(200) + 100);
        cdata[rc].height = 165;
        if (rnd(100) < 52)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 1;
        if (cdata[rc].sex == 1)
        {
            cdata[rc].image = 2;
        }
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 72;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 250;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 262;
        cdata[rc].dv_correction_value = 100;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 73;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - 999999;
        cdata[rc].height = 180;
        if (rnd(100) < 0)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 393;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 74;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 25;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 281;
        sdata(60, rc) = 500;
        cdata[rc].dv_correction_value = 550;
        cdata[rc].pv_correction_value = 100;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 75;
        cdata[rc].melee_attack_type = 3;
        cdata[rc].special_attack_type = 0;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 12;
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 252;
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
        cdatan(2, rc) = dbidn;
        cdata[rc]._158 = 76;
        cdata[rc].melee_attack_type = 0;
        cdata[rc].special_attack_type = 6;
        cdata[rc].birth_year = gdata_year - (rnd(10) + 10);
        cdata[rc].height = 240;
        cbitmod(983, rc, 1);
        if (rnd(100) < 53)
        {
            cdata[rc].sex = 0;
        }
        else
        {
            cdata[rc].sex = 1;
        }
        if (mode == 1)
        {
            cdata[rc].sex = cmsex;
        }
        cdata[rc].image = 471;
        cdata[rc].dv_correction_value = 100;
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
