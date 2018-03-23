#include "ability.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "macro.hpp"
#include "variables.hpp"


namespace elona
{


void pc_turn(bool = true);


int ctrl_inventory()
{
    int mainweapon = 0;
    int countequip = 0;
    int showmoney = 0;
    int citrade = 0;
    int dropcontinue = 0;
label_20591:
    if (invctrl == 22)
    {
        if (invctrl(1) == 1)
        {
            remove_card_and_figures();
        }
    }
    if (menucycle == 1)
    {
        if (mdata(6) == 1)
        {
            p = 0;
            for (int cnt = 0; cnt < 12; ++cnt)
            {
                if (cycle(cnt, 1) == -1)
                {
                    break;
                }
                if (cycle(cnt, 1) == invctrl)
                {
                    p = 1;
                    break;
                }
            }
            if (p == 0)
            {
                invctrl = cycle(0, 1);
            }
        }
    }
    invmark(11) = 0;
    invmark(12) = 0;
    page = 0;
    pagesize = 16;
    listmax = 0;
    cs = invmark(invctrl) % 1000;
    page = invmark(invctrl) / 1000;
    cs_bk = -1;
    cc = 0;
    page_load();
    mainweapon = -1;
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        if (cnt == 0)
        {
            p = -1;
            if (invctrl == 2 || invctrl == 6 || invctrl == 10 || invctrl == 12
                || invctrl == 16 || invctrl == 20 || invctrl == 21
                || invctrl == 23 || invctrl == 24 || invctrl == 25)
            {
                continue;
            }
        }
        if (cnt == 1)
        {
            p = cc;
            if (invctrl == 20 || invctrl == 25)
            {
                p = tc;
            }
            if (invctrl == 27)
            {
                p = map(tlocx, tlocy, 1) - 1;
                if (p == 0 || p == -1)
                {
                    continue;
                }
            }
            if (invctrl == 3 || invctrl == 11 || invctrl == 22 || invctrl == 28)
            {
                break;
            }
        }
        int cnt2 = cnt;
        if (invctrl != 1 && invctrl != 5 && invctrl != 13 && invctrl != 14
            && invctrl != 18 && invctrl != 20 && invctrl != 23 && invctrl != 25
            && invctrl != 27)
        {
            countequip = 0;
        }
        else
        {
            countequip = 1;
        }
        if (invctrl == 11 || invctrl == 12 || invctrl == 25 || invctrl == 27)
        {
            showmoney = 1;
        }
        else
        {
            showmoney = 0;
        }
        for (const auto& cnt : items(p))
        {
            if (inv[cnt].number <= 0)
            {
                inv[cnt].number = 0;
                continue;
            }
            if (inv[cnt].id == 488)
            {
                inv[cnt].function = 9;
            }
            if (inv[cnt].id == 504)
            {
                inv[cnt].function = 38;
            }
            if (inv[cnt].id >= 800 || inv[cnt].id < 0)
            {
                dialog(
                    u8"Invalid Item Id found. Item No:"s + cnt + u8", Id:"s
                    + inv[cnt].id
                    + u8" has been removed from your inventory."s);
                inv[cnt].number = 0;
                inv[cnt].id = 0;
                continue;
            }
            if (mdata(6) == 1)
            {
                if (invctrl == 7)
                {
                    if (the_item_db[inv[cnt].id]->subcategory != 53100
                        && inv[cnt].id != 621)
                    {
                        continue;
                    }
                }
            }
            if (cnt2 == 0)
            {
                if (invctrl == 27)
                {
                    if (inv[cnt].position.x != tlocx
                        || inv[cnt].position.y != tlocy)
                    {
                        continue;
                    }
                }
                else if (invctrl != 11 && invctrl != 22 && invctrl != 28)
                {
                    if (inv[cnt].position.x != cdata[cc].position.x
                        || inv[cnt].position.y != cdata[cc].position.y)
                    {
                        continue;
                    }
                }
            }
            item_checkknown(cnt);
            reftype = the_item_db[inv[cnt].id]->category;
            if (inv[cnt].own_state == 5)
            {
                if (ibit(16, cnt) == 0 || invctrl != 14)
                {
                    if (invctrl != 1)
                    {
                        continue;
                    }
                }
            }
            if (countequip == 0)
            {
                if (inv[cnt].body_part != 0)
                {
                    continue;
                }
            }
            if (inv[cnt].body_part != 0)
            {
                if (mainweapon == -1)
                {
                    if (reftype == 10000)
                    {
                        mainweapon = cnt;
                    }
                }
            }
            if (invctrl == 5)
            {
                if (reftype != 57000 && reftype != 91000
                    && inv[cnt].material != 35)
                {
                    continue;
                }
            }
            if (invctrl == 6)
            {
                if (iequiploc(cnt) != cdata_body_part(cc, body) / 10000)
                {
                    continue;
                }
            }
            if (invctrl == 7)
            {
                if (the_item_db[inv[cnt].id]->is_readable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 8)
            {
                if (the_item_db[inv[cnt].id]->is_drinkable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 9)
            {
                if (the_item_db[inv[cnt].id]->is_zappable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 11)
            {
                if (inv[cnt].id == 54 || inv[cnt].id == 55)
                {
                    continue;
                }
            }
            if (invctrl == 11 || invctrl == 12)
            {
                if (shoptrade)
                {
                    if (inv[cnt].weight >= 0)
                    {
                        continue;
                    }
                    else if (reftype != 92000)
                    {
                        continue;
                    }
                }
                else if (inv[cnt].weight < 0)
                {
                    if (reftype == 92000)
                    {
                        continue;
                    }
                }
                if (inv[cnt].value <= 1)
                {
                    continue;
                }
                if (ibit(5, cnt) == 1)
                {
                    continue;
                }
                if (inv[cnt].param3 < 0)
                {
                    continue;
                }
                if (inv[cnt].quality == 6)
                {
                    continue;
                }
            }
            if (invctrl == 13)
            {
                if (inv[cnt].identification_state >= 3)
                {
                    continue;
                }
            }
            if (invctrl == 14)
            {
                if (inv[cnt].function == 0
                    && the_item_db[inv[cnt].id]->is_usable == 0
                    && ibit(10, cnt) == 0)
                {
                    continue;
                }
            }
            if (invctrl == 15)
            {
                if (reftype != 72000)
                {
                    continue;
                }
            }
            if (invctrl == 16)
            {
                if (reftype != 57000)
                {
                    continue;
                }
                else if (inv[cnt].param2 != 0)
                {
                    continue;
                }
            }
            if (invctrl == 17)
            {
                if (reftype != 52000 && inv[cnt].id != 617)
                {
                    continue;
                }
            }
            if (invctrl == 18)
            {
                if (inv[cidip].id == 617)
                {
                    if (inv[cnt].id != 342)
                    {
                        continue;
                    }
                }
                if (cidip == cnt || inv[cnt].id == 516)
                {
                    continue;
                }
            }
            if (invctrl == 19)
            {
                dbid = inv[cnt].id;
                dbspec = 12;
                int is_offerable = access_item_db(16);
                if (is_offerable == 0)
                {
                    continue;
                }
            }
            if (invctrl == 20)
            {
                if (inv[cnt].id == 54 || inv[cnt].id == 55)
                {
                    continue;
                }
            }
            if (invctrl == 21)
            {
                if (calcitemvalue(cnt, 0) * inv[cnt].number
                    < calcitemvalue(citrade, 0) * inv[citrade].number / 2 * 3)
                {
                    continue;
                }
                if (ibit(9, cnt))
                {
                    continue;
                }
            }
            if (invctrl == 23)
            {
                if (invctrl(1) == 0)
                {
                    if (reftype >= 50000 && reftype != 60000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 1)
                {
                    if (reftype != 10000 && reftype != 24000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 2)
                {
                    if (reftype < 12000 || reftype >= 24000)
                    {
                        if (reftype < 30000 || reftype >= 50000)
                        {
                            continue;
                        }
                    }
                }
                if (invctrl(1) == 3)
                {
                    if (ibit(4, cnt) == 0)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 4)
                {
                    if (inv[cnt].body_part != 0)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (reftype != 56000)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 6)
                {
                    if (inv[cnt].weight <= 0 || inv[cnt].id == 641)
                    {
                        continue;
                    }
                }
                if (invctrl(1) == 7)
                {
                    if (inv[cnt].quality >= 4 || reftype >= 50000)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 0)
                {
                    if (gdata_current_map == 36)
                    {
                        if (inv[cnt].id != 687 || inv[cnt].param2 == 0)
                        {
                            continue;
                        }
                    }
                    else if (inv[cnt].own_state != 4)
                    {
                        continue;
                    }
                }
                else if (inv[cnt].own_state == 4)
                {
                    continue;
                }
                if (invctrl(1) == 2)
                {
                    if (inv[cnt].id != 615)
                    {
                        continue;
                    }
                }
                if (reftype == 72000)
                {
                    continue;
                }
                if (invctrl(1) == 3)
                {
                    if (reftype != 57000)
                    {
                        continue;
                    }
                }
            }
            else if (inv[cnt].own_state == 4)
            {
                if (invctrl != 1 && invctrl != 2 && invctrl != 3
                    && invctrl != 5)
                {
                    continue;
                }
            }
            if (invctrl == 26)
            {
                if (reftype != 52000 && inv[cnt].id != 578 && inv[cnt].id != 685
                    && inv[cnt].id != 699 && inv[cnt].id != 772)
                {
                    continue;
                }
                if (inv[cnt].id == 685)
                {
                    if (inv[cnt].subname != 0)
                    {
                        continue;
                    }
                }
            }
            if (invctrl == 27)
            {
                if (cnt2 == 0)
                {
                    if (inv[cnt].own_state != 1)
                    {
                        continue;
                    }
                }
            }
            list(0, listmax) = cnt;
            list(1, listmax) = reftype * 1000 + inv[cnt].id;
            if (inv[cnt].id == 544)
            {
                list(1, listmax) += inv[cnt].param1 + 900;
            }
            if (invctrl == 1 || invctrl == 13)
            {
                if (inv[cnt].body_part != 0)
                {
                    list(1, listmax) -= 99999000;
                }
            }
            if (cnt2 == 0)
            {
                list(1, listmax) -= 199998000;
            }
            if (invctrl == 28)
            {
                list(1, listmax) = calcmedalvalue(cnt);
            }
            ++listmax;
        }
    }
    f = 0;
    if (listmax == 0)
    {
        if (invctrl == 21)
        {
            txt(lang(
                itemname(citrade) + u8"に見合う物を所持していない。"s,
                u8"You don't have stuff that match "s + itemname(citrade)
                    + u8"."s));
            f = 1;
        }
        if (invctrl == 27)
        {
            if (tc != 0)
            {
                txt(lang(
                    name(tc) + u8"は盗めるものを所持していない。"s,
                    name(tc) + u8" has nothing to steal."s));
                f = 1;
            }
            else
            {
                txt(lang(
                    u8"そこに盗めるものはない。"s,
                    u8"There's nothing to steal."s));
                f = 1;
            }
        }
    }
    if (invctrl == 19)
    {
        int stat = item_find(60002, 2);
        if (stat == -1)
        {
            ++msgdup;
            txt(lang(u8"ここには祭壇がない。"s, u8"There's no altar here."s));
            f = 1;
        }
    }
    if (invctrl == 27)
    {
        if (tc > 0)
        {
            if (cdata[tc].relationship == 10)
            {
                txt(lang(
                    u8"仲間からは盗みたくない。"s,
                    u8"You don't want to rob your ally."s));
                f = 1;
            }
        }
    }
    if (invctrl == 24)
    {
        if (invctrl(1) == 0)
        {
            if (gdata_current_map == 36)
            {
                if (gdata_mages_guild_quota <= 0)
                {
                    txt(lang(
                        u8"現在魔術士ギルドのノルマはない。"s,
                        u8"You have no quota for Mages Guild."s));
                    f = 1;
                }
            }
        }
    }
    if (f == 1)
    {
        if (invsubroutine == 1)
        {
            invsubroutine = 0;
            return 0;
        }
        update_screen();
        pc_turn(false);
    }
    sort_list_by_column1();
    if (invctrl == 3)
    {
        if (listmax == 0)
        {
            turn_end();
            return 0;
        }
    }
    if (returnfromidentify == 0)
    {
        std::string valn;
        if (invctrl == 18)
        {
            valn = itemname(cidip, 1);
        }
        else if (invctrl == 21)
        {
            valn = itemname(citrade);
        }
        s(0) = "";
        s(1) = lang(u8"どのアイテムを調べる？ "s, u8"Examine what? "s);
        s(2) = lang(u8"どのアイテムを置く？ "s, u8"Drop what? "s);
        s(3) = lang(
            u8"どのアイテムを拾う？ "s,
            u8"Which item do you want to pick up? "s);
        s(4) = lang(u8"何を装備する？"s, u8"Equip what?"s);
        s(5) = lang(u8"何を食べよう？ "s, u8"Eat what? "s);
        s(6) = "";
        s(7) = lang(u8"どれを読む？ "s, u8"Read what? "s);
        s(8) = lang(u8"どれを飲む？ "s, u8"Drink what? "s);
        s(9) = lang(u8"どれを振る？ "s, u8"Zap what? "s);
        s(10) = lang(u8"どれを渡す？ "s, u8"Which item do you want to give? "s);
        s(11) = lang(u8"どれを購入する？ "s, u8"What do you want to buy? "s);
        s(12) = lang(u8"どれを売却する？ "s, u8"What do you want to sell? "s);
        s(13) = lang(
            u8"どのアイテムを鑑定する？ "s,
            u8"Which item do you want to identify? "s);
        s(14) = lang(u8"どのアイテムを使用する？ "s, u8"Use what? "s);
        s(15) = lang(u8"どれを開ける？ "s, u8"Open what? "s);
        s(16) = lang(u8"何を料理する？ "s, u8"Cook what? "s);
        s(17) = lang(u8"何を混ぜる？ "s, u8"Blend what? "s);
        s(18) = lang(
            u8"何に混ぜる？("s + valn + u8"の効果を適用するアイテムを選択) "s,
            u8"Which item do you want to apply the effect of "s + valn
                + u8"? "s);
        s(19) = lang(
            u8"何を神に捧げる？ "s,
            u8"What do you want to offer to your God? "s);
        s(20) =
            lang(u8"何を交換する？ "s, u8"Which item do you want to trade? "s);
        s(21) = lang(
            valn + u8"の代わりに何を提示する？ "s,
            u8"What do you offer for "s + valn + u8"? "s);
        s(22) = lang(u8"何を取る？ "s, u8"Take what? "s);
        s(23) = lang(u8"何を対象にする？ "s, u8"Target what? "s);
        s(24) = lang(u8"何を入れる？ "s, u8"Put what? "s);
        s(25) = lang(u8"何をもらう？ "s, u8"Which item do you want to take? "s);
        s(26) = lang(u8"何を投げる？ "s, u8"Throw what? "s);
        s(27) = lang(u8"何を盗む？ "s, u8"Steal what? "s);
        s(28) = lang(u8"何と交換する？ "s, u8"Trade what? "s);
        s(29) =
            lang(u8"何を予約する？"s, u8"Which item do you want to reserve? "s);
        if (s(invctrl) != ""s)
        {
            txtnew();
        }
        if (invsc == 0)
        {
            txt(s(invctrl));
        }
        if (invctrl == 28)
        {
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                p = inv[stat].number;
            }
            else
            {
                p = 0;
            }
            txt(lang(
                u8"(持っているメダル: "s + p + u8"枚)"s,
                u8"(Coins: "s + p + u8")"s));
        }
        if (invctrl == 24)
        {
            if (invctrl(1) == 0)
            {
                if (gdata_current_map == 36)
                {
                    txt(lang(
                        u8"ノルマ残り: "s + gdata_mages_guild_quota + u8"GP"s,
                        ""s + gdata_mages_guild_quota
                            + u8"guild points are needed to gain a rank."s));
                }
            }
        }
    }
    gsel(3);
    pos(960, 96);
    picload(fs::u8path(u8"./graphic/deco_inv.bmp"), 1);
    gsel(0);
    if (returnfromidentify == 0)
    {
        windowshadow = 1;
    }
    returnfromidentify = 0;
label_2060_internal:
    if (invsc != 0)
    {
        f = 0;
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            p = list(0, cnt);
            if (inv[p].id == invsc)
            {
                ci = p;
                f = 1;
                if (ibit(4, ci))
                {
                    if (inv[ci].count <= 0)
                    {
                        continue;
                    }
                }
                break;
            }
        }
        cc = 0;
        if (f == 0)
        {
            int stat = inv_find(invsc, 0);
            if (stat == -1)
            {
                txt(lang(
                    u8"そのアイテムは存在しない。"s,
                    u8"The item doesn't exist."s));
            }
            else
            {
                txtnew();
                txt(lang(
                    u8"その行為は、ワールドマップにいる間はできない。"s,
                    u8"You can't do that while you're in a global area."s));
            }
            invsc = 0;
            update_screen();
            pc_turn(false);
        }
        invsc = 0;
        if (mdata(6) == 1)
        {
            if (invctrl == 9 || invctrl == 15 || invctrl == 26)
            {
                txtnew();
                txt(lang(
                    u8"その行為は、ワールドマップにいる間はできない。"s,
                    u8"You can't do that while you're in a global area."s));
                update_screen();
                pc_turn(false);
            }
        }
        goto label_2062_internal;
    }
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
    if (menucycle == 1)
    {
        font(lang(cfg_font1, cfg_font2), 12 + sizefix - en * 2, 0);
        y = 34;
        x = windoww - 650 + 156;
        window2(x, y, 475, 22, 5, 5);
        pos(x - 28, y - 8);
        gcopy(3, 64, 288, 50, 32);
        if (dropcontinue)
        {
            i = 4;
        }
        else if (invally == 1)
        {
            i = 2;
        }
        else if (invcontainer)
        {
            i = 3;
        }
        else if (mdata(6) == 1)
        {
            i = 1;
        }
        else
        {
            i = 0;
        }
        for (int cnt = 0; cnt < 12; ++cnt)
        {
            if (cycle(cnt, i) == -1)
            {
                break;
            }
            p = cycle(cnt, i);
            pos(x + cnt * 44 + 20, y - 24);
            gcopy(3, 288 + invicon(p) * 48, 48, 48, 48);
            if (invctrl == p)
            {
                gmode(5, -1, -1, 70);
                pos(x + cnt * 44 + 20, y - 24);
                gcopy(3, 288 + invicon(p) * 48, 48, 48, 48);
                gmode(2);
            }
            pos(x + cnt * 44 + 46
                    - strlen_u(
                          i18n::_(u8"ui", u8"inventory_command", u8"_"s + p))
                        * 3,
                y + 7);
            if (invctrl == p)
            {
                bmes(
                    i18n::_(u8"ui", u8"inventory_command", u8"_"s + p),
                    255,
                    255,
                    255);
            }
            else
            {
                bmes(
                    i18n::_(u8"ui", u8"inventory_command", u8"_"s + p),
                    165,
                    165,
                    165);
            }
            if (invkey(p) != ""s)
            {
                pos(x + cnt * 44 + 46, y + 18);
                bmes(u8"("s + invkey(p) + u8")"s, 235, 235, 235);
            }
        }
        pos(x + 325, y + 32);
        bmes(
            ""s + key_prev + u8","s + key_next + u8",Tab "s
                + lang(u8"[メニュー切替]"s, u8"[Change]"s),
            255,
            255,
            255);
    }
label_2061_internal:
    s = lang(
        i18n::_(u8"ui", u8"inventory_command", u8"_"s + invctrl)
            + u8"アイテムの選択"s,
        i18n::_(u8"ui", u8"inventory_command", u8"_"s + invctrl));
    s(1) = strhint2 + strhint5 + strhint5b + strhint3;
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9
        || invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        s(1) += strhint7;
    }
    if (invctrl == 1)
    {
        s(1) += ""s + key_mode2 + u8" "s
            + lang(u8"[保持指定]"s, u8"[Tag No-Drop]"s);
    }
    if (invctrl == 2)
    {
        if (dropcontinue == 0)
        {
            s(1) += ""s + key_mode2 + u8" "s
                + lang(u8"[連続で置く]"s, u8"[Multi Drop]"s);
        }
    }
    display_window((windoww - 640) / 2 + inf_screenx, winposy(432), 640, 432);
    if (invicon(invctrl) != -1)
    {
        pos(wx + 46, wy - 14);
        gcopy(3, 288 + invicon(invctrl) * 48, 48, 48, 48);
    }
    s = lang(u8"重さ"s, u8"Weight"s);
    if (invctrl == 11 || invctrl == 12)
    {
        s = lang(u8"値段"s, u8"Price"s);
    }
    if (invctrl == 28)
    {
        s = lang(u8"メダル"s, u8"Medal"s);
    }
    display_topic(lang(u8"アイテムの名称"s, u8"Name"s), wx + 28, wy + 30);
    display_topic(s, wx + 526, wy + 30);
    if (showresist)
    {
        pos(wx + 300, wy + 40);
        mes(lang(
            u8"火 冷 雷 闇 幻 毒 獄 音 神 沌 魔"s,
            u8"Fi Co Li Da Mi Po Nt So Nr Ch Ma"s));
    }
    pos(wx + ww - 136, wy - 6);
    gcopy(3, 960, 96, 144, 48);
    if (showresist == 0)
    {
        pos(wx + ww - 186, wy - 6);
        gcopy(3, 960, 144, 48, 72);
    }
    pos(wx + ww - 246, wy - 6);
    gcopy(3, 1008, 144, 48, 72);
    pos(wx - 6, wy - 6);
    gcopy(3, 960, 216, 48, 72);
    s = ""s + listmax + u8" items"s;
    s += u8"  (重さ合計 "s + cnvweight(cdata[0].inventory_weight) + u8"/"s
        + cnvweight(cdata[0].max_inventory_weight) + u8"  荷車 "s
        + cnvweight(gdata_cargo_weight) + u8")"s;
    if (invctrl == 25)
    {
        s = ""s;
    }
    display_note(s);
    if (invctrl == 25)
    {
        x = (windoww - 640) / 2 + inf_screenx + 455;
        y = winposy(432) - 32;
        int w = 200;
        int h = 102;
        window(x + 4, y + 4, w, h - h % 8, 0, -1);
        window(x, y, w, h - h % 8, 0, 0);
        font(lang(cfg_font1, cfg_font2), 12 + en - en * 2, 0);
        pos(x + 16, y + 17);
        mes(u8"Dv:"s + cdata[tc].dv + u8" Pv:"s + cdata[tc].pv);
        pos(x + 16, y + 35);
        mes(lang(u8"装備重量:"s, u8"EquipWt:"s)
            + cnvweight(cdata[tc].sum_of_equipment_weight) + ""s
            + cnveqweight(tc));
        x = wx + 40;
        y = wy + wh - 65 - wh % 8;
        pos(x, y);
        mes(lang(u8"装備箇所:"s, u8"Equip:"s));
        x += 60;
        for (int cnt = 100; cnt < 130; ++cnt)
        {
            if (cdata_body_part(tc, cnt) == 0)
            {
                continue;
            }
            p = cdata_body_part(tc, cnt);
            if (p % 10000 != 0)
            {
                color(50, 50, 200);
            }
            else
            {
                color(100, 100, 100);
            }
            pos(x, y);
            mes(""s + i18n::_(u8"ui", u8"body_part", u8"_"s + (p / 10000)));
            color(0, 0, 0);
            x +=
                (std::size(i18n::_(u8"ui", u8"body_part", u8"_"s + (p / 10000)))
                 + 1)
                * 6;
        }
    }
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        if (cnt % 2 == 0)
        {
            pos(wx + 70, wy + 60 + cnt * 19);
            gfini(540, 18);
            gfdec2(12, 14, 16);
        }
    }
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        p = list(0, p);
        s(0) = itemname(p, inv[p].number);
        s(1) = cnvweight(inv[p].weight * inv[p].number);
        if (invctrl == 11)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(p, 0) + u8" gp"s;
        }
        if (invctrl == 12)
        {
            s += u8" "s + cnvweight(inv[p].weight);
            s(1) = ""s + calcitemvalue(p, 1) + u8" gp"s;
        }
        if (invctrl == 28)
        {
            s(1) = ""s + calcmedalvalue(p) + lang(u8" 枚"s, u8" Coins"s);
        }
        if (invctrl != 3 && invctrl != 11 && invctrl != 22 && invctrl != 27
            && invctrl != 28)
        {
            if (p >= 5080)
            {
                s += lang(u8"(足元)"s, u8" (Ground)"s);
            }
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            if (gdata(40 + cnt) == inv[p].id + invctrl * 10000)
            {
                s += u8"{"s + cnt + u8"}"s;
            }
        }
        display_key(wx + 58, wy + 60 + cnt * 19 - 2, cnt);
        p(1) = inv[p].image % 1000;
        prepare_item_image(p(1), inv[p].color, inv[p].param1);
        pos(wx + 37, wy + 69 + cnt * 19);
        gmode(2, chipi(2, p(1)), chipi(3, p(1)));
        grotate(
            1,
            0,
            960,
            0,
            chipi(2, p(1)) * inf_tiles / chipi(3, p(1)),
            inf_tiles);
        if (inv[p].body_part != 0)
        {
            pos(wx + 46, wy + 72 + cnt * 18 - 3);
            gcopy(3, 12, 348, 12, 12);
            if (p == mainweapon)
            {
                s += lang(u8"(利腕)"s, u8" (Main hand)"s);
            }
        }
        if (showresist)
        {
            equipinfo(p, wx + 300, wy + 60 + cnt * 19 + 2);
            s = strmid(s, 0, 24);
        }
        cs_list(cs == cnt, s, wx + 84, wy + 60 + cnt * 19 - 1, 0, 1, p);
        pos(wx + 600 - strlen_u(s(1)) * 7, wy + 60 + cnt * 19 + 2);
        mes(s(1));
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    if (showmoney)
    {
        if (showresist == 0)
        {
            font(lang(cfg_font1, cfg_font2), 13 - en * 2, 0);
            gmode(2);
            pos(wx + 340, wy + 32);
            gcopy(3, 0, 392, 24, 24);
            pos(wx + 368, wy + 37 - en * 2);
            mes(""s + cdata[tc].gold + u8" gp"s);
        }
    }
    redraw();
    await(cfg_wait1);
    key_check();
    cursor_check();
    invmark(invctrl) = page * 1000 + cs;
    ELONA_GET_SELECTED_ITEM(p, 0);
    if (mode == 9)
    {
        if (listmax == 0)
        {
            p = -1;
            key = key_cancel;
        }
    }
    if (p != -1)
    {
        ci = p;
        if (invctrl == 12 || (invctrl == 24 && invctrl(1) != 0))
        {
            cc = -1;
        }
        else
        {
            cc = 0;
        }
    label_2062_internal:
        int stat = cargocheck();
        if (stat == 0)
        {
            goto label_2061_internal;
        }
        if (invctrl == 1)
        {
            show_item_description();
            goto label_20591;
        }
        if (invctrl == 2)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(lang(
                    u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                    u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                goto label_2060_internal;
            }
            if (!inv_getspace(-1))
            {
                txt(lang(
                    u8"これ以上は置けない。"s,
                    u8"You can't drop items any more."s));
                snd(27);
                goto label_2060_internal;
            }
            if (mdata(18) != 0)
            {
                if (inv_sum(-1) >= mdata(18))
                {
                    if (the_item_db[inv[ci].id]->category != 60000)
                    {
                        txt(lang(
                            u8"これ以上は置けない。"s,
                            u8"You can't drop items any more."s));
                        snd(27);
                        goto label_2060_internal;
                    }
                }
            }
            if (inv[ci].number > 1)
            {
                txt(lang(
                    itemname(ci, 1) + u8"をいくつ落とす？ (1〜"s
                        + inv[ci].number + u8") "s,
                    u8"How many? (1 to "s + inv[ci].number + u8")"s));
                display_msg(screenmsgy, 1);
                inputlog = ""s + inv[ci].number;
                show_number_of_text_prompt(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    8,
                    1,
                    inv[ci].number);
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number)
                {
                    in = inv[ci].number;
                }
                if (in == 0 || rtval == -1)
                {
                    goto label_2060_internal;
                }
            }
            else
            {
                in = 1;
            }
            savecycle();
            dropval = 0;
            drop_item();
            if (dropcontinue)
            {
                menucycle = 1;
                ++dropcontinue;
                goto label_20591;
            }
            turn_end();
            return 0;
        }
        if (invctrl == 3 || invctrl == 11 || invctrl == 12 || invctrl == 22
            || (invctrl == 24 && (invctrl(1) == 3 || invctrl(1) == 5)))
        {
            if (invctrl != 3 && invctrl != 22)
            {
                if (ibit(13, ci))
                {
                    snd(27);
                    txt(lang(
                        u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                        u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                    goto label_2060_internal;
                }
            }
            if (invctrl == 24)
            {
                if (invctrl(1) == 3 || invctrl(1) == 5)
                {
                    if (inv_sum(-1) >= invcontainer)
                    {
                        snd(27);
                        txt(lang(
                            u8"これ以上入らない。"s,
                            u8"The container is full."s));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (inv[ci].weight >= efp * 100)
                    {
                        snd(27);
                        txt(lang(
                            u8"重さが"s + cnvweight(efp * 100)
                                + u8"以上の物は入らない。"s,
                            u8"The container can only hold items weight less than "s
                                + cnvweight(efp * 100) + u8"."s));
                        goto label_2060_internal;
                    }
                    if (inv[ci].weight <= 0)
                    {
                        snd(27);
                        txt(lang(
                            u8"荷物は入らない。"s,
                            u8"The container cannot hold cargos"s));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!actionsp(0, 10))
                    {
                        txt(lang(
                            u8"疲労し過ぎて失敗した！"s,
                            u8"You are too exhausted!"s));
                        goto label_2063_internal;
                    }
                }
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    if (gdata_rights_to_succeed_to < 1)
                    {
                        txt(lang(
                            u8"遺産の相続権を持っていない。"s,
                            u8"You don't have a claim."s));
                        goto label_2060_internal;
                    }
                }
                if (invctrl(1) == 5)
                {
                    if (!actionsp(0, 10))
                    {
                        txt(lang(
                            u8"疲労し過ぎて失敗した！"s,
                            u8"You are too exhausted!"s));
                        goto label_2063_internal;
                    }
                }
            }
            if (inv[ci].own_state > 0 && inv[ci].own_state < 3)
            {
                snd(27);
                ++msgdup;
                if (inv[ci].own_state == 2)
                {
                    txt(lang(
                        u8"それは持ち運べない。"s, u8"You can't carry it."s));
                }
                if (inv[ci].own_state == 1)
                {
                    txt(lang(
                            u8"それはあなたの物ではない。"s,
                            u8"It's not your property."s),
                        lang(
                            u8"盗むなんてとんでもない。"s,
                            u8"You can't just take it."s),
                        lang(u8"それは拾えない。"s, u8"It's not yours."s));
                }
                update_screen();
                pc_turn(false);
            }
            page_save();
            if (mode == 6 && inv[ci].number > 1 && invctrl != 22)
            {
                if (invctrl == 11)
                {
                    txt(lang(
                        itemname(ci, 1) + u8"をいくつ買う？ (1〜"s
                            + inv[ci].number + u8") "s,
                        u8"How many? (1 to "s + inv[ci].number + u8")"s));
                }
                if (invctrl == 12)
                {
                    txt(lang(
                        itemname(ci, 1) + u8"をいくつ売る？ (1〜"s
                            + inv[ci].number + u8") "s,
                        u8"How many? (1 to "s + inv[ci].number + u8")"s));
                }
                display_msg(screenmsgy, 2);
                inputlog = ""s + inv[ci].number;
                show_number_of_text_prompt(
                    (windoww - 200) / 2 + inf_screenx,
                    winposy(60),
                    8,
                    1,
                    inv[ci].number);
                in = elona::stoi(inputlog(0));
                if (in > inv[ci].number)
                {
                    in = inv[ci].number;
                }
                if (in == 0 || rtval == -1)
                {
                    screenupdate = -1;
                    update_screen();
                    stick(p);
                    goto label_2060_internal;
                }
            }
            else
            {
                in = inv[ci].number;
            }
            if (mode == 6 && invctrl != 22 && invctrl != 24)
            {
                if (invctrl == 11)
                {
                    txt(lang(
                        itemname(ci, in) + u8"を "s + in * calcitemvalue(ci, 0)
                            + u8" gp で買う？"s,
                        u8"Do you really want to buy "s + itemname(ci, in)
                            + u8" for "s + in * calcitemvalue(ci, 0)
                            + u8" gold pieces?"s));
                }
                if (invctrl == 12)
                {
                    txt(lang(
                        itemname(ci, in) + u8"を "s + in * calcitemvalue(ci, 1)
                            + u8" gp で売る？"s,
                        u8"Do you really want to sell "s + itemname(ci, in)
                            + u8" for "s + in * calcitemvalue(ci, 1)
                            + u8" gold pieces?"s));
                }
                ELONA_YES_NO_PROMPT();
                show_prompt(promptx, prompty, 160);
                if (rtval != 0)
                {
                    screenupdate = -1;
                    update_screen();
                    goto label_20591;
                }
                if (invctrl == 11)
                {
                    if (calcitemvalue(ci, 0) * in > cdata[0].gold)
                    {
                        screenupdate = -1;
                        update_screen();
                        txt(lang(
                                u8"あなたは財布を開いてがっかりした…"s,
                                u8"You check your wallet and shake your head."s),
                            lang(
                                u8"もっと稼がないと買えない！"s,
                                u8"You need to earn more money!"s));
                        msgkeep = 1;
                        goto label_20591;
                    }
                }
                if (invctrl == 12)
                {
                    if (cdata[tc].character_role != 1009)
                    {
                        if (calcitemvalue(ci, 1) * in > cdata[tc].gold)
                        {
                            screenupdate = -1;
                            update_screen();
                            txt(lang(
                                name(tc) + u8"は財布を開いてがっかりした…"s,
                                name(tc) + u8" checks "s + his(tc)
                                    + u8" wallet and shake "s + his(tc)
                                    + u8" head."s));
                            msgkeep = 1;
                            goto label_20591;
                        }
                    }
                }
            }
            int stat = pick_up_item();
            if (stat == 0)
            {
                goto label_20591;
            }
            if (stat == -1)
            {
                turn_end();
                return 0;
            }
            if (invctrl == 22)
            {
                if (invctrl(1) == 1)
                {
                    --gdata_rights_to_succeed_to;
                    if (invctrl(1) == 1)
                    {
                        txt(lang(
                            u8"残り"s + gdata_rights_to_succeed_to
                                + u8"個分のアイテムの相続権を持っている。"s,
                            u8"You can claim "s + gdata_rights_to_succeed_to
                                + u8" more heirloom"s
                                + _s2(gdata_rights_to_succeed_to) + u8"."s));
                    }
                }
                if (invctrl(1) == 4)
                {
                    ++gdata_gift_count_of_little_sister;
                    invsubroutine = 0;
                    return 1;
                }
            }
            screenupdate = -1;
            update_screen();
            goto label_20591;
        }
        if (invctrl == 5)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(lang(
                    u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                    u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                goto label_2060_internal;
            }
            screenupdate = -1;
            update_screen();
            savecycle();
            if (cdata[0].nutrition > 10000)
            {
                txt(lang(
                        u8"今はとても食べられない。"s,
                        u8"Your are too full to eat."s),
                    lang(
                        u8"腹がさける…"s,
                        u8"You are too bloated to eat any more."s),
                    lang(
                        u8"まだ腹は減っていない。"s,
                        u8"Your stomach can't digest any more."s));
                update_screen();
                pc_turn(false);
            }
            do_eat_command();
            return 0;
        }
        if (invctrl == 6)
        {
            if (cc == 0)
            {
                if (trait(161) != 0)
                {
                    if (inv[ci].weight >= 1000)
                    {
                        txt(lang(
                            u8"それは重すぎて装備できない。"s,
                            u8"It's too heavy to equip."s));
                        goto label_2060_internal;
                    }
                }
            }
            equip_item(cc);
            refresh_character(cc);
            screenupdate = -1;
            update_screen();
            snd(13);
            txtnew();
            txt(lang(
                itemname(ci) + u8"を装備した。"s,
                u8"You equip "s + itemname(ci) + u8"."s));
            gdata(808) = 1;
            switch (inv[ci].curse_state)
            {
            case curse_state_t::doomed:
                txt(lang(
                    name(cc) + u8"は破滅への道を歩み始めた。"s,
                    u8"You are now one step closer to doom."s));
                break;
            case curse_state_t::cursed:
                txt(lang(
                    name(cc) + u8"は急に寒気がしてふるえた。"s,
                    u8"You suddenly feel a chill and shudder."s));
                break;
            case curse_state_t::none: break;
            case curse_state_t::blessed:
                txt(lang(
                    name(cc) + u8"は何かに見守られている感じがした。"s,
                    u8"You feel as someone is watching you intently."s));
                break;
            }
            if (cdata_body_part(cc, body) / 10000 == 5)
            {
                equip_melee_weapon();
            }
            menucycle = 1;
            ctrl_inventory_equipment();
            return 0;
        }
        if (invctrl == 7)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            do_read_commad();
            return 0;
        }
        if (invctrl == 8)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            do_drink_command();
            return 0;
        }
        if (invctrl == 9)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            do_zap_command();
            return 0;
        }
        if (invctrl == 10)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(lang(
                    u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                    u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                goto label_2060_internal;
            }
            ti = inv_getfreeid(tc);
            if (cdata[tc].sleep)
            {
                txt(lang(
                    name(tc) + u8"は眠っている。"s,
                    name(tc) + u8" "s + is(tc) + u8" sleeping."s));
                snd(27);
                goto label_2060_internal;
            }
            if (ti == -1)
            {
                txt(lang(
                    name(tc) + u8"はこれ以上持てない。"s,
                    his(tc) + u8" inventory is full."s));
                snd(27);
                goto label_2060_internal;
            }
            reftype = the_item_db[inv[ci].id]->category;
            if (inv[ci].id == 729)
            {
                txt(lang(
                    u8"あなたは"s + name(tc) + u8"に"s + itemname(ci, 1)
                        + u8"をプレゼントした。"s,
                    u8"You give "s + name(tc) + u8" "s + itemname(ci, 1)
                        + u8"."s));
                --inv[ci].number;
                refresh_burden_state();
                txt(lang(
                    u8"「え、これを"s + _ore(3) + u8"にくれるの"s + _ka(1) + ""s
                        + _thanks(2) + u8"」"s,
                    u8"\"Thank you!\""s));
                modimp(tc, giftvalue(inv[ci].param4));
                cdata[tc].emotion_icon = 317;
                update_screen();
                pc_turn(false);
            }
            f = 0;
            p = sdata(10, tc) * 500 + sdata(11, tc) * 500
                + sdata(153, tc) * 2500 + 25000;
            if (cdata[tc].id == 265)
            {
                p *= 5;
            }
            if (inv_weight(tc) + inv[ci].weight > p)
            {
                f = 1;
            }
            if (cdata[tc].id != 265)
            {
                if (reftype == 60000)
                {
                    f = 2;
                }
                if (reftype == 64000)
                {
                    f = 3;
                }
            }
            if (inv[ci].weight < 0)
            {
                f = 4;
            }
            if (f)
            {
                s(0) = "";
                s(1) = lang(u8"「重すぎ」"s, u8"\"Too heavy!\""s);
                s(2) = lang(u8"「無理」"s, u8"\"No way.\""s);
                s(3) = lang(u8"「いらん」"s, u8"\"I don't want it.\""s);
                s(4) = lang(u8"「イヤ！」"s, u8"\"Never!\""s);
                snd(27);
                txt(lang(name(tc) + s(f), s(f)));
                goto label_2060_internal;
            }
            f = 0;
            if (cdata[tc].relationship == 10)
            {
                f = 1;
            }
            else
            {
                if (inv[ci].identification_state < 2)
                {
                    snd(27);
                    txt(lang(
                        u8"「そんな得体の知れないものはいらない"s + _yo()
                            + u8"」"s,
                        u8"\"I dont't want it. It's too creepy.\""s));
                    goto label_2060_internal;
                }
                if (is_cursed(inv[ci].curse_state))
                {
                    snd(27);
                    txt(lang(
                        u8"「それ、呪われてい"s + _ru() + u8"」"s,
                        u8"\"It's cursed!\""s));
                    goto label_2060_internal;
                }
                if (reftype == 53000)
                {
                    f = 1;
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/neg/"))
                    {
                        f = 0;
                    }
                    if (inv[ci].id == 16 || inv[ci].id == 245)
                    {
                        f = 0;
                    }
                }
                if (reftype == 52000)
                {
                    f = 1;
                    if (the_item_db[inv[ci].id]->subcategory == 52002)
                    {
                        if (cdata[tc].drunk)
                        {
                            snd(27);
                            txt(lang(
                                u8"「もう飲めない"s + _yo() + u8"」"s,
                                u8"\"Enough for me.\""s));
                            goto label_2060_internal;
                        }
                    }
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/neg/"))
                    {
                        f = 0;
                    }
                    if (strutil::contains(
                            the_item_db[inv[ci].id]->filter, u8"/nogive/"))
                    {
                        f = 0;
                    }
                    if (cbit(978, tc))
                    {
                        if (inv[ci].id == 262 || inv[ci].id == 519
                            || inv[ci].id == 392)
                        {
                            f = 1;
                            txt(lang(u8"「おろす…」"s, u8"\"Abortion...\""s));
                        }
                    }
                }
            }
            if (f)
            {
                snd(13);
                txt(lang(
                    itemname(ci, 1) + u8"を渡した。"s,
                    u8"You hand "s + itemname(ci, 1) + u8" to "s + name(tc)
                        + u8"."s));
                if (inv[ci].id == 477 || inv[ci].id == 473)
                {
                    txtef(2);
                    txt(lang(
                        name(tc) + u8"は顔を赤らめた。"s,
                        name(tc) + u8" blushes."s));
                    modimp(tc, 15);
                    cdata[tc].emotion_icon = 317;
                }
                if (inv[ci].id == 620)
                {
                    txtef(8);
                    txt(lang(
                        name(tc) + u8"は激怒して"s + itemname(ci, 1)
                            + u8"を叩き割った。"s,
                        name(tc) + u8" throws it on the ground angrily."s));
                    snd(47);
                    txtef(9);
                    txt(lang(
                            name(tc) + u8"「サイテー！！」"s,
                            u8"\"You scum!\""s),
                        lang(
                            name(tc) + u8"「このヘンタイ！」"s,
                            u8"\"What are you trying to do!\""s),
                        lang(
                            name(tc) + u8"「ガード！ガード！ガード！」"s,
                            u8"\"Guard! Guard! Guard!\""s));
                    modimp(tc, -20);
                    cdata[tc].emotion_icon = 318;
                    --inv[ci].number;
                    refresh_burden_state();
                    goto label_20591;
                }
                item_copy(ci, ti);
                --inv[ci].number;
                inv[ti].number = 1;
                item_stack(tc, ti, 1);
                ci = ti;
                rc = tc;
                set_item_which_will_be_used();
                wear_most_valuable_equipment_for_all_body_parts();
                if (tc < 16)
                {
                    create_pcpic(tc, true);
                }
                refresh_character(tc);
                refresh_burden_state();
                if (invally == 1)
                {
                    goto label_20591;
                }
                update_screen();
                turn_end();
                return 0;
            }
            snd(27);
            txt(lang(
                name(tc) + u8"は"s + itemname(ci, 1) + u8"を受け取らない。"s,
                name(tc) + u8" refuse"s + _s(tc) + u8" to take "s
                    + itemname(ci, 1) + u8"."s));
            goto label_2060_internal;
        }
        if (invctrl == 13)
        {
            screenupdate = -1;
            update_screen();
            int stat = item_identify(ci, -1, efp);
            if (stat == 0)
            {
                txt(lang(
                    u8"新しい知識は得られなかった。より上位の鑑定で調べる必要がある。"s,
                    u8"You need higher identification to gain new knowledge."s));
            }
            else if (stat < 3)
            {
                txt(lang(
                    u8"それは"s + itemname(ci, inv[ci].number)
                        + u8"だと判明したが、完全には鑑定できなかった。"s,
                    u8"The item is half-identified as "s + itemname(ci, 1)
                        + u8"."s));
            }
            else
            {
                txt(lang(
                    u8"それは"s + itemname(ci, inv[ci].number)
                        + u8"だと完全に判明した。"s,
                    u8"The item is fully identified as "s + itemname(ci, 1)
                        + u8"."s));
            }
            item_stack(0, ci, 1);
            invsubroutine = 0;
            return 1;
        }
        if (invctrl == 14)
        {
            savecycle();
            do_use_command();
            return 0;
        }
        if (invctrl == 16)
        {
            screenupdate = -1;
            update_screen();
            invsubroutine = 0;
            return 1;
        }
        if (invctrl == 15)
        {
            screenupdate = -1;
            update_screen();
            savecycle();
            do_open_command();
            return 0;
        }
        if (invctrl == 17)
        {
            cidip = ci;
            savecycle();
            invctrl = 18;
            txtnew();
            snd(26);
            goto label_20591;
        }
        if (invctrl == 18)
        {
            screenupdate = -1;
            update_screen();
            do_dip_command();
            return 0;
        }
        if (invctrl == 19)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(lang(
                    u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                    u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                goto label_2060_internal;
            }
            screenupdate = -1;
            update_screen();
            savecycle();
            offer();
            return 0;
        }
        if (invctrl == 20)
        {
            citrade = ci;
            invctrl = 21;
            snd(26);
            goto label_20591;
        }
        if (invctrl == 21)
        {
            if (ibit(13, ci))
            {
                snd(27);
                txt(lang(
                    u8"それはあなたの大事なものだ。<調べる>メニューから解除できる。"s,
                    u8"It's set as no-drop. You can reset it from the <examine> menu."s));
                goto label_2060_internal;
            }
            if (cdata[tc].continuous_action_id != 0)
            {
                cdata[tc].continuous_action_id = 0;
                cdata[tc].continuous_action_turn = 0;
                cdata[tc].continuous_action_item = 0;
            }
            snd(13);
            ibitmod(12, citrade, 0);
            txt(lang(
                itemname(ci) + u8"を"s + itemname(citrade) + u8"と交換した。"s,
                u8"You receive "s + itemname(citrade) + u8" in exchange for "s
                    + itemname(ci) + u8"."s));
            if (inv[citrade].body_part != 0)
            {
                p = inv[citrade].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
                inv[citrade].body_part = 0;
            }
            ti = citrade;
            item_exchange(ci, ti);
            convertartifact(ci);
            rc = tc;
            ci = citrade;
            if (cdata[rc].item_which_will_be_used == ci)
            {
                cdata[rc].item_which_will_be_used = 0;
            }
            wear_most_valuable_equipment_for_all_body_parts();
            if (tc >= 16)
            {
                supply_new_equipment();
            }
            inv_getfreeid_force();
            refresh_character(tc);
            refresh_burden_state();
            invsubroutine = 0;
            return 1;
        }
        if (invctrl == 23)
        {
            item_separate(ci);
            invsubroutine = 0;
            return 1;
        }
        if (invctrl == 24)
        {
            if (invctrl(1) == 0)
            {
                snd(100);
                if (gdata_current_map == 36)
                {
                    gdata_mages_guild_quota -=
                        (inv[ci].param1 + 1) * inv[ci].number;
                    if (gdata_mages_guild_quota <= 0)
                    {
                        gdata_mages_guild_quota = 0;
                    }
                    txtef(2);
                    txt(lang(
                            itemname(ci) + u8"を納入した"s,
                            u8"You deliver "s + itemname(ci) + u8". "s)
                        + u8"("s + (inv[ci].param1 + 1) * inv[ci].number
                        + u8" Guild Point)"s);
                    if (gdata_mages_guild_quota == 0)
                    {
                        snd(51);
                        txtef(2);
                        txt(lang(
                            u8"ノルマを達成した！"s,
                            u8"You fulfill the quota!"s));
                    }
                }
                else
                {
                    qdata(13, gdata_executing_immediate_quest) +=
                        inv[ci].weight * inv[ci].number;
                    txtef(2);
                    txt(lang(
                            itemname(ci) + u8"を納入した。"s,
                            u8"You deliver"s + itemname(ci) + u8"."s)
                        + u8" +"s + cnvweight(inv[ci].weight * inv[ci].number)
                        + lang(u8"  納入済み"s, u8" Delivered "s) + u8"("s
                        + cnvweight(qdata(13, gdata_executing_immediate_quest))
                        + u8") "s + lang(u8"納入ノルマ"s, u8"Quota "s) + u8"("s
                        + cnvweight(qdata(12, gdata_executing_immediate_quest))
                        + u8")"s);
                }
                inv[ci].number = 0;
                refresh_burden_state();
                goto label_20591;
            }
            if (invctrl(1) == 2)
            {
                if (cdata[0].gold < inv[ci].subname)
                {
                    snd(27);
                    txt(lang(
                        u8"金が足りない…"s, u8"You don't have enough money."s));
                    goto label_2060_internal;
                }
                if (gdata_left_bill <= 0)
                {
                    snd(27);
                    txt(lang(
                        u8"まだ納税する必要はない。"s,
                        u8"You don't have to pay your tax yet."s));
                    goto label_20591;
                }
                cdata[0].gold -= inv[ci].subname;
                snd(12);
                txtef(2);
                txt(lang(
                    itemname(ci) + u8"を支払った。"s,
                    u8"You pay "s + itemname(ci) + u8"."s));
                --inv[ci].number;
                --gdata_left_bill;
                refresh_burden_state();
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
        }
        if (invctrl == 25)
        {
            ti = inv_getfreeid(0);
            if (ti == -1)
            {
                txt(lang(
                    u8"バックパックが一杯だ。"s, u8"Your inventory is full."s));
                goto label_2060_internal;
            }
            f = 0;
            if (the_item_db[inv[ci].id]->category == 77000)
            {
                f = 2;
            }
            if (f != 0)
            {
                s(0) = "";
                s(1) = lang(u8"「やだ」"s, u8"\"No!\""s);
                s(2) = lang(u8"「あげないよ」"s, u8"\"It's mine.\""s);
                s(3) = lang(u8"「だめ」"s, u8"\"Get off!\""s);
                s(4) = lang(u8"「イヤ！」"s, u8"\"Never.\""s);
                snd(27);
                txtef(4);
                txt(lang(name(tc) + s(f), s(f)));
                goto label_2060_internal;
            }
            if (inv[ci].body_part != 0)
            {
                if (is_cursed(inv[ci].curse_state))
                {
                    txt(lang(
                        itemname(ci) + u8"は呪われていて外せない。"s,
                        ""s + itemname(ci)
                            + u8" is cursed and can't be taken off."s));
                    goto label_20591;
                }
                p = inv[ci].body_part;
                cdata_body_part(tc, p) = cdata_body_part(tc, p) / 10000 * 10000;
                inv[ci].body_part = 0;
            }
            if (inv[ci].id == 477 || inv[ci].id == 473)
            {
                txtef(8);
                txt(lang(
                    name(tc) + u8"は激怒して"s + itemname(ci, 1)
                        + u8"を飲み込んだ。"s,
                    name(tc) + u8" swallows "s + itemname(ci, 1)
                        + u8" angrily."s));
                snd(65);
                modimp(tc, -20);
                cdata[tc].emotion_icon = 318;
                --inv[ci].number;
                goto label_20591;
            }
            snd(13);
            ibitmod(12, ci, 0);
            if (inv[ci].id == 54)
            {
                in = inv[ci].number;
            }
            else
            {
                in = 1;
            }
            txt(lang(
                itemname(ci, in) + u8"を受け取った。"s,
                u8"You take "s + itemname(ci, in) + u8"."s));
            if (inv[ci].id == 54)
            {
                cdata[0].gold += in;
                inv[ci].number = 0;
            }
            else
            {
                item_copy(ci, ti);
                inv[ci].number -= in;
                inv[ti].number = in;
                item_stack(0, ti, 1);
                convertartifact(ti);
            }
            rc = tc;
            wear_most_valuable_equipment_for_all_body_parts();
            if (tc < 16)
            {
                create_pcpic(tc, true);
            }
            refresh_character(tc);
            refresh_burden_state();
            goto label_20591;
        }
        if (invctrl == 26)
        {
            savecycle();
            int stat = target_position();
            if (stat != 1)
            {
                if (stat == 0)
                {
                    txt(lang(
                        u8"その場所は見えない。"s,
                        u8"You can't see the location."s));
                    update_screen();
                }
                pc_turn(false);
            }
            if (chipm(7, map(tlocx, tlocy, 0)) & 4)
            {
                txt(lang(
                    u8"そこには投げられない。"s,
                    u8"The location is blocked."s));
                update_screen();
                pc_turn(false);
            }
            do_throw_command();
            return 0;
        }
        if (invctrl == 27)
        {
            do_steal_command();
            invsubroutine = 0;
            return 1;
        }
        if (invctrl == 28)
        {
            txtnew();
            ti = inv_getfreeid(0);
            if (ti == -1)
            {
                txt(lang(
                    u8"これ以上持てない。"s, u8"Your inventory is full."s));
                snd(27);
                goto label_20591;
            }
            int stat = item_find(622, 3, 1);
            if (stat != -1)
            {
                i = stat;
                p = inv[i].number;
            }
            else
            {
                p = 0;
            }
            if (p < calcmedalvalue(ci))
            {
                txt(lang(
                    u8"メダルの数が足りない…"s,
                    u8"You don't have enough coins."s));
                snd(27);
                goto label_20591;
            }
            inv[i].number -= calcmedalvalue(ci);
            snd(12);
            item_copy(ci, ti);
            txt(lang(
                ""s + itemname(ti, 1) + u8"を受け取った！"s,
                u8"You receive "s + itemname(ti, 1) + u8"!"s));
            item_stack(0, ti, 1);
            convertartifact(ti, 1);
            goto label_20591;
        }
    }
    if (key == key_identify)
    {
        if (listmax != 0)
        {
            ci = list(0, pagesize * page + cs);
            show_item_description();
            goto label_20591;
        }
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_2060_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_2060_internal;
        }
    }
    if (menucycle == 1)
    {
        if (key == key_next || key == key_prev)
        {
            if (dropcontinue)
            {
                i = 4;
            }
            else if (invally == 1)
            {
                i = 2;
            }
            else if (invcontainer)
            {
                i = 3;
            }
            else if (mdata(6) == 1)
            {
                i = 1;
            }
            else
            {
                i = 0;
            }
            p = -1;
            for (int cnt = 0; cnt < 12; ++cnt)
            {
                if (invctrl == cycle(cnt, i))
                {
                    p = cnt;
                    break;
                }
            }
            if (p != -1)
            {
                if (key == key_next)
                {
                    ++p;
                    if (cycle(p, i) == -1)
                    {
                        p = 0;
                    }
                }
                if (key == key_prev)
                {
                    --p;
                    if (p < 0)
                    {
                        p = cyclemax(i);
                    }
                }
                if (invctrl != cycle(p, i))
                {
                    invctrl = cycle(p, i);
                    snd(100);
                    screenupdate = -1;
                    update_screen();
                    goto label_20591;
                }
            }
        }
    }
    if (key == key_mode2)
    {
        if (invctrl == 1)
        {
            ci = list(0, pagesize * page + cs);
            if (ibit(13, ci) == 0)
            {
                ibitmod(13, ci, 1);
                txt(lang(
                    itemname(ci) + u8"を大事なものに指定した。"s,
                    u8"You set "s + itemname(ci) + u8" as no-drop."s));
            }
            else
            {
                ibitmod(13, ci, 0);
                txt(lang(
                    itemname(ci) + u8"はもう大事なものではない。"s,
                    itemname(ci) + u8" is no longer set as no-drop."s));
            }
        }
        if (invctrl == 2)
        {
            if (dropcontinue == 0)
            {
                txt(lang(
                    u8"続けてアイテムを置くことができる。"s,
                    u8"You can continuously drop items."s));
                dropcontinue = 1;
                snd(100);
                screenupdate = -1;
                update_screen();
                goto label_20591;
            }
        }
    }
    if (key == key_mode)
    {
        if (showresist == 1)
        {
            showresist = 0;
        }
        else
        {
            showresist = 1;
        }
        snd(1);
        goto label_2060_internal;
    }
    if (key == key_cancel)
    {
    label_2063_internal:
        savecycle();
        if (invctrl == 22)
        {
            if (invctrl(1) == 0)
            {
                if (listmax > 0)
                {
                    txt(lang(
                        u8"まだアイテムが残っているがいい？"s,
                        u8"Really leave these items?"s));
                    ELONA_YES_NO_PROMPT();
                    show_prompt(promptx, prompty, 160);
                    if (rtval != 0)
                    {
                        goto label_2060_internal;
                    }
                }
            }
        }
        cc = 0;
        efcancel = 1;
        if (invsubroutine == 1)
        {
            invsubroutine = 0;
            return 0;
        }
        if (invctrl == 6)
        {
            screenupdate = -1;
            update_screen();
            menucycle = 1;
            ctrl_inventory_equipment();
            return 0;
        }
        if (invctrl == 11 || invctrl == 12 || invctrl == 22 || invctrl == 28)
        {
            load_shoptmp();
            return 0;
        }
        if (invally == 1)
        {
            invally = 0;
        }
        if (dropcontinue)
        {
            dropcontinue = 0;
            turn_end();
            return 0;
        }
        screenupdate = 0;
        update_screen();
        pc_turn(false);
    }
    if (invctrl == 5 || invctrl == 7 || invctrl == 8 || invctrl == 9
        || invctrl == 14 || invctrl == 15 || invctrl == 26)
    {
        if (key == u8"sc"s)
        {
            p = list(0, pagesize * page + cs);
            if (inv[p].weight < 0)
            {
                snd(27);
                txt(lang(
                    u8"荷車の荷物は登録できない。"s,
                    u8"You can't make a shortcut for cargo stuff."s));
                goto label_20591;
            }
            snd(20);
            p = inv[list(0, pagesize * page + cs)].id + invctrl * 10000;
            if (gdata(40 + sc) == p)
            {
                gdata(40 + sc) = 0;
                goto label_2060_internal;
            }
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                if (gdata(40 + cnt) == p)
                {
                    gdata(40 + cnt) = 0;
                }
            }
            gdata(40 + sc) = p;
            txt(lang(
                u8"{"s + sc + u8"}キーにショートカットを割り当てた。"s,
                u8"You have assigned the shortcut to {"s + sc + u8"} key."s));
            goto label_2060_internal;
        }
    }
    goto label_2061_internal;
}



} // namespace elona
