#include "character_status.hpp"

#include <limits>

#include "../util/scope_guard.hpp"
#include "ability.hpp"
#include "adventurer.hpp"
#include "animation.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "map.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "random.hpp"
#include "trait.hpp"
#include "variables.hpp"



namespace elona
{

void modify_ether_disease_stage(int delta)
{
    int original_amount = 0;
    int add_amount = 0;
    int mod_amount = 0;
    int cnt2_at_m134 = 0;
    int i_at_m134 = 0;
    original_amount = game()->ether_disease_stage / 1000;
    add_amount = delta + (delta > 0) * game()->ether_disease_speed;
    if (cdata.player().traits().level("core.slow_ether_disease_progress"))
    {
        if (delta > 0)
        {
            add_amount = add_amount * 100 / 150;
        }
    }
    game()->ether_disease_stage =
        clamp(game()->ether_disease_stage + add_amount, 0, 20000);
    mod_amount = game()->ether_disease_stage / 1000 - original_amount;
    if (mod_amount > 0)
    {
        if (original_amount == 0)
        {
            txt(i18n::s.get("core.chara.corruption.symptom"),
                Message::color{ColorIndex::purple});
            maybe_show_ex_help(15);
        }
        if (original_amount + mod_amount >= 20)
        {
            add_amount = 20 - original_amount;
        }
        else
        {
            add_amount = mod_amount;
        }
        for (int cnt = 0, cnt_end = (add_amount); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            if (original_amount + cnt2_at_m134 > 20)
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
                if (cdata.player().traits().level(
                        *the_trait_db.get_id_from_integer(tid)) <= traitref(1))
                {
                    continue;
                }
                cdata.player().traits().sub(
                    *the_trait_db.get_id_from_integer(tid), 1);
                i_at_m134 = original_amount + cnt2_at_m134;
                game()->ether_disease_history.at(i_at_m134) = tid;
                txt(i18n::s.get("core.chara.corruption.add"),
                    Message::color{ColorIndex::purple});
                txt(traitrefn(1), Message::color{ColorIndex::red});
                if (tid == 203)
                {
                    body_part_make_unequippable(cdata.player(), "core.leg");
                }
                if (tid == 205)
                {
                    body_part_make_unequippable(cdata.player(), "core.back");
                }
                if (tid == 206)
                {
                    body_part_make_unequippable(cdata.player(), "core.neck");
                }
                break;
            }
        }
        animeload(8, cdata.player());
        chara_refresh(cdata.player());
        return;
    }
    if (mod_amount < 0)
    {
        if (original_amount + mod_amount < 0)
        {
            add_amount = original_amount;
        }
        else
        {
            add_amount = std::abs(mod_amount);
        }
        if (add_amount < 0)
        {
            add_amount = 0;
        }
        for (int cnt = 0, cnt_end = (add_amount); cnt < cnt_end; ++cnt)
        {
            cnt2_at_m134 = cnt;
            for (int cnt = 0; cnt < 100000; ++cnt)
            {
                int tid = rnd(17) + 200;
                if (cnt == 0)
                {
                    i_at_m134 = original_amount - cnt2_at_m134 - 1;
                    if (game()->ether_disease_history.at(i_at_m134) != 0)
                    {
                        tid = game()->ether_disease_history.at(i_at_m134);
                    }
                }
                int stat = trait_get_info(0, tid);
                if (stat == 0 || traitref != 3)
                {
                    continue;
                }
                if (cdata.player().traits().level(
                        *the_trait_db.get_id_from_integer(tid)) >= 0)
                {
                    continue;
                }
                cdata.player().traits().add(
                    *the_trait_db.get_id_from_integer(tid), 1);
                txt(i18n::s.get("core.chara.corruption.remove"),
                    Message::color{ColorIndex::green});
                txt(traitrefn(0), Message::color{ColorIndex::green});
                if (tid == 203)
                {
                    body_part_make_equippable(cdata.player(), "core.leg");
                }
                if (tid == 205)
                {
                    body_part_make_equippable(cdata.player(), "core.back");
                }
                if (tid == 206)
                {
                    body_part_make_equippable(cdata.player(), "core.neck");
                }
                break;
            }
        }
        animeload(10, cdata.player());
        chara_refresh(cdata.player());
        return;
    }
}



void modify_potential(Character& chara, int id, int delta)
{
    chara.get_skill(id).potential =
        clamp(chara.get_skill(id).potential + delta, 2, 400);
}



void modify_karma(Character& chara, int delta)
{
    if (cdata.player().traits().level("core.evil_man") && delta < 0)
    {
        delta = delta * 75 / 100;
        if (delta == 0)
            return;
    }
    if (cdata.player().traits().level("core.good_man") && delta < 0)
    {
        delta = delta * 150 / 100;
    }

    if (delta >= 0)
    {
        Message::instance().txtef(ColorIndex::orange);
    }
    else
    {
        Message::instance().txtef(ColorIndex::purple);
    }
    txt(i18n::s.get("core.chara_status.karma.changed", delta));
    if (delta > 0)
    {
        if (chara.karma < -30 && chara.karma + delta >= -30)
        {
            txt(i18n::s.get(
                    "core.chara_status.karma.you_are_no_longer_criminal"),
                Message::color{ColorIndex::green});
        }
    }
    else if (delta < 0)
    {
        if (chara.karma >= -30 && chara.karma + delta < -30)
        {
            txt(i18n::s.get("core.chara_status.karma.you_are_criminal_now"),
                Message::color{ColorIndex::purple});
            go_hostile();
        }
    }

    chara.karma += delta;

    int max = 20;
    if (cdata.player().traits().level("core.evil_man"))
    {
        max -= 20;
    }
    if (cdata.player().traits().level("core.good_man"))
    {
        max += 20;
    }
    chara.karma = clamp(chara.karma, -100, max);
}



void modify_weight(Character& chara, int delta, bool force)
{
    int min = chara.height * chara.height * 18 / 25000;
    int max = chara.height * chara.height * 24 / 10000;

    if (chara.weight < min)
    {
        chara.weight = min;
        return;
    }
    if (!force && delta > 0)
    {
        if (chara.weight > max)
        {
            return;
        }
    }

    chara.weight =
        chara.weight * (100 + delta) / 100 + (delta > 0) - (delta < 0);

    if (chara.weight < 1)
    {
        chara.weight = 1;
    }
    if (is_in_fov(chara))
    {
        if (delta >= 3)
        {
            txt(i18n::s.get("core.chara.weight.gain", chara));
        }
        if (delta <= -3)
        {
            txt(i18n::s.get("core.chara.weight.lose", chara));
        }
    }
}



void modify_height(Character& chara, int delta)
{
    chara.height =
        chara.height * (100 + delta) / 100 + (delta > 0) - (delta < 0);
    if (chara.height < 1)
    {
        chara.height = 1;
    }
    if (is_in_fov(chara))
    {
        if (delta > 0)
        {
            txt(i18n::s.get("core.chara.height.gain", chara));
        }
        if (delta < 0)
        {
            txt(i18n::s.get("core.chara.height.lose", chara));
        }
    }
}



void refresh_speed(Character& chara)
{
    chara.current_speed = chara.get_skill(18).level *
        clamp((100 - chara.speed_correction_value), 0, 100) / 100;
    if (chara.current_speed < 10)
    {
        chara.current_speed = 10;
    }
    chara.speed_percentage_in_next_turn = 0;

    if (!chara.is_player() && game()->mount != chara.index)
        return;

    if (game()->mount != 0)
    {
        const auto mount_speed = cdata[game()->mount].get_skill(18).level *
            clamp(100 - cdata[game()->mount].speed_correction_value, 0, 100) /
            100;

        cdata.player().current_speed = mount_speed * 100 /
            clamp(100 + mount_speed -
                      cdata[game()->mount].get_skill(10).level * 3 / 2 -
                      cdata.player().get_skill(301).level * 2 -
                      (cdata[game()->mount].is_suitable_for_mount() == 1) * 50,
                  100,
                  1000);
        if (cdata[game()->mount].is_unsuitable_for_mount())
        {
            cdata.player().current_speed /= 10;
        }
        if (game()->mount == chara.index)
        {
            chara.current_speed = clamp(
                lua_int{
                    chara.get_skill(10).level +
                    cdata.player().get_skill(301).level},
                lua_int{10},
                mount_speed);
            return;
        }
    }

    gspdorg = cdata.player().get_skill(18).base_level;

    if (game()->mount == 0)
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
    if (cdata.player().burden_state >= 3)
    {
        cdata.player().speed_percentage_in_next_turn -= 50;
    }
    if (cdata.player().burden_state == 2)
    {
        cdata.player().speed_percentage_in_next_turn -= 30;
    }
    if (cdata.player().burden_state == 1)
    {
        cdata.player().speed_percentage_in_next_turn -= 10;
    }
    if (map_data.type == mdata_t::MapType::world_map ||
        map_data.type == mdata_t::MapType::field)
    {
        if (game()->cargo_weight > game()->max_cargo_weight)
        {
            cdata.player().speed_percentage_in_next_turn -= 25 +
                25 * (game()->cargo_weight / (game()->max_cargo_weight + 1));
        }
    }
    gspd = cdata.player().current_speed *
        (100 + cdata.player().speed_percentage) / 100;
    if (gspd < 10)
    {
        gspd = 10;
    }
}



void refresh_speed_correction_value(Character& chara)
{
    int number_of_body_parts = chara.body_parts.size();
    if (number_of_body_parts > 13)
    {
        chara.speed_correction_value = (number_of_body_parts - 13) * 5;
    }
    else
    {
        chara.speed_correction_value = 0;
    }
}



void gain_level(Character& chara)
{
    chara.experience -= chara.required_experience;
    if (chara.experience < 0)
    {
        chara.experience = 0;
    }
    ++chara.level;
    if (chara.role != Role::adventurer)
    {
        if (r2 == 0)
        {
            if (chara.is_player())
            {
                txt(i18n::s.get(
                        "core.chara.gain_level.self", chara, chara.level),
                    Message::color{ColorIndex::green});
            }
            else
            {
                txt(i18n::s.get("core.chara.gain_level.other", chara),
                    Message::color{ColorIndex::green});
            }
        }
    }
    else
    {
        adventurer_add_news(NewsType::growth, chara);
    }
    p = 5 * (100 + chara.get_skill(14).base_level * 10) /
            (300 + chara.level * 15) +
        1;
    if (chara.is_player())
    {
        if (chara.level % 5 == 0)
        {
            if (chara.max_level < chara.level)
            {
                if (chara.level <= 50)
                {
                    ++game()->acquirable_feat_count;
                }
            }
        }
        gain_special_action();
        p += cdata.player().traits().level("core.more_bonus_points");
    }
    chara.skill_bonus += p;
    chara.total_skill_bonus += p;
    if (chara.race == "core.mutant" ||
        (chara.is_player() &&
         cdata.player().traits().level("core.changing_body") == 1))
    {
        if (chara.level < 37 && chara.level % 3 == 0 &&
            chara.max_level < chara.level)
        {
            body_part_gain_new_slot(chara, !cm);
        }
    }
    if (chara.max_level < chara.level)
    {
        chara.max_level = chara.level;
    }
    if (!chara.is_player_or_ally())
    {
        grow_primary_skills(chara);
    }
    update_required_experience(chara);
    chara_refresh(chara);
}



void grow_primary_skills(Character& chara)
{
    for (int i = 10; i < 20; ++i)
    {
        chara.get_skill(i).base_level += rnd(3);
        if (chara.get_skill(i).base_level > 2000)
        {
            chara.get_skill(i).base_level = 2000;
        }
    }
    for (const auto& skill : mainskill)
    {
        chara.get_skill(skill).base_level += rnd(3);
        if (chara.get_skill(skill).base_level > 2000)
        {
            chara.get_skill(skill).base_level = 2000;
        }
    }
}



void update_required_experience(Character& chara)
{
    chara.required_experience = clamp(chara.level, 1, 200) *
            (clamp(chara.level, 1, 200) + 1) *
            (clamp(chara.level, 1, 200) + 2) *
            (clamp(chara.level, 1, 200) + 3) +
        3000;
    if (chara.required_experience > 100000000 || chara.required_experience < 0)
    {
        chara.required_experience = 100000000;
    }
}



void earn_gold(Character& chara, int delta)
{
    constexpr auto max = std::numeric_limits<decltype(chara.gold)>::max();

    if (chara.gold > max - delta)
    {
        chara.gold = max;
    }
    else
    {
        chara.gold += delta;
    }
}



void earn_platinum(Character& chara, int delta)
{
    constexpr auto max = std::numeric_limits<decltype(chara.platinum)>::max();

    if (chara.platinum > max - delta)
    {
        chara.platinum = max;
    }
    else
    {
        chara.platinum += delta;
    }
}



int gain_skills_by_geen_engineering(
    const Character& original_ally,
    const Character& gene_ally)
{
    if (gene_ally.splits() || gene_ally.splits2())
    {
        return 0;
    }
    randomize(charaid2int(gene_ally.id));
    int dbmax = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        rtval = rnd(40) + 150;
        if (original_ally.get_skill(rtval).level == 0)
        {
            if (gene_ally.get_skill(rtval).level > 0)
            {
                dblist(0, dbmax) = rtval;
                ++dbmax;
            }
        }
    }
    rtval(0) = dblist(0, 0);
    rtval(1) = -1;
    if (dbmax >= 2)
    {
        if (rnd(3) == 0)
        {
            for (int cnt = 1, cnt_end = cnt + (dbmax - 1); cnt < cnt_end; ++cnt)
            {
                if (dblist(0, cnt) != rtval)
                {
                    rtval(1) = dblist(0, cnt);
                    break;
                }
            }
        }
    }
    randomize();
    return dbmax;
}



optional<data::InstanceId> gene_engineering_get_transplanted_body_part(
    const Character& original_ally,
    const Character& gene_ally)
{
    if (strutil::contains(chara_db_get_filter(gene_ally.id), u8"/man/"))
        return none;
    if (gene_ally.splits() || gene_ally.splits2())
        return none;

    if (!body_part_has_empty_slot(original_ally))
        return none;

    std::vector<data::InstanceId> body_parts;
    for (const auto& body_part : gene_ally.body_parts)
    {
        const auto gene_body_part = body_part.id;
        if (gene_body_part == "core.ammo" || gene_body_part == "core.shoot" ||
            gene_body_part == "core.body")
        {
            continue;
        }
        body_parts.push_back(gene_body_part);
    }
    if (body_parts.empty())
        return none;

    randomize(charaid2int(gene_ally.id));
    lib::scope_guard _reset_random_seed{[] { randomize(); }};

    bool already_has = false;
    data::InstanceId transplanted_body_part;
    for (int _i = 0; _i < 3; ++_i)
    {
        transplanted_body_part = choice(body_parts);
        already_has = false;
        for (const auto& body_part : original_ally.body_parts)
        {
            const auto org_body_part = body_part.id;
            if (org_body_part == transplanted_body_part)
            {
                already_has = true;
                break;
            }
        }
        if (already_has)
        {
            break;
        }
    }

    if (!already_has)
    {
        return transplanted_body_part;
    }

    std::unordered_map<data::InstanceId, size_t> num_of_gene_body_parts;
    for (const auto& body_part : gene_ally.body_parts)
    {
        ++num_of_gene_body_parts[body_part.id];
    }

    for (int _i = 0; _i < 25; ++_i)
    {
        {
            // TODO
            int n = rnd(15) + 1;
            switch (n)
            {
            case 1: transplanted_body_part = "core.head"; break;
            case 2: transplanted_body_part = "core.neck"; break;
            case 3: transplanted_body_part = "core.back"; break;
            case 4: transplanted_body_part = "core.body"; break;
            case 5: transplanted_body_part = "core.hand"; break;
            case 6: transplanted_body_part = "core.ring"; break;
            case 7: transplanted_body_part = "core.arm"; break;
            case 8: transplanted_body_part = "core.waist"; break;
            case 9: transplanted_body_part = "core.leg"; break;
            case 10: transplanted_body_part = "core.shoot"; break;
            case 11: transplanted_body_part = "core.ammo"; break;
            default: transplanted_body_part = "_invalid_"; break;
            }
        }
        size_t num_of_org_body_parts{};
        for (const auto& body_part : original_ally.body_parts)
        {
            const auto org_body_part = body_part.id;
            if (org_body_part == transplanted_body_part)
            {
                ++num_of_org_body_parts;
                break;
            }
        }
        if (num_of_org_body_parts <
            num_of_gene_body_parts[transplanted_body_part])
        {
            return transplanted_body_part;
        }
    }

    return none;
}

} // namespace elona
