#include "ability.hpp"
#include "adventurer.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "macro.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "talk.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

talk_result_t talk_shop_buy()
{
    invctrl = 11;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_shop_sell()
{
    invctrl = 12;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    cc = 0;
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_inn_eat()
{
    if (cdata[0].gold < calcmealvalue())
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    if (cdata[0].nutrition >= 15000)
    {
        buff = i18n::s.get("core.locale.talk.npc.innkeeper.eat.not_hungry");
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata[0].gold -= calcmealvalue();
    snd(18);
    cdata[0].nutrition = 15000;
    buff = i18n::s.get("core.locale.talk.npc.innkeeper.eat.here_you_are");
    txt(lang(u8"なかなか美味しかった。"s, u8"It was tasty."s),
        lang(u8"悪くない。"s, u8"Not bad at all."s),
        lang(u8"あなたは舌鼓をうった。"s, u8"You smack your lips."s));
    show_eating_message();
    chara_anorexia(0);
    return talk_result_t::talk_npc;
}

talk_result_t talk_wizard_identify(int chatval)
{
    if (cdata[0].gold < calcidentifyvalue(chatval - 14))
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    p = 0;
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].identification_state
            != identification_state_t::completely_identified)
        {
            ++p;
        }
    }
    if (p == 0)
    {
        buff = i18n::s.get("core.locale.talk.npc.wizard.identify.already");
        return talk_result_t::talk_npc;
    }
    if (chatval == 15)
    {
        cdata[0].gold -= calcidentifyvalue(1);
        p(0) = 0;
        p(1) = 0;
        p(0) = 0;
        p(1) = 0;
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number == 0)
            {
                continue;
            }
            if (inv[cnt].identification_state
                != identification_state_t::completely_identified)
            {
                const auto result = item_identify(inv[cnt], 250);
                item_stack(0, cnt, 1);
                ++p(1);
                if (result >= identification_state_t::completely_identified)
                {
                    ++p;
                }
            }
        }
        txt(i18n::s.get("core.locale.talk.npc.wizard.identify.count", p(0), p(1)));
        buff = i18n::s.get("core.locale.talk.npc.wizard.identify.finished");
    }
    else
    {
        if (chatval == 14)
        {
            efp = 250;
        }
        else
        {
            efp = 1000;
        }
        efid = 411;
        magic();
        if (efcancel == 1)
        {
            buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
            return talk_result_t::talk_npc;
        }
        if (idtresult == identification_state_t::completely_identified)
        {
            buff = i18n::s.get("core.locale.talk.npc.wizard.identify.finished");
        }
        else
        {
            buff = i18n::s.get("core.locale.talk.npc.wizard.identify.need_investigate");
        }
        cdata[0].gold -= calcidentifyvalue(chatval - 14);
    }
    snd(12);
    return talk_result_t::talk_npc;
}

talk_result_t talk_informer_list_adventurers()
{
    list_adventurers();
    buff = i18n::s.get("core.locale.talk.npc.informer.show_adventurers");
    return talk_result_t::talk_npc;
}

talk_result_t talk_healer_restore_attributes()
{
    if (cdata[0].gold < calcrestorecost())
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata[0].gold -= calcrestorecost();
    tcbk = tc;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        tc = cnt;
        efid = 439;
        efp = 100;
        magic();
        efid = 440;
        efp = 100;
        magic();
    }
    tc = tcbk;
    talk_start();
    buff = i18n::s.get("core.locale.talk.npc.healer.restore_attributes");
    return talk_result_t::talk_npc;
}

talk_result_t talk_trade()
{
    invsubroutine = 1;
    for (const auto& cnt : items(tc))
    {
        if (inv[cnt].number != 0)
        {
            inv[cnt].identification_state =
                identification_state_t::completely_identified;
        }
    }
    invctrl(0) = 20;
    invctrl(1) = 0;
    menu_result result = ctrl_inventory();
    if (!result.succeeded)
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        return talk_result_t::talk_npc;
    }
    buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    return talk_result_t::talk_npc;
}

talk_result_t talk_arena_master(int chatval)
{
    if (gdata_mount != 0)
    {
        int stat =
            cell_findspace(cdata[0].position.x, cdata[0].position.y, 1);
        if (stat == 0)
        {
            txt(lang(
                    u8"降りるスペースがない。"s,
                    u8"There's no place to get off."s));
            return talk_result_t::talk_end;
        }
        cell_setchara(gdata_mount, rtval, rtval(1));
        txt(lang(
                name(gdata_mount) + u8"から降りた。"s,
                u8"You dismount from "s + name(gdata_mount) + u8"."s));
        ride_end();
    }
    gdata(74) = calcfame(
        0,
        (220 - gdata(120) / 50)
        * (100 + clamp(adata(22, gdata_current_map), 0, 50)) / 100
        + 2);
    listmax = 0;
    randomize(adata(26, gdata_current_map));
    if (chatval == 21)
    {
        if (adata(26, gdata_current_map) > gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
        {
            buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.game_is_over");
            return talk_result_t::talk_npc;
        }
        randomize(adata(24, gdata_current_map));
        for (int cnt = 0; cnt < 50; ++cnt)
        {
            arenaop(0) = 0;
            arenaop(1) = (100 - gdata(120) / 100) / 3 + 1;
            arenaop(2) = 3;
            if (gdata(120) / 100 < 30)
            {
                arenaop(2) = 4;
            }
            if (gdata(120) / 100 < 10)
            {
                arenaop(2) = 5;
            }
            minlevel = arenaop(1) / 3 * 2;
            flt(arenaop(1));
            fixlv = arenaop(2);
            chara_create(56, 0, -3, 0);
            if (cmshade)
            {
                continue;
            }
            if (cdata[rc].level < minlevel)
            {
                continue;
            }
            if (cdata[rc].original_relationship != -3)
            {
                continue;
            }
            break;
        }
        arenaop(1) = cdata[rc].id;
        buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.target",
                           cdata[rc], chara_refstr(cdata[rc].id, 2));
    }
    else
    {
        if (adata(27, gdata_current_map) > gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
        {
            buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.game_is_over");
            return talk_result_t::talk_npc;
        }
        arenaop(0) = 1;
        arenaop(1) = (100 - gdata(120) / 100) / 2 + 1;
        buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.target", arenaop(1));
    }
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.arena_master.choices.enter"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.arena_master.choices.leave"));
    chatesc = 1;
    talk_window_query();
    if (chatval != 1)
    {
        buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.cancel");
        return talk_result_t::talk_npc;
    }
    if (arenaop == 0)
    {
        adata(26, gdata_current_map) = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 24;
    }
    if (arenaop == 1)
    {
        adata(27, gdata_current_map) = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 24;
    }
    gdata_executing_immediate_quest_type = 1;
    gdata(71) = 1;
    gdata_executing_immediate_quest = 0;
    gdata(73) = 1;
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
    gdata_destination_map = 6;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_pet_arena_master(int chatval)
{
    gdata(74) = calcfame(
        0,
        (220 - gdata(121) / 50)
        * (50 + clamp(adata(23, gdata_current_map), 0, 50)) / 100
        + 2);
    listmax = 0;
    if (chatval == 40)
    {
        arenaop(0) = 0;
        arenaop(1) = 1;
        arenaop(2) = (100 - gdata(121) / 100) / 3 * 2 + 3;
        buff = i18n::s.get("core.locale.talk.npc.pet_arena_master.register.target", arenaop(2));
    }
    if (chatval == 41)
    {
        arenaop(0) = 1;
        arenaop(1) = 2;
        arenaop(2) = (100 - gdata(121) / 100) / 2 + 1;
        arenaop(1) = rnd(7) + 2;
        buff = i18n::s.get("core.locale.talk.npc.pet_arena_master.register.target_group",
                           arenaop(1), arenaop(2));
    }
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.pet_arena_master.register.choices.enter"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.pet_arena_master.register.choices.leave"));
    chatesc = 1;
    talk_window_query();
    if (chatval != 1)
    {
        buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.cancel");
        return talk_result_t::talk_npc;
    }
    DIM2(followerexist, 16);
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        followerexist(cnt) = cdata[cnt].state;
    }
    allyctrl = 2;
    int stat = ctrl_ally();
    if (stat == -1)
    {
        buff = i18n::s.get("core.locale.talk.npc.arena_master.enter.cancel");
        return talk_result_t::talk_npc;
    }
    gdata_executing_immediate_quest_type = 2;
    gdata(71) = 0;
    gdata_executing_immediate_quest = 0;
    gdata(73) = 1;
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
    gdata_destination_map = 40;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_pet_arena_master_score()
{
    buff = i18n::s.get("core.locale.talk.npc.arena_master.streak", adata(23, gdata_current_map));
    return talk_result_t::talk_npc;
}

talk_result_t talk_arena_master_score()
{
    buff = i18n::s.get("core.locale.talk.npc.arena_master.streak", adata(22, gdata_current_map));
    return talk_result_t::talk_npc;
}

talk_result_t talk_quest_delivery()
{
    int stat = inv_getfreeid_force();
    ti = stat;
    item_copy(deliver(1), ti);
    inv[ti].number = 1;
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used();
    rq = deliver;
    --inv[deliver(1)].number;
    txt(i18n::s.get("core.locale.talk.npc.quest_giver.hand_over", inv[deliver(1)]));
    quest_set_data(3);
    quest_complete();
    refresh_burden_state();
    return talk_result_t::talk_npc;
}

talk_result_t talk_quest_supply()
{
    int stat = inv_getfreeid_force();
    ti = stat;
    item_copy(supply, ti);
    inv[ti].number = 1;
    cdata[tc].was_passed_item_by_you_just_now() = true;
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used();
    --inv[supply].number;
    txt(i18n::s.get("core.locale.talk.npc.quest_giver.hand_over", inv[supply]));
    quest_set_data(3);
    quest_complete();
    refresh_burden_state();
    return talk_result_t::talk_npc;
}

talk_result_t talk_shop_attack()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.shop.attack.dialog");
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.shop.attack.choices.attack"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.shop.attack.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval != 1)
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        return talk_result_t::talk_npc;
    }
    go_hostile();
    return talk_result_t::talk_end;
}

talk_result_t talk_guard_return_item()
{
    listmax = 0;
    p = itemfind(0, 284);
    if (p == -1)
    {
        p = itemfind(0, 283);
    }
    --inv[p].number;
    if (inv[p].param1 == 0)
    {
        buff = i18n::s.get("core.locale.talk.npc.guard.lost.empty.dialog");
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.guard.lost.empty.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(0, -5);
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.guard.lost.dialog");
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.guard.lost.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(0, 5);
        ++gdata_lost_wallet_count;
        if (gdata_lost_wallet_count >= 4)
        {
            listmax = 0;
            buff = i18n::s.get_enum("core.locale.talk.npc.guard.lost.found_often.dialog", 0);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum("core.locale.talk.npc.guard.lost.found_often.dialog", 1);
            ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.npc.guard.lost.found_often.response"));
            chatesc = 1;
            talk_window_query();
            modify_karma(0, -10);
        }
    }
    refresh_burden_state();
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_bartender_call_ally()
{
    allyctrl = 0;
    int stat = ctrl_ally();
    if (stat != -1)
    {
        rc = stat;
        if (cdata[rc].state == 1)
        {
            buff = i18n::s.get("core.locale.talk.npc.bartender.call_ally.no_need");
            return talk_result_t::talk_npc;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.bartender.call_ally.cost",
                           calcresurrectvalue(rc));
        if (cdata[0].gold >= calcresurrectvalue(rc))
        {
            ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.npc.bartender.call_ally.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.bartender.call_ally.choices.go_back"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            snd(12);
            cdata[0].gold -= calcresurrectvalue(rc);
            buff = i18n::s.get("core.locale.talk.npc.bartender.call_ally.brings_back",
                               cdata[tc], cdata[rc]);
            revive_character();
        }
        else
        {
            buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        }
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_ally_order_wait()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.ally.wait_at_town", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    map(cdata[tc].position.x, cdata[tc].position.y, 1) = 0;
    cdata[tc].state = 7;
    cdata[tc].current_map = 0;
    return talk_result_t::talk_end;
}

talk_result_t talk_ally_abandon()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.ally.abandon.prompt", cdata[tc]);
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.yes"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.no"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        txt(i18n::s.get("core.locale.talk.npc.ally.abandon.you_abandoned", cdata[tc]));
        map(cdata[tc].position.x, cdata[tc].position.y, 1) = 0;
        chara_delete(tc);
        return talk_result_t::talk_end;
    }
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_slave_buy(int chatval)
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        flt(cdata[0].level / 2 + 5);
        fixlv = 2;
        if (chatval == 36)
        {
            fltn(u8"man"s);
        }
        else
        {
            fltn(u8"horse"s);
        }
        chara_create(56, 0, -3, 0);
        if (cdata[56].level == 0)
        {
            chara_vanquish(56);
            continue;
        }
        break;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.slave_keeper.buy.cost",
                       cnven(cdatan(0, 56)), calcslavevalue(56));
    if (cdata[0].gold >= calcslavevalue(56))
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.slave_keeper.buy.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.slave_keeper.buy.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        txt(i18n::s.get("core.locale.talk.npc.slave_keeper.buy.you_buy", cnven(cdatan(0, 56))));
        snd(12);
        cdata[0].gold -= calcslavevalue(56);
        rc = 56;
        new_ally_joins();
        buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_slave_sell()
{
    allyctrl = 1;
    int stat = ctrl_ally();
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.slave_trader.sell.price",
                           (calcslavevalue(rc) * 2 / 3));
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.npc.slave_trader.sell.choices.deal"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.slave_trader.sell.choices.go_back"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            txt(i18n::s.get("core.locale.talk.npc.slave_trader.sell.you_sell_off",
                            cnven(cdatan(0, rc))));
            snd(11);
            cdata[0].gold += calcslavevalue(rc) * 2 / 3;
            if (cdata[rc].state == 1)
            {
                map(cdata[rc].position.x, cdata[rc].position.y, 1) = 0;
            }
            if (cdata[rc].is_escorted() == 1)
            {
                event_add(15, cdata[rc].id);
            }
            chara_delete(rc);
            buff = i18n::s.get("core.locale.talk.npc.common.thanks");
        }
        else
        {
            buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        }
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_ally_marriage()
{
    if (cdata[tc].impression < 200)
    {
        buff = i18n::s.get("core.locale.talk.npc.ally.marriage.refuses", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    cdata[tc].is_married() = true;
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.ally.marriage.accepts");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    marry = tc;
    event_add(13);
    return talk_result_t::talk_end;
}

talk_result_t talk_ally_gene()
{
    if (gdata_current_map == 30)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.ally.make_gene.refuses");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return talk_result_t::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.ally.make_gene.accepts");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    cdata[tc].has_made_gene() = true;
    if (gdata_wizard == 0)
    {
        gdata(98) = tc;
    }
    return talk_result_t::talk_end;
}

talk_result_t talk_innkeeper_shelter()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.innkeeper.go_to_shelter");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
    gdata_destination_map = 30;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    snd(49);
    return talk_result_t::talk_end;
}

talk_result_t talk_servant_fire()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.servant.fire.prompt", cdata[tc]);
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.yes"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.no"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        txt(i18n::s.get("core.locale.talk.npc.servant.fire.you_dismiss", cdata[tc]));
        chara_vanquish(tc);
        calccosthire();
        return talk_result_t::talk_end;
    }
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_maid_think_of_house_name()
{
    mdatan(0) = random_title();
    if (rnd(5))
    {
        mdatan(0) = i18n::s.get_enum("core.locale.talk.npc.maid.think_of_house_name.suffixes",
                                     rnd(11), mdatan(0));
    }
    screenupdate = -1;
    update_entire_screen();
    buff = i18n::s.get("core.locale.talk.npc.maid.think_of_house_name.come_up_with", mdatan(0));
    return talk_result_t::talk_npc;
}

talk_result_t talk_sister_buy_indulgence()
{
    if (cdata[0].karma >= -30)
    {
        buff = i18n::s.get("core.locale.talk.npc.sister.buy_indulgence.karma_is_not_low");
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.sister.buy_indulgence.cost", calcguiltvalue());
    if (cdata[0].gold >= calcguiltvalue())
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.sister.buy_indulgence.choices.buy"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.sister.buy_indulgence.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        snd(12);
        cdata[0].gold -= calcguiltvalue();
        modify_karma(0, (cdata[0].karma - -30) * -1 + 1);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_informer_investigate_ally()
{
    int tcchat = tc;
    allyctrl = 4;
    int stat = ctrl_ally();
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.informer.investigate_ally.cost");
        if (cdata[0].gold >= 10000)
        {
            ELONA_APPEND_RESPONSE(
                1, i18n::s.get("core.locale.talk.npc.informer.investigate_ally.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.informer.investigate_ally.choices.go_back"));
        chatesc = 1;
        talk_window_query();
        if (chatval == 1)
        {
            snd(12);
            cdata[0].gold -= 10000;
            cc = rc;
            csctrl = 4;
            snd(26);
            menu_character_sheet();
            cc = 0;
            talk_start();
            buff = "";
        }
        else
        {
            buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        }
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    tc = tcchat;
    return talk_result_t::talk_npc;
}

talk_result_t talk_ally_silence()
{
    if (cdata[tc].is_silent() == 0)
    {
        cdata[tc].is_silent() = true;
        buff = u8"("s
            + i18n::s.get("core.locale.talk.npc.ally.silence.start", cdata[tc])
            + u8")"s;
    }
    else
    {
        buff = u8"("s
            + i18n::s.get("core.locale.talk.npc.ally.silence.stop", cdata[tc])
            + u8")"s;
        cdata[tc].is_silent() = false;
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_adventurer_hire()
{
    buff = i18n::s.get("core.locale.talk.npc.adventurer.hire.cost", calchireadv(tc));
    if (cdata[0].gold >= calchireadv(tc))
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.adventurer.hire.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.adventurer.hire.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        snd(12);
        cdata[0].gold -= calchireadv(tc);
        cdata[tc].relationship = 10;
        cdata[tc].is_contracting() = true;
        cdata[tc].period_of_contract = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 168;
        ++cdata[tc].hire_count;
        snd(64);
        txtef(5);
        txt(i18n::s.get("core.locale.talk.npc.adventurer.hire.you_hired", cdata[tc]));
        buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_adventurer_join()
{
    if (cdata[0].level * 3 / 2 + 10 < cdata[tc].level)
    {
        buff = i18n::s.get("core.locale.talk.npc.adventurer.join.too_weak");
        return talk_result_t::talk_npc;
    }
    if (cdata[tc].impression >= 200 && cdata[tc].hire_count > 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.npc.adventurer.join.accept");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        f = chara_get_free_slot_ally();
        if (f == 0)
        {
            buff = i18n::s.get("core.locale.talk.npc.adventurer.join.party_full");
            return talk_result_t::talk_npc;
        }
        rc = tc;
        new_ally_joins();
        cdata[rc].character_role = 0;
        cdata[rc].current_map = 0;
        cdata[tc].impression = 100;
        rc = oc;
        create_adventurer();
        return talk_result_t::talk_end;
    }
    buff = i18n::s.get("core.locale.talk.npc.adventurer.join.not_known");
    return talk_result_t::talk_npc;
}

talk_result_t talk_moyer_sell_paels_mom()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.prompt");
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.choices.sell"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        txt(i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.you_sell"));
        modify_karma(0, -20);
        snd(11);
        cdata[0].gold += 50000;
        gdata_pael_and_her_mom = 1002;
        rc = chara_find(222);
        cdata[rc].ai_calm = 3;
        cdata[rc].relationship = 0;
        cdata[rc].initial_position.x = 48;
        cdata[rc].initial_position.y = 18;
        cell_movechara(rc, 48, 18);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_wizard_return()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.wizard.return");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    try_to_return();
    return talk_result_t::talk_end;
}

talk_result_t talk_shop_reload_ammo()
{
    if (calccostreload(0) == 0)
    {
        buff = i18n::s.get("core.locale.talk.npc.shop.ammo.no_ammo");
        return talk_result_t::talk_npc;
    }
    buff = i18n::s.get("core.locale.talk.npc.shop.ammo.cost", calccostreload(0));
    if (cdata[0].gold >= calccostreload(0))
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.shop.ammo.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.shop.ammo.choices.go_back"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        snd(12);
        cdata[0].gold -= calccostreload(0);
        p = calccostreload(0, true);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks");
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_spell_writer_reserve()
{
    screenupdate = -1;
    update_screen();
    invctrl = 0;
    show_spell_writer_menu();
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_sex()
{
    ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.common.sex.choices.accept"));
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.common.sex.choices.go_back"));
    buff = i18n::s.get("core.locale.talk.npc.common.sex.prompt");
    talk_window_query();
    if (chatval != 1)
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.common.sex.start");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.common.sex.response"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    continuous_action_sex();
    return talk_result_t::talk_end;
}

talk_result_t talk_result_maid_chase_out()
{
    --gdata_number_of_waiting_guests;
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.maid.do_not_meet");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_prostitute_buy()
{
    sexvalue = sdata(17, tc) * 25 + 100 + cdata[0].fame / 10;
    if (cdata[0].gold >= sexvalue)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.common.sex.choices.accept"));
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.common.sex.choices.go_back"));
    buff = i18n::s.get("core.locale.talk.npc.prostitute.buy", sexvalue);
    talk_window_query();
    if (chatval != 1)
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata[cc].gold -= sexvalue;
    cdata[tc].gold += sexvalue;
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.common.sex.start");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.locale.talk.npc.common.sex.response"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    cc = tc;
    tc = 0;
    continuous_action_sex();
    cc = 0;
    return talk_result_t::talk_end;
}

talk_result_t talk_caravan_master_hire()
{
    if (gdata_current_map == 43)
    {
        p(0) = 45;
        p(1) = 48;
        p(2) = 0;
    }
    if (gdata_current_map == 45)
    {
        p(0) = 43;
        p(1) = 48;
        p(2) = 0;
    }
    if (gdata_current_map == 48)
    {
        p(0) = 43;
        p(1) = 45;
        p(2) = 0;
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (p(cnt) == 0)
        {
            ELONA_APPEND_RESPONSE(
                0, i18n::s.get("core.locale.talk.npc.caravan_master.hire.choices.go_back"));
            break;
        }
        ELONA_APPEND_RESPONSE(p(cnt), mapname(p(cnt)));
    }
    buff = i18n::s.get("core.locale.talk.npc.caravan_master.hire.tset");
    talk_window_query();
    if (chatval <= 0)
    {
        buff = i18n::s.get("core.locale.talk.npc.common.you_kidding");
        return talk_result_t::talk_npc;
    }
    gdata_destination_map = adata(30, chatval);
    gdata_destination_dungeon_level = 1;
    levelexitby = 4;
    gdata(79) = 1;
    gdata(850) = adata(30, chatval);
    gdata_pc_home_x = adata(1, chatval);
    gdata_pc_home_y = adata(2, chatval);
    fixtransfermap = 1;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_guard_where_is(int chatval)
{
    talk_guide_quest_client();
    rc = rtval(chatval - 10000);
    p = direction(
        cdata[0].position.x,
        cdata[0].position.y,
        cdata[rc].position.x,
        cdata[rc].position.y);
    if (p == 1)
    {
        s = i18n::s.get("core.locale.talk.npc.guard.where_is.direction.west");
    }
    else if (p == 2)
    {
        s = i18n::s.get("core.locale.talk.npc.guard.where_is.direction.east");
    }
    else if (p == 3)
    {
        s = i18n::s.get("core.locale.talk.npc.guard.where_is.direction.north");
    }
    else
    {
        s = i18n::s.get("core.locale.talk.npc.guard.where_is.direction.south");
    }
    p = dist(
        cdata[0].position.x,
        cdata[0].position.y,
        cdata[rc].position.x,
        cdata[rc].position.y);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (rc == tc)
        {
            s = i18n::s.get("core.locale.talk.npc.common.you_kidding");
            break;
        }
        if (cdata[rc].state != 1)
        {
            s = i18n::s.get("core.locale.talk.npc.guard.where_is.dead");
            break;
        }
        if (p < 6)
        {
            s = i18n::s.get("core.locale.talk.npc.guard.where_is.very_close", s(0), cdata[rc]);
            break;
        }
        if (p < 12)
        {
            s = i18n::s.get("core.locale.talk.npc.guard.where_is.close", s(0), cdata[rc]);
            break;
        }
        if (p < 20)
        {
            s = i18n::s.get("core.locale.talk.npc.guard.where_is.moderate", s(0), cdata[rc]);
            break;
        }
        if (p < 35)
        {
            s = i18n::s.get("core.locale.talk.npc.guard.where_is.far", s(0), cdata[rc]);
            break;
        }
        s = i18n::s.get("core.locale.talk.npc.guard.where_is.very_far", s(0), cdata[rc]);
        break;
    }
    buff = s;
    return talk_result_t::talk_npc;
}

} // namespace

void talk_wrapper(talk_result_t initial)
{
    talk_result_t result = initial;
    bool finished = false;
    while (!finished)
    {
        switch (result)
        {
        case talk_result_t::talk_npc: result = talk_npc(); break;
        case talk_result_t::talk_unique: result = talk_unique(); break;
        case talk_result_t::talk_quest_giver:
            result = talk_quest_giver();
            break;
        case talk_result_t::talk_house_visitor:
            result = talk_house_visitor();
            break;
        case talk_result_t::talk_sleeping: result = talk_sleeping(); break;
        case talk_result_t::talk_busy: result = talk_busy(); break;
        case talk_result_t::talk_finish_escort:
            result = talk_finish_escort();
            break;
        case talk_result_t::talk_game_begin: result = talk_game_begin(); break;
        case talk_result_t::talk_more: result = talk_more(); break;
        case talk_result_t::talk_end:
            talk_end();
            finished = true;
            break;
        default: assert(0); break;
        }
    }
}


talk_result_t talk_npc()
{
    listmax = 0;
    if (buff == ""s)
    {
        get_npc_talk();
        int stat = chara_custom_talk(tc, 106);
        if (stat)
        {
            text_replace_tags_in_quest_board();
        }
        if (cdata[tc].interest > 0)
        {
            if (cdata[tc].relationship != 10)
            {
                if (tc >= 16)
                {
                    if (rnd(3) == 0)
                    {
                        if (cdata[tc].impression < 100)
                        {
                            if (rnd(sdata(17, 0) + 1) > 10)
                            {
                                chara_mod_impression(tc, rnd(3));
                            }
                            else
                            {
                                chara_mod_impression(tc, rnd(3) * -1);
                            }
                        }
                    }
                    cdata[tc].interest -= rnd(30);
                    cdata[tc].time_interest_revive = gdata_hour + gdata_day * 24
                        + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 8;
                }
            }
        }
    }
    if (cdata[tc].character_role == 18)
    {
        if (gdata_number_of_waiting_guests > 0)
        {
            ELONA_APPEND_RESPONSE(
                58, i18n::s.get("core.locale.talk.npc.maid.choices.meet_guest"));
            ELONA_APPEND_RESPONSE(
                59, i18n::s.get("core.locale.talk.npc.maid.choices.do_not_meet"));
        }
    }
    if (cdata[tc].interest > 0 && chatval(1) == 0)
    {
        ELONA_APPEND_RESPONSE(1, i18n::s.get("core.locale.talk.npc.common.choices.talk"));
    }
    if ((cdata[tc].character_role >= 1000 && cdata[tc].character_role < 2000)
        || cdata[tc].character_role == 2003)
    {
        ELONA_APPEND_RESPONSE(
            10, i18n::s.get("core.locale.talk.npc.shop.choices.buy"));
        ELONA_APPEND_RESPONSE(
            11, i18n::s.get("core.locale.talk.npc.shop.choices.sell"));
        if (cdata[tc].character_role == 1010)
        {
            ELONA_APPEND_RESPONSE(
                31, i18n::s.get("core.locale.talk.npc.shop.choices.attack"));
        }
        if (cdata[tc].character_role != 1010
            && cdata[tc].character_role != 1009)
        {
            ELONA_APPEND_RESPONSE(12, i18n::s.get("core.locale.talk.npc.shop.choices.invest"));
        }
    }
    if (cdata[tc].character_role == 9)
    {
        ELONA_APPEND_RESPONSE(
            33, i18n::s.get("core.locale.talk.npc.bartender.choices.call_ally"));
    }
    if (cdata[tc].character_role == 17)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                36, i18n::s.get("core.locale.talk.npc.slave_trader.choices.buy"));
        }
        ELONA_APPEND_RESPONSE(
            37, i18n::s.get("core.locale.talk.npc.slave_trader.choices.sell"));
    }
    if (cdata[tc].character_role == 22)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                57, i18n::s.get("core.locale.talk.npc.horse_keeper.choices.buy"));
        }
    }
    if (tc < 16)
    {
        if (cdata[tc].is_escorted() == 0)
        {
            if (cdata[tc].is_escorted_in_sub_quest() == 0)
            {
                ELONA_APPEND_RESPONSE(
                    34, i18n::s.get("core.locale.talk.npc.ally.choices.wait_at_town"));
                if (cdata[tc].is_married() == 0)
                {
                    ELONA_APPEND_RESPONSE(
                        38, i18n::s.get("core.locale.talk.npc.ally.choices.ask_for_marriage"));
                }
                else if (gdata_continuous_active_hours >= 15)
                {
                    ELONA_APPEND_RESPONSE(
                        39, i18n::s.get("core.locale.talk.npc.ally.choices.make_gene"));
                }
                if (cdata[tc].can_talk != 0)
                {
                    if (cdata[tc].is_silent() == 0)
                    {
                        ELONA_APPEND_RESPONSE(
                            48, i18n::s.get("core.locale.talk.npc.ally.choices.silence.start"));
                    }
                    else
                    {
                        ELONA_APPEND_RESPONSE(
                            48, i18n::s.get("core.locale.talk.npc.ally.choices.silence.stop"));
                    }
                }
                ELONA_APPEND_RESPONSE(
                    35, i18n::s.get("core.locale.talk.npc.ally.choices.abandon"));
            }
        }
    }
    if (cdata[tc].character_role == 1000 || cdata[tc].character_role == 1001)
    {
        ELONA_APPEND_RESPONSE(
            54, i18n::s.get("core.locale.talk.npc.shop.choices.ammo"));
    }
    if (cdata[tc].character_role == 1005)
    {
        ELONA_APPEND_RESPONSE(
            13,
            i18n::s.get("core.locale.talk.npc.innkeeper.choices.eat")
             + u8" ("s
                + calcmealvalue() + i18n::_(u8"ui", u8"gold") + u8")"s);
        if (gdata_weather == 1 || gdata_weather == 4 || gdata_weather == 2)
        {
            ELONA_APPEND_RESPONSE(
                43, i18n::s.get("core.locale.talk.npc.innkeeper.choices.go_to_shelter"));
        }
    }
    if (cdata[tc].character_role == 5)
    {
        ELONA_APPEND_RESPONSE(
            14,
            i18n::s.get("core.locale.talk.npc.wizard.choices.identify")
                + u8" ("s + calcidentifyvalue(0) + i18n::_(u8"ui", u8"gold")
                + u8")"s);
        ELONA_APPEND_RESPONSE(
            15,
            i18n::s.get("core.locale.talk.npc.wizard.choices.identify_all")
                + u8" ("s + calcidentifyvalue(1) + i18n::_(u8"ui", u8"gold")
                + u8")"s);
        ELONA_APPEND_RESPONSE(
            16,
            i18n::s.get("core.locale.talk.npc.wizard.choices.investigate")
                + u8" ("s + calcidentifyvalue(2) + i18n::_(u8"ui", u8"gold")
                + u8")"s);
    }
    if (cdata[tc].character_role == 7)
    {
        ELONA_APPEND_RESPONSE(17, i18n::s.get("core.locale.talk.npc.trainer.choices.train.ask"));
        ELONA_APPEND_RESPONSE(30, i18n::s.get("core.locale.talk.npc.trainer.choices.learn.ask"));
    }
    if (cdata[tc].character_role == 8)
    {
        ELONA_APPEND_RESPONSE(
            18, i18n::s.get("core.locale.talk.npc.informer.choices.show_adventurers"));
        ELONA_APPEND_RESPONSE(
            47, i18n::s.get("core.locale.talk.npc.informer.choices.investigate_ally"));
    }
    if (cdata[tc].character_role == 12)
    {
        ELONA_APPEND_RESPONSE(
            19,
            i18n::s.get("core.locale.talk.npc.healer.choices.restore_attributes")
            + u8"("s
                + calcrestorecost() + i18n::_(u8"ui", u8"gold") + u8")"s);
    }
    if (cdata[tc].character_role == 13)
    {
        ELONA_APPEND_RESPONSE(
            20, i18n::s.get("core.locale.talk.npc.common.choices.trade"));
        if (cdata[tc].is_contracting() == 0)
        {
            ELONA_APPEND_RESPONSE(
                50, i18n::s.get("core.locale.talk.npc.adventurer.choices.hire"));
            ELONA_APPEND_RESPONSE(
                51, i18n::s.get("core.locale.talk.npc.adventurer.choices.join"));
        }
    }
    if (cdata[tc].character_role == 10)
    {
        ELONA_APPEND_RESPONSE(
            21, i18n::s.get("core.locale.talk.npc.arena_master.choices.enter_duel"));
        ELONA_APPEND_RESPONSE(
            22, i18n::s.get("core.locale.talk.npc.arena_master.choices.enter_rumble"));
        ELONA_APPEND_RESPONSE(
            23, i18n::s.get("core.locale.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 11)
    {
        ELONA_APPEND_RESPONSE(
            40,
            i18n::s.get("core.locale.talk.npc.pet_arena_master.choices.register_duel"));
        ELONA_APPEND_RESPONSE(
            41,
            i18n::s.get("core.locale.talk.npc.pet_arena_master.choices.register_team"));
        ELONA_APPEND_RESPONSE(
            42, i18n::s.get("core.locale.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 18)
    {
        ELONA_APPEND_RESPONSE(
            45, i18n::s.get("core.locale.talk.npc.maid.choices.think_of_house_name"));
    }
    if (cdata[tc].character_role == 19)
    {
        ELONA_APPEND_RESPONSE(
            46, i18n::s.get("core.locale.talk.npc.sister.choices.buy_indulgence"));
    }
    int stat = talk_check_trade(tc);
    if (stat)
    {
        ELONA_APPEND_RESPONSE(
            20, i18n::s.get("core.locale.talk.npc.common.choices.trade"));
    }
    if (cdata[tc].character_role == 14)
    {
        int stat = talk_guide_quest_client();
        if (stat != 0)
        {
            for (int cnt = 0, cnt_end = (stat); cnt < cnt_end; ++cnt)
            {
                ELONA_APPEND_RESPONSE(
                    10000 + cnt,
                    i18n::s.get("core.locale.talk.npc.guard.choices.where_is", cdata[rtval(cnt)]));
            }
        }
        if (itemfind(0, 284) != -1)
        {
            ELONA_APPEND_RESPONSE(
                32,
                i18n::s.get("core.locale.talk.npc.guard.choices.lost_wallet"));
        }
        else if (itemfind(0, 283) != -1)
        {
            ELONA_APPEND_RESPONSE(
                32,
                i18n::s.get("core.locale.talk.npc.guard.choices.lost_suitcase"));
        }
    }
    if (cdata[tc].character_role == 21)
    {
        ELONA_APPEND_RESPONSE(
            53, i18n::s.get("core.locale.talk.npc.wizard.choices.return"));
    }
    if (cdata[tc].character_role == 1020)
    {
        if (gdata_belongs_to_mages_guild != 0)
        {
            ELONA_APPEND_RESPONSE(
                55, i18n::s.get("core.locale.talk.npc.spell_writer.choices.reserve"));
        }
    }
    if (cdata[tc].drunk != 0 || 0)
    {
        if (gdata_current_map != 35)
        {
            if (tc >= 16)
            {
                if (event_id() == -1)
                {
                    ELONA_APPEND_RESPONSE(
                        56,
                        i18n::s.get("core.locale.talk.npc.common.choices.sex"));
                }
            }
        }
    }
    if (cdata[tc].id == 335)
    {
        if (event_id() == -1)
        {
            ELONA_APPEND_RESPONSE(
                60, i18n::s.get("core.locale.talk.npc.prostitute.choices.buy"));
        }
    }
    if (cdata[tc].character_role == 23)
    {
        ELONA_APPEND_RESPONSE(
            61, i18n::s.get("core.locale.talk.npc.caravan_master.choices.hire"));
    }
    f = 0;
    deliver(0) = -1;
    deliver(1) = -1;
    if (gdata_current_dungeon_level == 1)
    {
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(1, cnt) == gdata_current_map)
            {
                if (qdata(0, cnt) == tc)
                {
                    rq = cnt;
                    f = 1;
                    break;
                }
            }
        }
    }
    if (f == 1)
    {
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(3, cnt) == 0)
            {
                continue;
            }
            if (qdata(8, cnt) != 1)
            {
                continue;
            }
            if (qdata(14, cnt) == 2)
            {
                if (qdata(10, cnt) == rq)
                {
                    p = qdata(11, cnt);
                    deliver = cnt;
                    for (const auto& cnt : items(0))
                    {
                        if (inv[cnt].number == 0)
                        {
                            continue;
                        }
                        if (inv[cnt].id == p)
                        {
                            deliver(1) = cnt;
                            break;
                        }
                    }
                }
            }
        }
        if (qdata(8, rq) == 3)
        {
            quest_set_data(3);
            quest_complete();
        }
        else if (qdata(14, rq) == 3 && qdata(8, rq) == 1)
        {
            supply = -1;
            for (const auto& cnt : items(0))
            {
                if (inv[cnt].number == 0)
                {
                    continue;
                }
                if (ibit(13, cnt))
                {
                    continue;
                }
                if (qdata(3, rq) == 1003)
                {
                    if (the_item_db[inv[cnt].id]->category == 57000)
                    {
                        if (inv[cnt].param1 / 1000 == qdata(12, rq))
                        {
                            if (inv[cnt].param2 == qdata(13, rq))
                            {
                                supply = cnt;
                                break;
                            }
                        }
                    }
                }
                if (qdata(3, rq) == 1004 || qdata(3, rq) == 1011)
                {
                    if (inv[cnt].id == qdata(11, rq))
                    {
                        supply = cnt;
                        break;
                    }
                }
            }
            if (supply != -1)
            {
                ELONA_APPEND_RESPONSE(
                    26,
                    i18n::s.get("core.locale.talk.npc.quest_giver.choices.here_is_item", inv[supply]));
            }
            else
            {
                ELONA_APPEND_RESPONSE(
                    24, i18n::s.get("core.locale.talk.npc.quest_giver.choices.about_the_work"));
            }
        }
        else if (qdata(3, rq) != 0)
        {
            ELONA_APPEND_RESPONSE(
                24, i18n::s.get("core.locale.talk.npc.quest_giver.choices.about_the_work"));
        }
    }
    if (deliver != -1 && deliver(1) != -1)
    {
        ELONA_APPEND_RESPONSE(
            25, i18n::s.get("core.locale.talk.npc.quest_giver.choices.here_is_delivery"));
    }
    if (gdata_current_map == 7)
    {
        if (tc >= 57)
        {
            if (cdata[tc].character_role != 0)
            {
                if ((cdata[tc].character_role < 2000
                     || cdata[tc].character_role >= 3000)
                    && event_id() == -1)
                {
                    ELONA_APPEND_RESPONSE(
                        44, i18n::s.get("core.locale.talk.npc.servant.choices.fire"));
                }
            }
        }
    }
    if (cdata[tc].character_role == 1015)
    {
        if (gdata_pael_and_her_mom == 1000)
        {
            rc = chara_find(222);
            if (rc != 0)
            {
                if (cdata[rc].state == 1)
                {
                    ELONA_APPEND_RESPONSE(
                        52, i18n::s.get("core.locale.talk.npc.moyer.choices.sell_paels_mom"));
                }
            }
        }
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    talk_window_query();
    if (chatval == 10 || chatval == 11)
    {
        if ((cdata[tc].character_role >= 1000
             && cdata[tc].character_role < 2000)
            || cdata[tc].character_role == 2003)
        {
            if (cdata[0].karma < -30 && cdata[0].is_incognito() == 0)
            {
                if (gdata_current_map != 14 && gdata_current_map != 7)
                {
                    listmax = 0;
                    if (chatval == 10)
                    {
                        buff = i18n::s.get("core.locale.talk.npc.shop.criminal.buy");
                    }
                    else
                    {
                        buff = i18n::s.get("core.locale.talk.npc.shop.criminal.sell");
                    }
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return talk_result_t::talk_npc;
                }
            }
        }
    }
    if (chatval == 1)
    {
        buff = "";
        return talk_result_t::talk_npc;
    }
    if (chatval == 10)
    {
        return talk_shop_buy();
    }
    if (chatval == 11)
    {
        return talk_shop_sell();
    }
    if (chatval == 12)
    {
        return talk_invest();
    }
    if (chatval == 13)
    {
        return talk_inn_eat();
    }
    if (chatval >= 14 && chatval < 17)
    {
        return talk_wizard_identify(chatval);
    }
    if (chatval == 17)
    {
        csctrl = 2;
        return talk_trainer();
    }
    if (chatval == 18)
    {
        return talk_informer_list_adventurers();
    }
    if (chatval == 19)
    {
        return talk_healer_restore_attributes();
    }
    if (chatval == 20)
    {
        return talk_trade();
    }
    if (chatval == 21 || chatval == 22)
    {
        return talk_arena_master(chatval);
    }
    if (chatval == 40 || chatval == 41)
    {
        return talk_pet_arena_master(chatval);
    }
    if (chatval == 42)
    {
        return talk_pet_arena_master_score();
    }
    if (chatval == 23)
    {
        return talk_arena_master_score();
    }
    if (chatval == 24)
    {
        return talk_result_t::talk_quest_giver;
    }
    if (chatval == 25)
    {
        return talk_quest_delivery();
    }
    if (chatval == 26)
    {
        return talk_quest_supply();
    }
    if (chatval == 30)
    {
        csctrl = 3;
        return talk_trainer();
    }
    if (chatval == 31)
    {
        return talk_shop_attack();
    }
    if (chatval == 32)
    {
        return talk_guard_return_item();
    }
    if (chatval == 33)
    {
        return talk_bartender_call_ally();
    }
    if (chatval == 34)
    {
        return talk_ally_order_wait();
    }
    if (chatval == 35)
    {
        return talk_ally_abandon();
    }
    if (chatval == 36 || chatval == 57)
    {
        return talk_slave_buy(chatval);
    }
    if (chatval == 37)
    {
        return talk_slave_sell();
    }
    if (chatval == 38)
    {
        return talk_ally_marriage();
    }
    if (chatval == 39)
    {
        return talk_ally_gene();
    }
    if (chatval == 43)
    {
        return talk_innkeeper_shelter();
    }
    if (chatval == 44)
    {
        return talk_servant_fire();
    }
    if (chatval == 45)
    {
        return talk_maid_think_of_house_name();
    }
    if (chatval == 46)
    {
        return talk_sister_buy_indulgence();
    }
    if (chatval == 47)
    {
        return talk_informer_investigate_ally();
    }
    if (chatval == 48)
    {
        return talk_ally_silence();
    }
    if (chatval == 50)
    {
        return talk_adventurer_hire();
    }
    if (chatval == 51)
    {
        return talk_adventurer_join();
    }
    if (chatval == 52)
    {
        return talk_moyer_sell_paels_mom();
    }
    if (chatval == 53)
    {
        return talk_wizard_return();
    }
    if (chatval == 54)
    {
        return talk_shop_reload_ammo();
    }
    if (chatval == 55)
    {
        return talk_spell_writer_reserve();
    }
    if (chatval == 56)
    {
        return talk_sex();
    }
    if (chatval == 58)
    {
        if (gdata_left_turns_of_timestop == 0)
        {
            event_add(25);
        }
        return talk_result_t::talk_end;
    }
    if (chatval == 59)
    {
        return talk_result_maid_chase_out();
    }
    if (chatval == 60)
    {
        return talk_prostitute_buy();
    }
    if (chatval == 61)
    {
        return talk_caravan_master_hire();
    }
    if (chatval >= 10000)
    {
        return talk_guard_where_is(chatval);
    }

    if (event_id() == 11)
    {
        levelexitby = 4;
        chatteleport = 1;
        snd(49);
    }

    return talk_result_t::talk_end;
}

} // namespace elona
