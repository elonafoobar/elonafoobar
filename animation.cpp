#include "animation.hpp"
#include "ability.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "map.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{


elona_vector1<int> ax;
elona_vector1<int> ay;
elona_vector1<int> ax2;
elona_vector1<int> ay2;



void play_animation_8(int anicol)
{
    if (is_in_fov(cc) == 0)
        return;

    prepare_item_image(10, anicol);
    int anidx = (cdata[cc].position.x - scx) * inf_tiles + inf_screenx;
    int anidy = (cdata[cc].position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(
        0,
        anidx - inf_tiles / 2,
        anidy - inf_tiles / 2,
        inf_tiles * 2,
        inf_tiles * 2);
    gmode(2);
    gsel(0);
    snd(66);

    for (int i = 0; i < 12; ++i)
    {
        redraw(0);
        pos(anidx - inf_tiles / 2, anidy - inf_tiles / 2);
        gcopy(4, 0, 0, inf_tiles * 2, inf_tiles * 2);
        pos(anidx + inf_tiles / 2, anidy + 16);
        grotate(1, 0, 960, 5 * i, i + 40, i + 40);
        redraw(1);
        await(cfg_animewait);
    }
}


void play_animation_6_5_7_11(int animeid, int anicol)
{
    if (is_in_fov(tc) == 0)
        return;

    if (animeid == 6)
    {
        prepare_item_image(8, anicol);
        snd(38);
    }
    if (animeid == 5 || animeid == 11)
    {
        prepare_item_image(7, anicol);
        snd(33);
    }
    if (animeid == 7)
    {
        prepare_item_image(9, anicol);
    }
    ax = (cdata[tc].position.x - scx) * inf_tiles + inf_screenx;
    ay = (cdata[tc].position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(
        0,
        ax - inf_tiles / 2,
        ay - inf_tiles / 2,
        inf_tiles * 2,
        inf_tiles * 2);
    gmode(2);
    gsel(0);

    for (int i = 0; i < 15; ++i)
    {
        ax2(i) = rnd(inf_tiles);
        ay2(i) = rnd(inf_tiles) - 8;
        ap(i) = (rnd(4) + 1) * -1;
        if (animeid == 6)
        {
            ap(i) *= -1;
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        if (animeid == 11)
        {
            await(5);
        }
        else
        {
            await(cfg_animewait);
        }
        int acnt2 = i * 2;
        redraw(0);
        pos(ax - inf_tiles / 2, ay - inf_tiles / 2);
        gcopy(4, 0, 0, inf_tiles * 2, inf_tiles * 2);
        for (int j = 0; j < 15; ++j)
        {
            pos(ax + ax2(j), ay + ay2(j) + acnt2 / ap(j));
            grotate(
                1,
                0,
                960,
                acnt2 * ap(j),
                inf_tiles - acnt2 * 2,
                inf_tiles - acnt2 * 2);
        }
        redraw(1);
    }
}


void play_animation_3(int anicol, int anisound)
{
    prepare_item_image(5, anicol);
    snd(35);
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime7.bmp"));
    pos(0, 0);
    gfini(480, 48);
    gfdec2(c_col(0, anicol), c_col(1, anicol), c_col(2, anicol));
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (6); cnt < cnt_end; ++cnt)
        {
            cnt2 = cnt;
            redraw(0);
            pos(0, 0);
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (maxbreath); cnt < cnt_end; ++cnt)
                {
                    int anidx = breathlist(0, cnt);
                    int anidy = breathlist(1, cnt);
                    if (fov_los(
                            cdata[cc].position.x,
                            cdata[cc].position.y,
                            anidx,
                            anidy)
                        == 0)
                    {
                        continue;
                    }
                    if ((anidx - scx) * inf_tiles + inf_screenx + inf_tiles / 2
                        < windoww)
                    {
                        if ((anidy - scy) * inf_tiles + inf_screeny + 16
                            < inf_screenh * inf_tiles + inf_screeny
                                - inf_tiles / 2)
                        {
                            pos((anidx - scx) * inf_tiles + inf_screenx
                                    + inf_tiles / 2,
                                (anidy - scy) * inf_tiles + inf_screeny + 16);
                            gmode(2, inf_tiles, inf_tiles);
                            grotate(
                                7,
                                cnt2 * 48,
                                0,
                                std::atan2(
                                    tlocx - cdata[cc].position.x,
                                    cdata[cc].position.y - tlocy),
                                inf_tiles,
                                inf_tiles);
                        }
                    }
                }
            }
            await(cfg_animewait);
            redraw(1);
        }
    }
    if (anisound)
    {
        snd(anisound, 0, 1);
    }
}


void play_animation_17_2(int animeid, int anicol, int anisound)
{
    snd(34);
    gsel(7);
    pos(0, 0);
    picload(fs::u8path(u8"./graphic/anime5.bmp"));
    pos(0, 96);
    gfini(480, 48);
    gfdec2(c_col(0, anicol), c_col(1, anicol), c_col(2, anicol));
    int anidx = (anix - scx) * inf_tiles + inf_screenx + 24;
    int anidy = (aniy - scy) * inf_tiles + inf_screeny + 24;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gmode(2);
    gsel(0);
    color(0, 0, 0);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
        {
            int anip = cnt;
            int anip1 = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (aniref * 2 + 1); cnt < cnt_end; ++cnt)
                {
                    anidy = aniy - aniref + cnt;
                    sy = anidy - scy;
                    if (sy < 0 || sy >= inf_screenh)
                    {
                        continue;
                    }
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (aniref * 2 + 1);
                             cnt < cnt_end;
                             ++cnt)
                        {
                            anidx = anix - aniref + cnt;
                            sx = anidx - scx;
                            if (sx < 0 || sx >= inf_screenw)
                            {
                                continue;
                            }
                            anip1 = dist(anix, aniy, anidx, anidy);
                            if (anip1 > aniref)
                            {
                                continue;
                            }
                            anip1 = 48 - (anip - 4) * (anip - 4) * 2;
                            if (animeid == 2)
                            {
                                if (fov_los(anix, aniy, anidx, anidy) == 0)
                                {
                                    continue;
                                }
                            }
                            if (sx * inf_tiles + inf_screenx < windoww)
                            {
                                if (sy * inf_tiles + inf_screeny
                                    < inf_screenh * inf_tiles + inf_screeny
                                        - inf_tiles / 2)
                                {
                                    pos(sx * inf_tiles + inf_screenx,
                                        sy * inf_tiles + inf_screeny);
                                    gmode(2, 48, 48);
                                    gcopy(7, anip * 48, 96, 48, 48);
                                }
                            }
                        }
                    }
                }
            }
            anidx = (anix - scx) * inf_tiles + inf_screenx + 24;
            anidy = (aniy - scy) * inf_tiles + inf_screeny + 24;
            if (anidx < windoww)
            {
                if (anidy
                    < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
                {
                    pos(anidx, anidy);
                    gmode(4, 96, 96, 250 - cnt * cnt * 2);
                    grotate(7, cnt * 96, 0, 0, 96, 96);
                }
            }
            redraw(1);
            redraw(0);
            gmode(0);
            pos(0, 0);
            gcopy(4, 0, 0, windoww, windowh);
            await(cfg_animewait);
        }
    }
    if (anisound)
    {
        snd(anisound, 0, 1);
    }
}



void play_animation_0(int anicol, int anisound)
{
    prepare_item_image(3, anicol);
    snd(37);
    int anidx = cdata[cc].position.x;
    int anidy = cdata[cc].position.y;
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime6.bmp"));
    pos(0, 0);
    gfini(480, 48);
    gfdec2(c_col(0, anicol), c_col(1, anicol), c_col(2, anicol));
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    ap(20) = -1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (20); cnt < cnt_end; ++cnt)
        {
            if (ap(20) == -1)
            {
                int stat = route_info(anidx, anidy, cnt);
                if (stat == -1)
                {
                    ap(cnt) = -1;
                    continue;
                }
                else if (stat == 0)
                {
                    ap(cnt) = -2;
                    ap(20) = 4;
                    continue;
                }
                if (dist(
                        anidx,
                        anidy,
                        cdata[cc].position.x,
                        cdata[cc].position.y)
                    > the_ability_db[efid].sdataref3 % 1000 + 1)
                {
                    ap(cnt) = -2;
                    ap(20) = 4;
                    continue;
                }
                ax(cnt) =
                    (anidx - scx) * inf_tiles + inf_screenx + inf_tiles / 2;
                ay(cnt) = (anidy - scy) * inf_tiles + inf_screeny + 8;
                ap(cnt) = 0;
            }
            else
            {
                --ap(20);
                if (ap(20) == 0)
                {
                    break;
                }
            }
            redraw(0);
            pos(0, 0);
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            cnt2 = cnt;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (cnt2 + 1); cnt < cnt_end; ++cnt)
                {
                    if (ap(cnt) == -1)
                    {
                        continue;
                    }
                    if (ap(cnt) == -2)
                    {
                        break;
                    }
                    if (ap(cnt) < 5)
                    {
                        if (ax(cnt) < windoww)
                        {
                            if (ay(cnt) < inf_screenh * inf_tiles + inf_screeny
                                    - inf_tiles / 2)
                            {
                                pos(ax(cnt), ay(cnt));
                                gmode(2, inf_tiles, inf_tiles);
                                grotate(
                                    7,
                                    ap(cnt) * 48,
                                    0,
                                    std::atan2(
                                        tlocx - cdata[cc].position.x,
                                        cdata[cc].position.y - tlocy),
                                    48,
                                    48);
                            }
                        }
                    }
                    ++ap(cnt);
                }
            }
            await(cfg_animewait + 15);
            redraw(1);
        }
    }
    if (anisound)
    {
        snd(anisound, 0, 1);
    }
}



void play_animation_15()
{
    if (is_in_fov(cc) == 0)
    {
        return;
    }
    prepare_item_image(aniref, aniref(1));
    ax = (cdata[cc].position.x - scx) * inf_tiles;
    ay = (cdata[cc].position.y - scy) * inf_tiles;
    ap = dist(cdata[cc].position.x, cdata[cc].position.y, anix, aniy) / 2 + 1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (ap); cnt < cnt_end; ++cnt)
        {
            ax -= (cdata[cc].position.x - anix) * inf_tiles / ap;
            ay -= (cdata[cc].position.y - aniy) * inf_tiles / ap;
            gsel(4);
            gmode(0);
            pos(0, 0);
            gcopy(0, ax, ay - inf_tiles / 2, inf_tiles, inf_tiles);
            gmode(2);
            gsel(0);
            gmode(2, inf_tiles, inf_tiles);
            if (ax + inf_tiles / 2 < windoww)
            {
                if (ay < inf_screenh * inf_tiles + inf_screeny - inf_tiles / 2)
                {
                    pos(ax + inf_tiles / 2, ay);
                    grotate(
                        1,
                        0,
                        960,
                        std::atan2(
                            anix - cdata[cc].position.x,
                            cdata[cc].position.y - aniy),
                        inf_tiles,
                        inf_tiles);
                }
            }
            redraw(1);
            redraw(0);
            gmode(0);
            pos(ax, ay - inf_tiles / 2);
            gcopy(4, 0, 0, inf_tiles, inf_tiles);
            gmode(2);
            await(cfg_animewait);
        }
    }
}



void play_animation_ranged_attack(int animeid, int anicol, int anisound)
{
    if (is_in_fov(cc) == 0)
    {
        return;
    }
    prepare_item_image(6, anicol);
    if (animeid == 18)
    {
        prepare_item_image(23, 0);
        snd(29);
    }
    if (animeid == 108)
    {
        prepare_item_image(1, anicol);
        snd(29);
    }
    if (animeid == 109)
    {
        prepare_item_image(2, anicol);
        snd(29);
    }
    if (animeid == 110)
    {
        ap = the_item_db[inv[aniref].id]->subcategory;
        if (ap == 24021)
        {
            prepare_item_image(13, anicol);
            snd(42);
        }
        if (ap == 24020)
        {
            prepare_item_image(2, anicol);
            snd(30);
        }
    }
    if (animeid == 111)
    {
        prepare_item_image(inv[aniref].image % 1000, inv[aniref].image / 1000);
    }
    if (animeid == 1)
    {
        snd(36);
    }
    ax = (cdata[cc].position.x - scx) * inf_tiles;
    ay = (cdata[cc].position.y - scy) * inf_tiles - 12;
    ap = dist(
             cdata[cc].position.x,
             cdata[cc].position.y,
             cdata[tc].position.x,
             cdata[tc].position.y)
            / 2
        + 1;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (ap); cnt < cnt_end; ++cnt)
        {
            ax -=
                (cdata[cc].position.x - cdata[tc].position.x) * inf_tiles / ap;
            ay -=
                (cdata[cc].position.y - cdata[tc].position.y) * inf_tiles / ap;
            gsel(4);
            gmode(0);
            pos(0, 0);
            gcopy(0, ax, ay - inf_tiles / 2, inf_tiles, inf_tiles);
            gmode(2);
            gsel(0);
            gmode(2, inf_tiles, inf_tiles);
            pos(ax + inf_tiles / 2, ay);
            grotate(
                1,
                0,
                960,
                std::atan2(
                    cdata[tc].position.x - cdata[cc].position.x,
                    cdata[cc].position.y - cdata[tc].position.y),
                inf_tiles,
                inf_tiles);
            redraw(1);
            redraw(0);
            gmode(0);
            pos(ax, ay - inf_tiles / 2);
            gcopy(4, 0, 0, inf_tiles, inf_tiles);
            gmode(2);
            await(cfg_animewait);
        }
    }
    if (anisound)
    {
        snd(anisound, 0, 1);
    }
}



void play_animation_9()
{
    snd(2);
    prepare_item_image(17, 0);
    int anidx = (cdata[tc].position.x - scx) * inf_tiles + inf_screenx;
    int anidy = (cdata[tc].position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, anidx - 16, anidy - 16, 64, 64);
    gmode(2);
    gsel(0);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (4); cnt < cnt_end; ++cnt)
        {
            redraw(0);
            pos(anidx - 16, anidy - 16);
            gcopy(4, 0, 0, 64, 64);
            pos(anidx + 16, anidy + 16);
            grotate(1, 0, 960, 0.5 * cnt - 0.8, cnt * 8 + 18, cnt * 8 + 18);
            redraw(1);
            await(cfg_animewait);
        }
    }
}



void play_animation_12()
{
    int anix1;
    switch (attackskill)
    {
    case 100:
    case 101:
    case 102:
    case 104:
    case 107: ap = 1; break;
    case 108:
    case 109:
    case 110:
    case 111: ap = 2; break;
    default: ap = 0; break;
    }
    aniref = aniref / 4 + 1;
    if (aniref > 20)
    {
        aniref = 20;
    }
    if (cbit(983, tc))
    {
        anix1 = 1104;
    }
    else
    {
        anix1 = 720;
    }
    if (ap == 0)
    {
        prepare_item_image(17, 0);
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (aniref); cnt < cnt_end; ++cnt)
        {
            sx(cnt) = rnd(24) - 12;
            sy(cnt) = rnd(8);
        }
    }
    int anidx = (cdata[tc].position.x - scx) * inf_tiles + inf_screenx;
    int anidy = (cdata[tc].position.y - scy) * inf_tiles + inf_screeny;
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, anidx - 24, anidy - 48, 96, 144);
    if (critical)
    {
        gsel(7);
        picload(fs::u8path(u8"./graphic/anime28.bmp"));
    }
    gmode(2);
    gsel(0);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (4 + (critical != 0)); cnt < cnt_end; ++cnt)
        {
            redraw(0);
            gmode(2);
            cnt2 = cnt * 2;
            gmode(2, inf_tiles, inf_tiles);
            if (critical)
            {
                pos(anidx - 24, anidy - 32);
                gcopy(7, cnt * 96, 0, 96, 96);
            }
            {
                int cnt = 0;
                for (int cnt_end = cnt + (aniref); cnt < cnt_end; ++cnt)
                {
                    pos(anidx + 24 + sx(cnt)
                            + (sx(cnt) < 4) * ((1 + (cnt % 2 == 0)) * -1) * cnt2
                            + (sx(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2,
                        anidy + sy(cnt) + cnt2 * cnt2 / 3);
                    grotate(1, anix1, 0, 0.4 * cnt, 6, 6);
                }
            }
            if (ap == 0)
            {
                pos(anidx + sx + 24, anidy + sy + 10);
                grotate(
                    1,
                    0,
                    960,
                    0.5 * cnt - 0.8,
                    cnt * 10 + aniref,
                    cnt * 10 + aniref);
            }
            if (ap == 1)
            {
                pos(anidx, anidy);
                gcopy(3, 1008 + cnt * 48, 432, 48, 48);
            }
            if (ap == 2)
            {
                pos(anidx, anidy);
                gcopy(3, 816 + cnt * 48, 432, 48, 48);
            }
            redraw(1);
            redraw(0);
            gmode(0);
            pos(anidx - 24, anidy - 48);
            gcopy(4, 0, 0, 96, 144);
            gmode(2);
            await(cfg_animewait);
        }
    }
}


void play_animation_20()
{
    snd(107);
    if (is_in_fov(anic) == 0)
    {
        return;
    }
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime13.bmp"));
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    int anidx = (cdata[anic].position.x - scx) * inf_tiles + inf_screenx - 24;
    int anidy = (cdata[anic].position.y - scy) * inf_tiles + inf_screeny - 60;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (10); cnt < cnt_end; ++cnt)
        {
            redraw(0);
            pos(0, 0);
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            cnt2 = cnt;
            gmode(2);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (anidy / 96 + 2); cnt < cnt_end; ++cnt)
                {
                    pos(anidx, anidy - cnt * 96);
                    gcopy(7, cnt2 / 2 * 96, (cnt == 0) * 96, 96, 96);
                }
            }
            await(cfg_animewait + 25);
            redraw(1);
        }
    }
}


void play_animation_19()
{
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime12.bmp"));
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    am = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (245); cnt < cnt_end; ++cnt)
        {
            if (cdata[cnt].state != 1)
            {
                continue;
            }
            if (animode == 0)
            {
                if (cnt == cc)
                {
                    continue;
                }
            }
            if (animode >= 100)
            {
                if (cnt != animode - 100)
                {
                    continue;
                }
            }
            ax(am) =
                (cdata[cnt].position.x - scx) * inf_tiles + inf_screenx - 24;
            if (am != 0)
            {
                ax(am) += 4 - rnd(8);
            }
            ay(am) =
                (cdata[cnt].position.y - scy) * inf_tiles + inf_screeny + 32;
            if (ay(am) < 0 || ay(am) > inf_screenh * inf_tiles + inf_screeny)
            {
                continue;
            }
            if (ax(am) < -20 || ax(am) > windoww + 20)
            {
                continue;
            }
            ap(am) = 20 + (am != 0) * rnd(5);
            ++am;
        }
    }
    {
        int cnt = 0;
        for (;; ++cnt)
        {
            redraw(0);
            pos(0, 0);
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            int af = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (am); cnt < cnt_end; ++cnt)
                {
                    if (ap(cnt) <= 0)
                    {
                        continue;
                    }
                    af = 1;
                    cnt2 = cnt;
                    int anidy =
                        ay(cnt) * std::clamp((20 - ap(cnt)), 0, 6) / 6 - 96;
                    gmode(2, 96, 96);
                    pos(ax(cnt), anidy);
                    gcopy(
                        7,
                        std::clamp((8 - ap(cnt)), 0, 8) * 96
                            + 96 * (ap(cnt) < 15),
                        0,
                        96,
                        96);
                    if (ap(cnt) <= 14)
                    {
                        if (ap(cnt) >= 6)
                        {
                            pos(ax(cnt), anidy + 16);
                            gcopy(7, (14 - ap(cnt)) / 2 * 96, 96, 96, 96);
                        }
                    }
                    int anidx = std::clamp(
                        anidy / 55 + 1,
                        0,
                        7 - std::clamp((11 - ap(cnt)) * 2, 0, 7));
                    {
                        int cnt = 1;
                        for (int cnt_end = cnt + (anidx); cnt < cnt_end; ++cnt)
                        {
                            pos(ax(cnt2), anidy - cnt * 55);
                            gcopy(7, 96 * (ap(cnt2) < 15), 0, 96, 55);
                            if (cnt == anidx)
                            {
                                pos(ax(cnt2), anidy - cnt * 55 - 40);
                                gcopy(7, 288, 0, 96, 40);
                            }
                        }
                    }
                    if (ap(cnt) >= 20)
                    {
                        ap(cnt) -= rnd(2);
                    }
                    else
                    {
                        --ap(cnt);
                    }
                }
            }
            if (cnt % 2 == 0)
            {
                if (cnt < 30)
                {
                    if (cnt / 3 < am)
                    {
                        if (animode == 0)
                        {
                            snd(37);
                        }
                        if (animode >= 100)
                        {
                            snd(33);
                        }
                    }
                }
            }
            if (af == 0)
            {
                break;
            }
            await(cfg_animewait + 25);
            redraw(1);
        }
    }
}


void play_animation_22()
{
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime17.bmp"));
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    am = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (75); cnt < cnt_end; ++cnt)
        {
            ax(am) = 240 + rnd(windoww);
            ay(am) = -96;
            ap(am) = rnd(8);
            ++am;
        }
    }
    {
        int cnt = 0;
        for (;; ++cnt)
        {
            redraw(0);
            if (cnt < 4)
            {
                pos(0, 0);
            }
            else
            {
                pos(5 - rnd(10), 5 - rnd(10));
            }
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            int af = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (am); cnt < cnt_end; ++cnt)
                {
                    if (ap(cnt) >= 16)
                    {
                        continue;
                    }
                    af = 1;
                    gmode(2, 96, 96);
                    if (ap(cnt) < 9)
                    {
                        ax(cnt) -= 16 + cnt % (windoww / 30);
                        ay(cnt) += 24 + cnt % (windowh / 10);
                    }
                    if (ap(cnt) >= 10)
                    {
                        pos(ax(cnt) - 48, ay(cnt));
                        gcopy(7, (ap(cnt) - 10) * 192, 96, 192, 96);
                    }
                    if (ap(cnt) < 16)
                    {
                        pos(ax(cnt), ay(cnt));
                        gcopy(
                            7, std::clamp((ap(cnt) - 8), 0, 8) * 96, 0, 96, 96);
                    }
                    ++ap(cnt);
                }
            }
            if (cnt % 2 == 0)
            {
                if (cnt < 8)
                {
                    if (cnt / 3 < am)
                    {
                        snd(108);
                    }
                }
            }
            if (af == 0)
            {
                break;
            }
            await(cfg_animewait + 40);
            redraw(1);
        }
    }
    await(cfg_animewait);
    redraw(0);
    pos(0, 0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    redraw(1);
}


void play_animation_21()
{
    gsel(7);
    picload(fs::u8path(u8"./graphic/anime16.bmp"));
    gsel(4);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 0, windoww, windowh);
    gsel(0);
    am = 0;
    {
        int cnt = 0;
        for (int cnt_end = cnt + (100); cnt < cnt_end; ++cnt)
        {
            ax(am) = rnd(windoww);
            ay(am) = rnd(inf_screenh * inf_tiles) - 96 - 24;
            ap(am) = 0 - rnd(3);
            ++am;
        }
    }
    {
        int cnt = 0;
        for (;; ++cnt)
        {
            redraw(0);
            pos(5 - rnd(10), 5 - rnd(10));
            gmode(0);
            gcopy(4, 0, 0, windoww, windowh);
            int af = 0;
            {
                int cnt = 0;
                for (int cnt_end = cnt + (am); cnt < cnt_end; ++cnt)
                {
                    if (ap(cnt) >= 10)
                    {
                        continue;
                    }
                    af = 1;
                    cnt2 = cnt;
                    gmode(2, 96, 96);
                    if (ap(cnt) < 10)
                    {
                        pos(ax(cnt), ay(cnt));
                        gcopy(7, ap(cnt) * 96, 96, 96, 96);
                        pos(ax(cnt), ay(cnt) - 96);
                        gcopy(7, ap(cnt) * 96, 0, 96, 96);
                    }
                    if (ap(cnt) < 0)
                    {
                        ap(cnt) += rnd(2);
                    }
                    else
                    {
                        ++ap(cnt);
                    }
                }
            }
            if (cnt % 2 == 0)
            {
                if (cnt < 8)
                {
                    if (cnt / 3 < am)
                    {
                        snd(108);
                    }
                }
            }
            if (af == 0)
            {
                break;
            }
            await(cfg_animewait + 40);
            redraw(1);
        }
    }
    await(cfg_animewait);
    redraw(0);
    pos(0, 0);
    gmode(0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    redraw(1);
}



void play_animation_14_16(int animeid)
{
    sx = FIXME_dig_animation_x;
    sy = FIXME_dig_animation_y;
    aniref = 4;
    ax = (sx - scx) * inf_tiles + inf_screenx;
    ay = (sy - scy) * inf_tiles + inf_screeny;
    if (animeid == 14)
    {
        prepare_item_image(17, 0);
    }
    {
        int cnt = 0;
        for (int cnt_end = cnt + (aniref); cnt < cnt_end; ++cnt)
        {
            sx(cnt) = rnd(24) - 12;
            sy(cnt) = rnd(8);
        }
    }
    gsel(4);
    gmode(0);
    pos(0, 0);
    gcopy(0, ax - 16, ay - 16, 64, 64);
    gmode(2);
    gsel(0);
    {
        int cnt = 0;
        for (int cnt_end = cnt + (5); cnt < cnt_end; ++cnt)
        {
            redraw(0);
            gmode(2);
            cnt2 = cnt * 2;
            gmode(2, inf_tiles, inf_tiles);
            {
                int cnt = 0;
                for (int cnt_end = cnt + (aniref); cnt < cnt_end; ++cnt)
                {
                    pos(ax + 24 + sx(cnt)
                            + (sx(cnt) < 4) * ((1 + (cnt % 2 == 0)) * -1) * cnt2
                            + (sx(cnt) > -4) * (1 + (cnt % 2 == 0)) * cnt2,
                        ay + sy(cnt) + cnt2 * cnt2 / 3);
                    grotate(1, 864, 0, 0.4 * cnt, 24, 24);
                }
            }
            pos(ax + sx + 24, ay + sy + 10);
            grotate(
                1,
                0,
                960,
                0.5 * cnt - 0.8,
                cnt * 10 + aniref * 3,
                cnt * 10 + aniref * 3);
            redraw(1);
            redraw(0);
            gmode(0);
            pos(ax - 16, ay - 16);
            pos(ax - 16, ay - 16);
            gcopy(4, 0, 0, 64, 64);
            gmode(2);
            await(cfg_animewait);
        }
    }
}


} // namespace



namespace elona
{



void play_animation(int animeid)
{
    if (mode == 9)
        return;
    if (cfg_animewait == 0)
        return;

    if (animeid != 21)
    {
        update_screen();
    }

    redraw(0);
    gmode(2, inf_tiles, inf_tiles);

    int anicol = 0;
    int anisound = 0;
    if (animeid < 4)
    {
        anicol = eleinfo(ele, 0);
        anisound = eleinfo(ele, 1);
    }

    switch (animeid)
    {
    case 8: play_animation_8(anicol); break;
    case 6:
    case 5:
    case 7:
    case 11: play_animation_6_5_7_11(animeid, anicol); break;
    case 3: play_animation_3(anicol, anisound); break;
    case 17:
    case 2: play_animation_17_2(animeid, anicol, anisound); break;
    case 0: play_animation_0(anicol, anisound); break;
    case 15: play_animation_15(); break;
    case 111:
    case 110:
    case 108:
    case 109:
    case 1:
    case 18: play_animation_ranged_attack(animeid, anicol, anisound); break;
    case 9: play_animation_9(); break;
    case 12: play_animation_12(); break;
    case 20: play_animation_20(); break;
    case 19: play_animation_19(); break;
    case 22: play_animation_22(); break;
    case 21: play_animation_21(); break;
    case 14:
    case 16: play_animation_14_16(animeid); break;
    default: break;
    }

    gmode(2);
}



} // namespace elona
