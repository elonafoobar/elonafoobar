#include "ability.hpp"
#include "audio.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "range.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{
int lv_at_m77 = 0;
int exp_at_m77 = 0;
int growth_at_m77 = 0;
int lvchange_at_m77 = 0;
}



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



int skillexp(int id, int cc, int experience, int prm_572, int prm_573)
{
    int exp2_at_m77 = 0;
    if (sdata.get(id, cc).original_level == 0)
    {
        return 0;
    }
    if (experience == 0)
    {
        return 0;
    }
    if (the_ability_db[id]->related_basic_attribute != 0)
    {
        skillexp(
            the_ability_db[id]->related_basic_attribute,
            cc,
            experience / (2 + prm_572));
    }
    lv_at_m77 = sdata.get(id, cc).original_level;
    growth_at_m77 = sdata.get(id, cc).potential;
    if (growth_at_m77 == 0)
    {
        return 0;
    }
    if (experience > 0)
    {
        exp_at_m77 = experience * growth_at_m77 / (100 + lv_at_m77 * 15);
        if (id >= 10)
        {
            if (id <= 19)
            {
                if (cdata[cc].growth_buffs[id - 10] > 0)
                {
                    exp_at_m77 = exp_at_m77
                        * (100 + cdata[cc].growth_buffs[id - 10]) / 100;
                }
            }
        }
        if (exp_at_m77 == 0)
        {
            if (rnd(lv_at_m77 / 10 + 1) == 0)
            {
                exp_at_m77 = 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        exp_at_m77 = experience;
    }
    if (gdata_current_map == 35)
    {
        exp_at_m77 /= 5;
    }
    if (exp_at_m77 > 0)
    {
        if (id >= 100)
        {
            if (prm_573 != 1000)
            {
                exp2_at_m77 = rnd(cdata[cc].required_experience * exp_at_m77
                                      / 1000 / (cdata[cc].level + prm_573)
                                  + 1)
                    + rnd(2);
                cdata[cc].experience += exp2_at_m77;
                if (cc == 0)
                {
                    gdata_sleep_experience += exp2_at_m77;
                }
            }
        }
    }
    exp_at_m77 += sdata.get(id, cc).experience;
    if (exp_at_m77 >= 1000)
    {
        lvchange_at_m77 = exp_at_m77 / 1000;
        exp_at_m77 = exp_at_m77 % 1000;
        lv_at_m77 += lvchange_at_m77;
        for (int cnt = 0, cnt_end = (lvchange_at_m77); cnt < cnt_end; ++cnt)
        {
            growth_at_m77 = growth_at_m77 * 0.9;
            if (growth_at_m77 < 1)
            {
                growth_at_m77 = 1;
            }
        }
        sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
        sdata.get(id, cc).experience = exp_at_m77;
        sdata.get(id, cc).potential = growth_at_m77;
        if (is_in_fov(cc))
        {
            if (cc == 0 || cc < 16)
            {
                snd(61);
                txtef(2);
                msgalert = 1;
            }
            txt(txtskillchange(id, cc, true));
        }
        chara_refresh(cc);
        return 1;
    }
    if (exp_at_m77 < 0)
    {
        lvchange_at_m77 = -exp_at_m77 / 1000 + 1;
        exp_at_m77 = 1000 + exp_at_m77 % 1000;
        if (lv_at_m77 - lvchange_at_m77 < 1)
        {
            lvchange_at_m77 = lv_at_m77 - 1;
            if (lv_at_m77 == 1)
            {
                if (lvchange_at_m77 == 0)
                {
                    exp_at_m77 = 0;
                }
            }
        }
        lv_at_m77 -= lvchange_at_m77;
        for (int cnt = 0, cnt_end = (lvchange_at_m77); cnt < cnt_end; ++cnt)
        {
            growth_at_m77 = int(growth_at_m77 * 1.1) + 1;
            if (growth_at_m77 > 400)
            {
                growth_at_m77 = 400;
            }
        }
        sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
        sdata.get(id, cc).experience = exp_at_m77;
        sdata.get(id, cc).potential = growth_at_m77;
        if (is_in_fov(cc))
        {
            if (cc == 0 || cc < 16)
            {
                if (lvchange_at_m77 != 0)
                {
                    msgalert = 1;
                    txtef(3);
                    txt(txtskillchange(id, cc, false));
                }
            }
        }
        chara_refresh(cc);
        return 1;
    }
    sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
    sdata.get(id, cc).experience = exp_at_m77;
    sdata.get(id, cc).potential = growth_at_m77;
    return 0;
}



int skillmod(int id, int cc, int experience)
{
    lv_at_m77 = sdata.get(id, cc).original_level;
    exp_at_m77 = sdata.get(id, cc).experience + experience;
    growth_at_m77 = sdata.get(id, cc).potential;
    if (growth_at_m77 == 0)
    {
        return 0;
    }
    if (exp_at_m77 >= 1000)
    {
        lvchange_at_m77 = exp_at_m77 / 1000;
        lv_at_m77 += lvchange_at_m77;
        exp_at_m77 = exp_at_m77 % 1000;
        for (int cnt = 0, cnt_end = (lvchange_at_m77); cnt < cnt_end; ++cnt)
        {
            growth_at_m77 = growth_at_m77 * 0.9;
            if (growth_at_m77 < 1)
            {
                growth_at_m77 = 1;
            }
        }
        sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
        sdata.get(id, cc).experience = exp_at_m77;
        sdata.get(id, cc).potential = growth_at_m77;
        if (is_in_fov(cc))
        {
            if (cc == 0 || cc < 16)
            {
                snd(61);
                txtef(2);
            }
            txt(txtskillchange(id, cc, true));
        }
        chara_refresh(cc);
        return 1;
    }
    if (exp_at_m77 < 0)
    {
        lvchange_at_m77 = -exp_at_m77 / 1000 + 1;
        exp_at_m77 = 1000 + exp_at_m77 % 1000;
        if (lv_at_m77 - lvchange_at_m77 < 1)
        {
            lvchange_at_m77 = lv_at_m77 - 1;
            if (lv_at_m77 == 1)
            {
                if (lvchange_at_m77 == 0)
                {
                    exp_at_m77 = 0;
                }
            }
        }
        lv_at_m77 -= lvchange_at_m77;
        for (int cnt = 0, cnt_end = (lvchange_at_m77); cnt < cnt_end; ++cnt)
        {
            growth_at_m77 = int(growth_at_m77 * 1.1) + 1;
            if (growth_at_m77 > 400)
            {
                growth_at_m77 = 400;
            }
        }
        sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
        sdata.get(id, cc).experience = exp_at_m77;
        sdata.get(id, cc).potential = growth_at_m77;
        if (cc == 0 || cc < 16)
        {
            if (is_in_fov(cc))
            {
                if (lvchange_at_m77 != 0)
                {
                    txtef(3);
                    txt(txtskillchange(id, cc, false));
                }
            }
        }
        chara_refresh(cc);
        return 1;
    }
    sdata.get(id, cc).original_level = clamp(lv_at_m77, 0, 2000);
    sdata.get(id, cc).experience = exp_at_m77;
    sdata.get(id, cc).potential = growth_at_m77;
    return 0;
}



void gain_digging_experience()
{
    skillexp(163, 0, 100);
    return;
}



void gain_literacy_experience()
{
    skillexp(150, 0, 15, 10, 100);
    return;
}



void gain_negotiation_experience(int cc)
{
    if (r2 >= (sdata(156, cc) + 10) * (sdata(156, cc) + 10))
    {
        skillexp(
            156, cc, clamp(r2 * r2 / (sdata(156, cc) * 5 + 10), 10, 1000), 10);
    }
}



void gain_lock_picking_experience(int cc)
{
    skillexp(158, cc, 100);
}



void gain_detection_experience(int cc)
{
    skillexp(159, cc, gdata_current_dungeon_level * 2 + 20);
}



void gain_casting_experience(int cc)
{
    if (cc == 0)
    {
        skillexp(r2, cc, the_ability_db[r2]->cost * 4 + 20, 4, 5);
        skillexp(172, cc, the_ability_db[r2]->cost + 10, 5);
    }
    else
    {
        skillexp(172, cc, the_ability_db[r2]->cost + 10, 5);
    }
}



void gain_mana_capacity_experience(int cc)
{
    skillexp(164, cc, std::abs(cdata[cc].mp) * 200 / (cdata[cc].max_mp + 1));
}



void gain_healing_and_meditation_experience(int cc)
{
    if (cdata[cc].hp != cdata[cc].max_hp)
    {
        if (sdata(154, cc) < sdata(11, cc))
        {
            skillexp(154, cc, 5 + sdata(154, cc) / 5, 1000);
        }
    }
    if (cdata[cc].mp != cdata[cc].max_mp)
    {
        if (sdata(155, cc) < sdata(16, cc))
        {
            skillexp(155, cc, 5 + sdata(155, cc) / 5, 1000);
        }
    }
}



void gain_stealth_experience(int cc)
{
    if (mdata(6) == 1)
    {
        if (rnd(20))
        {
            return;
        }
    }
    skillexp(157, cc, 2, 0, 1000);
}



void gain_investing_experience(int cc)
{
    skillexp(160, cc, 600);
}



void gain_weight_lifting_experience(int cc)
{
    if (cdata[0].inventory_weight_type == 0)
    {
        return;
    }
    if (mdata(6) == 1)
    {
        if (rnd(20))
        {
            return;
        }
    }
    skillexp(153, cc, 4, 0, 1000);
}



void gain_magic_device_experience(int cc)
{
    if (cc == 0)
    {
        skillexp(174, cc, 40);
    }
}



void gain_fishing_experience(int cc)
{
    skillexp(185, cc, 100);
}



void gain_memorization_experience(int cc)
{
    skillexp(165, cc, 10 + the_ability_db[efid]->sdataref4 / 5);
}



void gain_crafting_experience(int skill)
{
    skillexp(skill, 0, 50 + r2 * 20);
}



void gain_disarm_trap_experience()
{
    skillexp(175, cc, 50);
    return;
}



} // namespace elona
