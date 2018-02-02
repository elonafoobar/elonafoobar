#include "elona.hpp"
#include "variables.hpp"


namespace elona
{


void label_2754()
{
    switch (evid())
    {
    case 8: label_2678(); goto label_2755_internal;
    case 14:
        if (gdata_executing_immediate_quest_type == 1009)
        {
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
        }
        if (gdata_executing_immediate_quest_type == 1006)
        {
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
        }
        if (gdata_executing_immediate_quest_type == 1008)
        {
            txtef(8);
            txt(lang(
                u8"討伐に失敗した…"s, u8"You failed to slay the target..."s));
        }
        levelexitby = 4;
        snd(49);
        chatteleport = 1;
        return;
    case 1:
        label_27492();
        flt();
        characreate(-1, 23, cdata_x(0), cdata_y(0));
        goto label_2755_internal;
    case 27:
        if (gdata_current_map == 35)
        {
            goto label_2755_internal;
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
        goto label_2755_internal;
    case 28:
        txtef(5);
        txt(lang(
            u8"…ぅっぅぅ…っぅぅっぅううううみみゃぁ！！！"s,
            u8"memememw...MEMEMEM...MEWWWWWW!"s));
        msg_halt();
        animeid = 21;
        label_1426();
        flt();
        characreate(
            -1,
            336,
            evdata1(evnum - (evnum != 0) * 1),
            evdata2(evnum - (evnum != 0) * 1));
        goto label_2755_internal;
    case 2:
        tc = findchara(34);
        label_2242();
        goto label_2755_internal;
    case 24:
        initeco = 1;
        label_2270();
        goto label_2755_internal;
    case 3:
        tc = findchara(2);
        label_2242();
        goto label_2755_internal;
    case 11:
        tc = findchara(1);
        label_2242();
        goto label_2755_internal;
    case 23:
        tc = findchara(302);
        label_2242();
        gdata(171) = 23;
        goto label_2755_internal;
    case 12:
        label_1419();
        s = lang(u8"ペットとの再会"s, u8"Reunion with your pet"s);
        file = u8"bg_re13"s;
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
        label_1896();
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
        initlv = cdata_level(0) * 2 / 3 + 1;
        novoidlv = 1;
        characreate(-1, p, cdata_x(cc), cdata_y(cc));
        label_2659();
        goto label_2755_internal;
    case 13:
        music = 80;
        label_0068();
        s = lang(u8"結婚"s, u8"Marriage"s);
        file = u8"bg_re14"s;
        buff = lang(u8"長い交際の末、遂にあなたと"s + name(marry) +
                u8"は固い絆で結ばれた。婚儀の後、あなたの元に幾つか祝儀品が届けられた。"s,
            u8"At last, you and "s + name(marry) +
                u8" are united in marriage! After the wedding ceremony, you receive some gifts."s);
        listmax = 0;
        list(0, listmax) = 1;
        listn(0, listmax) = lang(
            u8"生涯をあなたに捧げる"s, u8"Without you, life has no meaning."s);
        ++listmax;
        label_1896();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(cdata_level(marry) + 5), calcfixlv(3));
                flttypemajor = fsetchest(rnd(length(fsetchest)));
                itemcreate(-1, 0, cdata_x(0), cdata_y(0), 0);
            }
        }
        itemcreate(-1, 559, cdata_x(0), cdata_y(0), 0);
        flt();
        itemcreate(-1, 55, cdata_x(0), cdata_y(0), rnd(3) + 2);
        txt(lang(
            u8"何かが足元に転がってきた。"s,
            u8"Something is put on the ground."s));
        autosave = 1 * (gdata_current_map != 35);
        goto label_2755_internal;
    case 29:
        voidboss(0) = 300;
        voidboss(1) = 26;
        voidboss(2) = 27;
        voidboss(3) = 28;
        voidboss(4) = 29;
        voidboss(5) = 140;
        voidboss(6) = 34;
        voidboss(7) = 141;
        voidboss(8) = 143;
        voidboss(9) = 144;
        voidboss(10) = 145;
        voidboss(11) = 242;
        voidboss(12) = 25;
        voidboss(13) = 257;
        voidboss(14) = 230;
        voidboss(15) = 202;
        voidboss(16) = 37;
        voidboss(17) = 33;
        voidboss(18) = 80;
        voidboss(19) = 332;
        randomize(gdata_year + gdata_current_dungeon_level);
        c = voidboss(rnd(length(voidboss)));
        randomize();
        flt();
        fixlv = 4;
        initlv = gdata_current_dungeon_level / 4;
        characreate(-1, c, -3, 0);
        cbitmod(976, rc, 1);
        cdata_relationship(rc) = -3;
        cdata_original_relationship(rc) = -3;
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
        goto label_2755_internal;
    case 4:
    {
        int cnt = 0;
        for (;; ++cnt)
        {
            label_1735();
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
    }
        tc = rc;
        adata(20, gdata_current_map) = tc;
        cdatan(0, rc) += u8" Lv"s + cdata_level(rc);
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
        goto label_2755_internal;
    case 5:
        music = 64;
        label_0068();
        snd(51);
        flt(calcobjlv(), calcfixlv());
        flttypemajor = 54000;
        itemcreate(-1, 0, cdata_x(0), cdata_y(0), 0);
        flt();
        itemcreate(-1, 236, cdata_x(0), cdata_y(0), 0);
        flt();
        itemcreate(-1, 54, cdata_x(0), cdata_y(0), 200 + inv_number(ci) * 5);
        flt();
        itemcreate(
            -1,
            55,
            cdata_x(0),
            cdata_y(0),
            std::clamp(rnd(3) + gdata_current_dungeon_level / 10, 1, 6));
        flt();
        itemcreate(-1, 239, cdata_x(0), cdata_y(0), 0);
        inv_param2(ci) = 0;
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
        cdata_fame(0) += gdata(74);
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
        goto label_2755_internal;
    case 16:
        txt(lang(
            u8"あなたは無事に護衛の任務を終えた。"s,
            u8"You complete the escort."s));
        tc = evdata2(evnum - (evnum != 0) * 1);
        label_2242();
        rq = evdata1(evnum - (evnum != 0) * 1);
        label_2679();
        chara_vanquish(evdata2(evnum - (evnum != 0) * 1));
        goto label_2755_internal;
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
                        label_2676();
                        break;
                    }
                }
            }
        }
    }
        goto label_2755_internal;
    case 6:
        if (cdata_level(0) > 5)
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
            if (cdata_karma(0) < -30)
            {
                modkarma(0, 10);
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
        cdata_gold(0) -= cdata_gold(0) / 3;
        decfame(0, 10);
        r1 = 0;
        label_1477();
        autosave = 1 * (gdata_current_map != 35);
        goto label_2755_internal;
    case 20:
        dmghp(evdata1(evnum - (evnum != 0) * 1), 9999, -11);
        cdata_character_role(evdata1(evnum - (evnum != 0) * 1)) = 0;
        cdata_state(evdata1(evnum - (evnum != 0) * 1)) = 0;
        flt();
        itemcreate(
            -1,
            55,
            cdata_x(evdata1(evnum - (evnum != 0) * 1)),
            cdata_y(evdata1(evnum - (evnum != 0) * 1)),
            4);
        gdata_pael_and_her_mom = 1001;
        tc = findchara(221);
        if (tc != 0)
        {
            if (cdata_state(tc) == 1)
            {
                txtef(4);
                txt(lang(
                    u8"パエル「おかあさんーー！！」"s,
                    cnvtalk(u8"M-mom...!!"s)));
                cdata_relationship(tc) = -3;
                cdata_hate(tc) = 1000;
                cdata_enemy_id(tc) = 0;
            }
        }
        goto label_2755_internal;
    case 7:
        label_1444();
        press();
        screenupdate = -1;
        label_1417();
        goto label_2755_internal;
    case 10: label_2673(); goto label_2755_internal;
    case 19:
        txtef(6);
        txt(""s + usermsg);
        goto label_2755_internal;
    case 25:
        --gdata_number_of_waiting_guests;
        if (get_freechara() == -1)
        {
            txt(lang(
                u8"ゲストは行方不明になった。"s, u8"The guest lost his way."s));
            goto label_2755_internal;
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
                    if (cdata_state(i) == 3)
                    {
                        if (cbit(969, i) == 0)
                        {
                            cdata_current_map(i) != gdata_current_map;
                            if (cdata_relationship(i) >= 0)
                            {
                                if (rnd(25) < p)
                                {
                                    break;
                                }
                                if (tc == 0)
                                {
                                    tc = i;
                                    ++p;
                                    if (cdata_impression(tc) < 25)
                                    {
                                        if (rnd(12) == 0)
                                        {
                                            break;
                                        }
                                    }
                                    if (cdata_impression(tc) < 0)
                                    {
                                        if (rnd(4))
                                        {
                                            break;
                                        }
                                    }
                                    continue;
                                }
                                if (cdata_impression(cnt) < cdata_impression(i))
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
                goto label_2755_internal;
            }
            cdata_state(tc) = 1;
            rc = tc;
            cxinit = cdata_x(0);
            cyinit = cdata_y(0);
            label_1532();
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
                            cdata_character_role(rc) = 2005;
                            break;
                        }
                    }
                    if (rnd(10) == 0)
                    {
                        characreate(-1, 334, -3, 0);
                        cdata_character_role(rc) = 2006;
                        break;
                    }
                    if (rnd(10) == 0)
                    {
                        characreate(-1, 1, -3, 0);
                        cdata_character_role(rc) = 2003;
                        cdata_shop_rank(rc) =
                            std::clamp(cdata_fame(0) / 100, 20, 100);
                        break;
                    }
                    if (rnd(4) == 0)
                    {
                        characreate(-1, 9, -3, 0);
                        cdata_character_role(rc) = 2000;
                        break;
                    }
                    if (rnd(4) == 0)
                    {
                        characreate(-1, 174, -3, 0);
                        cdata_character_role(rc) = 2001;
                        break;
                    }
                    characreate(-1, 16, -3, 0);
                    cdata_character_role(rc) = 2002;
                    break;
                }
            }
            tc = rc;
            cdata_relationship(tc) = 0;
            cdata_original_relationship(tc) = 0;
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
                if (cdata_state(c) != 1)
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
                        if (inv_number(cnt) == 0)
                        {
                            continue;
                        }
                        if (inv_function(cnt) != 44)
                        {
                            continue;
                        }
                        if (c == tc)
                        {
                            if (inv_param1(cnt) == 2)
                            {
                                cell_swap(c, -1, inv_x(cnt), inv_y(cnt));
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
                        p(2) = dist(inv_x(cnt), inv_y(cnt), inv_x(i), inv_y(i));
                        if (p(2) < p(1))
                        {
                            if (map(inv_x(cnt), inv_y(cnt), 1) == 0 || c == 0
                                || c == tc)
                            {
                                p(0) = cnt;
                                p(1) = p(2);
                            }
                        }
                        if (c == 0)
                        {
                            if (inv_param1(cnt) == 1)
                            {
                                p = cnt;
                                break;
                            }
                        }
                    }
                }
                if (p != 0)
                {
                    cell_swap(c, -1, inv_x(p), inv_y(p));
                }
                cdata_direction(c) =
                    direction(cdata_x(c), cdata_y(c), cdata_x(tc), cdata_y(tc));
                if (c == 0)
                {
                    gdata(35) = cdata_direction(c);
                }
            }
        }
        label_2242();
        goto label_2755_internal;
    case 30:
        i = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt)
            {
                if (cdata_state(cnt) != 1)
                {
                    continue;
                }
                if (cdata_character_role(cnt) != 13)
                {
                    if (cdata_character_role(cnt) != 3)
                    {
                        cdata_emotion_icon(cnt) = 2010;
                        txt(lang(
                            name(cnt) + u8"「目が！目がー！！」"s,
                            name(cnt) + u8" shout"s + _s(cnt) + u8" "s
                                + cnvtalk(u8"Eyes! My eyes!"s)));
                    }
                }
            }
        }
        goto label_2755_internal;
    case 17:
        i = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
            {
                if (cdata_state(cnt) != 1)
                {
                    continue;
                }
                if (cnt == 0)
                {
                    continue;
                }
                if (cdata_character_role(cnt) != 13)
                {
                    if (cdata_character_role(cnt) != 3)
                    {
                        if (cdata_character_role(cnt) != 0
                            || cdata_relationship(cnt) == 0
                            || cdata_current_map(cnt) == gdata_current_map)
                        {
                            cdata_emotion_icon(cnt) = 2006;
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
                    if (cdata_state(cnt) != 1)
                    {
                        continue;
                    }
                    if (cdata_character_role(cnt) == 18)
                    {
                        tc = cnt;
                        break;
                    }
                }
            }
            if (tc != 0)
            {
                label_2242();
            }
        }
        goto label_2755_internal;
    case 21:
        if (mdata(6) == 1)
        {
            goto label_2755_internal;
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
        color(0, 0, 0);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (40); cnt < cnt_end; ++cnt)
            {
                if (cnt == 14)
                {
                    snd(108);
                }
                redraw(0);
                color(0, 0, 0);
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
        label_1417();
        tlocx = evdata1(evnum - (evnum != 0) * 1);
        tlocy = evdata2(evnum - (evnum != 0) * 1);
        range_ = 31;
        ele = 59;
        aniref = range_;
        animeid = 17;
        anix = tlocx;
        aniy = tlocy;
        label_1426();
        label_1419();
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
            modkarma(0, -80 + trait(162) * 60);
        }
        else
        {
            modkarma(0, -10);
        }
        goto label_2755_internal;
    case 18:
        if (mdata(6) == 1)
        {
            goto label_2755_internal;
        }
        gdata_weather = 1;
        envonly = 1;
        label_0068();
        txt(lang(u8"終末の日が訪れた。"s, u8"Let's Ragnarok!"s));
        msg_halt();
        animeid = 21;
        label_1426();
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
                    label_1419();
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
        goto label_2755_internal;
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
                    if (cdata_state(cnt) == 1)
                    {
                        cdata_relationship(cnt) = -3;
                        cdata_enemy_id(cnt) = 0;
                        cdata_hate(cnt) = 250;
                    }
                }
            }
        }
        goto label_2755_internal;
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
                    initlv = cdata_level(0);
                    characreate(-1, 215, cdata_x(0), cdata_y(0));
                }
            }
        }
        goto label_2755_internal;
    }
label_2755_internal:
    return;
}


} // namespace elona
