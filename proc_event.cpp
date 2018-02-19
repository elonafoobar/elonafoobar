#include "ability.hpp"
#include "animation.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace elona
{


void proc_event()
{
    switch (evid())
    {
    case 8: hunt_all_targets(); break;
    case 14:
        switch (gdata_executing_immediate_quest_type)
        {
        case 1009:
            txt(lang(u8"パーティーは終了した。"s, u8"The party is over."s));
            calcpartyscore();
            calcpartyscore2();
            txt(lang(
                u8"最終得点は"s + qdata(13, gdata_executing_immediate_quest)
                    + u8"ポイントだった！"s,
                u8"Your final score is "s
                    + qdata(13, gdata_executing_immediate_quest)
                    + u8" points!"s));
            if (qdata(12, gdata_executing_immediate_quest)
                <= qdata(13, gdata_executing_immediate_quest))
            {
                gdata(73) = 3;
                qdata(8, gdata_executing_immediate_quest) = 3;
                txtef(2);
                txt(lang(
                    u8"パーティーは大盛況だった！"s,
                    u8"People had a hell of a good time!"s));
                msg_halt();
            }
            else
            {
                txtef(8);
                txt(lang(
                    u8"パーティーはぐだぐだになった…"s,
                    u8"The party turned out to be a big flop..."s));
            }
            break;
        case 1006:
            if (qdata(12, gdata_executing_immediate_quest)
                < qdata(13, gdata_executing_immediate_quest))
            {
                gdata(73) = 3;
                qdata(8, gdata_executing_immediate_quest) = 3;
                txtef(2);
                txt(lang(
                    u8"無事に納入を終えた！"s, u8"You complete the task!"s));
                msg_halt();
            }
            else
            {
                txtef(8);
                txt(lang(
                    u8"納入は間に合わなかった…"s,
                    u8"You fail to fulfill your task..."s));
            }
            break;
        case 1008:
            txtef(8);
            txt(lang(
                u8"討伐に失敗した…"s, u8"You failed to slay the target..."s));
            break;
        }
        levelexitby = 4;
        snd(49);
        chatteleport = 1;
        break;
    case 1:
        conquer_lesimas();
        flt();
        characreate(-1, 23, cdata[0].position.x, cdata[0].position.y);
        break;
    case 27:
        if (gdata_current_map == 35)
        {
            break;
        }
        flt();
        characreate(
            -1,
            319,
            evdata1(evnum - (evnum != 0) * 1),
            evdata2(evnum - (evnum != 0) * 1));
        txtef(4);
        txt(lang(
            u8"ビッグダディの肩から、リトルシスターが滑り落ちた。「Mr Bubbles！！」"s,
            u8"The little sister slips from Big Daddy's shoulder, "s
                + cnvtalk(u8"Mr.Bubbles!"s)));
        break;
    case 28:
        txtef(5);
        txt(lang(
            u8"…ぅっぅぅ…っぅぅっぅううううみみゃぁ！！！"s,
            u8"memememw...MEMEMEM...MEWWWWWW!"s));
        msg_halt();
        play_animation(21);
        flt();
        characreate(
            -1,
            336,
            evdata1(evnum - (evnum != 0) * 1),
            evdata2(evnum - (evnum != 0) * 1));
        break;
    case 2:
        tc = findchara(34);
        speak_to_npc();
        break;
    case 24:
        initeco = 1;
        initialize_economy();
        break;
    case 3:
        tc = findchara(2);
        speak_to_npc();
        break;
    case 11:
        tc = findchara(1);
        speak_to_npc();
        break;
    case 23:
        tc = findchara(302);
        speak_to_npc();
        gdata(171) = 23;
        break;
    case 12:
        update_screen();
        s = lang(u8"ペットとの再会"s, u8"Reunion with your pet"s);
        buff = lang(
            u8"あなたは懐かしい鳴き声に気付いて、ふと歩みを止めた。なんと、船が難破した時に居なくなったあなたのペットが、嬉しそうに走ってくる！あなたのペットは…"s,
            u8"As you approach the mining town, you notice a familiar call and stop walking. Your old pet who got separated from you during the shipwreck is now running towards you joyfully! Your pet is..."s);
        listmax = 0;
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"犬だ！"s, u8"a dog!"s);
        ++listmax;
        list(0, listmax) = 2;
        listn(0, listmax) = lang(u8"猫だ！"s, u8"a cat!"s);
        ++listmax;
        list(0, listmax) = 3;
        listn(0, listmax) = lang(u8"クマだ！"s, u8"a bear!"s);
        ++listmax;
        list(0, listmax) = 4;
        listn(0, listmax) = lang(u8"少女だ！"s, u8"a little girl!"s);
        ++listmax;
        show_random_event_window(u8"bg_re13");
        p = 3;
        if (rtval == 1)
        {
            p = 165;
        }
        if (rtval == 2)
        {
            p = 164;
        }
        if (rtval == 3)
        {
            p = 108;
        }
        if (rtval == 4)
        {
            p = 166;
        }
        flt();
        initlv = cdata[0].level * 2 / 3 + 1;
        novoidlv = 1;
        characreate(-1, p, cdata[cc].position.x, cdata[cc].position.y);
        new_ally_joins();
        break;
    case 13:
        music = 80;
        play_music();
        s = lang(u8"結婚"s, u8"Marriage"s);
        buff = lang(u8"長い交際の末、遂にあなたと"s + name(marry) +
                u8"は固い絆で結ばれた。婚儀の後、あなたの元に幾つか祝儀品が届けられた。"s,
            u8"At last, you and "s + name(marry) +
                u8" are united in marriage! After the wedding ceremony, you receive some gifts."s);
        listmax = 0;
        list(0, listmax) = 1;
        listn(0, listmax) = lang(
            u8"生涯をあなたに捧げる"s, u8"Without you, life has no meaning."s);
        ++listmax;
        show_random_event_window(u8"bg_re14");
        for (int i = 0; i < 5; ++i)
        {
            flt(calcobjlv(cdata[marry].level + 5), calcfixlv(3));
            flttypemajor = fsetchest(rnd(length(fsetchest)));
            itemcreate(-1, 0, cdata[0].position.x, cdata[0].position.y, 0);
        }
        itemcreate(-1, 559, cdata[0].position.x, cdata[0].position.y, 0);
        flt();
        itemcreate(
            -1, 55, cdata[0].position.x, cdata[0].position.y, rnd(3) + 2);
        txt(lang(
            u8"何かが足元に転がってきた。"s,
            u8"Something is put on the ground."s));
        autosave = 1 * (gdata_current_map != 35);
        break;
    case 29:
        randomize(gdata_year + gdata_current_dungeon_level);
        c = choice(std::initializer_list<int>{
            300, 26,  27, 28,  29,  140, 34, 141, 143, 144,
            145, 242, 25, 257, 230, 202, 37, 33,  80,  332,
        });
        randomize();
        flt();
        fixlv = 4;
        initlv = gdata_current_dungeon_level / 4;
        characreate(-1, c, -3, 0);
        cbitmod(976, rc, 1);
        cdata[rc].relationship = -3;
        cdata[rc].original_relationship = -3;
        tc = rc;
        adata(20, gdata_current_map) = tc;
        txtef(3);
        txtmore();
        txt(lang(
            u8"気をつけろ！この階は"s + mapname(gdata_current_map)
                + u8"の守護者、"s + cdatan(0, tc) + u8"によって守られている。"s,
            u8"Be aware! This level is guarded by the lord of "s
                + mapname(gdata_current_map) + u8", "s + cdatan(0, tc)
                + u8"."s));
        break;
    case 4:
        while (1)
        {
            set_character_generation_filter();
            fixlv = 4;
            initlv = gdata_current_dungeon_level + rnd(5);
            int stat = characreate(-1, 0, -3, 0);
            if (stat == 0)
            {
                continue;
            }
            else
            {
                cbitmod(976, rc, 1);
                break;
            }
        }
        tc = rc;
        adata(20, gdata_current_map) = tc;
        cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
        txt(lang(
            u8"どうやら最深層まで辿り着いたらしい…"s,
            u8"It seems you have reached the deepest level of this dungeon."s));
        txtef(3);
        txtmore();
        txt(lang(
            u8"気をつけろ！この階は"s + mapname(gdata_current_map)
                + u8"の守護者、"s + cdatan(0, tc) + u8"によって守られている。"s,
            u8"Be aware! This level is guarded by the lord of "s
                + mapname(gdata_current_map) + u8", "s + cdatan(0, tc)
                + u8"."s));
        break;
    case 5:
        music = 64;
        play_music();
        snd(51);
        flt(calcobjlv(), calcfixlv());
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
            std::clamp(rnd(3) + gdata_current_dungeon_level / 10, 1, 6));
        flt();
        itemcreate(-1, 239, cdata[0].position.x, cdata[0].position.y, 0);
        inv[ci].param2 = 0;
        txtef(2);
        txt(lang(
            u8"クエストを達成した！"s, u8"You have completed the quest!"s));
        snd(51);
        txtmore();
        txt(lang(
            u8"何かが足元に転がってきた。"s,
            u8"Something is put on the ground."s));
        modrank(2, 300, 8);
        gdata(74) = calcfame(0, gdata_current_dungeon_level * 30 + 200);
        txtef(2);
        txtmore();
        txt(lang(
            ""s + gdata(74) + u8"の名声値を手に入れた。"s,
            u8"You gain "s + gdata(74) + u8" fame."s));
        cdata[0].fame += gdata(74);
        if (gdata_current_map == 42)
        {
            adata(20, gdata_current_map) = 0;
            gdata(186) = gdata(186) + 5;
            txt(lang(
                u8"この階の封印が解けたようだ！"s,
                u8"The seal of this level is now broken!"s));
        }
        else
        {
            adata(20, gdata_current_map) = -1;
        }
        break;
    case 16:
        txt(lang(
            u8"あなたは無事に護衛の任務を終えた。"s,
            u8"You complete the escort."s));
        tc = evdata2(evnum - (evnum != 0) * 1);
        speak_to_npc();
        rq = evdata1(evnum - (evnum != 0) * 1);
        complete_quest();
        chara_vanquish(evdata2(evnum - (evnum != 0) * 1));
        break;
    case 15:
    {
        int cnt = 0;
        for (int cnt_end = cnt + (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(3, cnt) == 1007)
            {
                if (qdata(8, cnt) == 1)
                {
                    if (qdata(13, cnt) == evdata1(evnum - (evnum != 0) * 1))
                    {
                        rq = cnt;
                        val = qdata(3, rq);
                        failed_quest();
                        break;
                    }
                }
            }
        }
    }
        break;
    case 6:
        if (cdata[0].level > 5)
        {
            {
                int cnt = 10;
                for (int cnt_end = cnt + (40); cnt < cnt_end; ++cnt)
                {
                    if (cnt <= 17)
                    {
                        if (sdata(cnt, 0) != 0)
                        {
                            if (rnd(3) == 0)
                            {
                                txtmore();
                                skillexp(cnt, 0, -500);
                            }
                        }
                    }
                }
            }
            if (cdata[0].karma < -30)
            {
                modify_karma(0, 10);
            }
        }
        else
        {
            txt(lang(
                u8"レベル6に達していないので能力値の減少はない。"s,
                u8"Death penalty won't be applied until you hit Lv 6."s));
        }
        if (gdata_ether_disease_stage >= 20000)
        {
            modcorrupt(-2000);
        }
        txtmore();
        txt(lang(u8"金貨を幾らか失った…"s, u8"You lost some money."s));
        cdata[0].gold -= cdata[0].gold / 3;
        decfame(0, 10);
        r1 = 0;
        refresh_character();
        autosave = 1 * (gdata_current_map != 35);
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
        tc = findchara(221);
        if (tc != 0)
        {
            if (cdata[tc].state == 1)
            {
                txtef(4);
                txt(lang(
                    u8"パエル「おかあさんーー！！」"s,
                    cnvtalk(u8"M-mom...!!"s)));
                cdata[tc].relationship = -3;
                cdata[tc].hate = 1000;
                cdata[tc].enemy_id = 0;
            }
        }
        break;
    case 7:
        label_1444();
        press();
        screenupdate = -1;
        update_entire_screen();
        break;
    case 10: label_2673(); break;
    case 19:
        txtef(6);
        txt(""s + usermsg);
        break;
    case 25:
        --gdata_number_of_waiting_guests;
        if (get_freechara() == -1)
        {
            txt(lang(
                u8"ゲストは行方不明になった。"s, u8"The guest lost his way."s));
            break;
        }
        if (rnd(3) || 0)
        {
            p = 0;
            tc = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
                {
                    i = rnd(39) + 16;
                    if (cdata[i].state == 3)
                    {
                        if (cbit(969, i) == 0
                            && cdata[i].current_map != gdata_current_map)
                        {
                            if (cdata[i].relationship >= 0)
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
                    }
                }
            }
            if (tc == 0)
            {
                txt(lang(
                    u8"ゲストはすでに居なくなっていた。"s,
                    u8"It seems the guest has already left your house."s));
                break;
            }
            cdata[tc].state = 1;
            rc = tc;
            cxinit = cdata[0].position.x;
            cyinit = cdata[0].position.y;
            place_character();
        }
        else
        {
            flt(0, 2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
                {
                    if (gdata_last_month_when_trainer_visited != gdata_month
                        || rnd(5) == 0)
                    {
                        if (rnd(3))
                        {
                            characreate(-1, 333, -3, 0);
                            cdata[rc].character_role = 2005;
                            break;
                        }
                    }
                    if (rnd(10) == 0)
                    {
                        characreate(-1, 334, -3, 0);
                        cdata[rc].character_role = 2006;
                        break;
                    }
                    if (rnd(10) == 0)
                    {
                        characreate(-1, 1, -3, 0);
                        cdata[rc].character_role = 2003;
                        cdata[rc].shop_rank =
                            std::clamp(cdata[0].fame / 100, 20, 100);
                        break;
                    }
                    if (rnd(4) == 0)
                    {
                        characreate(-1, 9, -3, 0);
                        cdata[rc].character_role = 2000;
                        break;
                    }
                    if (rnd(4) == 0)
                    {
                        characreate(-1, 174, -3, 0);
                        cdata[rc].character_role = 2001;
                        break;
                    }
                    characreate(-1, 16, -3, 0);
                    cdata[rc].character_role = 2002;
                    break;
                }
            }
            tc = rc;
            cdata[tc].relationship = 0;
            cdata[tc].original_relationship = 0;
            cbitmod(964, tc, 1);
        }
        cbitmod(982, tc, 1);
        i = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (17); cnt < cnt_end; ++cnt)
            {
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
                inv_getheader(-1);
                p(0) = 0;
                p(1) = 6;
                {
                    int cnt = invhead;
                    for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                    {
                        if (inv[cnt].number == 0)
                        {
                            continue;
                        }
                        if (inv[cnt].function != 44)
                        {
                            continue;
                        }
                        if (c == tc)
                        {
                            if (inv[cnt].param1 == 2)
                            {
                                cell_swap(
                                    c,
                                    -1,
                                    inv[cnt].position.x,
                                    inv[cnt].position.y);
                                i = cnt;
                                p = cnt;
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
                        else if (cnt == i)
                        {
                            continue;
                        }
                        p(2) = dist(
                            inv[cnt].position.x,
                            inv[cnt].position.y,
                            inv[i].position.x,
                            inv[i].position.y);
                        if (p(2) < p(1))
                        {
                            if (map(inv[cnt].position.x, inv[cnt].position.y, 1)
                                    == 0
                                || c == 0 || c == tc)
                            {
                                p(0) = cnt;
                                p(1) = p(2);
                            }
                        }
                        if (c == 0)
                        {
                            if (inv[cnt].param1 == 1)
                            {
                                p = cnt;
                                break;
                            }
                        }
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
        }
        speak_to_npc();
        break;
    case 30:
        i = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].character_role != 13)
                {
                    if (cdata[cnt].character_role != 3)
                    {
                        cdata[cnt].emotion_icon = 2010;
                        txt(lang(
                            name(cnt) + u8"「目が！目がー！！」"s,
                            name(cnt) + u8" shout"s + _s(cnt) + u8" "s
                                + cnvtalk(u8"Eyes! My eyes!"s)));
                    }
                }
            }
        }
        break;
    case 17:
        i = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cnt == 0)
                {
                    continue;
                }
                if (cdata[cnt].character_role != 13)
                {
                    if (cdata[cnt].character_role != 3)
                    {
                        if (cdata[cnt].character_role != 0
                            || cdata[cnt].relationship == 0
                            || cdata[cnt].current_map == gdata_current_map)
                        {
                            cdata[cnt].emotion_icon = 2006;
                            int stat = customtalk(cnt, 104);
                            if (stat == 0)
                            {
                                ++i;
                            }
                        }
                    }
                }
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (std::clamp(i(0), 0, 3)); cnt < cnt_end;
                 ++cnt)
            {
                txtef(9);
                if (jp)
                {
                    txt(u8"「おかえり」"s,
                        u8"「よう戻ったか」"s,
                        u8"「無事で何よりです」"s,
                        u8"「おかか♪」"s,
                        u8"「待ってたよ」"s,
                        u8"「おかえりなさい！」"s);
                }
                if (en)
                {
                    txt(cnvtalk(u8"Welcome home!"s),
                        cnvtalk(u8"Hey, dear."s),
                        cnvtalk(u8"You're back!"s),
                        cnvtalk(u8"I was waiting for you."s),
                        cnvtalk(u8"Nice to see you again."s));
                }
            }
        }
        if (gdata_number_of_waiting_guests != 0)
        {
            tc = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
                {
                    if (cdata[cnt].state != 1)
                    {
                        continue;
                    }
                    if (cdata[cnt].character_role == 18)
                    {
                        tc = cnt;
                        break;
                    }
                }
            }
            if (tc != 0)
            {
                speak_to_npc();
            }
        }
        break;
    case 21:
        if (mdata(6) == 1)
        {
            break;
        }
        txtef(3);
        txt(lang(u8" *ゴゴゴゴゴゴ* "s, u8"* RRROOM-KABOOOOM*"s));
        msg_halt();
        gsel(7);
        pos(0, 0);
        picload(fs::u8path(u8"./graphic/bg22.bmp"));
        gsel(4);
        pos(windoww / 2 - 1, windowh / 2 - 1);
        gmode(0, 640, 480);
        grotate(7, 0, 0, 0, windoww + 4, windowh + 4);
        gsel(7);
        picload(fs::u8path(u8"./graphic/anime9.bmp"));
        gsel(0);
        dx = windoww / 2;
        dy = (windowh - inf_verh) / 2;
        p(0) = 0;
        p(1) = 0;
        p(2) = 0;
        p(3) = 0;
        p(4) = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (40); cnt < cnt_end; ++cnt)
            {
                if (cnt == 14)
                {
                    snd(108);
                }
                redraw(0);
                if (cnt < 16)
                {
                    pos(0, 0);
                }
                else
                {
                    pos(5 - rnd(10), 5 - rnd(10));
                }
                gmode(0);
                gcopy(4, 0, 0, windoww, windowh);
                if (cnt > 8)
                {
                    --p;
                }
                else
                {
                    ++p;
                }
                gmode(4, 192, 48, 255 - p * 5);
                pos(dx, dy);
                grotate(
                    7,
                    cnt / 2 % 2 * 192,
                    408,
                    0,
                    std::clamp(p * 32, 0, 192),
                    std::clamp(p * 8, 0, 48));
                if (cnt > 14)
                {
                    ++p(1);
                }
                else if (cnt < 12)
                {
                    p(1) = cnt / 2 % 2;
                }
                else if (cnt >= 12)
                {
                    p(1) = cnt % 3;
                }
                gmode(2, 96, 48);
                pos(dx, dy - std::clamp(cnt * 3 / 2, 0, 18) - 16);
                grotate(
                    7,
                    p(1) * 96,
                    288,
                    0,
                    std::clamp(cnt * 12, 0, 144),
                    std::clamp(cnt * 6, 0, 72));
                if (cnt > 4)
                {
                    ++p(2);
                    ++p(3);
                }
                gmode(4, 96, 96, std::clamp(p(2) * 6, 0, 100));
                pos(dx, dy - std::clamp(p(2) * 2, 0, 40));
                grotate(
                    7,
                    0,
                    0,
                    0,
                    std::clamp(p(2) * 8, 0, 240),
                    std::clamp(p(2) * 5, 0, 96));
                gmode(4, 96, 96, p(3) * 10);
                pos(dx, dy - std::clamp(p(3) * 2, 0, 160) - 6);
                grotate(
                    7,
                    96,
                    0,
                    0,
                    std::clamp(p(3) * 10, 0, 96),
                    std::clamp(p(3) * 10, 0, 96));
                gmode(4, 192, 80, std::clamp(p(3) * 5, 0, 100));
                pos(dx, dy - 4);
                grotate(
                    7,
                    cnt / 4 % 2 * 192,
                    96,
                    0,
                    std::clamp(p(2) * 8, 0, 400),
                    std::clamp(p(2), 0, 48));
                gmode(4, 192, 96, p(3) * 10);
                pos(dx, dy - 48 - std::clamp(p(3) * 2, 0, 148));
                grotate(7, cnt / 3 % 2 * 192, 96, 0, 192, 96);
                redraw(1);
                await(cfg_animewait + 50);
            }
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
        play_animation(17);
        update_screen();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (range_ * 2 + 1); cnt < cnt_end; ++cnt)
            {
                dy = tlocy - range_ + cnt;
                if (dy < 0 || dy >= mdata(1))
                {
                    continue;
                }
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (range_ * 2 + 1); cnt < cnt_end;
                         ++cnt)
                    {
                        dx = tlocx - range_ + cnt;
                        if (dx < 0 || dx >= mdata(0))
                        {
                            continue;
                        }
                        if (dist(tlocx, tlocy, dx, dy) > range_)
                        {
                            continue;
                        }
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
                            addmef(dx, dy, 5, 24, rnd(15) + 20, 50);
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
        }
        if (evdata1(evnum - (evnum != 0) * 1) == 33)
        {
            if (evdata2(evnum - (evnum != 0) * 1) == 16)
            {
                if (gdata_current_map == 15)
                {
                    if (gdata_red_blossom_in_palmia == 1)
                    {
                        gdata_red_blossom_in_palmia = 2;
                        snd(44);
                        txtef(2);
                        txt(lang(
                            u8"ジャーナルが更新された。"s,
                            u8"Your journal has been updated."s));
                    }
                }
            }
        }
        if (mdata(6) == 3 || mdata(6) == 2)
        {
            modify_karma(0, -80 + trait(162) * 60);
        }
        else
        {
            modify_karma(0, -10);
        }
        break;
    case 18:
        if (mdata(6) == 1)
        {
            break;
        }
        gdata_weather = 1;
        envonly = 1;
        play_music();
        txt(lang(u8"終末の日が訪れた。"s, u8"Let's Ragnarok!"s));
        msg_halt();
        play_animation(21);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (200); cnt < cnt_end; ++cnt)
            {
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt)
                    {
                        x = rnd(mdata(0));
                        y = rnd(mdata(1));
                        map(x, y, 0) = 37;
                    }
                }
                x = rnd(inf_screenw) + scx;
                y = rnd(inf_screenh) + scy;
                if (x < 0 || y < 0 || x >= mdata(0) || y >= mdata(1)
                    || rnd(5) == 0)
                {
                    x = rnd(mdata(0));
                    y = rnd(mdata(1));
                }
                addmef(
                    x,
                    y,
                    5,
                    24,
                    rnd(15) + 20,
                    50,
                    evdata1(evnum - (evnum != 0) * 1));
                mapitem_fire(x, y);
                if (cnt % 4 == 0)
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
                    int stat = characreate(-1, 0, x, y);
                    if (stat != 0)
                    {
                        cbitmod(964, rc, 1);
                    }
                }
                if (cnt % 7 == 0)
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
                    await(25);
                }
            }
        }
        break;
    case 22:
        if (evdata1(evnum - (evnum != 0) * 1) == 0)
        {
            txtef(3);
            txt(lang(
                u8"けたたましい警報が鳴り響いた！"s,
                u8"*beeeeeep!* An alarm sounds loudly!"s));
            {
                int cnt = 57;
                for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt)
                {
                    if (cdata[cnt].state == 1)
                    {
                        cdata[cnt].relationship = -3;
                        cdata[cnt].enemy_id = 0;
                        cdata[cnt].hate = 250;
                    }
                }
            }
        }
        break;
    case 26:
        if (mdata(6) != 1)
        {
            txt(lang(
                u8"強盗があなたに目をつけた！"s, u8"Blaggers pick on you!"s));
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
                {
                    flt();
                    initlv = cdata[0].level;
                    characreate(
                        -1, 215, cdata[0].position.x, cdata[0].position.y);
                }
            }
        }
        break;
    }
}



} // namespace elona
