#include "talk.hpp"
#include "ability.hpp"
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
                    if (cdata[0].continuous_action_turn == 0)
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
                    if (cdata[0].continuous_action_turn == 0)
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
        if (gdata_current_map != 35)
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
    buff = u8"("s +
        i18n::s.get("core.locale.talk.is_sleeping", cdata[tc])
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
    buff = u8"("s + name(tc)
        + i18n::s.get("core.locale.talk.is_busy", cdata[tc])
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
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.new_year.happy_new_year");
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
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.new_year.gift");
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
                -1, 752, cdata[0].position.x, cdata[0].position.y, 0);
            if (stat != 0)
            {
                inv[ci].param3 = cdata[tc].impression + rnd(50);
            }
            txt(i18n::s.get("core.locale.talk.visitor.adventurer.new_year.throws",
                            cdata[tc], inv[ci]));
            return talk_result_t::talk_end;
        }
        if (cdata[tc].impression < 25)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.hate.dialog");
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
            txt(i18n::s.get("core.locale.talk.visitor.adventurer.hate.text"));
            if (rnd(2) == 0)
            {
                for (int cnt = 0; cnt < 28; ++cnt)
                {
                    tlocx = cdata[tc].position.x + rnd(3) - rnd(3);
                    tlocy = cdata[tc].position.y - rnd(3) + rnd(3);
                    if (tlocx < 0 || tlocy < 0 || tlocx >= mdata(0)
                        || tlocy >= mdata(1))
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
                    txt(i18n::s.get("core.locale.talk.visitor.adventurer.hate.throws", cdata[tc]));
                    snd(91);
                    ccbk = cc;
                    cc = tc;
                    aniref(0) = 223;
                    aniref(1) = 0;
                    anix = tlocx;
                    aniy = tlocy;
                    play_animation(15);
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
                    txt(lang(
                        name(tc) + u8"は吐いた。"s, name(tc) + u8" vomits."s));
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
                    buff =
                        i18n::s.get("core.locale.talk.visitor.adventurer.like.dialog");
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
                        -1, 730, cdata[0].position.x, cdata[0].position.y, 0);
                    txt(i18n::s.get("core.locale.talk.visitor.receieve", inv[ci], cdata[tc]));
                    txt(i18n::s.get("core.locale.talk.visitor.adventurer.like.wonder_if"));
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
                listn(0, listmax) =
                    i18n::s.get("core.locale.visitor.adventurer.train.choices.pass");
                ++listmax;
                if (sdata.get(csskill, 0).original_level == 0)
                {
                    buff = i18n::s.get("core.locale.talk.visitor.adventurer.train.learn.dialog",
                                       i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                                       std::to_string(calclearncost(csskill, cc, true)) + i18n::_(u8"ui", u8"platinum"));
                    if (cdata[0].platinum_coin
                        >= calclearncost(csskill, cc, true))
                    {
                        list(0, listmax) = 1;
                        listn(0, listmax) =
                            i18n::s.get("core.locale.talk.visitor.adventurer.train.choices.learn");
                        ++listmax;
                    }
                }
                else
                {
                    buff = i18n::s.get("core.locale.talk.visitor.adventurer.train.train.dialog",
                                       i18n::_(u8"ability", std::to_string(csskill), u8"name"),
                                       std::to_string(calclearncost(csskill, cc, true)) + i18n::_(u8"ui", u8"platinum"));
                    if (cdata[0].platinum_coin
                        >= calctraincost(csskill, cc, true))
                    {
                        list(0, listmax) = 2;
                        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.adventurer.train.choices.train");
                        ++listmax;
                    }
                }
                chatesc = 1;
                talk_window_query();
                if (chatval == 0 || chatval == -1)
                {
                    listmax = 0;
                    buff = i18n::s.get("core.locale.talk.visitor.adventurer.train.pass");
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
                    cdata[0].platinum_coin -= calclearncost(csskill, 0, true);
                    skillgain(cc, csskill);
                    ++gdata_number_of_learned_skills_by_trainer;
                    listmax = 0;
                    buff = i18n::s.get("core.locale.talk.visitor.adventurer.train.learn.after");
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
                    cdata[0].platinum_coin -= calctraincost(csskill, 0, true);
                    modify_potential(
                        cc,
                        csskill,
                        clamp(
                            15 - sdata.get(csskill, cc).potential / 15,
                            2,
                            15 - (csskill < 18) * 10));
                    listmax = 0;
                    buff = i18n::s.get("core.locale.talk.visitor.adventurer.train.train.after");
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
                buff = i18n::s.get("core.locale.talk.visitor.adventurer.friendship.dialog");
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
                    txt(i18n::s.get("core.locale.talk.visitor.adventurer.friendship.no_empty_spot"));
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
                        -1, p, cdata[0].position.x, cdata[0].position.y, 0);
                    txt(i18n::s.get("core.locale.talk.visitor.receive", inv[ci], cdata[tc]));
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
                buff = i18n::s.get("core.locale.talk.visitor.adventurer.souvenir.dialog");
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
                    txt(i18n::s.get("core.locale.talk.visitor.adventurer.souvenir.inventory_is_full"));
                }
                else
                {
                    flt();
                    itemcreate(0, 729, -1, -1, 0);
                    txt(i18n::s.get("core.locale.talk.visitor.adventurer.souvenir.receive", inv[ci]));
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
                buff = i18n::s.get("core.locale.talk.visitor.adventurer.materials.dialog");
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
                txt(i18n::s.get("core.locale.talk.visitor.adventurer.materials.receive", cdata[tc]));
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
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.favorite_skill.dialog",
                               i18n::_(u8"ability", std::to_string(csskill), u8"name"));
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
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.favorite_stat.dialog",
                               i18n::_(u8"ability", std::to_string(csskill), u8"name"));
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
                buff = i18n::s.get("core.locale.talk.visitor.adventurer.conversation.dialog", cdata[0]);
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
                txt(i18n::s.get("core.locale.talk.visitor.adventurer.conversation.hold", cdata[tc]));
                chara_mod_impression(tc, 10);
                return talk_result_t::talk_end;
            }
        }
        if (rnd(3) == 0)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.adventurer.drink.dialog");
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
            txt(i18n::s.get("core.locale.talk.visitor.adventurer.drink.cheers", cdata[tc]));
            txtef(9);
            txt(lang(u8"「うぃっ！」"s, u8"*Hic*"s),
                lang(u8"「うまいぜ」"s, u8"\"Ah, good booze.\""s),
                lang(u8"「らららー♪」"s, u8"\"La-la-la-la.\""s),
                lang(u8"「ひっく」"s, u8"\"I'm going to heaven.\""s),
                lang(u8"「ふぅ」"s, u8"\"Whew!\""s),
                lang(u8"「たまらないわ」"s, u8"\"I'm revived!\""s),
                lang(u8"「んまっ♪」"s, u8"\"Awesome.\""s));
            dmgcon(tc, status_ailment_t::drunk, 1000);
            dmgcon(cc, status_ailment_t::drunk, 1000);
            chara_mod_impression(tc, 15);
            return talk_result_t::talk_end;
        }
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.wanted_to_say_hi");
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
            buff = i18n::s.get("core.locale.talk.visitor.trainer.no_more_this_month");
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
        buff = i18n::s.get("core.locale.talk.visitor.trainer.dialog.member",
                           guildname(),
                           plat);
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
            buff = i18n::s.get("core.locale.talk.visitor.trainer.dialog.nonmember", plat);
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.trainer.choices.not_today");
        ++listmax;
        if (cdata[0].platinum_coin >= plat)
        {
            for (int cnt = 0; cnt < 8; ++cnt)
            {
                if (p(cnt) == -1)
                {
                    break;
                }
                list(0, listmax) = p(cnt);
                listn(0, listmax) =
                    i18n::s.get("core.locale.talk.visitor.trainer.choices.improve",
                                i18n::_(u8"ability", std::to_string(p(cnt)), u8"name"));
                ++listmax;
            }
        }
        talk_window_query();
        if (chatval == 0 || chatval == -1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.trainer.regret");
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
        cdata[0].platinum_coin -= plat;
        snd(61);
        txtef(2);
        txt(i18n::s.get("core.locale.talk.visitor.trainer.potential_expands",
                        cdata[0],
                        i18n::_(u8"ability", std::to_string(chatval), u8"name")));
        modify_potential(0, chatval, 10);
        listmax = 0;
        buff = i18n::s.get("core.locale.talk.visitor.trainer.after");
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
        buff = i18n::s.get("core.locale.talk.visitor.wanted_to_say_hi");
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
        if (cdata[0].gold > 0)
        {
            list(0, listmax) = 1;
            listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.yes");
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.choices.no");
        ++listmax;
        buff = i18n::s.get("core.locale.talk.visitor.beggar.no_money");
        talk_window_query();
        if (chatval == 1)
        {
            p = cdata[0].gold / 20 + 1;
            txt(i18n::s.get("core.locale.talk.visitor.beggar.spare", p(0), cdata[tc]));
            cdata[0].gold -= p;
            snd(12);
            cdata[tc].gold += p;
            modify_karma(0, 2);
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.beggar.after");
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
        buff = i18n::s.get("core.locale.talk.visitor.punk.are_you_ready");
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.punk.no_turning_back");
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"うふふ"s, u8"Come on!"s);
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
        buff = i18n::s.get("core.locale.talk.visitor.mysterious_producer.want_to_be_star");
        talk_window_query();
        if (chatval == 1)
        {
            listmax = 0;
            buff = i18n::s.get("core.locale.talk.visitor.mysterious_producer.no_turning_back");
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"うふふ"s, u8"Come on!"s);
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
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.merchant.choices.buy");
        ++listmax;
        list(0, listmax) = 1;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.merchant.choices.sell");
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = i18n::s.get("core.locale.talk.visitor.merchant.choices.not_now");
        ++listmax;
        buff = i18n::s.get("core.locale.talk.visitor.merchant.dialog");
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
        buff = i18n::s.get("core.locale.talk.visitor.merchant.regret");
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
    listn(0, listmax) = lang(
        u8"エーテル抗体を1本渡す"s,
        u8"(Hand her a potion of cure corruption.)"s);
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
        buff = lang(u8"うそつき！"s, u8"Liar!"s);
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
    --inv[stat].number;
    txt(lang(u8"エーテル抗体を1本渡した。"s, u8"You give her a potion."s));
    snd(13);
    listmax = 0;
    buff = lang(
        u8"え…あ、ありがと〜！！おかあさん…薬だよ。これでよくなるよね？"s,
        u8"R-Really? Mommy, mommy! "s + cdatan(0, 0)
            + u8" gave us a cure! Are you gonna be ok now?"s);
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
        cdata[0].blind = 100;
        listmax = 0;
        buff = lang(
            u8"この洞窟…雨をしのぐにはちょうどいいわ。ロミアス、危険がないか奥を調べて来て。"s,
            u8"This cave...it's a good place to keep out the rain. Lomias, check the inner chamber to be sure there is no danger lurking here."s);
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
        buff = lang(u8"わかった。ここで待っていろ"s, u8"Okay. Wait here."s);
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
        txt(lang(u8"何かは殺された。"s, u8"Something is killed."s));
        txt(lang(u8"「ぐわぁ」"s, u8"\"Uggghhh!\""s));
        snd(8);
        spillblood(28, 6, 10);
        flt();
        itemcreate(-1, 705, 28, 6, 0);
        update_screen();
        await(500);
        await(500);
        listmax = 0;
        buff = lang(
            u8"…今の音は？ …ロミアス、大丈夫？"s,
            u8"...what was that sound? ...Lomias, are you alright?"s);
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
        buff = lang(
            u8"ああ、問題ない。どうやらこの洞窟は昔、誰かが住んでいたようだな。奥を見て来たが、今はもう使われていないようだ。"s,
            u8"It's nothing. Looks like this cave is long abandoned. It's a good place to stay."s);
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
        buff = lang(
            u8"そう、ならば都合がいいわ。…あら、あなた何を持っているの？ …キャーッ、プチじゃない！"s,
            u8"I see, that's convenient for us...wait Lomias, what arey you carrying?...Argh! Putits!"s);
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
        buff = lang(
            u8"こいつらか？心配する必要はない。以前、人間にペットとして飼われていたのだろう、ふふ…私によくなついているようだ。"s,
            u8"Don't worry. It appears these putits had been kept as pets by someone. They are kind of...cute."s);
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
        buff = lang(
            u8"うふ！あなたにも優しいところがあるのね。…来て。どうやら怪我人が意識を取り戻したみたいよ。"s,
            u8"Huh, sounds like even you have a soft spot...Come here, the injured is about to wake up."s);
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
        cdata[0].blind = 0;
        txt(lang(u8" 夢…か… "s, u8"It was...a dream...?"s));
    }
    else
    {
        txtnew();
    }
    txt(lang(
        u8"あなたは意識をとりもどした。"s, u8"You regain consciousness."s));
    if (jp)
    {
        listmax = 0;
        buff =
            u8"…意識が…もう戻ったのか？ 驚いたな。君の回復を待つために、我々の急を要する旅がいつまで中断されるのか、気を揉んでいたのだが。"s;
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
        buff =
            u8"君は重傷を負い川辺に倒れていた。宵闇が辺りを覆う前に、癒し手の力を持つ我々に発見されたのは、全くよくできた偶然だ。"s;
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
        buff =
            u8" …そんな物珍しげな顔をするな。君の察する通り、我々は異形の森の民だ。エレアは…シエラ・テールの高潔なる異端者は、他種族の詮索に付き合う無駄な時間をあいにく持ち合わせていないが、君は、我々に拾われた幸運をもっと素直に喜ぶべきだな。瀕死の君を回復させることは、ここにいるラーネイレ以外の何者にも不可能だっただろう。なにせ彼女はエレアの…"s;
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
        buff =
            u8"ロミアス、喋りすぎよ。たとえ意識の朦朧とした怪我人が相手だとしても。"s;
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
        buff = u8"…そうだな。私の悪い癖だ、わかってはいる。…さて、"s
            + cdatan(0, 0) + u8"といったな、"s;
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
    }
    else
    {
        listmax = 0;
        buff =
            u8"...you...you're awake already? Remarkable. I was beginning to worry that nursing a lowly adventurer would bring our urgent travel to a halt."s;
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
        buff =
            u8"You were badly wounded, passing out on the bank of a river. It was fortunate that we found you before the dark mantle of night enveloped this whole valley, almost as if Ehekatl, the goddess of luck herself had her eyes upon you."s;
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
        buff =
            u8"...stop your curious eyes. Yes, we are sons of Vindale whom they call the irreverent forest. Though we Eleas, noble but blameless \"heretics\", aren't keen to spend idle time responding to every senseless question about our race, you should be more thankful for your fate. If it weren't the lady Larnneire who cured your mortal wound, you wouldn't be hearing my tirade. For the lady is no ordinary Elea and only she can..."s;
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
        buff =
            u8"You talk too much Lomias, even though the one injured before you is still dazed."s;
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
        buff = u8"...yes, it's a bad habit of mine. Well, "s + cdatan(0, 0)
            + u8"..."s;
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
    }
    mdata(13) = 67;
    play_music();
    return talk_result_t::talk_unique;
}



talk_result_t talk_finish_escort()
{
    listmax = 0;
    buff = lang(
        u8"無事に到着できてほっとした"s + _yo() + _thanks(2),
        u8"We made it! Thank you!"s);
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
        buff = lang(
            u8"頼んでいた依頼は順調"s + _kana(1),
            u8"What about my contract? Is everything alright? "s);
        return talk_result_t::talk_npc;
    }
    quest_set_data(1);
    listmax = 0;
    list(0, listmax) = 1;
    listn(0, listmax) = lang(u8"受諾する"s, u8"I will take the job."s);
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = lang(u8"やめる"s, u8"Not now."s);
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
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
            buff = lang(
                u8"未完了の依頼が多すぎじゃない"s + _kana(1)
                    + u8"この仕事は、安心してまかせられない"s + _yo(),
                u8"Hey, you've got quite a few unfinished contracts. See me again when you have finished them."s);
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
                buff = lang(
                    u8"どうやらバックパックが一杯のよう"s + _da()
                        + u8"持ち物を整理してまた来て"s + _kure(),
                    u8"It seems your backpack is already full. Come see me again when you're ready."s);
                return talk_result_t::talk_npc;
            }
        }
        if (qdata(3, rq) == 1007)
        {
            f = chara_get_free_slot_ally();
            if (f == 0)
            {
                buff = lang(
                    u8"これ以上仲間を連れて行けないよう"s + _da()
                        + u8"人数を調整してまた来て"s + _kure(),
                    u8"It seems your party is already full. Come see me again when you're ready."s);
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
                        if (cdata[cnt].state == 0)
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
        buff = lang(
            _thanks() + u8"期待してい"s + _ru(),
            u8"Thanks. I'm counting on you."s);
        if (qdata(3, rq) == 1002)
        {
            ++qdata(15, qdata(10, rq));
            flt();
            itemcreate(
                0, qdata(11, rq), cdata[0].position.x, cdata[0].position.y, 0);
            txt(lang(
                itemname(ci, 1) + u8"をバックパックに入れた。"s,
                u8"You put "s + itemname(ci, 1) + u8" in your backpack."s));
            snd(100);
            refresh_burden_state();
            buff = lang(
                u8"これが依頼の品物"s + _da() + u8"期限には十分気をつけて"s
                    + _kure(),
                u8"Here's the package. Be aware of the deadline. I don't want to report you to the guards."s);
        }
    }
    else
    {
        buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
    }
    return talk_result_t::talk_npc;
}



talk_result_t talk_accepted_quest()
{
    if (qdata(3, rq) == 1001 || qdata(3, rq) == 1010)
    {
        listmax = 0;
        buff = lang(
            u8"では、早速案内するので、モンスターを一匹残らず退治して"s
                + _kure(),
            u8"Great! I'll guide you to the place, kill them all!"s);
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
        buff = lang(
            u8"畑までは案内するから、しっかりと期限内に作物を納入して"s
                + _kure(),
            u8"Fine. I'll take you to my farm."s);
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
        buff = lang(
            u8"ついて来て"s + _kure() + u8"パーティー会場まで案内する"s + _yo(),
            u8"Alright, I'll take you to the party now."s);
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
    gdata_previous_x = cdata[0].position.x;
    gdata_previous_y = cdata[0].position.y;
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
        buff = lang(
            u8"訓練が必要なときは、声をかけて"s + _kure(),
            u8"Come see me again when you need more training."s);
        return talk_result_t::talk_npc;
    }
    listmax = 0;
    if (csctrl == 2)
    {
        buff = lang(
            i18n::_(u8"ability", std::to_string(csskill), u8"name")
                + u8"の能力を訓練するには"s + calctraincost(csskill, cc)
                + i18n::_(u8"ui", u8"platinum") + u8"かかるけどいい"s
                + _kana(1),
            u8"Training "s
                + i18n::_(u8"ability", std::to_string(csskill), u8"name")
                + u8" will cost you "s + calctraincost(csskill, cc)
                + u8" platinum pieces."s);
        if (cdata[0].platinum_coin >= calctraincost(csskill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"訓練する"s, u8"Train me."s);
            ++listmax;
        }
    }
    else
    {
        buff = lang(
            i18n::_(u8"ability", std::to_string(csskill), u8"name")
                + u8"の能力を習得するには"s + calclearncost(csskill, cc)
                + i18n::_(u8"ui", u8"platinum") + u8"かかるけどいい"s
                + _kana(1),
            u8"Learning "s
                + i18n::_(u8"ability", std::to_string(csskill), u8"name")
                + u8" will cost you "s + calclearncost(csskill, cc)
                + u8" platinum pieces."s);
        if (cdata[0].platinum_coin >= calclearncost(csskill, cc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"習得する"s, u8"Teach me the skill."s);
            ++listmax;
        }
    }
    list(0, listmax) = 0;
    listn(0, listmax) = lang(u8"やめる"s, u8"Never mind."s);
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        snd(12);
        if (csctrl == 2)
        {
            cdata[0].platinum_coin -= calctraincost(csskill, cc);
            modify_potential(
                cc,
                csskill,
                clamp(15 - sdata.get(csskill, cc).potential / 15, 2, 15));
            buff = lang(
                u8"訓練は完了し"s + _ta()
                    + u8"潜在能力が伸びているはずなので、後は自分で鍛えて"s
                    + _kure(),
                u8"Well done. You've got more room to develop than anyone else I've ever drilled. Keep training."s);
        }
        else
        {
            cdata[0].platinum_coin -= calclearncost(csskill, cc);
            skillgain(cc, csskill);
            ++gdata_number_of_learned_skills_by_trainer;
            buff = lang(
                u8"可能な限りの知識は教え"s + _ta() + u8"後は存分に訓練して"s
                    + _kure(),
                u8"I've taught you all that I know of the skill. Now develop it by yourself."s);
        }
    }
    else
    {
        buff = lang(
            u8"訓練が必要なときは、声をかけて"s + _kure(),
            u8"Come see me again when you need more training."s);
    }
    return talk_result_t::talk_npc;
}



talk_result_t talk_invest()
{
    listmax = 0;
    buff = lang(
        u8"投資をしてくれる"s + _noka(1) + calcinvestvalue()
            + i18n::_(u8"ui", u8"gold") + u8"かかるけどいいの"s + _kana(1),
        u8"Oh, do you want to invest in my shop? It will cost you "s
            + calcinvestvalue() + u8" golds. I hope you got the money."s);
    if (cdata[0].gold >= calcinvestvalue())
    {
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"投資する"s, u8"Invest"s);
        ++listmax;
    }
    list(0, listmax) = 0;
    listn(0, listmax) = lang(u8"やめる"s, u8"Reject"s);
    ++listmax;
    chatesc = 1;
    talk_window_query();
    if (chatval == 1)
    {
        snd(12);
        cdata[0].gold -= calcinvestvalue();
        gain_investing_experience(0);
        cdata[tc].shop_rank += rnd(2) + 2;
        buff = lang(_thanks(2), u8"Thanks!"s);
    }
    else
    {
        buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
    }
    if (gdata_current_map == 7)
    {
        calccosthire();
    }
    return talk_result_t::talk_npc;
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
            p(0) = cdata[tc].image % 1000;
            p(1) = cdata[tc].image / 1000;
            chara_preparepic(cdata[tc]);
            pos(wx + 82, wy + 125 - chara_chips[p].offset_y);
            gmode(2);
            gcopy_c(
                5,
                0,
                960,
                chara_chips[p].width,
                chara_chips[p].height,
                chara_chips[p].width * 2,
                chara_chips[p].height * 2);
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
    display_topic(lang(u8"友好"s, u8"Impress"s), wx + 28, wy + 170);
    display_topic(lang(u8"興味"s, u8"Attract"s), wx + 28, wy + 215);
    font(12 + sizefix - en * 2, snail::font_t::style_t::bold);
    if (cdatan(1, tc) == ""s)
    {
        s = cdatan(0, tc) + u8" "s;
    }
    else
    {
        s = lang(
            cdatan(1, tc) + u8" "s + cdatan(0, tc) + u8" "s,
            cdatan(0, tc) + u8" of "s + cdatan(1, tc) + u8" "s);
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
        s += lang(u8" 名声 "s, u8" Fame: "s) + cdata[tc].fame;
    }
    if ((cdata[tc].character_role >= 1000 && cdata[tc].character_role < 2000)
        || cdata[tc].character_role == 2003)
    {
        s += lang(u8" 店の規模:"s, u8" Shop Rank:"s) + cdata[tc].shop_rank;
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
