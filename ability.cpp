#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "i18n.hpp"
#include "range.hpp"
#include "variables.hpp"

using namespace elona;



namespace elona
{


ability_db the_ability_db;
skill_data sdata;


void ability_db::define(lua_State* L)
{
    const char* id = luaL_checkstring(L, -2);
    if (!id)
        throw std::runtime_error(u8"Error: fail to load ability data");

    ELONA_CAT_DB_FIELD_INTEGER(related_basic_attribute, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref1, 0);
    ELONA_CAT_DB_FIELD_INTEGER(cost, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref3, 0);
    ELONA_CAT_DB_FIELD_INTEGER(sdataref4, 0);

    storage.emplace(
        std::stoi(id), // TODO
        ability_data{
            std::stoi(id),
            related_basic_attribute,
            sdataref1,
            cost,
            sdataref3,
            sdataref4,
        });
}


skill_data::skill_data()
    : storage(ELONA_MAX_CHARACTERS, std::vector<ability>(600))
{
}



void skill_data::clear(int cc)
{
    range::fill(storage[cc], ability{});
}



void skill_data::copy(int tc, int cc)
{
    range::copy(storage[cc], std::begin(storage[tc]));
}

void skillinit(int id, int cc, int initial_level)
{
    int potential = 0;
    int original_level = sdata.get(id, cc).original_level;
    if (id >= 100)
    {
        potential = initial_level * 5;
        if (original_level == 0)
        {
            potential += 100;
        }
        else
        {
            potential += 50;
        }
    }
    else
    {
        potential = initial_level * 20;
        if (potential > 400)
        {
            potential = 400;
        }
    }
    int level = 0;
    if (id == 18)
    {
        level = initial_level * (100 + cdata[cc].level * 2) / 100;
    }
    else
    {
        level = potential * potential * cdata[cc].level / 45000 + initial_level
            + cdata[cc].level / 3;
    }
    if (cdata[cc].level > 1)
    {
        potential = std::exp(std::log(0.9) * cdata[cc].level) * potential;
    }
    if (potential < 1)
    {
        potential = 1;
    }
    if (id == 2 || id == 19 || id == 3)
    {
        level = initial_level;
        potential = 100;
    }
    if (original_level + level > 2000)
    {
        level = 2000 - original_level;
    }
    sdata.get(id, cc).original_level += clamp(level, 0, 2000);
    sdata.get(id, cc).potential += potential;
}



void label_1512(int cc)
{
    for (int cnt = 50; cnt < 61; ++cnt)
    {
        p = cdata[cc].level * 4 + 96;
        if (p > 300)
        {
            p = 300;
        }
        if (sdata(cnt, cc) != 0)
        {
            if (sdata(cnt, cc) < 100 || sdata(cnt, cc) >= 500)
            {
                p = sdata(cnt, cc);
            }
            else
            {
                p += sdata(cnt, cc);
            }
        }
        if ((cnt == 60 && p < 500) || cc == 0)
        {
            p = 100;
        }
        sdata.get(cnt, cc).original_level = clamp(p(0), 1, 2000);
        sdata.get(cnt, cc).experience = 0;
        sdata.get(cnt, cc).potential = 0;
    }

    skillinit(100, cc, 4);
    skillinit(101, cc, 4);
    skillinit(103, cc, 4);
    skillinit(102, cc, 4);
    skillinit(104, cc, 4);
    skillinit(105, cc, 4);
    skillinit(107, cc, 4);
    skillinit(108, cc, 4);
    skillinit(111, cc, 4);
    skillinit(109, cc, 4);
    skillinit(173, cc, 4);
    skillinit(154, cc, 4);
    skillinit(155, cc, 4);
    skillinit(106, cc, 4);
    skillinit(157, cc, 4);
    skillinit(181, cc, 4);
    skillinit(171, cc, 4);
    skillinit(170, cc, 4);
    skillinit(169, cc, 4);
    skillinit(168, cc, 3);
    skillinit(19, cc, 50);
}



void gain_special_action()
{
    if (sdata.get(174, 0).original_level > 15)
    {
        if (spact(29) == 0)
        {
            spact(29) = 1;
            txtef(5);
            txt(lang(
                u8"あなたは「"s
                    + i18n::_(u8"ability", std::to_string(629), u8"name")
                    + u8"」の能力を得た。"s,
                u8"You have learned new ability, "s
                    + i18n::_(u8"ability", std::to_string(629), u8"name")
                    + u8"."s));
        }
        if (spact(30) == 0)
        {
            spact(30) = 1;
            txtef(5);
            txt(lang(
                u8"あなたは「"s
                    + i18n::_(u8"ability", std::to_string(630), u8"name")
                    + u8"」の能力を得た。"s,
                u8"You have learned new ability, "s
                    + i18n::_(u8"ability", std::to_string(630), u8"name")
                    + u8"."s));
        }
    }
    if (sdata.get(152, 0).original_level > 15)
    {
        if (spact(31) == 0)
        {
            spact(31) = 1;
            txtef(5);
            txt(lang(
                u8"あなたは「"s
                    + i18n::_(u8"ability", std::to_string(631), u8"name")
                    + u8"」の能力を得た。"s,
                u8"You have learned new ability, "s
                    + i18n::_(u8"ability", std::to_string(631), u8"name")
                    + u8"."s));
        }
    }
    return;
}



} // namespace elona
