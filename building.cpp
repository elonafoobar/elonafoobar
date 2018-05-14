#include "building.hpp"
#include "ability.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "item_db.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "race.hpp"
#include "ui.hpp"
#include "variables.hpp"

namespace elona
{

int sold = 0;
int rankorg = 0;
int rankcur = 0;

void initialize_home_adata()
{
    p = 7;
    adata(15, p) = 143;
    if (gdata_home_scale == 0)
    {
        adata(15, p) = 138;
    }
    if (gdata_home_scale == 4)
    {
        adata(15, p) = 148;
    }
    if (gdata_home_scale == 5)
    {
        adata(15, p) = 144;
    }
    if (gdata_home_scale != 0)
    {
        adata(1, p) = cdata[0].position.x;
        adata(2, p) = cdata[0].position.y;
    }
    adata(30, p) = gdata(850);
    return;
}

turn_result_t build_new_building()
{
    if (mdata(6) != 1)
    {
        txt(lang(
            u8"それはワールドマップでしか使えない。"s,
            u8"You can only use it in the world map."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    cell_featread(cdata[0].position.x, cdata[0].position.y);
    if (feat(0) != 0)
    {
        txt(lang(
            u8"その場所には建てられない。"s, u8"You can't build it here."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    area = -1;
    for (int cnt = 300; cnt < 450; ++cnt)
    {
        if (adata(16, cnt) == 0)
        {
            area = cnt;
            break;
        }
    }
    if (area == -1)
    {
        txt(lang(
            u8"もうこれ以上建物は建てられない。"s,
            u8"You can't build a building anymore."s));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    txt(lang(u8"本当にこの場所に建設する？ "s, u8"Really build it here? "s));
    ELONA_YES_NO_PROMPT();
    rtval = show_prompt(promptx, prompty, 160);
    if (rtval != 0)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    if (inv[ci].id == 344)
    {
        gdata_home_scale = inv[ci].param1;
        --inv[ci].number;
        cell_refresh(inv[ci].position.x, inv[ci].position.y);
        initialize_home_adata();
        std::string midbk = mid;
        mid = ""s + 7 + u8"_"s + 101;
        ctrl_file(file_operation_t::_12);
        mid = midbk;
        label_1749();
        levelexitby = 2;
        gdata_destination_map = 7;
        gdata_destination_dungeon_level = 1;
        gdata_pc_home_x = adata(1, 7);
        gdata_pc_home_y = adata(2, 7);
        snd(58);
        txtef(2);
        txt(lang(u8"新しい家を建てた！ "s, u8"You've built a new house!"s));
        msg_halt();
        snd(49);
        return turn_result_t::exit_map;
    }
    ctrl_file(file_operation_t::_13);
    p = area;
    adata(1, p) = cdata[0].position.x;
    adata(2, p) = cdata[0].position.y;
    adata(0, p) = 5;
    adata(11, p) = 1;
    adata(12, p) = 0;
    adata(18, p) = 3;
    adata(9, p) = 10000;
    adata(17, p) = 1;
    adata(10, p) = 1;
    adata(4, p) = 1;
    adata(3, p) = 8;
    adata(30, p) = gdata(850);
    if (inv[ci].id == 521)
    {
        adata(16, p) = 101;
        adata(15, p) = 151;
        adata(21, p) = 1;
        s = lang(u8"博物館"s, u8"museum"s);
    }
    if (inv[ci].id == 522)
    {
        adata(16, p) = 102;
        adata(15, p) = 150;
        adata(21, p) = 1;
        s = lang(u8"店"s, u8"shop"s);
    }
    if (inv[ci].id == 542)
    {
        adata(16, p) = 103;
        adata(15, p) = 152;
        adata(21, p) = 2;
        s = lang(u8"畑"s, u8"crop"s);
    }
    if (inv[ci].id == 543)
    {
        adata(16, p) = 104;
        adata(15, p) = 153;
        adata(21, p) = 1;
        s = lang(u8"倉庫"s, u8"storage"s);
    }
    if (inv[ci].id == 572)
    {
        adata(16, p) = 31;
        adata(15, p) = 154;
        adata(21, p) = 2;
        adata(12, p) = 1;
        s = lang(u8"牧場"s, u8"ranch"s);
    }
    if (inv[ci].id == 712)
    {
        adata(16, p) = 39;
        adata(15, p) = 138;
        adata(21, p) = 1;
        adata(12, p) = 1;
        s = lang(u8"ダンジョン"s, u8"dungeon"s);
    }
    snd(58);
    txtef(5);
    txt(lang(
        u8"あなたは"s + s + u8"を建設した！ "s,
        u8"You've built a "s + s + u8"!"s));
    label_1749();
    --inv[ci].number;
    cell_refresh(inv[ci].position.x, inv[ci].position.y);
    return turn_result_t::turn_end;
}

void prompt_hiring()
{
    txtnew();
    p = 0;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        if (cdata[cnt].state == 1 || cdata[cnt].state == 2)
        {
            if (cdata[cnt].character_role != 0)
            {
                ++p;
            }
        }
    }
    if (p >= gdata_home_scale + 2)
    {
        txt(lang(
                u8"家はすでに人であふれかえっている。"s,
                u8"You already have too many guests in your home."s));
        return;
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        randomize(gdata_day + cnt);
        if (rnd(2))
        {
            continue;
        }
        if (cnt == 0)
        {
            hire = 0;
        }
        else
        {
            hire = rnd(length(isethire));
        }
        dbid = isethire(hire);
        randomize(gdata_day + cnt);
        flt(20);
        int stat = characreate(-1, dbid, -3, 0);
        if (stat == 0)
        {
            continue;
        }
        cdata[rc].state = 10;
        cdata[rc].character_role = isethirerole(hire);
        if (cdata[rc].id == 1)
        {
            p = rnd(6);
            if (p == 0)
            {
                cdata[rc].character_role = 1001;
                cdatan(0, rc) = lang(
                    u8"武具店の"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of armory"s);
            }
            if (p == 1)
            {
                cdata[rc].character_role = 1006;
                cdatan(0, rc) = lang(
                    u8"雑貨屋の"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of general store"s);
            }
            if (p == 2)
            {
                cdata[rc].character_role = 1004;
                cdatan(0, rc) = lang(
                    u8"魔法店の"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of magic store"s);
            }
            if (p == 3)
            {
                cdata[rc].character_role = 1008;
                cdatan(0, rc) = lang(
                    u8"何でも屋の"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of goods store"s);
            }
            if (p == 4)
            {
                cdata[rc].character_role = 1001;
                cdatan(0, rc) = lang(
                    u8"武具店の"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of armory"s);
            }
            if (p == 5)
            {
                cdata[rc].character_role = 1007;
                cdatan(0, rc) = lang(
                    u8"ブラックマーケットの"s + cdatan(0, rc),
                    cdatan(0, rc) + u8" of blackmarket"s);
            }
            randomize();
            cdata[rc].shop_rank = rnd(15) + 1;
        }
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
             cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cnt == rc)
            {
                continue;
            }
            if (cdatan(0, cnt) == cdatan(0, rc))
            {
                chara_vanquish(rc);
            }
        }
    }
    randomize();
    txtnew();
    txt(lang(u8"誰を雇用する？"s, u8"Who do you want to hire?"s));
    allyctrl = 1;
    int stat = show_hire_menu();
    if (stat != -1)
    {
        tc = stat;
        txtnew();
        if (cdata[0].gold < calchirecost(tc) * 20)
        {
            txt(lang(
                    u8"お金が足りない…"s, u8"You don't have enough money..."s));
        }
        else
        {
            snd(12);
            cdata[0].gold -= calchirecost(tc) * 20;
            await(250);
            cdata[tc].state = 1;
            txtef(2);
            txt(lang(
                    cdatan(0, tc) + u8"を家に迎えた。"s,
                    u8"You hire "s + cdatan(0, tc) + u8"."s));
            snd(64);
        }
    }
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state == 10)
        {
            chara_vanquish(cnt);
        }
    }
    calccosthire();
}

void start_home_map_mode()
{
    int cxbk = cdata[0].position.x;
    int cybk = cdata[0].position.y;
    homemapmode = 1;
    label_1723();
    txtnew();
    txt(lang(
            u8"マウスの左クリックでタイルの敷設、右クリックでタイルの取得、移動キーでスクリーン移動、決定キーでタイル一覧、キャンセルキーで終了。"s,
            u8"Left click to place the tile, right click to pick the tile under your mouse cursor, movement keys to move current position, hit the enter key to show the list of tiles, hit the cancel key to exit."s));
    tlocinitx = cdata[0].position.x;
    tlocinity = cdata[0].position.y;
    tile = 0;
    while (1)
    {
        await();
        int stat = target_position();
        if (stat == -1)
        {
            break;
        }
        if ((chipm(7, tile) & 4) == 0)
        {
            map(tlocx, tlocy, 0) = tile;
            map(tlocx, tlocy, 2) = tile;
        }
        else
        {
            efid = 438;
            magic();
        }
        tlocinitx = tlocx;
        tlocinity = tlocy;
    }
    homemapmode = 0;
    cdata[0].position.x = cxbk;
    cdata[0].position.y = cybk;
}

void show_home_value()
{
    gsel(4);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        pos(cnt % 4 * 180, cnt / 4 * 300);
        picload(
            filesystem::dir::graphic() / (u8"g"s + (cnt + 1) + u8".bmp"),
            1);
    }
    gsel(0);
    snd(26);
    pagesize = 0;
    keyrange = 0;
    key_list = key_cancel;
    s(0) = lang(u8"家の情報"s, u8"Home Value"s);
    s(1) = lang(u8"決定ｷｰ,"s, u8"Enter key,"s) + strhint3;
    windowshadow = 1;
    display_window(
        (windoww - 440) / 2 + inf_screenx, winposy(360), 440, 360);
    display_topic(lang(u8"価値"s, u8"Value"s), wx + 28, wy + 36);
    display_topic(
        lang(u8"家宝ランク"s, u8"Heirloom Rank"s), wx + 28, wy + 106);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    gmode(4, 180, 300, 50);
    pos(wx + ww / 4, wy + wh / 2);
    grotate(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
    gmode(2);
    label_1730();
    s(0) = lang(u8"基本."s, u8"Base"s);
    s(1) = lang(u8"家具."s, u8"Deco"s);
    s(2) = lang(u8"家宝."s, u8"Heir"s);
    s(3) = lang(u8"総合."s, u8"Total"s);
    p(0) = gdata_basic_point_of_home_rank;
    p(1) = gdata(77);
    p(2) = gdata(78);
    p(3) = (p + p(1) + p(2)) / 3;
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        x = wx + 45 + cnt / 2 * 190;
        y = wy + 68 + cnt % 2 * 18;
        font(12 + sizefix - en * 2);
        pos(x, y);
        mes(s(cnt));
        font(14 - en * 2);
        for (int cnt = 0, cnt_end = cnt + (clamp(p(cnt) / 1000, 1, 10));
             cnt < cnt_end;
             ++cnt)
        {
            pos(x + 35 + cnt * 13 + en * 8, y - 2);
            bmes(lang(u8"★"s, u8"*"s), 255, 255, 50);
        }
    }
    font(12 + sizefix - en * 2);
    listmax = 10;
    sort_list_by_column1();
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        p = list(0, cnt);
        if (p == 0)
        {
            continue;
        }
        p(1) = inv[p].image % 1000;
        prepare_item_image(p(1), inv[p].color, inv[p].param1);
        pos(wx + 37, cnt * 16 + wy + 138);
        gmode(2, chipi(2, p(1)), chipi(3, p(1)));
        grotate(
            1,
            0,
            960,
            0,
            chipi(2, p(1)) * inf_tiles / chipi(3, p(1)),
            inf_tiles);
        pos(wx + 68, cnt * 16 + wy + 138);
        mes(""s + cnvrank((10 - cnt)) + lang(u8"位."s, ""s));
        pos(wx + 110, cnt * 16 + wy + 138);
        mes(itemname(p));
    }

        while (1)
        {
            redraw();
            await(config::instance().wait1);
            key_check();
            cursor_check();
            if (key == key_cancel)
            {
                break;
            }
        }
}

void prompt_move_ally()
{
    int tchome = 0;
    while(true) {

        txtnew();
        txt(lang(u8"誰を移動させる？"s, u8"Move who?"s));
        allyctrl = 0;
        int stat = show_hire_menu();
        if (stat == -1)
        {
            break;
        }
        if (cdata[stat].relationship <= -3)
        {
            txtnew();
            txtef(9);
            txt(cdatan(0, stat)
                + lang(u8"「触るな！」"s, (u8" "s + u8"\"Don't touch me!\""s)));
            break;
        }
        tchome = stat;
        tc = stat;
        snd(20);
    label_1718_internal:
        txtnew();
        txt(lang(
            cdatan(0, tc) + u8"をどこに移動させる？"s,
            u8"Where do you want to move "s + cdatan(0, tc) + u8"?"s));
        {
            int stat = target_position();
            if (stat == -1)
            {
                continue;
            }
        }
        if (chipm(7, map(tlocx, tlocy, 0)) & 4 || map(tlocx, tlocy, 1) != 0)
        {
            txt(lang(
                u8"その場所には移動させることができない。"s,
                u8"The location is invalid."s));
            goto label_1718_internal;
        }
        tc = tchome;
        map(cdata[tc].position.x, cdata[tc].position.y, 1) = 0;
        map(tlocx, tlocy, 1) = tc + 1;
        cdata[tc].position.x = tlocx;
        cdata[tc].initial_position.x = tlocx;
        cdata[tc].position.y = tlocy;
        cdata[tc].initial_position.y = tlocy;
        rowactend(tc);
        txtnew();
        txt(lang(
            cdatan(0, tc) + u8"を移動させた。"s,
            cdatan(0, tc) + u8" "s + is(tc) + u8" moved to the location."s));
        snd(43);
    }
}

void prompt_ally_staying()
{
    allyctrl = 3;
    {
        int stat = ctrl_ally();
        if (stat != -1)
        {
            int c = stat;
            snd(20);
            txtnew();
            if (getworker(gdata_current_map, c) == c)
            {
                if (gdata_current_map == 7)
                {
                    cdata[c].current_map = 0;
                    txt(lang(
                            cdatan(0, c) + u8"の滞在を取り消した。"s,
                            cdatan(0, c) + u8" "s + is(c)
                            + u8" no longer staying at your home."s));
                }
                else
                {
                    removeworker(gdata_current_map);
                    txt(lang(
                            cdatan(0, c) + u8"を役目から外した。"s,
                            u8"You remove "s + cdatan(0, c) + u8" from "s
                            + his(c) + u8" job."s));
                }
            }
            else
            {
                if (gdata_current_map == 7)
                {
                    cdata[c].initial_position.x = cdata[c].position.x;
                    cdata[c].initial_position.y = cdata[c].position.y;
                    txt(lang(
                            cdatan(0, c) + u8"を滞在させた。"s,
                            cdatan(0, c) + u8" stay"s + _s(c)
                            + u8" at your home now."s));
                }
                else
                {
                    removeworker(gdata_current_map);
                    txt(lang(
                            cdatan(0, c) + u8"を任命した。"s,
                            cdatan(0, c) + u8" take"s + _s(c)
                            + u8" charge of the job now."s));
                }
                cdata[c].current_map = gdata_current_map;
            }
        }
    }
}

void try_extend_shop()
{
    txtnew();
    if (cdata[0].gold < calcshopreform())
    {
        txt(lang(
                u8"お金が足りない…"s, u8"You don't have enough money..."s));
    }
    else
    {
        snd(12);
        cdata[0].gold -= calcshopreform();
        mdata(18) = clamp(mdata(18) + 10, 1, 400);
        txtef(2);
        txt(lang(
                u8"店を拡張した！これからは"s + mdata(18)
                + u8"個のアイテムを陳列できる。"s,
                u8"You extend your shop! You can display max of "s + mdata(18)
                + u8" items now!"s));
    }
}

void label_1723()
{
    p = 0;
    gsel(2);
    for (int cnt = 0; cnt < 2772; ++cnt)
    {
        f = 0;
        if (cnt < 231)
        {
            f = 1;
        }
        if (cnt >= 396)
        {
            if (cnt < 429)
            {
                f = 1;
            }
        }
        if (cnt >= 462)
        {
            if (cnt < 495)
            {
                f = 1;
            }
        }
        if (cnt >= 561)
        {
            if (cnt < 726)
            {
                f = 1;
            }
        }
        if (f == 0)
        {
            continue;
        }
        f = 1;
        pget(cnt % 33 * 48, cnt / 33 * 48);
        if (ginfo(16) == 0)
        {
            if (ginfo(17) == 0)
            {
                if (ginfo(18) == 0)
                {
                    f = 0;
                }
            }
        }
        if (chipm(0, cnt) == 2)
        {
            f = 0;
        }
        if (chipm(0, cnt) == 1)
        {
            f = 0;
        }
        if (chipm(1, cnt) == 5)
        {
            f = 0;
        }
        if (gdata_home_scale < 4)
        {
            if (chipm(0, cnt) == 3)
            {
                f = 0;
            }
        }
        if (f)
        {
            list(0, p) = cnt;
            ++p;
        }
        if (chipm(3, cnt) != 0)
        {
            cnt = cnt + chipm(3, cnt) - 1;
            continue;
        }
    }
    listmax = p;
    gsel(0);
    return;
}

void update_shop_and_report()
{
    area = -1;
    std::string midbk = mid;
    for (int cnt = 300; cnt < 450; ++cnt)
    {
        if (adata(16, cnt) == 102)
        {
            area = cnt;
            mid = ""s + area + u8"_"s + 101;
            show_shop_log();
        }
    }
    mid = midbk;
    if (adata(16, gdata_current_map) == 102)
    {
        update_shop();
    }
    return;
}

void show_shop_log()
{
    int shoplv = 0;
    int customer = 0;
    int dblistmax = 0;
    worker = getworker(area);
    if (worker == -1)
    {
        txt(lang(
            u8"[店]店には店番がいない。"s,
            u8"[Shop]You shop doesn't have a shopkeeper."s));
        return;
    }
    sold = 0;
    income(0) = 0;
    income(1) = 0;
    listmax = 0;
    shoplv = 100 - gdata(125) / 100;
    customer = 0;
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        customer += rnd(shoplv / 3 + 5);
    }
    customer = customer * (80 + sdata(17, worker) * 3 / 2) / 100;
    if (customer < 1)
    {
        customer = 1;
    }
    if (gdata_current_map != area)
    {
        ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
        ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
    }
    mode = 6;
    dblistmax = 0;
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number <= 0)
        {
            continue;
        }
        if (inv[cnt].id == 561)
        {
            continue;
        }
        if (inv[cnt].id == 562)
        {
            continue;
        }
        if (inv[cnt].id == 24)
        {
            continue;
        }
        if (inv[cnt].id == 54)
        {
            continue;
        }
        if (inv[cnt].id == 555)
        {
            continue;
        }
        if (inv[cnt].id == 344)
        {
            continue;
        }
        if (inv[cnt].weight < 0)
        {
            continue;
        }
        if (inv[cnt].quality >= 6)
        {
            continue;
        }
        if (inv[cnt].value < 50)
        {
            continue;
        }
        int category = the_item_db[inv[cnt].id]->category;
        if (category == 60000)
        {
            continue;
        }
        dblist(0, dblistmax) = cnt;
        dblist(1, dblistmax) = category;
        ++dblistmax;
    }
    for (int cnt = 0, cnt_end = (customer); cnt < cnt_end; ++cnt)
    {
        if (dblistmax == 0)
        {
            break;
        }
        p = rnd(dblistmax);
        ci = dblist(0, p);
        int category = dblist(1, p);
        int val0 = calcitemvalue(ci, 2);
        val0 = val0 * int((10 + std::sqrt(sdata(156, worker) * 200))) / 100;
        if (val0 <= 1)
        {
            continue;
        }
        if (rnd(val0) > shoplv * 100 + 500)
        {
            continue;
        }
        if (inv[ci].number <= 0)
        {
            continue;
        }
        if (rnd(8))
        {
            continue;
        }
        in = rnd(inv[ci].number) + 1;
        inv[ci].number -= in;
        sold += in;
        val0 = val0 * in;
        if (rnd(4) == 0)
        {
            list(0, listmax) = the_item_db[inv[ci].id]->level;
            list(1, listmax) = inv[ci].quality;
            listn(0, listmax) = std::to_string(category);
            listn(1, listmax) = std::to_string(val0);
            ++listmax;
        }
        else
        {
            income += val0;
        }
        if (area == gdata_current_map)
        {
            for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                if (cdata[cnt].continuous_action_id == 0
                    || cdata[cnt].continuous_action_turn == 0)
                {
                    continue;
                }
                if (cdata[cnt].continuous_action_item == ci)
                {
                    rowactend(cnt);
                }
            }
        }
    }
    mode = 0;
    if (gdata_current_map != area)
    {
        ctrl_file(file_operation2_t::_4, u8"inv_"s + mid + u8".s2");
    }
    else
    {
        ctrl_file(file_operation2_t::_4, u8"shoptmp.s2");
    }
    if (fs::exists(filesystem::dir::tmp() / u8"shop5.s2"))
    {
        ctrl_file(file_operation2_t::_3, u8"shop5.s2");
    }
    else
    {
        for (const auto& cnt : items(-1))
        {
            inv[cnt].number = 0;
        }
    }
    mode = 6;
    if (income != 0)
    {
        flt();
        itemcreate(-1, 54, -1, -1, income);
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt(list(0, cnt2), list(1, cnt2));
            flttypemajor = elona::stoi(listn(0, cnt2));
            int stat = itemcreate(-1, 0, -1, -1, 0);
            if (stat == 0)
            {
                f = 0;
                break;
            }
            if (inv[ci].value > elona::stoi(listn(1, cnt2)) * 2)
            {
                f = 1;
                break;
            }
            else
            {
                inv[ci].number = 0;
                if (cnt == 3)
                {
                    f = 0;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
        if (f == 0)
        {
            itemcreate(-1, 54, -1, -1, elona::stoi(listn(1, cnt)));
            income += elona::stoi(listn(1, cnt));
        }
        else
        {
            ++income(1);
        }
    }
    if (sold == 0)
    {
        if (config::instance().hideshopresult == 0)
        {
            txt(lang(
                u8"[店]"s + customer + u8"人が来客したが、"s + cdatan(0, worker)
                    + u8"はアイテムを一つも売れなかった。"s,
                u8"[Shop]"s + customer + u8" customers visited your shop but "s
                    + cdatan(0, worker) + u8" couldn't sell any item."s));
        }
    }
    else
    {
        if (config::instance().hideshopresult <= 1)
        {
            s = ""s + income + lang(u8"gold"s, u8" gold pieces"s);
            if (income(1) != 0)
            {
                s += lang(
                    u8"と"s + income(1) + u8"個のアイテム"s,
                    u8" and "s + income(1) + u8" items"s);
            }
            snd(24);
            txtef(5);
            txt(lang(
                u8"[店]"s + customer + u8"人の来客があり、"s + cdatan(0, worker)
                    + u8"は"s + sold + u8"個のアイテムを売却した。"s + s
                    + u8"が売り上げとして金庫に保管された。"s,
                u8"[Shop]"s + customer + u8" customers visited your shop and "s
                    + cdatan(0, worker) + u8" sold "s + sold + u8" items. "s
                    + cdatan(0, worker) + u8" put "s + s
                    + u8" in the shop strong box."s));
        }
        skillexp(156, worker, clamp(int(std::sqrt(income(0))) * 6, 25, 1000));
    }
    if (sold > (110 - gdata(125) / 100) / 10)
    {
        modrank(5, 30, 2);
    }
    mode = 0;
    ctrl_file(file_operation2_t::_4, u8"shop5.s2");
    ctrl_file(file_operation2_t::_3, u8"shoptmp.s2");
    return;
}

void update_shop()
{
    mdata(10) = (100 - gdata(125) / 100) / 4 + 1;
    for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
        {
            map(cnt, y, 4) = 0;
            map(cnt, y, 9) = 0;
        }
    }
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number <= 0)
        {
            continue;
        }
        x = inv[cnt].position.x;
        y = inv[cnt].position.y;
        if (x < 0 || x >= mdata(0) || y < 0 || y >= mdata(1))
        {
            continue;
        }
        cell_refresh(x, y);
    }
    return;
}

void label_1727(bool val0)
{
    rc = 56;
    fixlv = 2;
    dbmode = 3;
    access_character_info();
    ++dblist(val0 ? 1 : 0, cdata[56].id);
    if (fixlv == 6)
    {
        rtval = 70 + cdata[56].level;
    }
    else
    {
        rtval = cdata[56].level / 10 + 2;
        if (chipc(3, cdata[56].image % 1000) > inf_tiles)
        {
            rtval = rtval / 2 * 3 + 40;
        }
        p = the_character_db[cdata[56].id]->rarity / 1000;
        if (p < 80)
        {
            rtval = rtval + 80 - p;
        }
    }
    if (dblist(val0 ? 1 : 0, cdata[56].id) > 1)
    {
        rtval /= 3;
        if (rtval > 15)
        {
            rtval = 15;
        }
    }
    return;
}

void update_museum()
{
    rankorg = gdata(123);
    rankcur = 0;
    DIM3(dblist, 2, 800);
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (inv[cnt].id != 503 && inv[cnt].id != 504)
        {
            continue;
        }
        if (wpeek(map(inv[cnt].position.x, inv[cnt].position.y, 4), 0)
            != inv[cnt].image)
        {
            continue;
        }
        dbid = inv[cnt].subname;
        label_1727(inv[cnt].id != 503);
        if (inv[cnt].id == 503)
        {
            rankcur += rtval;
        }
        else
        {
            rankcur += rtval / 2;
        }
    }
    rankcur = 10000 - int(std::sqrt(rankcur) * 100);
    if (rankcur < 100)
    {
        rankcur = 100;
    }
    gdata(123) = rankcur;
    if (rankorg != rankcur)
    {
        if (rankorg > rankcur)
        {
            txtef(2);
        }
        else
        {
            txtef(8);
        }
        txtnew();
        txt(lang(
            u8"ランク変動("s + rankn(10, 3) + u8" "s + rankorg / 100
                + u8"位 → "s + rankcur / 100 + u8"位 )《"s + ranktitle(3)
                + u8"》"s,
            u8"Museum Rank:"s + cnvrank(rankorg / 100) + u8"->"s
                + cnvrank(rankcur / 100) + u8" Your museum is now known as <"s
                + ranktitle(3) + u8">."s));
    }
    mdata(10) = (100 - gdata(123) / 100) / 2 + 1;
    return;
}


void label_1729(int val0)
{
    int category = the_item_db[inv[val0].id]->category;
    if (category == 60000)
    {
        gdata(77) += clamp(inv[val0].value / 50, 50, 500);
    }
    p = inv[val0].value;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (category == 60000)
        {
            p /= 20;
            break;
        }
        if (category == 80000)
        {
            p /= 10;
            break;
        }
        if (category == 77000)
        {
            p /= 10;
            break;
        }
        p /= 1000;
    }
    int n = 0;
    if (p > list(1, n))
    {
        list(0, n) = val0;
        list(1, n) = p;
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            if (list(1, cnt) < list(1, n))
            {
                n = cnt;
            }
        }
    }
    return;
}

void label_1730()
{
    if (gdata_current_dungeon_level != 1)
    {
        return;
    }
    rankorg = gdata(124);
    rankcur = 0;
    gdata(77) = 0;
    gdata(78) = 0;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        list(0, cnt) = 0;
        list(1, cnt) = 0;
    }
    for (const auto& cnt : items(-1))
    {
        if (inv[cnt].number == 0)
        {
            continue;
        }
        if (wpeek(map(inv[cnt].position.x, inv[cnt].position.y, 4), 0)
            != inv[cnt].image)
        {
            continue;
        }
        label_1729(cnt);
    }
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (list(0, cnt) != 0)
        {
            gdata(78) += clamp(list(1, cnt), 100, 2000);
        }
    }
    if (gdata(77) > 10000)
    {
        gdata(77) = 10000;
    }
    if (gdata(78) > 10000)
    {
        gdata(78) = 10000;
    }
    rankcur =
        10000 - (gdata_basic_point_of_home_rank + gdata(77) + gdata(78)) / 3;
    if (rankcur < 100)
    {
        rankcur = 100;
    }
    gdata(124) = rankcur;
    if (rankorg != rankcur)
    {
        if (rankorg > rankcur)
        {
            txtef(2);
        }
        else
        {
            txtef(8);
        }
        txtnew();
        txt(lang(
            u8"家具("s + gdata(77) / 100 + u8"点) 家宝("s + gdata(78) / 100
                + u8"点) ランク変動("s + rankn(10, 4) + u8" "s + rankorg / 100
                + u8"位 → "s + rankcur / 100 + u8"位 )《"s + ranktitle(4)
                + u8"》"s,
            u8"Furniture Value:"s + gdata(77) / 100 + u8" Heirloom Value:"s
                + gdata(78) / 100 + u8" Home Rank:"s + cnvrank(rankorg / 100)
                + u8"->"s + cnvrank(rankcur / 100)
                + u8" Your home is now known as <"s + ranktitle(4) + u8">."s));
    }
    return;
}

int cbreeder(int prm_984)
{
    std::string s_at_m173;
    int p_at_m173 = 0;
    s_at_m173 = refchara_str(cdata[prm_984].id, 8);
    p_at_m173 = the_race_db[cdatan(2, prm_984)]->breed_power;
    p_at_m173 = p_at_m173 * 100 / (100 + cdata[prm_984].level * 5);
    return p_at_m173;
}

void update_ranch()
{
    worker = getworker(gdata_current_map);
    livestock = 0;
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (cdata[cnt].state != 1)
        {
            continue;
        }
        if (cdata[cnt].is_livestock() == 0)
        {
            continue;
        }
        ++livestock;
    }
    for (int cnt = 0, cnt_end = (renewmulti); cnt < cnt_end; ++cnt)
    {
        if (worker == -1)
        {
            goto label_1734_internal;
        }
        if (rnd(5000)
            > cbreeder(worker) * 100 / (100 + livestock * 20) - livestock * 2)
        {
            if (livestock != 0 || rnd(30) != 0)
            {
                goto label_1734_internal;
            }
        }
        flt(calcobjlv(cdata[worker].level), 1);
        if (rnd(2))
        {
            dbid = cdata[worker].id;
        }
        else
        {
            dbid = 0;
        }
        if (rnd(10) != 0)
        {
            fltnrace = cdatan(2, worker);
        }
        if (cdata[worker].id == 319)
        {
            dbid = 176;
        }
        {
            int stat = characreate(-1, dbid, 4 + rnd(11), 4 + rnd(8));
            if (stat != 0)
            {
                cdata[rc].is_livestock() = true;
                ++livestock;
            }
        }
    label_1734_internal:
        egg = 0;
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            if (cdata[cnt].is_livestock() == 0)
            {
                continue;
            }
            x = rnd(11) + 4;
            y = rnd(8) + 4;
            if (map(x, y, 4) != 0)
            {
                continue;
            }
            flt(calcobjlv(cdata[cnt].level), 2);
            p = rnd(5);
            f = 0;
            if (rnd(egg + 1) > 2)
            {
                continue;
            }
            if (livestock > 10)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock > 20)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock > 30)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (livestock > 40)
            {
                if (rnd(4) == 0)
                {
                    continue;
                }
            }
            if (p == 0)
            {
                if (rnd(60) == 0)
                {
                    f = 1;
                }
                if (cdatan(2, cnt) == u8"chicken"s)
                {
                    if (rnd(20) == 0)
                    {
                        f = 1;
                    }
                }
                if (f)
                {
                    ++egg;
                    int stat = itemcreate(-1, 573, x, y, 0);
                    if (stat)
                    {
                        inv[ci].subname = cdata[cnt].id;
                        inv[ci].weight = cdata[cnt].weight * 10 + 250;
                        inv[ci].value = clamp(
                            cdata[cnt].weight * cdata[cnt].weight / 10000,
                            200,
                            40000);
                    }
                }
                continue;
            }
            if (p == 1)
            {
                if (rnd(60) == 0)
                {
                    f = 1;
                }
                if (cdatan(2, cnt) == u8"sheep"s)
                {
                    if (rnd(20) == 0)
                    {
                        f = 1;
                    }
                }
                if (f)
                {
                    ++egg;
                    int stat = itemcreate(-1, 574, x, y, 0);
                    if (stat)
                    {
                        inv[ci].subname = cdata[cnt].id;
                    }
                }
                continue;
            }
            if (p == 2)
            {
                if (rnd(80) == 0)
                {
                    f = 1;
                }
                if (f)
                {
                    int stat = itemcreate(-1, 575, x, y, 0);
                    if (stat)
                    {
                        inv[ci].subname = cdata[cnt].id;
                        inv[ci].weight = cdata[cnt].weight * 40 + 300;
                        inv[ci].value = clamp(
                            cdata[cnt].weight * cdata[cnt].weight / 5000,
                            1,
                            20000);
                    }
                }
                continue;
            }
            if (p == 3)
            {
                if (rnd(80) == 0)
                {
                    f = 1;
                }
                if (f)
                {
                    dbid = 222;
                    if (rnd(2))
                    {
                        dbid = 45;
                    }
                    itemcreate(-1, dbid, x, y, 0);
                }
                continue;
            }
        }
    }
    return;
}

} // namespace elona
