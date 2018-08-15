#include "ability.hpp"
#include "activity.hpp"
#include "adventurer.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "db_item.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
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
    if (cdata.player().gold < calcmealvalue())
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    if (cdata.player().nutrition >= 15000)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.innkeeper.eat.not_hungry", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata.player().gold -= calcmealvalue();
    snd(18);
    cdata.player().nutrition = 15000;
    buff = i18n::s.get(
        "core.locale.talk.npc.innkeeper.eat.here_you_are", cdata[tc]);
    txt(i18n::s.get_enum("core.locale.talk.npc.innkeeper.eat.results", rnd(3)));
    show_eating_message();
    chara_anorexia(cdata.player());
    return talk_result_t::talk_npc;
}

talk_result_t talk_wizard_identify(int chatval_)
{
    if (cdata.player().gold < calcidentifyvalue(chatval_ - 14))
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    p = 0;
    for (const auto& cnt : items(0))
    {
        if (inv[cnt].number() == 0)
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
        buff = i18n::s.get(
            "core.locale.talk.npc.wizard.identify.already", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    if (chatval_ == 15)
    {
        cdata.player().gold -= calcidentifyvalue(1);
        p(0) = 0;
        p(1) = 0;
        p(0) = 0;
        p(1) = 0;
        for (const auto& cnt : items(0))
        {
            if (inv[cnt].number() == 0)
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
        txt(i18n::s.get(
            "core.locale.talk.npc.wizard.identify.count", p(0), p(1)));
        buff = i18n::s.get(
            "core.locale.talk.npc.wizard.identify.finished", cdata[tc]);
    }
    else
    {
        if (chatval_ == 14)
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
            buff = i18n::s.get(
                "core.locale.talk.npc.common.you_kidding", cdata[tc]);
            return talk_result_t::talk_npc;
        }
        if (idtresult == identification_state_t::completely_identified)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.wizard.identify.finished", cdata[tc]);
        }
        else
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.wizard.identify.need_investigate",
                cdata[tc]);
        }
        cdata.player().gold -= calcidentifyvalue(chatval_ - 14);
    }
    snd(12);
    return talk_result_t::talk_npc;
}

talk_result_t talk_informer_list_adventurers()
{
    list_adventurers();
    buff = i18n::s.get(
        "core.locale.talk.npc.informer.show_adventurers", cdata[tc]);
    return talk_result_t::talk_npc;
}

talk_result_t talk_healer_restore_attributes()
{
    if (cdata.player().gold < calcrestorecost())
    {
        buff = i18n::_(u8"ui", u8"no_gold");
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata.player().gold -= calcrestorecost();
    tcbk = tc;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() != character::state_t::alive)
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
    buff = i18n::s.get(
        "core.locale.talk.npc.healer.restore_attributes", cdata[tc]);
    return talk_result_t::talk_npc;
}

talk_result_t talk_trade()
{
    invsubroutine = 1;
    for (const auto& cnt : items(tc))
    {
        if (inv[cnt].number() != 0)
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
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    return talk_result_t::talk_npc;
}

talk_result_t talk_arena_master(int chatval_)
{
    if (gdata_mount != 0)
    {
        int stat = cell_findspace(
            cdata.player().position.x, cdata.player().position.y, 1);
        if (stat == 0)
        {
            txt(i18n::s.get("core.locale.magic.mount.no_place_to_get_off"));
            return talk_result_t::talk_end;
        }
        cell_setchara(gdata_mount, rtval, rtval(1));
        txt(i18n::s.get(
            "core.locale.magic.mount.dismount", cdata[gdata_mount]));
        ride_end();
    }
    gdata(74) = calcfame(
        0,
        (220 - gdata(120) / 50)
                * (100 + clamp(adata(22, gdata_current_map), 0, 50)) / 100
            + 2);
    listmax = 0;
    randomize(adata(26, gdata_current_map));
    if (chatval_ == 21)
    {
        if (adata(26, gdata_current_map) > gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.arena_master.enter.game_is_over",
                cdata[tc]);
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
        buff = i18n::s.get(
            "core.locale.talk.npc.arena_master.enter.target",
            cdata[rc],
            chara_refstr(cdata[rc].id, 2),
            cdata[tc]);
    }
    else
    {
        if (adata(27, gdata_current_map) > gdata_hour + gdata_day * 24
                + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.arena_master.enter.game_is_over",
                cdata[tc]);
            return talk_result_t::talk_npc;
        }
        arenaop(0) = 1;
        arenaop(1) = (100 - gdata(120) / 100) / 2 + 1;
        buff = i18n::s.get(
            "core.locale.talk.npc.arena_master.enter.target_group",
            arenaop(1),
            cdata[tc]);
    }
    ELONA_APPEND_RESPONSE(
        1,
        i18n::s.get("core.locale.talk.npc.arena_master.enter.choices.enter"));
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get("core.locale.talk.npc.arena_master.enter.choices.leave"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ != 1)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.arena_master.enter.cancel", cdata[tc]);
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
    gdata_previous_x = cdata.player().position.x;
    gdata_previous_y = cdata.player().position.y;
    gdata_destination_map = 6;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_pet_arena_master(int chatval_)
{
    gdata(74) = calcfame(
        0,
        (220 - gdata(121) / 50)
                * (50 + clamp(adata(23, gdata_current_map), 0, 50)) / 100
            + 2);
    listmax = 0;
    if (chatval_ == 40)
    {
        arenaop(0) = 0;
        arenaop(1) = 1;
        arenaop(2) = (100 - gdata(121) / 100) / 3 * 2 + 3;
        buff = i18n::s.get(
            "core.locale.talk.npc.pet_arena_master.register.target",
            arenaop(2),
            cdata[tc]);
    }
    if (chatval_ == 41)
    {
        arenaop(0) = 1;
        arenaop(1) = 2;
        arenaop(2) = (100 - gdata(121) / 100) / 2 + 1;
        arenaop(1) = rnd(7) + 2;
        buff = i18n::s.get(
            "core.locale.talk.npc.pet_arena_master.register.target_group",
            arenaop(1),
            arenaop(2),
            cdata[tc]);
    }
    ELONA_APPEND_RESPONSE(
        1,
        i18n::s.get(
            "core.locale.talk.npc.pet_arena_master.register.choices.enter"));
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get(
            "core.locale.talk.npc.pet_arena_master.register.choices.leave"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ != 1)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.arena_master.enter.cancel", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    DIM2(followerexist, 16);
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        followerexist(cnt) = static_cast<int>(cdata[cnt].state());
    }
    int stat = ctrl_ally(ctrl_ally_operation::pet_arena);
    if (stat == -1)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.arena_master.enter.cancel", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    gdata_executing_immediate_quest_type = 2;
    gdata(71) = 0;
    gdata_executing_immediate_quest = 0;
    gdata(73) = 1;
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata.player().position.x;
    gdata_previous_y = cdata.player().position.y;
    gdata_destination_map = 40;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_pet_arena_master_score()
{
    buff = i18n::s.get(
        "core.locale.talk.npc.arena_master.streak",
        adata(23, gdata_current_map));
    return talk_result_t::talk_npc;
}

talk_result_t talk_arena_master_score()
{
    buff = i18n::s.get(
        "core.locale.talk.npc.arena_master.streak",
        adata(22, gdata_current_map));
    return talk_result_t::talk_npc;
}

talk_result_t talk_quest_delivery()
{
    int stat = inv_getfreeid_force();
    ti = stat;
    item_copy(deliver(1), ti);
    inv[ti].set_number(1);
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used(cdata[tc]);
    rq = deliver;
    inv[deliver(1)].modify_number(-1);
    txt(i18n::s.get("core.locale.talk.npc.common.hand_over", inv[deliver(1)]));
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
    inv[ti].set_number(1);
    cdata[tc].was_passed_item_by_you_just_now() = true;
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used(cdata[tc]);
    inv[supply].modify_number(-1);
    txt(i18n::s.get("core.locale.talk.npc.common.hand_over", inv[supply]));
    quest_set_data(3);
    quest_complete();
    refresh_burden_state();
    return talk_result_t::talk_npc;
}

talk_result_t talk_shop_attack()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.shop.attack.dialog", cdata[tc]);
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.locale.talk.npc.shop.attack.choices.attack"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.shop.attack.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
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
    inv[p].modify_number(-1);
    if (inv[p].param1 == 0)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.guard.lost.empty.dialog", cdata[tc]);
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.guard.lost.empty.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(cdata.player(), -5);
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.guard.lost.dialog", cdata[tc]);
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.locale.talk.npc.guard.lost.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(cdata.player(), 5);
        ++gdata_lost_wallet_count;
        if (gdata_lost_wallet_count >= 4)
        {
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.locale.talk.npc.guard.lost.found_often.dialog",
                0,
                cdata[tc]);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum(
                "core.locale.talk.npc.guard.lost.found_often.dialog", 1);
            ELONA_APPEND_RESPONSE(
                0,
                i18n::s.get(
                    "core.locale.talk.npc.guard.lost.found_often.response"));
            chatesc = 1;
            talk_window_query();
            modify_karma(cdata.player(), -10);
        }
    }
    refresh_burden_state();
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_bartender_call_ally()
{
    int stat = ctrl_ally(ctrl_ally_operation::call_back);
    if (stat != -1)
    {
        rc = stat;
        if (cdata[rc].state() == character::state_t::alive)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.bartender.call_ally.no_need", cdata[tc]);
            return talk_result_t::talk_npc;
        }
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.bartender.call_ally.cost",
            calcresurrectvalue(rc),
            cdata[tc]);
        if (cdata.player().gold >= calcresurrectvalue(rc))
        {
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get(
                    "core.locale.talk.npc.bartender.call_ally.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.locale.talk.npc.bartender.call_ally.choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            snd(12);
            cdata.player().gold -= calcresurrectvalue(rc);
            buff = i18n::s.get(
                "core.locale.talk.npc.bartender.call_ally.brings_back",
                cdata[tc],
                cdata[rc]);
            revive_character();
        }
        else
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
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
    cdata[tc].set_state(character::state_t::pet_waiting);
    cdata[tc].current_map = 0;
    return talk_result_t::talk_end;
}

talk_result_t talk_ally_abandon()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.ally.abandon.prompt", cdata[tc]);
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.yes"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.ally.abandon.choices.no"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get(
            "core.locale.talk.npc.ally.abandon.you_abandoned", cdata[tc]));
        map(cdata[tc].position.x, cdata[tc].position.y, 1) = 0;
        chara_delete(tc);
        return talk_result_t::talk_end;
    }
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_slave_buy(int chatval_)
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        flt(cdata.player().level / 2 + 5);
        fixlv = 2;
        if (chatval_ == 36)
        {
            fltn(u8"man"s);
        }
        else
        {
            fltn(u8"horse"s);
        }
        chara_create(56, 0, -3, 0);
        if (cdata.tmp().level == 0)
        {
            chara_vanquish(56);
            continue;
        }
        break;
    }
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.npc.slave_trader.buy.cost",
        cnven(cdatan(0, 56)),
        calcslavevalue(56),
        cdata[tc]);
    if (cdata.player().gold >= calcslavevalue(56))
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.npc.slave_trader.buy.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get("core.locale.talk.npc.slave_trader.buy.choices.go_back"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ == 1)
    {
        txt(i18n::s.get(
            "core.locale.talk.npc.slave_trader.buy.you_buy",
            cnven(cdatan(0, 56))));
        snd(12);
        cdata.player().gold -= calcslavevalue(56);
        rc = 56;
        new_ally_joins();
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_slave_sell()
{
    int stat = ctrl_ally(ctrl_ally_operation::sell);
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.slave_trader.sell.price",
            (calcslavevalue(rc) * 2 / 3),
            cdata[tc]);
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get("core.locale.talk.npc.slave_trader.sell.choices.deal"));
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.locale.talk.npc.slave_trader.sell.choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            txt(i18n::s.get(
                "core.locale.talk.npc.slave_trader.sell.you_sell_off",
                cnven(cdatan(0, rc))));
            snd(11);
            earn_gold(cdata.player(), calcslavevalue(rc) * 2 / 3);
            if (cdata[rc].state() == character::state_t::alive)
            {
                map(cdata[rc].position.x, cdata[rc].position.y, 1) = 0;
            }
            if (cdata[rc].is_escorted() == 1)
            {
                event_add(15, cdata[rc].id);
            }
            chara_delete(rc);
            buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
        }
        else
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_ally_marriage()
{
    if (cdata[tc].impression < 200)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.ally.marriage.refuses", cdata[tc]);
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
    if (gdata_current_map == mdata_t::map_id_t::shelter_)
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
    buff =
        i18n::s.get("core.locale.talk.npc.innkeeper.go_to_shelter", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata.player().position.x;
    gdata_previous_y = cdata.player().position.y;
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
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.locale.talk.npc.servant.fire.choices.yes"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.servant.fire.choices.no"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get(
            "core.locale.talk.npc.servant.fire.you_dismiss", cdata[tc]));
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
        mdatan(0) = i18n::s.get_enum(
            "core.locale.talk.npc.maid.think_of_house_name.suffixes",
            rnd(11),
            mdatan(0));
    }
    screenupdate = -1;
    update_entire_screen();
    buff = i18n::s.get(
        "core.locale.talk.npc.maid.think_of_house_name.come_up_with",
        mdatan(0),
        cdata[tc]);
    return talk_result_t::talk_npc;
}

talk_result_t talk_sister_buy_indulgence()
{
    if (cdata.player().karma >= -30)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.sister.buy_indulgence.karma_is_not_low");
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.npc.sister.buy_indulgence.cost",
        calcguiltvalue(),
        cdata[tc]);
    if (cdata.player().gold >= calcguiltvalue())
    {
        ELONA_APPEND_RESPONSE(
            1,
            i18n::s.get(
                "core.locale.talk.npc.sister.buy_indulgence.choices.buy"));
    }
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get(
            "core.locale.talk.npc.sister.buy_indulgence.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd(12);
        cdata.player().gold -= calcguiltvalue();
        modify_karma(cdata.player(), (cdata.player().karma - -30) * -1 + 1);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_informer_investigate_ally()
{
    int tcchat = tc;
    int stat = ctrl_ally(ctrl_ally_operation::investigate);
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.informer.investigate_ally.cost", cdata[tc]);
        if (cdata.player().gold >= 10000)
        {
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get("core.locale.talk.npc.informer.investigate_ally."
                            "choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get("core.locale.talk.npc.informer.investigate_ally."
                        "choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            snd(12);
            cdata.player().gold -= 10000;
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
            buff = i18n::s.get(
                "core.locale.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
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
    buff = i18n::s.get(
        "core.locale.talk.npc.adventurer.hire.cost",
        calchireadv(tc),
        cdata[tc]);
    if (cdata.player().gold >= calchireadv(tc))
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.npc.adventurer.hire.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.adventurer.hire.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd(12);
        cdata.player().gold -= calchireadv(tc);
        cdata[tc].relationship = 10;
        cdata[tc].is_contracting() = true;
        cdata[tc].period_of_contract = gdata_hour + gdata_day * 24
            + gdata_month * 24 * 30 + gdata_year * 24 * 30 * 12 + 168;
        ++cdata[tc].hire_count;
        snd(64);
        txtef(5);
        txt(i18n::s.get(
            "core.locale.talk.npc.adventurer.hire.you_hired", cdata[tc]));
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_adventurer_join()
{
    if (cdata.player().level * 3 / 2 + 10 < cdata[tc].level)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.adventurer.join.too_weak", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    if (cdata[tc].impression >= 200 && cdata[tc].hire_count > 2)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.adventurer.join.accept", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        f = chara_get_free_slot_ally();
        if (f == 0)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.adventurer.join.party_full", cdata[tc]);
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
    buff = i18n::s.get(
        "core.locale.talk.npc.adventurer.join.not_known", cdata[tc]);
    return talk_result_t::talk_npc;
}

talk_result_t talk_moyer_sell_paels_mom()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.prompt");
    ELONA_APPEND_RESPONSE(
        1,
        i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.choices.sell"));
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get(
            "core.locale.talk.npc.moyer.sell_paels_mom.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get("core.locale.talk.npc.moyer.sell_paels_mom.you_sell"));
        modify_karma(cdata.player(), -20);
        snd(11);
        earn_gold(cdata.player(), 50000);
        gdata_pael_and_her_mom = 1002;
        rc = chara_find(222);
        cdata[rc].ai_calm = 3;
        cdata[rc].relationship = 0;
        cdata[rc].initial_position.x = 48;
        cdata[rc].initial_position.y = 18;
        cell_movechara(rc, 48, 18);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_wizard_return()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.wizard.return", cdata[tc]);
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
    buff = i18n::s.get(
        "core.locale.talk.npc.shop.ammo.cost", calccostreload(0), cdata[tc]);
    if (cdata.player().gold >= calccostreload(0))
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.npc.shop.ammo.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.shop.ammo.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd(12);
        cdata.player().gold -= calccostreload(0);
        p = calccostreload(0, true);
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
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
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.locale.talk.npc.common.sex.choices.accept"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.common.sex.choices.go_back"));
    buff = i18n::s.get("core.locale.talk.npc.common.sex.prompt", cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.common.sex.start", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.common.sex.response"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    continuous_action_sex();
    return talk_result_t::talk_end;
}

talk_result_t talk_result_maid_chase_out()
{
    --gdata_number_of_waiting_guests;
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.maid.do_not_meet", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    buff = "";
    return talk_result_t::talk_npc;
}

talk_result_t talk_prostitute_buy()
{
    sexvalue = sdata(17, tc) * 25 + 100 + cdata.player().fame / 10;
    if (cdata.player().gold >= sexvalue)
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.npc.common.sex.choices.accept"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.common.sex.choices.go_back"));
    buff =
        i18n::s.get("core.locale.talk.npc.prostitute.buy", sexvalue, cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    snd(12);
    cdata[cc].gold -= sexvalue;
    earn_gold(cdata[tc], sexvalue);
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.common.sex.start", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.locale.talk.npc.common.sex.response"));
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
    if (gdata_current_map == mdata_t::map_id_t::north_tyris_south_border)
    {
        p(0) = 45;
        p(1) = 48;
        p(2) = 0;
    }
    if (gdata_current_map == mdata_t::map_id_t::south_tyris_north_border)
    {
        p(0) = 43;
        p(1) = 48;
        p(2) = 0;
    }
    if (gdata_current_map == mdata_t::map_id_t::test_world_north_border)
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
                0,
                i18n::s.get("core.locale.talk.npc.caravan_master.hire.choices."
                            "go_back"));
            break;
        }
        ELONA_APPEND_RESPONSE(p(cnt), mapname(p(cnt)));
    }
    buff = i18n::s.get("core.locale.talk.npc.caravan_master.hire.tset");
    int chatval_ = talk_window_query();
    if (chatval_ <= 0)
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    gdata_destination_map = adata(30, chatval_);
    gdata_destination_dungeon_level = 1;
    levelexitby = 4;
    gdata(79) = 1;
    gdata(850) = adata(30, chatval_);
    gdata_pc_x_in_world_map = adata(1, chatval_);
    gdata_pc_y_in_world_map = adata(2, chatval_);
    fixtransfermap = 1;
    chatteleport = 1;
    return talk_result_t::talk_end;
}

talk_result_t talk_guard_where_is(int chatval_)
{
    talk_guide_quest_client();
    rc = rtval(chatval_ - 10000);
    p = direction(
        cdata.player().position.x,
        cdata.player().position.y,
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
        cdata.player().position.x,
        cdata.player().position.y,
        cdata[rc].position.x,
        cdata[rc].position.y);
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (rc == tc)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.common.you_kidding", cdata[tc]);
            break;
        }
        if (cdata[rc].state() != character::state_t::alive)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.guard.where_is.dead", cdata[tc]);
            break;
        }
        if (p < 6)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.guard.where_is.very_close",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 12)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.guard.where_is.close",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 20)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.guard.where_is.moderate",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 35)
        {
            s = i18n::s.get(
                "core.locale.talk.npc.guard.where_is.far",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        s = i18n::s.get(
            "core.locale.talk.npc.guard.where_is.very_far",
            s(0),
            cdata[rc],
            cdata[tc]);
        break;
    }
    buff = s;
    return talk_result_t::talk_npc;
}

talk_result_t talk_accepted_quest()
{
    if (qdata(3, rq) == 1001 || qdata(3, rq) == 1010)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.quest_giver.accept.hunt", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
    }
    if (qdata(3, rq) == 1006)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.quest_giver.accept.harvest", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
    }
    if (qdata(3, rq) == 1009)
    {
        listmax = 0;
        buff = i18n::s.get(
            "core.locale.talk.npc.quest_giver.accept.party", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::_(u8"ui", u8"more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return talk_result_t::talk_end;
            }
        }
    }
    gdata_executing_immediate_quest_type = qdata(3, rq);
    gdata(71) = qdata(14, rq);
    gdata_executing_immediate_quest = rq;
    gdata(73) = 1;
    gdata_previous_map2 = gdata_current_map;
    gdata_previous_dungeon_level = gdata_current_dungeon_level;
    gdata_previous_x = cdata.player().position.x;
    gdata_previous_y = cdata.player().position.y;
    gdata_destination_map = 13;
    gdata_destination_dungeon_level = 1;
    levelexitby = 2;
    chatteleport = 1;
    return talk_result_t::talk_end;
}



talk_result_t talk_trainer()
{
    tcbk = tc;
    menucycle = 0;
    menu_character_sheet();
    talk_start();
    if (csskill == -1)
    {
        buff = i18n::s.get("core.locale.talk.npc.trainer.leave", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    if (csctrl == 2)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.trainer.cost.training",
            i18n::_(u8"ability", std::to_string(csskill), u8"name"),
            calctraincost(csskill, cc),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calctraincost(csskill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = i18n::s.get(
                "core.locale.talk.npc.trainer.choices.train.accept");
            ++listmax;
        }
    }
    else
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.trainer.cost.learning",
            i18n::_(u8"ability", std::to_string(csskill), u8"name"),
            calclearncost(csskill, cc),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calclearncost(csskill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = i18n::s.get(
                "core.locale.talk.npc.trainer.choices.learn.accept");
            ++listmax;
        }
    }
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.npc.trainer.choices.go_back");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd(12);
        if (csctrl == 2)
        {
            cdata.player().platinum_coin -= calctraincost(csskill, cc);
            modify_potential(
                cdata[cc],
                csskill,
                clamp(15 - sdata.get(csskill, cc).potential / 15, 2, 15));
            buff = i18n::s.get(
                "core.locale.talk.npc.trainer.finish.training", cdata[tc]);
        }
        else
        {
            cdata.player().platinum_coin -= calclearncost(csskill, cc);
            chara_gain_skill(cdata[cc], csskill);
            ++gdata_number_of_learned_skills_by_trainer;
            buff = i18n::s.get(
                "core.locale.talk.npc.trainer.finish.learning", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.locale.talk.npc.trainer.leave", cdata[tc]);
    }
    return talk_result_t::talk_npc;
}



talk_result_t talk_invest()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.locale.talk.npc.shop.invest.ask", calcinvestvalue(), cdata[tc]);
    if (cdata.player().gold >= calcinvestvalue())
    {
        list(0, listmax) = 1;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.npc.shop.invest.choices.invest");
        ++listmax;
    }
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.npc.shop.invest.choices.reject");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd(12);
        cdata.player().gold -= calcinvestvalue();
        gain_investing_experience(0);
        cdata[tc].shop_rank += rnd(2) + 2;
        buff = i18n::s.get("core.locale.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        calccosthire();
    }
    return talk_result_t::talk_npc;
}

talk_result_t talk_finish_escort()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.npc.quest_giver.finish.escort");
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return talk_result_t::talk_end;
        }
    }
    return talk_result_t::talk_end;
}



talk_result_t talk_quest_giver()
{
    if (qdata(8, rq) == 1)
    {
        buff = i18n::s.get(
            "core.locale.talk.npc.quest_giver.about.during", cdata[tc]);
        return talk_result_t::talk_npc;
    }
    quest_set_data(1);
    listmax = 0;
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.npc.quest_giver.about.choices.take");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.talk.npc.quest_giver.about.choices.leave");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(3, cnt) == 0)
            {
                continue;
            }
            if (qdata(8, cnt) != 0)
            {
                ++p;
            }
        }
        if (p >= 5)
        {
            buff = i18n::s.get(
                "core.locale.talk.npc.quest_giver.about.too_many_unfinished",
                cdata[tc]);
            return talk_result_t::talk_npc;
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            p = gdata(160 + cnt);
            f = 0;
            for (int cnt = 0; cnt < 5; ++cnt)
            {
                if (gdata(160 + cnt) == p)
                {
                    ++f;
                }
            }
            if (qdata(8, p) == 0 || f > 1)
            {
                gdata(160 + cnt) = rq;
                break;
            }
        }
        if (qdata(3, rq) == 1002)
        {
            if (inv_getfreeid(0) == -1)
            {
                buff = i18n::s.get(
                    "core.locale.talk.npc.quest_giver.about.backpack_full",
                    cdata[tc]);
                return talk_result_t::talk_npc;
            }
        }
        if (qdata(3, rq) == 1007)
        {
            f = chara_get_free_slot_ally();
            if (f == 0)
            {
                buff = i18n::s.get(
                    "core.locale.talk.npc.quest_giver.about.party_full",
                    cdata[tc]);
                return talk_result_t::talk_npc;
            }
            for (int cnt = 0;; ++cnt)
            {
                if (cnt == 99)
                {
                    dbid = 35;
                }
                else
                {
                    dbid = 0;
                }
                flt(qdata(5, rq) + cnt, 1);
                fltn(u8"man"s);
                int stat = chara_create(56, dbid, -3, 0);
                f = stat;
                if (f == 1)
                {
                    for (int cnt = 0; cnt < 16; ++cnt)
                    {
                        if (cdata[cnt].state() == character::state_t::empty)
                        {
                            continue;
                        }
                        if (cdata[cnt].id == cdata[rc].id)
                        {
                            if (cdata[cnt].is_escorted() == 1)
                            {
                                f = 0;
                                break;
                            }
                        }
                    }
                }
                if (f == 1)
                {
                    break;
                }
            }
            rc = 56;
            new_ally_joins();
            cdata[rc].is_escorted() = true;
            qdata(13, rq) = cdata[rc].id;
        }
        qdata(8, rq) = 1;
        if (qdata(9, rq) == -1)
        {
            return talk_accepted_quest();
        }
        buff = i18n::s.get(
            "core.locale.talk.npc.quest_giver.about.thanks", cdata[tc]);
        if (qdata(3, rq) == 1002)
        {
            ++qdata(15, qdata(10, rq));
            flt();
            itemcreate(
                0,
                qdata(11, rq),
                cdata.player().position.x,
                cdata.player().position.y,
                0);
            txt(i18n::s.get(
                "core.locale.common.you_put_in_your_backpack", inv[ci]));
            snd(100);
            refresh_burden_state();
            buff = i18n::s.get(
                "core.locale.talk.npc.quest_giver.about.here_is_package",
                cdata[tc]);
        }
    }
    else
    {
        buff =
            i18n::s.get("core.locale.talk.npc.common.you_kidding", cdata[tc]);
    }
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
        case talk_result_t::talk_ignored: result = talk_ignored(); break;
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
                                chara_modify_impression(cdata[tc], rnd(3));
                            }
                            else
                            {
                                chara_modify_impression(cdata[tc], rnd(3) * -1);
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
                58,
                i18n::s.get("core.locale.talk.npc.maid.choices.meet_guest"));
            ELONA_APPEND_RESPONSE(
                59,
                i18n::s.get("core.locale.talk.npc.maid.choices.do_not_meet"));
        }
    }
    if (cdata[tc].interest > 0 && !chatval_unique_chara_id)
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.locale.talk.npc.common.choices.talk"));
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
            ELONA_APPEND_RESPONSE(
                12, i18n::s.get("core.locale.talk.npc.shop.choices.invest"));
        }
    }
    if (cdata[tc].character_role == 9)
    {
        ELONA_APPEND_RESPONSE(
            33,
            i18n::s.get("core.locale.talk.npc.bartender.choices.call_ally"));
    }
    if (cdata[tc].character_role == 17)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                36,
                i18n::s.get("core.locale.talk.npc.slave_trader.choices.buy"));
        }
        ELONA_APPEND_RESPONSE(
            37, i18n::s.get("core.locale.talk.npc.slave_trader.choices.sell"));
    }
    if (cdata[tc].character_role == 22)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                57,
                i18n::s.get("core.locale.talk.npc.horse_keeper.choices.buy"));
        }
    }
    if (tc < 16)
    {
        if (cdata[tc].is_escorted() == 0)
        {
            if (cdata[tc].is_escorted_in_sub_quest() == 0)
            {
                ELONA_APPEND_RESPONSE(
                    34,
                    i18n::s.get(
                        "core.locale.talk.npc.ally.choices.wait_at_town"));
                if (cdata[tc].is_married() == 0)
                {
                    ELONA_APPEND_RESPONSE(
                        38,
                        i18n::s.get("core.locale.talk.npc.ally.choices.ask_for_"
                                    "marriage"));
                }
                else if (gdata_continuous_active_hours >= 15)
                {
                    ELONA_APPEND_RESPONSE(
                        39,
                        i18n::s.get(
                            "core.locale.talk.npc.ally.choices.make_gene"));
                }
                if (cdata[tc].can_talk != 0)
                {
                    if (cdata[tc].is_silent() == 0)
                    {
                        ELONA_APPEND_RESPONSE(
                            48,
                            i18n::s.get("core.locale.talk.npc.ally.choices."
                                        "silence.start"));
                    }
                    else
                    {
                        ELONA_APPEND_RESPONSE(
                            48,
                            i18n::s.get("core.locale.talk.npc.ally.choices."
                                        "silence.stop"));
                    }
                }
                ELONA_APPEND_RESPONSE(
                    35,
                    i18n::s.get("core.locale.talk.npc.ally.choices.abandon"));
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
            i18n::s.get("core.locale.talk.npc.innkeeper.choices.eat") + u8" ("s
                + calcmealvalue() + i18n::_(u8"ui", u8"gold") + u8")"s);
        if (gdata_weather == 1 || gdata_weather == 4 || gdata_weather == 2)
        {
            ELONA_APPEND_RESPONSE(
                43,
                i18n::s.get(
                    "core.locale.talk.npc.innkeeper.choices.go_to_shelter"));
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
        ELONA_APPEND_RESPONSE(
            17, i18n::s.get("core.locale.talk.npc.trainer.choices.train.ask"));
        ELONA_APPEND_RESPONSE(
            30, i18n::s.get("core.locale.talk.npc.trainer.choices.learn.ask"));
    }
    if (cdata[tc].character_role == 8)
    {
        ELONA_APPEND_RESPONSE(
            18,
            i18n::s.get(
                "core.locale.talk.npc.informer.choices.show_adventurers"));
        ELONA_APPEND_RESPONSE(
            47,
            i18n::s.get(
                "core.locale.talk.npc.informer.choices.investigate_ally"));
    }
    if (cdata[tc].character_role == 12)
    {
        ELONA_APPEND_RESPONSE(
            19,
            i18n::s.get(
                "core.locale.talk.npc.healer.choices.restore_attributes")
                + u8"("s + calcrestorecost() + i18n::_(u8"ui", u8"gold")
                + u8")"s);
    }
    if (cdata[tc].character_role == 13)
    {
        ELONA_APPEND_RESPONSE(
            20, i18n::s.get("core.locale.talk.npc.common.choices.trade"));
        if (cdata[tc].is_contracting() == 0)
        {
            ELONA_APPEND_RESPONSE(
                50,
                i18n::s.get("core.locale.talk.npc.adventurer.choices.hire"));
            ELONA_APPEND_RESPONSE(
                51,
                i18n::s.get("core.locale.talk.npc.adventurer.choices.join"));
        }
    }
    if (cdata[tc].character_role == 10)
    {
        ELONA_APPEND_RESPONSE(
            21,
            i18n::s.get(
                "core.locale.talk.npc.arena_master.choices.enter_duel"));
        ELONA_APPEND_RESPONSE(
            22,
            i18n::s.get(
                "core.locale.talk.npc.arena_master.choices.enter_rumble"));
        ELONA_APPEND_RESPONSE(
            23, i18n::s.get("core.locale.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 11)
    {
        ELONA_APPEND_RESPONSE(
            40,
            i18n::s.get(
                "core.locale.talk.npc.pet_arena_master.choices.register_duel"));
        ELONA_APPEND_RESPONSE(
            41,
            i18n::s.get(
                "core.locale.talk.npc.pet_arena_master.choices.register_team"));
        ELONA_APPEND_RESPONSE(
            42, i18n::s.get("core.locale.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 18)
    {
        ELONA_APPEND_RESPONSE(
            45,
            i18n::s.get(
                "core.locale.talk.npc.maid.choices.think_of_house_name"));
    }
    if (cdata[tc].character_role == 19)
    {
        ELONA_APPEND_RESPONSE(
            46,
            i18n::s.get("core.locale.talk.npc.sister.choices.buy_indulgence"));
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
                    i18n::s.get(
                        "core.locale.talk.npc.guard.choices.where_is",
                        cdata[rtval(cnt)]));
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
                i18n::s.get(
                    "core.locale.talk.npc.guard.choices.lost_suitcase"));
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
                55,
                i18n::s.get(
                    "core.locale.talk.npc.spell_writer.choices.reserve"));
        }
    }
    if (cdata[tc].drunk != 0 || 0)
    {
        if (gdata_current_map != mdata_t::map_id_t::show_house)
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
            61,
            i18n::s.get("core.locale.talk.npc.caravan_master.choices.hire"));
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
                        if (inv[cnt].number() == 0)
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
                if (inv[cnt].number() == 0)
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
                    i18n::s.get(
                        "core.locale.talk.npc.quest_giver.choices.here_is_item",
                        inv[supply]));
            }
            else
            {
                ELONA_APPEND_RESPONSE(
                    24,
                    i18n::s.get("core.locale.talk.npc.quest_giver.choices."
                                "about_the_work"));
            }
        }
        else if (qdata(3, rq) != 0)
        {
            ELONA_APPEND_RESPONSE(
                24,
                i18n::s.get(
                    "core.locale.talk.npc.quest_giver.choices.about_the_work"));
        }
    }
    if (deliver != -1 && deliver(1) != -1)
    {
        ELONA_APPEND_RESPONSE(
            25,
            i18n::s.get(
                "core.locale.talk.npc.quest_giver.choices.here_is_delivery"));
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
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
                        44,
                        i18n::s.get(
                            "core.locale.talk.npc.servant.choices.fire"));
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
                if (cdata[rc].state() == character::state_t::alive)
                {
                    ELONA_APPEND_RESPONSE(
                        52,
                        i18n::s.get("core.locale.talk.npc.moyer.choices.sell_"
                                    "paels_mom"));
                }
            }
        }
    }
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;

    int chatval_ = talk_window_query();

    if (chatval_ == 10 || chatval_ == 11)
    {
        if ((cdata[tc].character_role >= 1000
             && cdata[tc].character_role < 2000)
            || cdata[tc].character_role == 2003)
        {
            if (cdata.player().karma < -30
                && cdata.player().is_incognito() == 0)
            {
                if (gdata_current_map != mdata_t::map_id_t::derphy
                    && gdata_current_map != mdata_t::map_id_t::your_home)
                {
                    listmax = 0;
                    if (chatval_ == 10)
                    {
                        buff = i18n::s.get(
                            "core.locale.talk.npc.shop.criminal.buy",
                            cdata[tc]);
                    }
                    else
                    {
                        buff = i18n::s.get(
                            "core.locale.talk.npc.shop.criminal.sell",
                            cdata[tc]);
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

    switch (chatval_)
    {
    case 1: buff = ""; return talk_result_t::talk_npc;
    case 10: return talk_shop_buy();
    case 11: return talk_shop_sell();
    case 12: return talk_invest();
    case 13: return talk_inn_eat();
    case 14:
    case 15:
    case 16: return talk_wizard_identify(chatval_);
    case 17: csctrl = 2; return talk_trainer();
    case 18: return talk_informer_list_adventurers();
    case 19: return talk_healer_restore_attributes();
    case 20: return talk_trade();
    case 21:
    case 22: return talk_arena_master(chatval_);
    case 40:
    case 41: return talk_pet_arena_master(chatval_);
    case 42: return talk_pet_arena_master_score();
    case 23: return talk_arena_master_score();
    case 24: return talk_result_t::talk_quest_giver;
    case 25: return talk_quest_delivery();
    case 26: return talk_quest_supply();
    case 30: csctrl = 3; return talk_trainer();
    case 31: return talk_shop_attack();
    case 32: return talk_guard_return_item();
    case 33: return talk_bartender_call_ally();
    case 34: return talk_ally_order_wait();
    case 35: return talk_ally_abandon();
    case 36:
    case 57: return talk_slave_buy(chatval_);
    case 37: return talk_slave_sell();
    case 38: return talk_ally_marriage();
    case 39: return talk_ally_gene();
    case 43: return talk_innkeeper_shelter();
    case 44: return talk_servant_fire();
    case 45: return talk_maid_think_of_house_name();
    case 46: return talk_sister_buy_indulgence();
    case 47: return talk_informer_investigate_ally();
    case 48: return talk_ally_silence();
    case 50: return talk_adventurer_hire();
    case 51: return talk_adventurer_join();
    case 52: return talk_moyer_sell_paels_mom();
    case 53: return talk_wizard_return();
    case 54: return talk_shop_reload_ammo();
    case 55: return talk_spell_writer_reserve();
    case 56: return talk_sex();
    case 58:
    {
        if (gdata_left_turns_of_timestop == 0)
        {
            event_add(25);
        }
        return talk_result_t::talk_end;
    }
    case 59: return talk_result_maid_chase_out();
    case 60: return talk_prostitute_buy();
    case 61: return talk_caravan_master_hire();
    }

    if (chatval_ >= 10000)
    {
        return talk_guard_where_is(chatval_);
    }

    if (event_id() == 11)
    {
        levelexitby = 4;
        chatteleport = 1;
        snd(49);
    }

    return talk_result_t::talk_end;
} // namespace elona

} // namespace elona
