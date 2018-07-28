#include "ability.hpp"
#include "animation.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map_cell.hpp"
#include "mef.hpp"
#include "quest.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{


void proc_event()
{
    switch (event_id())
    {
    case 8: quest_all_targets_killed(); break;
    case 14:
        switch (gdata_executing_immediate_quest_type)
        {
        case 1009:
            txt(i18n::s.get("core.locale.quest.party.is_over"));
            calcpartyscore();
            calcpartyscore2();
            txt(i18n::s.get(
                "core.locale.quest.party.final_score",
                qdata(13, gdata_executing_immediate_quest)));
            if (qdata(12, gdata_executing_immediate_quest)
                <= qdata(13, gdata_executing_immediate_quest))
            {
                gdata(73) = 3;
                qdata(8, gdata_executing_immediate_quest) = 3;
                txtef(2);
                txt(i18n::s.get("core.locale.quest.party.complete"));
                msg_halt();
            }
            else
            {
                txtef(8);
                txt(i18n::s.get("core.locale.quest.party.fail"));
            }
            break;
        case 1006:
            if (qdata(12, gdata_executing_immediate_quest)
                < qdata(13, gdata_executing_immediate_quest))
            {
                gdata(73) = 3;
                qdata(8, gdata_executing_immediate_quest) = 3;
                txtef(2);
                txt(i18n::s.get("core.locale.quest.collect.complete"));
                msg_halt();
            }
            else
            {
                txtef(8);
                txt(i18n::s.get("core.locale.quest.collect.fail"));
            }
            break;
        case 1008:
            txtef(8);
            txt(i18n::s.get("core.locale.quest.conquer.fail"));
            break;
        }
        levelexitby = 4;
        snd(49);
        chatteleport = 1;
        break;
    case 1:
        conquer_lesimas();
        flt();
        chara_create(-1, 23, cdata[0].position.x, cdata[0].position.y);
        break;
    case 27:
        if (gdata_current_map == mdata_t::map_id_t::show_house)
        {
            break;
        }
        flt();
        chara_create(
            -1,
            319,
            evdata1(evnum - (evnum != 0) * 1),
            evdata2(evnum - (evnum != 0) * 1));
        txtef(4);
        txt(i18n::s.get("core.locale.event.little_sister_slips"));
        break;
    case 28:
        txtef(5);
        txt(i18n::s.get("core.locale.event.ehekatl"));
        msg_halt();
        ragnarok_animation().play();
        flt();
        chara_create(
            -1,
            336,
            evdata1(evnum - (evnum != 0) * 1),
            evdata2(evnum - (evnum != 0) * 1));
        break;
    case 2:
        tc = chara_find(34);
        talk_to_npc();
        break;
    case 24:
        initeco = 1;
        initialize_economy();
        break;
    case 3:
        tc = chara_find(2);
        talk_to_npc();
        break;
    case 11:
        tc = chara_find(1);
        talk_to_npc();
        break;
    case 23:
        tc = chara_find(302);
        talk_to_npc();
        gdata(171) = 23;
        break;
    case 12:
        update_screen();
        s = i18n::s.get("core.locale.event.popup.reunion_with_pet.title");
        buff = i18n::s.get("core.locale.event.popup.reunion_with_pet.text");
        listmax = 4;
        for (int cnt = 0; cnt < listmax; cnt++)
        {
            list(0, cnt) = cnt;
            listn(0, cnt) = i18n::s.get_enum("core.locale.event.popup.reunion_with_pet.choices",
                                             cnt);
        }
        {
            int result = show_random_event_window(u8"bg_re13");
            p = 3;
            if (result == 0)
            {
                p = 165;
            }
            if (result == 1)
            {
                p = 164;
            }
            if (result == 2)
            {
                p = 108;
            }
            if (result == 3)
            {
                p = 166;
            }
        }
        flt();
        initlv = cdata[0].level * 2 / 3 + 1;
        novoidlv = 1;
        chara_create(-1, p, cdata[cc].position.x, cdata[cc].position.y);
        new_ally_joins();
        break;
    case 13:
        play_music("core.music.mcWedding");
        s = i18n::s.get("core.locale.event.popup.marriage.title");
        buff = i18n::s.get("core.locale.event.popup.marriage.text", cdata[marry]);
        listmax = 1;
        for (int cnt = 0; cnt < listmax; cnt++)
        {
            list(0, cnt) = cnt;
            listn(0, cnt) = i18n::s.get_enum("core.locale.event.popup.marriage.choices",
                                             cnt);
        }
        show_random_event_window(u8"bg_re14");
        for (int i = 0; i < 5; ++i)
        {
            flt(calcobjlv(cdata[marry].level + 5), calcfixlv(3));
            flttypemajor = choice(fsetchest);
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        }
        itemcreate(-1, 559, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(
            -1, 55, cdata[0].position.x, cdata[0].position.y, rnd(3) + 2);
        txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
        autosave = 1 * (gdata_current_map != mdata_t::map_id_t::show_house);
        break;
    case 29:
    {
        randomize(gdata_year + gdata_current_dungeon_level);
        int c = choice(std::initializer_list<int>{
            300, 26,  27, 28,  29,  140, 34, 141, 143, 144,
            145, 242, 25, 257, 230, 202, 37, 33,  80,  332,
        });
        randomize();
        flt();
        fixlv = 4;
        initlv = clamp(gdata_current_dungeon_level / 4, 50, 250);
        chara_create(-1, c, -3, 0);
        cdata[rc].is_lord_of_dungeon() = true;
        cdata[rc].relationship = -3;
        cdata[rc].original_relationship = -3;
        tc = rc;
        adata(20, gdata_current_map) = tc;
        txtef(3);
        txt(i18n::s.get("core.locale.event.guarded_by_lord", mapname(gdata_current_map), cdata[tc]));
    }
    break;
    case 4:
        while (1)
        {
            chara_set_generation_filter();
            fixlv = 4;
            initlv = gdata_current_dungeon_level + rnd(5);
            int stat = chara_create(-1, 0, -3, 0);
            if (stat == 0)
            {
                continue;
            }
            else
            {
                cdata[rc].is_lord_of_dungeon() = true;
                break;
            }
        }
        tc = rc;
        adata(20, gdata_current_map) = tc;
        cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
        txt(i18n::s.get("core.locale.event.reached_deepest_level"));
        txtef(3);
        txt(i18n::s.get("core.locale.event.guarded_by_lord", mapname(gdata_current_map), cdata[tc]));
        break;
    case 5:
        play_music("core.music.mcVictory");
        snd(51);
        flt(0, calcfixlv());
        flttypemajor = 54000;
        itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(-1, 236, cdata[0].position.x, cdata[0].position.y, 0);
        nostack = 1;
        flt();
        itemcreate(-1, 54, cdata[0].position.x, cdata[0].position.y);
        inv[ci].number = 200 + inv[ci].number * 5;
        flt();
        itemcreate(
            -1,
            55,
            cdata[0].position.x,
            cdata[0].position.y,
            clamp(rnd(3) + gdata_current_dungeon_level / 10, 1, 6));
        flt();
        itemcreate(-1, 239, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param2 = 0;
        txtef(2);
        txt(i18n::s.get("core.locale.quest.completed"));
        snd(51);
        txt(i18n::s.get("core.locale.common.something_is_put_on_the_ground"));
        modrank(2, 300, 8);
        gdata(74) = calcfame(0, gdata_current_dungeon_level * 30 + 200);
        txtef(2);
        txt(i18n::s.get("core.locale.quest.gain_fame", gdata(74)));
        cdata[0].fame += gdata(74);
        if (gdata_current_map == mdata_t::map_id_t::the_void)
        {
            adata(20, gdata_current_map) = 0;
            gdata(186) = gdata(186) + 5;
            txt(i18n::s.get("core.locale.event.seal_broken"));
        }
        else
        {
            adata(20, gdata_current_map) = -1;
        }
        break;
    case 16:
        txt(i18n::s.get("core.locale.quest.escort.complete"));
        tc = evdata2(evnum - (evnum != 0) * 1);
        talk_to_npc();
        rq = evdata1(evnum - (evnum != 0) * 1);
        quest_complete();
        chara_vanquish(evdata2(evnum - (evnum != 0) * 1));
        break;
    case 15:
        for (int i = 0; i < gdata_number_of_existing_quests; ++i)
        {
            if (qdata(3, i) == 1007 && qdata(8, i) == 1
                && qdata(13, i) == evdata1(evnum - (evnum != 0) * 1))
            {
                rq = i;
                quest_failed(qdata(3, rq));
                break;
            }
        }
        break;
    case 6:
        if (cdata[0].level > 5)
        {
            for (int i = 10; i < 18; ++i)
            {
                if (sdata(i, 0) != 0 && rnd(3) == 0)
                {
                    skillexp(i, 0, -500);
                }
            }
            if (cdata[0].karma < -30)
            {
                modify_karma(0, 10);
            }
        }
        else
        {
            txt(i18n::s.get("core.locale.event.death_penalty_not_applied"));
        }
        if (gdata_ether_disease_stage >= 20000)
        {
            modcorrupt(-2000);
        }
        txt(i18n::s.get("core.locale.event.you_lost_some_money"));
        cdata[0].gold -= cdata[0].gold / 3;
        decfame(0, 10);
        chara_refresh(0);
        autosave = 1 * (gdata_current_map != mdata_t::map_id_t::show_house);
        break;
    case 20:
        dmghp(evdata1(evnum - (evnum != 0) * 1), 9999, -11);
        cdata[evdata1(evnum - (evnum != 0) * 1)].character_role = 0;
        cdata[evdata1(evnum - (evnum != 0) * 1)].state = 0;
        flt();
        itemcreate(
            -1,
            55,
            cdata[evdata1(evnum - (evnum != 0) * 1)].position.x,
            cdata[evdata1(evnum - (evnum != 0) * 1)].position.y,
            4);
        gdata_pael_and_her_mom = 1001;
        tc = chara_find(221);
        if (tc != 0)
        {
            if (cdata[tc].state == 1)
            {
                txtef(4);
                txt(i18n::s.get("core.locale.event.pael"));
                cdata[tc].relationship = -3;
                cdata[tc].hate = 1000;
                cdata[tc].enemy_id = 0;
            }
        }
        break;
    case 7:
        label_1444();
        wait_key_pressed();
        screenupdate = -1;
        update_entire_screen();
        break;
    case 10: quest_check_all_for_failed(); break;
    case 19:
        txtef(6);
        txt(""s + usermsg);
        break;
    case 25:
        --gdata_number_of_waiting_guests;
        if (chara_get_free_slot() == -1)
        {
            txt(i18n::s.get("core.locale.event.guest_lost_his_way"));
            break;
        }
        if (rnd(3) == 0)
        {
            flt(0, 2);
            for (int i = 0; i < 1; ++i)
            {
                if (gdata_last_month_when_trainer_visited != gdata_month
                    || rnd(5) == 0)
                {
                    if (rnd(3))
                    {
                        chara_create(-1, 333, -3, 0);
                        cdata[rc].character_role = 2005;
                        break;
                    }
                }
                if (rnd(10) == 0)
                {
                    chara_create(-1, 334, -3, 0);
                    cdata[rc].character_role = 2006;
                    break;
                }
                if (rnd(10) == 0)
                {
                    chara_create(-1, 1, -3, 0);
                    cdata[rc].character_role = 2003;
                    cdata[rc].shop_rank = clamp(cdata[0].fame / 100, 20, 100);
                    break;
                }
                if (rnd(4) == 0)
                {
                    chara_create(-1, 9, -3, 0);
                    cdata[rc].character_role = 2000;
                    break;
                }
                if (rnd(4) == 0)
                {
                    chara_create(-1, 174, -3, 0);
                    cdata[rc].character_role = 2001;
                    break;
                }
                chara_create(-1, 16, -3, 0);
                cdata[rc].character_role = 2002;
                break;
            }
            tc = rc;
            cdata[tc].relationship = 0;
            cdata[tc].original_relationship = 0;
            cdata[tc].is_temporary() = true;
        }
        else
        {
            p = 0;
            tc = 0;
            for (int j = 0; j < 100; ++j)
            {
                i = rnd(39) + 16;
                if (cdata[i].state == 3 && cdata[i].is_contracting() == 0
                    && cdata[i].current_map != gdata_current_map
                    && cdata[i].relationship >= 0)
                {
                    if (rnd(25) < p)
                    {
                        break;
                    }
                    if (tc == 0)
                    {
                        tc = i;
                        ++p;
                        if (cdata[tc].impression < 25)
                        {
                            if (rnd(12) == 0)
                            {
                                break;
                            }
                        }
                        if (cdata[tc].impression < 0)
                        {
                            if (rnd(4))
                            {
                                break;
                            }
                        }
                        continue;
                    }
                    if (cdata[tc].impression < cdata[i].impression)
                    {
                        tc = i;
                        ++p;
                    }
                }
            }
            if (tc == 0)
            {
                txt(i18n::s.get("core.locale.event.guest_already_left"));
                break;
            }
            cdata[tc].state = 1;
            rc = tc;
            cxinit = cdata[0].position.x;
            cyinit = cdata[0].position.y;
            chara_place();
        }
        cdata[tc].visited_just_now() = true;
        i = 0;
        for (int cnt = 0; cnt < 17; ++cnt) // 17?
        {
            int c{};
            if (cnt == 0)
            {
                c = tc;
            }
            else
            {
                c = cnt - 1;
            }
            if (cdata[c].state != 1)
            {
                continue;
            }
            if (gdata_mount != 0)
            {
                if (c == gdata_mount)
                {
                    continue;
                }
            }
            p(0) = 0;
            p(1) = 6;
            for (const auto& ci : items(-1))
            {
                if (inv[ci].number == 0)
                    continue;
                if (inv[ci].function != 44)
                    continue;
                if (c == tc)
                {
                    if (inv[ci].param1 == 2)
                    {
                        cell_swap(
                            c, -1, inv[ci].position.x, inv[ci].position.y);
                        i = ci;
                        p = ci;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                if (i == 0)
                {
                    break;
                }
                else if (ci == i)
                {
                    continue;
                }
                p(2) = dist(
                    inv[ci].position.x,
                    inv[ci].position.y,
                    inv[i].position.x,
                    inv[i].position.y);
                if (p(2) < p(1))
                {
                    if (map(inv[ci].position.x, inv[ci].position.y, 1) == 0
                        || c == 0 || c == tc)
                    {
                        p(0) = ci;
                        p(1) = p(2);
                    }
                }
                if (c == 0 && inv[ci].param1 == 1)
                {
                    p = ci;
                    break;
                }
            }
            if (p != 0)
            {
                cell_swap(c, -1, inv[p].position.x, inv[p].position.y);
            }
            cdata[c].direction = direction(
                cdata[c].position.x,
                cdata[c].position.y,
                cdata[tc].position.x,
                cdata[tc].position.y);
            if (c == 0)
            {
                gdata(35) = cdata[c].direction;
            }
        }
        talk_to_npc();
        break;
    case 30:
        i = 0;
        for (int cc = 0; cc < 16; ++cc)
        {
            if (cdata[cc].state != 1)
                continue;
            if (cdata[cc].character_role != 13 && cdata[cc].character_role != 3)
            {
                cdata[cc].emotion_icon = 2010;
                txt(i18n::s.get("core.locale.event.my_eyes", cdata[cc]));
            }
        }
        break;
    case 17:
        i = 0;
        for (int cc = 1; cc < ELONA_MAX_CHARACTERS; ++cc)
        {
            if (cdata[cc].state != 1)
                continue;
            if (cdata[cc].character_role != 13 && cdata[cc].character_role != 3)
            {
                if (cdata[cc].character_role != 0 || cdata[cc].relationship == 0
                    || cdata[cc].current_map == gdata_current_map)
                {
                    cdata[cc].emotion_icon = 2006;
                    int stat = chara_custom_talk(cc, 104);
                    if (stat == 0)
                    {
                        ++i;
                    }
                }
            }
        }
        for (int j = 0; j < clamp(i(0), 0, 3); ++j)
        {
            txtef(9);
            // TODO JP had 6 choices but EN had 5. An extra choice was
            // added for EN so the lists would be the same length. It
            // would be nice to have a way to check the number of
            // variants in a list of translation choices.
            int text_index = rnd(6);
            txt(i18n::s.get_enum("core.locale.event.okaeri", text_index));
        }
        if (gdata_number_of_waiting_guests != 0)
        {
            tc = 0;
            for (int cc = 0; cc < ELONA_MAX_CHARACTERS; ++cc)
            {
                if (cdata[cc].state != 1)
                    continue;
                if (cdata[cc].character_role == 18)
                {
                    tc = cc;
                    break;
                }
            }
            if (tc != 0)
            {
                talk_to_npc();
            }
        }
        break;
    case 21:
        if (mdata_map_type == mdata_t::map_type_t::world_map)
            break;
        txtef(3);
        txt(i18n::s.get("core.locale.event.bomb"));
        msg_halt();
        gsel(7);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"bg22.bmp");
        gsel(4);
        pos(windoww / 2 - 1, windowh / 2 - 1);
        gmode(0);
        gcopy_c(7, 0, 0, 640, 480, windoww + 4, windowh + 4);
        gsel(7);
        picload(filesystem::dir::graphic() / u8"anime9.bmp");
        gsel(0);
        dx = windoww / 2;
        dy = (windowh - inf_verh) / 2;
        p(0) = 0;
        p(1) = 0;
        p(2) = 0;
        p(3) = 0;
        p(4) = 0;
        for (int i = 0; i < 40; ++i)
        {
            if (i == 14)
            {
                snd(108);
            }
            if (i < 16)
            {
                pos(0, 0);
            }
            else
            {
                pos(5 - rnd(10), 5 - rnd(10));
            }
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            if (i > 8)
            {
                --p;
            }
            else
            {
                ++p;
            }
            pos(dx, dy);
            gmode(4, 255 - p * 5);
            gcopy_c(
                7,
                i / 2 % 2 * 192,
                408,
                192,
                48,
                clamp(p * 32, 0, 192),
                clamp(p * 8, 0, 48));
            if (i > 14)
            {
                ++p(1);
            }
            else if (i < 12)
            {
                p(1) = i / 2 % 2;
            }
            else if (i >= 12)
            {
                p(1) = i % 3;
            }
            pos(dx, dy - clamp(i * 3 / 2, 0, 18) - 16);
            gmode(2);
            gcopy_c(
                7,
                p(1) * 96,
                288,
                96,
                48,
                clamp(i * 12, 0, 144),
                clamp(i * 6, 0, 72));
            if (i > 4)
            {
                ++p(2);
                ++p(3);
            }
            pos(dx, dy - clamp(p(2) * 2, 0, 40));
            gmode(4, clamp(p(2) * 6, 0, 100));
            gcopy_c(
                7,
                0,
                0,
                96,
                96,
                clamp(p(2) * 8, 0, 240),
                clamp(p(2) * 5, 0, 96));
            pos(dx, dy - clamp(p(3) * 2, 0, 160) - 6);
            gmode(4, p(3) * 10);
            gcopy_c(
                7,
                96,
                0,
                96,
                96,
                clamp(p(3) * 10, 0, 96),
                clamp(p(3) * 10, 0, 96));
            pos(dx, dy - 4);
            gmode(4, clamp(p(3) * 5, 0, 100));
            gcopy_c(
                7,
                i / 4 % 2 * 192,
                96,
                192,
                80,
                clamp(p(2) * 8, 0, 400),
                clamp(p(2), 0, 48));
            pos(dx, dy - 48 - clamp(p(3) * 2, 0, 148));
            gmode(4, p(3) * 10);
            gcopy_c(7, i / 3 % 2 * 192, 192, 96, 96, 192, 96);
            redraw();
            await(config::instance().animewait * 3.5);
        }
        gmode(2);
        update_entire_screen();
        tlocx = evdata1(evnum - (evnum != 0) * 1);
        tlocy = evdata2(evnum - (evnum != 0) * 1);
        range_ = 31;
        ele = 59;
        aniref = range_;
        anix = tlocx;
        aniy = tlocy;
        ball_animation(ball_animation::type_t::atomic_bomb).play();
        update_screen();
        for (int i = 0; i < range_ * 2 + 1; ++i)
        {
            dy = tlocy - range_ + i;
            if (dy < 0 || dy >= mdata_map_height)
                continue;
            {
                for (int j = 0; j < range_ * 2 + 1; ++j)
                {
                    dx = tlocx - range_ + j;
                    if (dx < 0 || dx >= mdata_map_width)
                        continue;
                    if (dist(tlocx, tlocy, dx, dy) > range_)
                        continue;
                    f = 0;
                    if (chipm(7, map(dx, dy, 0)) & 4)
                    {
                        f = 1;
                    }
                    if (rnd(4) || f == 1)
                    {
                        map(dx, dy, 0) = 37;
                    }
                    if (rnd(10) == 0 || f == 1)
                    {
                        mef_add(dx, dy, 5, 24, rnd(15) + 20, 50);
                    }
                    if (map(dx, dy, 1) != 0)
                    {
                        tc = map(dx, dy, 1) - 1;
                        dmg = 1000;
                        dmghp(tc, dmg, -17);
                    }
                    mapitem_fire(dx, dy);
                }
            }
        }
        if (evdata1(evnum - (evnum != 0) * 1) == 33
            && evdata2(evnum - (evnum != 0) * 1) == 16
            && gdata_current_map == mdata_t::map_id_t::palmia && gdata_red_blossom_in_palmia == 1)
        {
            gdata_red_blossom_in_palmia = 2;
            snd(44);
            txtef(2);
            txt(i18n::s.get("core.locale.quest.journal_updated"));
        }
        if (mdata_map_type == mdata_t::map_type_t::town || mdata_map_type == mdata_t::map_type_t::guild)
        {
            modify_karma(0, -80 + trait(162) * 60);
        }
        else
        {
            modify_karma(0, -10);
        }
        break;
    case 18:
        if (mdata_map_type == mdata_t::map_type_t::world_map)
            break;
        gdata_weather = 1;
        sound_play_environmental();
        txt(i18n::s.get("core.locale.event.ragnarok"));
        msg_halt();
        ragnarok_animation().play();
        for (int i = 0; i < 200; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                x = rnd(mdata_map_width);
                y = rnd(mdata_map_height);
                map(x, y, 0) = 37;
            }
            x = rnd(inf_screenw) + scx;
            y = rnd(inf_screenh) + scy;
            if (x < 0 || y < 0 || x >= mdata_map_width || y >= mdata_map_height || rnd(5) == 0)
            {
                x = rnd(mdata_map_width);
                y = rnd(mdata_map_height);
            }
            mef_add(
                x,
                y,
                5,
                24,
                rnd(15) + 20,
                50,
                evdata1(evnum - (evnum != 0) * 1));
            mapitem_fire(x, y);
            if (i % 4 == 0)
            {
                flt(100, calcfixlv(3));
                if (rnd(4))
                {
                    fltnrace = u8"dragon"s;
                }
                else
                {
                    fltnrace = u8"giant"s;
                }
                int stat = chara_create(-1, 0, x, y);
                if (stat != 0)
                {
                    cdata[rc].is_temporary() = true;
                }
            }
            if (i % 7 == 0)
            {
                update_screen();
                if (rnd(7))
                {
                    snd(6);
                }
                else
                {
                    snd(45);
                }
                await(config::instance().animewait);
            }
        }
        break;
    case 22:
        if (evdata1(evnum - (evnum != 0) * 1) != 0)
            break;
        txtef(3);
        txt(i18n::s.get("core.locale.event.alarm"));
        for (int cc = ELONA_MAX_PARTY_CHARACTERS; cc < ELONA_MAX_CHARACTERS;
             ++cc)
        {
            if (cdata[cc].state == 1)
            {
                cdata[cc].relationship = -3;
                cdata[cc].enemy_id = 0;
                cdata[cc].hate = 250;
            }
        }
        break;
    case 26:
        if (mdata_map_type == mdata_t::map_type_t::world_map)
            break;
        txt(i18n::s.get("core.locale.event.beggars"));
        for (int i = 0; i < 3; ++i)
        {
            flt();
            initlv = cdata[0].level;
            chara_create(-1, 215, cdata[0].position.x, cdata[0].position.y);
        }
        break;
    }
}



} // namespace elona
