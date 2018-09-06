#include "casino.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "casino_card.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "dmgheal.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "random.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

elona_vector1<int> atxpic;
int atxap;
int txtadvmsgfix;
elona_vector1<int> mattile;

void casino_dealer()
{
    begintempinv();
    atxthrough = 0;
    atxpic = 0;
    snd(39);
    mode = 9;
    atxbg = u8"bg13"s;
    atxbgbk = "";
    SDIM3(atxinfon, 80, 5);
    if (atxid == 2)
    {
        casino_random_site();
        return;
    }
    if (atxid == 1)
    {
        txt(i18n::s.get("core.locale.casino.talk_to_dealer"));
        play_music("core.mcCasino");
        casino_wrapper();
        return;
    }
    if (atxid == 4)
    {
        play_music("core.mcCasino");
        casino_wrapper();
        return;
    }
    casino_acquire_items();
    return;
}

void casino_choose_card()
{
label_18671_internal:
    key = "";
    keylog = "";
    screenupdate = -1;
    update_screen();
    if (atxid >= 2)
    {
        txtadvmsgfix = 136;
    }
    for (int cnt = 0, cnt_end = (noteinfo()); cnt < cnt_end; ++cnt)
    {
        noteget(s, cnt);
        if (strmid(s, 0, 1) == u8"@"s)
        {
            s(1) = strmid(s, 1, 2);
            s = strmid(s, 3, s(0).size() - 3);
            font(16 - en * 2);
            color(250, 240, 230);
            if (s(1) == u8"BL"s)
            {
                color(130, 130, 250);
            }
            if (s(1) == u8"GR"s)
            {
                color(130, 250, 130);
            }
            if (s(1) == u8"QM"s)
            {
                color(0, 100, 0);
            }
        }
        else
        {
            font(16 - en * 2);
            color(250, 240, 230);
        }
        pos(170, cnt * 20 + 120 + txtadvmsgfix);
        mes(s);
        color(0, 0, 0);
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
    gsel(2);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    gmode(2);
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
    }
    casino_adv_draw_mat();
label_1868_internal:
    x(0) = 170;
    x(1) = 400;
    y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
    y(1) = 20 * listmax;
    gmode(0);
    pos(x, y);
    gcopy(2, x, y, x(1), y(1));
    gmode(2);
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        display_key(
            170, noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20, cnt);
        s = listn(0, p);
        cs_list(
            cs == cnt,
            s,
            200,
            noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20,
            0,
            2);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    redraw();
    await(Config::instance().wait1);
    key_check();
    cursor_check();
    ELONA_GET_SELECTED_ITEM(rtval, snd(40));
    if (chatesc != -1)
    {
        if (key == key_cancel)
        {
            snd(40);
            rtval = chatesc;
        }
    }
    if (rtval != -1)
    {
        casino_fade_in_choices();
        atxpic = 0;
        return;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_18671_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_18671_internal;
        }
    }
    goto label_1868_internal;
}

void casino_adv_draw_mat()
{
    casino_prepare_choice_graphic();
    if (mattile != -1)
    {
        mattile = rnd(mattile(2)) + mattile(1);
    }
    for (int cnt = 0; cnt < 12; ++cnt)
    {
        x(0) = 170;
        x(1) = 300;
        y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
        y(1) = 20 * listmax;
        gmode(0);
        pos(x - 50, y - 50);
        gcopy(2, x - 50, y - 50, 100 + x(1), y(1) + 100);
        if (cnt == 11)
        {
            break;
        }
        pos(x + x(1) / 2 - 10 + cnt, y + y(1) / 2);
        gmode(4, cnt * 25);
        gcopy_c(2, 0, 0, x(1), y(1));
        if (atxpic != 0)
        {
            x(0) = 345;
            x(1) = atxpic(2) + 120;
            y(0) = 170;
            y(1) = atxpic(3);
            gmode(0);
            pos(x - atxpic(2) / 2, y - atxpic(3) / 2);
            gcopy(2, x - atxpic(2) / 2, y - atxpic(3) / 2, x(1), y(1));
            pos(x, y);
            gmode(2);
            double p_double;
            if (cnt == 10)
            {
                p_double = 0;
            }
            else
            {
                p_double = 0.6222 * cnt;
            }
            p(1) = 1;
            if (atxpic == 2)
            {
                p(1) = 5;
            }
            grotate(
                p(1),
                atxpic(1) % 33 * 32,
                atxpic(1) / 33 * 32,
                inf_tiles,
                inf_tiles,
                cnt * (atxpic(2) / 10),
                cnt * (atxpic(3) / 10),
                p_double);
        }
        if (mattile != -1)
        {
            int cnt2 = cnt;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                x(0) = cnt * 250 + 170;
                x(1) = 96;
                y(0) = 120;
                y(1) = 96;
                gmode(0);
                pos(x, y);
                gcopy(2, x, y, x(1), y(1));
                pos(x + x(1) / 2, y + y(1) / 2);
                gmode(2);
                gcopy_c(
                    1,
                    mattile % 33 * 32,
                    mattile / 33 * 32,
                    inf_tiles,
                    inf_tiles,
                    cnt2 * 9,
                    cnt2 * 9);
            }
        }
        await(20);
        redraw();
    }
    gmode(2);
    atxpic = 0;
    return;
}

void casino_fade_in_choices()
{
    casino_prepare_choice_graphic();
    for (int cnt = 0; cnt < 11; ++cnt)
    {
        x = 170;
        y(0) = noteinfo() * 20 + 120 + txtadvmsgfix + 16;
        y(1) = 20 * listmax;
        gmode(0);
        pos(x - 50, y - 50);
        gcopy(2, x - 50, y - 50, 100 + x(1), y(1) + 100);
        pos(x + x(1) / 2 - 2 * cnt, y + y(1) / 2);
        gmode(4, 250 - cnt * 25);
        gcopy_c(2, 0, 0, x(1), y(1));
        await(15);
        redraw();
    }
    return;
}

void casino_prepare_choice_graphic()
{
    x(1) = 300;
    cs = -1;
    boxf(170, noteinfo() * 20 + 120 + txtadvmsgfix + 16, x(1), 20 * listmax);
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        display_key(
            170, noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20, cnt);
        s = listn(0, p);
        gmode(2);
        cs_list(
            cs == cnt,
            s,
            200,
            noteinfo() * 20 + 120 + txtadvmsgfix + 16 + cnt * 20,
            0,
            2);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
    gsel(2);
    gmode(0);
    pos(0, 0);
    gcopy(
        0, 170, noteinfo() * 20 + 120 + txtadvmsgfix + 16, x(1), 20 * listmax);
    gsel(0);
    gmode(2);
    cs = 0;
    return;
}

void casino_acquire_items()
{
    mtilefilecur = -1;
    map_prepare_tileset_atlas();
    f = 0;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number() != 0)
        {
            f = 1;
        }
    }
    if (f == 1)
    {
        if (cdata.player().hp >= 0)
        {
            txt(i18n::s.get("core.locale.casino.can_acquire"));
            screenupdate = -1;
            update_screen();
            invsubroutine = 1;
            invctrl(0) = 22;
            invctrl(1) = 0;
            ctrl_inventory();
        }
    }
    mode = 0;
    atxid = 0;
    exittempinv();
    await(100);
    snd(39);
    play_music();
    return;
}

void casino_random_site()
{
    int atxrefval1 = 0;
    atxap = 10;
    atxspot = 19;
    atxinfon(0) = u8"ランダムサイト"s;
    atxinit();
    atxthrough = 1;
    if (atxid(1) == 0)
    {
        atxid(1) = 3;
        atxlv = gdata_current_dungeon_level;
        if (mdata_map_type == mdata_t::MapType::dungeon)
        {
            atxid(1) = 1;
        }
        if (mdata_map_type == mdata_t::MapType::dungeon_tower)
        {
            atxid(1) = 4;
        }
        if (mdata_map_type == mdata_t::MapType::dungeon_forest)
        {
            atxid(1) = 2;
        }
        if (mdata_map_type == mdata_t::MapType::dungeon_castle)
        {
            atxid(1) = 4;
        }
        if (mdata_map_type == mdata_t::MapType::world_map)
        {
            atxlv = cdata.player().level;
            if (4 <= gdata(62) && gdata(62) < 9)
            {
                atxid(1) = 2;
            }
            if (264 <= gdata(62) && gdata(62) < 363)
            {
                atxid(1) = 3;
            }
            if (9 <= gdata(62) && gdata(62) < 13)
            {
                atxid(1) = 2;
            }
            if (13 <= gdata(62) && gdata(62) < 17)
            {
                atxid(1) = 3;
            }
        }
    }
    if (atxid(1) == 8)
    {
        atxbg = u8"bg21"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 16;
        noteadd(u8"この辺りは残骸やら遺品やらでごちゃごちゃだ。"s);
    }
    if (atxid(1) == 7)
    {
        atxbg = u8"bg20"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 15;
        noteadd(u8"この辺りには見たこともない植物がたくさんある。"s);
    }
    if (atxid(1) == 6)
    {
        atxbg = u8"bg19"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 14;
        noteadd(u8"天然の鉱石の宝庫だ。"s);
    }
    if (atxid(1) == 5)
    {
        atxbg = u8"bg18"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 13;
        noteadd(u8"綺麗な泉がある。"s);
    }
    if (atxid(1) == 1)
    {
        atxbg = u8"bg13"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 9;
    }
    if (atxid(1) == 4)
    {
        atxbg = u8"bg17"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 12;
    }
    if (atxid(1) == 2)
    {
        atxbg = u8"bg15"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 10;
    }
    if (atxid(1) == 3)
    {
        atxbg = u8"bg16"s;
        mattile(0) = 0;
        mattile(1) = 495;
        mattile(2) = 3;
        atxspot = 11;
    }
label_1875:
    if (atxap <= 0 || cdata.player().hp < 0)
    {
        casino_adv_finish_search();
        return;
    }
    atxinit();
    noteadd(u8"何をしよう？"s);
    list(0, listmax) = 1;
    listn(0, listmax) = u8"探索"s;
    ++listmax;
    list(0, listmax) = 3;
    listn(0, listmax) = u8"去る"s;
    ++listmax;
    atxinfon(1) = u8"行動回数残り "s + atxap + u8"回\n"s;
    chatesc = 3;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    if (rtval == 1)
    {
        goto label_1876_internal;
        return;
    }
    if (rtval == 2)
    {
        goto label_1876_internal;
        return;
    }
    if (rtval == 3)
    {
        casino_adv_finish_search();
        return;
    }
    goto label_1875;
label_1876_internal:
    --atxap;
    atxinit();
    if (rnd(1) == 0)
    {
        atxrefval1 = -1;
        if (atxid(1) == 7)
        {
            atxpic(0) = 1;
            atxpic(1) = 171;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"茂みを見つけた。"s);
            list(0, listmax) = 1;
            listn(0, listmax) = u8"調べる"s;
            ++listmax;
            list(0, listmax) = 2;
            listn(0, listmax) = u8"採取する("s
                + i18n::_(u8"ability", std::to_string(180), u8"name") + u8": "s
                + sdata(180, 0) + u8")"s;
            ++listmax;
            atxrefval1 = 7;
        }
        if (atxid(1) == 6)
        {
            atxpic(0) = 1;
            atxpic(1) = 219;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"鉱石の岩がある。"s);
            list(0, listmax) = 1;
            listn(0, listmax) = u8"調べる"s;
            ++listmax;
            list(0, listmax) = 2;
            listn(0, listmax) = u8"掘る("s
                + i18n::_(u8"ability", std::to_string(163), u8"name") + u8": "s
                + sdata(163, 0) + u8")"s;
            ++listmax;
            atxrefval1 = 7;
        }
        if (atxid(1) == 5)
        {
            atxpic(0) = 1;
            atxpic(1) = 439;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"泉がある。"s);
            list(0, listmax) = 1;
            listn(0, listmax) = u8"飲む"s;
            ++listmax;
            list(0, listmax) = 2;
            listn(0, listmax) = u8"釣る("s
                + i18n::_(u8"ability", std::to_string(185), u8"name") + u8": "s
                + sdata(185, 0) + u8")"s;
            ++listmax;
            atxrefval1 = 7;
        }
        if (atxid(1) == 8)
        {
            atxpic(0) = 1;
            atxpic(1) = 199;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"残骸を見つけた。"s);
            list(0, listmax) = 1;
            listn(0, listmax) = u8"あさる"s;
            ++listmax;
            list(0, listmax) = 2;
            listn(0, listmax) = u8"解剖する("s
                + i18n::_(u8"ability", std::to_string(161), u8"name") + u8": "s
                + sdata(161, 0) + u8")"s;
            ++listmax;
            atxrefval1 = 7;
        }
        if (atxrefval1 == -1)
        {
            noteadd(u8"壁に何やら怪しいひび割れがある…"s);
            list(0, listmax) = 1;
            listn(0, listmax) = u8"叩く(筋力)"s;
            ++listmax;
            list(0, listmax) = 2;
            listn(0, listmax) = u8"調べる(感知)"s;
            ++listmax;
        }
        atxinfon(1) = u8"行動回数残り "s + atxap + u8"回\n"s;
        chatesc = 1;
        txtadvmsgfix = 0;
        txtadvscreenupdate = 1;
        casino_choose_card();
        atxinit();
        if (rtval == 1)
        {
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                p = random_material(atxlv);
                atxpic(0) = 1;
                atxpic(1) = matref(2, p);
                atxpic(2) = 96;
                atxpic(3) = 96;
                snd(41);
                mat(p) += 1;
                noteadd(
                    "@BL"
                    + i18n::s.get(
                          "core.locale.casino.you_get", 1, matname(p), mat(p)));
            }
            atxthrough = 1;
            goto label_1875;
        }
        if (rtval == 2)
        {
            atxthrough = 1;
            goto label_1875;
        }
    }
    if (rnd(8) == 0)
    {
        if (rnd(4) == 0)
        {
            noteadd(u8"あれ…？"s);
            noteadd(u8"道に迷った！ (行動回数-2)"s);
            atxap -= 2;
            atxthrough = 1;
            goto label_1875;
        }
        if (rnd(2) == 0)
        {
            atxpic(0) = 2;
            atxpic(1) = 205;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"幽霊に脅かされた！ (行動回数-1)"s);
            snd(70);
            atxap -= 1;
            atxthrough = 1;
            goto label_1875;
        }
        if (rnd(2) == 0)
        {
            atxpic(0) = 1;
            atxpic(1) = 424;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"小石につまづいてころんでしまった！ (行動回数-1)"s);
            snd(70);
            atxap -= 1;
            atxthrough = 1;
            goto label_1875;
        }
    }
    if (rnd(8) == 0)
    {
        if (rnd(4) == 0)
        {
            atxpic(0) = 1;
            atxpic(1) = 200;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"ふかふかの藁を見つけた。"s);
            noteadd(u8"ふかふかして気持ちいい。（行動回数+3)"s);
            atxap += 2;
            atxthrough = 1;
            goto label_1875;
        }
        if (rnd(2) == 0)
        {
            atxpic(0) = 1;
            atxpic(1) = 294;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"切り株がある。"s);
            noteadd(u8"腰を下ろして疲れを癒した。（行動回数+2)"s);
            atxap += 2;
            atxthrough = 1;
            goto label_1875;
        }
        if (rnd(2) == 0)
        {
            atxpic(0) = 1;
            atxpic(1) = 127;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"綺麗な花を見つけた。"s);
            noteadd(u8"心がなごんだ…（行動回数+2)"s);
            atxap += 2;
            atxthrough = 1;
            goto label_1875;
        }
    }
    if (rnd(7) == 0)
    {
        if (rnd(3))
        {
            atxpic(0) = 2;
            atxpic(1) = 210;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"痛っ！蚊に刺された。"s);
            snd(2);
            damage_hp(cdata.player(), cdata.player().max_hp * 5 / 100, -10);
        }
        else
        {
            atxpic(0) = 2;
            atxpic(1) = 216;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"うっ！ヘビに噛まれた。"s);
            snd(2);
            damage_hp(cdata.player(), cdata.player().max_hp * 10 / 100, -10);
        }
        atxthrough = 1;
        goto label_1875;
    }
    if (rnd(3) == 0)
    {
        if (rnd(3))
        {
            atxpic(0) = 2;
            atxpic(1) = 210;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"痛っ！蚊に刺された。"s);
            snd(2);
            damage_hp(cdata.player(), cdata.player().max_hp * 5 / 100, -10);
        }
        else
        {
            atxpic(0) = 2;
            atxpic(1) = 216;
            atxpic(2) = 96;
            atxpic(3) = 96;
            noteadd(u8"うっ！ヘビに噛まれた。"s);
            snd(2);
            damage_hp(cdata.player(), cdata.player().max_hp * 10 / 100, -10);
        }
        atxthrough = 1;
        goto label_1875;
    }
    if (rnd(2) == 0)
    {
        atxpic(0) = 1;
        atxpic(1) = 220;
        atxpic(2) = 96;
        atxpic(3) = 96;
        noteadd(u8"宝箱がある。"s);
        list(0, listmax) = 1;
        listn(0, listmax) = u8"錠を解体する("s
            + i18n::_(u8"ability", std::to_string(158), u8"name") + u8": "s
            + sdata(158, 0) + u8")"s;
        ++listmax;
        list(0, listmax) = 3;
        listn(0, listmax) = u8"叩き割る(筋力: "s + sdata(10, 0) + u8")"s;
        ++listmax;
        atxinfon(1) = u8"行動回数残り "s + atxap + u8"回\n"s;
        chatesc = 1;
        txtadvmsgfix = 0;
        txtadvscreenupdate = 1;
        casino_choose_card();
        atxinit();
        goto label_1875;
    }
    if (rnd(2) == 0)
    {
        p = random_material(atxlv);
        atxpic(0) = 1;
        atxpic(1) = matref(2, p);
        atxpic(2) = 96;
        atxpic(3) = 96;
        snd(41);
        mat(p) += 1;
        noteadd(
            "@BL"
            + i18n::s.get("core.locale.casino.you_get", 1, matname(p), mat(p)));
        atxthrough = 1;
        goto label_1875;
    }
    if (rnd(3) == 0)
    {
        noteadd(u8"何も見つからなかった…"s);
        atxthrough = 1;
        goto label_1875;
    }
    noteadd(u8"何も見つからなかった…"s);
    atxthrough = 1;
    goto label_1875;
}

void casino_adv_finish_search()
{
    atxinit();
    if (cdata.player().hp >= 0)
    {
        noteadd(u8"探索を終えた。"s);
        list(0, listmax) = 0;
        listn(0, listmax) = u8"戻る"s;
        ++listmax;
    }
    else
    {
        noteadd(u8"ぐふ…"s);
        list(0, listmax) = 0;
        listn(0, listmax) = u8"(断末魔の叫び)"s;
        ++listmax;
    }
    atxinfon(1) = u8"行動回数残り "s + atxap + u8"回\n"s;
    chatesc = 0;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    casino_acquire_items();
    return;
}

void casino_wrapper()
{
    bool finished = false;
    while (!finished)
    {
        finished = casino_start();
    }
}

bool casino_start()
{
    bool finished = false;
    atxbg = u8"bg14"s;
    mattile = -1;
    atxinfon(0) = i18n::s.get("core.locale.casino.window.title");
    atxinit();
    noteadd(i18n::s.get_enum("core.locale.casino.window.desc", 0));
    noteadd(i18n::s.get_enum("core.locale.casino.window.desc", 1));
    noteadd(i18n::s.get_enum("core.locale.casino.window.desc", 2));
    if (gdata_used_casino_once == 0)
    {
        noteadd(""s);
        noteadd(i18n::s.get_enum("core.locale.casino.window.first", 0));
        noteadd(i18n::s.get_enum("core.locale.casino.window.first", 1));
        gdata_used_casino_once = 1;
        snd(41);
        mat(1) += 10;
        noteadd(
            "@BL"
            + i18n::s.get(
                  "core.locale.casino.you_get", 10, matname(1), mat(1)));
    }
    atxinfon(1) = i18n::s.get("core.locale.casino.chips_left", mat(1)) + "\n";
    atxinfon(2) = "";
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.casino.window.choices.leave");
    ++listmax;
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.locale.casino.window.choices.blackjack");
    ++listmax;
    chatesc = 0;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    if (rtval == 0)
    {
        casino_acquire_items();
        return true;
    }
    else if (rtval == 1)
    {
        while (!finished)
        {
            finished = casino_blackjack();
        }
        return false;
    }
    return true;
}

bool casino_blackjack()
{
    int stake = 0;
    int winrow = 0;
    int cardround = 0;
    int winner = 0;
    atxinit();
    noteadd(i18n::s.get_enum("core.locale.casino.blackjack.desc", 0));
    noteadd(i18n::s.get_enum("core.locale.casino.blackjack.desc", 1));
    noteadd(i18n::s.get_enum("core.locale.casino.blackjack.desc", 2));
    noteadd(i18n::s.get_enum("core.locale.casino.blackjack.desc", 3));
    atxinfon(1) = i18n::s.get("core.locale.casino.chips_left", mat(1)) + "\n";
    atxinfon(2) = "";
    if (mat(1) <= 0)
    {
        noteadd(""s);
        noteadd(i18n::s.get("core.locale.casino.blackjack.no_chips"));
    }
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.casino.blackjack.choices.quit");
    ++listmax;
    if (mat(1) >= 1)
    {
        list(0, listmax) = 1;
        listn(0, listmax) =
            i18n::s.get("core.locale.casino.blackjack.choices.bet", 1);
        ++listmax;
    }
    if (mat(1) >= 5)
    {
        list(0, listmax) = 5;
        listn(0, listmax) =
            i18n::s.get("core.locale.casino.blackjack.choices.bet", 5);
        ++listmax;
    }
    if (mat(1) >= 20)
    {
        list(0, listmax) = 20;
        listn(0, listmax) =
            i18n::s.get("core.locale.casino.blackjack.choices.bet", 20);
        ++listmax;
    }
    chatesc = 0;
    txtadvmsgfix = 0;
    txtadvscreenupdate = 1;
    casino_choose_card();
    if (rtval == 0)
    {
        return true;
    }
    stake = rtval;
    winrow = 0;
    cardround = 0;
    autosave = 1 * (gdata_current_map != mdata_t::MapId::show_house);
    for (int cnt = 0;; ++cnt)
    {
        screenupdate = -1;
        update_screen();
        atxinit();
        if (cnt == 0)
        {
            mat(1) -= stake;
            noteadd(i18n::s.get(
                "core.locale.casino.you_lose", stake, matname(1), mat(1)));
        }
        if (cardround == 0)
        {
            nojoker = 1;
            initcard(60, 160);
            cardplayerinit(2, 5);
            cardplayeradd(0, 220, 124);
            cardplayeradd(1, 220, 240);
        }
        font(14 - en * 2, snail::Font::Style::bold);
        color(255, 255, 255);
        pos(152, 154);
        mes(i18n::s.get("core.locale.casino.blackjack.game.dealer"));
        pos(152, 270);
        mes(i18n::s.get("core.locale.casino.blackjack.game.you"));
        color(0, 0, 0);
        showcardpile();
        showcardholder();
        showcard();
        if (cardround == 0)
        {
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                int stat = servecard(cnt % 2);
                if (cnt != 2)
                {
                    opencard2(stat);
                }
            }
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (cpcardnum(0) >= 5)
                {
                    break;
                }
                if (cpscore(0) < cpscore(1) || cpscore(0) - rnd(5) <= 11)
                {
                    int stat = servecard(0);
                    opencard2(stat);
                    --cnt;
                    continue;
                }
            }
        }
        noteadd(i18n::s.get(
            "core.locale.casino.blackjack.game.your_hand", cpscore(1)));
        if (cardround == -1)
        {
            noteadd(i18n::s.get(
                "core.locale.casino.blackjack.game.dealers_hand", cpscore(0)));
            winner = -1;
            if (cpscore(0) <= 21)
            {
                if (cpscore(1) > 21 || cpscore(0) > cpscore(1))
                {
                    winner = 0;
                }
            }
            if (cpscore(1) <= 21)
            {
                if (cpscore(0) > 21 || cpscore(1) > cpscore(0))
                {
                    winner = 1;
                }
            }
            if (winner == -1)
            {
                noteadd(i18n::s.get(
                    "core.locale.casino.blackjack.game.result.draw"));
            }
            if (winner == 0)
            {
                noteadd(i18n::s.get(
                    "core.locale.casino.blackjack.game.result.lose"));
            }
            if (winner == 1)
            {
                noteadd(i18n::s.get(
                    "core.locale.casino.blackjack.game.result.win"));
            }
        }
        atxinfon(1) =
            i18n::s.get("core.locale.casino.chips_left", mat(1)) + "\n";
        atxinfon(2) =
            i18n::s.get("core.locale.casino.blackjack.game.bets", stake) + " "
            + i18n::s.get("core.locale.casino.blackjack.game.wins", winrow);
        if (cardround == -1)
        {
            if (winner == 1)
            {
                ++winrow;
            }
            if (winner != 0)
            {
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.locale.casino.blackjack.game.result.choices.next_"
                    "round");
                ++listmax;
            }
            if (winner == 0)
            {
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.locale.casino.blackjack.game.result.choices.leave");
                ++listmax;
            }
            chatesc = -1;
            txtadvmsgfix = 240;
            txtadvscreenupdate = 0;
            casino_choose_card();
            if (winner == 0)
            {
                break;
            }
            cardround = 0;
            continue;
        }
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.casino.blackjack.game.choices.stay");
        ++listmax;
        if (pileremain() > 10)
        {
            if (cpcardnum(1) < 5)
            {
                list(0, listmax) = 1;
                listn(0, listmax) = i18n::s.get(
                    "core.locale.casino.blackjack.game.choices.hit");
                ++listmax;
            }
            list(0, listmax) = 2;
            listn(0, listmax) = i18n::s.get(
                "core.locale.casino.blackjack.game.choices.cheat",
                sdata(12, 0));
            ++listmax;
        }
        chatesc = -1;
        txtadvmsgfix = 240;
        txtadvscreenupdate = 0;
        casino_choose_card();
        if (rtval == 0)
        {
            opencard2(cpblackcard(0));
            cardround = -1;
            continue;
        }
        if (rtval == 1)
        {
            int stat = servecard(1);
            p = stat;
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                if (cpscore(1) >= 22)
                {
                    if (pileremain() > 10)
                    {
                        if (rnd(sdata(19, 0)) > 40)
                        {
                            txt(
                                i18n::s.get("core.locale.casino.blackjack.game."
                                            "bad_feeling"));
                            trashcard(p);
                            int stat = servecard(1);
                            p = stat;
                        }
                    }
                }
            }
            opencard2(p);
        }
        if (rtval == 2)
        {
            trashcard(lastcard(1));
            int stat = servecard(1);
            opencard2(stat);
            p = 20;
            if (stake == 5)
            {
                p = 40;
            }
            if (stake == 20)
            {
                p = 60;
            }
            if (rnd(sdata(12, 0)) < rnd(p(0)))
            {
                atxinit();
                noteadd(i18n::s.get(
                    "core.locale.casino.blackjack.game.cheat.dialog"));
                atxinfon(1) =
                    i18n::s.get("core.locale.casino.chips_left", mat(1)) + "\n";
                atxinfon(2) =
                    i18n::s.get("core.locale.casino.blackjack.game.bets", stake)
                    + " "
                    + i18n::s.get(
                          "core.locale.casino.blackjack.game.wins", winrow);
                winrow = 0;
                txt(i18n::s.get(
                    "core.locale.casino.blackjack.game.cheat.text"));
                modify_karma(cdata.player(), -5);
                list(0, listmax) = 0;
                listn(0, listmax) = i18n::s.get(
                    "core.locale.casino.blackjack.game.cheat.response");
                ++listmax;
                chatesc = -1;
                txtadvmsgfix = 0;
                txtadvscreenupdate = 1;
                casino_choose_card();
                break;
            }
        }
        ++cardround;
    }
    if (winrow > 0)
    {
        atxinit();
        noteadd(i18n::s.get(
            "core.locale.casino.blackjack.game.total_wins", winrow));
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            i = 2;
            if (winrow > 2)
            {
                i = 3;
            }
            if (winrow > 7)
            {
                if (stake >= 5)
                {
                    i = 4;
                }
            }
            if (winrow > 15)
            {
                if (stake >= 20)
                {
                    i = 5;
                }
            }
            flt(calcobjlv(rnd(stake + winrow * 2) + winrow * 3 / 2 + stake / 2),
                i);
            flttypemajor = choice(fsetwear);
            itemcreate(-1, 0, -1, -1, 0);
            if (inv[ci].number() == 0)
            {
                --cnt;
                continue;
            }
        }
        snd(41);
        noteadd(
            "@GR"
            + i18n::s.get("core.locale.casino.blackjack.game.loot", inv[ci]));
        if (winrow > 3)
        {
            // Potion of cure corruption
            if (winrow + 1 > rnd(10))
            {
                flt();
                itemcreate(-1, 559, -1, -1, 0);
                snd(41);
                noteadd(
                    "@GR"
                    + i18n::s.get(
                          "core.locale.casino.blackjack.game.loot", inv[ci]));
            }
        }
        list(0, listmax) = 0;
        listn(0, listmax) =
            i18n::s.get("core.locale.casino.blackjack.game.leave");
        ++listmax;
        chatesc = 0;
        txtadvmsgfix = 0;
        txtadvscreenupdate = 1;
        casino_choose_card();
        winrow = 0;
    }
    return true;
}

} // namespace elona
