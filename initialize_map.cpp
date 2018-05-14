#include "ability.hpp"
#include "audio.hpp"
#include "building.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "event.hpp"
#include "item.hpp"
#include "itemgen.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "mapgen.hpp"
#include "ui.hpp"
#include "variables.hpp"


namespace elona
{

turn_result_t initialize_map()
{
    int maxnpcbk = 0;
    elona_vector2<int> rolebk;
    int maxmedal = 0;
    elona_vector2<int> medalbk;
    int noaggrorefresh = 0;

    clear_damage_popups();

label_17401:
    mapupdate = 0;
    if (gdata_current_dungeon_level > adata(10, gdata_current_map))
    {
        gdata_current_dungeon_level = adata(10, gdata_current_map);
    }
    if (gdata_current_dungeon_level < adata(17, gdata_current_map))
    {
        gdata_current_dungeon_level = adata(17, gdata_current_map);
    }
    if (gdata_deepest_dungeon_level < gdata_current_dungeon_level)
    {
        if (gdata_current_map != 30)
        {
            gdata_deepest_dungeon_level = gdata_current_dungeon_level;
        }
    }
    if (adata(6, gdata_current_map) < gdata_current_dungeon_level)
    {
        adata(6, gdata_current_map) = gdata_current_dungeon_level;
    }
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cnt == 0)
        {
            continue;
        }
        if (cdata[cnt].current_map != 0)
        {
            if (cdata[cnt].current_map == gdata_current_map)
            {
                if (cdata[cnt].state == 9)
                {
                    cdata[cnt].state = 1;
                }
            }
        }
    }
    mid =
        ""s + gdata_current_map + u8"_"s + (100 + gdata_current_dungeon_level);
    if (mode == 3)
    {
        ctrl_file(file_operation_t::_1);
        ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
        goto label_1744_internal;
    }
    if (getkey(snail::key::backspace))
    {
        if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
        {
            int stat = dialog(
                lang(
                    u8"マップを初期化しますか？（注：ゲームに影響が出る可能性があります。エラーが出てマップが読み込めない場合のみ、必ず元のセーブのバックアップをとった上で実行してください。）"s,
                    u8"Initialize this map? (Warning, only do this if an error occurs when loading this map. Make sure make a backup of the current save folder before doing this.)"s),
                3);
            if (stat == 6)
            {
                ctrl_file(file_operation_t::_11);
            }
        }
    }
    if (fs::exists(filesystem::dir::tmp() / (u8"mdata_"s + mid + u8".s2")))
    {
        ctrl_file(file_operation_t::_1);
        if (mdata(7) == 0)
        {
            goto label_1741_internal;
        }
        if (mdata(19) != gdata(184) || (gdata(79) == 1 && mdata(6) == 1))
        {
            if (mdata(6) == 3 || mdata(6) == 2 || mdata(6) == 6
                || mdata(6) == 1)
            {
                mapupdate = 1;
                goto label_1741_internal;
            }
        }
        ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
        if (mode == 2)
        {
            map_placeplayer();
        }
        goto label_1742_internal;
    }
label_1741_internal:
    if (mapupdate == 1)
    {
        maxnpcbk = 0;
        DIM3(rolebk, 2, ELONA_MAX_CHARACTERS);
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].state == 0)
            {
                continue;
            }
            if ((cdata[cnt].character_role >= 1000
                 && cdata[cnt].character_role < 2000)
                || cdata[cnt].character_role == 2003)
            {
                rolebk(0, maxnpcbk) = cdata[cnt].character_role;
                rolebk(1, maxnpcbk) = cdata[cnt].shop_rank;
                ++maxnpcbk;
            }
        }
        maxmedal = 0;
        DIM3(medalbk, 2, 30);
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                x = cnt;
                if (map(x, y, 6) / 1000 % 100 == 32)
                {
                    if (maxmedal < 30)
                    {
                        medalbk(0, maxmedal) = x;
                        medalbk(1, maxmedal) = y;
                        ++maxmedal;
                    }
                }
            }
        }
    }
    mdata(3) = 0;
    for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
         ++cnt)
    {
        cdata[cnt].state = 0;
    }
    for (int cnt = 1320; cnt < 5480; ++cnt)
    {
        inv[cnt].number = 0;
    }
    DIM2(mdata, 100);
    mdata(11) = gdata_current_dungeon_level;
    mdata(2) = adata(4, gdata_current_map);
    mdata(12) = adata(18, gdata_current_map);
    mdata(6) = adata(0, gdata_current_map);
    mdata(9) = adata(9, gdata_current_map);
    mdata(7) = adata(11, gdata_current_map);
    mdata(8) = adata(12, gdata_current_map);
    mdata(14) = adata(21, gdata_current_map);
    if (mapupdate)
    {
        randomize(
            gdata_random_seed + gdata_current_map * 1000
            + gdata_current_dungeon_level);
    }
    if (gdata_current_map == 7)
    {
        if (mdatan(0) == ""s
            || mdatan(0) == lang(u8"ノースティリス"s, u8"North Tyris"s))
        {
            mdatan(0) = lang(u8"わが家"s, u8"Your Home"s);
        }
    }
    else
    {
        mdatan(0) = mapname(gdata_current_map);
    }
    if (gdata_current_map == 30)
    {
        if (gdata_current_dungeon_level == 1)
        {
            map_initcustom(u8"shelter_2"s);
            mdata(7) = 0;
            mdata(6) = 6;
        }
        else
        {
            map_initcustom(u8"shelter_1"s);
            mdata(15) = 0;
        }
        mdata(10) = 0;
        mdata(18) = 5;
        map_placeplayer();
        mdata(13) = 68;
    }
    if (adata(16, gdata_current_map) == 8)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            event_add(4);
        }
    }
    if (adata(16, gdata_current_map) == 101)
    {
        map_initcustom(u8"museum_1"s);
        mdata(13) = 53;
        map_placeplayer();
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 15, 17, 0);
        inv[ci].param1 = 4;
    }
    if (adata(16, gdata_current_map) == 102)
    {
        map_initcustom(u8"shop_1"s);
        mdata(13) = 53;
        mdata(18) = 10;
        map_placeplayer();
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 17, 14, 0);
        inv[ci].param1 = 8;
        flt();
        itemcreate(-1, 561, 19, 10, 0);
        inv[ci].count = 5;
        flt();
        itemcreate(-1, 562, 17, 11, 0);
    }
    if (adata(16, gdata_current_map) == 103)
    {
        map_initcustom(u8"crop_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 80;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 14, 5, 0);
        inv[ci].param1 = 9;
    }
    if (adata(16, gdata_current_map) == 31)
    {
        map_initcustom(u8"ranch_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 80;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 23, 8, 0);
        inv[ci].param1 = 11;
        flt();
        itemcreate(-1, 562, 22, 6, 0);
    }
    if (adata(16, gdata_current_map) == 39)
    {
        map_initcustom(u8"dungeon1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 350;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 39, 54, 0);
        inv[ci].param1 = 15;
    }
    if (adata(16, gdata_current_map) == 104)
    {
        map_initcustom(u8"storage_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 200;
        mdata(15) = 0;
    }
    if (gdata_current_map == 13)
    {
        generate_random_nefia();
    }
    if (gdata_current_map == 9)
    {
        mdata(0) = 16;
        mdata(1) = 16;
        mdata(10) = 0;
        map_initialize();
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                map(cnt, p, 0) = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
            }
        }
        map_placeplayer();
        for (int cnt = 0; cnt < 0; ++cnt)
        {
            flt();
            characreate(-1, 0, cdata[0].position.x, cdata[0].position.y + 5);
        }
        for (int cnt = 0; cnt < 100; ++cnt)
        {
            x = rnd(mdata(0));
            y = rnd(mdata(1));
        }
        flt();
        characreate(-1, 41, cdata[0].position.x, cdata[0].position.y);
        cdata[rc].character_role = 22;
        cdata[rc].is_livestock() = true;
    }
    if (gdata_current_map == 10)
    {
        map_initcustom(u8"grave_1"s);
        mdata(10) = 7;
        mdata(13) = 79;
        map_placeplayer();
        for (int cnt = 0, cnt_end = (mdata(10) / 2); cnt < cnt_end; ++cnt)
        {
            set_character_generation_filter();
            characreate(-1, 0, -3, 0);
        }
    }
    if (gdata_current_map == 41)
    {
        map_initcustom(u8"jail1"s);
        mdata(10) = 0;
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 20)
    {
        map_initcustom(u8"shrine_1"s);
        mdata(10) = 10;
        flt();
        itemcreate(-1, 171, 10, 8, 0);
        inv[ci].param1 = 1;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 13, 8, 0);
        inv[ci].param1 = 2;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 10, 13, 0);
        inv[ci].param1 = 5;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 13, 13, 0);
        inv[ci].param1 = 4;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 20, 8, 0);
        inv[ci].param1 = 3;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 23, 8, 0);
        inv[ci].param1 = 7;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 20, 13, 0);
        inv[ci].param1 = 6;
        inv[ci].own_state = 1;
        flt();
        itemcreate(-1, 171, 23, 13, 0);
        inv[ci].own_state = 1;
        mdata(13) = 79;
        map_placeplayer();
        for (int cnt = 0, cnt_end = (mdata(10) / 2); cnt < cnt_end; ++cnt)
        {
            set_character_generation_filter();
            characreate(-1, 0, -3, 0);
        }
    }
    if (gdata_current_map == 32)
    {
        map_initcustom(u8"office_1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 173, 9, 2);
        cdata[rc].character_role = 1012;
        cdata[rc].shop_rank = 10;
        flt();
        characreate(-1, 173, 15, 2);
        cdata[rc].character_role = 1012;
        cdata[rc].shop_rank = 10;
        flt();
        characreate(-1, 173, 21, 2);
        cdata[rc].character_role = 1013;
        cdata[rc].shop_rank = 10;
        flt();
        characreate(-1, 173, 3, 2);
        cdata[rc].character_role = 1013;
        cdata[rc].shop_rank = 10;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            characreate(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            characreate(-1, 77, 3 + cnt * 6, 9);
            cdata[rc].character_role = 14;
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 48)
    {
        map_initcustom(u8"test2"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 7, 23);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 1, 5, 17);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 1, 16, 19);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        characreate(-1, 70, 17, 13);
        cdata[rc].character_role = 9;
        flt();
        characreate(-1, 353, 7, 3);
        cdata[rc].character_role = 23;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            characreate(-1, 9, -3, 0);
            flt();
            characreate(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 160, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 161, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
        }
        flt();
        characreate(-1, 77, 5, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 8, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        mdata(13) = 79;
        map_placeplayer();
        event_add(30);
    }
    if (gdata_current_map == 43 || gdata_current_map == 45)
    {
        map_initcustom(u8"station-nt1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 7, 23);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 1, 5, 17);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 1, 16, 19);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        characreate(-1, 70, 17, 13);
        cdata[rc].character_role = 9;
        flt();
        characreate(-1, 353, 7, 3);
        cdata[rc].character_role = 23;
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            characreate(-1, 9, -3, 0);
            flt();
            characreate(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 160, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 161, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
        }
        flt();
        characreate(-1, 77, 5, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 8, 7);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 46)
    {
        map_initcustom(u8"inn1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 19, 10);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        characreate(-1, 351, 26, 16);
        cdata[rc].character_role = 3;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 35, 25, 15);
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 35, 25, 17);
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 35, 27, 18);
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 35, 27, 16);
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 35, 26, 17);
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 352, 4, 3);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 271, 4, 2);
        flt();
        characreate(-1, 269, 3, 3);
        flt();
        characreate(-1, 272, 4, 4);
        flt();
        characreate(-1, 274, 5, 4);
        flt();
        characreate(-1, 239, 24, 3);
        flt();
        characreate(-1, 239, 26, 4);
        flt();
        characreate(-1, 239, 25, 5);
        flt();
        characreate(-1, 239, 25, 9);
        flt();
        characreate(-1, 326, 12, 9);
        for (int cnt = 0; cnt < 2; ++cnt)
        {
            flt();
            characreate(-1, 9, -3, 0);
            flt();
            characreate(-1, 159, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 36, -3, 0);
            cdata[rc].relationship = -1;
            cdata[rc].original_relationship = -1;
            flt();
            characreate(-1, 8, -3, 0);
            flt();
            characreate(-1, 185, -3, 0);
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 34)
    {
        map_initcustom(u8"smith0"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 208, 17, 11);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 209, 8, 16);
        cdata[rc].character_role = 1016;
        cdata[rc].shop_rank = 100;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            flt();
            characreate(-1, 164, -3, 0);
            cdata[rc].character_role = 3;
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 29)
    {
        map_initcustom(u8"sister"s);
        mdata(10) = 0;
        mdata(13) = 79;
        if (mapupdate == 0)
        {
            flt();
            itemcreate(-1, 668, 12, 8, 0);
            inv[ci].param2 = 4;
        }
        flt();
        characreate(-1, 249, 12, 6);
        cdata[rc].character_role = 1019;
        for (int cnt = 0; cnt < 6; ++cnt)
        {
            flt();
            characreate(-1, 211, -3, 0);
            cdata[rc].character_role = 3;
        }
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            flt();
            characreate(-1, 246, -3, 0);
            cdata[rc].character_role = 3;
        }
        map_placeplayer();
    }
    if (gdata_current_map == 21)
    {
        map_initcustom(u8"cyberdome"s);
        mdata(10) = 10;
        flt();
        itemcreate(-1, 171, 19, 5, 0);
        inv[ci].param1 = 1;
        inv[ci].own_state = 1;
        flt();
        characreate(-1, 173, 9, 16);
        cdata[rc].character_role = 1011;
        cdata[rc].shop_rank = 10;
        flt();
        characreate(-1, 173, 9, 8);
        cdata[rc].character_role = 1011;
        cdata[rc].shop_rank = 10;
        flt();
        characreate(-1, 322, 28, 7);
        cdata[rc].character_role = 3;
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            characreate(-1, 171, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 172, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0, cnt_end = (mdata(10) / 2); cnt < cnt_end; ++cnt)
        {
            set_character_generation_filter();
            characreate(-1, 0, -3, 0);
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 25)
    {
        map_initcustom(u8"highmountain"s);
        mdata(10) = 20;
        flt();
        characreate(-1, 41, 21, 23);
        cdata[rc].character_role = 21;
        flt();
        characreate(-1, 1, 9, 44);
        cdata[rc].character_role = 1017;
        cdata[rc].shop_rank = 5;
        cdatan(0, rc) = lang(
            u8"染色店の"s + cdatan(0, rc),
            sncnv(cdatan(0, rc)) + u8"the dye vendor"s);
        flt();
        characreate(-1, 1, 13, 37);
        cdata[rc].character_role = 1018;
        cdata[rc].shop_rank = 30;
        cdatan(0, rc) = lang(
            u8"おみやげ屋の"s + cdatan(0, rc),
            sncnv(cdatan(0, rc)) + u8"the souvenir vendor"s);
        flt();
        characreate(-1, 70, 24, 48);
        cdata[rc].character_role = 9;
        flt();
        characreate(-1, 239, 7, 36);
        flt();
        characreate(-1, 239, 9, 38);
        flt();
        characreate(-1, 239, 6, 33);
        flt();
        characreate(-1, 239, 3, 33);
        flt();
        characreate(-1, 239, 8, 31);
        flt();
        characreate(-1, 239, 4, 36);
        for (int cnt = 0; cnt < 7; ++cnt)
        {
            flt();
            characreate(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 239, -3, 0);
        }
        for (int cnt = 0; cnt < 15; ++cnt)
        {
            flt();
            characreate(-1, 239, -3, 0);
        }
        for (int cnt = 0, cnt_end = (mdata(10) / 2); cnt < cnt_end; ++cnt)
        {
            set_character_generation_filter();
            characreate(-1, 0, -3, 0);
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata_current_map == 6)
    {
        map_initcustom(u8"arena_1"s);
        map_placeplayer();
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cdata[cnt].state == 1)
            {
                if (cdata[cnt].relationship == 10)
                {
                    if (cnt != 0)
                    {
                        map(cdata[cnt].position.x, cdata[cnt].position.y, 1) =
                            0;
                        cdata[cnt].state = 8;
                    }
                }
            }
        }
        if (arenaop == 0)
        {
            fixlv = arenaop(2);
            characreate(
                -1,
                arenaop(1),
                cdata[0].position.x - 1,
                cdata[0].position.y - 4);
            cdata[rc].hate = 30;
            cdata[rc].relationship = -3;
            cdata[rc].relationship = -3;
            cdata[rc].original_relationship = -3;
            cdata[rc].is_lord_of_dungeon() = true;
        }
        if (arenaop == 1)
        {
            for (int cnt = 0, cnt_end = (3 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt(arenaop(1), 2);
                characreate(
                    -1, 0, cdata[0].position.x - 1, cdata[0].position.y - 5);
                cdata[rc].relationship = -3;
                cdata[rc].original_relationship = -3;
                cdata[rc].hate = 30;
                cdata[rc].relationship = -3;
                cdata[rc].is_lord_of_dungeon() = true;
                if (cdata[rc].level > arenaop(1)
                    || cdata[rc].relationship != -3)
                {
                    chara_vanquish(rc);
                    --cnt;
                    continue;
                }
            }
        }
    }
    if (gdata_current_map == 40)
    {
        map_initcustom(u8"arena_2"s);
        mdata(10) = 0;
        mdata(13) = 81;
        for (int cnt = 0; cnt < 16; ++cnt)
        {
            if (cnt == 0 || cnt == 56)
            {
                continue;
            }
            if (followerin(cnt) == 0)
            {
                cdata[cnt].state = 6;
                cdata[cnt].position.x = 0;
                cdata[cnt].position.y = 0;
            }
            else
            {
                cdata[cnt].state = 1;
            }
        }
        map_placeplayer();
        petarenawin = 0;
        for (int cnt = 0, cnt_end = (arenaop(1)); cnt < cnt_end; ++cnt)
        {
            flt(arenaop(2), calcfixlv(3));
            characreate(-1, 0, -3, 0);
            map(cdata[rc].position.x, cdata[rc].position.y, 1) = 0;
            f = 1;
            if (arenaop == 0)
            {
                if (cdata[rc].level < arenaop(2) / 2)
                {
                    f = 0;
                }
            }
            if (cdata[rc].relationship != -3)
            {
                f = 0;
            }
            if (f == 0)
            {
                chara_vanquish(rc);
                --cnt;
                continue;
            }
            map_placearena(rc, 1);
            if (cnt == 0)
            {
                enemyteam = rc;
            }
        }
        for (int cnt = ELONA_MAX_PARTY_CHARACTERS; cnt < ELONA_MAX_CHARACTERS;
             ++cnt)
        {
            if (cdata[cnt].relationship == -3)
            {
                cdata[cnt].has_been_used_stethoscope() = true;
            }
        }
    }
    if (gdata_current_map == 22)
    {
        map_initcustom(u8"god"s);
        mdata(10) = 0;
        mdata(13) = 63;
        flt();
        characreate(-1, 175, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == 23)
    {
        map_initcustom(u8"god"s);
        mdata(10) = 0;
        mdata(13) = 63;
        flt();
        characreate(-1, 177, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == 24)
    {
        map_initcustom(u8"god"s);
        mdata(13) = 63;
        mdata(10) = 0;
        flt();
        characreate(-1, 178, 12, 14);
        map_placeplayer();
    }
    if (gdata_current_map == 7)
    {
        map_initcustom(u8"home"s + gdata_home_scale);
        mdata(13) = 68;
        gdata_entrance_type = 4;
        map_placeplayer();
        mdata(15) = 0;
        mdata(12) = 3;
        if (gdata_current_dungeon_level == 1)
        {
            if (gdata_home_scale == 0)
            {
                mdata(20) = 1;
                flt();
                characreate(-1, 33, 18, 10);
                cdata[rc].character_role = 3;
                flt();
                characreate(-1, 34, 16, 11);
                cdata[rc].character_role = 3;
                flt();
                itemcreate(-1, 510, 6, 10, 0);
                inv[ci].count = 3;
                flt();
                itemcreate(-1, 547, 15, 19, 0);
                inv[ci].count = 4;
                flt();
                itemcreate(-1, 579, 9, 8, 0);
                inv[ci].count = 6;
                flt();
                itemcreate(-1, 24, 18, 19, 0);
                inv[ci].param1 = 1;
            }
            else
            {
                ctrl_file(file_operation2_t::_3, u8"inv_"s + mid + u8".s2");
                for (const auto& cnt : items(-1))
                {
                    if (inv[cnt].number == 0)
                    {
                        continue;
                    }
                    inv[cnt].position.x = mdata(0) / 2;
                    inv[cnt].position.y = mdata(1) / 2;
                    cell_refresh(inv[cnt].position.x, inv[cnt].position.y);
                }
                ctrl_file(file_operation_t::_17);
                for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                     cnt < ELONA_MAX_CHARACTERS;
                     ++cnt)
                {
                    cdata[cnt].position.x = mdata(0) / 2;
                    cdata[cnt].position.y = mdata(1) / 2;
                    cdata[cnt].initial_position.x = mdata(0) / 2;
                    cdata[cnt].initial_position.y = mdata(1) / 2;
                }
            }
            if (gdata_home_scale == 5)
            {
                flt();
                characreate(-1, 1, 31, 20);
                cdata[rc].character_role = 1006;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = sngeneral(cdatan(0, rc));
                flt();
                characreate(-1, 1, 9, 20);
                cdata[rc].character_role = 1001;
                cdata[rc].shop_rank = 12;
                cdatan(0, rc) = snarmor(cdatan(0, rc));
                flt();
                characreate(-1, 1, 4, 20);
                cdata[rc].character_role = 1008;
                cdata[rc].shop_rank = 10;
                cdatan(0, rc) = sngoods(cdatan(0, rc));
                flt();
                characreate(-1, 41, 4, 11);
                cdata[rc].character_role = 5;
                flt();
                characreate(-1, 70, 30, 11);
                cdata[rc].character_role = 9;
                flt();
                characreate(-1, 74, 30, 4);
                cdata[rc].character_role = 12;
                flt();
                characreate(-1, 41, 4, 4);
                cdata[rc].character_role = 1004;
                cdata[rc].shop_rank = 11;
                cdatan(0, rc) = snmagic(cdatan(0, rc));
            }
        }
        else
        {
            flt();
            itemcreate(-1, 219, cdata[0].position.x, cdata[0].position.y, 0);
        }
        initialize_home_mdata();
    }
    if (gdata_current_map == 4)
    {
        map_initcustom(u8"ntyris"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == 44)
    {
        map_initcustom(u8"styris"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == 47)
    {
        map_initcustom(u8"test"s);
        initialize_world_map();
        map_placeplayer();
    }
    if (gdata_current_map == 14)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata(10) = 35;
            map_initcustom(u8"rogueden"s);
            map_placeplayer();
            mdata(15) = 0;
            flt();
            characreate(-1, 253, 23, 14);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 259, 13, 18);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 294, 16, 17);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 1, 10, 17);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 70, 15, 15);
            cdata[rc].character_role = 9;
            flt();
            characreate(-1, 1, 13, 3);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 29, 23);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 26, 7);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 30, 4);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 29, 4);
            cdata[rc].character_role = 17;
            cdatan(0, rc) = lang(u8"謎の奴隷商人"s, u8"The slave master"s);
            flt();
            characreate(-1, 1, 10, 6);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 73, 7, 15);
            cdata[rc].character_role = 10;
            flt();
            characreate(-1, 38, 9, 18);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = lang(
                u8"ダルフィ"s + cdatan(0, rc), cdatan(0, rc) + u8" of Derphy"s);
            flt();
            characreate(-1, 40, 13, 18);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 5, 26);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 69, 3, 28);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                characreate(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            label_2669();
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                dbid = 0;
                set_character_generation_filter();
                characreate(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata(12) = 0;
            map_initcustom(u8"thiefguild"s);
            mdata(14) = 1;
            mdata(6) = 2;
            mdata(10) = 25;
            mdata(13) = 79;
            mdata(17) = 0;
            mdatan(0) = lang(u8"盗賊ギルド"s, u8"Thieves Guild"s);
            map_placeplayer();
            flt();
            characreate(-1, 292, 21, 9);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 40, 3, 6);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 3, 12);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 1, 5, 18);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 27, 13);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 21, 19);
            cdata[rc].character_role = 1021;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = lang(
                u8"盗賊店の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the fence"s);
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                characreate(-1, 293, -3, 0);
            }
        }
    }
    if (gdata_current_map == 15)
    {
        mdata(10) = 45;
        map_initcustom(u8"palmia"s);
        map_placeplayer();
        mdata(15) = 0;
        flt();
        characreate(-1, 70, 42, 27);
        cdata[rc].character_role = 9;
        flt();
        characreate(-1, 74, 34, 3);
        cdata[rc].character_role = 12;
        flt();
        characreate(-1, 73, 22, 31);
        cdata[rc].character_role = 10;
        flt();
        characreate(-1, 142, 5, 15);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 247, 41, 11);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 301, 5, 6);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 320, 24, 6);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 320, 15, 22);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 326, 15, 22);
        cdata[rc].character_role = 3;
        if (gdata_mias_dream == 1000)
        {
            flt();
            characreate(-1, 246, 42, 11);
            cdata[rc].character_role = 3;
        }
        flt();
        characreate(-1, 1, 48, 18);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        flt();
        characreate(-1, 1, 30, 17);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        characreate(-1, 1, 48, 3);
        cdata[rc].character_role = 1008;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sngoods(cdatan(0, rc));
        flt();
        characreate(-1, 1, 42, 17);
        cdata[rc].character_role = 1001;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = snarmor(cdatan(0, rc));
        flt();
        characreate(-1, 1, 11, 14);
        cdata[rc].character_role = 1003;
        cdata[rc].shop_rank = 9;
        cdatan(0, rc) = snbakery(cdatan(0, rc));
        cdata[rc].image = 138;
        flt();
        characreate(-1, 41, 41, 3);
        cdata[rc].character_role = 1004;
        cdata[rc].shop_rank = 11;
        cdatan(0, rc) = snmagic(cdatan(0, rc));
        flt();
        characreate(-1, 1, 41, 28);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        flt();
        characreate(-1, 79, 7, 2);
        cdata[rc].character_role = 15;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 80, 6, 2);
        cdata[rc].character_role = 15;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 38, 49, 11);
        cdata[rc].character_role = 6;
        cdatan(0, rc) = lang(
            u8"パルミア市街地の"s + cdatan(0, rc),
            cdatan(0, rc) + u8" of Palmia city"s);
        flt();
        characreate(-1, 40, 30, 27);
        cdata[rc].character_role = 7;
        cdatan(0, rc) = sntrainer(cdatan(0, rc));
        flt();
        characreate(-1, 41, 32, 27);
        cdata[rc].character_role = 5;
        flt();
        characreate(-1, 69, 29, 28);
        cdata[rc].character_role = 8;
        flt();
        characreate(-1, 77, 16, 5);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 16, 9);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 5, 3);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 8, 3);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 35, 14);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 38, 14);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 29, 2);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 19, 18);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        flt();
        characreate(-1, 77, 22, 18);
        cdata[rc].character_role = 14;
        cdata[rc].ai_calm = 3;
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            flt();
            characreate(-1, 16, -3, 0);
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 39, -3, 0);
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 4; ++cnt)
        {
            flt();
            characreate(-1, 77, -3, 0);
            cdata[rc].character_role = 14;
        }
        label_2669();
        for (int cnt = 0; cnt < 25; ++cnt)
        {
            dbid = 0;
            set_character_generation_filter();
            characreate(-1, dbid, -3, 0);
        }
    }
    if (gdata_current_map == 36)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata(10) = 40;
            map_initcustom(u8"lumiest"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata_sewer_sweeping)
            {
                cell_featset(18, 45, tile_downstairs, 11, 20);
            }
            flt();
            characreate(-1, 252, 12, 24);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 280, 21, 3);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 290, 5, 20);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 320, 28, 29);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 41, 19);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 32, 43);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 29, 28);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 16, 45);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 13, 24);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 70, 41, 42);
            cdata[rc].character_role = 9;
            flt();
            characreate(-1, 74, 10, 16);
            cdata[rc].character_role = 12;
            flt();
            characreate(-1, 1, 47, 30);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 24, 47);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 37, 30);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 37, 12);
            cdata[rc].character_role = 1003;
            cdata[rc].shop_rank = 9;
            cdatan(0, rc) = snbakery(cdatan(0, rc));
            cdata[rc].image = 138;
            flt();
            characreate(-1, 41, 6, 15);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 33, 43);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 47, 12);
            cdata[rc].character_role = 1014;
            cdata[rc].shop_rank = 5;
            cdatan(0, rc) = snfish(cdatan(0, rc));
            flt();
            characreate(-1, 38, 3, 38);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = lang(
                u8"ルミエストの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Lumiest"s);
            flt();
            characreate(-1, 40, 21, 28);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 21, 30);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 69, 23, 38);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 6; ++cnt)
            {
                flt();
                characreate(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 7; ++cnt)
            {
                flt();
                characreate(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            label_2669();
            for (int cnt = 0; cnt < 25; ++cnt)
            {
                dbid = 0;
                set_character_generation_filter();
                characreate(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata(12) = 0;
            map_initcustom(u8"mageguild"s);
            mdata(14) = 1;
            mdata(6) = 2;
            mdata(10) = 25;
            mdata(13) = 79;
            mdata(17) = 0;
            mdatan(0) = lang(u8"魔術士ギルド"s, u8"Mages Guild"s);
            map_placeplayer();
            flt();
            characreate(-1, 288, 24, 3);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 41, 27, 8);
            cdata[rc].character_role = 1020;
            cdatan(0, rc) = lang(
                u8"魔法書作家の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the spell writer"s);
            flt();
            characreate(-1, 41, 22, 8);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 74, 3, 9);
            cdata[rc].character_role = 12;
            flt();
            characreate(-1, 40, 12, 6);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 3, 3);
            cdata[rc].character_role = 5;
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                characreate(-1, 289, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 20)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqSewer"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"ルミエスト下水道"s, u8"The Sewer"s);
            put_questtarget();
            gdata_entrance_type = 1;
            map_placeplayer();
        }
    }
    if (gdata_current_map == 12)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata(10) = 35;
            map_initcustom(u8"yowyn"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata_cat_house)
            {
                cell_featset(23, 22, tile_downstairs, 11, 3);
            }
            flt();
            characreate(-1, 224, 3, 17);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 227, 26, 11);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 231, 14, 20);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 1, 11, 5);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 25, 8);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 7, 8);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 14);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 35, 18);
            cdata[rc].character_role = 22;
            cdatan(0, rc) = lang(
                u8"馬屋の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the horse master"s);
            flt();
            characreate(-1, 267, 33, 16);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 267, 37, 19);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 268, 34, 19);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 268, 38, 16);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 38, 3, 4);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = lang(
                u8"ヨウィンの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Yowyn"s);
            flt();
            characreate(-1, 40, 20, 14);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 24, 16);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 69, 26, 16);
            cdata[rc].character_role = 8;
            flt();
            characreate(-1, 213, 14, 12);
            cdata[rc].character_role = 3;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                flt();
                characreate(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 3; ++cnt)
            {
                flt();
                characreate(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            label_2669();
            for (int cnt = 0; cnt < 15; ++cnt)
            {
                dbid = 0;
                set_character_generation_filter();
                characreate(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqcat"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"タムの猫屋敷"s, u8"Cat Mansion"s);
            put_questtarget();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 4)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqwar"s);
            mdata(14) = 2;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdata(7) = 0;
            mdatan(0) = lang(u8"防衛線"s, u8"Battle Field"s);
            put_questtarget();
            gdata_entrance_type = 8;
            map_placeplayer();
            listmax = 0;
            for (int cnt = ELONA_MAX_PARTY_CHARACTERS;
                 cnt < ELONA_MAX_CHARACTERS;
                 ++cnt)
            {
                if (cdata[cnt].state == 1)
                {
                    if (cdata[cnt].is_quest_target() == 1)
                    {
                        list(0, listmax) = cnt;
                        ++listmax;
                    }
                }
            }
            for (int cnt = 0; cnt < 30; ++cnt)
            {
                flt();
                characreate(-1, 233 + 2 * (cnt > 22), 11, 16);
                cdata[rc].relationship = 10;
                cdata[rc].original_relationship = 10;
                cdata[rc].hate = 100;
                p = list(0, rnd(listmax));
                cdata[rc].enemy_id = p;
                cdata[p].hate = 100;
                cdata[p].enemy_id = rc;
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata_current_map == 33)
    {
        mdata(10) = 35;
        map_initcustom(u8"noyel"s);
        map_placeplayer();
        mdata(15) = 0;
        flt();
        characreate(-1, 202, 46, 18);
        gdata_fire_giant = rc;
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 203, 47, 18);
        cdata[rc].character_role = 1015;
        flt();
        characreate(-1, 35, 47, 20);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 35, 45, 19);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 35, 49, 20);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 326, 28, 22);
        cdata[rc].character_role = 3;
        flt();
        characreate(-1, 221, 19, 3);
        cdata[rc].character_role = 3;
        if (gdata_pael_and_her_mom != 1001)
        {
            flt();
            characreate(-1, 222, 19, 2);
            cdata[rc].character_role = 3;
        }
        flt();
        characreate(-1, 70, 40, 33);
        cdata[rc].character_role = 9;
        flt();
        characreate(-1, 74, 44, 6);
        cdata[rc].character_role = 12;
        flt();
        characreate(-1, 206, 44, 3);
        cdata[rc].character_role = 19;
        flt();
        characreate(-1, 1, 19, 31);
        cdata[rc].character_role = 1001;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = snarmor(cdatan(0, rc));
        flt();
        characreate(-1, 1, 11, 31);
        cdata[rc].character_role = 1006;
        cdata[rc].shop_rank = 10;
        cdatan(0, rc) = sngeneral(cdatan(0, rc));
        flt();
        characreate(-1, 1, 38, 34);
        cdata[rc].character_role = 1005;
        cdata[rc].shop_rank = 8;
        cdatan(0, rc) = sninn(cdatan(0, rc));
        flt();
        characreate(-1, 1, 5, 27);
        cdata[rc].character_role = 1003;
        cdata[rc].shop_rank = 9;
        cdatan(0, rc) = snbakery(cdatan(0, rc));
        cdata[rc].image = 138;
        flt();
        characreate(-1, 41, 56, 5);
        cdata[rc].character_role = 1004;
        cdata[rc].shop_rank = 11;
        cdatan(0, rc) = snmagic(cdatan(0, rc));
        flt();
        characreate(-1, 1, 39, 35);
        cdata[rc].character_role = 1009;
        cdata[rc].shop_rank = 12;
        cdatan(0, rc) = sntrade(cdatan(0, rc));
        flt();
        characreate(-1, 38, 5, 18);
        cdata[rc].character_role = 6;
        cdatan(0, rc) = lang(
            u8"ノイエルの"s + cdatan(0, rc), cdatan(0, rc) + u8" of Noyel"s);
        flt();
        characreate(-1, 40, 18, 20);
        cdata[rc].character_role = 7;
        cdatan(0, rc) = sntrainer(cdatan(0, rc));
        flt();
        characreate(-1, 41, 4, 33);
        cdata[rc].character_role = 5;
        flt();
        characreate(-1, 69, 6, 33);
        cdata[rc].character_role = 8;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            characreate(-1, 16, rnd(32), rnd(mdata(1)));
            cdata[rc].character_role = 4;
            flt();
            characreate(-1, 39, rnd(32), rnd(mdata(1)));
            cdata[rc].character_role = 4;
        }
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            flt();
            characreate(-1, 77, rnd(32), rnd(mdata(1)));
            cdata[rc].character_role = 14;
        }
        label_2669();
        for (int cnt = 0; cnt < 8; ++cnt)
        {
            set_character_generation_filter();
            characreate(-1, 35, rnd(11) + 25, rnd(5) + 15);
            cdata[rc].character_role = 3;
        }
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            dbid = 0;
            set_character_generation_filter();
            characreate(-1, dbid, rnd(55), rnd(mdata(1)));
        }
    }
    if (gdata_current_map == 11)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata(10) = 40;
            map_initcustom(u8"kapul"s);
            map_placeplayer();
            mdata(15) = 0;
            flt();
            characreate(-1, 223, 15, 18);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 243, 36, 27);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 279, 5, 26);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 297, 29, 3);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 320, 24, 21);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 320, 12, 26);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 320, 8, 11);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 8, 14);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 1, 16, 17);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 23, 7);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 32, 14);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 22, 14);
            cdata[rc].character_role = 1008;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 16, 25);
            cdata[rc].character_role = 1007;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 17, 28);
            cdata[rc].character_role = 1002;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = snfood(cdatan(0, rc));
            flt();
            characreate(-1, 41, 22, 22);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 35, 3);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            characreate(-1, 70, 15, 15);
            cdata[rc].character_role = 9;
            flt();
            characreate(-1, 73, 26, 3);
            cdata[rc].character_role = 10;
            flt();
            characreate(-1, 179, 25, 4);
            cdata[rc].character_role = 11;
            flt();
            characreate(-1, 38, 8, 12);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = lang(
                u8"ポート・カプールの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Port Kapul"s);
            flt();
            characreate(-1, 40, 16, 4);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 14, 4);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 69, 17, 5);
            cdata[rc].character_role = 8;
            flt();
            characreate(-1, 74, 27, 11);
            cdata[rc].character_role = 12;
            for (int cnt = 0; cnt < 2; ++cnt)
            {
                flt();
                characreate(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                characreate(-1, 71, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 5; ++cnt)
            {
                flt();
                characreate(-1, 76, -3, 0);
                cdata[rc].character_role = 14;
            }
            flt();
            characreate(-1, 72, 7, 6);
            cdata[rc].character_role = 4;
            label_2669();
            for (int cnt = 0; cnt < 20; ++cnt)
            {
                set_character_generation_filter();
                characreate(-1, 0, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata(12) = 0;
            map_initcustom(u8"fighterguild"s);
            mdata(14) = 1;
            mdata(6) = 2;
            mdata(10) = 25;
            mdata(13) = 79;
            mdata(17) = 0;
            mdatan(0) = lang(u8"戦士ギルド"s, u8"Fighters Guild"s);
            map_placeplayer();
            flt();
            characreate(-1, 291, 27, 4);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 74, 28, 10);
            cdata[rc].character_role = 12;
            flt();
            characreate(-1, 40, 15, 10);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 14, 18);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 1, 29, 15);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                flt();
                characreate(-1, 295, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 25)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqkamikaze"s);
            mdata(14) = 2;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdata(7) = 0;
            mdatan(0) = lang(u8"戦場"s, u8"Doom Ground"s);
            gdata_entrance_type = 4;
            gdata_duration_of_kamikaze_attack = 0;
            map_placeplayer();
            for (int cnt = 0; cnt < 10; ++cnt)
            {
                flt();
                characreate(-1, 204, cdata[0].position.x, cdata[0].position.y);
                cdata[rc].relationship = 10;
                cdata[rc].original_relationship = 10;
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata_current_map == 5)
    {
        if (gdata_current_dungeon_level == 1)
        {
            mdata(10) = 40;
            map_initcustom(u8"vernis"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata_thieves_hideout)
            {
                cell_featset(48, 5, tile_downstairs, 11, 4);
            }
            flt();
            characreate(-1, 28, 39, 3);
            flt();
            characreate(-1, 29, 42, 23);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 30, 24, 5);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 31, 40, 24);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 32, 40, 25);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 226, 30, 5);
            cdata[rc].character_role = 3;
            flt();
            characreate(-1, 326, 42, 24);
            cdata[rc].character_role = 3;
            if (gdata_puppys_cave == 1000)
            {
                flt();
                characreate(-1, 225, 31, 4);
                cdata[rc].character_role = 3;
            }
            flt();
            characreate(-1, 1, 47, 9);
            cdata[rc].character_role = 1014;
            cdata[rc].shop_rank = 5;
            cdatan(0, rc) = snfish(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 12);
            cdata[rc].character_role = 1001;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 39, 27);
            cdata[rc].character_role = 1009;
            cdata[rc].shop_rank = 12;
            cdatan(0, rc) = sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 10, 15);
            cdata[rc].character_role = 1006;
            cdata[rc].shop_rank = 10;
            cdatan(0, rc) = sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 41, 7, 26);
            cdata[rc].character_role = 1004;
            cdata[rc].shop_rank = 11;
            cdatan(0, rc) = snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 25);
            cdata[rc].character_role = 1005;
            cdata[rc].shop_rank = 8;
            cdatan(0, rc) = sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 22, 26);
            cdata[rc].character_role = 1003;
            cdata[rc].shop_rank = 9;
            cdatan(0, rc) = snbakery(cdatan(0, rc));
            cdata[rc].image = 138;
            flt();
            characreate(-1, 41, 28, 16);
            cdata[rc].character_role = 5;
            flt();
            characreate(-1, 70, 38, 27);
            cdata[rc].character_role = 9;
            flt();
            characreate(-1, 74, 6, 25);
            cdata[rc].character_role = 12;
            flt();
            characreate(-1, 38, 10, 7);
            cdata[rc].character_role = 6;
            cdatan(0, rc) = lang(
                u8"ヴェルニースの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Vernis"s);
            flt();
            characreate(-1, 40, 27, 16);
            cdata[rc].character_role = 7;
            cdatan(0, rc) = sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 69, 25, 16);
            cdata[rc].character_role = 8;
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                characreate(-1, 16, -3, 0);
                cdata[rc].character_role = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata[rc].character_role = 4;
            }
            for (int cnt = 0; cnt < 4; ++cnt)
            {
                flt();
                characreate(-1, 77, -3, 0);
                cdata[rc].character_role = 14;
            }
            label_2669();
            for (int cnt = 0; cnt < 25; ++cnt)
            {
                dbid = 0;
                set_character_generation_filter();
                characreate(-1, dbid, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 3)
        {
            mdata(12) = 0;
            map_initcustom(u8"puti"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"スライムの坑道"s, u8"The Mine"s);
            put_questtarget();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 4)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqrogue"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"盗賊の隠れ家"s, u8"Robber's Hideout"s);
            put_questtarget();
            map_placeplayer();
        }
        if (gdata_current_dungeon_level == 5)
        {
            mdata(12) = 0;
            map_initcustom(u8"sqNightmare"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"生体兵器実験場"s, u8"Test Site"s);
            put_questtarget();
            gdata_entrance_type = 7;
            mapstartx = 6;
            mapstarty = 27;
            map_placeplayer();
        }
    }
    if (gdata_current_map == 2)
    {
        mdata(0) = 34;
        mdata(1) = 22;
        mdata(10) = 4;
        mdata(15) = 0;
        map_initialize();
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            p = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                map(cnt, p, 0) = tile_default
                    + (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
            }
        }
        mdatan(0) = "";
        if (4 <= gdata(62) && gdata(62) < 9)
        {
            mdatan(0) = lang(u8"森"s, u8"Forest"s);
            map_randomtile(8, 25);
            map_randomtile(0, 10);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            for (int cnt = 0, cnt_end = (20 + rnd(20)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
                map(inv[ci].position.x, inv[ci].position.y, 0) = 0;
            }
        }
        if (264 <= gdata(62) && gdata(62) < 363)
        {
            mdatan(0) = lang(u8"水上"s, u8"Sea"s);
        }
        if (9 <= gdata(62) && gdata(62) < 13)
        {
            mdatan(0) = lang(u8"草原"s, u8"Grassland"s);
            map_randomtile(9, 10);
            map_randomtile(10, 10);
            map_randomtile(0, 30);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            for (int cnt = 0, cnt_end = (10 + rnd(10)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (13 <= gdata(62) && gdata(62) < 17)
        {
            mdatan(0) = lang(u8"荒野"s, u8"Desert"s);
            map_randomtile(18, 25);
            map_randomtile(17, 10);
            map_randomtile(19, 2);
            map_randomtile(20, 4);
            map_randomtile(21, 2);
            for (int cnt = 0, cnt_end = (4 + rnd(4)); cnt < cnt_end; ++cnt)
            {
                flt();
                itemcreate(-1, 527, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (chipm(0, gdata(62)) == 4)
        {
            mdatan(0) = lang(u8"雪原"s, u8"Snow Field"s);
            map_randomtile(57, 4);
            map_randomtile(56, 4);
            map_randomtile(49, 2);
            map_randomtile(46, 1);
            map_randomtile(47, 1);
            map_randomtile(48, 1);
            map_randomtile(51, 1);
            for (int cnt = 0, cnt_end = (3 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                fltselect = 8;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        if (mdatan(0) == ""s)
        {
            mdatan(0) = lang(u8"平地"s, u8"Plain Field"s);
            map_randomtile(1, 10);
            map_randomtile(2, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            map_randomtile(6, 2);
            for (int cnt = 0, cnt_end = (5 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypemajor = 80000;
                itemcreate(-1, 0, -1, -1, 0);
                inv[ci].own_state = 1;
            }
        }
        map_placeplayer();
        if (264 > gdata(62) || gdata(62) >= 363)
        {
            for (int cnt = 0, cnt_end = (4 + rnd(5)); cnt < cnt_end; ++cnt)
            {
                flt();
                flttypeminor = 64000;
                itemcreate(-1, 0, -1, -1, 0);
            }
        }
        if (encounter == 0)
        {
            for (int cnt = 0, cnt_end = (mdata(10) + 1); cnt < cnt_end; ++cnt)
            {
                set_character_generation_filter();
                flt();
                characreate(-1, 0, -3, 0);
            }
        }
        if (encounter == 4)
        {
            mdata(10) = 0;
            flt();
            initlv = encounterlv;
            characreate(-1, 302, cdata[0].position.x, cdata[0].position.y);
            for (int cnt = 0, cnt_end = (6 + rnd(6)); cnt < cnt_end; ++cnt)
            {
                flt();
                initlv = encounterlv + rnd(10);
                characreate(-1, 303 + rnd(3), 14, 11);
                cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
            }
            gdatan(1) = random_title(2);
            event_add(23);
        }
        if (encounter == 3)
        {
            mdata(10) = 0;
            mdata(6) = 7;
            rq = encounterref;
            gdata_executing_immediate_quest_type = 1007;
            gdata(71) = 1;
            gdata_executing_immediate_quest = rq;
            gdata(73) = 1;
            p = rnd(3) + 5;
            for (int cnt = 0, cnt_end = (p); cnt < cnt_end; ++cnt)
            {
                flt(qdata(5, rq), 3);
                int stat = characreate(
                    -1, 0, cdata[0].position.x, cdata[0].position.y);
                if (stat != 0)
                {
                    cdata[rc].hate = 30;
                    cdata[rc].relationship = -3;
                    cdata[rc].original_relationship = -3;
                }
            }
        }
        if (encounter == 2)
        {
            flt();
            characreate(-1, 1, 10, 11);
            cdata[rc].character_role = 1010;
            cdata[rc].shop_rank = encounterlv;
            cdatan(0, rc) = lang(
                u8"行商人の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the wandering vendor"s);
            generatemoney(rc);
            for (int cnt = 0, cnt_end = (encounterlv / 2 + 1); cnt < cnt_end;
                 ++cnt)
            {
                r2 = 1;
                gain_level(rc);
            }
            event_add(11);
            for (int cnt = 0, cnt_end = (6 + rnd(6)); cnt < cnt_end; ++cnt)
            {
                flt();
                initlv = encounterlv + rnd(10);
                characreate(-1, 159 + rnd(3), 14, 11);
                cdata[rc].character_role = 16;
                cdatan(0, rc) += u8" Lv"s + cdata[rc].level;
            }
        }
        if (encounter == 1)
        {
            p = rnd(9);
            if (cdata[0].level <= 5)
            {
                p = rnd(3);
            }
            for (int cnt = 0, cnt_end = (2 + p); cnt < cnt_end; ++cnt)
            {
                flt(calcobjlv(encounterlv), calcfixlv(2));
                if (gdata_weather == 1)
                {
                    if ((33 > gdata(62) || gdata(62) >= 66) && rnd(3) == 0)
                    {
                        fixlv = 5;
                    }
                }
                if (cnt < 4)
                {
                    characreate(
                        -1, 0, cdata[0].position.x, cdata[0].position.y);
                }
                else
                {
                    characreate(-1, 0, -3, 0);
                }
                cdata[rc].hate = 30;
            }
        }
        encounter = 0;
    }
    if (gdata_current_map == 42)
    {
        generate_random_nefia();
        if (gdata(186) == 0)
        {
            gdata(186) = adata(17, gdata_current_map) + 4;
        }
        if (gdata(186) <= gdata_current_dungeon_level)
        {
            event_add(29);
        }
        else
        {
            adata(20, gdata_current_map) = 0;
        }
    }
    if (gdata_current_map == 3)
    {
        map_tileset(mdata(12));
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (gdata_current_dungeon_level == adata(10, gdata_current_map))
            {
                map_initcustom(u8"lesimas_1"s);
                mdata(10) = 0;
                mdata(7) = 0;
                mdata(13) = 66;
                mdatan(0) = lang(u8"レシマス最深層"s, u8"The Depth"s);
                if (gdata_main_quest_flag < 170)
                {
                    event_add(3);
                }
                x = 16;
                y = 13;
                cell_featset(x, y, tile_upstairs, 10);
                mdata(5) = y * 1000 + x;
                map_placeplayer();
                if (npcmemory(0, 2) == 0)
                {
                    flt();
                    characreate(-1, 2, 16, 6);
                }
                else if (npcmemory(0, 23) == 0)
                {
                    flt();
                    characreate(-1, 23, 16, 6);
                }
                break;
            }
            generate_random_nefia();
            break;
        }
        if (gdata_current_dungeon_level == 3)
        {
            characreate(-1, 139, cdata[0].position.x, cdata[0].position.y);
            cdata[rc].character_role = 3;
            cdata[rc].ai_calm = 3;
        }
        if (gdata_current_dungeon_level == 17)
        {
            characreate(-1, 146, cdata[0].position.x, cdata[0].position.y);
            cdata[rc].character_role = 3;
            cdata[rc].ai_calm = 3;
        }
    }
    if (gdata_current_map == 16)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"firet1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == 17)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"undeadt1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == 18)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"roguet1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == 19)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            map_initcustom(u8"d_1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        }
        else
        {
            generate_random_nefia();
        }
    }
    if (gdata_current_map == 27)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_puppys_cave < 2)
            {
                if (findally(225) == -1)
                {
                    flt();
                    characreate(-1, 225, -3, 0);
                    cdata[rc].does_not_search_enemy() = true;
                }
            }
        }
    }
    if (gdata_current_map == 38)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_minotaur_king < 2)
            {
                flt();
                characreate(-1, 300, -3, 0);
            }
        }
    }
    if (gdata_current_map == 28)
    {
        generate_random_nefia();
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (gdata_novice_knight < 2)
            {
                flt();
                characreate(-1, 242, -3, 0);
                tc = rc;
                for (int cnt = 0; cnt < 5; ++cnt)
                {
                    flt();
                    characreate(
                        -1, 240, cdata[tc].position.x, cdata[tc].position.y);
                }
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    flt();
                    characreate(
                        -1, 238, cdata[tc].position.x, cdata[tc].position.y);
                    flt();
                    characreate(
                        -1, 237, cdata[tc].position.x, cdata[tc].position.y);
                }
            }
        }
    }
    if (gdata_current_map == 37)
    {
        if (gdata_current_dungeon_level == 20)
        {
            map_initcustom(u8"sqPyramid"s);
            mdata(10) = 40;
            mdata(13) = 61;
            map_placeplayer();
            for (int cnt = 0, cnt_end = (mdata(10) + 1); cnt < cnt_end; ++cnt)
            {
                set_character_generation_filter();
                characreate(-1, 0, -3, 0);
            }
        }
        if (gdata_current_dungeon_level == 21)
        {
            map_initcustom(u8"sqPyramid2"s);
            mdata(10) = 0;
            mdata(13) = 61;
            map_placeplayer();
        }
    }
    if (gdata_current_map == 26)
    {
        generate_random_nefia();
    }
    map_setfog();
    if (gdata_current_map == 40 || dbg_revealmap || gdata_current_map == 6
        || mdata(6) == 3 || mdata(6) == 1 || mdata(6) == 5 || mdata(6) == 2
        || gdata_current_map == 30 || gdata_current_map == 32
        || gdata_current_map == 34 || gdata_current_map == 35
        || (gdata_current_map == 13
            && gdata_executing_immediate_quest_type == 1009))
    {
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                map(cnt, y, 2) = map(cnt, y, 0);
            }
        }
    }
    if (mapupdate == 1)
    {
        if (mdata(6) == 1)
        {
            f = 0;
            i = 0;
            for (int cnt = 300; cnt < 500; ++cnt)
            {
                p = cnt;
                if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                    || adata(16, cnt) == 0)
                {
                    continue;
                }
                for (int cnt = 0; cnt < 300; ++cnt)
                {
                    if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                        || adata(16, cnt) == 0)
                    {
                        continue;
                    }
                    if (adata(1, p) == adata(1, cnt))
                    {
                        if (adata(2, p) == adata(2, cnt))
                        {
                            for (int cnt = 0;; ++cnt)
                            {
                                await();
                                dx = clamp(rnd(cnt / 4 + 1) + 1, 1, mdata(0));
                                dy = clamp(rnd(cnt / 4 + 1) + 1, 1, mdata(1));
                                x = adata(1, p) + rnd(dx) - rnd(dx);
                                y = adata(2, p) + rnd(dy) - rnd(dy);
                                if (x < 0 || y < 0 || x >= mdata(0)
                                    || y >= mdata(1))
                                {
                                    continue;
                                }
                                if (33 <= map(x, y, 0) && map(x, y, 0) < 66)
                                {
                                    continue;
                                }
                                if (map(x, y, 0) > 19)
                                {
                                    continue;
                                }
                                i = 1;
                                for (int cnt = 0, cnt_end = (300);
                                     cnt < cnt_end;
                                     ++cnt)
                                {
                                    if (adata(1, cnt) == 0 || adata(2, cnt) == 0
                                        || adata(16, cnt) == 0)
                                    {
                                        continue;
                                    }
                                    if (x == adata(1, cnt))
                                    {
                                        if (y == adata(2, cnt))
                                        {
                                            i = 0;
                                            break;
                                        }
                                    }
                                }
                                if (i == 0)
                                {
                                    continue;
                                }
                                dialog(lang(
                                    u8"エリアが再配置されます。"s + mapname(p)
                                        + u8"の位置は、x"s + adata(1, p)
                                        + u8":y"s + adata(2, p) + u8"からx"s + x
                                        + u8":y"s + y + u8"に変更されます。"s,
                                    u8"The location of "s + mapname(p)
                                        + u8" has been changed from x"s
                                        + adata(1, p) + u8":y"s + adata(2, p)
                                        + u8" to x"s + x + u8":y"s + y
                                        + u8"."s));
                                adata(1, p) = x;
                                adata(2, p) = y;
                                ++f;
                                break;
                            }
                        }
                    }
                }
            }
            label_1749();
        }
        mapupdate = 0;
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].state == 0)
            {
                continue;
            }
            if ((cdata[cnt].character_role >= 1000
                 && cdata[cnt].character_role < 2000)
                || cdata[cnt].character_role == 2003)
            {
                int cnt2 = cnt;
                for (int cnt = 0, cnt_end = (maxnpcbk); cnt < cnt_end; ++cnt)
                {
                    if (cdata[cnt2].character_role == rolebk(0, cnt))
                    {
                        cdata[cnt2].shop_rank = rolebk(1, cnt);
                        rolebk(0, cnt) = 0;
                        rolebk(1, cnt) = 0;
                        break;
                    }
                }
            }
        }
        for (int cnt = 0, cnt_end = (maxmedal); cnt < cnt_end; ++cnt)
        {
            cell_featset(medalbk(0, cnt), medalbk(1, cnt), tile_hidden, 32);
        }
    }
    randomize();
    mdata(19) = gdata(184);
    mdata(21) = 1;
label_1742_internal:
    if (gdata_current_map == 4)
    {
        if (gdata_main_quest_flag == 180)
        {
            cdata[0].position.x = adata(1, 11);
            cdata[0].position.y = adata(2, 11);
            gdata(35) = 1;
            gdata(60) = -1;
            msg_newline();
            msgtemp = lang(
                u8"  三年の月日が経ち、あなたは再びノースティリスに降り立った。"s,
                u8"  Three years elapsed and you set foot on cool soil of North Tyris's again."s);
        }
    }
    for (int cnt = 16; cnt < 55; ++cnt)
    {
        if (cdata[cnt].state != 3)
        {
            continue;
        }
        if (cdata[cnt].is_contracting())
        {
            cdata[cnt].relationship = 10;
            cdata[cnt].current_map = gdata_current_map;
            goto label_1743_internal;
        }
        if (cdata[cnt].current_map != gdata_current_map)
        {
            continue;
        }
        if (mdata(6) != 3 && mdata(6) != 2)
        {
            continue;
        }
        if (gdata_current_dungeon_level != 1)
        {
            continue;
        }
    label_1743_internal:
        if (gdata_current_map == 6 || gdata_current_map == 40)
        {
            continue;
        }
        rc = cnt;
        cdata[rc].state = 1;
        if (cdata[cnt].is_contracting() == 1)
        {
            cxinit = cdata[0].position.x;
            cyinit = cdata[0].position.y;
            place_character();
        }
        else
        {
            cxinit = -1;
            place_character();
            cdata[rc].hp = cdata[rc].max_hp;
            cdata[rc].mp = cdata[rc].max_mp;
        }
    }
    if (mdata(7) == 1)
    {
        if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12
            >= mdata(3))
        {
            if (mdata(17) == 0)
            {
                if (mdata(3) != 0)
                {
                    if (gdata_current_dungeon_level == 1)
                    {
                        if (gdata_current_map == 36)
                        {
                            map_reload(u8"lumiest"s);
                        }
                        if (gdata_current_map == 5)
                        {
                            map_reload(u8"vernis"s);
                        }
                        if (gdata_current_map == 15)
                        {
                            map_reload(u8"palmia"s);
                        }
                        if (gdata_current_map == 11)
                        {
                            map_reload(u8"kapul"s);
                        }
                        if (gdata_current_map == 12)
                        {
                            map_reload(u8"yowyn"s);
                        }
                        if (gdata_current_map == 14)
                        {
                            map_reload(u8"rogueden"s);
                        }
                        if (gdata_current_map == 33)
                        {
                            if (gdata_month == 12)
                            {
                                if (adata(29, gdata_current_map) == 0)
                                {
                                    adata(29, gdata_current_map) = 1;
                                    label_1755();
                                }
                                map_reload(u8"noyel_fest"s);
                            }
                            else
                            {
                                if (adata(29, gdata_current_map) == 1)
                                {
                                    adata(29, gdata_current_map) = 0;
                                    label_1755();
                                }
                                map_reload(u8"noyel"s);
                            }
                            gdata_released_fire_giant = 0;
                        }
                    }
                }
            }
        }
        for (int cnt = 0, cnt_end = (mdata(1)); cnt < cnt_end; ++cnt)
        {
            y = cnt;
            for (int cnt = 0, cnt_end = (mdata(0)); cnt < cnt_end; ++cnt)
            {
                map(cnt, y, 1) = 0;
            }
        }
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            rc = cnt;
            cdata[rc].was_passed_item_by_you_just_now() = false;
            if (rc < 57)
            {
                if (mode == 11)
                {
                    continue;
                }
            }
            if (cdata[rc].state == 2)
            {
                if (gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                        + gdata_year * 24 * 30 * 12
                    >= cdata[rc].time_to_revive)
                {
                    label_1540();
                }
                else
                {
                    continue;
                }
            }
            if (cdata[rc].state != 1)
            {
                continue;
            }
            if (cdata[rc].character_role == 14)
            {
                if (cdata[0].karma < -30)
                {
                    if (cdata[0].level > cdata[rc].level)
                    {
                        r2 = 1;
                        gain_level(rc);
                    }
                }
            }
            if (rc >= 57)
            {
                cdata[rc].hp = cdata[rc].max_hp;
                cdata[rc].mp = cdata[rc].max_mp;
                cdata[rc].insanity = 0;
            }
            if (rc >= 57)
            {
                if (mdata(8) == 1)
                {
                    cdata[rc].position.x = cdata[rc].initial_position.x;
                    cdata[rc].position.y = cdata[rc].initial_position.y;
                }
                if (cdata[rc].is_quest_target() == 0)
                {
                    cdata[rc].hate = 0;
                    cdata[rc].relationship = cdata[rc].original_relationship;
                }
                if (cdata[rc].character_role == 14)
                {
                    if (cdata[0].karma < -30)
                    {
                        if (cdata[0].is_incognito() == 0)
                        {
                            cdata[rc].hate = 200;
                            cdata[rc].relationship = -3;
                        }
                    }
                }
                if (mdata(6) == 3 || mdata(6) == 2)
                {
                    cdata[rc].sleep = 0;
                    if (gdata_hour >= 22 || gdata_hour < 7)
                    {
                        if (rnd(6) == 0)
                        {
                            cdata[rc].sleep = rnd(400);
                        }
                    }
                }
            }
            if (rc == 0 || gdata_mount != rc)
            {
                cell_check(cdata[rc].position.x, cdata[rc].position.y);
                if (map(cdata[rc].position.x, cdata[rc].position.y, 1) != 0
                    || cellaccess != 1)
                {
                    for (int cnt = 0;; ++cnt)
                    {
                        x = cdata[rc].position.x + rnd((cnt / 2 + 2))
                            - rnd((cnt / 2 + 2));
                        y = cdata[rc].position.y + rnd((cnt / 2 + 2))
                            - rnd((cnt / 2 + 2));
                        if (cnt > 100)
                        {
                            x = rnd(mdata(0));
                            y = rnd(mdata(1));
                        }
                        if (cnt > 1000)
                        {
                            break;
                        }
                        cell_check(x, y);
                        if (cellaccess == 1)
                        {
                            cdata[rc].position.x = x;
                            cdata[rc].position.y = y;
                            break;
                        }
                    }
                }
            }
            if (cdata[rc].is_ridden() == 0)
            {
                map(cdata[rc].position.x, cdata[rc].position.y, 1) = rc + 1;
            }
        }
    }
label_1744_internal:
    DIM4(efmap, 4, mdata(0), mdata(1));
    if (mdata(0) == 0 || mdata(1) == 0)
    {
        if (medit == 0)
        {
            dialog(lang(
                u8"マップのロードに失敗しました。"s, u8"Map loading failed."s));
            mode = 2;
            gdata_current_map = 7;
            gdata_current_dungeon_level = 1;
            gdata_pc_home_x = adata(1, 7);
            gdata_pc_home_y = adata(2, 7);
            gdata_previous_map = 2;
            levelexitby = 4;
            goto label_17401;
        }
    }
    label_1745();
    gdata_other_character_count = 0;
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        cdata[cnt].turn_cost = 0;
        if (cdata[cnt].id == 343)
        {
            getunid(cnt);
        }
        if (noaggrorefresh == 0)
        {
            cdata[cnt].enemy_id = 0;
            cdata[cnt].hate = 0;
        }
        cdata[cnt].vision_flag = 0;
        if (cnt > 57)
        {
            if (cdata[cnt].state != 0)
            {
                ++gdata_other_character_count;
            }
        }
    }
    cdata[0].current_map = gdata_current_map;
    cdata[0].current_dungeon_level = gdata_current_dungeon_level;
    raderx = -1;
    radery = -1;
    raderw = 120 / mdata(0) + 2;
    raderh = 84 / mdata(1) + 2;
    scx = cdata[0].position.x;
    scy = cdata[0].position.y;
    msync = 1;
    label_1746();
    label_1439();
    label_1428();
    if (mdata(6) == 3)
    {
        label_2671();
    }
    if (mode == 11)
    {
        // This result will be ignored by the caller.
        return turn_result_t::turn_begin;
    }
    if (gdata_main_quest_flag == 9)
    {
        sceneid = 2;
        do_play_scene();
        gdata_main_quest_flag = 10;
    }
    if (gdata_main_quest_flag == 60)
    {
        sceneid = 5;
        do_play_scene();
        gdata_main_quest_flag = 65;
    }
    if (gdata_main_quest_flag == 110)
    {
        sceneid = 26;
        do_play_scene();
        gdata_main_quest_flag = 115;
    }
    if (gdata_main_quest_flag == 115)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 1)
        {
            sceneid = 28;
            do_play_scene();
            gdata_main_quest_flag = 116;
        }
    }
    if (gdata_main_quest_flag == 116)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 2)
        {
            sceneid = 29;
            do_play_scene();
            gdata_main_quest_flag = 117;
        }
    }
    if (gdata_main_quest_flag == 117)
    {
        if (gdata_magic_stone_of_fool + gdata_magic_stone_of_king
                + gdata_magic_stone_of_sage
            >= 3)
        {
            sceneid = 30;
            do_play_scene();
            gdata_main_quest_flag = 120;
        }
    }
    if (gdata_current_map == 3)
    {
        if (gdata_main_quest_flag == 10)
        {
            sceneid = 3;
            do_play_scene();
            gdata_main_quest_flag = 20;
        }
        if (gdata_current_dungeon_level == 4)
        {
            if (gdata_main_quest_flag == 65)
            {
                sceneid = 7;
                do_play_scene();
                gdata_main_quest_flag = 70;
            }
        }
        if (gdata_current_dungeon_level == 7)
        {
            if (gdata_main_quest_flag == 70)
            {
                sceneid = 15;
                do_play_scene();
                gdata_main_quest_flag = 75;
            }
        }
        if (gdata_current_dungeon_level == 10)
        {
            if (gdata_main_quest_flag == 75)
            {
                sceneid = 16;
                do_play_scene();
                gdata_main_quest_flag = 80;
            }
        }
        if (gdata_current_dungeon_level == 14)
        {
            if (gdata_main_quest_flag == 80)
            {
                sceneid = 17;
                do_play_scene();
                gdata_main_quest_flag = 85;
            }
        }
        if (gdata_current_dungeon_level == 16)
        {
            if (gdata_main_quest_flag == 85)
            {
                sceneid = 24;
                do_play_scene();
                gdata_main_quest_flag = 90;
            }
        }
        if (gdata_current_dungeon_level == 26)
        {
            if (gdata_main_quest_flag == 125)
            {
                sceneid = 33;
                do_play_scene();
                gdata_main_quest_flag = 130;
            }
        }
        if (gdata_current_dungeon_level == 28)
        {
            if (gdata_main_quest_flag == 130)
            {
                sceneid = 35;
                do_play_scene();
                gdata_main_quest_flag = 135;
            }
        }
        if (gdata_current_dungeon_level == 31)
        {
            if (gdata_main_quest_flag == 135)
            {
                sceneid = 40;
                do_play_scene();
                gdata_main_quest_flag = 140;
            }
        }
        if (gdata_current_dungeon_level == 35)
        {
            if (gdata_main_quest_flag == 140)
            {
                sceneid = 60;
                do_play_scene();
                gdata_main_quest_flag = 145;
            }
        }
        if (gdata_current_dungeon_level == 38)
        {
            if (gdata_main_quest_flag == 145)
            {
                sceneid = 70;
                do_play_scene();
                gdata_main_quest_flag = 150;
            }
        }
        if (gdata_current_dungeon_level == 42)
        {
            if (gdata_main_quest_flag == 150)
            {
                sceneid = 90;
                do_play_scene();
                gdata_main_quest_flag = 160;
            }
        }
    }
    if (adata(16, gdata_current_map) == 33)
    {
        tc = findchara(222);
        if (tc != 0)
        {
            if (gdata_pael_and_her_mom >= 10)
            {
                cdata[tc].image = 360;
                cdata[tc].portrait = -1;
            }
        }
    }
    if (adata(16, gdata_current_map) == 36)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_mages_guild);
        }
    }
    if (adata(16, gdata_current_map) == 14)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_thieves_guild);
        }
    }
    if (adata(16, gdata_current_map) == 11)
    {
        if (gdata_current_dungeon_level == 3)
        {
            event_add(22, gdata_belongs_to_fighters_guild);
        }
    }
    if (gdata_current_map == 5)
    {
        if (gdata_main_quest_flag == 0)
        {
            sceneid = 1;
            do_play_scene();
            gdata_main_quest_flag = 9;
        }
        if (gdata_has_not_been_to_vernis == 0)
        {
            gdata_has_not_been_to_vernis = 1;
            event_add(12);
        }
    }
    if (gdata_current_map == 15)
    {
        if (gdata_main_quest_flag == 30)
        {
            sceneid = 4;
            do_play_scene();
            gdata_main_quest_flag = 40;
        }
        if (gdata_main_quest_flag == 100)
        {
            sceneid = 25;
            do_play_scene();
            gdata_main_quest_flag = 105;
        }
    }
    if (gdata_current_map == 4)
    {
        if (gdata_main_quest_flag == 180)
        {
            sceneid = 100;
            do_play_scene();
            gdata_main_quest_flag = 200;
            gdata_year += 3;
        }
    }
    if (adata(16, gdata_current_map) == 8)
    {
        if (gdata_current_dungeon_level == adata(10, gdata_current_map))
        {
            if (adata(20, gdata_current_map) == -1)
            {
                msgtemp += lang(
                    u8"辺りからは何の緊張感も感じられない。"s
                        + mapname(gdata_current_map)
                        + u8"の主はもういないようだ。"s,
                    u8"This place is pretty dull. The dungeon master is no longer sighted here."s);
            }
        }
    }
    play_music();
    label_2088();
    noaggrorefresh = 0;
    if (adata(0, gdata_current_map) == 1)
    {
        // initialize_cloud_data();
        label_1748();
    }
    if (mode == 3)
    {
        mode = 0;
        if (mapsubroutine == 0)
        {
            screenupdate = -1;
            update_entire_screen();
            txt_conv();
            update_screen();
            if (evnum == 0)
            {
                return turn_result_t::pc_turn_user_error;
            }
            else
            {
                return turn_result_t::turn_begin;
            }
        }
        else
        {
            mapsubroutine = 0;
            // This result will be ignored by the caller.
            return turn_result_t::turn_begin;
        }
    }
    wake_up();
    pcattacker = 0;
    cdata[0].enemy_id = 0;
    gdata(94) = 0;
    mode = 0;
    screenupdate = -1;
    update_entire_screen();
    txt_conv();
    if (gdata_current_map == 7)
    {
        if (gdata_main_quest_flag != 0)
        {
            if (findchara(33) != 0)
            {
                chara_vanquish(findchara(33));
            }
            if (findchara(34) != 0)
            {
                chara_vanquish(findchara(34));
            }
        }
    }
    if (gdata_current_map == 15)
    {
        if (gdata_main_quest_flag >= 90)
        {
            if (findchara(80) != 0)
            {
                chara_vanquish(findchara(80));
            }
        }
    }
    if (mdata(6) == 3)
    {
        for (int cnt = 0, cnt_end = (gdata_number_of_existing_quests);
             cnt < cnt_end;
             ++cnt)
        {
            if (qdata(3, cnt) == 1007)
            {
                if (qdata(8, cnt) == 1)
                {
                    int cnt2 = cnt;
                    for (int cnt = 0; cnt < 16; ++cnt)
                    {
                        if (cdata[cnt].is_escorted() == 1)
                        {
                            if (cdata[cnt].state == 1)
                            {
                                if (cdata[cnt].id == qdata(13, cnt2))
                                {
                                    if (qdata(12, cnt2) == gdata_current_map)
                                    {
                                        event_add(16, cnt2, cnt);
                                        cdata[cnt].is_escorted() = false;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (adata(16, gdata_current_map) == 101
        || adata(16, gdata_current_map) == 102)
    {
        for (int cnt = 0; cnt < 5; ++cnt)
        {
            monster_respawn();
        }
    }
    if (mdata(7) == 1)
    {
        label_1576();
    }
    if (adata(16, gdata_current_map) == 102)
    {
        update_shop();
    }
    if (adata(16, gdata_current_map) == 101)
    {
        update_museum();
    }
    if (gdata_current_map == 7)
    {
        label_1730();
    }
    if (adata(16, gdata_current_map) == 31)
    {
        for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
        {
            if (cdata[cnt].is_livestock() == 1)
            {
                cdata[cnt].hate = 0;
                cdata[cnt].relationship = -1;
                cdata[cnt].original_relationship = -1;
            }
        }
    }
    if (mdata(6) == 1)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(202) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(202) = 1;
                        ghelp = 2;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (mdata(6) == 3)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(203) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(203) = 1;
                        ghelp = 3;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (gdata_current_map == 30)
    {
        if (config::instance().extrahelp)
        {
            if (gdata(214) == 0)
            {
                if (mode == 0)
                {
                    if (cdata[0].continuous_action_turn == 0)
                    {
                        gdata(214) = 1;
                        ghelp = 14;
                        show_ex_help();
                    }
                }
            }
        }
    }
    if (mdata(6) == 3 || gdata_current_map == 7 || mdata(6) == 2)
    {
        if (gdata_distance_between_town >= 16)
        {
            p = gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
                + gdata_year * 24 * 30 * 12 - gdata_departure_date;
            txt(lang(
                cnvdate(gdata_departure_date, false) + u8"に"s
                    + mapname(gdata_left_town_map) + u8"を発ってから、"s
                    + p / 24 + u8"日と"s + p % 24 + u8"時間の旅を終えた。"s,
                ""s + p / 24 + u8" days and "s + p % 24
                    + u8" hours have passed since you left "s
                    + mapname(gdata_left_town_map) + u8"."s));
            p = 0;
            exp = cdata[0].level * gdata_distance_between_town * sdata(182, 0)
                    / 100
                + 1;
            for (int cnt = 0; cnt < 16; ++cnt)
            {
                if (cdata[cnt].state != 1)
                {
                    continue;
                }
                ++p;
                cdata[cnt].experience += exp;
            }
            if (p == 1)
            {
                s = u8"あなた"s;
            }
            else
            {
                s = u8"あなたとその仲間"s;
            }
            txt(lang(
                s + u8"は"s + gdata_distance_between_town
                    + u8"マイルの距離を歩き、経験を積んだ。"s,
                u8"You've walked about "s + gdata_distance_between_town
                    + u8" miles and have gained experience."s));
            skillexp(182, 0, 25 + gdata_distance_between_town * 2 / 3, 0, 1000);
            gdata_distance_between_town = 0;
        }
    }
    if (gdata_current_map == 13)
    {
        if (gdata_executing_immediate_quest_type == 1009)
        {
            txtef(9);
            txt(lang(
                ""s + gdata_left_minutes_of_executing_quest
                    + u8"分間の間にパーティーを盛り上げよう。目標は"s
                    + qdata(12, gdata_executing_immediate_quest)
                    + u8"ポイント。"s,
                u8"You have to warm up the party within "s
                    + gdata_left_minutes_of_executing_quest
                    + u8" minites. Your target score is "s
                    + qdata(12, gdata_executing_immediate_quest)
                    + u8" points."s));
        }
        if (gdata_executing_immediate_quest_type == 1006)
        {
            if (qdata(12, gdata_executing_immediate_quest) <= 0)
            {
                qdata(12, gdata_executing_immediate_quest) = 15000;
                qdata(6, gdata_executing_immediate_quest) = 400;
            }
            txtef(9);
            txt(lang(
                ""s + gdata_left_minutes_of_executing_quest
                    + u8"分以内に、納入箱に"s
                    + cnvweight(qdata(12, gdata_executing_immediate_quest))
                    + u8"の作物を納入しよう。"s,
                u8"To complete the quest, you have to harvest "s
                    + cnvweight(qdata(12, gdata_executing_immediate_quest))
                    + u8" worth farm products and put them into the delivery chest within "s
                    + gdata_left_minutes_of_executing_quest + u8" minutes."s));
        }
        if (gdata_executing_immediate_quest_type == 1008)
        {
            txtef(9);
            txt(lang(
                ""s + gdata_left_minutes_of_executing_quest + u8"分以内に、"s
                    + refchara_str(
                          qdata(12, gdata_executing_immediate_quest), 2)
                    + u8"を討伐しなければならない。"s,
                u8"You have to slay "s
                    + refchara_str(
                          qdata(12, gdata_executing_immediate_quest), 2)
                    + u8" within "s + gdata_left_minutes_of_executing_quest
                    + u8" minites."s));
        }
    }
    return turn_result_t::turn_begin;
}



} // namespace elona
