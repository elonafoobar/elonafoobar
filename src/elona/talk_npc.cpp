#include "ability.hpp"
#include "activity.hpp"
#include "adventurer.hpp"
#include "area.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "data/types/type_item.hpp"
#include "deferred_event.hpp"
#include "elona.hpp"
#include "food.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "magic.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "menu.hpp"
#include "message.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "talk.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

TalkResult talk_shop_buy()
{
    invctrl = 11;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_shop_sell()
{
    invctrl = 12;
    invfile = cdata[tc].shop_store_id;
    shop_sell_item();
    cc = 0;
    screenupdate = -1;
    update_screen();
    cs = 0;
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_inn_eat()
{
    if (cdata.player().gold < calcmealvalue())
    {
        buff = i18n::s.get("core.ui.no_gold");
        return TalkResult::talk_npc;
    }
    if (cdata.player().nutrition >= 15000)
    {
        buff = i18n::s.get("core.talk.npc.innkeeper.eat.not_hungry", cdata[tc]);
        return TalkResult::talk_npc;
    }
    snd("core.paygold1");
    cdata.player().gold -= calcmealvalue();
    snd("core.eat1");
    cdata.player().nutrition = 15000;
    buff = i18n::s.get("core.talk.npc.innkeeper.eat.here_you_are", cdata[tc]);
    txt(i18n::s.get("core.talk.npc.innkeeper.eat.results"));
    show_eating_message();
    chara_anorexia(cdata.player());
    return TalkResult::talk_npc;
}

TalkResult talk_wizard_identify(int chatval_)
{
    if (cdata.player().gold < calcidentifyvalue(chatval_ - 14))
    {
        buff = i18n::s.get("core.ui.no_gold");
        return TalkResult::talk_npc;
    }
    p = 0;
    for (const auto& item : inv.pc())
    {
        if (item.number() == 0)
        {
            continue;
        }
        if (item.identify_state != IdentifyState::completely)
        {
            ++p;
        }
    }
    if (p == 0)
    {
        buff = i18n::s.get("core.talk.npc.wizard.identify.already", cdata[tc]);
        return TalkResult::talk_npc;
    }
    if (chatval_ == 15)
    {
        cdata.player().gold -= calcidentifyvalue(1);
        p(0) = 0;
        p(1) = 0;
        p(0) = 0;
        p(1) = 0;
        for (auto&& item : inv.pc())
        {
            if (item.number() == 0)
            {
                continue;
            }
            if (item.identify_state != IdentifyState::completely)
            {
                const auto result = item_identify(item, 250);
                item_stack(0, item, true);
                ++p(1);
                if (result >= IdentifyState::completely)
                {
                    ++p;
                }
            }
        }
        txt(i18n::s.get("core.talk.npc.wizard.identify.count", p(0), p(1)));
        buff = i18n::s.get("core.talk.npc.wizard.identify.finished", cdata[tc]);
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
            buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
            return TalkResult::talk_npc;
        }
        if (idtresult == IdentifyState::completely)
        {
            buff = i18n::s.get(
                "core.talk.npc.wizard.identify.finished", cdata[tc]);
        }
        else
        {
            buff = i18n::s.get(
                "core.talk.npc.wizard.identify.need_investigate", cdata[tc]);
        }
        cdata.player().gold -= calcidentifyvalue(chatval_ - 14);
    }
    snd("core.paygold1");
    return TalkResult::talk_npc;
}

TalkResult talk_informer_list_adventurers()
{
    list_adventurers();
    buff = i18n::s.get("core.talk.npc.informer.show_adventurers", cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_healer_restore_attributes()
{
    if (cdata.player().gold < calcrestorecost())
    {
        buff = i18n::s.get("core.ui.no_gold");
        return TalkResult::talk_npc;
    }
    snd("core.paygold1");
    cdata.player().gold -= calcrestorecost();
    tcbk = tc;
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].state() != Character::State::alive)
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
    buff = i18n::s.get("core.talk.npc.healer.restore_attributes", cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_trade()
{
    invsubroutine = 1;
    for (auto&& item : inv.for_chara(cdata[tc]))
    {
        if (item.number() != 0)
        {
            item.identify_state = IdentifyState::completely;
        }
    }
    invctrl(0) = 20;
    invctrl(1) = 0;
    MenuResult result = ctrl_inventory();
    if (!result.succeeded)
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        return TalkResult::talk_npc;
    }
    buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_arena_master(int chatval_)
{
    if (game_data.mount != 0)
    {
        int stat = cell_findspace(
            cdata.player().position.x, cdata.player().position.y, 1);
        if (stat == 0)
        {
            txt(i18n::s.get("core.magic.mount.no_place_to_get_off"));
            return TalkResult::talk_end;
        }
        cell_setchara(game_data.mount, rtval, rtval(1));
        txt(i18n::s.get("core.magic.mount.dismount", cdata[game_data.mount]));
        ride_end();
    }
    game_data.executing_immediate_quest_fame_gained = calcfame(
        0,
        (220 - game_data.ranks.at(0) / 50) *
                (100 +
                 clamp(
                     area_data[game_data.current_map].winning_streak_in_arena,
                     0,
                     50)) /
                100 +
            2);
    listmax = 0;
    randomize(area_data[game_data.current_map].time_of_next_arena);
    if (chatval_ == 21)
    {
        if (area_data[game_data.current_map].time_of_next_arena >
            game_data.date.hours())
        {
            buff = i18n::s.get(
                "core.talk.npc.arena_master.enter.game_is_over", cdata[tc]);
            return TalkResult::talk_npc;
        }
        randomize(area_data[game_data.current_map].arena_random_seed);
        for (int cnt = 0; cnt < 50; ++cnt)
        {
            arenaop(0) = 0;
            arenaop(1) = (100 - game_data.ranks.at(0) / 100) / 3 + 1;
            arenaop(2) = 3;
            if (game_data.ranks.at(0) / 100 < 30)
            {
                arenaop(2) = 4;
            }
            if (game_data.ranks.at(0) / 100 < 10)
            {
                arenaop(2) = 5;
            }
            minlevel = arenaop(1) / 3 * 2;
            flt(arenaop(1));
            fixlv = static_cast<Quality>(arenaop(2));
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
        arenaop(1) = charaid2int(cdata[rc].id);
        buff = i18n::s.get(
            "core.talk.npc.arena_master.enter.target",
            cdatan(0, rc),
            cdata[tc]);
    }
    else
    {
        if (area_data[game_data.current_map].time_of_next_rumble >
            game_data.date.hours())
        {
            buff = i18n::s.get(
                "core.talk.npc.arena_master.enter.game_is_over", cdata[tc]);
            return TalkResult::talk_npc;
        }
        arenaop(0) = 1;
        arenaop(1) = (100 - game_data.ranks.at(0) / 100) / 2 + 1;
        buff = i18n::s.get(
            "core.talk.npc.arena_master.enter.target_group",
            arenaop(1),
            cdata[tc]);
    }
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.arena_master.enter.choices.enter"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.arena_master.enter.choices.leave"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ != 1)
    {
        buff =
            i18n::s.get("core.talk.npc.arena_master.enter.cancel", cdata[tc]);
        return TalkResult::talk_npc;
    }
    if (arenaop == 0)
    {
        area_data[game_data.current_map].time_of_next_arena =
            game_data.date.hours() + 24;
    }
    if (arenaop == 1)
    {
        area_data[game_data.current_map].time_of_next_rumble =
            game_data.date.hours() + 24;
    }
    game_data.executing_immediate_quest_type = 1;
    game_data.executing_immediate_quest_show_hunt_remain = 1;
    game_data.executing_immediate_quest = 0;
    game_data.executing_immediate_quest_status = 1;
    map_prepare_for_travel_with_prev(static_cast<int>(mdata_t::MapId::arena));
    chatteleport = 1;
    return TalkResult::talk_end;
}

TalkResult talk_pet_arena_master(int chatval_)
{
    game_data.executing_immediate_quest_fame_gained = calcfame(
        0,
        (220 - game_data.ranks.at(1) / 50) *
                (50 +
                 clamp(
                     area_data[game_data.current_map]
                         .winning_streak_in_pet_arena,
                     0,
                     50)) /
                100 +
            2);
    listmax = 0;
    if (chatval_ == 40)
    {
        arenaop(0) = 0;
        arenaop(1) = 1;
        arenaop(2) = (100 - game_data.ranks.at(1) / 100) / 3 * 2 + 3;
        buff = i18n::s.get(
            "core.talk.npc.pet_arena_master.register.target",
            arenaop(2),
            cdata[tc]);
    }
    if (chatval_ == 41)
    {
        arenaop(0) = 1;
        arenaop(1) = 2;
        arenaop(2) = (100 - game_data.ranks.at(1) / 100) / 2 + 1;
        arenaop(1) = rnd(7) + 2;
        buff = i18n::s.get(
            "core.talk.npc.pet_arena_master.register.target_group",
            arenaop(1),
            arenaop(2),
            cdata[tc]);
    }
    ELONA_APPEND_RESPONSE(
        1,
        i18n::s.get("core.talk.npc.pet_arena_master.register.choices.enter"));
    ELONA_APPEND_RESPONSE(
        0,
        i18n::s.get("core.talk.npc.pet_arena_master.register.choices.leave"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ != 1)
    {
        buff =
            i18n::s.get("core.talk.npc.arena_master.enter.cancel", cdata[tc]);
        return TalkResult::talk_npc;
    }
    DIM2(followerexist, 16);
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        followerexist(cnt) = static_cast<int>(cdata[cnt].state());
    }
    int stat = ctrl_ally(ControlAllyOperation::pet_arena);
    if (stat == -1)
    {
        buff =
            i18n::s.get("core.talk.npc.arena_master.enter.cancel", cdata[tc]);
        return TalkResult::talk_npc;
    }
    game_data.executing_immediate_quest_type = 2;
    game_data.executing_immediate_quest_show_hunt_remain = 0;
    game_data.executing_immediate_quest = 0;
    game_data.executing_immediate_quest_status = 1;
    map_prepare_for_travel_with_prev(
        static_cast<int>(mdata_t::MapId::pet_arena));
    chatteleport = 1;
    return TalkResult::talk_end;
}

TalkResult talk_pet_arena_master_score()
{
    buff = i18n::s.get(
        "core.talk.npc.arena_master.streak",
        area_data[game_data.current_map].winning_streak_in_pet_arena,
        cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_arena_master_score()
{
    buff = i18n::s.get(
        "core.talk.npc.arena_master.streak",
        area_data[game_data.current_map].winning_streak_in_arena,
        cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_quest_delivery()
{
    int stat = inv_getfreeid_force();
    ti = stat;
    item_copy(deliver(1), ti);
    inv[ti].set_number(1);
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used(cdata[tc], inv[ci]);
    rq = deliver;
    inv[deliver(1)].modify_number(-1);
    txt(i18n::s.get("core.talk.npc.common.hand_over", inv[deliver(1)]));
    quest_set_data(3);
    quest_complete();
    refresh_burden_state();
    return TalkResult::talk_npc;
}

TalkResult talk_quest_supply()
{
    int stat = inv_getfreeid_force();
    ti = stat;
    item_copy(supply, ti);
    inv[ti].set_number(1);
    cdata[tc].was_passed_item_by_you_just_now() = true;
    ci = ti;
    rc = tc;
    chara_set_item_which_will_be_used(cdata[tc], inv[ci]);
    inv[supply].modify_number(-1);
    txt(i18n::s.get("core.talk.npc.common.hand_over", inv[supply]));
    quest_set_data(3);
    quest_complete();
    refresh_burden_state();
    return TalkResult::talk_npc;
}

TalkResult talk_shop_attack()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.shop.attack.dialog", cdata[tc]);
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.shop.attack.choices.attack"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.shop.attack.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        return TalkResult::talk_npc;
    }
    go_hostile();
    return TalkResult::talk_end;
}

TalkResult talk_guard_return_item()
{
    listmax = 0;
    auto wallet_opt = itemfind(0, 284);
    if (!wallet_opt)
    {
        wallet_opt = itemfind(0, 283);
    }
    Item& wallet = *wallet_opt;
    p = wallet.index;
    wallet.modify_number(-1);
    if (wallet.param1 == 0)
    {
        buff = i18n::s.get("core.talk.npc.guard.lost.empty.dialog", cdata[tc]);
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.talk.npc.guard.lost.empty.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(cdata.player(), -5);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.guard.lost.dialog", cdata[tc]);
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.talk.npc.guard.lost.response"));
        chatesc = 1;
        talk_window_query();
        modify_karma(cdata.player(), 5);
        ++game_data.lost_wallet_count;
        if (game_data.lost_wallet_count >= 4)
        {
            listmax = 0;
            buff = i18n::s.get_enum(
                "core.talk.npc.guard.lost.found_often.dialog", 0, cdata[tc]);
            tc = tc * 1 + 0;
            ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
            chatesc = 1;
            ELONA_TALK_SCENE_CUT();
            buff = i18n::s.get_enum(
                "core.talk.npc.guard.lost.found_often.dialog", 1);
            ELONA_APPEND_RESPONSE(
                0,
                i18n::s.get("core.talk.npc.guard.lost.found_often.response"));
            chatesc = 1;
            talk_window_query();
            modify_karma(cdata.player(), -10);
        }
    }
    refresh_burden_state();
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_bartender_call_ally()
{
    int stat = ctrl_ally(ControlAllyOperation::call_back);
    if (stat != -1)
    {
        rc = stat;
        if (cdata[rc].state() == Character::State::alive)
        {
            buff = i18n::s.get(
                "core.talk.npc.bartender.call_ally.no_need", cdata[tc]);
            return TalkResult::talk_npc;
        }
        listmax = 0;
        buff = i18n::s.get(
            "core.talk.npc.bartender.call_ally.cost",
            calcresurrectvalue(rc),
            cdata[tc]);
        if (cdata.player().gold >= calcresurrectvalue(rc))
        {
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get("core.talk.npc.bartender.call_ally.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get("core.talk.npc.bartender.call_ally.choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            snd("core.paygold1");
            cdata.player().gold -= calcresurrectvalue(rc);
            buff = i18n::s.get(
                "core.talk.npc.bartender.call_ally.brings_back",
                cdata[tc],
                cdata[rc]);
            revive_character();
        }
        else
        {
            buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_ally_order_wait()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.ally.wait_at_town", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
        .chara_index_plus_one = 0;
    cdata[tc].set_state(Character::State::pet_waiting);
    cdata[tc].current_map = 0;
    return TalkResult::talk_end;
}

TalkResult talk_ally_abandon()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.ally.abandon.prompt", cdata[tc]);
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.ally.abandon.choices.yes"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.ally.abandon.choices.no"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get("core.talk.npc.ally.abandon.you_abandoned", cdata[tc]));
        cell_data.at(cdata[tc].position.x, cdata[tc].position.y)
            .chara_index_plus_one = 0;
        chara_delete(tc);
        return TalkResult::talk_end;
    }
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_slave_buy(int chatval_)
{
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        flt(cdata.player().level / 2 + 5);
        fixlv = Quality::good;
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
        "core.talk.npc.slave_trader.buy.cost",
        cnven(cdatan(0, 56)),
        calcslavevalue(56),
        cdata[tc]);
    if (cdata.player().gold >= calcslavevalue(56))
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.slave_trader.buy.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.slave_trader.buy.choices.go_back"));
    chatesc = 1;

    chatval_ = talk_window_query();

    if (chatval_ == 1)
    {
        txt(i18n::s.get(
            "core.talk.npc.slave_trader.buy.you_buy", cnven(cdatan(0, 56))));
        snd("core.paygold1");
        cdata.player().gold -= calcslavevalue(56);
        rc = 56;
        new_ally_joins();
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_slave_sell()
{
    int stat = ctrl_ally(ControlAllyOperation::sell);
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get(
            "core.talk.npc.slave_trader.sell.price",
            (calcslavevalue(rc) * 2 / 3),
            cdata[tc]);
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.slave_trader.sell.choices.deal"));
        ELONA_APPEND_RESPONSE(
            0, i18n::s.get("core.talk.npc.slave_trader.sell.choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            txt(i18n::s.get(
                "core.talk.npc.slave_trader.sell.you_sell_off",
                cnven(cdatan(0, rc))));
            snd("core.getgold1");
            earn_gold(cdata.player(), calcslavevalue(rc) * 2 / 3);
            if (cdata[rc].state() == Character::State::alive)
            {
                cell_data.at(cdata[rc].position.x, cdata[rc].position.y)
                    .chara_index_plus_one = 0;
            }
            if (cdata[rc].is_escorted() == 1)
            {
                event_add(15, charaid2int(cdata[rc].id));
            }
            chara_delete(rc);
            buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
        }
        else
        {
            buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_ally_marriage()
{
    if (cdata[tc].impression < 200)
    {
        buff = i18n::s.get("core.talk.npc.ally.marriage.refuses", cdata[tc]);
        return TalkResult::talk_npc;
    }
    cdata[tc].is_married() = true;
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.ally.marriage.accepts");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    marry = tc;
    event_add(13);
    return TalkResult::talk_end;
}

TalkResult talk_ally_gene()
{
    if (game_data.current_map == mdata_t::MapId::shelter_)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.npc.ally.make_gene.refuses");
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        return TalkResult::talk_end;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.ally.make_gene.accepts");
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    cdata[tc].has_made_gene() = true;
    if (game_data.wizard == 0)
    {
        game_data.character_and_status_for_gene = tc;
    }
    return TalkResult::talk_end;
}

TalkResult talk_innkeeper_shelter()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.innkeeper.go_to_shelter", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    map_prepare_for_travel_with_prev(
        static_cast<int>(mdata_t::MapId::shelter_));
    chatteleport = 1;
    snd("core.exitmap1");
    return TalkResult::talk_end;
}

TalkResult talk_servant_fire()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.servant.fire.prompt", cdata[tc]);
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.servant.fire.choices.yes"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.servant.fire.choices.no"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get("core.talk.npc.servant.fire.you_dismiss", cdata[tc]));
        chara_vanquish(tc);
        calccosthire();
        return TalkResult::talk_end;
    }
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_maid_think_of_house_name()
{
    mdatan(0) = random_title(RandomTitleType::character);
    if (rnd(5))
    {
        mdatan(0) = i18n::s.get(
            "core.talk.npc.maid.think_of_house_name.suffixes", mdatan(0));
    }
    screenupdate = -1;
    update_entire_screen();
    buff = i18n::s.get(
        "core.talk.npc.maid.think_of_house_name.come_up_with",
        mdatan(0),
        cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_sister_buy_indulgence()
{
    if (cdata.player().karma >= -30)
    {
        buff =
            i18n::s.get("core.talk.npc.sister.buy_indulgence.karma_is_not_low");
        return TalkResult::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.npc.sister.buy_indulgence.cost",
        calcguiltvalue(),
        cdata[tc]);
    if (cdata.player().gold >= calcguiltvalue())
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.sister.buy_indulgence.choices.buy"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.sister.buy_indulgence.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd("core.paygold1");
        cdata.player().gold -= calcguiltvalue();
        modify_karma(cdata.player(), (cdata.player().karma - -30) * -1 + 1);
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_informer_investigate_ally()
{
    int tcchat = tc;
    int stat = ctrl_ally(ControlAllyOperation::investigate);
    if (stat != -1)
    {
        rc = stat;
        listmax = 0;
        buff = i18n::s.get(
            "core.talk.npc.informer.investigate_ally.cost", cdata[tc]);
        if (cdata.player().gold >= 10000)
        {
            ELONA_APPEND_RESPONSE(
                1,
                i18n::s.get(
                    "core.talk.npc.informer.investigate_ally.choices.pay"));
        }
        ELONA_APPEND_RESPONSE(
            0,
            i18n::s.get(
                "core.talk.npc.informer.investigate_ally.choices.go_back"));
        chatesc = 1;
        int chatval_ = talk_window_query();
        if (chatval_ == 1)
        {
            snd("core.paygold1");
            cdata.player().gold -= 10000;
            cc = rc;
            snd("core.pop2");
            menu_character_sheet_investigate();
            cc = 0;
            talk_start();
            buff = "";
        }
        else
        {
            buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    tc = tcchat;
    return TalkResult::talk_npc;
}

TalkResult talk_ally_silence()
{
    if (cdata[tc].is_silent() == 0)
    {
        cdata[tc].is_silent() = true;
        buff = i18n::s.get("core.talk.npc.ally.silence.start", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.ally.silence.stop", cdata[tc]);
        cdata[tc].is_silent() = false;
    }
    return TalkResult::talk_npc;
}

TalkResult talk_adventurer_hire()
{
    buff = i18n::s.get(
        "core.talk.npc.adventurer.hire.cost", calchireadv(tc), cdata[tc]);
    if (cdata.player().gold >= calchireadv(tc))
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.adventurer.hire.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.adventurer.hire.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd("core.paygold1");
        cdata.player().gold -= calchireadv(tc);
        cdata[tc].relationship = 10;
        cdata[tc].is_contracting() = true;
        cdata[tc].period_of_contract = game_data.date.hours() + 168;
        ++cdata[tc].hire_count;
        snd("core.pray1");
        txt(i18n::s.get("core.talk.npc.adventurer.hire.you_hired", cdata[tc]),
            Message::color{ColorIndex::orange});
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_adventurer_join()
{
    if (cdata.player().level * 3 / 2 + 10 < cdata[tc].level)
    {
        buff = i18n::s.get("core.talk.npc.adventurer.join.too_weak", cdata[tc]);
        return TalkResult::talk_npc;
    }
    if (cdata[tc].impression >= 200 && cdata[tc].hire_count > 2)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.npc.adventurer.join.accept", cdata[tc]);
        tc = tc * 1 + 0;
        ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
        chatesc = 1;
        ELONA_TALK_SCENE_CUT();
        f = chara_get_free_slot_ally();
        if (f == 0)
        {
            buff = i18n::s.get(
                "core.talk.npc.adventurer.join.party_full", cdata[tc]);
            return TalkResult::talk_npc;
        }
        rc = tc;
        new_ally_joins();
        cdata[rc].character_role = 0;
        cdata[rc].current_map = 0;
        cdata[tc].impression = 100;
        rc = oc;
        create_adventurer();
        return TalkResult::talk_end;
    }
    buff = i18n::s.get("core.talk.npc.adventurer.join.not_known", cdata[tc]);
    return TalkResult::talk_npc;
}

TalkResult talk_moyer_sell_paels_mom()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.moyer.sell_paels_mom.prompt");
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.moyer.sell_paels_mom.choices.sell"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.moyer.sell_paels_mom.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        txt(i18n::s.get("core.talk.npc.moyer.sell_paels_mom.you_sell"));
        modify_karma(cdata.player(), -20);
        snd("core.getgold1");
        earn_gold(cdata.player(), 50000);
        game_data.quest_flags.pael_and_her_mom = 1002;
        rc = chara_find("core.lily");
        cdata[rc].ai_calm = 3;
        cdata[rc].relationship = 0;
        cdata[rc].initial_position.x = 48;
        cdata[rc].initial_position.y = 18;
        cell_movechara(rc, 48, 18);
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_wizard_return()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.wizard.return", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    try_to_return();
    return TalkResult::talk_end;
}

TalkResult talk_shop_reload_ammo()
{
    if (calccostreload(0) == 0)
    {
        buff = i18n::s.get("core.talk.npc.shop.ammo.no_ammo", cdata[tc]);
        return TalkResult::talk_npc;
    }
    buff = i18n::s.get(
        "core.talk.npc.shop.ammo.cost", calccostreload(0), cdata[tc]);
    if (cdata.player().gold >= calccostreload(0))
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.shop.ammo.choices.pay"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.shop.ammo.choices.go_back"));
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd("core.paygold1");
        cdata.player().gold -= calccostreload(0);
        p = calccostreload(0, true);
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_spell_writer_reserve()
{
    screenupdate = -1;
    update_screen();
    invctrl = 0;
    show_spell_writer_menu();
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_sex()
{
    ELONA_APPEND_RESPONSE(
        1, i18n::s.get("core.talk.npc.common.sex.choices.accept"));
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.common.sex.choices.go_back"));
    buff = i18n::s.get("core.talk.npc.common.sex.prompt", cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        return TalkResult::talk_npc;
    }
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.common.sex.start", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.talk.npc.common.sex.response"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    activity_sex();
    return TalkResult::talk_end;
}

TalkResult talk_result_maid_chase_out()
{
    --game_data.number_of_waiting_guests;
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.maid.do_not_meet", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    buff = "";
    return TalkResult::talk_npc;
}

TalkResult talk_prostitute_buy()
{
    int sexvalue = sdata(17, tc) * 25 + 100 + cdata.player().fame / 10;
    if (cdata.player().gold >= sexvalue)
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.common.sex.choices.accept"));
    }
    ELONA_APPEND_RESPONSE(
        0, i18n::s.get("core.talk.npc.common.sex.choices.go_back"));
    buff = i18n::s.get("core.talk.npc.prostitute.buy", sexvalue, cdata[tc]);
    int chatval_ = talk_window_query();
    if (chatval_ != 1)
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        return TalkResult::talk_npc;
    }
    snd("core.paygold1");
    cdata[cc].gold -= sexvalue;
    earn_gold(cdata[tc], sexvalue);
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.common.sex.start", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.talk.npc.common.sex.response"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    cc = tc;
    tc = 0;
    activity_sex();
    cc = 0;
    return TalkResult::talk_end;
}

TalkResult talk_caravan_master_hire()
{
    map_set_caravan_destinations();

    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (p(cnt) == 0)
        {
            ELONA_APPEND_RESPONSE(
                0,
                i18n::s.get(
                    "core.talk.npc.caravan_master.hire.choices.go_back"));
            break;
        }
        ELONA_APPEND_RESPONSE(p(cnt), mapname(p(cnt)));
    }
    buff = i18n::s.get("core.talk.npc.caravan_master.hire.tset");
    int chatval_ = talk_window_query();
    if (chatval_ <= 0)
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
        return TalkResult::talk_npc;
    }
    game_data.destination_map = area_data[chatval_].outer_map;
    game_data.destination_dungeon_level = 1;
    levelexitby = 4;
    game_data.reset_world_map_in_diastrophism_flag = 1;
    game_data.destination_outer_map = area_data[chatval_].outer_map;
    game_data.pc_x_in_world_map = area_data[chatval_].position.x;
    game_data.pc_y_in_world_map = area_data[chatval_].position.y;
    fixtransfermap = 1;
    chatteleport = 1;
    return TalkResult::talk_end;
}

TalkResult talk_guard_where_is(int chatval_)
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
        s = i18n::s.get("core.talk.npc.guard.where_is.direction.west");
    }
    else if (p == 2)
    {
        s = i18n::s.get("core.talk.npc.guard.where_is.direction.east");
    }
    else if (p == 3)
    {
        s = i18n::s.get("core.talk.npc.guard.where_is.direction.north");
    }
    else
    {
        s = i18n::s.get("core.talk.npc.guard.where_is.direction.south");
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
            s = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
            break;
        }
        if (cdata[rc].state() != Character::State::alive)
        {
            s = i18n::s.get("core.talk.npc.guard.where_is.dead", cdata[tc]);
            break;
        }
        if (p < 6)
        {
            s = i18n::s.get(
                "core.talk.npc.guard.where_is.very_close",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 12)
        {
            s = i18n::s.get(
                "core.talk.npc.guard.where_is.close",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 20)
        {
            s = i18n::s.get(
                "core.talk.npc.guard.where_is.moderate",
                s(0),
                cdata[rc],
                cdata[tc]);
            break;
        }
        if (p < 35)
        {
            s = i18n::s.get(
                "core.talk.npc.guard.where_is.far", s(0), cdata[rc], cdata[tc]);
            break;
        }
        s = i18n::s.get(
            "core.talk.npc.guard.where_is.very_far",
            s(0),
            cdata[rc],
            cdata[tc]);
        break;
    }
    buff = s;
    return TalkResult::talk_npc;
}

TalkResult talk_accepted_quest()
{
    if (quest_data[rq].id == 1001 || quest_data[rq].id == 1010)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.npc.quest_giver.accept.hunt", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
    }
    if (quest_data[rq].id == 1006)
    {
        listmax = 0;
        buff =
            i18n::s.get("core.talk.npc.quest_giver.accept.harvest", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
    }
    if (quest_data[rq].id == 1009)
    {
        listmax = 0;
        buff = i18n::s.get("core.talk.npc.quest_giver.accept.party", cdata[tc]);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.ui.more");
        ++listmax;
        chatesc = 1;
        talk_window_query();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                return TalkResult::talk_end;
            }
        }
    }
    game_data.executing_immediate_quest_type = quest_data[rq].id;
    game_data.executing_immediate_quest_show_hunt_remain =
        quest_data[rq].client_chara_type;
    game_data.executing_immediate_quest = rq;
    game_data.executing_immediate_quest_status = 1;
    map_prepare_for_travel_with_prev(static_cast<int>(mdata_t::MapId::quest));
    chatteleport = 1;
    return TalkResult::talk_end;
}

TalkResult talk_trainer(bool is_training)
{
    tcbk = tc;
    menucycle = 0;
    optional<int> selected_skill_opt =
        menu_character_sheet_trainer(is_training);
    talk_start();
    if (!selected_skill_opt)
    {
        buff = i18n::s.get("core.talk.npc.trainer.leave", cdata[tc]);
        return TalkResult::talk_npc;
    }
    int selected_skill = *selected_skill_opt;
    listmax = 0;
    if (is_training)
    {
        buff = i18n::s.get(
            "core.talk.npc.trainer.cost.training",
            i18n::s.get_m(
                "ability",
                the_ability_db.get_id_from_legacy(selected_skill)->get(),
                "name"),
            calctraincost(selected_skill, cc),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calctraincost(selected_skill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) =
                i18n::s.get("core.talk.npc.trainer.choices.train.accept");
            ++listmax;
        }
    }
    else
    {
        buff = i18n::s.get(
            "core.talk.npc.trainer.cost.learning",
            i18n::s.get_m(
                "ability",
                the_ability_db.get_id_from_legacy(selected_skill)->get(),
                "name"),
            calclearncost(selected_skill, cc),
            cdata[tc]);
        if (cdata.player().platinum_coin >= calclearncost(selected_skill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) =
                i18n::s.get("core.talk.npc.trainer.choices.learn.accept");
            ++listmax;
        }
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.npc.trainer.choices.go_back");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd("core.paygold1");
        if (is_training)
        {
            cdata.player().platinum_coin -= calctraincost(selected_skill, cc);
            modify_potential(
                cdata[cc],
                selected_skill,
                clamp(
                    15 - sdata.get(selected_skill, cc).potential / 15, 2, 15));
            buff =
                i18n::s.get("core.talk.npc.trainer.finish.training", cdata[tc]);
        }
        else
        {
            cdata.player().platinum_coin -= calclearncost(selected_skill, cc);
            chara_gain_skill(cdata[cc], selected_skill);
            ++game_data.number_of_learned_skills_by_trainer;
            buff =
                i18n::s.get("core.talk.npc.trainer.finish.learning", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.trainer.leave", cdata[tc]);
    }
    return TalkResult::talk_npc;
}

TalkResult talk_trainer_train_skill()
{
    return talk_trainer(true);
}

TalkResult talk_trainer_learn_skill()
{
    return talk_trainer(false);
}


TalkResult talk_invest()
{
    listmax = 0;
    buff = i18n::s.get(
        "core.talk.npc.shop.invest.ask", calcinvestvalue(), cdata[tc]);
    if (cdata.player().gold >= calcinvestvalue())
    {
        list(0, listmax) = 1;
        listn(0, listmax) =
            i18n::s.get("core.talk.npc.shop.invest.choices.invest");
        ++listmax;
    }
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.talk.npc.shop.invest.choices.reject");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        snd("core.paygold1");
        cdata.player().gold -= calcinvestvalue();
        chara_gain_exp_investing(cdata.player());
        cdata[tc].shop_rank += rnd(2) + 2;
        buff = i18n::s.get("core.talk.npc.common.thanks", cdata[tc]);
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        calccosthire();
    }
    return TalkResult::talk_npc;
}

TalkResult talk_finish_escort()
{
    listmax = 0;
    buff = i18n::s.get("core.talk.npc.quest_giver.finish.escort", cdata[tc]);
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.ui.more");
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (scenemode)
    {
        if (scene_cut == 1)
        {
            return TalkResult::talk_end;
        }
    }
    return TalkResult::talk_end;
}



TalkResult talk_quest_giver()
{
    if (quest_data[rq].progress == 1)
    {
        buff = i18n::s.get("core.talk.npc.quest_giver.about.during", cdata[tc]);
        return TalkResult::talk_npc;
    }
    quest_set_data(1);
    listmax = 0;
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.talk.npc.quest_giver.about.choices.take");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.talk.npc.quest_giver.about.choices.leave");
    ++listmax;
    chatesc = 1;
    int chatval_ = talk_window_query();
    if (chatval_ == 1)
    {
        p = 0;
        for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (quest_data[cnt].id == 0)
            {
                continue;
            }
            if (quest_data[cnt].progress != 0)
            {
                ++p;
            }
        }
        if (p >= 5)
        {
            buff = i18n::s.get(
                "core.talk.npc.quest_giver.about.too_many_unfinished",
                cdata[tc]);
            return TalkResult::talk_npc;
        }
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            p = game_data.taken_quests.at(cnt);
            f = 0;
            for (int cnt = 0; cnt < 5; ++cnt)
            {
                if (game_data.taken_quests.at(cnt) == p)
                {
                    ++f;
                }
            }
            if (quest_data[p].progress == 0 || f > 1)
            {
                game_data.taken_quests.at(cnt) = rq;
                break;
            }
        }
        if (quest_data[rq].id == 1002)
        {
            if (inv_getfreeid(0) == -1)
            {
                buff = i18n::s.get(
                    "core.talk.npc.quest_giver.about.backpack_full", cdata[tc]);
                return TalkResult::talk_npc;
            }
        }
        if (quest_data[rq].id == 1007)
        {
            f = chara_get_free_slot_ally();
            if (f == 0)
            {
                buff = i18n::s.get(
                    "core.talk.npc.quest_giver.about.party_full", cdata[tc]);
                return TalkResult::talk_npc;
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
                flt(quest_data[rq].difficulty + cnt, Quality::bad);
                fltn(u8"man"s);
                int stat = chara_create(56, dbid, -3, 0);
                f = stat;
                if (f == 1)
                {
                    for (int cnt = 0; cnt < 16; ++cnt)
                    {
                        if (cdata[cnt].state() == Character::State::empty)
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
            quest_data[rq].extra_info_2 = charaid2int(cdata[rc].id);
        }
        quest_data[rq].progress = 1;
        if (quest_data[rq].deadline_days == -1)
        {
            return talk_accepted_quest();
        }
        buff = i18n::s.get("core.talk.npc.quest_giver.about.thanks", cdata[tc]);
        if (quest_data[rq].id == 1002)
        {
            ++quest_data[quest_data[rq].target_chara_index]
                  .delivery_has_package_flag;
            flt();
            itemcreate_player_inv(quest_data[rq].target_item_id, 0);
            txt(i18n::s.get("core.common.you_put_in_your_backpack", inv[ci]));
            snd("core.inv");
            refresh_burden_state();
            buff = i18n::s.get(
                "core.talk.npc.quest_giver.about.here_is_package", cdata[tc]);
        }
    }
    else
    {
        buff = i18n::s.get("core.talk.npc.common.you_kidding", cdata[tc]);
    }
    return TalkResult::talk_npc;
}



/// Check whether character at `chara_index` is one of the targets of the
/// trading quests you are taking now.
bool _talk_check_trade(int chara_index)
{
    for (const auto& quest_index : game_data.taken_quests)
    {
        const auto& quest = quest_data[quest_index];
        if (quest.progress == 1 &&
            quest.originating_map_id == game_data.current_map &&
            game_data.current_dungeon_level == 1 &&
            chara_index == quest.target_chara_index)
        {
            return true;
        }
    }

    return false;
}

} // namespace

void talk_wrapper(TalkResult initial)
{
    TalkResult result = initial;
    bool finished = false;
    while (!finished)
    {
        switch (result)
        {
        case TalkResult::talk_npc: result = talk_npc(); break;
        case TalkResult::talk_unique: result = talk_unique(); break;
        case TalkResult::talk_quest_giver: result = talk_quest_giver(); break;
        case TalkResult::talk_house_visitor:
            result = talk_house_visitor();
            break;
        case TalkResult::talk_sleeping: result = talk_sleeping(); break;
        case TalkResult::talk_busy: result = talk_busy(); break;
        case TalkResult::talk_ignored: result = talk_ignored(); break;
        case TalkResult::talk_finish_escort:
            result = talk_finish_escort();
            break;
        case TalkResult::talk_game_begin: result = talk_game_begin(); break;
        case TalkResult::talk_more: result = talk_more(); break;
        case TalkResult::talk_end:
            talk_end();
            finished = true;
            break;
        default: assert(0); break;
        }
    }
}


TalkResult talk_npc()
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
                    cdata[tc].time_interest_revive = game_data.date.hours() + 8;
                }
            }
        }
    }
    if (cdata[tc].character_role == 18)
    {
        if (game_data.number_of_waiting_guests > 0)
        {
            ELONA_APPEND_RESPONSE(
                58, i18n::s.get("core.talk.npc.maid.choices.meet_guest"));
            ELONA_APPEND_RESPONSE(
                59, i18n::s.get("core.talk.npc.maid.choices.do_not_meet"));
        }
    }
    if (cdata[tc].interest > 0 && !chatval_unique_chara_id)
    {
        ELONA_APPEND_RESPONSE(
            1, i18n::s.get("core.talk.npc.common.choices.talk"));
    }
    if ((cdata[tc].character_role >= 1000 && cdata[tc].character_role < 2000) ||
        cdata[tc].character_role == 2003)
    {
        ELONA_APPEND_RESPONSE(
            10, i18n::s.get("core.talk.npc.shop.choices.buy"));
        ELONA_APPEND_RESPONSE(
            11, i18n::s.get("core.talk.npc.shop.choices.sell"));
        if (cdata[tc].character_role == 1010)
        {
            ELONA_APPEND_RESPONSE(
                31, i18n::s.get("core.talk.npc.shop.choices.attack"));
        }
        if (cdata[tc].character_role != 1010 &&
            cdata[tc].character_role != 1009)
        {
            ELONA_APPEND_RESPONSE(
                12, i18n::s.get("core.talk.npc.shop.choices.invest"));
        }
    }
    if (cdata[tc].character_role == 9)
    {
        ELONA_APPEND_RESPONSE(
            33, i18n::s.get("core.talk.npc.bartender.choices.call_ally"));
    }
    if (cdata[tc].character_role == 17)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                36, i18n::s.get("core.talk.npc.slave_trader.choices.buy"));
        }
        ELONA_APPEND_RESPONSE(
            37, i18n::s.get("core.talk.npc.slave_trader.choices.sell"));
    }
    if (cdata[tc].character_role == 22)
    {
        if (chara_get_free_slot_ally() != 0)
        {
            ELONA_APPEND_RESPONSE(
                57, i18n::s.get("core.talk.npc.horse_keeper.choices.buy"));
        }
    }
    if (tc < 16)
    {
        if (cdata[tc].is_escorted() == 0)
        {
            if (cdata[tc].is_escorted_in_sub_quest() == 0)
            {
                ELONA_APPEND_RESPONSE(
                    34, i18n::s.get("core.talk.npc.ally.choices.wait_at_town"));
                if (cdata[tc].is_married() == 0)
                {
                    ELONA_APPEND_RESPONSE(
                        38,
                        i18n::s.get(
                            "core.talk.npc.ally.choices.ask_for_marriage"));
                }
                else if (game_data.continuous_active_hours >= 15)
                {
                    ELONA_APPEND_RESPONSE(
                        39,
                        i18n::s.get("core.talk.npc.ally.choices.make_gene"));
                }
                if (cdata[tc].can_talk != 0)
                {
                    if (cdata[tc].is_silent() == 0)
                    {
                        ELONA_APPEND_RESPONSE(
                            48,
                            i18n::s.get(
                                "core.talk.npc.ally.choices.silence.start"));
                    }
                    else
                    {
                        ELONA_APPEND_RESPONSE(
                            48,
                            i18n::s.get(
                                "core.talk.npc.ally.choices.silence.stop"));
                    }
                }
                ELONA_APPEND_RESPONSE(
                    35, i18n::s.get("core.talk.npc.ally.choices.abandon"));
            }
        }
    }
    if (cdata[tc].character_role == 1000 || cdata[tc].character_role == 1001)
    {
        ELONA_APPEND_RESPONSE(
            54, i18n::s.get("core.talk.npc.shop.choices.ammo"));
    }
    if (cdata[tc].character_role == 1005)
    {
        ELONA_APPEND_RESPONSE(
            13,
            i18n::s.get("core.talk.npc.innkeeper.choices.eat") + u8" ("s +
                calcmealvalue() + i18n::s.get("core.ui.gold") + u8")"s);
        if (game_data.weather == 1 || game_data.weather == 4 ||
            game_data.weather == 2)
        {
            ELONA_APPEND_RESPONSE(
                43,
                i18n::s.get("core.talk.npc.innkeeper.choices.go_to_shelter"));
        }
    }
    if (cdata[tc].character_role == 5)
    {
        ELONA_APPEND_RESPONSE(
            14,
            i18n::s.get("core.talk.npc.wizard.choices.identify") + u8" ("s +
                calcidentifyvalue(0) + i18n::s.get("core.ui.gold") + u8")"s);
        ELONA_APPEND_RESPONSE(
            15,
            i18n::s.get("core.talk.npc.wizard.choices.identify_all") + u8" ("s +
                calcidentifyvalue(1) + i18n::s.get("core.ui.gold") + u8")"s);
        ELONA_APPEND_RESPONSE(
            16,
            i18n::s.get("core.talk.npc.wizard.choices.investigate") + u8" ("s +
                calcidentifyvalue(2) + i18n::s.get("core.ui.gold") + u8")"s);
    }
    if (cdata[tc].character_role == 7)
    {
        ELONA_APPEND_RESPONSE(
            17, i18n::s.get("core.talk.npc.trainer.choices.train.ask"));
        ELONA_APPEND_RESPONSE(
            30, i18n::s.get("core.talk.npc.trainer.choices.learn.ask"));
    }
    if (cdata[tc].character_role == 8)
    {
        ELONA_APPEND_RESPONSE(
            18, i18n::s.get("core.talk.npc.informer.choices.show_adventurers"));
        ELONA_APPEND_RESPONSE(
            47, i18n::s.get("core.talk.npc.informer.choices.investigate_ally"));
    }
    if (cdata[tc].character_role == 12)
    {
        ELONA_APPEND_RESPONSE(
            19,
            i18n::s.get("core.talk.npc.healer.choices.restore_attributes") +
                u8"("s + calcrestorecost() + i18n::s.get("core.ui.gold") +
                u8")"s);
    }
    if (cdata[tc].character_role == 13)
    {
        ELONA_APPEND_RESPONSE(
            20, i18n::s.get("core.talk.npc.common.choices.trade"));
        if (cdata[tc].is_contracting() == 0)
        {
            ELONA_APPEND_RESPONSE(
                50, i18n::s.get("core.talk.npc.adventurer.choices.hire"));
            ELONA_APPEND_RESPONSE(
                51, i18n::s.get("core.talk.npc.adventurer.choices.join"));
        }
    }
    if (cdata[tc].character_role == 10)
    {
        ELONA_APPEND_RESPONSE(
            21, i18n::s.get("core.talk.npc.arena_master.choices.enter_duel"));
        ELONA_APPEND_RESPONSE(
            22, i18n::s.get("core.talk.npc.arena_master.choices.enter_rumble"));
        ELONA_APPEND_RESPONSE(
            23, i18n::s.get("core.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 11)
    {
        ELONA_APPEND_RESPONSE(
            40,
            i18n::s.get(
                "core.talk.npc.pet_arena_master.choices.register_duel"));
        ELONA_APPEND_RESPONSE(
            41,
            i18n::s.get(
                "core.talk.npc.pet_arena_master.choices.register_team"));
        ELONA_APPEND_RESPONSE(
            42, i18n::s.get("core.talk.npc.arena_master.choices.score"));
    }
    if (cdata[tc].character_role == 18)
    {
        ELONA_APPEND_RESPONSE(
            45, i18n::s.get("core.talk.npc.maid.choices.think_of_house_name"));
    }
    if (cdata[tc].character_role == 19)
    {
        ELONA_APPEND_RESPONSE(
            46, i18n::s.get("core.talk.npc.sister.choices.buy_indulgence"));
    }
    if (_talk_check_trade(tc))
    {
        ELONA_APPEND_RESPONSE(
            20, i18n::s.get("core.talk.npc.common.choices.trade"));
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
                        "core.talk.npc.guard.choices.where_is",
                        cdata[rtval(cnt)]));
            }
        }
        if (itemfind(0, 284))
        {
            ELONA_APPEND_RESPONSE(
                32, i18n::s.get("core.talk.npc.guard.choices.lost_wallet"));
        }
        else if (itemfind(0, 283))
        {
            ELONA_APPEND_RESPONSE(
                32, i18n::s.get("core.talk.npc.guard.choices.lost_suitcase"));
        }
    }
    if (cdata[tc].character_role == 21)
    {
        ELONA_APPEND_RESPONSE(
            53, i18n::s.get("core.talk.npc.wizard.choices.return"));
    }
    if (cdata[tc].character_role == 1020)
    {
        if (game_data.guild.belongs_to_mages_guild != 0)
        {
            ELONA_APPEND_RESPONSE(
                55, i18n::s.get("core.talk.npc.spell_writer.choices.reserve"));
        }
    }
    if (cdata[tc].drunk != 0 || 0)
    {
        if (game_data.current_map != mdata_t::MapId::show_house)
        {
            if (tc >= 16)
            {
                if (!event_has_pending_events())
                {
                    ELONA_APPEND_RESPONSE(
                        56, i18n::s.get("core.talk.npc.common.choices.sex"));
                }
            }
        }
    }
    if (cdata[tc].id == CharaId::prostitute)
    {
        if (!event_has_pending_events())
        {
            ELONA_APPEND_RESPONSE(
                60, i18n::s.get("core.talk.npc.prostitute.choices.buy"));
        }
    }
    if (cdata[tc].character_role == 23)
    {
        ELONA_APPEND_RESPONSE(
            61, i18n::s.get("core.talk.npc.caravan_master.choices.hire"));
    }
    f = 0;
    deliver(0) = -1;
    deliver(1) = -1;
    if (game_data.current_dungeon_level == 1)
    {
        for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (quest_data[cnt].originating_map_id == game_data.current_map)
            {
                if (quest_data[cnt].client_chara_index == tc)
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
        for (int cnt = 0, cnt_end = (game_data.number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (quest_data[cnt].id == 0)
            {
                continue;
            }
            if (quest_data[cnt].progress != 1)
            {
                continue;
            }
            if (quest_data[cnt].client_chara_type == 2)
            {
                if (quest_data[cnt].target_chara_index == rq)
                {
                    p = quest_data[cnt].target_item_id;
                    deliver = cnt;
                    for (const auto& item : inv.pc())
                    {
                        if (item.number() == 0)
                        {
                            continue;
                        }
                        if (item.id == int2itemid(p))
                        {
                            deliver(1) = item.index;
                            break;
                        }
                    }
                }
            }
        }
        if (quest_data[rq].progress == 3)
        {
            quest_set_data(3);
            quest_complete();
        }
        else if (
            quest_data[rq].client_chara_type == 3 &&
            quest_data[rq].progress == 1)
        {
            supply = -1;
            for (const auto& item : inv.pc())
            {
                if (item.number() == 0)
                {
                    continue;
                }
                if (item.is_marked_as_no_drop())
                {
                    continue;
                }
                if (quest_data[rq].id == 1003)
                {
                    if (the_item_db[itemid2int(item.id)]->category == 57000 &&
                        item.param1 / 1000 == quest_data[rq].extra_info_1 &&
                        item.param2 == quest_data[rq].extra_info_2)
                    {
                        supply = item.index;
                        break;
                    }
                }
                if (quest_data[rq].id == 1004 || quest_data[rq].id == 1011)
                {
                    if (item.id == int2itemid(quest_data[rq].target_item_id))
                    {
                        supply = item.index;
                        break;
                    }
                }
            }
            if (supply != -1)
            {
                ELONA_APPEND_RESPONSE(
                    26,
                    i18n::s.get(
                        "core.talk.npc.quest_giver.choices.here_is_item",
                        inv[supply]));
            }
            else
            {
                ELONA_APPEND_RESPONSE(
                    24,
                    i18n::s.get(
                        "core.talk.npc.quest_giver.choices.about_the_work"));
            }
        }
        else if (quest_data[rq].id != 0)
        {
            ELONA_APPEND_RESPONSE(
                24,
                i18n::s.get(
                    "core.talk.npc.quest_giver.choices.about_the_work"));
        }
    }
    if (deliver != -1 && deliver(1) != -1)
    {
        ELONA_APPEND_RESPONSE(
            25,
            i18n::s.get("core.talk.npc.quest_giver.choices.here_is_delivery"));
    }
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        if (tc >= 57)
        {
            if (cdata[tc].character_role != 0)
            {
                if ((cdata[tc].character_role < 2000 ||
                     cdata[tc].character_role >= 3000) &&
                    !event_has_pending_events())
                {
                    ELONA_APPEND_RESPONSE(
                        44, i18n::s.get("core.talk.npc.servant.choices.fire"));
                }
            }
        }
    }
    if (cdata[tc].character_role == 1015)
    {
        if (game_data.quest_flags.pael_and_her_mom == 1000)
        {
            rc = chara_find("core.lily");
            if (rc != 0)
            {
                if (cdata[rc].state() == Character::State::alive)
                {
                    ELONA_APPEND_RESPONSE(
                        52,
                        i18n::s.get(
                            "core.talk.npc.moyer.choices.sell_paels_mom"));
                }
            }
        }
    }
    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.bye"));
    chatesc = 1;

    int chatval_ = talk_window_query();

    if (chatval_ == 10 || chatval_ == 11)
    {
        if ((cdata[tc].character_role >= 1000 &&
             cdata[tc].character_role < 2000) ||
            cdata[tc].character_role == 2003)
        {
            if (cdata.player().karma < -30 &&
                cdata.player().is_incognito() == 0)
            {
                if (game_data.current_map != mdata_t::MapId::derphy &&
                    game_data.current_map != mdata_t::MapId::your_home)
                {
                    listmax = 0;
                    if (chatval_ == 10)
                    {
                        buff = i18n::s.get(
                            "core.talk.npc.shop.criminal.buy", cdata[tc]);
                    }
                    else
                    {
                        buff = i18n::s.get(
                            "core.talk.npc.shop.criminal.sell", cdata[tc]);
                    }
                    tc = tc * 1 + 0;
                    ELONA_APPEND_RESPONSE(0, i18n::s.get("core.ui.more"));
                    chatesc = 1;
                    ELONA_TALK_SCENE_CUT();
                    return TalkResult::talk_npc;
                }
            }
        }
    }

    switch (chatval_)
    {
    case 1: buff = ""; return TalkResult::talk_npc;
    case 10: return talk_shop_buy();
    case 11: return talk_shop_sell();
    case 12: return talk_invest();
    case 13: return talk_inn_eat();
    case 14:
    case 15:
    case 16: return talk_wizard_identify(chatval_);
    case 17: return talk_trainer_train_skill();
    case 18: return talk_informer_list_adventurers();
    case 19: return talk_healer_restore_attributes();
    case 20: return talk_trade();
    case 21:
    case 22: return talk_arena_master(chatval_);
    case 40:
    case 41: return talk_pet_arena_master(chatval_);
    case 42: return talk_pet_arena_master_score();
    case 23: return talk_arena_master_score();
    case 24: return TalkResult::talk_quest_giver;
    case 25: return talk_quest_delivery();
    case 26: return talk_quest_supply();
    case 30: return talk_trainer_learn_skill();
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
        if (game_data.left_turns_of_timestop == 0)
        {
            event_add(25);
        }
        return TalkResult::talk_end;
    }
    case 59: return talk_result_maid_chase_out();
    case 60: return talk_prostitute_buy();
    case 61: return talk_caravan_master_hire();
    }

    if (chatval_ >= 10000)
    {
        return talk_guard_where_is(chatval_);
    }

    if (event_processing_event() == 11)
    {
        levelexitby = 4;
        chatteleport = 1;
        snd("core.exitmap1");
    }

    return TalkResult::talk_end;
}

} // namespace elona
