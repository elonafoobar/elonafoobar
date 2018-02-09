#include "character.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "item.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{


void render_shadow_low(int light)
{
    color(0, 0, 0);
    gmode(6, inf_tiles, inf_tiles, light);

    for (int y = 0; y < inf_screenh; ++y)
    {
        for (int x = 0; x < inf_screenw; ++x)
        {
            if (slight(x + 2, y + 2) >= 1000)
            {
                pos(x * inf_tiles + inf_screenx, y * inf_tiles + inf_screeny);
                gcopy(3, 144, 752);
            }
        }
    }
}



void render_shadow_high(int light, int sxfix_, int syfix_)
{
    gmode(6, inf_tiles, inf_tiles, light);
    if (scrollanime == 0)
    {
        int y_ = 2;
        int dy_ = inf_screeny + syfix_ * (scrollp > 3);
        int cnt = 0;
        for (int cnt_end = cnt + (inf_screenh); cnt < cnt_end; ++cnt)
        {
            int x_ = 2;
            int dx_ = inf_screenx + sxfix_ * (scrollp > 3);
            int cnt = 0;
            for (int cnt_end = cnt + (inf_screenw); cnt < cnt_end; ++cnt)
            {
                int p_ = slight(x_, y_);
                if (p_ > 0)
                {
                    if (p_ < 300)
                    {
                        int cnt = 0;
                        for (int cnt_end = cnt + (1 + (deco(2, p_) != 0));
                             cnt < cnt_end;
                             ++cnt)
                        {
                            int deco2;
                            if (deco(0, p_) < 0 || cnt)
                            {
                                if (cnt == 1)
                                {
                                    deco2 = deco(2, p_);
                                }
                                else
                                {
                                    deco2 = deco(1, p_);
                                }
                                int cnt = 0;
                                for (int cnt_end = cnt + (1); cnt < cnt_end;
                                     ++cnt)
                                {
                                    if (deco2 == 1)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 2)
                                    {
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 3)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 4)
                                    {
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 5)
                                    {
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 6)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 7)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 8)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 9)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 10)
                                    {
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 20)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 704, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 704, 24, 48);
                                        break;
                                    }
                                    if (deco2 == 21)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 48, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 48, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 30)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 0, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 31)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 96, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 96, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 32)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 656, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 656, 24, 48);
                                        break;
                                    }
                                    if (deco2 == 33)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 752, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 752, 24, 48);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                pos(dx_, dy_);
                                gcopy(
                                    3,
                                    0 + deco(0, p_) * inf_tiles,
                                    656 + deco(1, p_) * inf_tiles);
                            }
                        }
                    }
                    else
                    {
                        int p2_ = (p_ - 1000) % 16;
                        int i_ = 0;
                        if (p2_ == 15)
                        {
                            p2_ = (p_ - 1000) % 256;
                            if (p2_ == 127)
                            {
                                i_ = 13;
                            }
                            if (p2_ == 223)
                            {
                                i_ = 14;
                            }
                            if (p2_ == 191)
                            {
                                i_ = 15;
                            }
                            if (p2_ == 239)
                            {
                                i_ = 16;
                            }
                            if (p2_ == 207 || p2_ == 63)
                            {
                                i_ = 17;
                            }
                        }
                        else
                        {
                            i_ = shadowmap(p2_);
                        }
                        pos(dx_, dy_);
                        gcopy(3, 144 + i_ * inf_tiles, 752);
                    }
                }
                ++x_;
                dx_ += inf_tiles;
            }
            ++y_;
            dy_ += inf_tiles;
        }
    }
    else
    {
        int f_ = 0;
        if (scrollp > 3 || mdata(6) == 20)
        {
            f_ = 1;
        }
        int y_ = 1;
        int dy_ = inf_screeny + syfix_ * f_ - 48;
        int cnt = 0;
        for (int cnt_end = cnt + (inf_screenh + 2); cnt < cnt_end; ++cnt)
        {
            if (dy_ <= -inf_tiles || dy_ >= windowh - inf_verh)
            {
                dy_ += inf_tiles;
                ++y_;
                continue;
            }
            int x_ = 1;
            int dx_ = inf_screenx + sxfix_ * f_ - 48;
            int cnt = 0;
            for (int cnt_end = cnt + (inf_screenw + 2); cnt < cnt_end; ++cnt)
            {
                int p_ = slight(x_, y_);
                if (p_ > 0)
                {
                    if (p_ < 300)
                    {
                        int deco2;
                        int cnt = 0;
                        for (int cnt_end = cnt + (1 + (deco(2, p_) != 0));
                             cnt < cnt_end;
                             ++cnt)
                        {
                            if (deco(0, p_) < 0 || cnt)
                            {
                                if (cnt == 1)
                                {
                                    deco2 = deco(2, p_);
                                }
                                else
                                {
                                    deco2 = deco(1, p_);
                                }
                                int cnt = 0;
                                for (int cnt_end = cnt + (1); cnt < cnt_end;
                                     ++cnt)
                                {
                                    if (deco2 == 1)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 2)
                                    {
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 3)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 4)
                                    {
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 5)
                                    {
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 6)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 7)
                                    {
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 8)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 9)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 168, 680, 24, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 168, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 10)
                                    {
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 144, 680, 24, 24);
                                        pos(dx_ + 24, dy_ + 24);
                                        gcopy(3, 144, 656, 24, 24);
                                        break;
                                    }
                                    if (deco2 == 20)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 704, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 704, 24, 48);
                                        break;
                                    }
                                    if (deco2 == 21)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 48, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 48, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 30)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 0, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 31)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 96, 656, 48, 24);
                                        pos(dx_, dy_ + 24);
                                        gcopy(3, 96, 776, 48, 24);
                                        break;
                                    }
                                    if (deco2 == 32)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 656, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 656, 24, 48);
                                        break;
                                    }
                                    if (deco2 == 33)
                                    {
                                        pos(dx_, dy_);
                                        gcopy(3, 0, 752, 24, 48);
                                        pos(dx_ + 24, dy_);
                                        gcopy(3, 120, 752, 24, 48);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                pos(dx_, dy_);
                                gcopy(
                                    3,
                                    0 + deco(0, p_) * inf_tiles,
                                    656 + deco(1, p_) * inf_tiles);
                            }
                        }
                    }
                    else
                    {
                        int p2_ = (p_ - 1000) % 16;
                        int i_ = 0;
                        if (p2_ == 15)
                        {
                            p2_ = (p_ - 1000) % 256;
                            if (p2_ == 127)
                            {
                                i_ = 13;
                            }
                            if (p2_ == 223)
                            {
                                i_ = 14;
                            }
                            if (p2_ == 191)
                            {
                                i_ = 15;
                            }
                            if (p2_ == 239)
                            {
                                i_ = 16;
                            }
                            if (p2_ == 207 || p2_ == 63)
                            {
                                i_ = 17;
                            }
                        }
                        else
                        {
                            i_ = shadowmap(p2_);
                        }
                        pos(dx_, dy_);
                        gcopy(3, 144 + i_ * inf_tiles, 752, 48, 48);
                    }
                }
                ++x_;
                dx_ += inf_tiles;
            }
            ++y_;
            dy_ += inf_tiles;
        }
    }
}



} // namespace



namespace elona
{


void cell_draw()
{
    int syfix_ = 0;
    int sxfix_ = 0;
    int scrturn_ = 0;
    int scrturnbk_ = 0;
    int scrturnnew_ = 0;
    int light_ = 0;
    int flick_ = 0;
    int dy_ = 0;
    int ly_ = 0;
    int y_ = 0;
    int dx_ = 0;
    int lx_ = 0;
    elona_vector1<int> p_;
    int x_ = 0;
    int px_ = 0;
    int py_ = 0;
    int ground_ = 0;
    int ani_ = 0;
    int sel_ = 0;
    int wall_ = 0;
    int p2_ = 0;
    int i_ = 0;
    elona_vector1<int> flooritem_;
    int stackh_ = 0;
    int cnt2_ = 0;
    int c_ = 0;
    int col_ = 0;
    int h_ = 0;
    syfix_ = (scy != scybk) * syfix;
    sxfix_ = (scx != scxbk) * sxfix;
    scrturn_ = scrturn / 5;

    if (scrturn_ != scrturnbk_)
    {
        scrturnbk_ = scrturn_;
        scrturnnew_ = 1;
    }
    else
    {
        scrturnnew_ = 0;
    }

    light_ = gdata(89);
    randomize(scrturn_);

    if (gdata_torch == 1)
    {
        if (mdata(6) >= 20 && mdata(6) <= 23)
        {
            light_ -= 50;
        }
    }
    if (gdata_hour > 17 || gdata_hour < 6)
    {
        flick_ = rnd(10);
    }
    else
    {
        flick_ = -15;
    }

    repw(2) = repw(1);
    reph(2) = cdata[0].position.y + (syfix < 0);
    reph(3) = reph(2) + 1;

    if (cdata[0].position.y == mdata(1) - 2)
    {
        if (syfix < 0)
        {
            --reph(3);
        }
    }
    if (cdata[0].position.y == mdata(1) - 1)
    {
        if (syfix > 0)
        {
            --reph(3);
        }
    }

    dy_ = (reph(1) - scy) * inf_tiles + inf_screeny + syfix_;
    ly_ = 1;

    int cnt = reph(1);
    for (int cnt_end = cnt + (reph); cnt < cnt_end; ++cnt)
    {
        y_ = cnt;
        dx_ = (repw(1) + repw - 1 - scx) * inf_tiles + inf_screenx + sxfix_;
        lx_ = 1;
        if (dy_ <= -inf_tiles || dy_ >= windowh - inf_verh)
        {
            dy_ += inf_tiles;
            ++lx_;
            continue;
        }
        if (y_ < 0 || y_ >= mdata(1))
        {
            int cnt = scx;
            for (int cnt_end = cnt + (inf_screenw); cnt < cnt_end; ++cnt)
            {
                gmode(0, inf_tiles, inf_tiles);
                p_ = tile_fog;
                pos(dx_, dy_);
                gcopy(2, p_ % 33 * inf_tiles, p_ / 33 * inf_tiles);
                dx_ -= inf_tiles;
                ++lx_;
            }
            dy_ += inf_tiles;
            ++ly_;
            continue;
        }
        color(0, 0, 0);
        {
            int cnt = 0;
            for (int cnt_end = cnt + (repw); cnt < cnt_end; ++cnt)
            {
                x_ = repw(1) + repw - 1 - cnt;
                if (reph(3) == y_)
                {
                    if (x_ == repw(2))
                    {
                        px_ = (cdata[0].position.x - scx) * inf_tiles
                            + inf_screenx - 48;
                        if (scxbk == scx)
                        {
                            px_ -= sxfix;
                        }
                        py_ = (cdata[0].position.y + 1 - scy) * inf_tiles
                            + inf_screeny;
                        if (scybk == scy)
                        {
                            py_ -= syfix;
                        }
                        color(0, 0, 0);
                        gmode(5, inf_tiles, inf_tiles, 50 + flick_);
                        pos(px_, py_);
                        gcopy(3, 800, 208, 144, 48);
                    }
                }
                if (reph(2) == y_)
                {
                    if (x_ == repw(2))
                    {
                        if (cdata[0].state == 1)
                        {
                            ground_ = map(
                                cdata[0].position.x, cdata[0].position.y, 0);
                            px_ = (cdata[0].position.x - scx) * inf_tiles
                                + inf_screenx;
                            if (scxbk == scx)
                            {
                                px_ -= sxfix;
                            }
                            py_ = (cdata[0].position.y - scy) * inf_tiles
                                + inf_screeny;
                            if (scybk == scy)
                            {
                                py_ -= syfix;
                            }
                            color(0, 0, 0);
                            gmode(5, inf_tiles, inf_tiles, 50 + flick_);
                            pos(px_ - 48, py_ - 48);
                            gcopy(3, 800, 112, 144, 96);
                            if (py_ < windowh - inf_verh - 24)
                            {
                                if (cdata[0].continuous_action_id == 7)
                                {
                                    ani_ = 0;
                                }
                                else
                                {
                                    ani_ = cdata[0].turn % 4 * 32;
                                }
                                if (mdata(6) == 1)
                                {
                                    gmode(6, 32, 16, 85);
                                    color(0, 0, 0);
                                    pos(px_ + 24, py_ + 27);
                                    grotate(3, 240, 384, 0, 20, 10);
                                    gmode(2, 32, 48);
                                    pos(px_ + 24, py_ + 14);
                                    grotate(
                                        10,
                                        ani_,
                                        cdata[0].direction * 48,
                                        0,
                                        16,
                                        24);
                                }
                                else if (chipm(0, ground_) == 3)
                                {
                                    gmode(4, 32, 20, 146);
                                    color(0, 0, 0);
                                    pos(px_ + 24, py_ + 36);
                                    grotate(
                                        10,
                                        ani_,
                                        cdata[0].direction * 48 + 28,
                                        0,
                                        24,
                                        16);
                                    gmode(2, 32, 28);
                                    pos(px_ + 24, py_ + 16);
                                    grotate(
                                        10,
                                        ani_,
                                        cdata[0].direction * 48,
                                        0,
                                        24,
                                        24);
                                }
                                else
                                {
                                    gmode(6, -1, -1, 110);
                                    color(0, 0, 0);
                                    pos(px_ + 8, py_ + 20);
                                    gcopy(3, 240, 384, 32, 16);
                                    if (fishanime == 3)
                                    {
                                        if (fishanime(1) % 8 < 4)
                                        {
                                            py_ -= fishanime(1) % 4
                                                * (fishanime(1) % 4);
                                        }
                                        else
                                        {
                                            py_ += fishanime(1) % 4
                                                    * (fishanime(1) % 4)
                                                - 9;
                                        }
                                    }
                                    gmode(2, 32, 48);
                                    pos(px_ + 24, py_ + 8);
                                    grotate(
                                        10,
                                        ani_,
                                        cdata[0].direction * 48,
                                        0,
                                        24,
                                        40);
                                }
                                gmode(2);
                                color(0, 0, 0);
                            }
                            if (cdata[0].furious != 0)
                            {
                                pos(px_, py_ - 24);
                                gcopy(3, 32, 608, 16, 16);
                            }
                            if (cdata[0].emotion_icon != 0)
                            {
                                draw_emo(0, px_ + 4, py_ - 32);
                            }
                        }
                    }
                }
                if (dx_ <= -inf_tiles || dx_ >= windoww)
                {
                    dx_ -= inf_tiles;
                    ++lx_;
                    continue;
                }
                if (x_ < 0 || x_ >= mdata(0))
                {
                    gmode(0, inf_tiles, inf_tiles);
                    p_ = tile_fog;
                    pos(dx_, dy_);
                    gcopy(2, p_ % 33 * inf_tiles, p_ / 33 * inf_tiles);
                    dx_ -= inf_tiles;
                    continue;
                }
                ground_ = map(x_, y_, 2);
                sel_ = 2;
                gmode(0, inf_tiles, inf_tiles);
                pos(dx_, dy_);
                wall_ = 0;
                if (chipm(2, ground_) == 2)
                {
                    if (y_ < mdata(1) - 1)
                    {
                        if (chipm(2, map(x_, y_ + 1, 2)) != 2
                            && map(x_, y_ + 1, 2) != tile_fog)
                        {
                            ground_ += 33;
                        }
                    }
                }
                if (chipm(2, ground_))
                {
                    wall_ = 1;
                }
                if (chipm(3, ground_) != 0)
                {
                    gcopy(
                        sel_,
                        (ground_ % 33
                         + (scrturn_ % (chipm(3, ground_) + 1)
                            - (scrturn_ % (chipm(3, ground_) + 1)
                               == chipm(3, ground_))
                                * 2 * (chipm(3, ground_) != 0)))
                            * inf_tiles,
                        ground_ / 33 * inf_tiles);
                }
                else
                {
                    gcopy(
                        sel_,
                        ground_ % 33 * inf_tiles,
                        ground_ / 33 * inf_tiles);
                }
                gmode(2, inf_tiles, inf_tiles);
                if (map(x_, y_, 7) != 0)
                {
                    if (mapsync(x_, y_) == msync)
                    {
                        p_(0) = map(x_, y_, 7) % 10;
                        p_(1) = map(x_, y_, 7) / 10;
                        if (p_(1))
                        {
                            gcopy(5, p_(1) * inf_tiles + 288, 1152);
                        }
                        if (p_)
                        {
                            if (p_ > 6)
                            {
                                p_ = 6;
                            }
                            gcopy(5, p_ * inf_tiles, 1152);
                        }
                    }
                }
                if (efmap(1, x_, y_) > 0)
                {
                    if (mapsync(x_, y_) == msync)
                    {
                        p_ = efmap(0, x_, y_);
                        if (scrturnnew_ == 1)
                        {
                            --efmap(1, x_, y_);
                        }
                        if (mefsubref(2, p_) == 1)
                        {
                            gmode(4, 32, 32, efmap(1, x_, y_) * 12 + 30);
                            pos(dx_ + 24, dy_ + 24);
                            grotate(
                                3,
                                mefsubref(0, p_) + efmap(3, x_, y_) * 32,
                                mefsubref(1, p_),
                                0.785 * efmap(2, x_, y_),
                                32,
                                32);
                        }
                        else
                        {
                            gmode(4, 32, 32, 150);
                            pos(dx_ + 8, dy_ + 8);
                            gcopy(
                                3,
                                mefsubref(0, p_) + efmap(1, x_, y_) * 32,
                                mefsubref(1, p_));
                        }
                        gmode(2, inf_tiles, inf_tiles);
                    }
                }
                if (map(x_, y_, 6) != 0)
                {
                    if (map(x_, y_, 2) == map(x_, y_, 0))
                    {
                        p_ = map(x_, y_, 6) % 1000;
                        if (p_ != 999 && p_ != 0)
                        {
                            pos(dx_, dy_ - chipm(5, p_));
                            gcopy(
                                2,
                                p_ % 33 * inf_tiles,
                                p_ / 33 * inf_tiles,
                                inf_tiles,
                                48 + chipm(6, p_));
                        }
                        if (mdata(6) == 1)
                        {
                            p_ = map(x_, y_, 6) / 100000 % 100
                                + map(x_, y_, 6) / 10000000 * 100;
                            if (adata(16, p_) == 8)
                            {
                                if (adata(6, p_) == adata(10, p_))
                                {
                                    pos(dx_ + 16, dy_ - 16);
                                    gcopy(3, 32, 624, 16, 16);
                                }
                                else if (adata(6, p_) != 0)
                                {
                                    pos(dx_ + 16, dy_ - 16);
                                    gcopy(3, 48, 624, 16, 16);
                                }
                            }
                        }
                    }
                }
                if (map(x_, y_, 8) != 0)
                {
                    if (mapsync(x_, y_) == msync)
                    {
                        p2_ = map(x_, y_, 8) - 1;
                        p_(0) = mef(1, p2_) % 10000;
                        p_(1) = mef(1, p2_) / 10000;
                        pos(dx_, dy_ - chipi(4, p_));
                        if (chipi(7, p_))
                        {
                            p_ += (scrturn_ + p2_) % (chipi(7, p_) + 1)
                                - ((scrturn_ + p2_) % (chipi(7, p_) + 1)
                                   == chipi(7, p_))
                                    * 2 * (chipi(7, p_) != 0);
                        }
                        if (mef(1, p2_) > 10000)
                        {
                            prepare_item_image(p_, p_(1));
                            gcopy(1, 0, 960, inf_tiles, inf_tiles);
                        }
                        else
                        {
                            gcopy(
                                1,
                                chipi(0, p_),
                                chipi(1, p_),
                                inf_tiles,
                                inf_tiles);
                        }
                    }
                }
                if (map(x_, y_, 5) != 0)
                {
                    if (map(x_, y_, 5) < 0)
                    {
                        if (mode == 6 || mode == 9)
                        {
                            i_ = 0;
                            p_ = 363;
                            goto label_0380_internal;
                        }
                        p_ = -map(x_, y_, 5);
                        flooritem_(0) = p_ % 1000 + 5080;
                        flooritem_(1) = p_ / 1000 % 1000 + 5080;
                        flooritem_(2) = p_ / 1000000 % 1000 + 5080;
                        stackh_ = 0;
                        {
                            int cnt = 0;
                            for (int cnt_end = cnt + (3); cnt < cnt_end; ++cnt)
                            {
                                cnt2_ = 2 - cnt;
                                if (flooritem_(cnt2_) == 6079)
                                {
                                    continue;
                                }
                                p_ = inv[flooritem_(cnt2_)].image;
                                i_ = inv[flooritem_(cnt2_)].color;
                                prepare_item_image(p_, i_);
                                if (mdata(6) == 1)
                                {
                                    gmode(2, chipi(2, p_), chipi(3, p_));
                                    pos(dx_ + 24, dy_ + 24 - stackh_ / 2);
                                    grotate(1, 0, 960, 0, 24, 24);
                                }
                                else
                                {
                                    if (cfg_objectshadow)
                                    {
                                        if (chipi(6, p_))
                                        {
                                            gmode(
                                                2,
                                                chipi(2, p_),
                                                chipi(3, p_),
                                                70);
                                            if (chipi(3, p_) == inf_tiles)
                                            {
                                                pos(dx_ + chipi(2, p_) / 2
                                                        + chipi(6, p_) / 80 + 2,
                                                    dy_ - chipi(4, p_) + 22
                                                        - stackh_);
                                                if (chipi(4, p_) < 24)
                                                {
                                                    func_2(
                                                        1,
                                                        0,
                                                        960,
                                                        chipi(6, p_) / 2,
                                                        chipi(2, p_),
                                                        chipi(3, p_));
                                                }
                                            }
                                            else
                                            {
                                                pos(dx_ + chipi(2, p_) / 2
                                                        + chipi(6, p_) / 4,
                                                    dy_ - chipi(4, p_) + 46
                                                        - stackh_);
                                                func_2(
                                                    1,
                                                    0,
                                                    960,
                                                    chipi(6, p_) * 2,
                                                    chipi(2, p_),
                                                    chipi(3, p_));
                                            }
                                            gmode(2);
                                        }
                                    }
                                    pos(dx_, dy_ - chipi(4, p_) - stackh_);
                                    if (chipi(7, p_) == 0)
                                    {
                                        gcopy(
                                            1,
                                            0,
                                            960,
                                            chipi(2, p_),
                                            chipi(3, p_));
                                    }
                                    else
                                    {
                                        gcopy(
                                            1,
                                            chipi(0, p_)
                                                + (scrturn_ % (chipi(7, p_) + 1)
                                                   - (scrturn_
                                                          % (chipi(7, p_) + 1)
                                                      == chipi(7, p_))
                                                       * 2
                                                       * (chipi(7, p_) != 0))
                                                    * inf_tiles,
                                            chipi(1, p_),
                                            chipi(2, p_),
                                            chipi(3, p_));
                                    }
                                }
                                stackh_ += chipi(5, p_);
                                if (p_ == 531)
                                {
                                    if (chipc(3, i_) == 96)
                                    {
                                        stackh_ += 44;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        i_ = wpeek(map(x_, y_, 5), 2);
                        p_ = wpeek(map(x_, y_, 5), 0);
                    label_0380_internal:
                        prepare_item_image(p_, i_);
                        if (mdata(6) == 1)
                        {
                            gmode(2, chipi(2, p_), chipi(3, p_));
                            pos(dx_ + 24, dy_ + 24);
                            grotate(1, 0, 960, 0, 24, 24);
                        }
                        else
                        {
                            if (cfg_objectshadow)
                            {
                                if (chipi(6, p_))
                                {
                                    gmode(2, chipi(2, p_), chipi(3, p_), 80);
                                    if (chipi(3, p_) == inf_tiles)
                                    {
                                        pos(dx_ + chipi(2, p_) / 2
                                                + chipi(6, p_) / 80 + 2,
                                            dy_ - chipi(4, p_) + 22);
                                        if (chipi(4, p_) < 24)
                                        {
                                            func_2(
                                                1,
                                                0,
                                                960,
                                                chipi(6, p_) / 2,
                                                chipi(2, p_),
                                                chipi(3, p_));
                                        }
                                    }
                                    else
                                    {
                                        pos(dx_ + chipi(2, p_) / 2
                                                + chipi(6, p_) / 4,
                                            dy_ - chipi(4, p_) + 46);
                                        func_2(
                                            1,
                                            0,
                                            960,
                                            chipi(6, p_) * 2,
                                            chipi(2, p_),
                                            chipi(3, p_));
                                    }
                                    gmode(2);
                                }
                            }
                            pos(dx_, dy_ - chipi(4, p_));
                            if (chipi(7, p_) == 0)
                            {
                                gcopy(1, 0, 960, chipi(2, p_), chipi(3, p_));
                            }
                            else
                            {
                                gcopy(
                                    1,
                                    chipi(0, p_)
                                        + (scrturn_ % (chipi(7, p_) + 1)
                                           - (scrturn_ % (chipi(7, p_) + 1)
                                              == chipi(7, p_))
                                               * 2 * (chipi(7, p_) != 0))
                                            * inf_tiles,
                                    chipi(1, p_),
                                    chipi(2, p_),
                                    chipi(3, p_));
                            }
                        }
                    }
                }
                if (map(x_, y_, 1) != 0)
                {
                    c_ = map(x_, y_, 1) - 1;
                    if (synccheck(c_, -1))
                    {
                        if (cbit(6, c_) == 1)
                        {
                            if (cbit(7, 0) == 0)
                            {
                                if (cdata[c_].wet == 0)
                                {
                                    c_ = 0;
                                }
                            }
                        }
                        if (c_ != 0)
                        {
                            if (cbit(967, c_) == 1)
                            {
                                if (mdata(6) == 1)
                                {
                                    gmode(6, 32, 16, 85);
                                    color(0, 0, 0);
                                    pos(dx_ + 24, dy_ + 27);
                                    grotate(3, 240, 384, 0, 20, 10);
                                    gmode(2, 32, 48);
                                    pos(dx_ + 24, dy_ + 14);
                                    grotate(
                                        10 + c_,
                                        ani_,
                                        cdata[c_].direction * 48,
                                        0,
                                        16,
                                        24);
                                }
                                else if (chipm(0, ground_) == 3)
                                {
                                    gmode(4, 32, 20, 146);
                                    color(0, 0, 0);
                                    pos(dx_ + 24, dy_ + 36);
                                    grotate(
                                        10 + c_,
                                        ani_,
                                        cdata[c_].direction * 48 + 28,
                                        0,
                                        24,
                                        16);
                                    gmode(2, 32, 28);
                                    pos(dx_ + 24, dy_ + 16);
                                    grotate(
                                        10 + c_,
                                        ani_,
                                        cdata[c_].direction * 48,
                                        0,
                                        24,
                                        24);
                                }
                                else
                                {
                                    gmode(6, -1, -1, 110);
                                    color(0, 0, 0);
                                    pos(dx_ + 8, dy_ + 20);
                                    gcopy(3, 240, 384, 32, 16);
                                    gmode(2, 32, 48);
                                    pos(dx_ + 24, dy_ + 8);
                                    grotate(
                                        10 + c_,
                                        ani_,
                                        cdata[c_].direction * 48,
                                        0,
                                        24,
                                        40);
                                }
                                gmode(2);
                                color(0, 0, 0);
                                if (cdata[c_].furious != 0)
                                {
                                    pos(dx_ + 12, dy_ - 28);
                                    gcopy(3, 32, 608, 16, 16);
                                }
                                if (cdata[c_].emotion_icon != 0)
                                {
                                    draw_emo(c_, dx_ + 4, dy_ - 32);
                                }
                            }
                            else
                            {
                                col_ = cdata[c_].image / 1000;
                                p_ = cdata[c_].image % 1000;
                                if (cbit(985, c_))
                                {
                                    gmode(2, 48, 96, 80);
                                    pos(dx_ + 26 - 11, dy_ - 32 + 11);
                                    func_2(1, 96, 816, -80, 48, 96);
                                    pos(dx_, dy_ - 63);
                                    gcopy(1, 96, 816, 48, 96);
                                    chipc(4, p_) += 24;
                                }
                                gsel(5);
                                color(0);
                                boxf(0, 960, chipc(2, p_), chipc(3, p_) + 960);
                                pos(0, 960);
                                gcopy(
                                    5,
                                    chipc(0, p_),
                                    chipc(1, p_),
                                    chipc(2, p_),
                                    chipc(3, p_));
                                gfini(chipc(2, p_), chipc(3, p_));
                                gfdec2(
                                    c_col(0, col_),
                                    c_col(1, col_),
                                    c_col(2, col_));
                                gsel(0);
                                if (mdata(6) == 1)
                                {
                                    gmode(6, 32, 16, 85);
                                    color(0, 0, 0);
                                    pos(dx_ + 24, dy_ + 32);
                                    grotate(3, 240, 384, 0, 20, 10);
                                    gmode(2, chipc(2, p_), chipc(3, p_));
                                    pos(dx_ + 24, dy_ + 24 - chipc(4, p_) / 4);
                                    grotate(5, 0, 960, 0, 24, chipc(3, p_) / 2);
                                    if (cdata[c_].emotion_icon != 0)
                                    {
                                        draw_emo(
                                            c_,
                                            dx_ + 4,
                                            dy_ - chipc(4, p_) / 4 - 16);
                                    }
                                }
                                else
                                {
                                    if (chipm(0, ground_) == 3)
                                    {
                                        gmode(4, inf_tiles, inf_tiles, 100);
                                        color(0, 0, 0);
                                        pos(dx_,
                                            dy_ + 16 - chipc(4, p_)
                                                - (chipm(0, ground_) == 3)
                                                    * -16);
                                        gcopy(
                                            5,
                                            0,
                                            976,
                                            chipc(2, p_),
                                            chipc(3, p_) - 16);
                                        gmode(2, inf_tiles, inf_tiles);
                                        pos(dx_,
                                            dy_ - chipc(4, p_)
                                                - (chipm(0, ground_) == 3)
                                                    * -16);
                                        gcopy(
                                            5,
                                            0,
                                            960,
                                            chipc(2, p_),
                                            chipc(3, p_) - 16);
                                    }
                                    else
                                    {
                                        gmode(6, -1, -1, 110);
                                        color(0, 0, 0);
                                        pos(dx_ + 8, dy_ + 20);
                                        gcopy(3, 240, 384, 32, 16);
                                        gmode(2, inf_tiles, inf_tiles);
                                        pos(dx_,
                                            dy_ - chipc(4, p_)
                                                - (chipm(0, ground_) == 3)
                                                    * -16);
                                        gcopy(
                                            5,
                                            0,
                                            960,
                                            chipc(2, p_),
                                            chipc(3, p_));
                                    }
                                    if (cdata[c_].furious != 0)
                                    {
                                        pos(dx_ + 12, dy_ - chipc(4, p_) - 12);
                                        gcopy(3, 32, 608, 16, 16);
                                    }
                                    if (cdata[c_].emotion_icon != 0)
                                    {
                                        draw_emo(
                                            c_,
                                            dx_ + 4,
                                            dy_ - chipc(4, p_) - 16);
                                    }
                                }
                                if (cbit(985, c_))
                                {
                                    pos(dx_, dy_ - 26);
                                    gcopy(1, 96, 768, 48, 48);
                                    chipc(4, p_) -= 24;
                                }
                            }
                            if (cbit(966, c_) == 1 || gdata(94) == c_)
                            {
                                h_ = std::min(
                                    cdata[c_].hp * 30 / cdata[c_].max_hp, 30);
                                if (h_ > 0)
                                {
                                    if (c_ < 16)
                                    {
                                        if (mdata(6) != 1)
                                        {
                                            pos(dx_ + 9, dy_ + 32);
                                            gcopy(3, 480 - h_, 517, h_, 3);
                                        }
                                    }
                                    else
                                    {
                                        pos(dx_ + 9, dy_ + 32);
                                        gcopy(3, 480 - h_, 513, h_, 3);
                                    }
                                }
                            }
                        }
                    }
                }
                if (map(x_, y_, 9) != 0)
                {
                    p_ = map(x_, y_, 9);
                    if (gdata_hour > 17 || gdata_hour < 6 || lightdata(6, p_))
                    {
                        if (mapsync(x_, y_) == msync)
                        {
                            light_ -= (6
                                       - std::clamp(
                                             dist(
                                                 cdata[0].position.x,
                                                 cdata[0].position.y,
                                                 x_,
                                                 y_),
                                             0,
                                             6))
                                * lightdata(4, p_);
                            pos(dx_, dy_ - lightdata(3, p_));
                            gmode(
                                5,
                                inf_tiles,
                                inf_tiles,
                                lightdata(2, p_) + rnd((lightdata(5, p_) + 1)));
                            gcopy(
                                3,
                                192 + lightdata(0, p_) * 48
                                    + rnd((lightdata(1, p_) + 1)) * inf_tiles,
                                704);
                        }
                    }
                }
                if (wall_ == 0)
                {
                    if (ground_ != tile_fog)
                    {
                        if (y_ > 0)
                        {
                            if (dy_ > 48)
                            {
                                ground_ = map(x_, y_ - 1, 0);
                                if (chipm(2, ground_))
                                {
                                    pos(dx_ + (dx_ < 0) * -dx_, dy_);
                                    gfini(
                                        inf_tiles
                                            - (dx_ > windoww - inf_tiles)
                                                * (dx_ + inf_tiles - windoww)
                                            + (dx_ < 0) * dx_,
                                        24);
                                    gfdec2(16, 16, 16);
                                    pos(dx_ + (dx_ < 0) * -dx_, dy_ + 24);
                                    gfini(
                                        inf_tiles
                                            - (dx_ > windoww - inf_tiles)
                                                * (dx_ + inf_tiles - windoww)
                                            + (dx_ < 0) * dx_,
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
                    if (y_ > 0)
                    {
                        p_ = map(x_, y_ - 1, 2);
                        if (chipm(2, p_) != 2 && p_ != tile_fog)
                        {
                            if (dy_ > 20)
                            {
                                pos(dx_, dy_ - 12);
                                gcopy(
                                    sel_,
                                    ground_ % 33 * inf_tiles,
                                    ground_ / 33 * inf_tiles,
                                    inf_tiles
                                        - (dx_ > windoww - inf_tiles)
                                            * (dx_ + inf_tiles - windoww),
                                    12);
                                pos(dx_ + (dx_ < 0) * -dx_, dy_ - 20);
                                gfini(
                                    inf_tiles
                                        - (dx_ > windoww - inf_tiles)
                                            * (dx_ + inf_tiles - windoww)
                                        + (dx_ < 0) * dx_,
                                    8);
                                gfdec2(25, 25, 25);
                            }
                        }
                    }
                }
                dx_ -= inf_tiles;
                ++lx_;
            }
        }
        dy_ += inf_tiles;
        ++ly_;
    }

    if (light_ < 25)
    {
        light_ = 25;
    }

    if (mdata(6) == 1)
    {
        int cnt = 0;
        for (int cnt_end = cnt + (12); cnt < cnt_end; ++cnt)
        {
            gmode(5, -1, -1, 7 + cnt * 2);
            x_ = (cloud(0, cnt) - cdata[0].position.x * 48 + sxfix) * 100
                    / (40 + cnt * 5)
                + scrturn * 100 / (50 + cnt * 20);
            y_ = (cloud(1, cnt) - cdata[0].position.y * 48 + syfix) * 100
                / (40 + cnt * 5);
            x_ = x_ % (windoww + cloud(4, cnt)) - cloud(4, cnt);
            y_ = y_ % (inf_very + cloud(5, cnt)) - cloud(5, cnt);
            h_ = cloud(5, cnt);
            if (y_ + cloud(5, cnt) >= inf_very)
            {
                h_ = inf_very - y_;
            }
            if (y_ < inf_very)
            {
                pos(x_, y_);
                gcopy(2, cloud(2, cnt), cloud(3, cnt), cloud(4, cnt), h_);
            }
        }
    }

    if (cfg_shadow != 0)
    {
        render_shadow_low(light_);
    }
    else
    {
        render_shadow_high(light_, sxfix_, syfix_);
    }
    gmode(2);
    randomize();
}



} // namespace elona
