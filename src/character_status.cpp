#include "character_status.hpp"
#include <limits>
#include "ability.hpp"
#include "adventurer.hpp"
#include "character.hpp"
#include "config.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace
{



int get_random_body_part()
{
    if (rnd(7) == 0)
    {
        return 2;
    }
    if (rnd(9) == 0)
    {
        return 3;
    }
    if (rnd(8) == 0)
    {
        return 5;
    }
    if (rnd(4) == 0)
    {
        return 6;
    }
    if (rnd(6) == 0)
    {
        return 7;
    }
    if (rnd(5) == 0)
    {
        return 8;
    }
    if (rnd(5) == 0)
    {
        return 9;
    }
    return 1;
}



} // namespace



namespace elona
{



void modify_ether_disease_stage(int delta)
{
    int org_at_m134 = 0;
    int p_at_m134 = 0;
    int mod_at_m134 = 0;
    int cnt2_at_m134 = 0;
    int i_at_m134 = 0;
    org_at_m134 = game_data.ether_disease_stage / 1000;
    p_at_m134 = delta + (delta > 0) * game_data.ether_disease_speed;
    if (trait(168))
    {
        if (delta > 0)
        {
            p_at_m134 = p_at_m134 * 100 / 150;
        }
    }
    game_data.ether_disease_stage += p_at_m134;
    if (game_data.ether_disease_stage < 0)
    {
        game_data.ether_disease_stage = 0;
    }
    mod_at_m134 = game_data.ether_disease_stage / 1000 - org_at_m134;
    if (mod_at_m134 > 0)
    {
        if (org_at_m134 == 0)
        {
            txtef(8);
            txt(i18n::s.get("core.locale.chara.corruption.symptom"));
            if (Config::instance().extrahelp)
            {
                if (gdata_exhelp_flag(15) == 0)
                {
                    if (mode == 0)
                    {
                        if (cdata.player().continuous_action.turn == 0)
                        {
                            gdata_exhelp_flag(15) = 1;
                            ghelp = 15;
                            show_ex_help();
                        }
                    }
                }
            }
        }
        if (org_at_m134 + mod_at_m134 >= 20)
        {
            p_at_m134 = 20 - org_at_m134;
        }
        else
        {
            p_at_m134 = mod_at_m134;
        }
        for (int cnt = 0, cnt_end = (p_at_m134); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            if (org_at_m134 + cnt2_at_m134 > 20)
            {
                break;
            }
            for (int cnt = 0; cnt < 100000; ++cnt)
            {
                int tid = rnd(17) + 200;
                int stat = trait_get_info(0, tid);
                if (stat == 0 || traitref != 3)
                {
                    continue;
                }
                if (trait(tid) <= traitref(1))
                {
                    continue;
                }
                --trait(tid);
                i_at_m134 = 700 + org_at_m134 + cnt2_at_m134;
                gdata(i_at_m134) = tid;
                txtef(8);
                txt(i18n::s.get("core.locale.chara.corruption.add"));
                txtef(3);
                txt(traitrefn(1));
                if (tid == 203)
                {
                    body = 9;
                    lost_body_part(0);
                }
                if (tid == 205)
                {
                    body = 3;
                    lost_body_part(0);
                }
                if (tid == 206)
                {
                    body = 2;
                    lost_body_part(0);
                }
                break;
            }
        }
        animeload(8, 0);
        chara_refresh(0);
        return;
    }
    if (mod_at_m134 < 0)
    {
        if (org_at_m134 + mod_at_m134 < 0)
        {
            p_at_m134 = org_at_m134;
        }
        else
        {
            p_at_m134 = std::abs(mod_at_m134);
        }
        if (p_at_m134 < 0)
        {
            p_at_m134 = 0;
        }
        for (int cnt = 0, cnt_end = (p_at_m134); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            for (int cnt = 0; cnt < 100000; ++cnt)
            {
                int tid = rnd(17) + 200;
                if (cnt == 0)
                {
                    i_at_m134 = 700 + org_at_m134 - cnt2_at_m134 - 1;
                    if (gdata(i_at_m134) != 0)
                    {
                        tid = gdata(i_at_m134);
                    }
                }
                int stat = trait_get_info(0, tid);
                if (stat == 0 || traitref != 3)
                {
                    continue;
                }
                if (trait(tid) >= 0)
                {
                    continue;
                }
                ++trait(tid);
                txtef(2);
                txt(i18n::s.get("core.locale.chara.corruption.remove"));
                txtef(2);
                txt(traitrefn(0));
                break;
            }
        }
        animeload(10, 0);
        chara_refresh(0);
        return;
    }
}



void modify_potential(Character& cc, int id, int delta)
{
    sdata.get(id, cc.index).potential =
        clamp(sdata.get(id, cc.index).potential + delta, 2, 400);
}



void modify_karma(Character& cc, int delta)
{
    if (trait(162) && delta < 0)
    {
        delta = delta * 75 / 100;
        if (delta == 0)
            return;
    }
    if (trait(169) && delta < 0)
    {
        delta = delta * 150 / 100;
    }

    if (delta >= 0)
    {
        txtef(5);
    }
    else
    {
        txtef(8);
    }
    txt(i18n::s.get("core.locale.chara_status.karma.changed", delta));
    if (delta > 0)
    {
        if (cc.karma < -30 && cc.karma + delta >= -30)
        {
            txtef(2);
            txt(i18n::s.get(
                "core.locale.chara_status.karma.you_are_no_longer_criminal"));
        }
    }
    else if (delta < 0)
    {
        if (cc.karma >= -30 && cc.karma + delta < -30)
        {
            txtef(8);
            txt(i18n::s.get(
                "core.locale.chara_status.karma.you_are_criminal_now"));
            go_hostile();
        }
    }

    cc.karma += delta;

    int max = 20;
    if (trait(162))
    {
        max -= 20;
    }
    if (trait(169))
    {
        max += 20;
    }
    cc.karma = clamp(cc.karma, -100, max);
}



void modify_weight(Character& cc, int delta, bool force)
{
    int min = cc.height * cc.height * 18 / 25000;
    int max = cc.height * cc.height * 24 / 10000;

    if (cc.weight < min)
    {
        cc.weight = min;
        return;
    }
    if (!force && delta > 0)
    {
        if (cc.weight > max)
        {
            return;
        }
    }

    cc.weight = cc.weight * (100 + delta) / 100 + (delta > 0) - (delta < 0);

    if (cc.weight < 1)
    {
        cc.weight = 1;
    }
    if (is_in_fov(cc))
    {
        if (delta >= 3)
        {
            txt(i18n::s.get("core.locale.chara.weight.gain", cc));
        }
        if (delta <= -3)
        {
            txt(i18n::s.get("core.locale.chara.weight.lose", cc));
        }
    }
}



void modify_height(Character& cc, int delta)
{
    cc.height = cc.height * (100 + delta) / 100 + (delta > 0) - (delta < 0);
    if (cc.height < 1)
    {
        cc.height = 1;
    }
    if (is_in_fov(cc))
    {
        if (delta > 0)
        {
            txt(i18n::s.get("core.locale.chara.height.gain", cc));
        }
        if (delta < 0)
        {
            txt(i18n::s.get("core.locale.chara.height.lose", cc));
        }
    }
}



void refresh_speed(Character& cc)
{
    cc.current_speed = sdata(18, cc.index)
        * clamp((100 - cc.speed_correction_value), 0, 100) / 100;
    if (cc.current_speed < 10)
    {
        cc.current_speed = 10;
    }
    cc.speed_percentage_in_next_turn = 0;

    if (cc.index != 0 && game_data.mount != cc.index)
        return;

    if (game_data.mount != 0)
    {
        const auto mount_speed = sdata(18, game_data.mount)
            * clamp(100 - cdata[game_data.mount].speed_correction_value, 0, 100)
            / 100;

        cdata.player().current_speed = mount_speed * 100
            / clamp(100 + mount_speed - sdata(10, game_data.mount) * 3 / 2
                        - sdata(301, 0) * 2
                        - (cdata[game_data.mount].is_suitable_for_mount() == 1)
                            * 50,
                    100,
                    1000);
        if (cdata[game_data.mount].is_unsuitable_for_mount())
        {
            cdata.player().current_speed /= 10;
        }
        if (game_data.mount == cc.index)
        {
            cc.current_speed =
                clamp(sdata(10, cc.index) + sdata(301, 0), 10, mount_speed);
            return;
        }
    }

    gspdorg = sdata.get(18, 0).original_level;

    if (game_data.mount == 0)
    {
        int n = cdata.player().nutrition / 1000 * 1000;
        if (n < 1000)
        {
            cdata.player().speed_percentage_in_next_turn -= 30;
        }
        if (n < 2000)
        {
            cdata.player().speed_percentage_in_next_turn -= 10;
        }
        if (cdata.player().sp < 0)
        {
            cdata.player().speed_percentage_in_next_turn -= 30;
        }
        if (cdata.player().sp < 25)
        {
            cdata.player().speed_percentage_in_next_turn -= 20;
        }
        if (cdata.player().sp < 50)
        {
            cdata.player().speed_percentage_in_next_turn -= 10;
        }
    }
    if (cdata.player().inventory_weight_type >= 3)
    {
        cdata.player().speed_percentage_in_next_turn -= 50;
    }
    if (cdata.player().inventory_weight_type == 2)
    {
        cdata.player().speed_percentage_in_next_turn -= 30;
    }
    if (cdata.player().inventory_weight_type == 1)
    {
        cdata.player().speed_percentage_in_next_turn -= 10;
    }
    if (mdata_map_type == mdata_t::MapType::world_map
        || mdata_map_type == mdata_t::MapType::field)
    {
        if (game_data.cargo_weight > game_data.current_cart_limit)
        {
            cdata.player().speed_percentage_in_next_turn -= 25
                + 25
                    * (game_data.cargo_weight
                       / (game_data.current_cart_limit + 1));
        }
    }
    gspd = cdata.player().current_speed
        * (100 + cdata.player().speed_percentage) / 100;
    if (gspd < 10)
    {
        gspd = 10;
    }
}



void refresh_speed_correction_value(Character& cc)
{
    int number_of_body_parts{};
    for (const auto& body_part : cc.body_parts)
    {
        if (body_part)
        {
            ++number_of_body_parts;
        }
    }
    if (number_of_body_parts > 13)
    {
        cc.speed_correction_value = (number_of_body_parts - 13) * 5;
    }
    else
    {
        cc.speed_correction_value = 0;
    }
}



void gain_new_body_part(Character& cc)
{
    int slot = -1;
    for (size_t i = 0; i < cc.body_parts.size(); ++i)
    {
        if (cc.body_parts[i] == 0)
        {
            slot = static_cast<int>(i);
            break;
        }
    }

    if (slot == -1)
    {
        refresh_speed_correction_value(cc);
        return;
    }

    const auto body_part = get_random_body_part();
    cc.body_parts[slot] = body_part * 10000;
    if (!cm)
    {
        txt(i18n::s.get(
            "core.locale.chara_status.gain_new_body_part",
            cc,
            i18n::_(u8"ui", u8"body_part", u8"_"s + body_part)));
    }

    refresh_speed_correction_value(cc);
}



void gain_level(Character& cc)
{
    cc.experience -= cc.required_experience;
    if (cc.experience < 0)
    {
        cc.experience = 0;
    }
    ++cc.level;
    if (cc.character_role != 13)
    {
        if (r2 == 0)
        {
            txtef(2);
            if (cc.index == 0)
            {
                txt(i18n::s.get(
                    "core.locale.chara.gain_level.self", cc, cc.level));
            }
            else
            {
                txt(i18n::s.get("core.locale.chara.gain_level.other", cc));
            }
        }
    }
    else
    {
        addnews(2, cc.index);
    }
    p = 5 * (100 + sdata.get(14, cc.index).original_level * 10)
            / (300 + cc.level * 15)
        + 1;
    if (cc.index == 0)
    {
        if (cc.level % 5 == 0)
        {
            if (cc.max_level < cc.level)
            {
                if (cc.level <= 50)
                {
                    ++game_data.acquirable_feat_count;
                }
            }
        }
        gain_special_action();
        p += trait(154);
    }
    cc.skill_bonus += p;
    cc.total_skill_bonus += p;
    if (cdatan(2, cc.index) == u8"mutant"s || (cc.index == 0 && trait(0) == 1))
    {
        if (cc.level < 37)
        {
            if (cc.level % 3 == 0)
            {
                if (cc.max_level < cc.level)
                {
                    gain_new_body_part(cc);
                }
            }
        }
    }
    if (cc.max_level < cc.level)
    {
        cc.max_level = cc.level;
    }
    if (cc.index >= 16)
    {
        grow_primary_skills(cc);
    }
    update_required_experience(cc);
    chara_refresh(cc.index);
}



void grow_primary_skills(Character& cc)
{
    for (int i = 10; i < 20; ++i)
    {
        sdata.get(i, cc.index).original_level += rnd(3);
        if (sdata.get(i, cc.index).original_level > 2000)
        {
            sdata.get(i, cc.index).original_level = 2000;
        }
    }
    for (const auto& skill : mainskill)
    {
        sdata.get(skill, cc.index).original_level += rnd(3);
        if (sdata.get(skill, cc.index).original_level > 2000)
        {
            sdata.get(skill, cc.index).original_level = 2000;
        }
    }
}



void update_required_experience(Character& cc)
{
    cc.required_experience = clamp(cc.level, 1, 200)
            * (clamp(cc.level, 1, 200) + 1) * (clamp(cc.level, 1, 200) + 2)
            * (clamp(cc.level, 1, 200) + 3)
        + 3000;
    if (cc.required_experience > 100000000 || cc.required_experience < 0)
    {
        cc.required_experience = 100000000;
    }
}



void earn_gold(Character& cc, int delta)
{
    constexpr auto max = std::numeric_limits<decltype(cc.gold)>::max();

    if (cc.gold > max - delta)
    {
        cc.gold = max;
    }
    else
    {
        cc.gold += delta;
    }
}



void earn_platinum(Character& cc, int delta)
{
    constexpr auto max = std::numeric_limits<decltype(cc.platinum_coin)>::max();

    if (cc.platinum_coin > max - delta)
    {
        cc.platinum_coin = max;
    }
    else
    {
        cc.platinum_coin += delta;
    }
}



} // namespace elona
