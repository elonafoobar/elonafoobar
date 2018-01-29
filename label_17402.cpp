#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
void label_2743(bool = true);


void label_17402()
{
label_17401:
    mapupdate = 0;
    if (gdata(22) > adata(10, gdata(20))) { gdata(22) = adata(10, gdata(20)); }
    if (gdata(22) < adata(17, gdata(20))) { gdata(22) = adata(17, gdata(20)); }
    if (gdata(1) < gdata(22)) {
        if (gdata(20) != 30) { gdata(1) = gdata(22); }
    }
    if (adata(6, gdata(20)) < gdata(22)) { adata(6, gdata(20)) = gdata(22); }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
            if (cnt == 0) { continue; }
            if (cdata(80, cnt) != 0) {
                if (cdata(80, cnt) == gdata(20)) {
                    if (cdata(0, cnt) == 9) { cdata(0, cnt) = 1; }
                }
            }
        }
    }
    mid = ""s + gdata(20) + u8"_"s + (100 + gdata(22));
    if (mode == 3) {
        fmode = 1;
        label_2107();
        file = u8"inv_"s + mid + u8".s2"s;
        fmode = 3;
        label_2107();
        goto label_1744_internal;
    }
    getkey(a, 8);
    if (a) {
        exist(exedir + u8"tmp\\mdata_"s + mid + u8".s2"s);
        if (strsize != -1) {
            dialog(
                lang(
                    u8"マップを初期化しますか？（注：ゲームに影響が出る可能性があります。エラーが出てマップが読み込めない場合のみ、必ず元のセーブのバックアップをとった上で実行してください。）"s,
                    u8"Initialize this map? (Warning, only do this if an error occurs when loading this map. Make sure make a backup of the current save folder before doing this.)"s),
                3);
            if (stat == 6) {
                fmode = 11;
                label_2107();
            }
        }
    }
    exist(exedir + u8"tmp\\mdata_"s + mid + u8".s2"s);
    if (strsize != -1) {
        fmode = 1;
        label_2107();
        if (mdata(7) == 0) { goto label_1741_internal; }
        if (mdata(19) != gdata(184) || gdata(79) == 1 && mdata(6) == 1) {
            if (mdata(6) == 3 || mdata(6) == 2 || mdata(6) == 6 ||
                mdata(6) == 1) {
                mapupdate = 1;
                goto label_1741_internal;
            }
        }
        file = u8"inv_"s + mid + u8".s2"s;
        fmode = 3;
        label_2107();
        if (mode == 2) { map_placeplayer(); }
        goto label_1742_internal;
    }
label_1741_internal:
    if (mapupdate == 1) {
        maxnpcbk = 0;
        DIM3(rolebk, 2, 245);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt) {
                if (cdata(0, cnt) == 0) { continue; }
                if (cdata(150, cnt) >= 1000 && cdata(150, cnt) < 2000 ||
                    cdata(150, cnt) == 2003) {
                    rolebk(0, maxnpcbk) = cdata(150, cnt);
                    rolebk(1, maxnpcbk) = cdata(151, cnt);
                    ++maxnpcbk;
                }
            }
        }
        maxmedal = 0;
        DIM3(medalbk, 2, 30);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                y = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        x = cnt;
                        if (map(x, y, 6) / 1000 % 100 == 32) {
                            if (maxmedal < 30) {
                                medalbk(0, maxmedal) = x;
                                medalbk(1, maxmedal) = y;
                                ++maxmedal;
                            }
                        }
                    }
                }
            }
        }
    }
    mdata(3) = 0;
    {
        int cnt = 57;
        for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt) {
            cdata(0, cnt) = 0;
        }
    }
    {
        int cnt = 1320;
        for (int cnt_end = cnt + (4160); cnt < cnt_end; ++cnt) {
            inv(0, cnt) = 0;
        }
    }
    DIM2(mdata, 100);
    mdata(11) = gdata(22);
    mdata(2) = adata(4, gdata(20));
    mdata(12) = adata(18, gdata(20));
    mdata(6) = adata(0, gdata(20));
    mdata(9) = adata(9, gdata(20));
    mdata(7) = adata(11, gdata(20));
    mdata(8) = adata(12, gdata(20));
    mdata(14) = adata(21, gdata(20));
    if (mapupdate) { randomize(gdata(8) + gdata(20) * 1000 + gdata(22)); }
    if (gdata(20) == 7) {
        if (mdatan(0) == ""s ||
            mdatan(0) == lang(u8"ノースティリス"s, u8"North Tyris"s)) {
            mdatan(0) = lang(u8"わが家"s, u8"Your Home"s);
        }
    } else {
        mdatan(0) = mapname(gdata(20));
    }
    if (gdata(20) == 30) {
        if (gdata(22) == 1) {
            map_initcustom(u8"shelter_2"s);
            mdata(7) = 0;
            mdata(6) = 6;
        } else {
            map_initcustom(u8"shelter_1"s);
            mdata(15) = 0;
        }
        mdata(10) = 0;
        mdata(18) = 5;
        map_placeplayer();
        mdata(13) = 68;
    }
    if (adata(16, gdata(20)) == 8) {
        label_16952();
        if (gdata(22) == adata(10, gdata(20))) { evadd(4); }
    }
    if (adata(16, gdata(20)) == 35) {
        file = ""s + userfile;
        id = 0;
        label_2095();
        fmode = 19;
        label_2107();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                y = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        x = cnt;
                        map(x, y, 1) = 0;
                    }
                }
            }
        }
        importmode = 0;
        fmode = 21;
        label_2107();
        mdata(10) = 0;
        mdata(7) = 0;
        mdata(15) = 0;
        mdata(6) = 7;
        mdata(9) = 10000;
        gdata(73) = 3;
        inv_getheader(-1);
        {
            int cnt = invhead;
            for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt) {
                if (inv(3, cnt) >= maxitemid - 2 ||
                    inv(3, cnt) > length(ioriginalnameref)) {
                    inv(0, cnt) = 0;
                    cell_refresh(inv(5, cnt), inv(6, cnt));
                    continue;
                }
                if (inv(0, cnt) > 0) { inv(21, cnt) = 5; }
            }
        }
        label_2111();
        evadd(19);
        map_placeplayer();
    }
    if (adata(16, gdata(20)) == 101) {
        map_initcustom(u8"museum_1"s);
        mdata(13) = 53;
        map_placeplayer();
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 15, 17, 0);
        inv(25, ci) = 4;
    }
    if (adata(16, gdata(20)) == 102) {
        map_initcustom(u8"shop_1"s);
        mdata(13) = 53;
        mdata(18) = 10;
        map_placeplayer();
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 17, 14, 0);
        inv(25, ci) = 8;
        flt();
        itemcreate(-1, 561, 19, 10, 0);
        inv(9, ci) = 5;
        flt();
        itemcreate(-1, 562, 17, 11, 0);
    }
    if (adata(16, gdata(20)) == 103) {
        map_initcustom(u8"crop_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 80;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 14, 5, 0);
        inv(25, ci) = 9;
    }
    if (adata(16, gdata(20)) == 31) {
        map_initcustom(u8"ranch_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 80;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 23, 8, 0);
        inv(25, ci) = 11;
        flt();
        itemcreate(-1, 562, 22, 6, 0);
    }
    if (adata(16, gdata(20)) == 39) {
        map_initcustom(u8"dungeon1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 350;
        mdata(15) = 0;
        flt();
        itemcreate(-1, 24, 39, 54, 0);
        inv(25, ci) = 15;
    }
    if (adata(16, gdata(20)) == 104) {
        map_initcustom(u8"storage_1"s);
        mdata(13) = 68;
        map_placeplayer();
        mdata(18) = 200;
        mdata(15) = 0;
    }
    if (gdata(20) == 13) { label_16952(); }
    if (gdata(20) == 9) {
        mdata(0) = 16;
        mdata(1) = 16;
        mdata(10) = 0;
        map_initialize();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                p = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        map(cnt, p, 0) = tile_default +
                            (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
                    }
                }
            }
        }
        map_placeplayer();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (0); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 0, cdata(1, 0), cdata(2, 0) + 5);
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (280); cnt < cnt_end; ++cnt) {}
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt) {
                x = rnd(mdata(0));
                y = rnd(mdata(1));
            }
        }
        flt();
        characreate(-1, 41, cdata(1, 0), cdata(2, 0));
        cdata(150, rc) = 22;
        cbitmod(960, rc, 1);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (6 + rnd(6)); cnt < cnt_end; ++cnt) {}
        }
    }
    if (gdata(20) == 10) {
        map_initcustom(u8"grave_1"s);
        mdata(10) = 7;
        mdata(13) = 79;
        map_placeplayer();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(10) / 2); cnt < cnt_end; ++cnt) {
                label_1735();
                characreate(-1, 0, -3, 0);
            }
        }
    }
    if (gdata(20) == 41) {
        map_initcustom(u8"jail1"s);
        mdata(10) = 0;
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 20) {
        map_initcustom(u8"shrine_1"s);
        mdata(10) = 10;
        flt();
        itemcreate(-1, 171, 10, 8, 0);
        inv(25, ci) = 1;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 13, 8, 0);
        inv(25, ci) = 2;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 10, 13, 0);
        inv(25, ci) = 5;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 13, 13, 0);
        inv(25, ci) = 4;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 20, 8, 0);
        inv(25, ci) = 3;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 23, 8, 0);
        inv(25, ci) = 7;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 20, 13, 0);
        inv(25, ci) = 6;
        inv(21, ci) = 1;
        flt();
        itemcreate(-1, 171, 23, 13, 0);
        inv(21, ci) = 1;
        mdata(13) = 79;
        map_placeplayer();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(10) / 2); cnt < cnt_end; ++cnt) {
                label_1735();
                characreate(-1, 0, -3, 0);
            }
        }
    }
    if (gdata(20) == 32) {
        map_initcustom(u8"office_1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 173, 9, 2);
        cdata(150, rc) = 1012;
        cdata(151, rc) = 10;
        flt();
        characreate(-1, 173, 15, 2);
        cdata(150, rc) = 1012;
        cdata(151, rc) = 10;
        flt();
        characreate(-1, 173, 21, 2);
        cdata(150, rc) = 1013;
        cdata(151, rc) = 10;
        flt();
        characreate(-1, 173, 3, 2);
        cdata(150, rc) = 1013;
        cdata(151, rc) = 10;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 16, -3, 0);
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata(150, rc) = 4;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 77, 3 + cnt * 6, 9);
                cdata(150, rc) = 14;
            }
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 48) {
        map_initcustom(u8"test2"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 7, 23);
        cdata(150, rc) = 1006;
        cdata(151, rc) = 10;
        sngeneral(cdatan(0, rc));
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 1, 5, 17);
        cdata(150, rc) = 1009;
        cdata(151, rc) = 12;
        sntrade(cdatan(0, rc));
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 1, 16, 19);
        cdata(150, rc) = 1005;
        cdata(151, rc) = 8;
        sninn(cdatan(0, rc));
        flt();
        characreate(-1, 70, 17, 13);
        cdata(150, rc) = 9;
        flt();
        characreate(-1, 353, 7, 3);
        cdata(150, rc) = 23;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 9, -3, 0);
                flt();
                characreate(-1, 159, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 160, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 161, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
            }
        }
        flt();
        characreate(-1, 77, 5, 7);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 8, 7);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        mdata(13) = 79;
        map_placeplayer();
        evadd(30);
    }
    if (gdata(20) == 43 || gdata(20) == 45) {
        map_initcustom(u8"station-nt1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 7, 23);
        cdata(150, rc) = 1006;
        cdata(151, rc) = 10;
        sngeneral(cdatan(0, rc));
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 1, 5, 17);
        cdata(150, rc) = 1009;
        cdata(151, rc) = 12;
        sntrade(cdatan(0, rc));
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 1, 16, 19);
        cdata(150, rc) = 1005;
        cdata(151, rc) = 8;
        sninn(cdatan(0, rc));
        flt();
        characreate(-1, 70, 17, 13);
        cdata(150, rc) = 9;
        flt();
        characreate(-1, 353, 7, 3);
        cdata(150, rc) = 23;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 9, -3, 0);
                flt();
                characreate(-1, 159, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 160, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 161, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
            }
        }
        flt();
        characreate(-1, 77, 5, 7);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 8, 7);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 46) {
        map_initcustom(u8"inn1"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 1, 19, 10);
        cdata(150, rc) = 1005;
        cdata(151, rc) = 8;
        sninn(cdatan(0, rc));
        flt();
        characreate(-1, 351, 26, 16);
        cdata(150, rc) = 3;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 35, 25, 15);
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 35, 25, 17);
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 35, 27, 18);
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 35, 27, 16);
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 35, 26, 17);
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 352, 4, 3);
        cdata(150, rc) = 3;
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
        {
            int cnt = 0;
            for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 9, -3, 0);
                flt();
                characreate(-1, 159, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 36, -3, 0);
                cdata(9, rc) = -1;
                cdata(69, rc) = -1;
                flt();
                characreate(-1, 8, -3, 0);
                flt();
                characreate(-1, 185, -3, 0);
            }
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 34) {
        map_initcustom(u8"smith0"s);
        mdata(10) = 0;
        flt();
        characreate(-1, 208, 17, 11);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 209, 8, 16);
        cdata(150, rc) = 1016;
        cdata(151, rc) = 100;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 164, -3, 0);
                cdata(150, rc) = 3;
            }
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 29) {
        map_initcustom(u8"sister"s);
        mdata(10) = 0;
        mdata(13) = 79;
        if (mapupdate == 0) {
            flt();
            itemcreate(-1, 668, 12, 8, 0);
            inv(26, ci) = 4;
        }
        flt();
        characreate(-1, 249, 12, 6);
        cdata(150, rc) = 1019;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (6); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 211, -3, 0);
                cdata(150, rc) = 3;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (8); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 246, -3, 0);
                cdata(150, rc) = 3;
            }
        }
        map_placeplayer();
    }
    if (gdata(20) == 21) {
        map_initcustom(u8"cyberdome"s);
        mdata(10) = 10;
        flt();
        itemcreate(-1, 171, 19, 5, 0);
        inv(25, ci) = 1;
        inv(21, ci) = 1;
        flt();
        characreate(-1, 173, 9, 16);
        cdata(150, rc) = 1011;
        cdata(151, rc) = 10;
        flt();
        characreate(-1, 173, 9, 8);
        cdata(150, rc) = 1011;
        cdata(151, rc) = 10;
        flt();
        characreate(-1, 322, 28, 7);
        cdata(150, rc) = 3;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 171, -3, 0);
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 172, -3, 0);
                cdata(150, rc) = 4;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(10) / 2); cnt < cnt_end; ++cnt) {
                label_1735();
                characreate(-1, 0, -3, 0);
            }
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 25) {
        map_initcustom(u8"highmountain"s);
        mdata(10) = 20;
        flt();
        characreate(-1, 41, 21, 23);
        cdata(150, rc) = 21;
        flt();
        characreate(-1, 1, 9, 44);
        cdata(150, rc) = 1017;
        cdata(151, rc) = 5;
        cdatan(0, rc) = lang(u8"染色店の"s + cdatan(0, rc),
            sncnv(cdatan(0, rc)) + u8"the dye vendor"s);
        flt();
        characreate(-1, 1, 13, 37);
        cdata(150, rc) = 1018;
        cdata(151, rc) = 30;
        cdatan(0, rc) = lang(u8"おみやげ屋の"s + cdatan(0, rc),
            sncnv(cdatan(0, rc)) + u8"the souvenir vendor"s);
        flt();
        characreate(-1, 70, 24, 48);
        cdata(150, rc) = 9;
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
        {
            int cnt = 0;
            for (int cnt_end = cnt + (7); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 16, -3, 0);
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 239, -3, 0);
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 239, -3, 0);
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(10) / 2); cnt < cnt_end; ++cnt) {
                label_1735();
                characreate(-1, 0, -3, 0);
            }
        }
        mdata(13) = 79;
        map_placeplayer();
    }
    if (gdata(20) == 6) {
        map_initcustom(u8"arena_1"s);
        map_placeplayer();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                if (cdata(0, cnt) == 1) {
                    if (cdata(9, cnt) == 10) {
                        if (cnt != 0) {
                            map(cdata(1, cnt), cdata(2, cnt), 1) = 0;
                            cdata(0, cnt) = 8;
                        }
                    }
                }
            }
        }
        if (arenaop == 0) {
            fixlv = arenaop(2);
            characreate(-1, arenaop(1), cdata(1, 0) - 1, cdata(2, 0) - 4);
            cdata(201, rc) = 30;
            cdata(9, rc) = -3;
            cdata(9, rc) = -3;
            cdata(69, rc) = -3;
            cbitmod(976, rc, 1);
        }
        if (arenaop == 1) {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3 + rnd(4)); cnt < cnt_end; ++cnt) {
                    flt(arenaop(1), 2);
                    characreate(-1, 0, cdata(1, 0) - 1, cdata(2, 0) - 5);
                    cdata(9, rc) = -3;
                    cdata(69, rc) = -3;
                    cdata(201, rc) = 30;
                    cdata(9, rc) = -3;
                    cbitmod(976, rc, 1);
                    if (cdata(38, rc) > arenaop(1) || cdata(9, rc) != -3) {
                        chara_vanquish(rc);
                        --cnt;
                        continue;
                    }
                }
            }
        }
    }
    if (gdata(20) == 40) {
        map_initcustom(u8"arena_2"s);
        mdata(10) = 0;
        mdata(13) = 81;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                if (cnt == 0 || cnt == 56) { continue; }
                if (followerin(cnt) == 0) {
                    cdata(0, cnt) = 6;
                    cdata(1, cnt) = 0;
                    cdata(2, cnt) = 0;
                } else {
                    cdata(0, cnt) = 1;
                }
            }
        }
        map_placeplayer();
        petarenawin = 0;
        if (arenaimport == 1) {
            file = ""s + userfile;
            id = 0;
            label_2095();
            importmode = 1;
            fmode = 21;
            label_2107();
            label_2111();
        } else {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (arenaop(1)); cnt < cnt_end; ++cnt) {
                    flt(arenaop(2), calcfixlv(3));
                    characreate(-1, 0, -3, 0);
                    map(cdata(1, rc), cdata(2, rc), 1) = 0;
                    f = 1;
                    if (arenaop == 0) {
                        if (cdata(38, rc) < arenaop(2) / 2) { f = 0; }
                    }
                    if (cdata(9, rc) != -3) { f = 0; }
                    if (f == 0) {
                        chara_vanquish(rc);
                        --cnt;
                        continue;
                    }
                    map_placearena(rc, 1);
                    if (cnt == 0) { enemyteam = rc; }
                }
            }
        }
        {
            int cnt = 57;
            for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt) {
                if (cdata(9, cnt) == -3) { cbitmod(966, cnt, 1); }
            }
        }
    }
    if (gdata(20) == 22) {
        map_initcustom(u8"god"s);
        mdata(10) = 0;
        mdata(13) = 63;
        flt();
        characreate(-1, 175, 12, 14);
        map_placeplayer();
    }
    if (gdata(20) == 23) {
        map_initcustom(u8"god"s);
        mdata(10) = 0;
        mdata(13) = 63;
        flt();
        characreate(-1, 177, 12, 14);
        map_placeplayer();
    }
    if (gdata(20) == 24) {
        map_initcustom(u8"god"s);
        mdata(13) = 63;
        mdata(10) = 0;
        flt();
        characreate(-1, 178, 12, 14);
        map_placeplayer();
    }
    if (gdata(20) == 7) {
        map_initcustom(u8"home"s + gdata(24));
        mdata(13) = 68;
        gdata(26) = 4;
        map_placeplayer();
        mdata(15) = 0;
        mdata(12) = 3;
        if (gdata(22) == 1) {
            if (gdata(24) == 0) {
                mdata(20) = 1;
                flt();
                characreate(-1, 33, 18, 10);
                cdata(150, rc) = 3;
                flt();
                characreate(-1, 34, 16, 11);
                cdata(150, rc) = 3;
                flt();
                itemcreate(-1, 510, 6, 10, 0);
                inv(9, ci) = 3;
                flt();
                itemcreate(-1, 547, 15, 19, 0);
                inv(9, ci) = 4;
                flt();
                itemcreate(-1, 579, 9, 8, 0);
                inv(9, ci) = 6;
                flt();
                itemcreate(-1, 24, 18, 19, 0);
                inv(25, ci) = 1;
            } else {
                file = u8"inv_"s + mid + u8".s2"s;
                fmode = 3;
                label_2107();
                inv_getheader(-1);
                {
                    int cnt = invhead;
                    for (int cnt_end = cnt + (invrange); cnt < cnt_end; ++cnt) {
                        if (inv(0, cnt) == 0) { continue; }
                        inv(5, cnt) = mdata(0) / 2;
                        inv(6, cnt) = mdata(1) / 2;
                        cell_refresh(inv(5, cnt), inv(6, cnt));
                    }
                }
                fmode = 17;
                label_2107();
                {
                    int cnt = 57;
                    for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt) {
                        cdata(1, cnt) = mdata(0) / 2;
                        cdata(2, cnt) = mdata(1) / 2;
                        cdata(171, cnt) = mdata(0) / 2;
                        cdata(172, cnt) = mdata(1) / 2;
                    }
                }
            }
            if (gdata(24) == 5) {
                flt();
                characreate(-1, 1, 31, 20);
                cdata(150, rc) = 1006;
                cdata(151, rc) = 10;
                sngeneral(cdatan(0, rc));
                flt();
                characreate(-1, 1, 9, 20);
                cdata(150, rc) = 1001;
                cdata(151, rc) = 12;
                snarmor(cdatan(0, rc));
                flt();
                characreate(-1, 1, 4, 20);
                cdata(150, rc) = 1008;
                cdata(151, rc) = 10;
                sngoods(cdatan(0, rc));
                flt();
                characreate(-1, 41, 4, 11);
                cdata(150, rc) = 5;
                flt();
                characreate(-1, 70, 30, 11);
                cdata(150, rc) = 9;
                flt();
                characreate(-1, 74, 30, 4);
                cdata(150, rc) = 12;
                flt();
                characreate(-1, 41, 4, 4);
                cdata(150, rc) = 1004;
                cdata(151, rc) = 11;
                snmagic(cdatan(0, rc));
            }
        } else {
            flt();
            itemcreate(-1, 219, cdata(1, 0), cdata(2, 0), 0);
        }
        label_1711();
    }
    if (gdata(20) == 4) {
        map_initcustom(u8"ntyris"s);
        label_1747();
        map_placeplayer();
    }
    if (gdata(20) == 44) {
        map_initcustom(u8"styris"s);
        label_1747();
        map_placeplayer();
    }
    if (gdata(20) == 47) {
        map_initcustom(u8"test"s);
        label_1747();
        map_placeplayer();
    }
    if (gdata(20) == 14) {
        if (gdata(22) == 1) {
            mdata(10) = 35;
            map_initcustom(u8"rogueden"s);
            map_placeplayer();
            mdata(15) = 0;
            flt();
            characreate(-1, 253, 23, 14);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 259, 13, 18);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 294, 16, 17);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 1, 10, 17);
            cdata(150, rc) = 1009;
            cdata(151, rc) = 12;
            sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 70, 15, 15);
            cdata(150, rc) = 9;
            flt();
            characreate(-1, 1, 13, 3);
            cdata(150, rc) = 1006;
            cdata(151, rc) = 10;
            sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 29, 23);
            cdata(150, rc) = 1005;
            cdata(151, rc) = 8;
            sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 26, 7);
            cdata(150, rc) = 1008;
            cdata(151, rc) = 10;
            sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 30, 4);
            cdata(150, rc) = 1007;
            cdata(151, rc) = 10;
            snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 29, 4);
            cdata(150, rc) = 17;
            cdatan(0, rc) = lang(u8"謎の奴隷商人"s, u8"The slave master"s);
            flt();
            characreate(-1, 1, 10, 6);
            cdata(150, rc) = 1001;
            cdata(151, rc) = 12;
            snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 73, 7, 15);
            cdata(150, rc) = 10;
            flt();
            characreate(-1, 38, 9, 18);
            cdata(150, rc) = 6;
            cdatan(0, rc) = lang(
                u8"ダルフィ"s + cdatan(0, rc), cdatan(0, rc) + u8" of Derphy"s);
            flt();
            characreate(-1, 40, 13, 18);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 5, 26);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 69, 3, 28);
            cdata(150, rc) = 8;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 16, -3, 0);
                    cdata(150, rc) = 4;
                    flt();
                    characreate(-1, 39, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            label_2669();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt) {
                    dbid = 0;
                    label_1735();
                    characreate(-1, dbid, -3, 0);
                }
            }
        }
        if (gdata(22) == 3) {
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
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 40, 3, 6);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 3, 12);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 1, 5, 18);
            cdata(150, rc) = 1007;
            cdata(151, rc) = 10;
            snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 27, 13);
            cdata(150, rc) = 1007;
            cdata(151, rc) = 10;
            snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 21, 19);
            cdata(150, rc) = 1021;
            cdata(151, rc) = 10;
            cdatan(0, rc) = lang(u8"盗賊店の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the fence"s);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 293, -3, 0);
                }
            }
        }
    }
    if (gdata(20) == 15) {
        mdata(10) = 45;
        map_initcustom(u8"palmia"s);
        map_placeplayer();
        mdata(15) = 0;
        flt();
        characreate(-1, 70, 42, 27);
        cdata(150, rc) = 9;
        flt();
        characreate(-1, 74, 34, 3);
        cdata(150, rc) = 12;
        flt();
        characreate(-1, 73, 22, 31);
        cdata(150, rc) = 10;
        flt();
        characreate(-1, 142, 5, 15);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 247, 41, 11);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 301, 5, 6);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 320, 24, 6);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 320, 15, 22);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 326, 15, 22);
        cdata(150, rc) = 3;
        if (gdata(460) == 1000) {
            flt();
            characreate(-1, 246, 42, 11);
            cdata(150, rc) = 3;
        }
        flt();
        characreate(-1, 1, 48, 18);
        cdata(150, rc) = 1006;
        cdata(151, rc) = 10;
        sngeneral(cdatan(0, rc));
        flt();
        characreate(-1, 1, 30, 17);
        cdata(150, rc) = 1005;
        cdata(151, rc) = 8;
        sninn(cdatan(0, rc));
        flt();
        characreate(-1, 1, 48, 3);
        cdata(150, rc) = 1008;
        cdata(151, rc) = 8;
        sngoods(cdatan(0, rc));
        flt();
        characreate(-1, 1, 42, 17);
        cdata(150, rc) = 1001;
        cdata(151, rc) = 12;
        snarmor(cdatan(0, rc));
        flt();
        characreate(-1, 1, 11, 14);
        cdata(150, rc) = 1003;
        cdata(151, rc) = 9;
        snbakery(cdatan(0, rc));
        cdata(7, rc) = 138;
        flt();
        characreate(-1, 41, 41, 3);
        cdata(150, rc) = 1004;
        cdata(151, rc) = 11;
        snmagic(cdatan(0, rc));
        flt();
        characreate(-1, 1, 41, 28);
        cdata(150, rc) = 1009;
        cdata(151, rc) = 12;
        sntrade(cdatan(0, rc));
        flt();
        characreate(-1, 79, 7, 2);
        cdata(150, rc) = 15;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 80, 6, 2);
        cdata(150, rc) = 15;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 38, 49, 11);
        cdata(150, rc) = 6;
        cdatan(0, rc) = lang(u8"パルミア市街地の"s + cdatan(0, rc),
            cdatan(0, rc) + u8" of Palmia city"s);
        flt();
        characreate(-1, 40, 30, 27);
        cdata(150, rc) = 7;
        sntrainer(cdatan(0, rc));
        flt();
        characreate(-1, 41, 32, 27);
        cdata(150, rc) = 5;
        flt();
        characreate(-1, 69, 29, 28);
        cdata(150, rc) = 8;
        flt();
        characreate(-1, 77, 16, 5);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 16, 9);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 5, 3);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 8, 3);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 35, 14);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 38, 14);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 29, 2);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 19, 18);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        flt();
        characreate(-1, 77, 22, 18);
        cdata(150, rc) = 14;
        cdata(202, rc) = 3;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 16, -3, 0);
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 39, -3, 0);
                cdata(150, rc) = 4;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 77, -3, 0);
                cdata(150, rc) = 14;
            }
        }
        label_2669();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (25); cnt < cnt_end; ++cnt) {
                dbid = 0;
                label_1735();
                characreate(-1, dbid, -3, 0);
            }
        }
    }
    if (gdata(20) == 36) {
        if (gdata(22) == 1) {
            mdata(10) = 40;
            map_initcustom(u8"lumiest"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata(465)) { cell_featset(18, 45, tile_downstairs, 11, 20); }
            flt();
            characreate(-1, 252, 12, 24);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 280, 21, 3);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 290, 5, 20);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 320, 28, 29);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 41, 19);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 32, 43);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 29, 28);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 16, 45);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 13, 24);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 70, 41, 42);
            cdata(150, rc) = 9;
            flt();
            characreate(-1, 74, 10, 16);
            cdata(150, rc) = 12;
            flt();
            characreate(-1, 1, 47, 30);
            cdata(150, rc) = 1006;
            cdata(151, rc) = 10;
            sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 24, 47);
            cdata(150, rc) = 1005;
            cdata(151, rc) = 8;
            sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 37, 30);
            cdata(150, rc) = 1001;
            cdata(151, rc) = 12;
            snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 37, 12);
            cdata(150, rc) = 1003;
            cdata(151, rc) = 9;
            snbakery(cdatan(0, rc));
            cdata(7, rc) = 138;
            flt();
            characreate(-1, 41, 6, 15);
            cdata(150, rc) = 1004;
            cdata(151, rc) = 11;
            snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 33, 43);
            cdata(150, rc) = 1009;
            cdata(151, rc) = 12;
            sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 47, 12);
            cdata(150, rc) = 1014;
            cdata(151, rc) = 5;
            snfish(cdatan(0, rc));
            flt();
            characreate(-1, 38, 3, 38);
            cdata(150, rc) = 6;
            cdatan(0, rc) = lang(u8"ルミエストの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Lumiest"s);
            flt();
            characreate(-1, 40, 21, 28);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 21, 30);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 69, 23, 38);
            cdata(150, rc) = 8;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (6); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 16, -3, 0);
                    cdata(150, rc) = 4;
                    flt();
                    characreate(-1, 39, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (7); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 77, -3, 0);
                    cdata(150, rc) = 14;
                }
            }
            label_2669();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (25); cnt < cnt_end; ++cnt) {
                    dbid = 0;
                    label_1735();
                    characreate(-1, dbid, -3, 0);
                }
            }
        }
        if (gdata(22) == 3) {
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
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 41, 27, 8);
            cdata(150, rc) = 1020;
            cdatan(0, rc) = lang(u8"魔法書作家の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the spell writer"s);
            flt();
            characreate(-1, 41, 22, 8);
            cdata(150, rc) = 1004;
            cdata(151, rc) = 11;
            snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 74, 3, 9);
            cdata(150, rc) = 12;
            flt();
            characreate(-1, 40, 12, 6);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 3, 3);
            cdata(150, rc) = 5;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 289, -3, 0);
                }
            }
        }
        if (gdata(22) == 20) {
            mdata(12) = 0;
            map_initcustom(u8"sqSewer"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"ルミエスト下水道"s, u8"The Sewer"s);
            put_questtarget();
            gdata(26) = 1;
            map_placeplayer();
        }
    }
    if (gdata(20) == 12) {
        if (gdata(22) == 1) {
            mdata(10) = 35;
            map_initcustom(u8"yowyn"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata(456)) { cell_featset(23, 22, tile_downstairs, 11, 3); }
            flt();
            characreate(-1, 224, 3, 17);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 227, 26, 11);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 231, 14, 20);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 1, 11, 5);
            cdata(150, rc) = 1006;
            cdata(151, rc) = 10;
            sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 25, 8);
            cdata(150, rc) = 1005;
            cdata(151, rc) = 8;
            sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 7, 8);
            cdata(150, rc) = 1008;
            cdata(151, rc) = 8;
            sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 14);
            cdata(150, rc) = 1009;
            cdata(151, rc) = 12;
            sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 35, 18);
            cdata(150, rc) = 22;
            cdatan(0, rc) = lang(u8"馬屋の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the horse master"s);
            flt();
            characreate(-1, 267, 33, 16);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 267, 37, 19);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 268, 34, 19);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 268, 38, 16);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 38, 3, 4);
            cdata(150, rc) = 6;
            cdatan(0, rc) = lang(u8"ヨウィンの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Yowyn"s);
            flt();
            characreate(-1, 40, 20, 14);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 24, 16);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 69, 26, 16);
            cdata(150, rc) = 8;
            flt();
            characreate(-1, 213, 14, 12);
            cdata(150, rc) = 3;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 16, -3, 0);
                    cdata(150, rc) = 4;
                    flt();
                    characreate(-1, 39, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 77, -3, 0);
                    cdata(150, rc) = 14;
                }
            }
            label_2669();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (15); cnt < cnt_end; ++cnt) {
                    dbid = 0;
                    label_1735();
                    characreate(-1, dbid, -3, 0);
                }
            }
        }
        if (gdata(22) == 3) {
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
        if (gdata(22) == 4) {
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
            gdata(26) = 8;
            map_placeplayer();
            listmax = 0;
            {
                int cnt = 57;
                for (int cnt_end = cnt + (188); cnt < cnt_end; ++cnt) {
                    if (cdata(0, cnt) == 1) {
                        if (cbit(970, cnt) == 1) {
                            list(0, listmax) = cnt;
                            ++listmax;
                        }
                    }
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (30); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 233 + 2 * (cnt > 22), 11, 16);
                    cdata(9, rc) = 10;
                    cdata(69, rc) = 10;
                    cdata(201, rc) = 100;
                    p = list(0, rnd(listmax));
                    cdata(29, rc) = p;
                    cdata(201, p) = 100;
                    cdata(29, p) = rc;
                }
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata(20) == 33) {
        mdata(10) = 35;
        map_initcustom(u8"noyel"s);
        map_placeplayer();
        mdata(15) = 0;
        flt();
        characreate(-1, 202, 46, 18);
        gdata(259) = rc;
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 203, 47, 18);
        cdata(150, rc) = 1015;
        flt();
        characreate(-1, 35, 47, 20);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 35, 45, 19);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 35, 49, 20);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 326, 28, 22);
        cdata(150, rc) = 3;
        flt();
        characreate(-1, 221, 19, 3);
        cdata(150, rc) = 3;
        if (gdata(453) != 1001) {
            flt();
            characreate(-1, 222, 19, 2);
            cdata(150, rc) = 3;
        }
        flt();
        characreate(-1, 70, 40, 33);
        cdata(150, rc) = 9;
        flt();
        characreate(-1, 74, 44, 6);
        cdata(150, rc) = 12;
        flt();
        characreate(-1, 206, 44, 3);
        cdata(150, rc) = 19;
        flt();
        characreate(-1, 1, 19, 31);
        cdata(150, rc) = 1001;
        cdata(151, rc) = 12;
        snarmor(cdatan(0, rc));
        flt();
        characreate(-1, 1, 11, 31);
        cdata(150, rc) = 1006;
        cdata(151, rc) = 10;
        sngeneral(cdatan(0, rc));
        flt();
        characreate(-1, 1, 38, 34);
        cdata(150, rc) = 1005;
        cdata(151, rc) = 8;
        sninn(cdatan(0, rc));
        flt();
        characreate(-1, 1, 5, 27);
        cdata(150, rc) = 1003;
        cdata(151, rc) = 9;
        snbakery(cdatan(0, rc));
        cdata(7, rc) = 138;
        flt();
        characreate(-1, 41, 56, 5);
        cdata(150, rc) = 1004;
        cdata(151, rc) = 11;
        snmagic(cdatan(0, rc));
        flt();
        characreate(-1, 1, 39, 35);
        cdata(150, rc) = 1009;
        cdata(151, rc) = 12;
        sntrade(cdatan(0, rc));
        flt();
        characreate(-1, 38, 5, 18);
        cdata(150, rc) = 6;
        cdatan(0, rc) = lang(
            u8"ノイエルの"s + cdatan(0, rc), cdatan(0, rc) + u8" of Noyel"s);
        flt();
        characreate(-1, 40, 18, 20);
        cdata(150, rc) = 7;
        sntrainer(cdatan(0, rc));
        flt();
        characreate(-1, 41, 4, 33);
        cdata(150, rc) = 5;
        flt();
        characreate(-1, 69, 6, 33);
        cdata(150, rc) = 8;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 16, rnd(32), rnd(mdata(1)));
                cdata(150, rc) = 4;
                flt();
                characreate(-1, 39, rnd(32), rnd(mdata(1)));
                cdata(150, rc) = 4;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt) {
                flt();
                characreate(-1, 77, rnd(32), rnd(mdata(1)));
                cdata(150, rc) = 14;
            }
        }
        label_2669();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (8); cnt < cnt_end; ++cnt) {
                label_1735();
                characreate(-1, 35, rnd(11) + 25, rnd(5) + 15);
                cdata(150, rc) = 3;
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt) {
                dbid = 0;
                label_1735();
                characreate(-1, dbid, rnd(55), rnd(mdata(1)));
            }
        }
    }
    if (gdata(20) == 11) {
        if (gdata(22) == 1) {
            mdata(10) = 40;
            map_initcustom(u8"kapul"s);
            map_placeplayer();
            mdata(15) = 0;
            flt();
            characreate(-1, 223, 15, 18);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 243, 36, 27);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 279, 5, 26);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 297, 29, 3);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 320, 24, 21);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 320, 12, 26);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 320, 8, 11);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 8, 14);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 1, 16, 17);
            cdata(150, rc) = 1009;
            cdata(151, rc) = 12;
            sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 23, 7);
            cdata(150, rc) = 1001;
            cdata(151, rc) = 12;
            snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 32, 14);
            cdata(150, rc) = 1006;
            cdata(151, rc) = 10;
            sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 1, 22, 14);
            cdata(150, rc) = 1008;
            cdata(151, rc) = 10;
            sngoods(cdatan(0, rc));
            flt();
            characreate(-1, 1, 16, 25);
            cdata(150, rc) = 1007;
            cdata(151, rc) = 10;
            snblack(cdatan(0, rc));
            flt();
            characreate(-1, 1, 17, 28);
            cdata(150, rc) = 1002;
            cdata(151, rc) = 10;
            snfood(cdatan(0, rc));
            flt();
            characreate(-1, 41, 22, 22);
            cdata(150, rc) = 1004;
            cdata(151, rc) = 11;
            snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 35, 3);
            cdata(150, rc) = 1005;
            cdata(151, rc) = 8;
            sninn(cdatan(0, rc));
            flt();
            characreate(-1, 70, 15, 15);
            cdata(150, rc) = 9;
            flt();
            characreate(-1, 73, 26, 3);
            cdata(150, rc) = 10;
            flt();
            characreate(-1, 179, 25, 4);
            cdata(150, rc) = 11;
            flt();
            characreate(-1, 38, 8, 12);
            cdata(150, rc) = 6;
            cdatan(0, rc) = lang(u8"ポート・カプールの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Port Kapul"s);
            flt();
            characreate(-1, 40, 16, 4);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 14, 4);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 69, 17, 5);
            cdata(150, rc) = 8;
            flt();
            characreate(-1, 74, 27, 11);
            cdata(150, rc) = 12;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (2); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 16, -3, 0);
                    cdata(150, rc) = 4;
                    flt();
                    characreate(-1, 39, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 71, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 76, -3, 0);
                    cdata(150, rc) = 14;
                }
            }
            flt();
            characreate(-1, 72, 7, 6);
            cdata(150, rc) = 4;
            label_2669();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt) {
                    label_1735();
                    characreate(-1, 0, -3, 0);
                }
            }
        }
        if (gdata(22) == 3) {
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
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 74, 28, 10);
            cdata(150, rc) = 12;
            flt();
            characreate(-1, 40, 15, 10);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 41, 14, 18);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 1, 29, 15);
            cdata(150, rc) = 1001;
            cdata(151, rc) = 12;
            snarmor(cdatan(0, rc));
            {
                int cnt = 0;
                for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 295, -3, 0);
                }
            }
        }
        if (gdata(22) == 25) {
            mdata(12) = 0;
            map_initcustom(u8"sqkamikaze"s);
            mdata(14) = 2;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdata(7) = 0;
            mdatan(0) = lang(u8"戦場"s, u8"Doom Ground"s);
            gdata(26) = 4;
            gdata(261) = 0;
            map_placeplayer();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 204, cdata(1, 0), cdata(2, 0));
                    cdata(9, rc) = 10;
                    cdata(69, rc) = 10;
                }
            }
            noaggrorefresh = 1;
        }
    }
    if (gdata(20) == 5) {
        if (gdata(22) == 1) {
            mdata(10) = 40;
            map_initcustom(u8"vernis"s);
            map_placeplayer();
            mdata(15) = 0;
            if (gdata(451)) { cell_featset(48, 5, tile_downstairs, 11, 4); }
            flt();
            characreate(-1, 28, 39, 3);
            flt();
            characreate(-1, 29, 42, 23);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 30, 24, 5);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 31, 40, 24);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 32, 40, 25);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 226, 30, 5);
            cdata(150, rc) = 3;
            flt();
            characreate(-1, 326, 42, 24);
            cdata(150, rc) = 3;
            if (gdata(455) == 1000) {
                flt();
                characreate(-1, 225, 31, 4);
                cdata(150, rc) = 3;
            }
            flt();
            characreate(-1, 1, 47, 9);
            cdata(150, rc) = 1014;
            cdata(151, rc) = 5;
            snfish(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 12);
            cdata(150, rc) = 1001;
            cdata(151, rc) = 12;
            snarmor(cdatan(0, rc));
            flt();
            characreate(-1, 1, 39, 27);
            cdata(150, rc) = 1009;
            cdata(151, rc) = 12;
            sntrade(cdatan(0, rc));
            flt();
            characreate(-1, 1, 10, 15);
            cdata(150, rc) = 1006;
            cdata(151, rc) = 10;
            sngeneral(cdatan(0, rc));
            flt();
            characreate(-1, 41, 7, 26);
            cdata(150, rc) = 1004;
            cdata(151, rc) = 11;
            snmagic(cdatan(0, rc));
            flt();
            characreate(-1, 1, 14, 25);
            cdata(150, rc) = 1005;
            cdata(151, rc) = 8;
            sninn(cdatan(0, rc));
            flt();
            characreate(-1, 1, 22, 26);
            cdata(150, rc) = 1003;
            cdata(151, rc) = 9;
            snbakery(cdatan(0, rc));
            cdata(7, rc) = 138;
            flt();
            characreate(-1, 41, 28, 16);
            cdata(150, rc) = 5;
            flt();
            characreate(-1, 70, 38, 27);
            cdata(150, rc) = 9;
            flt();
            characreate(-1, 74, 6, 25);
            cdata(150, rc) = 12;
            flt();
            characreate(-1, 38, 10, 7);
            cdata(150, rc) = 6;
            cdatan(0, rc) = lang(u8"ヴェルニースの"s + cdatan(0, rc),
                cdatan(0, rc) + u8" of Vernis"s);
            flt();
            characreate(-1, 40, 27, 16);
            cdata(150, rc) = 7;
            sntrainer(cdatan(0, rc));
            flt();
            characreate(-1, 69, 25, 16);
            cdata(150, rc) = 8;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 16, -3, 0);
                    cdata(150, rc) = 4;
                    flt();
                    characreate(-1, 39, -3, 0);
                    cdata(150, rc) = 4;
                }
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt) {
                    flt();
                    characreate(-1, 77, -3, 0);
                    cdata(150, rc) = 14;
                }
            }
            label_2669();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (25); cnt < cnt_end; ++cnt) {
                    dbid = 0;
                    label_1735();
                    characreate(-1, dbid, -3, 0);
                }
            }
        }
        if (gdata(22) == 3) {
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
        if (gdata(22) == 4) {
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
        if (gdata(22) == 5) {
            mdata(12) = 0;
            map_initcustom(u8"sqNightmare"s);
            mdata(14) = 1;
            mdata(6) = 20;
            mdata(10) = 0;
            mdata(13) = 61;
            mdata(17) = 1;
            mdatan(0) = lang(u8"生体兵器実験場"s, u8"Test Site"s);
            put_questtarget();
            gdata(26) = 7;
            mapstartx = 6;
            mapstarty = 27;
            map_placeplayer();
        }
    }
    if (gdata(20) == 2) {
        mdata(0) = 34;
        mdata(1) = 22;
        mdata(10) = 4;
        mdata(15) = 0;
        map_initialize();
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                p = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        map(cnt, p, 0) = tile_default +
                            (rnd(tile_default(2)) == 0) * rnd(tile_default(1));
                    }
                }
            }
        }
        mdatan(0) = "";
        if (4 <= gdata(62) && gdata(62) < 9) {
            mdatan(0) = lang(u8"森"s, u8"Forest"s);
            map_randomtile(8, 25);
            map_randomtile(0, 10);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (20 + rnd(20)); cnt < cnt_end; ++cnt) {
                    flt();
                    flttypemajor = 80000;
                    itemcreate(-1, 0, -1, -1, 0);
                    inv(21, ci) = 1;
                    map(inv(5, ci), inv(6, ci), 0) = 0;
                }
            }
        }
        if (264 <= gdata(62) && gdata(62) < 363) {
            mdatan(0) = lang(u8"水上"s, u8"Sea"s);
        }
        if (9 <= gdata(62) && gdata(62) < 13) {
            mdatan(0) = lang(u8"草原"s, u8"Grassland"s);
            map_randomtile(9, 10);
            map_randomtile(10, 10);
            map_randomtile(0, 30);
            map_randomtile(1, 4);
            map_randomtile(4, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (10 + rnd(10)); cnt < cnt_end; ++cnt) {
                    flt();
                    flttypemajor = 80000;
                    itemcreate(-1, 0, -1, -1, 0);
                    inv(21, ci) = 1;
                }
            }
        }
        if (13 <= gdata(62) && gdata(62) < 17) {
            mdatan(0) = lang(u8"荒野"s, u8"Desert"s);
            map_randomtile(18, 25);
            map_randomtile(17, 10);
            map_randomtile(19, 2);
            map_randomtile(20, 4);
            map_randomtile(21, 2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4 + rnd(4)); cnt < cnt_end; ++cnt) {
                    flt();
                    itemcreate(-1, 527, -1, -1, 0);
                    inv(21, ci) = 1;
                }
            }
        }
        if (chipm(0, gdata(62)) == 4) {
            mdatan(0) = lang(u8"雪原"s, u8"Snow Field"s);
            map_randomtile(57, 4);
            map_randomtile(56, 4);
            map_randomtile(49, 2);
            map_randomtile(46, 1);
            map_randomtile(47, 1);
            map_randomtile(48, 1);
            map_randomtile(51, 1);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (3 + rnd(5)); cnt < cnt_end; ++cnt) {
                    flt();
                    flttypemajor = 80000;
                    fltselect = 8;
                    itemcreate(-1, 0, -1, -1, 0);
                    inv(21, ci) = 1;
                }
            }
        }
        if (mdatan(0) == ""s) {
            mdatan(0) = lang(u8"平地"s, u8"Plain Field"s);
            map_randomtile(1, 10);
            map_randomtile(2, 2);
            map_randomtile(3, 2);
            map_randomtile(4, 2);
            map_randomtile(5, 2);
            map_randomtile(6, 2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (5 + rnd(5)); cnt < cnt_end; ++cnt) {
                    flt();
                    flttypemajor = 80000;
                    itemcreate(-1, 0, -1, -1, 0);
                    inv(21, ci) = 1;
                }
            }
        }
        map_placeplayer();
        if (264 <= gdata(62) && gdata(62) < 363) {
        } else {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (4 + rnd(5)); cnt < cnt_end; ++cnt) {
                    flt();
                    flttypeminor = 64000;
                    itemcreate(-1, 0, -1, -1, 0);
                }
            }
        }
        if (encounter == 0) {
            {
                int cnt = 0;
                for (int cnt_end = cnt + (mdata(10) + 1); cnt < cnt_end;
                     ++cnt) {
                    label_1735();
                    flt();
                    characreate(-1, 0, -3, 0);
                }
            }
        }
        if (encounter == 4) {
            mdata(10) = 0;
            flt();
            initlv = encounterlv;
            characreate(-1, 302, cdata(1, 0), cdata(2, 0));
            {
                int cnt = 0;
                for (int cnt_end = cnt + (6 + rnd(6)); cnt < cnt_end; ++cnt) {
                    flt();
                    initlv = encounterlv + rnd(10);
                    characreate(-1, 303 + rnd(3), 14, 11);
                    cdatan(0, rc) += u8" Lv"s + cdata(38, rc);
                }
            }
            gdatan(1) = random_title(2);
            evadd(23);
        }
        if (encounter == 3) {
            mdata(10) = 0;
            mdata(6) = 7;
            rq = encounterref;
            gdata(70) = 1007;
            gdata(71) = 1;
            gdata(72) = rq;
            gdata(73) = 1;
            p = rnd(3) + 5;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (p); cnt < cnt_end; ++cnt) {
                    flt(qdata(5, rq), 3);
                    characreate(-1, 0, cdata(1, 0), cdata(2, 0));
                    if (stat != 0) {
                        cdata(201, rc) = 30;
                        cdata(9, rc) = -3;
                        cdata(69, rc) = -3;
                    }
                }
            }
        }
        if (encounter == 2) {
            flt();
            characreate(-1, 1, 10, 11);
            cdata(150, rc) = 1010;
            cdata(151, rc) = encounterlv;
            cdatan(0, rc) = lang(u8"行商人の"s + cdatan(0, rc),
                sncnv(cdatan(0, rc)) + u8"the wandering vendor"s);
            generatemoney(rc);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (encounterlv / 2 + 1); cnt < cnt_end;
                     ++cnt) {
                    r1 = rc;
                    r2 = 1;
                    label_1454();
                }
            }
            evadd(11);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (6 + rnd(6)); cnt < cnt_end; ++cnt) {
                    flt();
                    initlv = encounterlv + rnd(10);
                    characreate(-1, 159 + rnd(3), 14, 11);
                    cdata(150, rc) = 16;
                    cdatan(0, rc) += u8" Lv"s + cdata(38, rc);
                }
            }
        }
        if (encounter == 1) {
            p = rnd(9);
            if (cdata(38, 0) <= 5) { p = rnd(3); }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (2 + p); cnt < cnt_end; ++cnt) {
                    flt(calcobjlv(encounterlv), calcfixlv(2));
                    if (gdata(17) == 1) {
                        if (33 <= gdata(62) && gdata(62) < 66) {
                        } else {
                            if (rnd(3) == 0) { fixlv = 5; }
                        }
                    }
                    if (cnt < 4) {
                        characreate(-1, 0, cdata(1, 0), cdata(2, 0));
                    } else {
                        characreate(-1, 0, -3, 0);
                    }
                    cdata(201, rc) = 30;
                }
            }
        }
        encounter = 0;
    }
    if (gdata(20) == 42) {
        label_16952();
        if (gdata(186) == 0) { gdata(186) = adata(17, gdata(20)) + 4; }
        if (gdata(186) <= gdata(22)) {
            evadd(29);
        } else {
            adata(20, gdata(20)) = 0;
        }
    }
    if (gdata(20) == 3) {
        map_tileset(mdata(12));
        {
            int cnt = 0;
            for (int cnt_end = cnt + (1); cnt < cnt_end; ++cnt) {
                if (gdata(22) == adata(10, gdata(20))) {
                    map_initcustom(u8"lesimas_1"s);
                    mdata(10) = 0;
                    mdata(7) = 0;
                    mdata(13) = 66;
                    mdatan(0) = lang(u8"レシマス最深層"s, u8"The Depth"s);
                    if (gdata(252) < 170) { evadd(3); }
                    x = 16;
                    y = 13;
                    cell_featset(x, y, tile_upstairs, 10);
                    mdata(5) = y * 1000 + x;
                    map_placeplayer();
                    if (npcmemory(0, 2) == 0) {
                        flt();
                        characreate(-1, 2, 16, 6);
                    } else {
                        if (npcmemory(0, 23) == 0) {
                            flt();
                            characreate(-1, 23, 16, 6);
                        }
                    }
                    break;
                }
                label_16952();
                break;
            }
        }
        if (gdata(22) == 3) {
            characreate(-1, 139, cdata(1, 0), cdata(2, 0));
            cdata(150, rc) = 3;
            cdata(202, rc) = 3;
        }
        if (gdata(22) == 17) {
            characreate(-1, 146, cdata(1, 0), cdata(2, 0));
            cdata(150, rc) = 3;
            cdata(202, rc) = 3;
        }
    }
    if (gdata(20) == 16) {
        if (gdata(22) == adata(10, gdata(20))) {
            map_initcustom(u8"firet1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        } else {
            label_16952();
        }
    }
    if (gdata(20) == 17) {
        if (gdata(22) == adata(10, gdata(20))) {
            map_initcustom(u8"undeadt1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        } else {
            label_16952();
        }
    }
    if (gdata(20) == 18) {
        if (gdata(22) == adata(10, gdata(20))) {
            map_initcustom(u8"roguet1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        } else {
            label_16952();
        }
    }
    if (gdata(20) == 19) {
        if (gdata(22) == adata(10, gdata(20))) {
            map_initcustom(u8"d_1"s);
            mdata(10) = 0;
            mdata(13) = 66;
            map_placeplayer();
        } else {
            label_16952();
        }
    }
    if (gdata(20) == 27) {
        label_16952();
        if (gdata(22) == adata(10, gdata(20))) {
            if (gdata(455) < 2) {
                if (findally(225) == -1) {
                    flt();
                    characreate(-1, 225, -3, 0);
                    cbitmod(979, rc, 1);
                }
            }
        }
    }
    if (gdata(20) == 38) {
        label_16952();
        if (gdata(22) == adata(10, gdata(20))) {
            if (gdata(472) < 2) {
                flt();
                characreate(-1, 300, -3, 0);
            }
        }
    }
    if (gdata(20) == 28) {
        label_16952();
        if (gdata(22) == adata(10, gdata(20))) {
            if (gdata(458) < 2) {
                flt();
                characreate(-1, 242, -3, 0);
                tc = rc;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt) {
                        flt();
                        characreate(-1, 240, cdata(1, tc), cdata(2, tc));
                    }
                }
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt) {
                        flt();
                        characreate(-1, 238, cdata(1, tc), cdata(2, tc));
                        flt();
                        characreate(-1, 237, cdata(1, tc), cdata(2, tc));
                    }
                }
            }
        }
    }
    if (gdata(20) == 37) {
        if (gdata(22) == 20) {
            map_initcustom(u8"sqPyramid"s);
            mdata(10) = 40;
            mdata(13) = 61;
            map_placeplayer();
            {
                int cnt = 0;
                for (int cnt_end = cnt + (mdata(10) + 1); cnt < cnt_end;
                     ++cnt) {
                    label_1735();
                    characreate(-1, 0, -3, 0);
                }
            }
        }
        if (gdata(22) == 21) {
            map_initcustom(u8"sqPyramid2"s);
            mdata(10) = 0;
            mdata(13) = 61;
            map_placeplayer();
        }
    }
    if (gdata(20) == 26) { label_16952(); }
    map_setfog();
    if (gdata(20) == 40 || dbg_revealmap || gdata(20) == 6 || mdata(6) == 3 ||
        mdata(6) == 1 || mdata(6) == 5 || mdata(6) == 2 || gdata(20) == 30 ||
        gdata(20) == 32 || gdata(20) == 34 || gdata(20) == 35 ||
        gdata(20) == 13 && gdata(70) == 1009) {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                y = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        map(cnt, y, 2) = map(cnt, y, 0);
                    }
                }
            }
        }
    }
    if (mapupdate == 1) {
        if (mdata(6) == 1) {
            f = 0;
            i = 0;
            {
                int cnt = 300;
                for (int cnt_end = cnt + (200); cnt < cnt_end; ++cnt) {
                    p = cnt;
                    if (adata(1, cnt) == 0 || adata(2, cnt) == 0 ||
                        adata(16, cnt) == 0) {
                        continue;
                    }
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (300); cnt < cnt_end; ++cnt) {
                            if (adata(1, cnt) == 0 || adata(2, cnt) == 0 ||
                                adata(16, cnt) == 0) {
                                continue;
                            }
                            if (adata(1, p) == adata(1, cnt)) {
                                if (adata(2, p) == adata(2, cnt)) {
                                    {
                                        int cnt = 0;
                                        for (;; ++cnt) {
                                            await();
                                            dx = limit(rnd(cnt / 4 + 1) + 1, 1,
                                                mdata(0));
                                            dy = limit(rnd(cnt / 4 + 1) + 1, 1,
                                                mdata(1));
                                            x = adata(1, p) + rnd(dx) - rnd(dx);
                                            y = adata(2, p) + rnd(dy) - rnd(dy);
                                            if (x < 0 || y < 0 ||
                                                x >= mdata(0) ||
                                                y >= mdata(1)) {
                                                continue;
                                            }
                                            if (33 <= map(x, y, 0) &&
                                                map(x, y, 0) < 66) {
                                                continue;
                                            }
                                            if (map(x, y, 0) > 19) { continue; }
                                            i = 1;
                                            {
                                                int cnt = 0;
                                                for (int cnt_end = cnt + (300);
                                                     cnt < cnt_end; ++cnt) {
                                                    if (adata(1, cnt) == 0 ||
                                                        adata(2, cnt) == 0 ||
                                                        adata(16, cnt) == 0) {
                                                        continue;
                                                    }
                                                    if (x == adata(1, cnt)) {
                                                        if (y ==
                                                            adata(2, cnt)) {
                                                            i = 0;
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                            if (i == 0) { continue; }
                                            dialog(lang(
                                                u8"エリアが再配置されます。"s +
                                                    mapname(p) +
                                                    u8"の位置は、x"s +
                                                    adata(1, p) + u8":y"s +
                                                    adata(2, p) + u8"からx"s +
                                                    x + u8":y"s + y +
                                                    u8"に変更されます。"s,
                                                u8"The location of "s +
                                                    mapname(p) +
                                                    u8" has been changed from x"s +
                                                    adata(1, p) + u8":y"s +
                                                    adata(2, p) + u8" to x"s +
                                                    x + u8":y"s + y + u8"."s));
                                            adata(1, p) = x;
                                            adata(2, p) = y;
                                            ++f;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            label_1749();
        }
        mapupdate = 0;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt) {
                if (cdata(0, cnt) == 0) { continue; }
                if (cdata(150, cnt) >= 1000 && cdata(150, cnt) < 2000 ||
                    cdata(150, cnt) == 2003) {
                    cnt2 = cnt;
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (maxnpcbk); cnt < cnt_end;
                             ++cnt) {
                            if (cdata(150, cnt2) == rolebk(0, cnt)) {
                                cdata(151, cnt2) = rolebk(1, cnt);
                                rolebk(0, cnt) = 0;
                                rolebk(1, cnt) = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (maxmedal); cnt < cnt_end; ++cnt) {
                cell_featset(medalbk(0, cnt), medalbk(1, cnt), tile_hidden, 32);
            }
        }
    }
    randomize();
    mdata(19) = gdata(184);
    mdata(21) = 1;
label_1742_internal:
    if (gdata(20) == 4) {
        if (gdata(252) == 180) {
            cdata(1, 0) = adata(1, 11);
            cdata(2, 0) = adata(2, 11);
            gdata(35) = 1;
            gdata(60) = -1;
            msg_newline();
            msgtemp = lang(
                u8"  三年の月日が経ち、あなたは再びノースティリスに降り立った。"s,
                u8"  Three years elapsed and you set foot on cool soil of North Tyris's again."s);
        }
    }
    {
        int cnt = 16;
        for (int cnt_end = cnt + (39); cnt < cnt_end; ++cnt) {
            if (cdata(0, cnt) != 3) { continue; }
            if (cbit(969, cnt)) {
                cdata(9, cnt) = 10;
                cdata(80, cnt) = gdata(20);
                goto label_1743_internal;
            }
            if (cdata(80, cnt) != gdata(20)) { continue; }
            if (mdata(6) != 3 && mdata(6) != 2) { continue; }
            if (gdata(22) != 1) { continue; }
        label_1743_internal:
            if (gdata(20) == 6 || gdata(20) == 40) { continue; }
            rc = cnt;
            cdata(0, rc) = 1;
            if (cbit(969, cnt) == 1) {
                cxinit = cdata(1, 0);
                cyinit = cdata(2, 0);
                label_1532();
            } else {
                cxinit = -1;
                label_1532();
                cdata(50, rc) = cdata(51, rc);
                cdata(55, rc) = cdata(56, rc);
            }
        }
    }
    if (mdata(7) == 1) {
        if (gdata(13) + gdata(12) * 24 + gdata(11) * 24 * 30 +
                gdata(10) * 24 * 30 * 12 >=
            mdata(3)) {
            if (mdata(17) == 0) {
                if (mdata(3) != 0) {
                    if (gdata(22) == 1) {
                        if (gdata(20) == 36) { map_reload(u8"lumiest"s); }
                        if (gdata(20) == 5) { map_reload(u8"vernis"s); }
                        if (gdata(20) == 15) { map_reload(u8"palmia"s); }
                        if (gdata(20) == 11) { map_reload(u8"kapul"s); }
                        if (gdata(20) == 12) { map_reload(u8"yowyn"s); }
                        if (gdata(20) == 14) { map_reload(u8"rogueden"s); }
                        if (gdata(20) == 33) {
                            if (gdata(11) == 12) {
                                if (adata(29, gdata(20)) == 0) {
                                    adata(29, gdata(20)) = 1;
                                    label_1755();
                                }
                                map_reload(u8"noyel_fest"s);
                            } else {
                                if (adata(29, gdata(20)) == 1) {
                                    adata(29, gdata(20)) = 0;
                                    label_1755();
                                }
                                map_reload(u8"noyel"s);
                            }
                            gdata(258) = 0;
                        }
                    }
                }
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (mdata(1)); cnt < cnt_end; ++cnt) {
                y = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (mdata(0)); cnt < cnt_end; ++cnt) {
                        map(cnt, y, 1) = 0;
                    }
                }
            }
        }
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt) {
                rc = cnt;
                cbitmod(987, rc, 0);
                if (rc < 57) {
                    if (mode == 11) { continue; }
                }
                if (cdata(0, rc) == 2) {
                    if (gdata(13) + gdata(12) * 24 + gdata(11) * 24 * 30 +
                            gdata(10) * 24 * 30 * 12 >=
                        cdata(5, rc)) {
                        label_1540();
                    } else {
                        continue;
                    }
                }
                if (cdata(0, rc) != 1) { continue; }
                if (cdata(150, rc) == 14) {
                    if (cdata(49, 0) < -30) {
                        if (cdata(38, 0) > cdata(38, rc)) {
                            r1 = rc;
                            r2 = 1;
                            label_1454();
                        }
                    }
                }
                if (rc >= 57) {
                    cdata(50, rc) = cdata(51, rc);
                    cdata(55, rc) = cdata(56, rc);
                    cdata(86, rc) = 0;
                }
                if (rc >= 57) {
                    if (mdata(8) == 1) {
                        cdata(1, rc) = cdata(171, rc);
                        cdata(2, rc) = cdata(172, rc);
                    }
                    if (cbit(970, rc) == 0) {
                        cdata(201, rc) = 0;
                        cdata(9, rc) = cdata(69, rc);
                    }
                    if (cdata(150, rc) == 14) {
                        if (cdata(49, 0) < -30) {
                            if (cbit(16, 0) == 0) {
                                cdata(201, rc) = 200;
                                cdata(9, rc) = -3;
                            }
                        }
                    }
                    if (mdata(6) == 3 || mdata(6) == 2) {
                        cdata(251, rc) = 0;
                        if (gdata(13) >= 22 || gdata(13) < 7) {
                            if (rnd(6) == 0) { cdata(251, rc) = rnd(400); }
                        }
                    }
                }
                if (rc == 0 || gdata(183) != rc) {
                    cell_check(cdata(1, rc), cdata(2, rc));
                    if (map(cdata(1, rc), cdata(2, rc), 1) != 0 ||
                        cellaccess != 1) {
                        {
                            int cnt = 0;
                            for (;; ++cnt) {
                                x = cdata(1, rc) + rnd((cnt / 2 + 2)) -
                                    rnd((cnt / 2 + 2));
                                y = cdata(2, rc) + rnd((cnt / 2 + 2)) -
                                    rnd((cnt / 2 + 2));
                                if (cnt > 100) {
                                    x = rnd(mdata(0));
                                    y = rnd(mdata(1));
                                }
                                if (cnt > 1000) { break; }
                                cell_check(x, y);
                                if (cellaccess == 1) {
                                    cdata(1, rc) = x;
                                    cdata(2, rc) = y;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (cbit(975, rc) == 0) {
                    map(cdata(1, rc), cdata(2, rc), 1) = rc + 1;
                }
            }
        }
    }
label_1744_internal:
    DIM4(efmap, 4, mdata(0), mdata(1));
    if (mdata(0) == 0 || mdata(1) == 0) {
        if (medit == 0) {
            dialog(lang(
                u8"マップのロードに失敗しました。"s, u8"Map loading failed."s));
            mode = 2;
            gdata(20) = 7;
            gdata(22) = 1;
            gdata(5) = adata(1, 7);
            gdata(6) = adata(2, 7);
            gdata(19) = 2;
            levelexitby = 4;
            goto label_17401;
        }
    }
    if (gdata(20) == 35) { label_2105(); }
    label_1745();
    gdata(3) = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt) {
            cdata(10, cnt) = 0;
            if (cdata(27, cnt) == 343) { getunid(cnt); }
            if (noaggrorefresh == 0) {
                cdata(29, cnt) = 0;
                cdata(201, cnt) = 0;
            }
            cdata(6, cnt) = 0;
            if (cnt > 57) {
                if (cdata(0, cnt) != 0) { ++gdata(3); }
            }
        }
    }
    cdata(80, 0) = gdata(20);
    cdata(81, 0) = gdata(22);
    raderx = -1;
    radery = -1;
    raderw = 120 / mdata(0) + 2;
    raderh = 84 / mdata(1) + 2;
    scx = cdata(1, 0);
    scy = cdata(2, 0);
    msync = 1;
    label_1746();
    label_1439();
    label_1428();
    if (mdata(6) == 3) { label_2671(); }
    if (mode == 11) { return; }
    if (gdata(252) == 9) {
        sceneid = 2;
        label_2680();
        gdata(252) = 10;
    }
    if (gdata(252) == 60) {
        sceneid = 5;
        label_2680();
        gdata(252) = 65;
    }
    if (gdata(252) == 110) {
        sceneid = 26;
        label_2680();
        gdata(252) = 115;
    }
    if (gdata(252) == 115) {
        if (gdata(253) + gdata(255) + gdata(254) >= 1) {
            sceneid = 28;
            label_2680();
            gdata(252) = 116;
        }
    }
    if (gdata(252) == 116) {
        if (gdata(253) + gdata(255) + gdata(254) >= 2) {
            sceneid = 29;
            label_2680();
            gdata(252) = 117;
        }
    }
    if (gdata(252) == 117) {
        if (gdata(253) + gdata(255) + gdata(254) >= 3) {
            sceneid = 30;
            label_2680();
            gdata(252) = 120;
        }
    }
    if (gdata(20) == 3) {
        if (gdata(252) == 10) {
            sceneid = 3;
            label_2680();
            gdata(252) = 20;
        }
        if (gdata(22) == 4) {
            if (gdata(252) == 65) {
                sceneid = 7;
                label_2680();
                gdata(252) = 70;
            }
        }
        if (gdata(22) == 7) {
            if (gdata(252) == 70) {
                sceneid = 15;
                label_2680();
                gdata(252) = 75;
            }
        }
        if (gdata(22) == 10) {
            if (gdata(252) == 75) {
                sceneid = 16;
                label_2680();
                gdata(252) = 80;
            }
        }
        if (gdata(22) == 14) {
            if (gdata(252) == 80) {
                sceneid = 17;
                label_2680();
                gdata(252) = 85;
            }
        }
        if (gdata(22) == 16) {
            if (gdata(252) == 85) {
                sceneid = 24;
                label_2680();
                gdata(252) = 90;
            }
        }
        if (gdata(22) == 26) {
            if (gdata(252) == 125) {
                sceneid = 33;
                label_2680();
                gdata(252) = 130;
            }
        }
        if (gdata(22) == 28) {
            if (gdata(252) == 130) {
                sceneid = 35;
                label_2680();
                gdata(252) = 135;
            }
        }
        if (gdata(22) == 31) {
            if (gdata(252) == 135) {
                sceneid = 40;
                label_2680();
                gdata(252) = 140;
            }
        }
        if (gdata(22) == 35) {
            if (gdata(252) == 140) {
                sceneid = 60;
                label_2680();
                gdata(252) = 145;
            }
        }
        if (gdata(22) == 38) {
            if (gdata(252) == 145) {
                sceneid = 70;
                label_2680();
                gdata(252) = 150;
            }
        }
        if (gdata(22) == 42) {
            if (gdata(252) == 150) {
                sceneid = 90;
                label_2680();
                gdata(252) = 160;
            }
        }
    }
    if (adata(16, gdata(20)) == 33) {
        tc = findchara(222);
        if (tc != 0) {
            if (gdata(453) >= 10) {
                cdata(7, tc) = 360;
                cdata(13, tc) = -1;
            }
        }
    }
    if (adata(16, gdata(20)) == 36) {
        if (gdata(22) == 3) { evadd(22, gdata(263)); }
    }
    if (adata(16, gdata(20)) == 14) {
        if (gdata(22) == 3) { evadd(22, gdata(265)); }
    }
    if (adata(16, gdata(20)) == 11) {
        if (gdata(22) == 3) { evadd(22, gdata(264)); }
    }
    if (gdata(20) == 5) {
        if (gdata(252) == 0) {
            sceneid = 1;
            label_2680();
            gdata(252) = 9;
        }
        if (gdata(257) == 0) {
            gdata(257) = 1;
            evadd(12);
        }
    }
    if (gdata(20) == 15) {
        if (gdata(252) == 30) {
            sceneid = 4;
            label_2680();
            gdata(252) = 40;
        }
        if (gdata(252) == 100) {
            sceneid = 25;
            label_2680();
            gdata(252) = 105;
        }
    }
    if (gdata(20) == 4) {
        if (gdata(252) == 180) {
            sceneid = 100;
            label_2680();
            gdata(252) = 200;
            gdata(10) += 3;
        }
    }
    if (adata(16, gdata(20)) == 8) {
        if (gdata(22) == adata(10, gdata(20))) {
            if (adata(20, gdata(20)) == -1) {
                msgtemp += lang(u8"辺りからは何の緊張感も感じられない。"s +
                        mapname(gdata(20)) + u8"の主はもういないようだ。"s,
                    u8"This place is pretty dull. The dungeon master is no longer sighted here."s);
            }
        }
    }
    label_0068();
    label_2088();
    noaggrorefresh = 0;
    if (adata(0, gdata(20)) == 1) {
        label_0200();
        label_1748();
    }
    if (mode == 3) {
        mode = 0;
        if (mapsubroutine == 0) {
            screenupdate = -1;
            label_1417();
            txt_conv();
            label_1419();
            if (evnum == 0) {
                label_2743(false);
            } else {
                label_2733();
                return;
            }
        } else {
            mapsubroutine = 0;
            return;
        }
    }
    wake_up();
    pcattacker = 0;
    cdata(29, 0) = 0;
    gdata(94) = 0;
    mode = 0;
    screenupdate = -1;
    label_1417();
    txt_conv();
    if (gdata(20) == 7) {
        if (gdata(252) != 0) {
            if (findchara(33) != 0) { chara_vanquish(findchara(33)); }
            if (findchara(34) != 0) { chara_vanquish(findchara(34)); }
        }
    }
    if (gdata(20) == 15) {
        if (gdata(252) >= 90) {
            if (findchara(80) != 0) { chara_vanquish(findchara(80)); }
        }
    }
    if (mdata(6) == 3) {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (gdata(75)); cnt < cnt_end; ++cnt) {
                if (qdata(3, cnt) == 1007) {
                    if (qdata(8, cnt) == 1) {
                        cnt2 = cnt;
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (16); cnt < cnt_end;
                                 ++cnt) {
                                if (cbit(963, cnt) == 1) {
                                    if (cdata(0, cnt) == 1) {
                                        if (cdata(27, cnt) == qdata(13, cnt2)) {
                                            if (qdata(12, cnt2) == gdata(20)) {
                                                evadd(16, cnt2, cnt);
                                                cbitmod(963, cnt, 0);
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
        }
    }
    if (adata(16, gdata(20)) == 101 || adata(16, gdata(20)) == 102) {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt) {
                label_1736();
            }
        }
    }
    if (mdata(7) == 1) { label_1576(); }
    if (adata(16, gdata(20)) == 102) { label_1726(); }
    if (adata(16, gdata(20)) == 101) { label_1728(); }
    if (gdata(20) == 7) { label_1730(); }
    if (adata(16, gdata(20)) == 31) {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt) {
                if (cbit(960, cnt) == 1) {
                    cdata(201, cnt) = 0;
                    cdata(9, cnt) = -1;
                    cdata(69, cnt) = -1;
                }
            }
        }
    }
    if (mdata(6) == 1) {
        if (cfg_extrahelp) {
            if (gdata(202) == 0) {
                if (mode == 0) {
                    if (cdata(141, 0) == 0) {
                        gdata(202) = 1;
                        ghelp = 2;
                        label_2701();
                    }
                }
            }
        }
    }
    if (mdata(6) == 3) {
        if (cfg_extrahelp) {
            if (gdata(203) == 0) {
                if (mode == 0) {
                    if (cdata(141, 0) == 0) {
                        gdata(203) = 1;
                        ghelp = 3;
                        label_2701();
                    }
                }
            }
        }
    }
    if (gdata(20) == 30) {
        if (cfg_extrahelp) {
            if (gdata(214) == 0) {
                if (mode == 0) {
                    if (cdata(141, 0) == 0) {
                        gdata(214) = 1;
                        ghelp = 14;
                        label_2701();
                    }
                }
            }
        }
    }
    if (mdata(6) == 3 || gdata(20) == 7 || mdata(6) == 2) {
        if (gdata(180) >= 16) {
            p = gdata(13) + gdata(12) * 24 + gdata(11) * 24 * 30 +
                gdata(10) * 24 * 30 * 12 - gdata(181);
            txtmore();
            txt(lang(cnvdate(gdata(181)) + u8"に"s + mapname(gdata(182)) +
                    u8"を発ってから、"s + p / 24 + u8"日と"s + p % 24 +
                    u8"時間の旅を終えた。"s,
                ""s + p / 24 + u8" days and "s + p % 24 +
                    u8" hours have passed since you left "s +
                    mapname(gdata(182)) + u8"."s));
            p = 0;
            exp = cdata(38, 0) * gdata(180) * sdata(182, 0) / 100 + 1;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (16); cnt < cnt_end; ++cnt) {
                    if (cdata(0, cnt) != 1) { continue; }
                    ++p;
                    cdata(35, cnt) += exp;
                }
            }
            if (p == 1) {
                s = u8"あなた"s;
            } else {
                s = u8"あなたとその仲間"s;
            }
            txtmore();
            txt(lang(s + u8"は"s + gdata(180) +
                    u8"マイルの距離を歩き、経験を積んだ。"s,
                u8"You've walked about "s + gdata(180) +
                    u8" miles and have gained experience."s));
            skillexp(182, 0, 25 + gdata(180) * 2 / 3, 0, 1000);
            gdata(180) = 0;
        }
    }
    if (gdata(20) == 13) {
        if (gdata(70) == 1009) {
            txtef(9);
            txt(lang(""s + gdata(84) +
                    u8"分間の間にパーティーを盛り上げよう。目標は"s +
                    qdata(12, gdata(72)) + u8"ポイント。"s,
                u8"You have to warm up the party within "s + gdata(84) +
                    u8" minitues. Your target score is "s +
                    qdata(12, gdata(72)) + u8" points."s));
        }
        if (gdata(70) == 1006) {
            if (qdata(12, gdata(72)) <= 0) {
                qdata(12, gdata(72)) = 15000;
                qdata(6, gdata(72)) = 400;
            }
            txtef(9);
            txt(lang(""s + gdata(84) + u8"分以内に、納入箱に"s +
                    cnvweight(qdata(12, gdata(72))) + u8"の作物を納入しよう。"s,
                u8"To complete the quest, you have to harvest "s +
                    cnvweight(qdata(12, gdata(72))) +
                    u8" worth farm products and put them into the delivery chest within "s +
                    gdata(84) + u8" minutes."s));
        }
        if (gdata(70) == 1008) {
            txtef(9);
            txt(lang(""s + gdata(84) + u8"分以内に、"s +
                    refchara_str(qdata(12, gdata(72)), 2) +
                    u8"を討伐しなければならない。"s,
                u8"You have to slay "s + refchara_str(qdata(12, gdata(72)), 2) +
                    u8" within "s + gdata(84) + u8" minitues."s));
        }
    }
    label_2733();
    return;
}


} // namespace elona
