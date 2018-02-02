#include "elona.hpp"
#include "variables.hpp"


namespace elona
{
void cell_draw()
{
    int syfix_at_m85 = 0;
    int sxfix_at_m85 = 0;
    int scrturn_at_m85 = 0;
    int scrturnbk_at_m85 = 0;
    int scrturnnew_at_m85 = 0;
    int light_at_m85 = 0;
    int flick_at_m85 = 0;
    int dy_at_m85 = 0;
    int ly_at_m85 = 0;
    int y_at_m85 = 0;
    int dx_at_m85 = 0;
    int lx_at_m85 = 0;
    int sx_at_m85 = 0;
    elona_vector1<int> p_at_m85;
    int x_at_m85 = 0;
    int px_at_m85 = 0;
    int py_at_m85 = 0;
    int ground_at_m85 = 0;
    int ani_at_m85 = 0;
    int sel_at_m85 = 0;
    int wall_at_m85 = 0;
    int p2_at_m85 = 0;
    int i_at_m85 = 0;
    elona_vector1<int> flooritem_at_m85;
    int stackh_at_m85 = 0;
    int cnt2_at_m85 = 0;
    int c_at_m85 = 0;
    int col_at_m85 = 0;
    int h_at_m85 = 0;
    int f_at_m85 = 0;
    syfix_at_m85 = (scy != scybk) * syfix;
    sxfix_at_m85 = (scx != scxbk) * sxfix;
    scrturn_at_m85 = scrturn / 5;
    if (scrturn_at_m85 != scrturnbk_at_m85)
    {
        scrturnbk_at_m85 = scrturn_at_m85;
        scrturnnew_at_m85 = 1;
    }
    else
    {
        scrturnnew_at_m85 = 0;
    }
    light_at_m85 = gdata(89);
    randomize(scrturn_at_m85);
    if (gdata_torch == 1)
    {
        if (mdata(6) >= 20 && mdata(6) <= 23)
        {
            light_at_m85 -= 50;
        }
    }
    if (gdata_hour > 17 || gdata_hour < 6)
    {
        flick_at_m85 = rnd(10);
    }
    else
    {
        flick_at_m85 = -15;
    }
    repw(2) = repw(1);
    reph(2) = cdata_y(0) + (syfix < 0);
    reph(3) = reph(2) + 1;
    if (cdata_y(0) == mdata(1) - 2)
    {
        if (syfix < 0)
        {
            --reph(3);
        }
    }
    if (cdata_y(0) == mdata(1) - 1)
    {
        if (syfix > 0)
        {
            --reph(3);
        }
    }
    dy_at_m85 = (reph(1) - scy) * inf_tiles + inf_screeny + syfix_at_m85;
    ly_at_m85 = 1;
    {
        int cnt = reph(1);
        for (int cnt_end = cnt + (reph); cnt < cnt_end; ++cnt)
        {
            y_at_m85 = cnt;
            dx_at_m85 = (repw(1) + repw - 1 - scx) * inf_tiles + inf_screenx
                + sxfix_at_m85;
            lx_at_m85 = 1;
            if (dy_at_m85 <= -inf_tiles || dy_at_m85 >= windowh - inf_verh)
            {
                dy_at_m85 += inf_tiles;
                ++lx_at_m85;
                continue;
            }
            if (y_at_m85 < 0 || y_at_m85 >= mdata(1))
            {
                {
                    int cnt = scx;
                    for (int cnt_end = cnt + (inf_screenw); cnt < cnt_end;
                         ++cnt)
                    {
                        sx_at_m85 = cnt;
                        gmode(0, inf_tiles, inf_tiles);
                        p_at_m85 = tile_fog;
                        pos(dx_at_m85, dy_at_m85);
                        gcopy(
                            2,
                            p_at_m85 % 33 * inf_tiles,
                            p_at_m85 / 33 * inf_tiles);
                        dx_at_m85 -= inf_tiles;
                        ++lx_at_m85;
                    }
                }
                dy_at_m85 += inf_tiles;
                ++ly_at_m85;
                continue;
            }
            color(0, 0, 0);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (repw); cnt < cnt_end; ++cnt)
                {
                    x_at_m85 = repw(1) + repw - 1 - cnt;
                    if (reph(3) == y_at_m85)
                    {
                        if (x_at_m85 == repw(2))
                        {
                            px_at_m85 = (cdata_x(0) - scx) * inf_tiles
                                + inf_screenx - 48;
                            if (scxbk == scx)
                            {
                                px_at_m85 -= sxfix;
                            }
                            py_at_m85 = (cdata_y(0) + 1 - scy) * inf_tiles
                                + inf_screeny;
                            if (scybk == scy)
                            {
                                py_at_m85 -= syfix;
                            }
                            color(0, 0, 0);
                            gmode(5, inf_tiles, inf_tiles, 50 + flick_at_m85);
                            pos(px_at_m85, py_at_m85);
                            gcopy(3, 800, 208, 144, 48);
                        }
                    }
                    if (reph(2) == y_at_m85)
                    {
                        if (x_at_m85 == repw(2))
                        {
                            if (cdata_state(0) == 1)
                            {
                                ground_at_m85 = map(cdata_x(0), cdata_y(0), 0);
                                px_at_m85 = (cdata_x(0) - scx) * inf_tiles
                                    + inf_screenx;
                                if (scxbk == scx)
                                {
                                    px_at_m85 -= sxfix;
                                }
                                py_at_m85 = (cdata_y(0) - scy) * inf_tiles
                                    + inf_screeny;
                                if (scybk == scy)
                                {
                                    py_at_m85 -= syfix;
                                }
                                color(0, 0, 0);
                                gmode(
                                    5, inf_tiles, inf_tiles, 50 + flick_at_m85);
                                pos(px_at_m85 - 48, py_at_m85 - 48);
                                gcopy(3, 800, 112, 144, 96);
                                if (py_at_m85 < windowh - inf_verh - 24)
                                {
                                    if (cdata_continuous_action_id(0) == 7)
                                    {
                                        ani_at_m85 = 0;
                                    }
                                    else
                                    {
                                        ani_at_m85 = cdata_turn(0) % 4 * 32;
                                    }
                                    if (mdata(6) == 1)
                                    {
                                        gmode(6, 32, 16, 85);
                                        color(0, 0, 0);
                                        pos(px_at_m85 + 24, py_at_m85 + 27);
                                        grotate(3, 240, 384, 0, 20, 10);
                                        gmode(2, 32, 48);
                                        pos(px_at_m85 + 24, py_at_m85 + 14);
                                        grotate(
                                            10,
                                            ani_at_m85,
                                            cdata_direction(0) * 48,
                                            0,
                                            16,
                                            24);
                                    }
                                    else if (chipm(0, ground_at_m85) == 3)
                                    {
                                        gmode(4, 32, 20, 146);
                                        color(0, 0, 0);
                                        pos(px_at_m85 + 24, py_at_m85 + 36);
                                        grotate(
                                            10,
                                            ani_at_m85,
                                            cdata_direction(0) * 48 + 28,
                                            0,
                                            24,
                                            16);
                                        gmode(2, 32, 28);
                                        pos(px_at_m85 + 24, py_at_m85 + 16);
                                        grotate(
                                            10,
                                            ani_at_m85,
                                            cdata_direction(0) * 48,
                                            0,
                                            24,
                                            24);
                                    }
                                    else
                                    {
                                        gmode(6, -1, -1, 110);
                                        color(0, 0, 0);
                                        pos(px_at_m85 + 8, py_at_m85 + 20);
                                        gcopy(3, 240, 384, 32, 16);
                                        if (fishanime == 3)
                                        {
                                            if (fishanime(1) % 8 < 4)
                                            {
                                                py_at_m85 -= fishanime(1) % 4
                                                    * (fishanime(1) % 4);
                                            }
                                            else
                                            {
                                                py_at_m85 += fishanime(1) % 4
                                                        * (fishanime(1) % 4)
                                                    - 9;
                                            }
                                        }
                                        gmode(2, 32, 48);
                                        pos(px_at_m85 + 24, py_at_m85 + 8);
                                        grotate(
                                            10,
                                            ani_at_m85,
                                            cdata_direction(0) * 48,
                                            0,
                                            24,
                                            40);
                                    }
                                    gmode(2);
                                    color(0, 0, 0);
                                }
                                if (cdata_furious(0) != 0)
                                {
                                    pos(px_at_m85, py_at_m85 - 24);
                                    gcopy(3, 32, 608, 16, 16);
                                }
                                if (cdata_emotion_icon(0) != 0)
                                {
                                    draw_emo(0, px_at_m85 + 4, py_at_m85 - 32);
                                }
                            }
                        }
                    }
                    if (dx_at_m85 <= -inf_tiles || dx_at_m85 >= windoww)
                    {
                        dx_at_m85 -= inf_tiles;
                        ++lx_at_m85;
                        continue;
                    }
                    if (x_at_m85 < 0 || x_at_m85 >= mdata(0))
                    {
                        gmode(0, inf_tiles, inf_tiles);
                        p_at_m85 = tile_fog;
                        pos(dx_at_m85, dy_at_m85);
                        gcopy(
                            2,
                            p_at_m85 % 33 * inf_tiles,
                            p_at_m85 / 33 * inf_tiles);
                        dx_at_m85 -= inf_tiles;
                        continue;
                    }
                    ground_at_m85 = map(x_at_m85, y_at_m85, 2);
                    sel_at_m85 = 2;
                    gmode(0, inf_tiles, inf_tiles);
                    pos(dx_at_m85, dy_at_m85);
                    wall_at_m85 = 0;
                    if (chipm(2, ground_at_m85) == 2)
                    {
                        if (y_at_m85 < mdata(1) - 1)
                        {
                            if (chipm(2, map(x_at_m85, y_at_m85 + 1, 2)) != 2
                                && map(x_at_m85, y_at_m85 + 1, 2) != tile_fog)
                            {
                                ground_at_m85 += 33;
                            }
                        }
                    }
                    if (chipm(2, ground_at_m85))
                    {
                        wall_at_m85 = 1;
                    }
                    if (chipm(3, ground_at_m85) != 0)
                    {
                        gcopy(
                            sel_at_m85,
                            (ground_at_m85 % 33
                             + (scrturn_at_m85 % (chipm(3, ground_at_m85) + 1)
                                - (scrturn_at_m85
                                       % (chipm(3, ground_at_m85) + 1)
                                   == chipm(3, ground_at_m85))
                                    * 2 * (chipm(3, ground_at_m85) != 0)))
                                * inf_tiles,
                            ground_at_m85 / 33 * inf_tiles);
                    }
                    else
                    {
                        gcopy(
                            sel_at_m85,
                            ground_at_m85 % 33 * inf_tiles,
                            ground_at_m85 / 33 * inf_tiles);
                    }
                    gmode(2, inf_tiles, inf_tiles);
                    if (map(x_at_m85, y_at_m85, 7) != 0)
                    {
                        if (mapsync(x_at_m85, y_at_m85) == msync)
                        {
                            p_at_m85(0) = map(x_at_m85, y_at_m85, 7) % 10;
                            p_at_m85(1) = map(x_at_m85, y_at_m85, 7) / 10;
                            if (p_at_m85(1))
                            {
                                gcopy(5, p_at_m85(1) * inf_tiles + 288, 1152);
                            }
                            if (p_at_m85)
                            {
                                if (p_at_m85 > 6)
                                {
                                    p_at_m85 = 6;
                                }
                                gcopy(5, p_at_m85 * inf_tiles, 1152);
                            }
                        }
                    }
                    if (efmap(1, x_at_m85, y_at_m85) > 0)
                    {
                        if (mapsync(x_at_m85, y_at_m85) == msync)
                        {
                            p_at_m85 = efmap(0, x_at_m85, y_at_m85);
                            if (scrturnnew_at_m85 == 1)
                            {
                                --efmap(1, x_at_m85, y_at_m85);
                            }
                            if (mefsubref(2, p_at_m85) == 1)
                            {
                                gmode(
                                    4,
                                    32,
                                    32,
                                    efmap(1, x_at_m85, y_at_m85) * 12 + 30);
                                pos(dx_at_m85 + 24, dy_at_m85 + 24);
                                grotate(
                                    3,
                                    mefsubref(0, p_at_m85)
                                        + efmap(3, x_at_m85, y_at_m85) * 32,
                                    mefsubref(1, p_at_m85),
                                    0.785 * efmap(2, x_at_m85, y_at_m85),
                                    32,
                                    32);
                            }
                            else
                            {
                                gmode(4, 32, 32, 150);
                                pos(dx_at_m85 + 8, dy_at_m85 + 8);
                                gcopy(
                                    3,
                                    mefsubref(0, p_at_m85)
                                        + efmap(1, x_at_m85, y_at_m85) * 32,
                                    mefsubref(1, p_at_m85));
                            }
                            gmode(2, inf_tiles, inf_tiles);
                        }
                    }
                    if (map(x_at_m85, y_at_m85, 6) != 0)
                    {
                        if (map(x_at_m85, y_at_m85, 2)
                            == map(x_at_m85, y_at_m85, 0))
                        {
                            p_at_m85 = map(x_at_m85, y_at_m85, 6) % 1000;
                            if (p_at_m85 != 999 && p_at_m85 != 0)
                            {
                                pos(dx_at_m85, dy_at_m85 - chipm(5, p_at_m85));
                                gcopy(
                                    2,
                                    p_at_m85 % 33 * inf_tiles,
                                    p_at_m85 / 33 * inf_tiles,
                                    inf_tiles,
                                    48 + chipm(6, p_at_m85));
                            }
                            if (mdata(6) == 1)
                            {
                                p_at_m85 =
                                    map(x_at_m85, y_at_m85, 6) / 100000 % 100
                                    + map(x_at_m85, y_at_m85, 6) / 10000000
                                        * 100;
                                if (adata(16, p_at_m85) == 8)
                                {
                                    if (adata(6, p_at_m85)
                                        == adata(10, p_at_m85))
                                    {
                                        pos(dx_at_m85 + 16, dy_at_m85 - 16);
                                        gcopy(3, 32, 624, 16, 16);
                                    }
                                    else if (adata(6, p_at_m85) != 0)
                                    {
                                        pos(dx_at_m85 + 16, dy_at_m85 - 16);
                                        gcopy(3, 48, 624, 16, 16);
                                    }
                                }
                            }
                        }
                    }
                    if (map(x_at_m85, y_at_m85, 8) != 0)
                    {
                        if (mapsync(x_at_m85, y_at_m85) == msync)
                        {
                            p2_at_m85 = map(x_at_m85, y_at_m85, 8) - 1;
                            p_at_m85(0) = mef(1, p2_at_m85) % 10000;
                            p_at_m85(1) = mef(1, p2_at_m85) / 10000;
                            pos(dx_at_m85, dy_at_m85 - chipi(4, p_at_m85));
                            if (chipi(7, p_at_m85))
                            {
                                p_at_m85 += (scrturn_at_m85 + p2_at_m85)
                                        % (chipi(7, p_at_m85) + 1)
                                    - ((scrturn_at_m85 + p2_at_m85)
                                           % (chipi(7, p_at_m85) + 1)
                                       == chipi(7, p_at_m85))
                                        * 2 * (chipi(7, p_at_m85) != 0);
                            }
                            if (mef(1, p2_at_m85) > 10000)
                            {
                                gsel(1);
                                color(0);
                                boxf(
                                    0,
                                    960,
                                    chipi(2, p_at_m85),
                                    chipi(3, p_at_m85) + 960);
                                if (p_at_m85 == 528)
                                {
                                    gmode(2);
                                    pos(0, 960);
                                    gcopy(1, 0, 768, inf_tiles, inf_tiles);
                                    pos(0, 1008);
                                    gzoom(
                                        22,
                                        20,
                                        5,
                                        chipc(0, p_at_m85(1)) + 8,
                                        chipc(1, p_at_m85(1)) + 4
                                            + (chipc(3, p_at_m85(1))
                                               > inf_tiles)
                                                * 8,
                                        chipc(2, p_at_m85(1)) - 16,
                                        chipc(3, p_at_m85(1)) - 8
                                            - (chipc(3, p_at_m85(1))
                                               > inf_tiles)
                                                * 10,
                                        1);
                                    pos(6, 974);
                                    gcopy(1, 0, 1008, 22, 20);
                                    gsel(selcur);
                                }
                                else if (p_at_m85 == 531)
                                {
                                    pos(8, 1058 - chipc(3, p_at_m85(1)));
                                    gcopy(
                                        5,
                                        chipc(0, p_at_m85(1)) + 8,
                                        chipc(1, p_at_m85(1)) + 2,
                                        chipc(2, p_at_m85(1)) - 16,
                                        chipc(3, p_at_m85(1)) - 8);
                                    gmode(4, -1, -1, 150);
                                    color(0, 0, 0);
                                    pos(0,
                                        960
                                            + (chipc(3, p_at_m85(1))
                                               == inf_tiles)
                                                * 48);
                                    gcopy(
                                        1,
                                        144,
                                        768
                                            + (chipc(3, p_at_m85(1))
                                               > inf_tiles)
                                                * 48,
                                        inf_tiles,
                                        chipc(3, p_at_m85(1))
                                            + (chipc(3, p_at_m85(1))
                                               > inf_tiles)
                                                * 48);
                                    gmode(2);
                                    gsel(selcur);
                                }
                                else
                                {
                                    pos(0, 960);
                                    gcopy(
                                        1,
                                        chipi(0, p_at_m85),
                                        chipi(1, p_at_m85),
                                        chipi(2, p_at_m85),
                                        chipi(3, p_at_m85));
                                    gfini(
                                        chipi(2, p_at_m85), chipi(3, p_at_m85));
                                    gfdec2(
                                        c_col(0, p_at_m85(1)),
                                        c_col(1, p_at_m85(1)),
                                        c_col(2, p_at_m85(1)));
                                    gsel(selcur);
                                }
                                gcopy(1, 0, 960, inf_tiles, inf_tiles);
                            }
                            else
                            {
                                gcopy(
                                    1,
                                    chipi(0, p_at_m85),
                                    chipi(1, p_at_m85),
                                    inf_tiles,
                                    inf_tiles);
                            }
                        }
                    }
                    if (map(x_at_m85, y_at_m85, 5) != 0)
                    {
                        if (map(x_at_m85, y_at_m85, 5) < 0)
                        {
                            if (mode == 6 || mode == 9)
                            {
                                i_at_m85 = 0;
                                p_at_m85 = 363;
                                goto label_0380_internal;
                            }
                            p_at_m85 = -map(x_at_m85, y_at_m85, 5);
                            flooritem_at_m85(0) = p_at_m85 % 1000 + 5080;
                            flooritem_at_m85(1) = p_at_m85 / 1000 % 1000 + 5080;
                            flooritem_at_m85(2) =
                                p_at_m85 / 1000000 % 1000 + 5080;
                            stackh_at_m85 = 0;
                            {
                                int cnt = 0;
                                for (int cnt_end = cnt + (3); cnt < cnt_end;
                                     ++cnt)
                                {
                                    cnt2_at_m85 = 2 - cnt;
                                    if (flooritem_at_m85(cnt2_at_m85) == 6079)
                                    {
                                        continue;
                                    }
                                    p_at_m85 = inv_image(
                                        flooritem_at_m85(cnt2_at_m85));
                                    i_at_m85 = inv_color(
                                        flooritem_at_m85(cnt2_at_m85));
                                    gsel(1);
                                    color(0);
                                    boxf(
                                        0,
                                        960,
                                        chipi(2, p_at_m85),
                                        chipi(3, p_at_m85) + 960);
                                    if (p_at_m85 == 528)
                                    {
                                        gmode(2);
                                        pos(0, 960);
                                        gcopy(1, 0, 768, inf_tiles, inf_tiles);
                                        pos(0, 1008);
                                        gzoom(
                                            22,
                                            20,
                                            5,
                                            chipc(0, i_at_m85) + 8,
                                            chipc(1, i_at_m85) + 4
                                                + (chipc(3, i_at_m85)
                                                   > inf_tiles)
                                                    * 8,
                                            chipc(2, i_at_m85) - 16,
                                            chipc(3, i_at_m85) - 8
                                                - (chipc(3, i_at_m85)
                                                   > inf_tiles)
                                                    * 10,
                                            1);
                                        pos(6, 974);
                                        gcopy(1, 0, 1008, 22, 20);
                                        gsel(selcur);
                                    }
                                    else if (p_at_m85 == 531)
                                    {
                                        pos(8, 1058 - chipc(3, i_at_m85));
                                        gcopy(
                                            5,
                                            chipc(0, i_at_m85) + 8,
                                            chipc(1, i_at_m85) + 2,
                                            chipc(2, i_at_m85) - 16,
                                            chipc(3, i_at_m85) - 8);
                                        gmode(4, -1, -1, 150);
                                        color(0, 0, 0);
                                        pos(0,
                                            960
                                                + (chipc(3, i_at_m85)
                                                   == inf_tiles)
                                                    * 48);
                                        gcopy(
                                            1,
                                            144,
                                            768
                                                + (chipc(3, i_at_m85)
                                                   > inf_tiles)
                                                    * 48,
                                            inf_tiles,
                                            chipc(3, i_at_m85)
                                                + (chipc(3, i_at_m85)
                                                   > inf_tiles)
                                                    * 48);
                                        gmode(2);
                                        gsel(selcur);
                                    }
                                    else
                                    {
                                        pos(0, 960);
                                        gcopy(
                                            1,
                                            chipi(0, p_at_m85),
                                            chipi(1, p_at_m85),
                                            chipi(2, p_at_m85),
                                            chipi(3, p_at_m85));
                                        gfini(
                                            chipi(2, p_at_m85),
                                            chipi(3, p_at_m85));
                                        gfdec2(
                                            c_col(0, i_at_m85),
                                            c_col(1, i_at_m85),
                                            c_col(2, i_at_m85));
                                        gsel(selcur);
                                    }
                                    if (mdata(6) == 1)
                                    {
                                        gmode(
                                            2,
                                            chipi(2, p_at_m85),
                                            chipi(3, p_at_m85));
                                        pos(dx_at_m85 + 24,
                                            dy_at_m85 + 24 - stackh_at_m85 / 2);
                                        grotate(1, 0, 960, 0, 24, 24);
                                    }
                                    else
                                    {
                                        if (cfg_objectshadow)
                                        {
                                            if (chipi(6, p_at_m85))
                                            {
                                                gmode(
                                                    2,
                                                    chipi(2, p_at_m85),
                                                    chipi(3, p_at_m85),
                                                    70);
                                                if (chipi(3, p_at_m85)
                                                    == inf_tiles)
                                                {
                                                    pos(dx_at_m85
                                                            + chipi(2, p_at_m85)
                                                                / 2
                                                            + chipi(6, p_at_m85)
                                                                / 80
                                                            + 2,
                                                        dy_at_m85
                                                            - chipi(4, p_at_m85)
                                                            + 22
                                                            - stackh_at_m85);
                                                    if (chipi(4, p_at_m85) < 24)
                                                    {
                                                        func_2(
                                                            1,
                                                            0,
                                                            960,
                                                            chipi(6, p_at_m85)
                                                                / 2,
                                                            chipi(2, p_at_m85),
                                                            chipi(3, p_at_m85));
                                                    }
                                                }
                                                else
                                                {
                                                    pos(dx_at_m85
                                                            + chipi(2, p_at_m85)
                                                                / 2
                                                            + chipi(6, p_at_m85)
                                                                / 4,
                                                        dy_at_m85
                                                            - chipi(4, p_at_m85)
                                                            + 46
                                                            - stackh_at_m85);
                                                    func_2(
                                                        1,
                                                        0,
                                                        960,
                                                        chipi(6, p_at_m85) * 2,
                                                        chipi(2, p_at_m85),
                                                        chipi(3, p_at_m85));
                                                }
                                                gmode(2);
                                            }
                                        }
                                        pos(dx_at_m85,
                                            dy_at_m85 - chipi(4, p_at_m85)
                                                - stackh_at_m85);
                                        if (chipi(7, p_at_m85) == 0)
                                        {
                                            gcopy(
                                                1,
                                                0,
                                                960,
                                                chipi(2, p_at_m85),
                                                chipi(3, p_at_m85));
                                        }
                                        else
                                        {
                                            gcopy(
                                                1,
                                                chipi(0, p_at_m85)
                                                    + (scrturn_at_m85
                                                           % (chipi(7, p_at_m85)
                                                              + 1)
                                                       - (scrturn_at_m85
                                                              % (chipi(
                                                                     7,
                                                                     p_at_m85)
                                                                 + 1)
                                                          == chipi(7, p_at_m85))
                                                           * 2
                                                           * (chipi(7, p_at_m85)
                                                              != 0))
                                                        * inf_tiles,
                                                chipi(1, p_at_m85),
                                                chipi(2, p_at_m85),
                                                chipi(3, p_at_m85));
                                        }
                                    }
                                    stackh_at_m85 += chipi(5, p_at_m85);
                                    if (p_at_m85 == 531)
                                    {
                                        if (chipc(3, i_at_m85) == 96)
                                        {
                                            stackh_at_m85 += 44;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            i_at_m85 = wpeek(map(x_at_m85, y_at_m85, 5), 2);
                            p_at_m85 = wpeek(map(x_at_m85, y_at_m85, 5), 0);
                        label_0380_internal:
                            gsel(1);
                            color(0);
                            boxf(
                                0,
                                960,
                                chipi(2, p_at_m85),
                                chipi(3, p_at_m85) + 960);
                            if (p_at_m85 == 528)
                            {
                                gmode(2);
                                pos(0, 960);
                                gcopy(1, 0, 768, inf_tiles, inf_tiles);
                                pos(0, 1008);
                                gzoom(
                                    22,
                                    20,
                                    5,
                                    chipc(0, i_at_m85) + 8,
                                    chipc(1, i_at_m85) + 4
                                        + (chipc(3, i_at_m85) > inf_tiles) * 8,
                                    chipc(2, i_at_m85) - 16,
                                    chipc(3, i_at_m85) - 8
                                        - (chipc(3, i_at_m85) > inf_tiles) * 10,
                                    1);
                                pos(6, 974);
                                gcopy(1, 0, 1008, 22, 20);
                                gsel(selcur);
                            }
                            else if (p_at_m85 == 531)
                            {
                                pos(8, 1058 - chipc(3, i_at_m85));
                                gcopy(
                                    5,
                                    chipc(0, i_at_m85) + 8,
                                    chipc(1, i_at_m85) + 2,
                                    chipc(2, i_at_m85) - 16,
                                    chipc(3, i_at_m85) - 8);
                                gmode(4, -1, -1, 150);
                                color(0, 0, 0);
                                pos(0,
                                    960
                                        + (chipc(3, i_at_m85) == inf_tiles)
                                            * 48);
                                gcopy(
                                    1,
                                    144,
                                    768 + (chipc(3, i_at_m85) > inf_tiles) * 48,
                                    inf_tiles,
                                    chipc(3, i_at_m85)
                                        + (chipc(3, i_at_m85) > inf_tiles)
                                            * 48);
                                gmode(2);
                                gsel(selcur);
                            }
                            else
                            {
                                pos(0, 960);
                                gcopy(
                                    1,
                                    chipi(0, p_at_m85),
                                    chipi(1, p_at_m85),
                                    chipi(2, p_at_m85),
                                    chipi(3, p_at_m85));
                                gfini(chipi(2, p_at_m85), chipi(3, p_at_m85));
                                gfdec2(
                                    c_col(0, i_at_m85),
                                    c_col(1, i_at_m85),
                                    c_col(2, i_at_m85));
                                gsel(selcur);
                            }
                            if (mdata(6) == 1)
                            {
                                gmode(
                                    2, chipi(2, p_at_m85), chipi(3, p_at_m85));
                                pos(dx_at_m85 + 24, dy_at_m85 + 24);
                                grotate(1, 0, 960, 0, 24, 24);
                            }
                            else
                            {
                                if (cfg_objectshadow)
                                {
                                    if (chipi(6, p_at_m85))
                                    {
                                        gmode(
                                            2,
                                            chipi(2, p_at_m85),
                                            chipi(3, p_at_m85),
                                            80);
                                        if (chipi(3, p_at_m85) == inf_tiles)
                                        {
                                            pos(dx_at_m85
                                                    + chipi(2, p_at_m85) / 2
                                                    + chipi(6, p_at_m85) / 80
                                                    + 2,
                                                dy_at_m85 - chipi(4, p_at_m85)
                                                    + 22);
                                            if (chipi(4, p_at_m85) < 24)
                                            {
                                                func_2(
                                                    1,
                                                    0,
                                                    960,
                                                    chipi(6, p_at_m85) / 2,
                                                    chipi(2, p_at_m85),
                                                    chipi(3, p_at_m85));
                                            }
                                        }
                                        else
                                        {
                                            pos(dx_at_m85
                                                    + chipi(2, p_at_m85) / 2
                                                    + chipi(6, p_at_m85) / 4,
                                                dy_at_m85 - chipi(4, p_at_m85)
                                                    + 46);
                                            func_2(
                                                1,
                                                0,
                                                960,
                                                chipi(6, p_at_m85) * 2,
                                                chipi(2, p_at_m85),
                                                chipi(3, p_at_m85));
                                        }
                                        gmode(2);
                                    }
                                }
                                pos(dx_at_m85, dy_at_m85 - chipi(4, p_at_m85));
                                if (chipi(7, p_at_m85) == 0)
                                {
                                    gcopy(
                                        1,
                                        0,
                                        960,
                                        chipi(2, p_at_m85),
                                        chipi(3, p_at_m85));
                                }
                                else
                                {
                                    gcopy(
                                        1,
                                        chipi(0, p_at_m85)
                                            + (scrturn_at_m85
                                                   % (chipi(7, p_at_m85) + 1)
                                               - (scrturn_at_m85
                                                      % (chipi(7, p_at_m85) + 1)
                                                  == chipi(7, p_at_m85))
                                                   * 2
                                                   * (chipi(7, p_at_m85) != 0))
                                                * inf_tiles,
                                        chipi(1, p_at_m85),
                                        chipi(2, p_at_m85),
                                        chipi(3, p_at_m85));
                                }
                            }
                        }
                    }
                    if (map(x_at_m85, y_at_m85, 1) != 0)
                    {
                        c_at_m85 = map(x_at_m85, y_at_m85, 1) - 1;
                        if (synccheck(c_at_m85, -1))
                        {
                            if (cbit(6, c_at_m85) == 1)
                            {
                                if (cbit(7, 0) == 0)
                                {
                                    if (cdata_wet(c_at_m85) == 0)
                                    {
                                        c_at_m85 = 0;
                                    }
                                }
                            }
                            if (c_at_m85 != 0)
                            {
                                if (cbit(967, c_at_m85) == 1)
                                {
                                    if (mdata(6) == 1)
                                    {
                                        gmode(6, 32, 16, 85);
                                        color(0, 0, 0);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 27);
                                        grotate(3, 240, 384, 0, 20, 10);
                                        gmode(2, 32, 48);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 14);
                                        grotate(
                                            10 + c_at_m85,
                                            ani_at_m85,
                                            cdata_direction(c_at_m85) * 48,
                                            0,
                                            16,
                                            24);
                                    }
                                    else if (chipm(0, ground_at_m85) == 3)
                                    {
                                        gmode(4, 32, 20, 146);
                                        color(0, 0, 0);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 36);
                                        grotate(
                                            10 + c_at_m85,
                                            ani_at_m85,
                                            cdata_direction(c_at_m85) * 48 + 28,
                                            0,
                                            24,
                                            16);
                                        gmode(2, 32, 28);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 16);
                                        grotate(
                                            10 + c_at_m85,
                                            ani_at_m85,
                                            cdata_direction(c_at_m85) * 48,
                                            0,
                                            24,
                                            24);
                                    }
                                    else
                                    {
                                        gmode(6, -1, -1, 110);
                                        color(0, 0, 0);
                                        pos(dx_at_m85 + 8, dy_at_m85 + 20);
                                        gcopy(3, 240, 384, 32, 16);
                                        gmode(2, 32, 48);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 8);
                                        grotate(
                                            10 + c_at_m85,
                                            ani_at_m85,
                                            cdata_direction(c_at_m85) * 48,
                                            0,
                                            24,
                                            40);
                                    }
                                    gmode(2);
                                    color(0, 0, 0);
                                    if (cdata_furious(c_at_m85) != 0)
                                    {
                                        pos(dx_at_m85 + 12, dy_at_m85 - 28);
                                        gcopy(3, 32, 608, 16, 16);
                                    }
                                    if (cdata_emotion_icon(c_at_m85) != 0)
                                    {
                                        draw_emo(
                                            c_at_m85,
                                            dx_at_m85 + 4,
                                            dy_at_m85 - 32);
                                    }
                                }
                                else
                                {
                                    col_at_m85 = cdata_image(c_at_m85) / 1000;
                                    p_at_m85 = cdata_image(c_at_m85) % 1000;
                                    if (cbit(985, c_at_m85))
                                    {
                                        gmode(2, 48, 96, 80);
                                        pos(dx_at_m85 + 26 - 11,
                                            dy_at_m85 - 32 + 11);
                                        func_2(1, 96, 816, -80, 48, 96);
                                        pos(dx_at_m85, dy_at_m85 - 63);
                                        gcopy(1, 96, 816, 48, 96);
                                        chipc(4, p_at_m85) += 24;
                                    }
                                    gsel(5);
                                    color(0);
                                    boxf(
                                        0,
                                        960,
                                        chipc(2, p_at_m85),
                                        chipc(3, p_at_m85) + 960);
                                    pos(0, 960);
                                    gcopy(
                                        5,
                                        chipc(0, p_at_m85),
                                        chipc(1, p_at_m85),
                                        chipc(2, p_at_m85),
                                        chipc(3, p_at_m85));
                                    gfini(
                                        chipc(2, p_at_m85), chipc(3, p_at_m85));
                                    gfdec2(
                                        c_col(0, col_at_m85),
                                        c_col(1, col_at_m85),
                                        c_col(2, col_at_m85));
                                    gsel(selcur);
                                    if (mdata(6) == 1)
                                    {
                                        gmode(6, 32, 16, 85);
                                        color(0, 0, 0);
                                        pos(dx_at_m85 + 24, dy_at_m85 + 32);
                                        grotate(3, 240, 384, 0, 20, 10);
                                        gmode(
                                            2,
                                            chipc(2, p_at_m85),
                                            chipc(3, p_at_m85));
                                        pos(dx_at_m85 + 24,
                                            dy_at_m85 + 24
                                                - chipc(4, p_at_m85) / 4);
                                        grotate(
                                            5,
                                            0,
                                            960,
                                            0,
                                            24,
                                            chipc(3, p_at_m85) / 2);
                                        if (cdata_emotion_icon(c_at_m85) != 0)
                                        {
                                            draw_emo(
                                                c_at_m85,
                                                dx_at_m85 + 4,
                                                dy_at_m85
                                                    - chipc(4, p_at_m85) / 4
                                                    - 16);
                                        }
                                    }
                                    else
                                    {
                                        if (chipm(0, ground_at_m85) == 3)
                                        {
                                            gmode(4, inf_tiles, inf_tiles, 100);
                                            color(0, 0, 0);
                                            pos(dx_at_m85,
                                                dy_at_m85 + 16
                                                    - chipc(4, p_at_m85)
                                                    - (chipm(0, ground_at_m85)
                                                       == 3)
                                                        * -16);
                                            gcopy(
                                                5,
                                                0,
                                                976,
                                                chipc(2, p_at_m85),
                                                chipc(3, p_at_m85) - 16);
                                            gmode(2, inf_tiles, inf_tiles);
                                            pos(dx_at_m85,
                                                dy_at_m85 - chipc(4, p_at_m85)
                                                    - (chipm(0, ground_at_m85)
                                                       == 3)
                                                        * -16);
                                            gcopy(
                                                5,
                                                0,
                                                960,
                                                chipc(2, p_at_m85),
                                                chipc(3, p_at_m85) - 16);
                                        }
                                        else
                                        {
                                            gmode(6, -1, -1, 110);
                                            color(0, 0, 0);
                                            pos(dx_at_m85 + 8, dy_at_m85 + 20);
                                            gcopy(3, 240, 384, 32, 16);
                                            gmode(2, inf_tiles, inf_tiles);
                                            pos(dx_at_m85,
                                                dy_at_m85 - chipc(4, p_at_m85)
                                                    - (chipm(0, ground_at_m85)
                                                       == 3)
                                                        * -16);
                                            gcopy(
                                                5,
                                                0,
                                                960,
                                                chipc(2, p_at_m85),
                                                chipc(3, p_at_m85));
                                        }
                                        if (cdata_furious(c_at_m85) != 0)
                                        {
                                            pos(dx_at_m85 + 12,
                                                dy_at_m85 - chipc(4, p_at_m85)
                                                    - 12);
                                            gcopy(3, 32, 608, 16, 16);
                                        }
                                        if (cdata_emotion_icon(c_at_m85) != 0)
                                        {
                                            draw_emo(
                                                c_at_m85,
                                                dx_at_m85 + 4,
                                                dy_at_m85 - chipc(4, p_at_m85)
                                                    - 16);
                                        }
                                    }
                                    if (cbit(985, c_at_m85))
                                    {
                                        pos(dx_at_m85, dy_at_m85 - 26);
                                        gcopy(1, 96, 768, 48, 48);
                                        chipc(4, p_at_m85) -= 24;
                                    }
                                }
                                if (cbit(966, c_at_m85) == 1
                                    || gdata(94) == c_at_m85)
                                {
                                    h_at_m85 = cdata_hp(c_at_m85) * 30
                                        / cdata_max_hp(c_at_m85);
                                    if (h_at_m85 > 30)
                                    {
                                        h_at_m85 = 30;
                                    }
                                    if (c_at_m85 < 16)
                                    {
                                        if (mdata(6) != 1)
                                        {
                                            pos(dx_at_m85 + 9, dy_at_m85 + 32);
                                            gcopy(
                                                3,
                                                480 - h_at_m85,
                                                517,
                                                h_at_m85,
                                                3);
                                        }
                                    }
                                    else
                                    {
                                        pos(dx_at_m85 + 9, dy_at_m85 + 32);
                                        gcopy(
                                            3,
                                            480 - h_at_m85,
                                            513,
                                            h_at_m85,
                                            3);
                                    }
                                }
                            }
                        }
                    }
                    if (map(x_at_m85, y_at_m85, 9) != 0)
                    {
                        p_at_m85 = map(x_at_m85, y_at_m85, 9);
                        if (gdata_hour > 17 || gdata_hour < 6
                            || lightdata(6, p_at_m85))
                        {
                            if (mapsync(x_at_m85, y_at_m85) == msync)
                            {
                                light_at_m85 -= (6
                                                 - std::clamp(
                                                       dist(
                                                           cdata_x(0),
                                                           cdata_y(0),
                                                           x_at_m85,
                                                           y_at_m85),
                                                       0,
                                                       6))
                                    * lightdata(4, p_at_m85);
                                pos(dx_at_m85,
                                    dy_at_m85 - lightdata(3, p_at_m85));
                                gmode(
                                    5,
                                    inf_tiles,
                                    inf_tiles,
                                    lightdata(2, p_at_m85)
                                        + rnd((lightdata(5, p_at_m85) + 1)));
                                gcopy(
                                    3,
                                    192 + lightdata(0, p_at_m85) * 48
                                        + rnd((lightdata(1, p_at_m85) + 1))
                                            * inf_tiles,
                                    704);
                            }
                        }
                    }
                    if (wall_at_m85 == 0)
                    {
                        if (ground_at_m85 != tile_fog)
                        {
                            if (y_at_m85 > 0)
                            {
                                if (dy_at_m85 > 48)
                                {
                                    ground_at_m85 =
                                        map(x_at_m85, y_at_m85 - 1, 0);
                                    if (chipm(2, ground_at_m85))
                                    {
                                        pos(dx_at_m85
                                                + (dx_at_m85 < 0) * -dx_at_m85,
                                            dy_at_m85);
                                        gfini(
                                            inf_tiles
                                                - (dx_at_m85
                                                   > windoww - inf_tiles)
                                                    * (dx_at_m85 + inf_tiles
                                                       - windoww)
                                                + (dx_at_m85 < 0) * dx_at_m85,
                                            24);
                                        gfdec2(16, 16, 16);
                                        pos(dx_at_m85
                                                + (dx_at_m85 < 0) * -dx_at_m85,
                                            dy_at_m85 + 24);
                                        gfini(
                                            inf_tiles
                                                - (dx_at_m85
                                                   > windoww - inf_tiles)
                                                    * (dx_at_m85 + inf_tiles
                                                       - windoww)
                                                + (dx_at_m85 < 0) * dx_at_m85,
                                            12);
                                        gfdec2(12, 12, 12);
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        gmode(0);
                        if (y_at_m85 > 0)
                        {
                            p_at_m85 = map(x_at_m85, y_at_m85 - 1, 2);
                            if (chipm(2, p_at_m85) != 2 && p_at_m85 != tile_fog)
                            {
                                if (dy_at_m85 > 20)
                                {
                                    pos(dx_at_m85, dy_at_m85 - 12);
                                    gcopy(
                                        sel_at_m85,
                                        ground_at_m85 % 33 * inf_tiles,
                                        ground_at_m85 / 33 * inf_tiles,
                                        inf_tiles
                                            - (dx_at_m85 > windoww - inf_tiles)
                                                * (dx_at_m85 + inf_tiles
                                                   - windoww),
                                        12);
                                    pos(dx_at_m85
                                            + (dx_at_m85 < 0) * -dx_at_m85,
                                        dy_at_m85 - 20);
                                    gfini(
                                        inf_tiles
                                            - (dx_at_m85 > windoww - inf_tiles)
                                                * (dx_at_m85 + inf_tiles
                                                   - windoww)
                                            + (dx_at_m85 < 0) * dx_at_m85,
                                        8);
                                    gfdec2(25, 25, 25);
                                }
                            }
                        }
                    }
                    dx_at_m85 -= inf_tiles;
                    ++lx_at_m85;
                }
            }
            dy_at_m85 += inf_tiles;
            ++ly_at_m85;
        }
    }
    if (light_at_m85 < 25)
    {
        light_at_m85 = 25;
    }
    if (mdata(6) == 1)
    {
        {
            int cnt = 0;
            for (int cnt_end = cnt + (12); cnt < cnt_end; ++cnt)
            {
                gmode(5, -1, -1, 7 + cnt * 2);
                x_at_m85 = (cloud(0, cnt) - cdata_x(0) * 48 + sxfix) * 100
                        / (40 + cnt * 5)
                    + scrturn * 100 / (50 + cnt * 20);
                y_at_m85 = (cloud(1, cnt) - cdata_y(0) * 48 + syfix) * 100
                    / (40 + cnt * 5);
                x_at_m85 = x_at_m85 % (windoww + cloud(4, cnt)) - cloud(4, cnt);
                y_at_m85 =
                    y_at_m85 % (inf_very + cloud(5, cnt)) - cloud(5, cnt);
                h_at_m85 = cloud(5, cnt);
                if (y_at_m85 + cloud(5, cnt) >= inf_very)
                {
                    h_at_m85 = inf_very - y_at_m85;
                }
                if (y_at_m85 < inf_very)
                {
                    pos(x_at_m85, y_at_m85);
                    gcopy(
                        2,
                        cloud(2, cnt),
                        cloud(3, cnt),
                        cloud(4, cnt),
                        h_at_m85);
                }
            }
        }
    }
    if (cfg_shadow != 0)
    {
        color(0, 0, 0);
        gmode(6, inf_tiles, inf_tiles, light_at_m85);
        y_at_m85 = 2;
        dy_at_m85 = inf_screeny;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (inf_screenh); cnt < cnt_end; ++cnt)
            {
                x_at_m85 = 2;
                dx_at_m85 = inf_screenx;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (inf_screenw); cnt < cnt_end;
                         ++cnt)
                    {
                        if (slight(x_at_m85, y_at_m85) >= 1000)
                        {
                            pos(dx_at_m85, dy_at_m85);
                            gcopy(3, 144, 752);
                        }
                        ++x_at_m85;
                        dx_at_m85 += inf_tiles;
                    }
                }
                ++y_at_m85;
                dy_at_m85 += inf_tiles;
            }
        }
        gmode(2);
        randomize();
        return;
    }
    gmode(6, inf_tiles, inf_tiles, light_at_m85);
    if (scrollanime == 0)
    {
        y_at_m85 = 2;
        dy_at_m85 = inf_screeny + syfix_at_m85 * (scrollp > 3);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (inf_screenh); cnt < cnt_end; ++cnt)
            {
                x_at_m85 = 2;
                dx_at_m85 = inf_screenx + sxfix_at_m85 * (scrollp > 3);
                cnt2_at_m85 = cnt;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (inf_screenw); cnt < cnt_end;
                         ++cnt)
                    {
                        p_at_m85 = slight(x_at_m85, y_at_m85);
                        if (p_at_m85 > 0)
                        {
                            if (p_at_m85 < 300)
                            {
                                {
                                    int cnt = 0;
                                    for (int cnt_end = cnt
                                             + (1 + (deco(2, p_at_m85) != 0));
                                         cnt < cnt_end;
                                         ++cnt)
                                    {
                                        if (deco(0, p_at_m85) < 0 || cnt)
                                        {
                                            if (cnt == 1)
                                            {
                                                deco2 = deco(2, p_at_m85);
                                            }
                                            else
                                            {
                                                deco2 = deco(1, p_at_m85);
                                            }
                                            {
                                                int cnt = 0;
                                                for (int cnt_end = cnt + (1);
                                                     cnt < cnt_end;
                                                     ++cnt)
                                                {
                                                    if (deco2 == 1)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 2)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 3)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 4)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 5)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 6)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 7)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 8)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 9)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 10)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 20)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 704, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            704,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                    if (deco2 == 21)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 48, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 48, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 30)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 0, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 31)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 96, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 96, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 32)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 656, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            656,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                    if (deco2 == 33)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 752, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            752,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            pos(dx_at_m85, dy_at_m85);
                                            gcopy(
                                                3,
                                                0
                                                    + deco(0, p_at_m85)
                                                        * inf_tiles,
                                                656
                                                    + deco(1, p_at_m85)
                                                        * inf_tiles);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                p2_at_m85 = (p_at_m85 - 1000) % 16;
                                i_at_m85 = 0;
                                if (p2_at_m85 == 15)
                                {
                                    p2_at_m85 = (p_at_m85 - 1000) % 256;
                                    if (p2_at_m85 == 127)
                                    {
                                        i_at_m85 = 13;
                                    }
                                    if (p2_at_m85 == 223)
                                    {
                                        i_at_m85 = 14;
                                    }
                                    if (p2_at_m85 == 191)
                                    {
                                        i_at_m85 = 15;
                                    }
                                    if (p2_at_m85 == 239)
                                    {
                                        i_at_m85 = 16;
                                    }
                                    if (p2_at_m85 == 207 || p2_at_m85 == 63)
                                    {
                                        i_at_m85 = 17;
                                    }
                                }
                                else
                                {
                                    i_at_m85 = shadowmap(p2_at_m85);
                                }
                                pos(dx_at_m85, dy_at_m85);
                                gcopy(3, 144 + i_at_m85 * inf_tiles, 752);
                            }
                        }
                        ++x_at_m85;
                        dx_at_m85 += inf_tiles;
                    }
                }
                ++y_at_m85;
                dy_at_m85 += inf_tiles;
            }
        }
    }
    else
    {
        f_at_m85 = 0;
        if (scrollp > 3 || mdata(6) == 20)
        {
            f_at_m85 = 1;
        }
        y_at_m85 = 1;
        dy_at_m85 = inf_screeny + syfix_at_m85 * f_at_m85 - 48;
        {
            int cnt = 0;
            for (int cnt_end = cnt + (inf_screenh + 2); cnt < cnt_end; ++cnt)
            {
                if (dy_at_m85 <= -inf_tiles || dy_at_m85 >= windowh - inf_verh)
                {
                    dy_at_m85 += inf_tiles;
                    ++y_at_m85;
                    continue;
                }
                x_at_m85 = 1;
                dx_at_m85 = inf_screenx + sxfix_at_m85 * f_at_m85 - 48;
                {
                    int cnt = 0;
                    for (int cnt_end = cnt + (inf_screenw + 2); cnt < cnt_end;
                         ++cnt)
                    {
                        p_at_m85 = slight(x_at_m85, y_at_m85);
                        if (p_at_m85 > 0)
                        {
                            if (p_at_m85 < 300)
                            {
                                {
                                    int cnt = 0;
                                    for (int cnt_end = cnt
                                             + (1 + (deco(2, p_at_m85) != 0));
                                         cnt < cnt_end;
                                         ++cnt)
                                    {
                                        if (deco(0, p_at_m85) < 0 || cnt)
                                        {
                                            if (cnt == 1)
                                            {
                                                deco2 = deco(2, p_at_m85);
                                            }
                                            else
                                            {
                                                deco2 = deco(1, p_at_m85);
                                            }
                                            {
                                                int cnt = 0;
                                                for (int cnt_end = cnt + (1);
                                                     cnt < cnt_end;
                                                     ++cnt)
                                                {
                                                    if (deco2 == 1)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 2)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 3)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 4)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 5)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 6)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 7)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 8)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 9)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            168,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 10)
                                                    {
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            680,
                                                            24,
                                                            24);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3,
                                                            144,
                                                            656,
                                                            24,
                                                            24);
                                                        break;
                                                    }
                                                    if (deco2 == 20)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 704, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            704,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                    if (deco2 == 21)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 48, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 48, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 30)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 0, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 31)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 96, 656, 48, 24);
                                                        pos(dx_at_m85,
                                                            dy_at_m85 + 24);
                                                        gcopy(
                                                            3, 96, 776, 48, 24);
                                                        break;
                                                    }
                                                    if (deco2 == 32)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 656, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            656,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                    if (deco2 == 33)
                                                    {
                                                        pos(dx_at_m85,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3, 0, 752, 24, 48);
                                                        pos(dx_at_m85 + 24,
                                                            dy_at_m85);
                                                        gcopy(
                                                            3,
                                                            120,
                                                            752,
                                                            24,
                                                            48);
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            pos(dx_at_m85, dy_at_m85);
                                            gcopy(
                                                3,
                                                0
                                                    + deco(0, p_at_m85)
                                                        * inf_tiles,
                                                656
                                                    + deco(1, p_at_m85)
                                                        * inf_tiles);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                p2_at_m85 = (p_at_m85 - 1000) % 16;
                                i_at_m85 = 0;
                                if (p2_at_m85 == 15)
                                {
                                    p2_at_m85 = (p_at_m85 - 1000) % 256;
                                    if (p2_at_m85 == 127)
                                    {
                                        i_at_m85 = 13;
                                    }
                                    if (p2_at_m85 == 223)
                                    {
                                        i_at_m85 = 14;
                                    }
                                    if (p2_at_m85 == 191)
                                    {
                                        i_at_m85 = 15;
                                    }
                                    if (p2_at_m85 == 239)
                                    {
                                        i_at_m85 = 16;
                                    }
                                    if (p2_at_m85 == 207 || p2_at_m85 == 63)
                                    {
                                        i_at_m85 = 17;
                                    }
                                }
                                else
                                {
                                    i_at_m85 = shadowmap(p2_at_m85);
                                }
                                pos(dx_at_m85, dy_at_m85);
                                gcopy(
                                    3, 144 + i_at_m85 * inf_tiles, 752, 48, 48);
                            }
                        }
                        ++x_at_m85;
                        dx_at_m85 += inf_tiles;
                    }
                }
                ++y_at_m85;
                dy_at_m85 += inf_tiles;
            }
        }
    }
    gmode(2);
    randomize();
    return;
}



} // namespace elona
