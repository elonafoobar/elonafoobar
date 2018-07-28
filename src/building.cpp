#include "building.hpp"
#include "ability.hpp"
#include "activity.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "itemgen.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "race.hpp"
#include "random.hpp"
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
    if (mdata_map_type != mdata_t::map_type_t::world_map)
    {
        txt(i18n::s.get("core.locale.building.can_only_use_in_world_map"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    cell_featread(cdata[0].position.x, cdata[0].position.y);
    if (feat(0) != 0)
    {
        txt(i18n::s.get("core.locale.building.cannot_build_it_here"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    area = -1;
    for (int cnt = 300; cnt < 450; ++cnt)
    {
        if (adata(16, cnt) == mdata_t::map_id_t::random_dungeon)
        {
            area = cnt;
            break;
        }
    }
    if (area == -1)
    {
        txt(i18n::s.get("core.locale.building.cannot_build_anymore"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    txt(i18n::s.get("core.locale.building.really_build_it_here"));
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
        gdata_pc_x_in_world_map = adata(1, 7);
        gdata_pc_y_in_world_map = adata(2, 7);
        snd(58);
        txtef(2);
        txt(i18n::s.get("core.locale.building.built_new_house"));
        msg_halt();
        snd(49);
        return turn_result_t::exit_map;
    }
    ctrl_file(file_operation_t::_13);
    p = area;
    adata(1, p) = cdata[0].position.x;
    adata(2, p) = cdata[0].position.y;
    adata(0, p) = mdata_t::map_type_t::player_owned;
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
        adata(16, p) = mdata_t::map_id_t::museum;
        adata(15, p) = 151;
        adata(21, p) = 1;
    }
    if (inv[ci].id == 522)
    {
        adata(16, p) = mdata_t::map_id_t::shop;
        adata(15, p) = 150;
        adata(21, p) = 1;
    }
    if (inv[ci].id == 542)
    {
        adata(16, p) = mdata_t::map_id_t::crop;
        adata(15, p) = 152;
        adata(21, p) = 2;
    }
    if (inv[ci].id == 543)
    {
        adata(16, p) = mdata_t::map_id_t::storage_house;
        adata(15, p) = 153;
        adata(21, p) = 1;
    }
    if (inv[ci].id == 572)
    {
        adata(16, p) = mdata_t::map_id_t::ranch;
        adata(15, p) = 154;
        adata(21, p) = 2;
        adata(12, p) = 1;
    }
    if (inv[ci].id == 712)
    {
        adata(16, p) = mdata_t::map_id_t::your_dungeon;
        adata(15, p) = 138;
        adata(21, p) = 1;
        adata(12, p) = 1;
    }
    s = i18n::s.get_enum("core.locale.building.names", inv[ci].id);
    snd(58);
    txtef(5);
    txt(i18n::s.get("core.locale.building.built_new", s(0)));
    label_1749();
    --inv[ci].number;
    cell_refresh(inv[ci].position.x, inv[ci].position.y);
    return turn_result_t::turn_end;
}

void addbuilding(int prm_1082, int prm_1083, int prm_1084, int prm_1085)
{
    int p_at_m194 = 0;
    p_at_m194 = -1;
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        if (bddata(0, prm_1082, cnt) == 0)
        {
            p_at_m194 = cnt;
            break;
        }
    }
    if (p_at_m194 == -1)
    {
        return;
    }
    bddata(0, prm_1082, p_at_m194) = prm_1083;
    bddata(1, prm_1082, p_at_m194) = prm_1084;
    bddata(2, prm_1082, p_at_m194) = prm_1085;
    bddata(3, prm_1082, p_at_m194) = bdref(0, prm_1083) + 363;
    return;
}

turn_result_t show_house_board()
{
    txtnew();
    if (mdata_map_type != mdata_t::map_type_t::player_owned)
    {
        ++msgdup;
        txt(i18n::s.get("core.locale.building.house_board.only_use_in_home"));
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    p(0) = 0;
    p(1) = 0;
    p(2) = 0;
    for (const auto& cnt : items(-1))
    {
        ++p(2);
        if (inv[cnt].number != 0)
        {
            if (the_item_db[inv[cnt].id]->category != 60000)
            {
                ++p;
            }
            else
            {
                ++p(1);
            }
        }
    }
    if (mdata_map_max_item_count != 0)
    {
        p(2) = mdata_map_max_item_count;
    }
    txt(i18n::s.get(
        "core.locale.building.house_board.item_count",
        mapname(gdata_current_map),
        p(0),
        p(1),
        p(2)));
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        if (getworker(gdata_current_map) != -1)
        {
            txt(i18n::s.get(
                "core.locale.building.shop.current_shopkeeper",
                cdata[getworker(gdata_current_map)]));
        }
        else
        {
            txt(i18n::s.get(
                "core.locale.building.shop.no_assigned_shopkeeper"));
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
    {
        if (getworker(gdata_current_map) != -1)
        {
            txt(i18n::s.get(
                "core.locale.building.ranch.current_breeder",
                cdata[getworker(gdata_current_map)]));
        }
        else
        {
            txt(i18n::s.get("core.locale.building.ranch.no_assigned_breeder"));
        }
    }
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
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
        txt(i18n::s.get(
            "core.locale.building.home.staying.count",
            p(0),
            gdata_home_scale + 2));
    }
    txtnew();
    txt(i18n::s.get("core.locale.building.house_board.what_do"));
    p = 0;
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
    {
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.building.house_board.choices.assign_a_shopkeeper"),
            u8"null"s,
            ""s + 4);
        if (mdata_map_max_item_count < 400)
        {
            ELONA_APPEND_PROMPT(
                i18n::s.get(
                    "core.locale.building.house_board.choices.extend",
                    calcshopreform()),
                u8"null"s,
                ""s + 5);
        }
    }
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::ranch)
    {
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.building.house_board.choices.assign_a_breeder"),
            u8"null"s,
            ""s + 4);
    }
    ELONA_APPEND_PROMPT(
        i18n::s.get("core.locale.building.house_board.choices.design"),
        u8"null"s,
        ""s + 0);
    if (gdata_current_map == mdata_t::map_id_t::your_home)
    {
        ELONA_APPEND_PROMPT(
            i18n::s.get("core.locale.building.house_board.choices.home_rank"),
            u8"null"s,
            ""s + 2);
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.building.house_board.choices.allies_in_your_home"),
            u8"null"s,
            ""s + 4);
        if (gdata_current_dungeon_level == 1)
        {
            ELONA_APPEND_PROMPT(
                i18n::s.get("core.locale.building.house_board.choices.recruit_a_servant"),
                u8"null"s,
                ""s + 6);
        }
        ELONA_APPEND_PROMPT(
            i18n::s.get(
                "core.locale.building.house_board.choices.move_a_stayer"),
            u8"null"s,
            ""s + 3);
    }
    int stat = show_prompt(promptx, prompty, 240);
    if (stat == -1)
    {
        update_screen();
        return turn_result_t::pc_turn_user_error;
    }
    rtval = stat;
    switch (rtval)
    {
    case 0: start_home_map_mode(); break;
    case 2: show_home_value(); break;
    case 3: prompt_move_ally(); break;
    case 4: prompt_ally_staying(); break;
    case 5: try_extend_shop(); break;
    case 6: prompt_hiring(); break;
    }
    tlocinitx = 0;
    tlocinity = 0;
    screenupdate = -1;
    update_screen();
    return turn_result_t::show_house_board;
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
        txt(i18n::s.get("core.locale.building.home.hire.too_many_guests"));
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
            hire = rnd(isethire.size());
        }
        dbid = isethire(hire);
        randomize(gdata_day + cnt);
        flt(20);
        int stat = chara_create(-1, dbid, -3, 0);
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
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.armory", cdata[rc]);
            }
            if (p == 1)
            {
                cdata[rc].character_role = 1006;
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.general_store", cdata[rc]);
            }
            if (p == 2)
            {
                cdata[rc].character_role = 1004;
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.magic_store", cdata[rc]);
            }
            if (p == 3)
            {
                cdata[rc].character_role = 1008;
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.goods_store", cdata[rc]);
            }
            if (p == 4)
            {
                cdata[rc].character_role = 1001;
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.armory", cdata[rc]);
            }
            if (p == 5)
            {
                cdata[rc].character_role = 1007;
                cdatan(0, rc) = i18n::s.get(
                    "core.locale.building.guests.blackmarket", cdata[rc]);
            }
            randomize();
            cdata[rc].shop_rank = rnd(15) + 1;
        }
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cnt == rc)
            {
                continue;
            }
            if (cdata[cnt].state != 0 && cdatan(0, cnt) == cdatan(0, rc))
            {
                chara_vanquish(rc);
            }
        }
    }
    randomize();
    txtnew();
    txt(i18n::s.get("core.locale.building.home.hire.who"));
    allyctrl = 1;
    int stat = show_hire_menu();
    if (stat != -1)
    {
        tc = stat;
        txtnew();
        if (cdata[0].gold < calchirecost(tc) * 20)
        {
            txt(i18n::s.get("core.locale.building.not_enough_money"));
        }
        else
        {
            snd(12);
            cdata[0].gold -= calchirecost(tc) * 20;
            await(config::instance().animewait * 10);
            cdata[tc].state = 1;
            lua::lua->on_chara_loaded(cdata[tc]);
            txtef(2);
            txt(i18n::s.get(
                "core.locale.building.home.hire.you_hire", cdata[tc]));
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
    prepare_hourse_board_tiles();
    txtnew();
    txt(i18n::s.get("core.locale.building.home.design.help"));
    tlocinitx = cdata[0].position.x;
    tlocinity = cdata[0].position.y;
    tile = 0;
    while (1)
    {
        await(config::instance().wait1);
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
    load_background_variants(4);
    gsel(0);
    snd(26);
    pagesize = 0;
    keyrange = 0;
    key_list = key_cancel;

    s(0) = i18n::s.get("core.locale.building.home.rank.title");
    s(1) = i18n::s.get("core.locale.building.home.rank.enter_key");
    windowshadow = 1;
    display_window((windoww - 440) / 2 + inf_screenx, winposy(360), 440, 360);
    display_topic(
        i18n::s.get("core.locale.building.home.rank.value"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.building.home.rank.heirloom_rank"),
        wx + 28,
        wy + 106);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    pos(wx + ww / 4, wy + wh / 2);
    gmode(4, 50);
    gcopy_c(4, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
    calc_home_rank();
    s(0) = i18n::s.get("core.locale.building.home.rank.type.base");
    s(1) = i18n::s.get("core.locale.building.home.rank.type.deco");
    s(2) = i18n::s.get("core.locale.building.home.rank.type.heir");
    s(3) = i18n::s.get("core.locale.building.home.rank.type.total");
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
            bmes(
                i18n::s.get("core.locale.building.home.rank.star"),
                x + 35 + cnt * 13 + en * 8,
                y - 2,
                {255, 255, 50});
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

        draw_item_with_portrait_scale_height(inv[p], wx + 37, cnt * 16 + wy + 138);

        pos(wx + 68, cnt * 16 + wy + 138);
        mes(i18n::s.get(
            "core.locale.building.home.rank.place", cnvrank(10 - cnt)));
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
    while (true)
    {

        txtnew();
        txt(i18n::s.get("core.locale.building.home.move.who"));
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
            txt(i18n::s.get(
                "core.locale.building.home.move.dont_touch_me", cdata[stat]));
            break;
        }
        tchome = stat;
        tc = stat;
        snd(20);
    label_1718_internal:
        txtnew();
        txt(i18n::s.get("core.locale.building.home.move.where", cdata[stat]));
        {
            int stat = target_position();
            if (stat == -1)
            {
                continue;
            }
        }
        if (chipm(7, map(tlocx, tlocy, 0)) & 4 || map(tlocx, tlocy, 1) != 0)
        {
            txt(i18n::s.get("core.locale.building.home.move.invalid"));
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
        txt(i18n::s.get("core.locale.building.home.move.is_moved", cdata[tc]));
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
                if (gdata_current_map == mdata_t::map_id_t::your_home)
                {
                    cdata[c].current_map = 0;
                    txt(i18n::s.get(
                        "core.locale.building.home.staying.remove.ally",
                        cdata[c]));
                }
                else
                {
                    removeworker(gdata_current_map);
                    txt(i18n::s.get(
                        "core.locale.building.home.staying.remove.worker",
                        cdata[c]));
                }
            }
            else
            {
                if (gdata_current_map == mdata_t::map_id_t::your_home)
                {
                    cdata[c].initial_position.x = cdata[c].position.x;
                    cdata[c].initial_position.y = cdata[c].position.y;
                    txt(i18n::s.get(
                        "core.locale.building.home.staying.add.ally",
                        cdata[c]));
                }
                else
                {
                    removeworker(gdata_current_map);
                    txt(i18n::s.get(
                        "core.locale.building.home.staying.add.worker",
                        cdata[c]));
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
        txt(i18n::s.get("core.locale.building.not_enough_money"));
    }
    else
    {
        snd(12);
        cdata[0].gold -= calcshopreform();
        mdata_map_max_item_count = clamp(mdata_map_max_item_count + 10, 1, 400);
        txtef(2);
        txt(i18n::s.get("core.locale.building.shop.extend", mdata_map_max_item_count));
    }
}

void prepare_hourse_board_tiles()
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
        if (adata(16, cnt) == mdata_t::map_id_t::shop)
        {
            area = cnt;
            mid = ""s + area + u8"_"s + 101;
            show_shop_log();
        }
    }
    mid = midbk;
    if (adata(16, gdata_current_map) == mdata_t::map_id_t::shop)
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
    std::string shop_mark =
        u8"["s + i18n::s.get("core.locale.building.shop.info") + u8"]"s;
    if (worker == -1)
    {
        txt(shop_mark
            + i18n::s.get("core.locale.building.shop.log.no_shopkeeper"));
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
    tmpload(filesystem::u8path(u8"shop5.s2"));
    if (fs::exists(filesystem::dir::tmp() / u8"shop5.s2"))
    {
        ctrl_file(file_operation2_t::_3, u8"shop5.s2");
    }
    else
    {
        for (const auto& cnt : items(-1))
        {
            item_remove(inv[cnt]);
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
            nostack = 1;
            int stat = itemcreate(-1, 0, -1, -1, 0);
            if (stat == 0)
            {
                f = 0;
                break;
            }
            if (inv[ci].value > elona::stoi(listn(1, cnt2)) * 2)
            {
                item_stack(-1, ci);
                f = 1;
                break;
            }
            else
            {
                item_remove(inv[ci]);
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
        if (!config::instance().hideshopresult)
        {
            txt(shop_mark
                + i18n::s.get(
                      "core.locale.building.shop.log.could_not_sell",
                      customer,
                      cdata[worker]));
        }
    }
    else
    {
        if (!config::instance().hideshopresult)
        {
            s = i18n::s.get("core.locale.building.shop.log.gold", income(0));
            if (income(1) != 0)
            {
                s += i18n::s.get(
                    "core.locale.building.shop.log.and_items", income(1));
            }
            snd(24);
            txtef(5);
            txt(shop_mark
                + i18n::s.get(
                      "core.locale.building.shop.log.sold_items",
                      customer,
                      cdata[worker],
                      sold,
                      s(0)));
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
    mdata_map_max_crowd_density = (100 - gdata(125) / 100) / 4 + 1;
    for (int cnt = 0, cnt_end = (mdata_map_height); cnt < cnt_end; ++cnt)
    {
        y = cnt;
        for (int cnt = 0, cnt_end = (mdata_map_width); cnt < cnt_end; ++cnt)
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
        if (x < 0 || x >= mdata_map_width || y < 0 || y >= mdata_map_height)
        {
            continue;
        }
        cell_refresh(x, y);
    }
    return;
}

void calc_collection_value(bool val0)
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
        if (draw_get_rect_chara(cdata[56].image % 1000)->height > inf_tiles)
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
        calc_collection_value(inv[cnt].id != 503);
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
        txt(i18n::s.get(
            "core.locale.building.museum.rank_change",
            cnvrank(rankorg / 100),
            cnvrank(rankcur / 100),
            ranktitle(3),
            rankn(10, 3)));
    }
    mdata_map_max_crowd_density = (100 - gdata(123) / 100) / 2 + 1;
    return;
}


void calc_hairloom_value(int val0)
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

void calc_home_rank()
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
        calc_hairloom_value(cnt);
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
        txt(i18n::s.get(
            "core.locale.building.home.rank.change",
            gdata(77) / 100,
            gdata(78) / 100,
            cnvrank(rankorg / 100),
            cnvrank(rankcur / 100),
            ranktitle(4),
            rankn(10, 4)));
    }
    return;
}

int cbreeder(int prm_984)
{
    std::string s_at_m173;
    int p_at_m173 = 0;
    s_at_m173 = chara_refstr(cdata[prm_984].id, 8);
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
            int stat = chara_create(-1, dbid, 4 + rnd(11), 4 + rnd(8));
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
