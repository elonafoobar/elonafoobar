#include "character_status.hpp"

#include <limits>

#include "../util/scope_guard.hpp"
#include "adventurer.hpp"
#include "chara_db.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_skill.hpp"
#include "fov.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "map.hpp"
#include "message.hpp"
#include "random.hpp"
#include "skill.hpp"
#include "variables.hpp"



namespace elona
{

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
    chara.current_speed = chara.skills().level("core.stat_speed") *
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
        const auto mount_speed =
            cdata[game()->mount].skills().level("core.stat_speed") *
            clamp(100 - cdata[game()->mount].speed_correction_value, 0, 100) /
            100;

        cdata.player().current_speed =
            mount_speed * 100 /
            clamp(
                100 + mount_speed -
                    cdata[game()->mount].skills().level("core.stat_strength") *
                        3 / 2 -
                    cdata.player().skills().level("core.riding") * 2 -
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
                    chara.skills().level("core.stat_strength") +
                    cdata.player().skills().level("core.riding")},
                lua_int{10},
                mount_speed);
            return;
        }
    }

    gspdorg = cdata.player().skills().base_level("core.stat_speed");

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
    p = 5 * (100 + chara.skills().base_level("core.stat_learning") * 10) /
            (300 + chara.level * 15) +
        1;
    if (chara.is_player())
    {
        if (chara.level % 5 == 0 && chara.max_level < chara.level &&
            chara.level <= 50)
        {
            ++chara.acquirable_feats;
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
        chara.skills().add_base_level(
            *the_skill_db.get_id_from_integer(i), rnd(3));
        if (chara.skills().base_level(*the_skill_db.get_id_from_integer(i)) >
            2000)
        {
            chara.skills().set_base_level(
                *the_skill_db.get_id_from_integer(i), 2000);
        }
    }
    for (const auto& skill : mainskill)
    {
        chara.skills().add_base_level(
            *the_skill_db.get_id_from_integer(skill), rnd(3));
        if (chara.skills().base_level(
                *the_skill_db.get_id_from_integer(skill)) > 2000)
        {
            chara.skills().set_base_level(
                *the_skill_db.get_id_from_integer(skill), 2000);
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
    randomize(the_character_db.ensure(gene_ally.id).integer_id);
    int dbmax = 0;
    for (int cnt = 0; cnt < 100; ++cnt)
    {
        rtval = rnd(40) + 150;
        if (original_ally.skills().level(
                *the_skill_db.get_id_from_integer(rtval)) == 0)
        {
            if (gene_ally.skills().level(
                    *the_skill_db.get_id_from_integer(rtval)) > 0)
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
    if (strutil::contains(chara_db_get_filter(gene_ally.id), "/man/"))
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

    randomize(the_character_db.ensure(gene_ally.id).integer_id);
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
