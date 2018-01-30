#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
void label_2251()
{
    listmax = 0;
    if (buff == ""s)
    {
        label_0176();
        customtalk(tc, 106);
        if (stat)
        {
            label_0173();
        }
        if (cdata(14, tc) > 0)
        {
            if (cdata(9, tc) != 10)
            {
                if (tc >= 16)
                {
                    if (rnd(3) == 0)
                    {
                        if (cdata(17, tc) < 100)
                        {
                            if (rnd(sdata(17, 0) + 1) > 10)
                            {
                                modimp(tc, rnd(3));
                            }
                            else
                            {
                                modimp(tc, rnd(3) * -1);
                            }
                        }
                    }
                    cdata(14, tc) -= rnd(30);
                    cdata(15, tc) = gdata(13) + gdata(12) * 24
                        + gdata(11) * 24 * 30 + gdata(10) * 24 * 30 * 12 + 8;
                }
            }
        }
    }
    if (cdata(150, tc) == 18)
    {
        if (gdata(814) > 0)
        {
            list(0, listmax) = 58;
            listn(0, listmax) =
                lang(u8"客に会う"s, u8"Yes, I'll meet the guest now."s);
            ++listmax;
            list(0, listmax) = 59;
            listn(0, listmax) =
                lang(u8"追い返す"s, u8"I don't want to meet anyone."s);
            ++listmax;
        }
    }
    if (cdata(14, tc) > 0 && chatval(1) == 0)
    {
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"話がしたい"s, u8"Let's Talk."s);
        ++listmax;
    }
    if (cdata(150, tc) >= 1000 && cdata(150, tc) < 2000
        || cdata(150, tc) == 2003)
    {
        list(0, listmax) = 10;
        listn(0, listmax) = lang(u8"買いたい"s, u8"I want to buy something."s);
        ++listmax;
        list(0, listmax) = 11;
        listn(0, listmax) = lang(u8"売りたい"s, u8"I want to sell something."s);
        ++listmax;
        if (cdata(150, tc) == 1010)
        {
            list(0, listmax) = 31;
            listn(0, listmax) = lang(u8"襲撃するよ"s, u8"Prepare to die!"s);
            ++listmax;
        }
        if (cdata(150, tc) != 1010 && cdata(150, tc) != 1009)
        {
            list(0, listmax) = 12;
            listn(0, listmax) = lang(
                u8"投資したい"s, u8"Need someone to invest in your shop?"s);
            ++listmax;
        }
    }
    if (cdata(150, tc) == 9)
    {
        list(0, listmax) = 33;
        listn(0, listmax) =
            lang(u8"仲間を呼び戻す"s, u8"Call back my allies."s);
        ++listmax;
    }
    if (cdata(150, tc) == 17)
    {
        if (get_freeally() != 0)
        {
            list(0, listmax) = 36;
            listn(0, listmax) =
                lang(u8"奴隷を買う"s, u8"I want to buy a slave."s);
            ++listmax;
        }
        list(0, listmax) = 37;
        listn(0, listmax) = lang(u8"奴隷を売る"s, u8"I want to sell a slave."s);
        ++listmax;
    }
    if (cdata(150, tc) == 22)
    {
        if (get_freeally() != 0)
        {
            list(0, listmax) = 57;
            listn(0, listmax) =
                lang(u8"馬を買う"s, u8"I want to buy a horse."s);
            ++listmax;
        }
    }
    if (tc < 16)
    {
        if (cbit(963, tc) == 0)
        {
            if (cbit(971, tc) == 0)
            {
                list(0, listmax) = 34;
                listn(0, listmax) =
                    lang(u8"街で待機しろ"s, u8"Wait at the town."s);
                ++listmax;
                if (cbit(961, tc) == 0)
                {
                    list(0, listmax) = 38;
                    listn(0, listmax) = lang(
                        u8"婚約を申し込む"s, u8"May I ask for your hand?"s);
                    ++listmax;
                }
                else
                {
                    if (gdata(90) >= 15)
                    {
                        list(0, listmax) = 39;
                        listn(0, listmax) =
                            lang(u8"遺伝子を残す"s, u8"Let's make a gene."s);
                        ++listmax;
                    }
                }
                if (cdata(23, tc) != 0)
                {
                    if (cbit(965, tc) == 0)
                    {
                        list(0, listmax) = 48;
                        listn(0, listmax) = lang(u8"黙らせる"s, u8"Shut up."s);
                        ++listmax;
                    }
                    else
                    {
                        list(0, listmax) = 48;
                        listn(0, listmax) =
                            lang(u8"喋らせる"s, u8"You can speak now."s);
                        ++listmax;
                    }
                }
                list(0, listmax) = 35;
                listn(0, listmax) =
                    lang(u8"縁を切る"s, u8"I'm going to abandon you."s);
                ++listmax;
            }
        }
    }
    if (cdata(150, tc) == 1000 || cdata(150, tc) == 1001)
    {
        list(0, listmax) = 54;
        listn(0, listmax) =
            lang(u8"矢弾の充填"s, u8"I need ammos for my weapon."s);
        ++listmax;
    }
    if (cdata(150, tc) == 1005)
    {
        list(0, listmax) = 13;
        listn(0, listmax) =
            lang(u8"食事をとる"s, u8"Bring me something to eat."s) + u8" ("s
            + calcmealvalue() + strgold + u8")"s;
        ++listmax;
        if (gdata(17) == 1 || gdata(17) == 4 || gdata(17) == 2)
        {
            list(0, listmax) = 43;
            listn(0, listmax) =
                lang(u8"シェルターに入る"s, u8"Take me to the shelter."s);
            ++listmax;
        }
    }
    if (cdata(150, tc) == 5)
    {
        list(0, listmax) = 14;
        listn(0, listmax) =
            lang(u8"鑑定したい"s, u8"I need you to identify an item."s)
            + u8" ("s + calcidentifyvalue(0) + strgold + u8")"s;
        ++listmax;
        list(0, listmax) = 15;
        listn(0, listmax) =
            lang(u8"全て鑑定してほしい"s, u8"Identify all of my stuff."s)
            + u8" ("s + calcidentifyvalue(1) + strgold + u8")"s;
        ++listmax;
        list(0, listmax) = 16;
        listn(0, listmax) = lang(u8"調査したい"s, u8"Investigate an item."s)
            + u8" ("s + calcidentifyvalue(2) + strgold + u8")"s;
        ++listmax;
    }
    if (cdata(150, tc) == 7)
    {
        list(0, listmax) = 17;
        listn(0, listmax) = lang(u8"訓練したい"s, u8"Train me."s);
        ++listmax;
        list(0, listmax) = 30;
        listn(0, listmax) =
            lang(u8"新しい能力を覚えたい"s, u8"What skills can you teach me?"s);
        ++listmax;
    }
    if (cdata(150, tc) == 8)
    {
        list(0, listmax) = 18;
        listn(0, listmax) =
            lang(u8"冒険者の情報"s, u8"Show me the list of adventurers."s);
        ++listmax;
        list(0, listmax) = 47;
        listn(0, listmax) = lang(
            u8"仲間の調査"s, u8"I want you to investigate one of my allies."s);
        ++listmax;
    }
    if (cdata(150, tc) == 12)
    {
        list(0, listmax) = 19;
        listn(0, listmax) = lang(u8"能力の復元"s, u8"Restore my attributes."s)
            + u8"("s + calcrestorecost() + strgold + u8")"s;
        ++listmax;
    }
    if (cdata(150, tc) == 13)
    {
        list(0, listmax) = 20;
        listn(0, listmax) =
            lang(u8"アイテム交換"s, u8"Are you interested in trade?"s);
        ++listmax;
        if (cbit(969, tc) == 0)
        {
            list(0, listmax) = 50;
            listn(0, listmax) =
                lang(u8"護衛を依頼する"s, u8"I want to hire you."s);
            ++listmax;
            list(0, listmax) = 51;
            listn(0, listmax) = lang(u8"仲間に誘う"s, u8"Join me!"s);
            ++listmax;
        }
    }
    if (cdata(150, tc) == 10)
    {
        list(0, listmax) = 21;
        listn(0, listmax) =
            lang(u8"試合に出る[決闘]"s, u8"I'm entering the arena. [Duel]"s);
        ++listmax;
        list(0, listmax) = 22;
        listn(0, listmax) = lang(
            u8"試合に出る[ランブル]"s, u8"I'm entering the arena. [Rumble]"s);
        ++listmax;
        list(0, listmax) = 23;
        listn(0, listmax) = lang(u8"成績を聞く"s, u8"Tell me my scores."s);
        ++listmax;
    }
    if (cdata(150, tc) == 11)
    {
        list(0, listmax) = 40;
        listn(0, listmax) =
            lang(u8"ペットデュエル"s, u8"I want to register my pet. [Duel]"s);
        ++listmax;
        list(0, listmax) = 41;
        listn(0, listmax) =
            lang(u8"チームバトル"s, u8"I want to register my team. [Team]"s);
        ++listmax;
        list(0, listmax) = 49;
        listn(0, listmax) =
            lang(u8"EXバトル"s, u8"I want to see extra teams. [Ex Battle]"s);
        ++listmax;
        list(0, listmax) = 42;
        listn(0, listmax) = lang(u8"成績を聞く"s, u8"Tell me my scores."s);
        ++listmax;
    }
    if (cdata(150, tc) == 18)
    {
        list(0, listmax) = 45;
        listn(0, listmax) = lang(
            u8"家の名前を考えてくれ"s, u8"Think of a nice name for my house."s);
        ++listmax;
    }
    if (cdata(150, tc) == 19)
    {
        list(0, listmax) = 46;
        listn(0, listmax) =
            lang(u8"免罪符を買いたい"s, u8"I want to buy an indulgence."s);
        ++listmax;
    }
    tradecheck(tc);
    if (stat)
    {
        list(0, listmax) = 20;
        listn(0, listmax) =
            lang(u8"アイテム交換"s, u8"Are you interested in trade?"s);
        ++listmax;
    }
    if (cdata(150, tc) == 14)
    {
        clientguide();
        if (stat != 0)
        {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (stat); cnt < cnt_end; ++cnt)
                {
                    list(0, listmax) = 10000 + cnt;
                    listn(0, listmax) = lang(
                        cdatan(0, rtval(cnt)) + u8"の居場所を聞く"s,
                        u8"Where is "s + cdatan(0, rtval(cnt)) + u8"?"s);
                    ++listmax;
                }
            }
        }
        if (itemfind(0, 284) != -1)
        {
            list(0, listmax) = 32;
            listn(0, listmax) = lang(
                u8"落し物の財布を届ける"s, u8"Here is a lost wallet I found."s);
            ++listmax;
        }
        else
        {
            if (itemfind(0, 283) != -1)
            {
                list(0, listmax) = 32;
                listn(0, listmax) = lang(
                    u8"落し物のカバンを届ける。"s,
                    u8"Here is a lost suitcase I found."s);
                ++listmax;
            }
        }
    }
    if (cdata(150, tc) == 21)
    {
        list(0, listmax) = 53;
        listn(0, listmax) = lang(u8"帰還したい"s, u8"I want to return."s);
        ++listmax;
    }
    if (cdata(150, tc) == 1020)
    {
        if (gdata(263) != 0)
        {
            list(0, listmax) = 55;
            listn(0, listmax) =
                lang(u8"魔法書の予約"s, u8"I want to reserve some books."s);
            ++listmax;
        }
    }
    if (cdata(257, tc) != 0 || 0)
    {
        if (gdata(20) != 35)
        {
            if (tc >= 16)
            {
                if (evid() == -1)
                {
                    list(0, listmax) = 56;
                    listn(0, listmax) = lang(
                        u8"気持ちいいことしない？"s,
                        u8"Interested in a little tail t'night?"s);
                    ++listmax;
                }
            }
        }
    }
    if (cdata(27, tc) == 335)
    {
        if (evid() == -1)
        {
            list(0, listmax) = 60;
            listn(0, listmax) = lang(u8"暗い場所に移ろう"s, u8"I'll buy you."s);
            ++listmax;
        }
    }
    if (cdata(150, tc) == 23)
    {
        list(0, listmax) = 61;
        listn(0, listmax) = lang(u8"キャラバンを雇う"s, u8"Hire caravan."s);
        ++listmax;
    }
    f = 0;
    deliver(0) = -1;
    deliver(1) = -1;
    if (gdata(22) == 1)
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (gdata(75)); cnt < cnt_end; ++cnt)
            {
                if (qdata(1, cnt) == gdata(20))
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
    }
    if (f == 1)
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (gdata(75)); cnt < cnt_end; ++cnt)
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
                        inv_getheader(0);
                        p = qdata(11, cnt);
                        deliver = cnt;
                        {
                            int cnt = invhead;
                            for (int cnt_end = cnt + (invrange); cnt < cnt_end;
                                 ++cnt)
                            {
                                if (inv(0, cnt) == 0)
                                {
                                    continue;
                                }
                                if (inv(3, cnt) == p)
                                {
                                    deliver(1) = cnt;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (qdata(8, rq) == 3)
        {
            val = 3;
            label_0184();
            label_2679();
        }
        else
        {
            if (qdata(14, rq) == 3 && qdata(8, rq) == 1)
            {
                supply = -1;
                inv_getheader(0);
                {
                    int cnt = invhead;
                    for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                    {
                        if (inv(0, cnt) == 0)
                        {
                            continue;
                        }
                        if (ibit(13, cnt))
                        {
                            continue;
                        }
                        if (qdata(3, rq) == 1003)
                        {
                            if (refitem(inv(3, cnt), 5) == 57000)
                            {
                                if (inv(25, cnt) / 1000 == qdata(12, rq))
                                {
                                    if (inv(26, cnt) == qdata(13, rq))
                                    {
                                        supply = cnt;
                                        break;
                                    }
                                }
                            }
                        }
                        if (qdata(3, rq) == 1004 || qdata(3, rq) == 1011)
                        {
                            if (inv(3, cnt) == qdata(11, rq))
                            {
                                supply = cnt;
                                break;
                            }
                        }
                    }
                }
                if (supply != -1)
                {
                    list(0, listmax) = 26;
                    listn(0, listmax) = lang(
                        itemname(supply, 1) + u8"を納入する"s,
                        u8"Here is "s + itemname(supply, 1) + u8" you asked."s);
                    ++listmax;
                }
                else
                {
                    list(0, listmax) = 24;
                    listn(0, listmax) =
                        lang(u8"依頼について"s, u8"About the work."s);
                    ++listmax;
                }
            }
            else
            {
                if (qdata(3, rq) != 0)
                {
                    list(0, listmax) = 24;
                    listn(0, listmax) =
                        lang(u8"依頼について"s, u8"About the work."s);
                    ++listmax;
                }
            }
        }
    }
    if (deliver != -1 && deliver(1) != -1)
    {
        list(0, listmax) = 25;
        listn(0, listmax) = lang(u8"配達物を渡す"s, u8"Here's your delivery."s);
        ++listmax;
    }
    if (gdata(20) == 7)
    {
        if (tc >= 57)
        {
            if (cdata(150, tc) != 0)
            {
                if (cdata(150, tc) >= 2000 && cdata(150, tc) < 3000)
                {
                }
                else
                {
                    if (evid() == -1)
                    {
                        list(0, listmax) = 44;
                        listn(0, listmax) =
                            lang(u8"解雇する"s, u8"You are fired."s);
                        ++listmax;
                    }
                }
            }
        }
    }
    if (cdata(150, tc) == 1015)
    {
        if (gdata(453) == 1000)
        {
            rc = findchara(222);
            if (rc != 0)
            {
                if (cdata(0, rc) == 1)
                {
                    list(0, listmax) = 52;
                    listn(0, listmax) = lang(
                        u8"パエルの母を売る"s, u8"I want to sell Pael's mom."s);
                    ++listmax;
                }
            }
        }
    }
    list(0, listmax) = 0;
    listn(0, listmax) = strbye;
    ++listmax;
    chatid = 0;
    chatesc = 1;
    label_2257();
    if (chatval == 10 || chatval == 11)
    {
        if (cdata(150, tc) >= 1000 && cdata(150, tc) < 2000
            || cdata(150, tc) == 2003)
        {
            if (cdata(49, 0) < -30)
            {
                if (gdata(20) != 14)
                {
                    if (gdata(20) != 7)
                    {
                        if (cbit(16, 0) == 0)
                        {
                            listmax = 0;
                            buff = lang(
                                u8"犯罪者に売る物はない"s + _yo(),
                                u8"I don't have business with criminals."s);
                            tc = tc * 1 + 0;
                            list(0, listmax) = 0;
                            listn(0, listmax) = strmore;
                            ++listmax;
                            chatesc = 1;
                            label_2257();
                            if (scenemode)
                            {
                                if (scene_cut == 1)
                                {
                                    label_2256();
                                    return;
                                }
                            }
                            label_2251();
                            return;
                        }
                    }
                }
            }
        }
    }
    if (chatval == 1)
    {
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 10)
    {
        invctrl = 11;
        invfile = cdata(153, tc);
        label_2263();
        screenupdate = -1;
        label_1419();
        cs = 0;
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 11)
    {
        invctrl = 12;
        invfile = cdata(153, tc);
        label_2263();
        cc = 0;
        screenupdate = -1;
        label_1419();
        cs = 0;
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 12)
    {
        label_2255();
        return;
    }
    if (chatval == 13)
    {
        if (cdata(30, 0) < calcmealvalue())
        {
            buff = strnogold;
            label_2251();
            return;
        }
        if (cdata(22, 0) >= 15000)
        {
            buff = lang(
                u8"腹が減っているようにはみえない"s + _yo(),
                u8"You don't seem that hungry."s);
            label_2251();
            return;
        }
        snd(12);
        cdata(30, 0) -= calcmealvalue();
        snd(18);
        cdata(22, 0) = 15000;
        buff = lang(_dozo(), u8"Here you are."s);
        txt(lang(u8"なかなか美味しかった。"s, u8"It was tasty."s),
            lang(u8"悪くない。"s, u8"Not bad at all."s),
            lang(u8"あなたは舌鼓をうった。"s, u8"You smack your lips."s));
        label_2162();
        chara_anorexia(0);
        label_2251();
        return;
    }
    if (chatval >= 14 && chatval < 17)
    {
        if (cdata(30, 0) < calcidentifyvalue(chatval - 14))
        {
            buff = strnogold;
            label_2251();
            return;
        }
        inv_getheader(0);
        p = 0;
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv(0, cnt) == 0)
                {
                    continue;
                }
                if (inv(8, cnt) < 3)
                {
                    ++p;
                }
            }
        }
        if (p == 0)
        {
            buff = lang(
                u8"鑑定するアイテムはないみたい"s + _da(),
                u8"Your items have already been identified."s);
            label_2251();
            return;
        }
        if (chatval == 15)
        {
            cdata(30, 0) -= calcidentifyvalue(1);
            inv_getheader(0);
            p(0) = 0;
            p(1) = 0;
            p(0) = 0;
            p(1) = 0;
            {
                int cnt = invhead;
                for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
                {
                    if (inv(0, cnt) == 0)
                    {
                        continue;
                    }
                    if (inv(8, cnt) < 3)
                    {
                        item_identify(cnt, -1, 250);
                        item_stack(0, cnt, 1);
                        ++p(1);
                        if (idtresult >= 3)
                        {
                            ++p;
                        }
                    }
                }
            }
            txt(lang(
                ""s + p(1) + u8"個の未判明のアイテムのうち、"s + p
                    + u8"個のアイテムが完全に判明した。"s,
                ""s + p + u8" out of "s + p(1)
                    + u8" unknown items are fully identified."s));
            buff = lang(
                u8"鑑定結果はこの通り"s + _da(),
                u8"Here, I have finished identifing your stuff."s);
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
            label_2176();
            if (efcancel == 1)
            {
                buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
                label_2251();
                return;
            }
            if (idtresult >= 3)
            {
                buff = lang(
                    u8"鑑定結果はこの通り"s + _da(),
                    u8"Here, I have finished identifing your stuff."s);
            }
            else
            {
                buff = lang(
                    u8"さらなる知識を求めるのなら、調査する必要が"s + _aru(),
                    u8"You need to investigate it to gain more knowledge."s);
            }
            cdata(30, 0) -= calcidentifyvalue(chatval - 14);
        }
        snd(12);
        label_2251();
        return;
    }
    if (chatval == 17)
    {
        csctrl = 2;
        label_2254();
        return;
    }
    if (chatval == 18)
    {
        label_1988();
        buff = lang(u8"お目当ての情報は見つかった"s + _kana(), u8"Done?"s);
        label_2251();
        return;
    }
    if (chatval == 19)
    {
        if (cdata(30, 0) < calcrestorecost())
        {
            buff = strnogold;
            label_2251();
            return;
        }
        snd(12);
        cdata(30, 0) -= calcrestorecost();
        tcbk = tc;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt)
            {
                if (cdata(0, cnt) != 1)
                {
                    continue;
                }
                tc = cnt;
                efid = 439;
                efp = 100;
                label_2176();
                txtmore();
                efid = 440;
                efp = 100;
                label_2176();
            }
        }
        tc = tcbk;
        label_2241();
        buff = lang(u8"治療が完了し"s + _ta(), u8"Done treatment. Take care!"s);
        label_2251();
        return;
    }
    if (chatval == 20)
    {
        invsubroutine = 1;
        inv_getheader(tc);
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt)
            {
                if (inv(0, cnt) != 0)
                {
                    inv(8, cnt) = 3;
                }
            }
        }
        invctrl(0) = 20;
        invctrl(1) = 0;
        label_20592();
        if (stat == 0)
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            label_2251();
            return;
        }
        buff = lang(_thanks(2), u8"Thanks!"s);
        label_2251();
        return;
    }
    if (chatval == 21 || chatval == 22)
    {
        if (gdata(183) != 0)
        {
            cell_findspace(cdata(1, 0), cdata(2, 0), 1);
            if (stat == 0)
            {
                txt(lang(
                    u8"降りるスペースがない。"s,
                    u8"There's no place to get off."s));
                label_2256();
                return;
            }
            cell_setchara(gdata(183), rtval, rtval(1));
            txt(lang(
                name(gdata(183)) + u8"から降りた。"s,
                u8"You dismount from "s + name(gdata(183)) + u8"."s));
            ride_end();
        }
        gdata(74) = calcfame(
            0,
            (220 - gdata(120) / 50) * (100 + limit(adata(22, gdata(20)), 0, 50))
                    / 100
                + 2);
        listmax = 0;
        randomize(adata(26, gdata(20)));
        if (chatval == 21)
        {
            if (adata(26, gdata(20)) > gdata(13) + gdata(12) * 24
                    + gdata(11) * 24 * 30 + gdata(10) * 24 * 30 * 12)
            {
                buff = lang(
                    u8"残念だが、今日の試合はもう終了し"s + _ta(),
                    u8"The game is over today. Come again tommorow."s);
                label_2251();
                return;
            }
            randomize(adata(24, gdata(20)));
            exrand_randomize(adata(24, gdata(20)));
            {
                int cnt = 0;
                for (int cnt_end = cnt + (50); cnt < cnt_end; ++cnt)
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
                    characreate(56, 0, -3, 0);
                    if (cmshade)
                    {
                        continue;
                    }
                    if (cdata(38, rc) < minlevel)
                    {
                        continue;
                    }
                    if (cdata(69, rc) != -3)
                    {
                        continue;
                    }
                    break;
                }
            }
            arenaop(1) = cdata(27, rc);
            buff = lang(
                u8"今日の対戦相手は"s + cdatan(0, rc) + _da() + u8"挑戦する"s
                    + _noka(1),
                u8"You got "s + cdatan(0, rc) + u8" today. What'ya say?"s);
        }
        else
        {
            if (adata(27, gdata(20)) > gdata(13) + gdata(12) * 24
                    + gdata(11) * 24 * 30 + gdata(10) * 24 * 30 * 12)
            {
                buff = lang(
                    u8"残念だが、今日の試合はもう終了し"s + _ta(),
                    u8"The game is over today. Come again tommorow."s);
                label_2251();
                return;
            }
            arenaop(0) = 1;
            arenaop(1) = (100 - gdata(120) / 100) / 2 + 1;
            buff = lang(
                u8"対戦相手はレベル"s + arenaop(1) + u8"以下の相手複数"s + _da()
                    + u8"挑戦する"s + _noka(1),
                u8"Your play is a group of monster around level "s + arenaop(1)
                    + u8". Sounds easy huh?"s);
        }
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"挑戦する"s, u8"Alright."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"I'll pass."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval != 1)
        {
            buff = lang(
                u8"用があるときは声をかけて"s + _kure(),
                u8"Alright. Call me if you changed your mind."s);
            label_2251();
            return;
        }
        if (arenaop == 0)
        {
            adata(26, gdata(20)) = gdata(13) + gdata(12) * 24
                + gdata(11) * 24 * 30 + gdata(10) * 24 * 30 * 12 + 24;
        }
        if (arenaop == 1)
        {
            adata(27, gdata(20)) = gdata(13) + gdata(12) * 24
                + gdata(11) * 24 * 30 + gdata(10) * 24 * 30 * 12 + 24;
        }
        gdata(70) = 1;
        gdata(71) = 1;
        gdata(72) = 0;
        gdata(73) = 1;
        gdata(66) = gdata(20);
        gdata(67) = gdata(22);
        gdata(68) = cdata(1, 0);
        gdata(69) = cdata(2, 0);
        gdata(64) = 6;
        gdata(65) = 1;
        levelexitby = 2;
        chatteleport = 1;
        label_2256();
        return;
    }
    if (chatval == 40 || chatval == 41 || chatval == 49)
    {
        arenaimport = 0;
        gdata(74) = calcfame(
            0,
            (220 - gdata(121) / 50) * (50 + limit(adata(23, gdata(20)), 0, 50))
                    / 100
                + 2);
        if (chatval == 49)
        {
            comctrl = 1;
            label_19432();
            if (stat == 0)
            {
                buff = lang(
                    u8"用があるときは声をかけて"s + _kure(),
                    u8"Alright. Call me if you changed your mind."s);
                label_2251();
                return;
            }
            arenaimport = 1;
        }
        listmax = 0;
        if (chatval == 40)
        {
            arenaop(0) = 0;
            arenaop(1) = 1;
            arenaop(2) = (100 - gdata(121) / 100) / 3 * 2 + 3;
            buff = lang(
                u8"一対一の戦いで、対戦相手はレベル"s + arenaop(2)
                    + u8"ぐらいの相手"s + _da() + u8"挑戦する"s + _noka(1),
                u8"The opponent is around level "s + arenaop(2)
                    + u8". Want to give it a try? "s);
        }
        if (chatval == 41)
        {
            arenaop(0) = 1;
            arenaop(1) = 2;
            arenaop(2) = (100 - gdata(121) / 100) / 2 + 1;
            arenaop(1) = rnd(7) + 2;
            buff = lang(""s + arenaop(1) +
                    u8"人同士のチームバトルで、対戦相手はレベル"s + arenaop(2) +
                    u8"以下の相手複数"s + _da() + u8"挑戦する"s + _noka(1),
                u8"It's a "s + arenaop(1) + u8" vs "s + arenaop(1) +
                    u8" match. The opponent's group is formed by the pets less than "s +
                    arenaop(2) + u8" levels. What you say?"s);
        }
        if (chatval == 49)
        {
            arenaop(0) = 1;
            arenaop(1) = 2;
            arenaop(2) = rtval(1);
            enemylv = rtval(1);
            arenaop(1) = rtval;
            buff = lang(""s + arenaop(1) +
                    u8"人同士のチームバトルで、対戦相手はレベル"s + arenaop(2) +
                    u8"以下の相手複数"s + _da() + u8"挑戦する"s + _noka(1),
                u8"It's a "s + arenaop(1) + u8" vs "s + arenaop(1) +
                    u8" match. The opponent's group is formed by the pets less than "s +
                    arenaop(2) + u8" levels. What you say?"s);
        }
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"挑戦する"s, u8"I'll send my pet."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"I'll pass."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval != 1)
        {
            buff = lang(
                u8"用があるときは声をかけて"s + _kure(),
                u8"Alright. Call me if you changed your mind."s);
            label_2251();
            return;
        }
        DIM2(followerexist, 16);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt)
            {
                followerexist(cnt) = cdata(0, cnt);
            }
        }
        allyctrl = 2;
        label_1959();
        if (stat == -1)
        {
            buff = lang(
                u8"用があるときは声をかけて"s + _kure(),
                u8"Alright. Call me if you changed your mind."s);
            label_2251();
            return;
        }
        gdata(70) = 2;
        gdata(71) = 0;
        gdata(72) = 0;
        gdata(73) = 1;
        gdata(66) = gdata(20);
        gdata(67) = gdata(22);
        gdata(68) = cdata(1, 0);
        gdata(69) = cdata(2, 0);
        gdata(64) = 40;
        gdata(65) = 1;
        levelexitby = 2;
        chatteleport = 1;
        label_2256();
        return;
    }
    if (chatval == 42)
    {
        buff = lang(u8"現在は"s + adata(23, gdata(20)) + u8"連勝中"s + _da() +
                u8"5連勝,20連勝毎にボーナスを与え"s + _ru(),
            u8"Your winning streak has reached "s + adata(23, gdata(20)) +
                u8" matchs now. Keep the audience excited. You get nice bonus at every 5th and 20th wins in a row."s);
        label_2251();
        return;
    }
    if (chatval == 23)
    {
        buff = lang(u8"現在は"s + adata(22, gdata(20)) + u8"連勝中"s + _da() +
                u8"5連勝,20連勝毎にボーナスを与え"s + _ru(),
            u8"Your winning streak has reached "s + adata(22, gdata(20)) +
                u8" matchs now. Keep the audience excited. You get nice bonus at every 5th and 20th wins in a row."s);
        label_2251();
        return;
    }
    if (chatval == 24)
    {
        label_2252();
        return;
    }
    if (chatval == 25)
    {
        label_2665();
        ti = stat;
        item_copy(deliver(1), ti);
        inv(0, ti) = 1;
        ci = ti;
        rc = tc;
        label_2663();
        rq = deliver;
        --inv(0, deliver(1));
        txt(lang(
            itemname(deliver(1), 1) + u8"を手渡した。"s,
            u8"You hand over "s + itemname(deliver(1), 1) + u8"."s));
        val = 3;
        label_0184();
        label_2679();
        label_1521();
        label_2251();
        return;
    }
    if (chatval == 26)
    {
        label_2665();
        ti = stat;
        item_copy(supply, ti);
        inv(0, ti) = 1;
        cbitmod(987, tc, 1);
        ci = ti;
        rc = tc;
        label_2663();
        --inv(0, supply);
        txt(lang(
            itemname(supply, 1) + u8"を手渡した。"s,
            u8"You hand over "s + itemname(supply, 1) + u8"."s));
        val = 3;
        label_0184();
        label_2679();
        label_1521();
        label_2251();
        return;
    }
    if (chatval == 30)
    {
        csctrl = 3;
        label_2254();
        return;
    }
    if (chatval == 31)
    {
        listmax = 0;
        buff = lang(
            _rob(2),
            u8"Oh crap. Another bandit trying to spoil my business! Form up, mercenaries."s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"神に祈れ"s, u8"Pray to your God."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) =
            lang(u8"いや、冗談です"s, u8"W-Wait! I was just kidding."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval != 1)
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            label_2251();
            return;
        }
        gohostile();
        label_2256();
        return;
    }
    if (chatval == 32)
    {
        listmax = 0;
        p = itemfind(0, 284);
        if (p == -1)
        {
            p = itemfind(0, 283);
        }
        --inv(0, p);
        if (inv(25, p) == 0)
        {
            buff = lang(u8"む…中身が空っぽ"s + _dana(2), u8"Hmm! It's empty!"s);
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"しまった…"s, u8"Oops...!"s);
            ++listmax;
            chatesc = 1;
            label_2257();
            modkarma(0, -5);
        }
        else
        {
            buff = lang(
                u8"わざわざ落し物を届けてくれた"s + _noka() + _kimi(3)
                    + u8"は市民の模範"s + _da() + _thanks(),
                u8"How nice of you to take the trouble to bring it. You're a model citizen indeed!"s);
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"当然のことだ"s, u8"It's nothing."s);
            ++listmax;
            chatesc = 1;
            label_2257();
            modkarma(0, 5);
            ++gdata(851);
            if (gdata(851) >= 4)
            {
                listmax = 0;
                buff = lang(
                    u8"む、また"s + _kimi(3) + _ka()
                        + u8"随分と頻繁に財布を見つけられるもの"s + _dana(),
                    u8"Oh, it's you again? How come you find the wallets so often?"s);
                tc = tc * 1 + 0;
                list(0, listmax) = 0;
                listn(0, listmax) = strmore;
                ++listmax;
                chatesc = 1;
                label_2257();
                if (scenemode)
                {
                    if (scene_cut == 1)
                    {
                        label_2256();
                        return;
                    }
                }
                buff = lang(u8"（…あやしい）"s, u8"(...suspicious)"s);
                list(0, listmax) = 0;
                listn(0, listmax) =
                    lang(u8"ぎくっ"s, u8"I really found it on the street!"s);
                ++listmax;
                chatesc = 1;
                label_2257();
                modkarma(0, -10);
            }
        }
        label_1521();
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 33)
    {
        allyctrl = 0;
        label_1959();
        if (stat != -1)
        {
            rc = stat;
            if (cdata(0, rc) == 1)
            {
                buff = lang(
                    u8"そいつは呼び戻す必要はないよう"s + _da(),
                    u8"Huh? You don't need to do that."s);
                label_2251();
                return;
            }
            listmax = 0;
            buff = lang(
                u8"そいつを呼び戻すには、"s + calcresurrectvalue(rc) + strgold
                    + u8"必要"s + _da(),
                u8"Alright. We had taken good care of your pet. It will cost you "s
                    + calcresurrectvalue(rc) + u8" gold pieces."s);
            if (cdata(30, 0) >= calcresurrectvalue(rc))
            {
                list(0, listmax) = 1;
                listn(0, listmax) = lang(u8"呼び戻す"s, u8"I'll pay."s);
                ++listmax;
            }
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"やめる"s, u8"Never mind."s);
            ++listmax;
            chatesc = 1;
            label_2257();
            if (chatval == 1)
            {
                snd(12);
                cdata(30, 0) -= calcresurrectvalue(rc);
                buff = lang(
                    u8"(バーテンが店の奥から"s + name(rc) + u8"を連れてきた)"s
                        + _dozo(),
                    u8"("s + name(tc) + u8" brings "s + name(rc)
                        + u8" from the stable.) There you go."s);
                label_1537();
            }
            else
            {
                buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            }
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 34)
    {
        listmax = 0;
        buff = lang(
            u8"(あなたは、"s + name(tc) + u8"に街で待っているように指示した)"s,
            u8"(You order "s + name(tc) + u8" to wait at the town.)"s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        map(cdata(1, tc), cdata(2, tc), 1) = 0;
        cdata(0, tc) = 7;
        cdata(80, tc) = 0;
        label_2256();
        return;
    }
    if (chatval == 35)
    {
        listmax = 0;
        buff = lang(
            u8"("s + name(tc)
                + u8"は悲しそうな目であなたを見ている。本当に縁を切る？)"s,
            u8"("s + name(tc) + u8" looks at you sadly. Really abandon "s
                + him(tc) + u8"? )"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"切る"s, u8"Yes."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"No."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            txt(lang(
                ""s + name(tc) + u8"と別れた…"s,
                u8"You abandoned "s + name(tc) + u8"..."s));
            map(cdata(1, tc), cdata(2, tc), 1) = 0;
            del_chara(tc);
            label_2256();
            return;
        }
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 36 || chatval == 57)
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
            {
                flt(cdata(38, 0) / 2 + 5);
                fixlv = 2;
                if (chatval == 36)
                {
                    fltn(u8"man"s);
                }
                else
                {
                    fltn(u8"horse"s);
                }
                characreate(56, 0, -3, 0);
                if (cdata(38, 56) == 0)
                {
                    chara_vanquish(56);
                    continue;
                }
                break;
            }
        }
        listmax = 0;
        buff = lang(
            u8"そう"s + _dana() + ""s + cdatan(0, 56) + u8"を"s
                + calcslavevalue(56) + strgold + u8"でどう"s + _da(1),
            u8"Okay. Let me check the stable....How about "s
                + cnven(cdatan(0, 56)) + u8" for "s + calcslavevalue(56)
                + u8" gold pieces. I'd say it's quite a bargain!"s);
        if (cdata(30, 0) >= calcslavevalue(56))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"買い取る"s, u8"I'll pay."s);
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"Never mind."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            txt(lang(
                cdatan(0, 56) + u8"を買い取った。"s,
                u8"You buy "s + cnven(cdatan(0, 56)) + u8"."s));
            snd(12);
            cdata(30, 0) -= calcslavevalue(56);
            rc = 56;
            label_2659();
            buff = lang(_thanks(2), u8"Thanks!"s);
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 37)
    {
        allyctrl = 1;
        label_1959();
        if (stat != -1)
        {
            rc = stat;
            listmax = 0;
            buff = lang(
                u8"なかなかの身体つき"s + _dana() + calcslavevalue(rc) * 2 / 3
                    + strgold + u8"でどう"s + _da(1),
                u8"Let me see....Hmmm, this one got a nice figure. I'll give you "s
                    + calcslavevalue(rc) * 2 / 3 + u8" gold pieces."s);
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"売る"s, u8"Deal."s);
            ++listmax;
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"やめる"s, u8"No way."s);
            ++listmax;
            chatesc = 1;
            label_2257();
            if (chatval == 1)
            {
                txt(lang(
                    cdatan(0, rc) + u8"を売り飛ばした。"s,
                    u8"You sell off "s + cnven(cdatan(0, rc)) + u8"."s));
                snd(11);
                cdata(30, 0) += calcslavevalue(rc) * 2 / 3;
                if (cdata(0, rc) == 1)
                {
                    map(cdata(1, rc), cdata(2, rc), 1) = 0;
                }
                if (cbit(963, rc) == 1)
                {
                    evadd(15, cdata(27, rc));
                }
                del_chara(rc);
                buff = lang(_thanks(2), u8"Thanks!"s);
            }
            else
            {
                buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            }
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 38)
    {
        if (cdata(17, tc) < 200)
        {
            buff = lang(
                u8"("s + name(tc) + u8"はやんわりと断った)"s,
                u8"("s + name(tc) + u8" gently refuses your proposal. )"s);
            label_2251();
            return;
        }
        cbitmod(961, tc, 1);
        listmax = 0;
        buff = lang(u8"はい…喜んで。"s, u8"With preasure."s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        marry = tc;
        evadd(13);
        label_2256();
        return;
    }
    if (chatval == 39)
    {
        if (gdata(20) == 30)
        {
            listmax = 0;
            buff = lang(u8"こんな場所では嫌よ"s, u8"Not here!"s);
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) = strmore;
            ++listmax;
            chatesc = 1;
            label_2257();
            if (scenemode)
            {
                if (scene_cut == 1)
                {
                    label_2256();
                    return;
                }
            }
            label_2256();
            return;
        }
        listmax = 0;
        buff = lang(u8"いやん、あなたったら…"s, u8"*blush*"s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        cbitmod(962, tc, 1);
        if (gdata(828) == 0)
        {
            gdata(98) = tc;
        }
        label_2256();
        return;
    }
    if (chatval == 43)
    {
        listmax = 0;
        buff = lang(
            u8"悪天候時はシェルターを無料で開放している"s + _nda()
                + u8"すみやかに避難して"s + _kure(),
            u8"The shelter is free to use for anyone. Here, come in."s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        gdata(66) = gdata(20);
        gdata(67) = gdata(22);
        gdata(68) = cdata(1, 0);
        gdata(69) = cdata(2, 0);
        gdata(64) = 30;
        gdata(65) = 1;
        levelexitby = 2;
        chatteleport = 1;
        snd(49);
        label_2256();
        return;
    }
    if (chatval == 44)
    {
        listmax = 0;
        buff = lang(
            u8"("s + name(tc)
                + u8"は悲しそうな目であなたを見ている。本当に縁を切る？)"s,
            u8"("s + name(tc) + u8" looks at you sadly. Really dismiss "s
                + him(tc) + u8"? )"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"切る"s, u8"Yes."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"No."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            txt(lang(
                ""s + name(tc) + u8"を解雇した… "s,
                u8"You dismiss "s + name(tc) + u8"."s));
            chara_vanquish(tc);
            calccosthire();
            label_2256();
            return;
        }
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 45)
    {
        mdatan(0) = random_title();
        if (jp)
        {
            s(0) = u8"の家"s;
            s(1) = u8"邸"s;
            s(2) = u8"城"s;
            s(3) = u8"ハーレム"s;
            s(4) = u8"の巣窟"s;
            s(5) = u8"ハウス"s;
            s(6) = u8"ホーム"s;
            s(7) = u8"の住処"s;
            s(8) = u8"宅"s;
            s(9) = u8"の隠れ家"s;
            s(10) = u8"ドーム"s;
            if (rnd(5))
            {
                mdatan(0) += s(rnd(10));
            }
        }
        else
        {
            s(0) = u8"Home"s;
            s(1) = u8"Mansion"s;
            s(2) = u8"Shack"s;
            s(3) = u8"Nest"s;
            s(4) = u8"Base"s;
            s(5) = u8"Hideout"s;
            s(6) = u8"Dome"s;
            s(7) = u8"Hut"s;
            s(8) = u8"Cabin"s;
            s(9) = u8"Hovel"s;
            s(10) = u8"Shed"s;
            if (rnd(3))
            {
                mdatan(0) += u8" "s + s(rnd(10));
            }
        }
        screenupdate = -1;
        label_1417();
        buff = lang(
            u8"そう"s + _dana() + u8"これからこの家の名前は"s + mdatan(0)
                + _da(),
            u8"Hey, I've come up a good idea! \""s + mdatan(0)
                + u8"\", doesn't it sound so charming?"s);
        label_2251();
        return;
    }
    if (chatval == 46)
    {
        if (cdata(49, 0) >= -30)
        {
            buff = lang(
                u8"その程度の罪なら自分でなんとかしなさい。"s,
                u8"You karma isn't that low. Come back after you have comitted more crimes!"s);
            label_2251();
            return;
        }
        listmax = 0;
        buff = lang(
            u8"免罪符を希望する"s + _noka(1) + calcguiltvalue() + strgold
                + u8"かかるけどいいの"s + _kana(1),
            u8"In the authority of all the saints, I will grant you an indulgence, for money of course. The price is "s
                + calcguiltvalue() + u8" gold pieces."s);
        if (cdata(30, 0) >= calcguiltvalue())
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"買う"s, u8"Deal."s);
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"The price is too high."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            snd(12);
            cdata(30, 0) -= calcguiltvalue();
            modkarma(0, (cdata(49, 0) - -30) * -1 + 1);
            buff = lang(_thanks(2), u8"Thanks!"s);
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 47)
    {
        tcchat = tc;
        allyctrl = 4;
        label_1959();
        if (stat != -1)
        {
            rc = stat;
            listmax = 0;
            buff = lang(
                u8"10000 goldかかるけどいい"s + _ka(1),
                u8"10000 gold pieces."s);
            if (cdata(30, 0) >= 10000)
            {
                list(0, listmax) = 1;
                listn(0, listmax) =
                    lang(u8"調査する"s, u8"Too expensive, but okay."s);
                ++listmax;
            }
            list(0, listmax) = 0;
            listn(0, listmax) = lang(u8"やめる"s, u8"No way!"s);
            ++listmax;
            chatesc = 1;
            label_2257();
            if (chatval == 1)
            {
                snd(12);
                cdata(30, 0) -= 10000;
                cc = rc;
                csctrl = 4;
                snd(26);
                label_20332();
                cc = 0;
                label_2241();
                buff = "";
            }
            else
            {
                buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            }
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        tc = tcchat;
        label_2251();
        return;
    }
    if (chatval == 48)
    {
        if (cbit(965, tc) == 0)
        {
            cbitmod(965, tc, 1);
            buff = u8"("s
                + lang((name(tc) + u8"はしゅんとなった…"s),
                       (name(tc) + u8" stops talking..."s))
                + u8")"s;
        }
        else
        {
            buff = u8"("s
                + lang((name(tc) + u8"はあなたに抱きついた"s),
                       (name(tc) + u8" hugs you."s))
                + u8")"s;
            cbitmod(965, tc, 0);
        }
        chatid = -1;
        label_2251();
        return;
    }
    if (chatval == 50)
    {
        buff = lang(
            _ore(3) + u8"の剣が必要な"s + _noka(1) + u8"そう"s + _dana(3)
                + u8"、"s + calchireadv(tc) + strgold
                + u8"払うならば、7日間護衛を引き受け"s + _ru(),
            u8"I will take the job for "s + calchireadv(tc)
                + u8" gold pieces, for seven day."s);
        if (cdata(30, 0) >= calchireadv(tc))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"頼む"s, u8"Sounds fair enough."s);
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"Some other time."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            snd(12);
            cdata(30, 0) -= calchireadv(tc);
            cdata(9, tc) = 10;
            cbitmod(969, tc, 1);
            cdata(84, tc) = gdata(13) + gdata(12) * 24 + gdata(11) * 24 * 30
                + gdata(10) * 24 * 30 * 12 + 168;
            ++cdata(85, tc);
            snd(64);
            txtef(5);
            txt(lang(
                name(tc) + u8"を雇った。"s,
                u8"You hired "s + name(tc) + u8"."s));
            buff = lang(_thanks(2), u8"Thanks!"s);
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 51)
    {
        if (cdata(38, 0) * 3 / 2 + 10 < cdata(38, tc))
        {
            buff = lang(
                _kimi(3) + u8"の仲間になれと？あまりにも力の差がありすぎる"s
                    + _na(),
                u8"Huh? You are no match for me."s);
            label_2251();
            return;
        }
        if (cdata(17, tc) >= 200 && cdata(85, tc) > 2)
        {
            listmax = 0;
            buff = lang(
                _kimi(3) + u8"となら上手くやっていけそう"s + _da() + _yoro(2),
                u8"Sure, I guess you and I can make a good team."s);
            tc = tc * 1 + 0;
            list(0, listmax) = 0;
            listn(0, listmax) = strmore;
            ++listmax;
            chatesc = 1;
            label_2257();
            if (scenemode)
            {
                if (scene_cut == 1)
                {
                    label_2256();
                    return;
                }
            }
            f = get_freeally();
            if (f == 0)
            {
                buff = lang(
                    u8"これ以上仲間を連れて行けないよう"s + _da()
                        + u8"人数を調整してまた来て"s + _kure(),
                    u8"It seems your party is already full. Come see me again when you're ready."s);
                label_2251();
                return;
            }
            rc = tc;
            label_2659();
            cdata(150, rc) = 0;
            cdata(80, rc) = 0;
            cdata(17, tc) = 100;
            rc = oc;
            label_2661();
            label_2256();
            return;
        }
        buff = lang(
            _kimi(3) + u8"の仲間になれと？悪い"s + _ga(3) + u8"お断り"s + _da(),
            u8"Huh? What made you think I'd want to join you? I don't even know you well."s);
        label_2251();
        return;
    }
    if (chatval == 52)
    {
        listmax = 0;
        buff = lang(
            u8"ほほう、モンスターの顔をした人間か。見世物としてなかなかいけそうだ。金貨50000枚で買い取ろう。"s,
            u8"Look what we have! A woman who got a monster's face. It'll be a good show. Wanna sell me for 50000 gold coins?"s);
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"売る"s, u8"Sure, take her."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"You cold bastard."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            txt(lang(u8"パエルの母親を売った…"s, u8"You sell Pael's mon..."s));
            modkarma(0, -20);
            snd(11);
            cdata(30, 0) += 50000;
            gdata(453) = 1002;
            rc = findchara(222);
            cdata(202, rc) = 3;
            cdata(9, rc) = 0;
            cdata(171, rc) = 48;
            cdata(172, rc) = 18;
            cell_movechara(rc, 48, 18);
            buff = lang(_thanks(2), u8"Thanks!"s);
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 53)
    {
        listmax = 0;
        buff = lang(
            u8"ここからふもとに下りるのは不便だから、ボランティアで帰還サービスをやってい"s
                + _ru() + _kimi(3) + u8"も帰還サービスを希望"s + _kana(),
            u8"I'm practicing a spell of return. Would you like to take my service?"s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        label_2081();
        label_2256();
        return;
    }
    if (chatval == 54)
    {
        if (calccostreload(0) == 0)
        {
            buff = lang(
                u8"充填する必要はないみたい"s + _da(),
                u8"Reload what? You don't have any ammo in your inventory."s);
            label_2251();
            return;
        }
        buff = lang(
            u8"そう"s + _dana(3) + u8"、全ての矢弾を補充すると"s
                + calccostreload(0) + strgold + _da(),
            u8"Sure, let me check what type of ammos you need....Okay, reloading all of your ammos will cost "s
                + calccostreload(0) + u8" gold pieces."s);
        if (cdata(30, 0) >= calccostreload(0))
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"頼む"s, u8"Alright."s);
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"Another time."s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (chatval == 1)
        {
            snd(12);
            cdata(30, 0) -= calccostreload(0);
            p = calccostreload(0, 1);
            buff = lang(_thanks(2), u8"Thanks!"s);
        }
        else
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
        }
        label_2251();
        return;
    }
    if (chatval == 55)
    {
        screenupdate = -1;
        label_1419();
        invctrl = 0;
        label_1984();
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 56)
    {
        list(0, listmax) = 1;
        listn(0, listmax) = lang(u8"はじめる"s, u8"Let's do it."s);
        ++listmax;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"W-wai.t.."s);
        ++listmax;
        buff = lang(
            u8"なかなかの体つき"s + _dana() + u8"よし、買"s + _u(2),
            u8"You are...quite attractive. I'll buy you."s);
        label_2257();
        if (chatval != 1)
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            label_2251();
            return;
        }
        listmax = 0;
        buff = lang(u8"いく"s + _yo(2), u8"Okay, no turning back now!"s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"うふふ"s, u8"Come on!"s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        label_2147();
        label_2256();
        return;
    }
    if (chatval == 58)
    {
        evadd(25);
        label_2256();
        return;
    }
    if (chatval == 59)
    {
        --gdata(814);
        listmax = 0;
        buff = lang(u8"追い返す"s + _yo(), u8"Alright."s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = strmore;
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        buff = "";
        label_2251();
        return;
    }
    if (chatval == 60)
    {
        sexvalue = sdata(17, tc) * 25 + 100 + cdata(34, 0) / 10;
        if (cdata(30, 0) >= sexvalue)
        {
            list(0, listmax) = 1;
            listn(0, listmax) = lang(u8"はじめる"s, u8"Let's do it."s);
            ++listmax;
        }
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"やめる"s, u8"W-wai.t.."s);
        ++listmax;
        buff = lang(
            u8"そう"s + _dana() + u8"金貨"s + sexvalue + u8"枚を前払いで"s
                + _kure(),
            u8"Okay sweetie, I need "s + sexvalue
                + u8" gold pieces in front."s);
        label_2257();
        if (chatval != 1)
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            label_2251();
            return;
        }
        snd(12);
        cdata(30, cc) -= sexvalue;
        cdata(30, tc) += sexvalue;
        listmax = 0;
        buff = lang(u8"いく"s + _yo(2), u8"Okay, no turning back now!"s);
        tc = tc * 1 + 0;
        list(0, listmax) = 0;
        listn(0, listmax) = lang(u8"うふふ"s, u8"Come on!"s);
        ++listmax;
        chatesc = 1;
        label_2257();
        if (scenemode)
        {
            if (scene_cut == 1)
            {
                label_2256();
                return;
            }
        }
        cc = tc;
        tc = 0;
        label_2147();
        cc = 0;
        label_2256();
        return;
    }
    if (chatval == 61)
    {
        if (gdata(20) == 43)
        {
            p(0) = 45;
            p(1) = 48;
            p(2) = 0;
        }
        if (gdata(20) == 45)
        {
            p(0) = 43;
            p(1) = 48;
            p(2) = 0;
        }
        if (gdata(20) == 48)
        {
            p(0) = 43;
            p(1) = 45;
            p(2) = 0;
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
            {
                if (p(cnt) == 0)
                {
                    list(0, listmax) = 0;
                    listn(0, listmax) = lang(u8"やめる"s, u8"Never mind!"s);
                    ++listmax;
                    break;
                }
                list(0, listmax) = p(cnt);
                listn(0, listmax) = mapname(p(cnt));
                ++listmax;
            }
        }
        buff = lang(u8"つぇｔ"s, u8"tset"s);
        label_2257();
        if (chatval <= 0)
        {
            buff = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
            label_2251();
            return;
        }
        gdata(64) = adata(30, chatval);
        gdata(65) = 1;
        levelexitby = 4;
        gdata(79) = 1;
        gdata(850) = adata(30, chatval);
        gdata(5) = adata(1, chatval);
        gdata(6) = adata(2, chatval);
        fixtransfermap = 1;
        chatteleport = 1;
        label_2256();
        return;
    }
    if (chatval >= 10000)
    {
        clientguide();
        rc = rtval(chatval - 10000);
        p = direction(cdata(1, 0), cdata(2, 0), cdata(1, rc), cdata(2, rc));
        if (p == 1)
        {
            s = lang(u8"西"s, u8"west"s);
        }
        else
        {
            if (p == 2)
            {
                s = lang(u8"東"s, u8"east"s);
            }
            else
            {
                if (p == 3)
                {
                    s = lang(u8"北"s, u8"north"s);
                }
                else
                {
                    s = lang(u8"南"s, u8"south"s);
                }
            }
        }
        p = dist(cdata(1, 0), cdata(2, 0), cdata(1, rc), cdata(2, rc));
        {
            int cnt = 0;
            for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt)
            {
                if (rc == tc)
                {
                    s = lang(u8"冷やかし"s + _ka(1), u8"You kidding? "s);
                    break;
                }
                if (cdata(0, rc) != 1)
                {
                    s = lang(
                        u8"奴なら今は死んでいる"s + _yo(2),
                        u8"Oh forget it, dead for now."s);
                    break;
                }
                if (p < 6)
                {
                    s = lang(
                        cdatan(0, rc) + u8"ならすぐ近くにいる"s + _yo() + s
                            + u8"の方を向いてごらん。"s,
                        u8"Oh look carefully before asking, just turn "s + s
                            + u8"."s);
                    break;
                }
                if (p < 12)
                {
                    s = lang(
                        u8"ちょっと前に"s + s + u8"の方で見かけた"s + _yo(),
                        u8"I saw "s + cdatan(0, rc)
                            + u8" just a minute ago. Try "s + s + u8"."s);
                    break;
                }
                if (p < 20)
                {
                    s = lang(
                        cdatan(0, rc) + u8"なら"s + s
                            + u8"の方角を探してごらん。"s,
                        u8"Walk to "s + s + u8" for a while, you'll find "s
                            + cdatan(0, rc) + u8"."s);
                    break;
                }
                if (p < 35)
                {
                    s = lang(
                        cdatan(0, rc) + u8"に会いたいのなら、"s + s
                            + u8"にかなり歩く必要があ"s + _ru(),
                        u8"If you want to meet "s + cdatan(0, rc)
                            + u8", you have to considerably walk to "s + s
                            + u8"."s);
                    break;
                }
                s = lang(
                    cdatan(0, rc) + _ka(3) + u8"、ここから"s + s
                        + u8"の物凄く離れた場所にいるはず"s + _da(),
                    u8"You need to walk long way to "s + s + u8" to meet "s
                        + cdatan(0, rc) + u8"."s);
                break;
            }
        }
        buff = s;
        label_2251();
        return;
    }
    if (evid() == 11)
    {
        levelexitby = 4;
        chatteleport = 1;
        snd(49);
    }
    label_2256();
    return;
}


} // namespace elona
