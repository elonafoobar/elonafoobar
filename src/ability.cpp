#include "ability.hpp"
#include "audio.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "random.hpp"
#include "range.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{



int increase_potential(int potential, int level_delta)
{
    for (int i = 0; i < level_delta; ++i)
    {
        potential = std::min(static_cast<int>(potential * 1.1) + 1, 400);
    }
    return potential;
}



int decrease_potential(int potential, int level_delta)
{
    for (int i = 0; i < level_delta; ++i)
    {
        potential = std::max(static_cast<int>(potential * 0.9), 1);
    }
    return potential;
}



void set_ability(
    Character& cc,
    int id,
    int original_level,
    int experience,
    int potential)
{
    sdata.get(id, cc.index).original_level = clamp(original_level, 0, 2000);
    sdata.get(id, cc.index).experience = experience;
    sdata.get(id, cc.index).potential = potential;
}



} // namespace



namespace elona
{


AbilityDB the_ability_db;
SkillData sdata;


void AbilityDB::define(lua_State* L)
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
        AbilityData{
            std::stoi(id),
            related_basic_attribute,
            sdataref1,
            cost,
            sdataref3,
            sdataref4,
        });
}


SkillData::SkillData()
    : storage(ELONA_MAX_CHARACTERS, std::vector<Ability>(600))
{
}



void SkillData::clear(int cc)
{
    range::fill(storage[cc], Ability{});
}



void SkillData::copy(int tc, int cc)
{
    range::copy(storage[cc], std::begin(storage[tc]));
}



void chara_init_skill(Character& cc, int id, int initial_level)
{
    int original_level = sdata.get(id, cc.index).original_level;
    int potential;
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
    int level;
    if (id == 18)
    {
        level = initial_level * (100 + cc.level * 2) / 100;
    }
    else
    {
        level = potential * potential * cc.level / 45000 + initial_level
            + cc.level / 3;
    }
    if (cc.level > 1)
    {
        potential = std::exp(std::log(0.9) * cc.level) * potential;
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
    sdata.get(id, cc.index).original_level += clamp(level, 0, 2000);
    sdata.get(id, cc.index).potential += potential;
}



void chara_init_common_skills(Character& cc)
{
    for (int element = 50; element < 61; ++element)
    {
        auto level = cc.level * 4 + 96;
        if (level > 300)
        {
            level = 300;
        }
        if (sdata(element, cc.index) != 0)
        {
            if (sdata(element, cc.index) < 100
                || sdata(element, cc.index) >= 500)
            {
                level = sdata(element, cc.index);
            }
            else
            {
                level += sdata(element, cc.index);
            }
        }
        if ((element == 60 && level < 500) || cc.index == 0)
        {
            level = 100;
        }
        sdata.get(element, cc.index).original_level = clamp(level, 1, 2000);
        sdata.get(element, cc.index).experience = 0;
        sdata.get(element, cc.index).potential = 0;
    }

    chara_init_skill(cc, 100, 4);
    chara_init_skill(cc, 101, 4);
    chara_init_skill(cc, 103, 4);
    chara_init_skill(cc, 102, 4);
    chara_init_skill(cc, 104, 4);
    chara_init_skill(cc, 105, 4);
    chara_init_skill(cc, 107, 4);
    chara_init_skill(cc, 108, 4);
    chara_init_skill(cc, 111, 4);
    chara_init_skill(cc, 109, 4);
    chara_init_skill(cc, 173, 4);
    chara_init_skill(cc, 154, 4);
    chara_init_skill(cc, 155, 4);
    chara_init_skill(cc, 106, 4);
    chara_init_skill(cc, 157, 4);
    chara_init_skill(cc, 181, 4);
    chara_init_skill(cc, 171, 4);
    chara_init_skill(cc, 170, 4);
    chara_init_skill(cc, 169, 4);
    chara_init_skill(cc, 168, 3);
    chara_init_skill(cc, 19, 50);
}



void chara_gain_skill(Character& cc, int id, int initial_level, int stock)
{
    if (id >= 400)
    {
        if (cc.index == 0)
        {
            spell(id - 400) += stock;
            modify_potential(cc, id, 1);
        }
    }
    if (sdata.get(id, cc.index).original_level != 0)
    {
        if (id < 400)
        {
            modify_potential(cc, id, 20);
        }
        return;
    }
    if (id >= 400)
    {
        modify_potential(cc, id, 200);
    }
    else
    {
        modify_potential(cc, id, 50);
    }
    sdata.get(id, cc.index).original_level =
        clamp(sdata.get(id, cc.index).original_level + initial_level, 1, 2000);

    chara_refresh(cc.index);
}



void gain_special_action()
{
    if (sdata.get(174, 0).original_level > 15)
    {
        if (spact(29) == 0)
        {
            spact(29) = 1;
            txtef(5);
            txt(i18n::s.get(
                "core.locale.skill.gained",
                i18n::_(u8"ability", std::to_string(629), u8"name")));
        }
        if (spact(30) == 0)
        {
            spact(30) = 1;
            txtef(5);
            txt(i18n::s.get(
                "core.locale.skill.gained",
                i18n::_(u8"ability", std::to_string(630), u8"name")));
        }
    }
    if (sdata.get(152, 0).original_level > 15)
    {
        if (spact(31) == 0)
        {
            spact(31) = 1;
            txtef(5);
            txt(i18n::s.get(
                "core.locale.skill.gained",
                i18n::_(u8"ability", std::to_string(631), u8"name")));
        }
    }
}



void chara_gain_fixed_skill_exp(Character& cc, int id, int experience)
{
    auto lv = sdata.get(id, cc.index).original_level;
    auto exp = sdata.get(id, cc.index).experience + experience;
    auto potential = sdata.get(id, cc.index).potential;

    if (potential == 0)
        return;

    if (exp >= 1000)
    {
        const auto lv_delta = exp / 1000;
        lv += lv_delta;
        exp = exp % 1000;
        potential = decrease_potential(potential, lv_delta);
        set_ability(cc, id, lv, exp, potential);
        if (is_in_fov(cc))
        {
            if (cc.index == 0 || cc.index < 16)
            {
                snd(61);
                txtef(2);
            }
            txt(txtskillchange(id, cc.index, true));
        }
        chara_refresh(cc.index);
        return;
    }
    if (exp < 0)
    {
        auto lv_delta = -exp / 1000 + 1;
        exp = 1000 + exp % 1000;
        if (lv - lv_delta < 1)
        {
            lv_delta = lv - 1;
            if (lv == 1)
            {
                if (lv_delta == 0)
                {
                    exp = 0;
                }
            }
        }
        lv -= lv_delta;
        potential = increase_potential(potential, lv_delta);
        set_ability(cc, id, lv, exp, potential);
        if (cc.index == 0 || cc.index < 16)
        {
            if (is_in_fov(cc))
            {
                if (lv_delta != 0)
                {
                    txtef(3);
                    txt(txtskillchange(id, cc.index, false));
                }
            }
        }
        chara_refresh(cc.index);
        return;
    }
    set_ability(cc, id, lv, exp, potential);
}



void chara_gain_skill_exp(
    Character& cc,
    int id,
    int experience,
    int experience_divisor_of_related_basic_attribute,
    int experience_divisor_of_character_level)
{
    if (sdata.get(id, cc.index).original_level == 0)
        return;
    if (experience == 0)
        return;

    if (the_ability_db[id]->related_basic_attribute != 0)
    {
        chara_gain_skill_exp(
            cc,
            the_ability_db[id]->related_basic_attribute,
            experience / (2 + experience_divisor_of_related_basic_attribute));
    }

    auto lv = sdata.get(id, cc.index).original_level;
    auto potential = sdata.get(id, cc.index).potential;
    if (potential == 0)
        return;

    int exp;
    if (experience > 0)
    {
        exp = experience * potential / (100 + lv * 15);
        if (id >= 10 && id <= 19)
        {
            if (cc.growth_buffs[id - 10] > 0)
            {
                exp = exp * (100 + cc.growth_buffs[id - 10]) / 100;
            }
        }
        if (exp == 0)
        {
            if (rnd(lv / 10 + 1) == 0)
            {
                exp = 1;
            }
            else
            {
                return;
            }
        }
    }
    else
    {
        exp = experience;
    }
    if (gdata_current_map == mdata_t::MapId::show_house)
    {
        exp /= 5;
    }
    if (exp > 0)
    {
        if (id >= 100)
        {
            if (experience_divisor_of_character_level != 1000)
            {
                const auto lvl_exp =
                    rnd(int(double(cc.required_experience) * exp / 1000
                            / (cc.level
                               + experience_divisor_of_character_level))
                        + 1)
                    + rnd(2);
                cc.experience += lvl_exp;
                if (cc.index == 0)
                {
                    gdata_sleep_experience += lvl_exp;
                }
            }
        }
    }
    exp += sdata.get(id, cc.index).experience;
    if (exp >= 1000)
    {
        const auto lv_delta = exp / 1000;
        exp = exp % 1000;
        lv += lv_delta;
        potential = decrease_potential(potential, lv_delta);
        set_ability(cc, id, lv, exp, potential);
        if (is_in_fov(cc))
        {
            if (cc.index == 0 || cc.index < 16)
            {
                snd(61);
                txtef(2);
                msgalert = 1;
            }
            txt(txtskillchange(id, cc.index, true));
        }
        chara_refresh(cc.index);
        return;
    }
    if (exp < 0)
    {
        auto lv_delta = -exp / 1000 + 1;
        exp = 1000 + exp % 1000;
        if (lv - lv_delta < 1)
        {
            lv_delta = lv - 1;
            if (lv == 1)
            {
                if (lv_delta == 0)
                {
                    exp = 0;
                }
            }
        }
        lv -= lv_delta;
        potential = increase_potential(potential, lv_delta);
        set_ability(cc, id, lv, exp, potential);
        if (is_in_fov(cc))
        {
            if (cc.index == 0 || cc.index < 16)
            {
                if (lv_delta != 0)
                {
                    msgalert = 1;
                    txtef(3);
                    txt(txtskillchange(id, cc.index, false));
                }
            }
        }
        chara_refresh(cc.index);
        return;
    }

    set_ability(cc, id, lv, exp, potential);
}



void gain_digging_experience()
{
    chara_gain_skill_exp(cdata.player(), 163, 100);
}



void gain_literacy_experience()
{
    chara_gain_skill_exp(cdata.player(), 150, 15, 10, 100);
}



void gain_negotiation_experience(int cc)
{
    if (r2 >= (sdata(156, cc) + 10) * (sdata(156, cc) + 10))
    {
        chara_gain_skill_exp(
            cdata[cc],
            156,
            clamp(r2 * r2 / (sdata(156, cc) * 5 + 10), 10, 1000),
            10);
    }
}



void gain_lock_picking_experience(int cc)
{
    chara_gain_skill_exp(cdata[cc], 158, 100);
}



void gain_detection_experience(int cc)
{
    chara_gain_skill_exp(cdata[cc], 159, gdata_current_dungeon_level * 2 + 20);
}



void gain_casting_experience(int cc)
{
    if (cc == 0)
    {
        chara_gain_skill_exp(
            cdata[cc], r2, the_ability_db[r2]->cost * 4 + 20, 4, 5);
        chara_gain_skill_exp(cdata[cc], 172, the_ability_db[r2]->cost + 10, 5);
    }
    else
    {
        chara_gain_skill_exp(cdata[cc], 172, the_ability_db[r2]->cost + 10, 5);
    }
}



void gain_mana_capacity_experience(int cc)
{
    chara_gain_skill_exp(
        cdata[cc], 164, std::abs(cdata[cc].mp) * 200 / (cdata[cc].max_mp + 1));
}



void gain_healing_and_meditation_experience(int cc)
{
    if (cdata[cc].hp != cdata[cc].max_hp)
    {
        if (sdata(154, cc) < sdata(11, cc))
        {
            chara_gain_skill_exp(cdata[cc], 154, 5 + sdata(154, cc) / 5, 1000);
        }
    }
    if (cdata[cc].mp != cdata[cc].max_mp)
    {
        if (sdata(155, cc) < sdata(16, cc))
        {
            chara_gain_skill_exp(cdata[cc], 155, 5 + sdata(155, cc) / 5, 1000);
        }
    }
}



void gain_stealth_experience(int cc)
{
    if (mdata_map_type == mdata_t::MapType::world_map)
    {
        if (rnd(20))
        {
            return;
        }
    }
    chara_gain_skill_exp(cdata[cc], 157, 2, 0, 1000);
}



void gain_investing_experience(int cc)
{
    chara_gain_skill_exp(cdata[cc], 160, 600);
}



void gain_weight_lifting_experience(int cc)
{
    if (cdata.player().inventory_weight_type == 0)
    {
        return;
    }
    if (mdata_map_type == mdata_t::MapType::world_map)
    {
        if (rnd(20))
        {
            return;
        }
    }
    chara_gain_skill_exp(cdata[cc], 153, 4, 0, 1000);
}



void gain_magic_device_experience(int cc)
{
    if (cc == 0)
    {
        chara_gain_skill_exp(cdata[cc], 174, 40);
    }
}



void gain_fishing_experience(int cc)
{
    chara_gain_skill_exp(cdata[cc], 185, 100);
}



void gain_memorization_experience(int cc)
{
    chara_gain_skill_exp(
        cdata[cc], 165, 10 + the_ability_db[efid]->sdataref4 / 5);
}



void gain_crafting_experience(int skill, int mat_amount)
{
    chara_gain_skill_exp(cdata.player(), skill, 50 + mat_amount * 20);
}



void gain_disarm_trap_experience()
{
    chara_gain_skill_exp(cdata[cc], 175, 50);
}



} // namespace elona
