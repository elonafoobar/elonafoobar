#include "talk.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "adventurer.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "mef.hpp"
#include "menu.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "shop.hpp"
#include "status_ailment.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

int plat = 0;
int chatpicloaded = 0;
int j_at_m193 = 0;
int p_at_m193 = 0;

void talk_start()
{
    gsel(4);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_chat.bmp");
    gsel(0);
    return;
}

void talk_to_npc()
{
    keyhalt = 1;
    if (cdata[tc].character_role == 1005)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(207) == 0)
            {
                if (mode == 0)
                {
                    if (cdata.player().continuous_action_turn == 0)
                    {
                        gdata(207) = 1;
                        ghelp = 7;
                        show_ex_help();
                        screenupdate = -1;
                        update_screen();
                    }
                }
            }
        }
    }
    if (cdata[tc].character_role == 7)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(208) == 0)
            {
                if (mode == 0)
                {
                    if (cdata.player().continuous_action_turn == 0)
                    {
                        gdata(208) = 1;
                        ghelp = 8;
                        show_ex_help();
                        screenupdate = -1;
                        update_screen();
                    }
                }
            }
        }
    }
    set_npc_religion();
    if (scenemode == 0)
    {
        snd(99);
        label_1745();
    }
    cs = 0;
    chatflag = 0;
    chatesc = 1;
    if (cdata[tc].relationship <= -1)
    {
        if (evnum == 0)
        {
            txt(i18n::s.get("core.locale.talk.will_not_listen", cdata[tc]));
            quest_teleport = false;
            update_screen();
            return;
        }
    }
    if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
            + gdata_year * 24 * 30 * 12
        >= cdata[tc].time_interest_revive)
    {
        cdata[tc].interest = 100;
    }
    if ((cdata[tc].character_role >= 1000 && cdata[tc].character_role < 2000)
        || cdata[tc].character_role == 2003)
    {
        invfile = cdata[tc].shop_store_id;
        shop_refresh_on_talk();
    }
    talk_start();
    if (scenemode == 1)
    {
        talk_wrapper(talk_result_t::talk_more);
        return;
    }
    chatval(1) = 0;
    chatval(2) = 1;
    if (cdata[tc].quality == 6 && tc >= 16)
    {
        chatval(1) = cdata[tc].id;
        chatval(2) = 0;
    }
    if (event_id() == 2)
    {
        talk_wrapper(talk_result_t::talk_game_begin);
        return;
    }
    if (event_id() == 16)
    {
        talk_wrapper(talk_result_t::talk_finish_escort);
        return;
    }
    if (cdata[tc].sleep != 0)
    {
        talk_wrapper(talk_result_t::talk_sleeping);
        return;
    }
    if (cdata[tc].continuous_action_id)
    {
        talk_wrapper(talk_result_t::talk_busy);
        return;
    }
    if (tc == 0)
    {
        talk_wrapper(talk_result_t::talk_end);
        return;
    }
    if (cdata[tc].visited_just_now())
    {
        cdata[tc].visited_just_now() = false;
        talk_wrapper(talk_result_t::talk_house_visitor);
    }
    if (chatval(1) != 0)
    {
        if (gdata_current_map != mdata_t::map_id_t::show_house)
        {
            if (tc >= 16)
            {
                talk_wrapper(talk_result_t::talk_unique);
                return;
            }
        }
    }
    if (quest_teleport)
    {
        quest_teleport = false;
        talk_wrapper(talk_result_t::talk_quest_giver);
        return;
    }
    buff = "";
    talk_wrapper(talk_result_t::talk_npc);
}



talk_result_t talk_more()
{
    listmax = 0;
    buff = buff;
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


talk_result_t talk_sleeping()
{
    listmax = 0;
    buff = u8"("s + i18n::s.get("core.locale.talk.is_sleeping", cdata[tc])
        + u8")"s;
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"bye");
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

talk_result_t talk_busy()
{
    listmax = 0;
    buff = u8"("s + i18n::s.get("core.locale.talk.is_busy", cdata[tc]) + u8")"s;
    tc = tc * 1 + 0;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"bye");
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

talk_result_t talk_ignored()
{
    listmax = 0;
    buff = i18n::s.get("core.locale.talk.ignores_you", cdata[tc]);
    tc = tc * 1 + 0;
    ELONA_APPEND_RESPONSE(0, i18n::_(u8"ui", u8"bye"));
    chatesc = 1;
    ELONA_TALK_SCENE_CUT();
    return talk_result_t::talk_end;
}

talk_result_t talk_house_visitor()
{
    listmax = 0;
    cc = 0;
    switch (cdata[tc].character_role)
    {
    case 13:
        if (gdata_month == 1 && rnd(4))
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.new_year.happy_new_year",
                cdata[tc]);
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
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.new_year.gift", cdata[tc]);
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
            flt();
            int stat = itemcreate(
                -1,
                752,
                cdata.player().position.x,
                cdata.player().position.y,
                0);
            if (stat != 0)
            {
                inv[ci].param3 = cdata[tc].impression + rnd(50);
            }
            txt(i18n::s.get(
                "core.locale.talk.visitor.adventurer.new_year.throws",
                cdata[tc],
                inv[ci]));
            return talk_result_t::talk_end;
        }
        if (cdata[tc].impression < 25)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.hate.dialog", cdata[tc]);
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
            txt(i18n::s.get(
                "core.locale.talk.visitor.adventurer.hate.text", cdata[tc]));
            if (rnd(2) == 0)
            {
                for (int cnt = 0; cnt < 28; ++cnt)
                {
                    tlocx = cdata[tc].position.x + rnd(3) - rnd(3);
                    tlocy = cdata[tc].position.y - rnd(3) + rnd(3);
                    if (tlocx < 0 || tlocy < 0 || tlocx >= mdata_map_width
                        || tlocy >= mdata_map_height)
                    {
                        continue;
                    }
                    if (tlocx == cdata[tc].position.x)
                    {
                        if (tlocy == cdata[tc].position.y)
                        {
                            continue;
                        }
                    }
                    txt(i18n::s.get(
                        "core.locale.talk.visitor.adventurer.hate.throws",
                        cdata[tc]));
                    snd(91);
                    ccbk = cc;
                    cc = tc;
                    throwing_object_animation(
                        {tlocx, tlocy}, cdata[cc].position, 223, 0)
                        .play();
                    cc = ccbk;
                    mef_add(tlocx, tlocy, 5, 24, rnd(15) + 20, 50, tc);
                    mapitem_fire(tlocx, tlocy);
                }
            }
            else
            {
                for (int cnt = 0, cnt_end = (8 + rnd(6)); cnt < cnt_end; ++cnt)
                {
                    flt();
                    itemcreate(-1, 704, -1, -1, 0);
                    txt(i18n::s.get("core.locale.food.vomits", cdata[tc]));
                    snd(104);
                    await(config::instance().animewait / 2);
                    update_screen();
                }
            }
            return talk_result_t::talk_end;
        }
        if (cdata[tc].impression >= 100)
        {
            if (cdata[tc].is_best_friend() == 0)
            {
                if (inv_getfreeid(-1) != -1)
                {
                    listmax = 0;
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.like.dialog",
                        cdata[tc]);
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
                    cdata[tc].is_best_friend() = true;
                    flt();
                    itemcreate(
                        -1,
                        730,
                        cdata.player().position.x,
                        cdata.player().position.y,
                        0);
                    txt(i18n::s.get(
                        "core.locale.talk.visitor.receive",
                        inv[ci],
                        cdata[tc]));
                    txt(i18n::s.get(
                        "core.locale.talk.visitor.adventurer.like.wonder_if"));
                    listmax = 0;
                }
            }
        }
        if (rnd(4) == 0)
        {
            if (cdata[tc].impression >= 150)
            {
                int stat = advfavoriteskill(tc);
                csskill = rtval(rnd(stat));
                if (cdata[tc].impression >= 300)
                {
                    if (rnd(3) == 0)
                    {
                        int stat = advfavoritestat(tc);
                        csskill = stat;
                    }
                }
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.locale.talk.visitor.adventurer.train.choices.pass");
                ++listmax;
                if (sdata.get(csskill, 0).original_level == 0)
                {
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.train.learn."
                        "dialog",
                        i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                        std::to_string(calclearncost(csskill, cc, true))
                            + i18n::_(u8"ui", u8"platinum"),
                        cdata[tc]);
                    if (cdata.player().platinum_coin
                        >= calclearncost(csskill, cc, true))
                    {
                        list(0, listmax) = 1;
                        listn(0, listmax) = i18n::s.get(
                            "core.locale.talk.visitor.adventurer.train.choices."
                            "learn");
                        ++listmax;
                    }
                }
                else
                {
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.train.train."
                        "dialog",
                        i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                        std::to_string(calclearncost(csskill, cc, true))
                            + i18n::_(u8"ui", u8"platinum"),
                        cdata[tc]);
                    if (cdata.player().platinum_coin
                        >= calctraincost(csskill, cc, true))
                    {
                        list(0, listmax) = 2;
                        listn(0, listmax) = i18n::s.get(
                            "core.locale.talk.visitor.adventurer.train.choices."
                            "train");
                        ++listmax;
                    }
                }
                chatesc = 1;
                talk_window_query();
                if (chatval == 0 || chatval == -1)
                {
                    listmax = 0;
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.train.pass",
                        cdata[tc]);
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
                snd(12);
                if (chatval == 1)
                {
                    cdata.player().platinum_coin -=
                        calclearncost(csskill, 0, true);
                    chara_gain_skill(cdata[cc], csskill);
                    ++gdata_number_of_learned_skills_by_trainer;
                    listmax = 0;
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.train.learn.after",
                        cdata[tc]);
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
                if (chatval == 2)
                {
                    cdata.player().platinum_coin -=
                        calctraincost(csskill, 0, true);
                    modify_potential(
                        cdata[cc],
                        csskill,
                        clamp(
                            15 - sdata.get(csskill, cc).potential / 15,
                            2,
                            15 - (csskill < 18) * 10));
                    listmax = 0;
                    buff = i18n::s.get(
                        "core.locale.talk.visitor.adventurer.train.train.after",
                        cdata[tc]);
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
                return talk_result_t::talk_end;
            }
        }
        if (rnd(5) == 0)
        {
            if (cdata[tc].impression >= 150)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.visitor.adventurer.friendship.dialog",
                    cdata[tc]);
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
                if (inv_getfreeid(-1) == -1)
                {
                    txt(
                        i18n::s.get("core.locale.talk.visitor.adventurer."
                                    "friendship.no_empty_spot"));
                }
                else
                {
                    if (rnd(4))
                    {
                        p = 55;
                    }
                    else
                    {
                        p = 622;
                    }
                    flt();
                    itemcreate(
                        -1,
                        p,
                        cdata.player().position.x,
                        cdata.player().position.y,
                        0);
                    txt(i18n::s.get(
                        "core.locale.talk.visitor.receive",
                        inv[ci],
                        cdata[tc]));
                    snd(14);
                }
                return talk_result_t::talk_end;
            }
        }
        if (rnd(4) == 0)
        {
            if (cdata[tc].impression >= 100)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.visitor.adventurer.souvenir.dialog",
                    cdata[tc]);
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
                if (inv_getfreeid(0) == -1)
                {
                    txt(
                        i18n::s.get("core.locale.talk.visitor.adventurer."
                                    "souvenir.inventory_is_full"));
                }
                else
                {
                    flt();
                    itemcreate(0, 729, -1, -1, 0);
                    txt(i18n::s.get(
                        "core.locale.talk.visitor.adventurer.souvenir.receive",
                        inv[ci]));
                    snd(14);
                }
                return talk_result_t::talk_end;
            }
        }
        if (rnd(5) == 0)
        {
            if (cdata[tc].impression >= 100)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.visitor.adventurer.materials.dialog",
                    cdata[tc]);
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
                txt(i18n::s.get(
                    "core.locale.talk.visitor.adventurer.materials.receive",
                    cdata[tc]));
                efid = 1117;
                efp = 100;
                tc = 0;
                magic();
                return talk_result_t::talk_end;
            }
        }
        if (rnd(8) == 0)
        {
            int stat = advfavoriteskill(tc);
            csskill = rtval(rnd(stat));
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.favorite_skill.dialog",
                i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                cdata[tc]);
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
        if (rnd(10) == 0)
        {
            int stat = advfavoritestat(tc);
            csskill = stat;
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.favorite_stat.dialog",
                i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                cdata[tc]);
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
        if (rnd(3) == 0)
        {
            if (cdata[tc].impression >= 75)
            {
                listmax = 0;
                buff = i18n::s.get(
                    "core.locale.talk.visitor.adventurer.conversation.dialog",
                    cdata.player(),
                    cdata[tc]);
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
                txt(i18n::s.get(
                    "core.locale.talk.visitor.adventurer.conversation.hold",
                    cdata[tc]));
                chara_modify_impression(cdata[tc], 10);
                return talk_result_t::talk_end;
            }
        }
        if (rnd(3) == 0)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.adventurer.drink.dialog", cdata[tc]);
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
            snd(17);
            txt(i18n::s.get(
                "core.locale.talk.visitor.adventurer.drink.cheers", cdata[tc]));
            txtef(9);
            txt(i18n::s.get_enum("core.locale.magic.alcohol.normal", rnd(7)));
            dmgcon(tc, status_ailment_t::drunk, 1000);
            dmgcon(cc, status_ailment_t::drunk, 1000);
            chara_modify_impression(cdata[tc], 15);
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff =
            i18n::s.get("core.locale.talk.visitor.wanted_to_say_hi", cdata[tc]);
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
    case 2005:
        if (gdata_last_month_when_trainer_visited == gdata_month)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.trainer.no_more_this_month",
                cdata[tc]);
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
        plat = 3;
        gdata_last_month_when_trainer_visited = gdata_month;
        buff = i18n::s.get(
            "core.locale.talk.visitor.trainer.dialog.member",
            guildname(),
            plat,
            cdata[tc]);
        if (gdata_belongs_to_mages_guild != 0)
        {
            p(0) = 16;
            p(1) = 15;
            p(2) = 14;
            p(3) = -1;
        }
        else if (gdata_belongs_to_fighters_guild != 0)
        {
            p(0) = 10;
            p(1) = 11;
            p(2) = 12;
            p(3) = -1;
        }
        else if (gdata_belongs_to_thieves_guild != 0)
        {
            p(0) = 12;
            p(1) = 13;
            p(2) = 11;
            p(3) = 14;
            p(4) = -1;
        }
        else
        {
            plat = 4;
            p(3) = -1;
            i = rnd(6);
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p(cnt) = 10 + cnt + i;
            }
            buff = i18n::s.get(
                "core.locale.talk.visitor.trainer.dialog.nonmember",
                plat,
                cdata[tc]);
        }
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.visitor.trainer.choices.not_today");
        ++listmax;
        if (cdata.player().platinum_coin >= plat)
        {
            for (int cnt = 0; cnt < 8; ++cnt)
            {
                if (p(cnt) == -1)
                {
                    break;
                }
                list(0, listmax) = p(cnt);
                listn(0, listmax) = i18n::s.get(
                    "core.locale.talk.visitor.trainer.choices.improve",
                    i18n::_(u8"ability", std::to_string(p(cnt)), u8"name"));
                ++listmax;
            }
        }
        talk_window_query();
        if (chatval == 0 || chatval == -1)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.trainer.regret", cdata[tc]);
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
        cdata.player().platinum_coin -= plat;
        snd(61);
        txtef(2);
        txt(i18n::s.get(
            "core.locale.talk.visitor.trainer.potential_expands",
            cdata.player(),
            i18n::_(u8"ability", std::to_string(chatval), u8"name")));
        modify_potential(cdata.player(), chatval, 10);
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.trainer.after", cdata[tc]);
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
    case 2002:
        listmax = 0;
        buff =
            i18n::s.get("core.locale.talk.visitor.wanted_to_say_hi", cdata[tc]);
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
    case 2000:
        if (cdata.player().gold > 0)
        {
            list(0, listmax) = 1;
            listn(0, listmax) =
                i18n::s.get("core.locale.talk.visitor.choices.yes");
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
        ++listmax;
        buff = i18n::s.get("core.locale.talk.visitor.beggar.dialog", cdata[tc]);
        talk_window_query();
        if (chatval == 1)
        {
            p = cdata.player().gold / 20 + 1;
            txt(i18n::s.get(
                "core.locale.talk.visitor.beggar.spare", p(0), cdata[tc]));
            cdata.player().gold -= p;
            snd(12);
            earn_gold(cdata[tc], p);
            modify_karma(cdata.player(), 2);
            listmax = 0;
            buff =
                i18n::s.get("core.locale.talk.visitor.beggar.after", cdata[tc]);
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
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.beggar.cheap");
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
    case 2001:
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
        ++listmax;
        buff = i18n::s.get("core.locale.talk.visitor.punk.dialog", cdata[tc]);
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff =
                i18n::s.get("core.locale.talk.npc.common.sex.start", cdata[tc]);
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) =
                i18n::s.get("core.locale.talk.npc.common.sex.response");
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
            continuous_action_sex();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.punk.hump");
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
    case 2006:
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
        ++listmax;
        buff = i18n::s.get(
            "core.locale.talk.visitor.mysterious_producer.want_to_be_star",
            cdata[tc]);
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get(
                "core.locale.talk.visitor.mysterious_producer.no_turning_back",
                cdata[tc]);
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) =
                i18n::s.get("core.locale.talk.npc.common.sex.response");
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
            continuous_action_sex();
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.punk.hump");
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
    case 2003:
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.visitor.merchant.choices.buy");
        ++listmax;
        list(0, listmax) = 1;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.visitor.merchant.choices.sell");
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) =
            i18n::s.get("core.locale.talk.visitor.merchant.choices.not_now");
        ++listmax;
        buff =
            i18n::s.get("core.locale.talk.visitor.merchant.dialog", cdata[tc]);
        talk_window_query();
        if (chatval == 0)
        {
            invctrl = 11;
            invfile = cdata[tc].shop_store_id;
            shop_sell_item();
            screenupdate = -1;
            update_screen();
            cs = 0;
            buff = "";
            return talk_result_t::talk_house_visitor;
        }
        if (chatval == 1)
        {
            invctrl = 12;
            invfile = cdata[tc].shop_store_id;
            shop_sell_item();
            cc = 0;
            screenupdate = -1;
            update_screen();
            cs = 0;
            buff = "";
            return talk_result_t::talk_house_visitor;
        }
        listmax = 0;
        buff =
            i18n::s.get("core.locale.talk.visitor.merchant.regret", cdata[tc]);
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
        cdata[tc].character_role = 2002;
        return talk_result_t::talk_end;
    }
    return talk_result_t::talk_end;
}



bool talk_give_potion_of_cure_corruption()
{
    list(0, listmax) = 1;
    listn(0, listmax) = i18n::s.get("core.locale.talk.unique.pael.give.choice");
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::_(u8"ui", u8"bye");
    ++listmax;
    talk_window_query();
    if (chatval != 1)
    {
        return false;
    }
    int stat = inv_find(559, 0);
    if (stat == -1)
    {
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.unique.pael.give.do_not_have");
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
                return false;
            }
        }
        return false;
    }
    inv[stat].modify_number(-1);
    txt(i18n::s.get("core.locale.talk.unique.pael.give.you_give"));
    snd(13);
    listmax = 0;
    buff =
        i18n::s.get("core.locale.talk.unique.pael.give.dialog", cdatan(0, 0));
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
            return false;
        }
    }
    return true;
}



talk_result_t talk_game_begin()
{
    if (lomiaseaster)
    {
        cdata.player().blind = 100;
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 0);
        tc =
            tc * (chara_find(33) == 0) + (chara_find(33) != 0) * chara_find(33);
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
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 1);
        tc =
            tc * (chara_find(34) == 0) + (chara_find(34) != 0) * chara_find(34);
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
        update_screen();
        await(3000);
        txtnew();
        txtef(3);
        txt(
            i18n::s.get("core.locale.talk.unique.lomias.begin.easter_egg."
                        "something_is_killed"));
        txt(i18n::s.get("core.locale.talk.unique.lomias.begin.easter_egg.ugh"));
        snd(8);
        spillblood(28, 6, 10);
        flt();
        itemcreate(-1, 705, 28, 6, 0);
        update_screen();
        await(500);
        await(500);
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 2);
        tc =
            tc * (chara_find(33) == 0) + (chara_find(33) != 0) * chara_find(33);
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
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 3);
        tc =
            tc * (chara_find(34) == 0) + (chara_find(34) != 0) * chara_find(34);
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
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 4);
        tc =
            tc * (chara_find(33) == 0) + (chara_find(33) != 0) * chara_find(33);
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
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 5);
        tc =
            tc * (chara_find(34) == 0) + (chara_find(34) != 0) * chara_find(34);
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
        listmax = 0;
        buff = i18n::s.get_enum(
            "core.locale.talk.unique.lomias.begin.easter_egg", 6);
        tc =
            tc * (chara_find(33) == 0) + (chara_find(33) != 0) * chara_find(33);
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
        await(1500);
        update_screen();
        fade_out();
        gsel(4);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"face1.bmp", 1);
        gsel(0);
        cdata.player().blind = 0;
        txt(i18n::s.get(
            "core.locale.talk.unique.lomias.begin.easter_egg.was_dream"));
    }
    else
    {
        txtnew();
    }
    txt(i18n::s.get(
        "core.locale.talk.unique.lomias.begin.regain_consciousness"));
    listmax = 0;
    buff = i18n::s.get_enum("core.locale.talk.unique.lomias.begin", 0);
    tc = tc * (chara_find(34) == 0) + (chara_find(34) != 0) * chara_find(34);
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
    listmax = 0;
    buff = i18n::s.get_enum("core.locale.talk.unique.lomias.begin", 1);
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
    listmax = 0;
    buff = i18n::s.get_enum("core.locale.talk.unique.lomias.begin", 2);
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
    listmax = 0;
    buff = i18n::s.get_enum("core.locale.talk.unique.lomias.begin", 3);
    tc = tc * (chara_find(33) == 0) + (chara_find(33) != 0) * chara_find(33);
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
    listmax = 0;
    buff = i18n::s.get_enum(
        "core.locale.talk.unique.lomias.begin", 4, cdatan(0, 0));
    tc = tc * (chara_find(34) == 0) + (chara_find(34) != 0) * chara_find(34);
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
    mdata_map_bgm = 67;
    play_music();
    return talk_result_t::talk_unique;
}


void talk_end()
{
    quest_teleport = false;
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
    return;
}



void talk_window_query()
{
    cs_bk = -1;
    key_list = key_enter;
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        ++keyrange;
    }
    keyrange = listmax;
    key = "";
    objprm(0, ""s);
    keylog = "";
    talk_window_init_and_show();
label_2258_internal:
    talk_window_show();
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (cs == cnt)
        {
            color(100, 160, 250);
        }
        else
        {
            color(255, 255, 255);
        }
        noteget(s, cnt);
        x = wx + 136;
        y = wy + wh - 56 - keyrange * 19 + cnt * 19 + 2;
        display_key(x, y, cnt);
        cs_list(cs == cnt, listn(0, cnt), x + 30, y, 4, 0);
        color(0, 0, 0);
    }
    cs_bk = cs;
    redraw();
    await(config::instance().wait1);
    key_check();
    cursor_check();
    int a{};
    a = stick(stick_key::escape);
    if (a == stick_key::escape)
    {
        if (scenemode)
        {
            scene_cut = 1;
            talk_reset_variables();
            return;
        }
    }
    p = -1;
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = list(0, cnt);
            break;
        }
    }
    if (p != -1)
    {
        chatval = p;
        talk_reset_variables();
        return;
    }
    if (key == key_cancel)
    {
        if (chatesc == 1)
        {
            chatval = -1;
            talk_reset_variables();
            return;
        }
    }
    goto label_2258_internal;
}



void talk_reset_variables()
{
    snd(10);
    cs = 0;
    listmax = 0;
}



void talk_window_init_and_show()
{
    talk_window_init();
    talk_window_show();
}



void talk_window_init()
{
    if (scenemode == 0)
    {
        screenupdate = -1;
        update_screen();
        cs = 0;
    }
    talk_conv(buff, 56 - en * 3);
    chatpicloaded = 0;
    wx = (windoww - 600) / 2 + inf_screenx;
    wy = winposy(380);
    ww = 600;
    wh = 380;
    gmode(6, 80);
    pos(wx + 4, wy - 16);
    gcopy(7, 0, 0, 600, 380);
}



void talk_window_show()
{
    gmode(2);
    pos(wx, wy - 20);
    gcopy(7, 0, 0, 600, 380);
    if (cdata[tc].portrait >= 0 || scenemode)
    {
        p = cdata[tc].sex * 64 + cdata[tc].portrait;
        if (scenemode)
        {
            p = elona::stoi(actor(1, rc));
        }
        pos(wx + 42, wy + 42);
        gcopy(4, p % 16 * 48, p / 16 * 72, 48, 72, 80, 112);
    }
    else
    {
        const auto portrait_filepath = filesystem::dir::user()
            / (u8"graphic/face"s + std::abs(cdata[tc].portrait + 1) + u8".bmp");
        if (!fs::exists(portrait_filepath) || cdata[tc].portrait == -1)
        {
            int chara_chip_id = cdata[tc].image % 1000;
            draw_chara(
                cdata[tc],
                wx + 82,
                wy + 125 - chara_chips[chara_chip_id].offset_y,
                2);
        }
        else
        {
            if (chatpicloaded == 0)
            {
                gsel(4);
                pos(0, 0);
                picload(portrait_filepath, 1);
                gsel(0);
                chatpicloaded = 1;
            }
            pos(wx + 42, wy + 42);
            gcopy(4, 0, 0, 80, 112, 80, 112);
        }
    }
    font(10 - en * 2);
    display_topic(
        i18n::s.get("core.locale.talk.window.impress"), wx + 28, wy + 170);
    display_topic(
        i18n::s.get("core.locale.talk.window.attract"), wx + 28, wy + 215);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    if (cdatan(1, tc) == ""s)
    {
        s = cdatan(0, tc) + u8" "s;
    }
    else
    {
        s = i18n::s.get(
                "core.locale.talk.window.of", cdatan(0, tc), cdatan(1, tc))
            + " ";
    }
    if (cdata[tc].sex == 0)
    {
        s += cnven(i18n::_(u8"ui", u8"male"));
    }
    else
    {
        s += cnven(i18n::_(u8"ui", u8"female"));
    }
    if (cdatan(1, tc) != ""s)
    {
        s += " " + i18n::s.get("core.locale.talk.window.fame", cdata[tc].fame);
    }
    if ((cdata[tc].character_role >= 1000 && cdata[tc].character_role < 2000)
        || cdata[tc].character_role == 2003)
    {
        s += " "
            + i18n::s.get(
                  "core.locale.talk.window.shop_rank", cdata[tc].shop_rank);
    }
    if (gdata_reveals_religion)
    {
        s += u8" ("s + i18n::_(u8"god", cdata[tc].god_id, u8"name") + u8")"s;
    }
    if (scenemode)
    {
        s = actor(0, rc);
    }
    pos(wx + 120, wy + 16);
    color(20, 10, 5);
    mes(s);
    color(0, 0, 0);
    font(13 - en * 2);
    if (chatval(2) == 1)
    {
        s = i18n::_(
            u8"ui",
            u8"impression",
            u8"_"s + chara_impression_level(cdata[tc].impression));
        if (cdata[tc].impression < 150)
        {
            s(1) = ""s + cdata[tc].impression;
        }
        else
        {
            s(1) = u8"???"s;
        }
        pos(wx + 32, wy + 198);
        color(20, 10, 5);
        mes(u8"("s + s(1) + u8")"s + s);
        color(0, 0, 0);
        if (cdata[tc].interest >= 0)
        {
            for (int cnt = 0, cnt_end = (cdata[tc].interest / 5 + 1);
                 cnt < cnt_end;
                 ++cnt)
            {
                draw("interest_icon", wx + 26 + cnt * 4, wy + 245);
            }
        }
    }
    else
    {
        pos(wx + 60, wy + 198);
        mes(u8"-"s);
        pos(wx + 60, wy + 245);
        mes(u8"-"s);
    }
    font(14 - en * 2);
    color(20, 10, 5);
    notesel(buff);
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        p = cnt;
        x = wx + 150;
        y = wy + 43 + cnt * 19;
        noteget(s, p);
        pos(x, y);
        mes(s);
    }
    color(0, 0, 0);
}



int talk_guide_quest_client()
{
    constexpr int max_quest = 5;

    int ret{};

    for (int i = 0; i < max_quest; ++i)
    {
        const auto quest_id = gdata(160 + i);
        if (qdata(8, quest_id) != 1)
            continue;
        if (gdata_current_dungeon_level != 1)
            continue;

        auto client = -1;
        if (qdata(3, quest_id) == 1011)
        {
            if (qdata(1, quest_id) == gdata_current_map)
            {
                client = qdata(10, quest_id);
            }
        }
        if (qdata(3, quest_id) == 1002)
        {
            if (qdata(1, qdata(10, quest_id)) == gdata_current_map)
            {
                client = qdata(0, qdata(10, quest_id));
            }
        }
        if (client != -1)
        {
            // Check duplicate
            bool duplicated{};
            for (int j = 0; j < i; ++j)
            {
                if (gdata(160 + j) == quest_id)
                {
                    duplicated = true;
                    break;
                }
            }
            if (!duplicated)
            {
                rtval(ret) = client;
                ++ret;
            }
        }
    }

    return ret;
}



int talk_check_trade(int prm_1081)
{
    j_at_m193 = 0;
    for (int cnt = 0; cnt < 5; ++cnt)
    {
        p_at_m193 = gdata(160 + cnt);
        if (qdata(8, p_at_m193) == 1)
        {
            if (gdata_current_dungeon_level == 1)
            {
                if (qdata(1, p_at_m193) == gdata_current_map)
                {
                    if (prm_1081 == qdata(10, p_at_m193))
                    {
                        j_at_m193 = 1;
                        break;
                    }
                }
            }
        }
    }
    return j_at_m193;
}


} // namespace elona
