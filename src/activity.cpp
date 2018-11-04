#include "activity.hpp"
#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "command.hpp"
#include "config/config.hpp"
#include "dmgheal.hpp"
#include "enchantment.hpp"
#include "fish.hpp"
#include "food.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "message.hpp"
#include "optional.hpp"
#include "status_ailment.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{
int digx = 0;
int digy = 0;

void rowact_check(int prm_789)
{
    if (cdata[prm_789].continuous_action)
    {
        if (cdata[prm_789].continuous_action.type
            != ContinuousAction::Type::travel)
        {
            cdata[prm_789].stops_continuous_action_if_damaged = 1;
        }
    }
}



void rowact_item(int prm_790)
{
    for (auto&& cc : cdata.all())
    {
        if (cc.state() != Character::State::alive)
        {
            continue;
        }
        if (cc.continuous_action.turn <= 0)
        {
            continue;
        }
        if (cc.continuous_action.type == ContinuousAction::Type::eat
            || cc.continuous_action.type == ContinuousAction::Type::read)
        {
            if (cc.continuous_action.item == prm_790)
            {
                cdata[cc.index].continuous_action.finish();
                txt(i18n::s.get("core.locale.activity.cancel.item", cc));
            }
        }
    }
}



void activity_handle_damage(Character& chara)
{
    if (chara.index == 0)
    {
        if (chara.continuous_action.type != ContinuousAction::Type::eat
            && chara.continuous_action.type != ContinuousAction::Type::read
            && chara.continuous_action.type != ContinuousAction::Type::travel)
        {
            rtval = 0;
        }
        else
        {
            screenupdate = -1;
            update_screen();
            prompt_stop_continuous_action();
        }
    }
    if (chara.index != 0 || rtval == 0)
    {
        if (is_in_fov(chara))
        {
            txt(i18n::s.get(
                "core.locale.activity.cancel.normal",
                chara,
                i18n::_(
                    u8"ui",
                    u8"action",
                    u8"_"s + static_cast<int>(chara.continuous_action.type))));
        }
        chara.continuous_action.finish();
    }
    screenupdate = -1;
    update_screen();
    chara.stops_continuous_action_if_damaged = 0;
}

optional<TurnResult> activity_proc(Character& chara)
{
    ci = chara.continuous_action.item;
    --chara.continuous_action.turn;
    if (chara.continuous_action.type == ContinuousAction::Type::fish)
    {
        auto_turn(Config::instance().animewait * 2);
        spot_fishing();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::dig_wall)
    {
        auto_turn(Config::instance().animewait * 0.75);
        spot_mining_or_wall();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::search_material)
    {
        auto_turn(Config::instance().animewait * 0.75);
        spot_material();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::dig_ground)
    {
        auto_turn(Config::instance().animewait * 0.75);
        spot_digging();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::sleep)
    {
        auto_turn(Config::instance().animewait / 4);
        do_rest();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::eat)
    {
        auto_turn(Config::instance().animewait * 5);
        return do_eat_command();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::read)
    {
        auto_turn(Config::instance().animewait * 1.25);
        return do_read_command();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::sex)
    {
        auto_turn(Config::instance().animewait * 2.5);
        continuous_action_sex();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::others)
    {
        if (game_data.continuous_action_about_to_start == 103)
        {
            auto_turn(Config::instance().animewait * 2);
        }
        else if (game_data.continuous_action_about_to_start == 104)
        {
            auto_turn(Config::instance().animewait * 2);
        }
        else if (game_data.continuous_action_about_to_start == 105)
        {
            auto_turn(Config::instance().animewait * 2.5);
        }
        else
        {
            auto_turn(Config::instance().animewait);
        }
        continuous_action_others();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::blend)
    {
        auto_turn(Config::instance().animewait);
        continuous_action_blending();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::perform)
    {
        auto_turn(Config::instance().animewait * 2);
        continuous_action_perform();
    }
    if (chara.continuous_action.type == ContinuousAction::Type::travel)
    {
        map_global_proc_travel_events();
        return proc_movement_event();
    }
    if (chara.continuous_action.turn > 0)
    {
        return TurnResult::turn_end;
    }
    cdata[cc].continuous_action.finish();
    if (cc == 0)
    {
        if (chatteleport == 1)
        {
            chatteleport = 0;
            return TurnResult::exit_map;
        }
    }

    return none;
}

void prompt_stop_continuous_action()
{
    txt(i18n::s.get(
        "core.locale.activity.cancel.prompt",
        i18n::_(
            u8"ui",
            u8"action",
            u8"_"s + static_cast<int>(cdata[cc].continuous_action.type))));
    rtval = yes_or_no(promptx, prompty, 160);
}



void continuous_action_perform()
{
    static int performtips;

    if (!cdata[cc].continuous_action)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.activity.perform.start", cdata[cc], inv[ci]));
        }
        cdata[cc].continuous_action.type = ContinuousAction::Type::perform;
        cdata[cc].continuous_action.turn = 61;
        cdata[cc].continuous_action.item = ci;
        cdata[cc].quality_of_performance = 40;
        cdata[cc].tip_gold = 0;
        if (cc == 0)
        {
            performtips = 0;
        }
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        ci = cdata[cc].continuous_action.item;
        if (cdata[cc].continuous_action.turn % 10 == 0)
        {
            if (is_in_fov(cdata[cc]))
            {
                if (rnd(10) == 0)
                {
                    txt(i18n::s.get(
                            "core.locale.activity.perform.sound.random"),
                        Message::color{ColorIndex::blue});
                }
                txt(i18n::s.get("core.locale.activity.perform.sound.cha"),
                    Message::color{ColorIndex::blue});
            }
        }
        if (cdata[cc].continuous_action.turn % 20 == 0)
        {
            gold = 0;
            make_sound(cdata[cc].position.x, cdata[cc].position.y, 5, 1, 1, cc);
            for (auto&& audience : cdata.all())
            {
                if (audience.state() != Character::State::alive)
                {
                    continue;
                }
                if (game_data.date.hours() >= audience.time_interest_revive)
                {
                    audience.interest = 100;
                }
                if (is_in_fov(cdata[cc]))
                {
                    if (audience.vision_flag != msync)
                    {
                        continue;
                    }
                }
                else if (
                    dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        audience.position.x,
                        audience.position.y)
                    > 3)
                {
                    continue;
                }
                if (audience.interest <= 0)
                {
                    continue;
                }
                if (audience.sleep > 0)
                {
                    continue;
                }
                x = audience.position.x;
                y = audience.position.y;
                if (cell_data.at(x, y).chara_index_plus_one == 0)
                {
                    continue;
                }
                tc = audience.index;
                if (tc == cc)
                {
                    continue;
                }
                if (cdata[tc].relationship == -3)
                {
                    if (cdata[tc].hate == 0)
                    {
                        if (is_in_fov(cdata[tc]))
                        {
                            txt(i18n::s.get(
                                "core.locale.activity.perform.gets_angry",
                                cdata[tc]));
                        }
                    }
                    cdata[tc].hate = 30;
                    continue;
                }
                if (cc == 0)
                {
                    cdata[tc].interest -= rnd(15);
                    cdata[tc].time_interest_revive =
                        game_data.date.hours() + 12;
                }
                if (cdata[tc].interest <= 0)
                {
                    if (is_in_fov(cdata[cc]))
                    {
                        txt(i18n::s.get("core.locale.activity.perform.dialog."
                                        "disinterest"),
                            Message::color{ColorIndex::cyan});
                    }
                    cdata[tc].interest = 0;
                    continue;
                }
                if (sdata(183, cc) < cdata[tc].level)
                {
                    if (rnd(3) == 0)
                    {
                        cdata[cc].quality_of_performance -= cdata[tc].level / 2;
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get("core.locale.activity.perform."
                                            "dialog.angry"),
                                Message::color{ColorIndex::cyan});
                            txt(i18n::s.get(
                                "core.locale.activity.perform.throws_rock",
                                cdata[tc]));
                        }
                        dmg = rnd(cdata[tc].level + 1) + 1;
                        if (cdata[tc].id == 29)
                        {
                            dmg = cdata[tc].level * 2 + rnd(100);
                        }
                        damage_hp(cdata[cc], dmg, -8);
                        if (cdata[cc].state() == Character::State::empty)
                        {
                            break;
                        }
                        continue;
                    }
                }
                if (rnd(3) == 0)
                {
                    p = cdata[cc].quality_of_performance
                            * cdata[cc].quality_of_performance
                            * (100
                               + inv[cdata[cc].continuous_action.item].param1
                                   / 5)
                            / 100 / 1000
                        + rnd(10);
                    p = clamp(
                        cdata[tc].gold * clamp(p(0), 1, 100) / 125,
                        0,
                        sdata(183, cc) * 100);
                    if (tc < 16)
                    {
                        p = rnd(clamp(p(0), 1, 100)) + 1;
                    }
                    if ((cdata[tc].character_role >= 1000
                         && cdata[tc].character_role < 2000)
                        || cdata[tc].character_role == 2003)
                    {
                        p /= 5;
                    }
                    if (p > cdata[tc].gold)
                    {
                        p = cdata[tc].gold;
                    }
                    cdata[tc].gold -= p;
                    earn_gold(cdata[cc], p);
                    gold += p;
                }
                if (cdata[tc].level > sdata(183, cc))
                {
                    continue;
                }
                p = rnd(cdata[tc].level + 1) + 1;
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 2 + 1))
                {
                    if (game_data.executing_immediate_quest_type == 1009)
                    {
                        if (tc >= 57)
                        {
                            cdata[tc].impression += rnd(3);
                            calcpartyscore();
                        }
                    }
                    if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance += p;
                    }
                    else if (rnd(2) == 0)
                    {
                        cdata[cc].quality_of_performance -= p;
                    }
                }
                if (encfindspec(cdata[cc].continuous_action.item, 60))
                {
                    if (rnd(15) == 0)
                    {
                        dmgcon(tc, StatusAilment::drunk, 500);
                    }
                }
                if (rnd(sdata(183, cc) + 1) > rnd(cdata[tc].level * 5 + 1))
                {
                    if (rnd(3) == 0)
                    {
                        if (is_in_fov(cdata[cc]))
                        {
                            txt(i18n::s.get(
                                    "core.locale.activity.perform.dialog."
                                    "interest",
                                    cdata[tc],
                                    cdata[cc]),
                                Message::color{ColorIndex::cyan});
                        }
                        cdata[cc].quality_of_performance += cdata[tc].level + 5;
                        if (cc == 0)
                        {
                            if (tc >= 16)
                            {
                                if (rnd(performtips * 2 + 2) == 0)
                                {
                                    x = clamp(
                                        cdata[cc].position.x - 1 + rnd(3),
                                        0,
                                        map_data.width - 1);
                                    y = clamp(
                                        cdata[cc].position.y - 1 + rnd(3),
                                        0,
                                        map_data.height - 1);
                                    cell_check(x, y);
                                    if (cellaccess == 0)
                                    {
                                        continue;
                                    }
                                    if (fov_los(
                                            cdata[tc].position.x,
                                            cdata[tc].position.y,
                                            x,
                                            y)
                                        == 0)
                                    {
                                        continue;
                                    }
                                    if (encfindspec(
                                            cdata[cc].continuous_action.item,
                                            49))
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 8),
                                            calcfixlv(
                                                (rnd(4) == 0)
                                                    ? Quality::miracle
                                                    : Quality::great));
                                    }
                                    else
                                    {
                                        flt(calcobjlv(
                                                cdata[cc].quality_of_performance
                                                / 10),
                                            calcfixlv(Quality::good));
                                    }
                                    flttypemajor = choice(fsetperform);
                                    dbid = 0;
                                    if (game_data.executing_immediate_quest_type
                                        == 1009)
                                    {
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 241;
                                        }
                                        if (rnd(150) == 0)
                                        {
                                            dbid = 622;
                                        }
                                        if (cdata[tc].level > 15)
                                        {
                                            if (rnd(1000) == 0)
                                            {
                                                dbid = 725;
                                            }
                                        }
                                        if (cdata[tc].level > 10)
                                        {
                                            if (rnd(800) == 0)
                                            {
                                                dbid = 726;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (rnd(10) == 0)
                                        {
                                            dbid = 724;
                                        }
                                        if (rnd(250) == 0)
                                        {
                                            dbid = 55;
                                        }
                                    }
                                    int stat = itemcreate(-1, dbid, x, y, 1);
                                    if (stat != 0)
                                    {
                                        // NOTE: may cause Lua creation
                                        // callbacks to run twice.
                                        inv[ci].modify_number(-1);
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ccbk = cc;
                                        cc = tc;
                                        ThrowingObjectAnimation(
                                            inv[ci].position,
                                            cdata[cc].position,
                                            inv[ci].image,
                                            inv[ci].color)
                                            .play();
                                        cc = ccbk;
                                        inv[ci].modify_number(1);
                                        cell_refresh(
                                            inv[ci].position.x,
                                            inv[ci].position.y);
                                        ++performtips;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (gold != 0)
            {
                cdata[cc].tip_gold += gold;
                if (is_in_fov(cdata[cc]))
                {
                    snd("core.getgold1");
                }
            }
        }
        return;
    }

    if (cc == 0)
    {
        int quality = 0;
        if (cdata[cc].quality_of_performance < 0)
        {
            quality = 0;
        }
        else if (cdata[cc].quality_of_performance < 20)
        {
            quality = 1;
        }
        else if (cdata[cc].quality_of_performance < 40)
        {
            quality = 2;
        }
        else if (cdata[cc].quality_of_performance == 40)
        {
            quality = 3;
        }
        else if (cdata[cc].quality_of_performance < 60)
        {
            quality = 4;
        }
        else if (cdata[cc].quality_of_performance < 80)
        {
            quality = 5;
        }
        else if (cdata[cc].quality_of_performance < 100)
        {
            quality = 6;
        }
        else if (cdata[cc].quality_of_performance < 120)
        {
            quality = 7;
        }
        else if (cdata[cc].quality_of_performance < 150)
        {
            quality = 8;
        }
        else
        {
            quality = 9;
        }
        txt(i18n::s.get_enum("core.locale.activity.perform.quality", quality));
    }

    if (cdata[cc].quality_of_performance > 40)
    {
        cdata[cc].quality_of_performance = cdata[cc].quality_of_performance
            * (100 + inv[cdata[cc].continuous_action.item].param1 / 5) / 100;
    }
    if (cdata[cc].tip_gold != 0)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.activity.perform.tip",
                cdata[cc],
                cdata[cc].tip_gold));
        }
    }
    cdata[cc].continuous_action.finish();
    int experience = cdata[cc].quality_of_performance - sdata(183, cc) + 50;
    if (experience > 0)
    {
        chara_gain_skill_exp(cdata[cc], 183, experience, 0, 0);
    }
}

void continuous_action_sex()
{
    int sexhost = 0;
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::sex;
        cdata[cc].continuous_action.turn = 25 + rnd(10);
        cdata[cc].continuous_action_target = tc;
        cdata[tc].continuous_action.type = ContinuousAction::Type::sex;
        cdata[tc].continuous_action.turn = cdata[cc].continuous_action.turn * 2;
        cdata[tc].continuous_action_target = cc + 10000;
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.activity.sex.take_clothes_off", cdata[cc]));
        }
        return;
    }
    sexhost = 1;
    tc = cdata[cc].continuous_action_target;
    if (tc >= 10000)
    {
        tc -= 10000;
        sexhost = 0;
    }
    if (cdata[tc].state() != Character::State::alive
        || cdata[tc].continuous_action.type != ContinuousAction::Type::sex)
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get(
                "core.locale.activity.sex.spare_life",
                i18n::_(u8"ui", u8"sex2", u8"_"s + cdata[tc].sex),
                cdata[tc]));
        }
        cdata[cc].continuous_action.finish();
        cdata[tc].continuous_action.finish();
        return;
    }
    if (cc == 0)
    {
        if (!action_sp(cdata.player(), 1 + rnd(2)))
        {
            txt(i18n::s.get("core.locale.magic.common.too_exhausted"));
            cdata[cc].continuous_action.finish();
            cdata[tc].continuous_action.finish();
            return;
        }
    }
    cdata[cc].emotion_icon = 317;
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (sexhost == 0)
        {
            if (cdata[cc].continuous_action.turn % 5 == 0)
            {
                if (is_in_fov(cdata[cc]))
                {
                    txt(i18n::s.get("core.locale.activity.sex.dialog"),
                        Message::color{ColorIndex::cyan});
                }
            }
        }
        return;
    }
    if (sexhost == 0)
    {
        cdata[cc].continuous_action.finish();
        return;
    }
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        int c{};
        if (cnt == 0)
        {
            c = cc;
        }
        else
        {
            c = tc;
        }
        cdata[cc].drunk = 0;
        if (cnt == 1)
        {
            if (rnd(3) == 0)
            {
                dmgcon(c, StatusAilment::insane, 500);
            }
            if (rnd(5) == 0)
            {
                dmgcon(c, StatusAilment::paralyzed, 500);
            }
            dmgcon(c, StatusAilment::insane, 300);
            heal_insanity(cdata[c], 10);
            chara_gain_skill_exp(cdata[c], 11, 250 + (c >= 57) * 1000);
            chara_gain_skill_exp(cdata[c], 15, 250 + (c >= 57) * 1000);
        }
        if (rnd(15) == 0)
        {
            dmgcon(c, StatusAilment::sick, 200);
        }
        chara_gain_skill_exp(cdata[c], 17, 250 + (c >= 57) * 1000);
    }
    sexvalue = sdata(17, cc) * (50 + rnd(50)) + 100;

    std::string dialog_head;
    std::string dialog_tail;
    std::string dialog_after;

    if (is_in_fov(cdata[cc]))
    {
        dialog_head =
            i18n::s.get("core.locale.activity.sex.after_dialog", cdata[tc]);
        Message::instance().txtef(ColorIndex::yellow_green);
    }
    if (tc != 0)
    {
        if (cdata[tc].gold >= sexvalue)
        {
            if (is_in_fov(cdata[cc]))
            {
                dialog_tail =
                    i18n::s.get("core.locale.activity.sex.take", cdata[tc]);
            }
        }
        else
        {
            if (is_in_fov(cdata[cc]))
            {
                dialog_tail = i18n::s.get(
                    "core.locale.activity.sex.take_all_i_have", cdata[tc]);
                if (rnd(3) == 0)
                {
                    if (cc != 0)
                    {
                        dialog_after = i18n::s.get(
                            "core.locale.activity.sex.gets_furious", cdata[cc]);
                        cdata[cc].enemy_id = tc;
                        cdata[cc].hate = 20;
                    }
                }
            }
            if (cdata[tc].gold <= 0)
            {
                cdata[tc].gold = 1;
            }
            sexvalue = cdata[tc].gold;
        }
        cdata[tc].gold -= sexvalue;
        if (cc == 0)
        {
            chara_modify_impression(cdata[tc], 5);
            flt();
            itemcreate(
                -1, 54, cdata[cc].position.x, cdata[cc].position.y, sexvalue);
            dialog_after += i18n::s.get(
                "core.locale.common.something_is_put_on_the_ground");
            modify_karma(cdata.player(), -1);
        }
        else
        {
            earn_gold(cdata[cc], sexvalue);
        }
    }
    if (!dialog_head.empty() || !dialog_tail.empty() || !dialog_after.empty())
    {
        txt(i18n::s.get(
                "core.locale.activity.sex.format", dialog_head, dialog_tail)
            + dialog_after);
    }
    cdata[cc].continuous_action.finish();
    cdata[tc].continuous_action.finish();
}


void continuous_action_eating()
{
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::eat;
        cdata[cc].continuous_action.turn = 8;
        cdata[cc].continuous_action.item = ci;
        if (is_in_fov(cdata[cc]))
        {
            snd("core.eat1");
            if (inv[ci].own_state == 1 && cc < 16)
            {
                txt(i18n::s.get(
                    "core.locale.activity.eat.start.in_secret",
                    cdata[cc],
                    inv[ci]));
            }
            else
            {
                txt(i18n::s.get(
                    "core.locale.activity.eat.start.normal",
                    cdata[cc],
                    inv[ci]));
            }
            if (inv[ci].id == 204 && inv[ci].subname == 344)
            {
                txt(i18n::s.get("core.locale.activity.eat.start.mammoth"));
            }
        }
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        return;
    }
    if (is_in_fov(cdata[cc]))
    {
        txt(i18n::s.get("core.locale.activity.eat.finish", cdata[cc], inv[ci]));
    }
    continuous_action_eating_finish();
    cdata[cc].continuous_action.finish();
}



void continuous_action_eating_finish()
{
    // `ci` may be overwritten in apply_general_eating_effect() call. E.g.,
    // vomit is created.
    const auto ci_save = ci;
    apply_general_eating_effect(ci);
    ci = ci_save;
    if (cc == 0)
    {
        item_identify(inv[ci], IdentifyState::partly_identified);
    }
    if (chara_unequip(ci))
    {
        chara_refresh(cc);
    }
    inv[ci].modify_number(-1);
    if (cc == 0)
    {
        show_eating_message();
    }
    else
    {
        if (ci == cdata[cc].item_which_will_be_used)
        {
            cdata[cc].item_which_will_be_used = 0;
        }
        if (cdata[cc].was_passed_item_by_you_just_now())
        {
            if (inv[ci].material == 35)
            {
                if (inv[ci].param3 < 0)
                {
                    txt(i18n::s.get("core.locale.food.passed_rotten"),
                        Message::color{ColorIndex::cyan});
                    damage_hp(cdata[cc], 999, -12);
                    if (cdata[cc].state() != Character::State::alive)
                    {
                        if (cdata[cc].relationship > 0)
                        {
                            modify_karma(cdata.player(), -5);
                        }
                        else
                        {
                            modify_karma(cdata.player(), -1);
                        }
                    }
                    chara_modify_impression(cdata[tc], -25);
                    return;
                }
            }
        }
    }
    chara_anorexia(cdata[cc]);
    if ((inv[ci].id == 755 && rnd(3)) || (inv[ci].id == 756 && rnd(10) == 0))
    {
        if (is_in_fov(cdata[cc]))
        {
            txt(i18n::s.get("core.locale.food.mochi.chokes", cdata[cc]),
                Message::color{ColorIndex::purple});
            txt(i18n::s.get("core.locale.food.mochi.dialog"));
        }
        ++cdata[cc].choked;
    }
}

void continuous_action_others()
{
    if (cc != 0)
    {
        cdata[cc].continuous_action.finish();
        return;
    }
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::others;
        cdata[cc].continuous_action.item = ci;
        cdata[cc].continuous_action_target = tc;
        if (game_data.continuous_action_about_to_start == 105)
        {
            txt(i18n::s.get("core.locale.activity.steal.start", inv[ci]));
            cdata[cc].continuous_action.turn =
                2 + clamp(inv[ci].weight / 500, 0, 50);
        }
        if (game_data.continuous_action_about_to_start == 100)
        {
            if (map_data.type == mdata_t::MapType::player_owned
                || map_is_town_or_guild())
            {
                txt(i18n::s.get("core.locale.activity.sleep.start.other"));
                cdata[cc].continuous_action.turn = 5;
            }
            else
            {
                txt(i18n::s.get("core.locale.activity.sleep.start.global"));
                cdata[cc].continuous_action.turn = 20;
            }
        }
        if (game_data.continuous_action_about_to_start == 101)
        {
            txt(i18n::s.get("core.locale.activity.construct.start", inv[ci]));
            cdata[cc].continuous_action.turn = 25;
        }
        if (game_data.continuous_action_about_to_start == 102)
        {
            txt(i18n::s.get("core.locale.activity.pull_hatch.start", inv[ci]));
            cdata[cc].continuous_action.turn = 10;
        }
        if (game_data.continuous_action_about_to_start == 103)
        {
            txt(i18n::s.get("core.locale.activity.dig", inv[ci]));
            cdata[cc].continuous_action.turn = 10
                + clamp(inv[ci].weight
                            / (1 + sdata(10, 0) * 10 + sdata(180, 0) * 40),
                        1,
                        100);
        }
        if (game_data.continuous_action_about_to_start == 104)
        {
            if (game_data.weather == 0 || game_data.weather == 3)
            {
                if (game_data.time_when_textbook_becomes_available
                    > game_data.date.hours())
                {
                    txt(i18n::s.get("core.locale.activity.study.start.bored"));
                    cdata[cc].continuous_action.finish();
                    return;
                }
            }
            game_data.time_when_textbook_becomes_available =
                game_data.date.hours() + 48;
            if (inv[ci].id == 563)
            {
                txt(i18n::s.get(
                    "core.locale.activity.study.start.studying",
                    i18n::_(
                        u8"ability",
                        std::to_string(inv[ci].param1),
                        u8"name")));
            }
            else
            {
                txt(i18n::s.get("core.locale.activity.study.start.training"));
            }
            if (game_data.weather != 0 && game_data.weather != 3)
            {
                if (game_data.current_map == mdata_t::MapId::shelter_
                    || map_can_use_bad_weather_in_study())
                {
                    txt(i18n::s.get(
                        "core.locale.activity.study.start.weather_is_bad"));
                }
            }
            cdata[cc].continuous_action.turn = 50;
        }
        update_screen();
        return;
    }
    tc = cdata[cc].continuous_action_target;
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (game_data.continuous_action_about_to_start == 103)
        {
            if (rnd(5) == 0)
            {
                chara_gain_skill_exp(cdata.player(), 180, 20, 4);
            }
            if (rnd(6) == 0)
            {
                if (rnd(55) > sdata.get(10, cc).original_level + 25)
                {
                    chara_gain_skill_exp(cdata[cc], 10, 50);
                }
            }
            if (rnd(8) == 0)
            {
                if (rnd(55) > sdata.get(11, cc).original_level + 28)
                {
                    chara_gain_skill_exp(cdata[cc], 11, 50);
                }
            }
            if (rnd(10) == 0)
            {
                if (rnd(55) > sdata.get(15, cc).original_level + 30)
                {
                    chara_gain_skill_exp(cdata[cc], 15, 50);
                }
            }
            if (rnd(4) == 0)
            {
                txt(i18n::s.get("core.locale.activity.harvest.sound"),
                    Message::color{ColorIndex::cyan});
            }
        }
        if (game_data.continuous_action_about_to_start == 104)
        {
            p = 25;
            if (game_data.weather != 0 && game_data.weather != 3)
            {
                if (game_data.current_map == mdata_t::MapId::shelter_)
                {
                    p = 5;
                }
                if (map_can_use_bad_weather_in_study())
                {
                    p = 5;
                    game_data.date.minute += 30;
                }
            }
            if (inv[ci].id == 563)
            {
                if (rnd(p(0)) == 0)
                {
                    chara_gain_skill_exp(cdata[cc], inv[ci].param1, 25);
                }
            }
            else if (rnd(p(0)) == 0)
            {
                chara_gain_skill_exp(cdata[cc], randattb(), 25);
            }
        }
        if (game_data.continuous_action_about_to_start == 105)
        {
            if (inv[ci].id == 688)
            {
                if (rnd(15) == 0)
                {
                    cdata[cc].continuous_action.finish();
                    txt(i18n::s.get("core.locale.activity.iron_maiden"));
                    damage_hp(cdata[cc], 9999, -18);
                    return;
                }
            }
            if (inv[ci].id == 689)
            {
                if (rnd(15) == 0)
                {
                    cdata[cc].continuous_action.finish();
                    txt(i18n::s.get("core.locale.activity.guillotine"));
                    damage_hp(cdata[cc], 9999, -19);
                    return;
                }
            }
            f = 0;
            f2 = 0;
            tg = inv_getowner(ci);
            if (tg != -1)
            {
                if (cdata[tg].original_relationship == -3)
                {
                    f2 = 1;
                }
            }
            i = sdata(300, 0) * 5 + sdata(12, 0) + 25;
            if (game_data.date.hour >= 19 || game_data.date.hour < 7)
            {
                i = i * 15 / 10;
            }
            if (inv[ci].quality == Quality::great)
            {
                i = i * 8 / 10;
            }
            if (inv[ci].quality >= Quality::miracle)
            {
                i = i * 5 / 10;
            }
            make_sound(
                cdata.player().position.x, cdata.player().position.y, 5, 8);
            for (int cnt = 16; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state() != Character::State::alive)
                {
                    continue;
                }
                if (cdata[cnt].sleep != 0)
                {
                    continue;
                }
                if (dist(
                        cdata[cnt].position.x,
                        cdata[cnt].position.y,
                        cdata.player().position.x,
                        cdata.player().position.y)
                    > 5)
                {
                    continue;
                }
                if (f2 == 1)
                {
                    if (cnt != tg)
                    {
                        continue;
                    }
                }
                p = rnd((i + 1))
                    * (80 + (is_in_fov(cdata[cnt]) == 0) * 50
                       + dist(
                             cdata[cnt].position.x,
                             cdata[cnt].position.y,
                             cdata.player().position.x,
                             cdata.player().position.y)
                           * 20)
                    / 100;
                if (cnt < 57)
                {
                    p = p * 2 / 3;
                }
                if (rnd(sdata(13, cnt) + 1) > p)
                {
                    if (is_in_fov(cdata[cnt]))
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.notice.in_fov",
                            cdata[cnt]));
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.notice.out_of_fov",
                            cdata[cnt]));
                    }
                    if (cdata[cnt].character_role == 14)
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.notice.dialog.guard"));
                        chara_modify_impression(cdata[cnt], -5);
                    }
                    else
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.notice.dialog.other"));
                        chara_modify_impression(cdata[cnt], -5);
                    }
                    cdata[cnt].emotion_icon = 520;
                    f = 1;
                }
            }
            if (f)
            {
                txt(i18n::s.get(
                    "core.locale.activity.steal.notice.you_are_found"));
                modify_karma(cdata.player(), -5);
                p = inv_getowner(ci);
                if (tg != -1)
                {
                    if (cdata[p].id != 202)
                    {
                        if (cdata[tg].sleep == 0)
                        {
                            cdata[tg].relationship = -2;
                            hostileaction(0, tg);
                            chara_modify_impression(cdata[tg], -20);
                        }
                    }
                }
                go_hostile();
            }
            if (tg != -1)
            {
                if (cdata[tg].state() != Character::State::alive)
                {
                    if (f != 1)
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.target_is_dead"));
                        f = 1;
                    }
                }
                if (cdata[tg].character_role == 20)
                {
                    if (f != 1)
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.cannot_be_stolen"));
                        f = 1;
                    }
                }
                if (dist(
                        cdata[cc].position.x,
                        cdata[cc].position.y,
                        cdata[tg].position.x,
                        cdata[tg].position.y)
                    >= 3)
                {
                    if (f != 1)
                    {
                        txt(i18n::s.get(
                            "core.locale.activity.steal.you_lose_the_target"));
                        f = 0;
                    }
                }
            }
            if (inv[ci].number() <= 0)
            {
                f = 1;
            }
            if (ibit(5, ci) == 1)
            {
                if (f != 1)
                {
                    txt(i18n::s.get(
                        "core.locale.activity.steal.cannot_be_stolen"));
                    f = 1;
                }
            }
            if (inv[ci].weight >= sdata(10, 0) * 500)
            {
                if (f != 1)
                {
                    txt(i18n::s.get(
                        "core.locale.activity.steal.it_is_too_heavy"));
                    f = 1;
                }
            }
            if (itemusingfind(ci, true) != -1)
            {
                if (f != 1)
                {
                    txt(i18n::s.get(
                        "core.locale.action.someone_else_is_using"));
                    f = 1;
                }
            }
            if (f)
            {
                txt(i18n::s.get("core.locale.activity.steal.abort"));
                cdata[cc].continuous_action.finish();
            }
        }
        return;
    }
    if (game_data.continuous_action_about_to_start == 105)
    {
        tg = inv_getowner(ci);
        if ((tg != -1 && cdata[tg].state() != Character::State::alive)
            || inv[ci].number() <= 0)
        {
            txt(i18n::s.get("core.locale.activity.steal.abort"));
            cdata[cc].continuous_action.finish();
            return;
        }
        in = 1;
        if (inv[ci].id == 54)
        {
            in = inv[ci].number();
        }
        ti = inv_getfreeid(0);
        if (ti == -1)
        {
            txt(i18n::s.get(
                "core.locale.action.pick_up.your_inventory_is_full"));
            return;
        }
        ibitmod(12, ci, 0);
        if (inv[ci].body_part != 0)
        {
            tc = inv_getowner(ci);
            if (tc != -1)
            {
                p = inv[ci].body_part;
                cdata[tc].body_parts[p - 100] =
                    cdata[tc].body_parts[p - 100] / 10000 * 10000;
            }
            inv[ci].body_part = 0;
            chara_refresh(tc);
        }
        item_copy(ci, ti);
        inv[ti].set_number(in);
        ibitmod(9, ti, 1);
        inv[ti].own_state = 0;
        inv[ci].modify_number((-in));
        if (inv[ci].number() <= 0)
        {
            cell_refresh(inv[ci].position.x, inv[ci].position.y);
        }
        txt(i18n::s.get("core.locale.activity.steal.succeed", inv[ti]));
        if (inv[ci].id == 54)
        {
            snd("core.getgold1");
            earn_gold(cdata.player(), in);
            inv[ti].remove();
        }
        else
        {
            item_stack(0, ti, 1);
            sound_pick_up();
        }
        refresh_burden_state();
        chara_gain_skill_exp(
            cdata.player(), 300, clamp(inv[ti].weight / 25, 0, 450) + 50);
        if (cdata.player().karma >= -30)
        {
            if (rnd(3) == 0)
            {
                txt(i18n::s.get("core.locale.activity.steal.guilt"));
                modify_karma(cdata.player(), -1);
            }
        }
    }
    if (game_data.continuous_action_about_to_start == 100)
    {
        txt(i18n::s.get("core.locale.activity.sleep.finish"));
        sleep_start();
    }
    if (game_data.continuous_action_about_to_start == 101)
    {
        snd("core.build1");
        txt(i18n::s.get("core.locale.activity.construct.finish", inv[ci]));
        item_build_shelter(inv[ci]);
    }
    if (game_data.continuous_action_about_to_start == 102)
    {
        txt(i18n::s.get("core.locale.activity.pull_hatch.finish"));
        chatteleport = 1;
        game_data.previous_map2 = game_data.current_map;
        game_data.previous_dungeon_level = game_data.current_dungeon_level;
        game_data.previous_x = cdata.player().position.x;
        game_data.previous_y = cdata.player().position.y;
        game_data.destination_map = 30;
        game_data.destination_dungeon_level = inv[ci].count;
        levelexitby = 2;
        snd("core.exitmap1");
    }
    if (game_data.continuous_action_about_to_start == 103)
    {
        txt(i18n::s.get(
            "core.locale.activity.harvest.finish",
            inv[ci],
            cnvweight(inv[ci].weight)));
        in = inv[ci].number();
        pick_up_item();
    }
    if (game_data.continuous_action_about_to_start == 104)
    {
        if (inv[ci].id == 563)
        {
            txt(i18n::s.get(
                "core.locale.activity.study.finish.studying",
                i18n::_(
                    u8"ability", std::to_string(inv[ci].param1), u8"name")));
        }
        else
        {
            txt(i18n::s.get("core.locale.activity.study.finish.training"));
        }
    }
    cdata[cc].continuous_action.finish();
}


void select_random_fish()
{
    if (rowactre != 0)
    {
        return;
    }
    ci = cdata.player().continuous_action.item;
    int dbmax = 0;
    int dbsum = 0;
    for (const auto fish : the_fish_db)
    {
        if (fish.no_generate)
        {
            continue;
        }
        i = clamp(inv[ci].param4 + (rnd(5) == 0) - (rnd(5) == 0), 0, 5);
        if (fish.rank != i)
        {
            continue;
        }
        dblist(0, dbmax) = fish.id;
        dblist(1, dbmax) = fish.rarity + dbsum;
        dbsum += fish.rarity;
        ++dbmax;
    }
    fish = 1;
    if (dbsum != 0)
    {
        const auto dbtmp = rnd(dbsum);
        for (int cnt = 0, cnt_end = (dbmax); cnt < cnt_end; ++cnt)
        {
            if (dblist(1, cnt) > dbtmp)
            {
                fish = dblist(0, cnt);
                break;
            }
        }
    }
}



void get_fish()
{
    flt();
    itemcreate(0, the_fish_db[fish]->item_id, -1, -1, 0);
    inv[ci].subname = fish;
    inv[ci].value = the_fish_db[fish]->value;
    inv[ci].weight = the_fish_db[fish]->weight;
    txt(i18n::s.get("core.locale.activity.fishing.get", inv[ci]));
    item_stack(0, ci, 1);
}



void spot_fishing()
{
    static int fishstat;

    if (!cdata[cc].continuous_action)
    {
        txt(i18n::s.get("core.locale.activity.fishing.start"));
        snd("core.fish_cast");
        if (rowactre == 0)
        {
            cdata[cc].continuous_action.item = ci;
        }
        cdata[cc].continuous_action.type = ContinuousAction::Type::fish;
        cdata[cc].continuous_action.turn = 100;
        racount = 0;
        fishstat = 0;
        gsel(9);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"fishing.bmp");
        gsel(0);
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (rnd(5) == 0)
        {
            fishstat = 1;
            select_random_fish();
        }
        if (fishstat == 1)
        {
            if (rnd(5) == 0)
            {
                if (Config::instance().animewait != 0)
                {
                    for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end;
                         ++cnt)
                    {
                        fishanime(0) = 1;
                        fishanime(1) = 3 + rnd(3);
                        addefmap(fishx, fishy, 4, 2);
                        ++scrturn;
                        update_screen();
                        redraw();
                        await(Config::instance().animewait * 2);
                    }
                }
                if (rnd(3) == 0)
                {
                    fishstat = 2;
                }
                if (rnd(6) == 0)
                {
                    fishstat = 0;
                }
                fishanime = 0;
            }
        }
        if (fishstat == 2)
        {
            fishanime = 2;
            snd("core.water2");
            cdata.player().emotion_icon = 220;
            if (Config::instance().animewait != 0)
            {
                for (int cnt = 0, cnt_end = (8 + rnd(10)); cnt < cnt_end; ++cnt)
                {
                    ++scrturn;
                    update_screen();
                    redraw();
                    await(Config::instance().animewait * 2);
                }
            }
            if (rnd(10))
            {
                fishstat = 3;
            }
            else
            {
                fishstat = 0;
            }
            fishanime = 0;
        }
        if (fishstat == 3)
        {
            fishanime = 3;
            if (Config::instance().animewait != 0)
            {
                for (int cnt = 0, cnt_end = (28 + rnd(15)); cnt < cnt_end;
                     ++cnt)
                {
                    if (cnt % 7 == 0)
                    {
                        snd("core.fish_fight");
                    }
                    fishanime(1) = cnt;
                    ++scrturn;
                    update_screen();
                    addefmap(fishx, fishy, 5, 2);
                    redraw();
                    await(Config::instance().animewait * 2);
                }
            }
            if (the_fish_db[fish]->difficulty >= rnd(sdata(185, 0) + 1))
            {
                fishstat = 0;
            }
            else
            {
                fishstat = 4;
            }
            fishanime = 0;
        }
        if (fishstat == 4)
        {
            fishanime = 4;
            snd("core.fish_get");
            if (Config::instance().animewait != 0)
            {
                for (int cnt = 0; cnt < 21; ++cnt)
                {
                    fishanime(1) = cnt;
                    if (cnt == 1)
                    {
                        addefmap(fishx, fishy, 1, 3);
                    }
                    ++scrturn;
                    update_screen();
                    redraw();
                    await(Config::instance().animewait * 2);
                }
            }
            sound_pick_up();
            fishanime = 0;
            cdata[cc].continuous_action.finish();
            get_fish();
            gain_fishing_experience(0);
            cdata.player().emotion_icon = 306;
        }
        if (rnd(10) == 0)
        {
            damage_sp(cdata[cc], 1);
        }
        return;
    }
    txt(i18n::s.get("core.locale.activity.fishing.fail"));
    cdata[cc].continuous_action.finish();
}



void spot_material()
{
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type =
            ContinuousAction::Type::search_material;
        cdata[cc].continuous_action.turn = 40;
        txt(i18n::s.get("core.locale.activity.material.start"));
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    cdata[cc].continuous_action.finish();
}



void spot_digging()
{
    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::dig_ground;
        cdata[cc].continuous_action.turn = 20;
        if (rowactre == 0)
        {
            txt(i18n::s.get("core.locale.activity.dig_spot.start.global"));
        }
        else
        {
            txt(i18n::s.get("core.locale.activity.dig_spot.start.other"));
        }
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (cdata[cc].turn % 5 == 0)
        {
            txt(i18n::s.get("core.locale.activity.dig_spot.sound"),
                Message::color{ColorIndex::blue});
        }
        return;
    }
    txt(i18n::s.get("core.locale.activity.dig_spot.finish"));
    if (map_data.type == mdata_t::MapType::world_map)
    {
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number() == 0)
            {
                continue;
            }
            if (inv[cnt].id == 621)
            {
                if (inv[cnt].param1 != 0)
                {
                    if (inv[cnt].param1 == cdata.player().position.x)
                    {
                        if (inv[cnt].param2 == cdata.player().position.y)
                        {
                            snd("core.chest1");
                            txt(i18n::s.get("core.locale.activity.dig_spot."
                                            "something_is_there"),
                                Message::color{ColorIndex::orange});
                            msg_halt();
                            snd("core.ding2");
                            flt();
                            itemcreate(
                                -1,
                                622,
                                cdata.player().position.x,
                                cdata.player().position.y,
                                2 + rnd(3));
                            flt();
                            itemcreate(
                                -1,
                                55,
                                cdata.player().position.x,
                                cdata.player().position.y,
                                1 + rnd(3));
                            flt();
                            itemcreate(
                                -1,
                                54,
                                cdata.player().position.x,
                                cdata.player().position.y,
                                rnd(10000) + 2000);
                            for (int cnt = 0, cnt_end = (4); cnt < cnt_end;
                                 ++cnt)
                            {
                                flt(calcobjlv(cdata.player().level + 10),
                                    calcfixlv(Quality::good));
                                if (cnt == 0)
                                {
                                    fixlv = Quality::godly;
                                }
                                flttypemajor = choice(fsetchest);
                                itemcreate(
                                    -1,
                                    0,
                                    cdata.player().position.x,
                                    cdata.player().position.y,
                                    0);
                            }
                            txt(
                                i18n::s.get("core.locale.common.something_is_"
                                            "put_on_the_ground"));
                            autosave = 1
                                * (game_data.current_map
                                   != mdata_t::MapId::show_house);
                            inv[cnt].modify_number(-1);
                            break;
                        }
                    }
                }
            }
        }
    }
    spillfrag(refx, refy, 1);
    cdata[cc].continuous_action.finish();
}



void spot_mining_or_wall()
{
    static int countdig{};

    if (!cdata[cc].continuous_action)
    {
        cdata[cc].continuous_action.type = ContinuousAction::Type::dig_wall;
        cdata[cc].continuous_action.turn = 40;
        if (rowactre == 0)
        {
            txt(i18n::s.get("core.locale.activity.dig_mining.start.wall"));
        }
        else
        {
            txt(i18n::s.get("core.locale.activity.dig_mining.start.spot"));
        }
        if (chipm(0, cell_data.at(refx, refy).chip_id_actual) == 6)
        {
            txt(i18n::s.get("core.locale.activity.dig_mining.start.hard"));
        }
        countdig = 0;
        racount = 0;
        return;
    }
    if (rowactre != 0)
    {
        search_material_spot();
        return;
    }
    if (cdata[cc].continuous_action.turn > 0)
    {
        if (rnd(5) == 0)
        {
            damage_sp(cdata[cc], 1);
        }
        ++countdig;
        f = 0;
        if (chipm(0, cell_data.at(refx, refy).chip_id_actual) == 6)
        {
            if (rnd(12000) < sdata(10, cc) + sdata(163, cc) * 10)
            {
                f = 1;
            }
            p = 30 - sdata(163, cc) / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        else
        {
            if (rnd(1500) < sdata(10, cc) + sdata(163, cc) * 10)
            {
                f = 1;
            }
            p = 20 - sdata(163, cc) / 2;
            if (p > 0)
            {
                if (countdig <= p)
                {
                    f = 0;
                }
            }
        }
        if (f == 1
            || (game_data.quest_flags.tutorial == 2
                && game_data.current_map == mdata_t::MapId::your_home))
        {
            rtval = 0;
            if (rnd(5) == 0)
            {
                rtval = 54;
            }
            if (rnd(8) == 0)
            {
                rtval = -1;
            }
            if (cell_data.at(refx, refy).feats != 0)
            {
                cell_featread(refx, refy);
                if (feat(1) == 22)
                {
                    discover_hidden_path();
                }
            }
            cell_data.at(refx, refy).chip_id_actual = tile_tunnel;
            spillfrag(refx, refy, 2);
            snd("core.crush1");
            BreakingAnimation({refx, refy}).play();
            txt(i18n::s.get("core.locale.activity.dig_mining.finish.wall"));
            if (game_data.quest_flags.tutorial == 2
                && game_data.current_map == mdata_t::MapId::your_home)
            {
                flt();
                itemcreate(-1, 208, digx, digy, 0);
                inv[ci].curse_state = CurseState::cursed;
                txt(i18n::s.get("core.locale.activity.dig_mining.finish.find"));
                game_data.quest_flags.tutorial = 3;
            }
            else if (
                rtval != 0 && game_data.current_map != mdata_t::MapId::shelter_)
            {
                if (rtval > 0)
                {
                    flt();
                    itemcreate(-1, rtval, digx, digy, 0);
                }
                else if (rtval == -1)
                {
                    flt(calcobjlv(game_data.current_dungeon_level),
                        calcfixlv(Quality::good));
                    flttypemajor = 77000;
                    itemcreate(-1, 0, digx, digy, 0);
                }
                txt(i18n::s.get("core.locale.activity.dig_mining.finish.find"));
            }
            gain_digging_experience();
            cdata[cc].continuous_action.finish();
        }
        else if (cdata[cc].turn % 5 == 0)
        {
            txt(i18n::s.get("core.locale.activity.dig_spot.sound"),
                Message::color{ColorIndex::blue});
        }
        return;
    }
    txt(i18n::s.get("core.locale.activity.dig_mining.fail"));
    cdata[cc].continuous_action.finish();
}

TurnResult do_dig_after_sp_check()
{
    if (cdata[cc].sp < 0)
    {
        txt(i18n::s.get("core.locale.action.dig.too_exhausted"));
        update_screen();
        return TurnResult::pc_turn_user_error;
    }
    rowactre = 0;
    digx = tlocx;
    digy = tlocy;
    spot_mining_or_wall();
    return TurnResult::turn_end;
}

int search_material_spot()
{
    if (cell_data.at(cdata.player().position.x, cdata.player().position.y).feats
        == 0)
    {
        return 0;
    }
    if (feat(1) < 24 || 28 < feat(1))
    {
        return 0;
    }
    atxspot = 11;
    atxlv = game_data.current_dungeon_level;
    if (map_data.type == mdata_t::MapType::dungeon)
    {
        atxspot = 9;
    }
    if (map_data.type == mdata_t::MapType::dungeon_tower)
    {
        atxspot = 12;
    }
    if (map_data.type == mdata_t::MapType::dungeon_forest)
    {
        atxspot = 10;
    }
    if (map_data.type == mdata_t::MapType::dungeon_castle)
    {
        atxspot = 12;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        atxlv = cdata.player().level / 2 + rnd(10);
        if (atxlv > 30)
        {
            atxlv = 30 + rnd((rnd(atxlv - 30) + 1));
        }
        if (4 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 9)
        {
            atxspot = 10;
        }
        if (264 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 363)
        {
            atxspot = 11;
        }
        if (9 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 13)
        {
            atxspot = 10;
        }
        if (13 <= game_data.stood_world_map_tile
            && game_data.stood_world_map_tile < 17)
        {
            atxspot = 11;
        }
    }
    cell_featread(cdata.player().position.x, cdata.player().position.y);
    if (feat(1) == 27)
    {
        atxlv += sdata(161, 0) / 3;
        atxspot = 16;
    }
    if (feat(1) == 26)
    {
        atxspot = 13;
    }
    if (feat(1) == 25)
    {
        atxspot = 14;
    }
    if (feat(1) == 28)
    {
        atxspot = 15;
    }
    if (rnd(7) == 0)
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            i = 5;
            if (atxspot == 14)
            {
                if (sdata(163, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(i18n::s.get(
                        "core.locale.activity.material.digging.fails"));
                    break;
                }
                i = 1;
                chara_gain_skill_exp(cdata.player(), 163, 40);
            }
            if (atxspot == 13)
            {
                if (sdata(185, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(i18n::s.get(
                        "core.locale.activity.material.fishing.fails"));
                    break;
                }
                i = 2;
                chara_gain_skill_exp(cdata.player(), 185, 40);
            }
            if (atxspot == 15)
            {
                if (sdata(180, 0) < rnd(atxlv * 2 + 1) || rnd(10) == 0)
                {
                    txt(i18n::s.get(
                        "core.locale.activity.material.searching.fails"));
                    break;
                }
                i = 3;
                chara_gain_skill_exp(cdata.player(), 180, 30);
            }
            matgetmain(random_material(atxlv, 0), 1, i);
        }
    }
    if (rnd(50 + trait(159) * 20) == 0)
    {
        s = i18n::s.get("core.locale.activity.material.searching.no_more");
        if (feat(1) == 26)
        {
            s = i18n::s.get("core.locale.activity.material.fishing.no_more");
        }
        if (feat(1) == 25)
        {
            s = i18n::s.get("core.locale.activity.material.digging.no_more");
        }
        if (feat(1) == 28)
        {
            s = i18n::s.get("core.locale.activity.material.harvesting.no_more");
        }
        txt(s);
        cdata[cc].continuous_action.finish();
        cell_data.at(cdata.player().position.x, cdata.player().position.y)
            .feats = 0;
    }
    return 0;
}



void matgetmain(int material_id, int amount, int spot_type)
{
    if (amount == 0)
    {
        amount = 1;
    }
    mat(material_id) += amount;
    snd("core.alert1");

    std::string verb;
    switch (spot_type)
    {
    case 0:
        verb = i18n::s.get("core.locale.activity.material.get_verb.get");
        break;
    case 1:
        verb = i18n::s.get("core.locale.activity.material.get_verb.dig_up");
        break;
    case 2:
        verb = i18n::s.get("core.locale.activity.material.get_verb.fish_up");
        break;
    case 3:
        verb = i18n::s.get("core.locale.activity.material.get_verb.harvest");
        break;
    case 5:
        verb = i18n::s.get("core.locale.activity.material.get_verb.find");
        break;
    default:
        verb = i18n::s.get("core.locale.activity.material.get_verb.get");
        break;
    }

    txt(i18n::s.get(
            "core.locale.activity.material.get",
            verb,
            amount,
            matname(material_id))
            + u8"("s + mat(material_id) + u8") "s,
        Message::color{ColorIndex::blue});
}



void matdelmain(int material_id, int amount)
{
    std::string message;
    if (amount == 0)
    {
        amount = 1;
    }
    mat(material_id) -= amount;
    txt(i18n::s.get(
        "core.locale.activity.material.lose", matname(material_id), amount));
    txt(i18n::s.get(
            "core.locale.activity.material.lose_total", mat(material_id)),
        Message::color{ColorIndex::blue});
}


} // namespace elona
