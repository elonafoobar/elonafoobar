#include "character.hpp"
#include "config.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "variables.hpp"

using namespace elona;


namespace
{



template <typename T>
struct loop_xy
{
    struct iterator
    {
        using value_type = std::pair<T, T>;
        using difference_type = size_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_category = std::input_iterator_tag;

        iterator(T x, T y, T width)
            : value(x, y)
            , width(width)
        {
        }

        reference operator*() const
        {
            return value;
        }

        pointer operator->() const
        {
            return &value;
        }

        bool operator!=(const iterator& other) const noexcept
        {
            return value != other.value;
        }

        void operator++()
        {
            ++value.first;
            if (value.first == width)
            {
                value.first = 0;
                ++value.second;
            }
        }

    private:
        value_type value;
        T width;
    };


    loop_xy(T width, T height)
        : width(width)
        , height(height)
    {
    }


    iterator begin() const
    {
        return {0, 0, width};
    }

    iterator end() const
    {
        return {0, height, width};
    }

private:
    T width;
    T height;
};



void render_shadow_low(int light)
{
    gmode(6, inf_tiles, inf_tiles, light);

    for (const auto& pos : loop_xy<int>(inf_screenw, inf_screenh))
    {
        const auto x = pos.first;
        const auto y = pos.second;
        if (slight(x + 2, y + 2) >= 1000)
        {
            elona::pos(
                x * inf_tiles + inf_screenx, y * inf_tiles + inf_screeny);
            gcopy(3, 144, 752);
        }
    }
}



void render_shadow(int p_, int dx_, int dy_)
{
    if (p_ <= 0)
        return;
    if (p_ < 300)
    {
        for (int i = 0; i < 1 + (deco(2, p_) != 0); ++i)
        {
            if (deco(0, p_) < 0 || i == 1)
            {
                int deco2;
                if (i == 0)
                {
                    deco2 = deco(1, p_);
                }
                else
                {
                    deco2 = deco(2, p_);
                }
                switch (deco2)
                {
                case 1:
                    pos(dx_, dy_);
                    gcopy(3, 168, 680, 24, 24);
                    break;
                case 2:
                    pos(dx_ + 24, dy_ + 24);
                    gcopy(3, 144, 656, 24, 24);
                    break;
                case 3:
                    pos(dx_, dy_ + 24);
                    gcopy(3, 168, 656, 24, 24);
                    break;
                case 4:
                    pos(dx_ + 24, dy_);
                    gcopy(3, 144, 680, 24, 24);
                    break;
                case 5:
                    pos(dx_ + 24, dy_ + 24);
                    gcopy(3, 144, 656, 24, 24);
                    pos(dx_, dy_);
                    gcopy(3, 168, 680, 24, 24);
                    break;
                case 6:
                    pos(dx_, dy_ + 24);
                    gcopy(3, 168, 656, 24, 24);
                    pos(dx_ + 24, dy_);
                    gcopy(3, 144, 680, 24, 24);
                    break;
                case 7:
                    pos(dx_, dy_ + 24);
                    gcopy(3, 168, 656, 24, 24);
                    pos(dx_ + 24, dy_ + 24);
                    gcopy(3, 144, 656, 24, 24);
                    break;
                case 8:
                    pos(dx_, dy_);
                    gcopy(3, 168, 680, 24, 24);
                    pos(dx_ + 24, dy_);
                    gcopy(3, 144, 680, 24, 24);
                    break;
                case 9:
                    pos(dx_, dy_);
                    gcopy(3, 168, 680, 24, 24);
                    pos(dx_, dy_ + 24);
                    gcopy(3, 168, 656, 24, 24);
                    break;
                case 10:
                    pos(dx_ + 24, dy_);
                    gcopy(3, 144, 680, 24, 24);
                    pos(dx_ + 24, dy_ + 24);
                    gcopy(3, 144, 656, 24, 24);
                    break;
                case 20:
                    pos(dx_, dy_);
                    gcopy(3, 0, 704, 24, 48);
                    pos(dx_ + 24, dy_);
                    gcopy(3, 120, 704, 24, 48);
                    break;
                case 21:
                    pos(dx_, dy_);
                    gcopy(3, 48, 656, 48, 24);
                    pos(dx_, dy_ + 24);
                    gcopy(3, 48, 776, 48, 24);
                    break;
                case 30:
                    pos(dx_, dy_);
                    gcopy(3, 0, 656, 48, 24);
                    pos(dx_, dy_ + 24);
                    gcopy(3, 0, 776, 48, 24);
                    break;
                case 31:
                    pos(dx_, dy_);
                    gcopy(3, 96, 656, 48, 24);
                    pos(dx_, dy_ + 24);
                    gcopy(3, 96, 776, 48, 24);
                    break;
                case 32:
                    pos(dx_, dy_);
                    gcopy(3, 0, 656, 24, 48);
                    pos(dx_ + 24, dy_);
                    gcopy(3, 120, 656, 24, 48);
                    break;
                case 33:
                    pos(dx_, dy_);
                    gcopy(3, 0, 752, 24, 48);
                    pos(dx_ + 24, dy_);
                    gcopy(3, 120, 752, 24, 48);
                    break;
                default: break;
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



void render_shadow_high(int light, int sxfix_, int syfix_)
{
    gmode(6, inf_tiles, inf_tiles, light);

    if (scrollanime == 0)
    {
        for (const auto& pos : loop_xy<int>(inf_screenw, inf_screenh))
        {
            const auto x = pos.first;
            const auto y = pos.second;
            render_shadow(
                slight(x + 2, y + 2),
                inf_screenx + sxfix_ * (scrollp > 3) + x * inf_tiles,
                inf_screeny + syfix_ * (scrollp > 3) + y * inf_tiles);
        }
    }
    else
    {
        int f_ = 0;
        if (scrollp > 3 || mdata(6) == 20)
        {
            f_ = 1;
        }
        for (const auto& pos : loop_xy<int>(inf_screenw + 2, inf_screenh + 2))
        {
            const auto x = pos.first;
            const auto y = pos.second;
            int dy_ = inf_screeny + syfix_ * f_ - 48 + y * inf_tiles;
            if (dy_ <= -inf_tiles || dy_ >= windowh - inf_verh)
                continue;
            render_shadow(
                slight(x + 1, y + 1),
                inf_screenx + sxfix_ * f_ - 48 + x * inf_tiles,
                dy_);
        }
    }
}



struct cloud
{
    cloud(int x0, int y0, int x, int y, int width, int height)
        : x0(x0)
        , y0(y0)
        , x(x)
        , y(y)
        , width(width)
        , height(height)
    {
    }

    int x0;
    int y0;
    int x;
    int y;
    int width;
    int height;
};

std::vector<cloud> clouds;


void initialize_cloud_data()
{
    for (int i = 0; i < 12; ++i)
    {
        int x0 = rnd(100) + i * 200 + 100000;
        int y0 = rnd(100) + i / 5 * 200 + 100000;
        if (rnd(2) == 0)
        {
            clouds.emplace_back(x0, y0, 288, 1040, 208, 160);
        }
        else
        {
            clouds.emplace_back(x0, y0, 0, 976, 288, 224);
        }
    }
}



void render_cloud()
{
    static int dummy = ((void)initialize_cloud_data(), 0);
    UNUSED(dummy);

    for (size_t i = 0; i < clouds.size(); ++i)
    {
        gmode(5, -1, -1, 7 + i * 2);
        int x = (clouds[i].x0 - cdata[0].position.x * inf_tiles + sxfix) * 100
                / (40 + i * 5)
            + scrturn * 100 / (50 + i * 20);
        int y = (clouds[i].y0 - cdata[0].position.y * inf_tiles + syfix) * 100
            / (40 + i * 5);
        x = x % (windoww + clouds[i].width) - clouds[i].width;
        y = y % (inf_very + clouds[i].height) - clouds[i].height;
        int height = clouds[i].height;
        if (y + height > inf_very)
        {
            height = inf_very - y;
        }
        if (y < inf_very)
        {
            pos(x, y);
            gcopy(2, clouds[i].x, clouds[i].y, clouds[i].width, height);
        }
    }
}



void draw_hp_bar(int cc, int x, int y)
{
    const int ratio = std::min(cdata[cc].hp * 30 / cdata[cc].max_hp, 30);
    if (ratio <= 0)
        return;

    if (cc < 16)
    {
        if (mdata(6) != 1)
        {
            pos(x + 9, y + 32);
            gcopy(3, 480 - ratio, 517, ratio, 3);
        }
    }
    else
    {
        pos(x + 9, y + 32);
        gcopy(3, 480 - ratio, 513, ratio, 3);
    }
}



struct lightdata_t
{
    int _0;
    int _1;
    int _2;
    int _3;
    int _4;
    int _5;
    bool _6;
};


lightdata_t lightdata[] = {
    {0, 0, 0, 0, 0, 0, false},      {1, 1, 50, 8, 8, 50, true},
    {1, 1, 70, 28, 8, 70, true},    {3, 0, 100, 30, 8, 20, false},
    {3, 0, 80, 0, 6, 40, false},    {11, 0, 140, 48, 10, 20, false},
    {5, 1, 170, 4, 2, 80, true},    {9, 1, 30, 8, 2, 80, true},
    {9, 1, 30, 24, 2, 80, true},    {7, 0, 35, 4, 1, 40, true},
    {7, 0, 35, 24, 1, 40, true},    {8, 0, 120, 0, 15, 15, false},
    {4, 0, 50, 48, 5, 70, true},    {4, 0, 50, 16, 5, 70, true},
    {0, 0, 140, 62, 10, 20, false}, {11, 0, 100, 72, 10, 20, false},
    {9, 1, 30, 50, 5, 80, true},    {12, 0, 100, 24, 3, 10, false},
    {12, 0, 20, 32, 2, 30, true},   {13, 0, 70, 35, 3, 10, false},
};



} // namespace



namespace elona
{


void cell_draw()
{
    int scrturnbk_ = 0;
    int scrturnnew_ = 0;
    elona_vector1<int> p_;
    int ground_ = 0;
    int ani_ = 0;

    const int syfix_ = (scy != scybk) * syfix;
    const int sxfix_ = (scx != scxbk) * sxfix;
    const int scrturn_ = scrturn / 5;

    if (scrturn_ != scrturnbk_)
    {
        scrturnbk_ = scrturn_;
        scrturnnew_ = 1;
    }
    else
    {
        scrturnnew_ = 0;
    }

    int light_ = gdata(89);
    randomize(scrturn_);

    if (gdata_torch == 1)
    {
        if (mdata(6) >= 20 && mdata(6) <= 23)
        {
            light_ -= 50;
        }
    }
    int flick_ = 0;
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

    int dy_ = (reph(1) - scy) * inf_tiles + inf_screeny + syfix_;

    for (int y = reph(1); y < reph(1) + reph; ++y, dy_ += inf_tiles)
    {
        int dx_ = (repw(1) + repw - 1 - scx) * inf_tiles + inf_screenx + sxfix_;
        if (dy_ <= -inf_tiles || dy_ >= windowh - inf_verh)
        {
            continue;
        }
        if (y < 0 || y >= mdata(1))
        {
            for (int i = scx; i < scx + inf_screenw; ++i)
            {
                gmode(0, inf_tiles, inf_tiles);
                p_ = tile_fog;
                pos(dx_, dy_);
                gcopy(2, p_ % 33 * inf_tiles, p_ / 33 * inf_tiles);
                dx_ -= inf_tiles;
            }
            continue;
        }
        for (int cnt = 0; cnt < repw; ++cnt, dx_ -= inf_tiles)
        {
            const int x_ = repw(1) + repw - 1 - cnt;
            int px_ = 0;
            int py_ = 0;
            if (reph(3) == y && x_ == repw(2) && cdata[0].state == 1)
            {
                px_ =
                    (cdata[0].position.x - scx) * inf_tiles + inf_screenx - 48;
                if (scxbk == scx)
                {
                    px_ -= sxfix;
                }
                py_ = (cdata[0].position.y + 1 - scy) * inf_tiles + inf_screeny;
                if (scybk == scy)
                {
                    py_ -= syfix;
                }
                gmode(5, inf_tiles, inf_tiles, 50 + flick_);
                pos(px_, py_);
                gcopy(3, 800, 208, 144, 48);
            }
            if (reph(2) == y && x_ == repw(2) && cdata[0].state == 1)
            {
                ground_ = map(cdata[0].position.x, cdata[0].position.y, 0);
                px_ = (cdata[0].position.x - scx) * inf_tiles + inf_screenx;
                if (scxbk == scx)
                {
                    px_ -= sxfix;
                }
                py_ = (cdata[0].position.y - scy) * inf_tiles + inf_screeny;
                if (scybk == scy)
                {
                    py_ -= syfix;
                }
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
                        pos(px_ + 24, py_ + 27);
                        grotate(3, 240, 384, 0, 20, 10);
                        gmode(2, 32, 48);
                        pos(px_ + 24, py_ + 14);
                        grotate(10, ani_, cdata[0].direction * 48, 0, 16, 24);
                    }
                    else if (chipm(0, ground_) == 3)
                    {
                        gmode(4, 32, 20, 146);
                        pos(px_ + 24, py_ + 36);
                        grotate(
                            10, ani_, cdata[0].direction * 48 + 28, 0, 24, 16);
                        gmode(2, 32, 28);
                        pos(px_ + 24, py_ + 16);
                        grotate(10, ani_, cdata[0].direction * 48, 0, 24, 24);
                    }
                    else
                    {
                        gmode(6, -1, -1, 110);
                        pos(px_ + 8, py_ + 20);
                        gcopy(3, 240, 384, 32, 16);
                        if (fishanime == 3)
                        {
                            if (fishanime(1) % 8 < 4)
                            {
                                py_ -= fishanime(1) % 4 * (fishanime(1) % 4);
                            }
                            else
                            {
                                py_ +=
                                    fishanime(1) % 4 * (fishanime(1) % 4) - 9;
                            }
                        }
                        gmode(2, 32, 48);
                        pos(px_ + 24, py_ + 8);
                        grotate(10, ani_, cdata[0].direction * 48, 0, 24, 40);
                    }
                    gmode(2);
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
            if (dx_ <= -inf_tiles || dx_ >= windoww)
            {
                continue;
            }
            if (x_ < 0 || x_ >= mdata(0))
            {
                gmode(0, inf_tiles, inf_tiles);
                p_ = tile_fog;
                pos(dx_, dy_);
                gcopy(2, p_ % 33 * inf_tiles, p_ / 33 * inf_tiles);
                continue;
            }
            ground_ = map(x_, y, 2);
            gmode(0, inf_tiles, inf_tiles);
            pos(dx_, dy_);
            bool wall_ = false;
            if (chipm(2, ground_) == 2 && y < mdata(1) - 1
                && chipm(2, map(x_, y + 1, 2)) != 2
                && map(x_, y + 1, 2) != tile_fog)
            {
                ground_ += 33;
            }
            if (chipm(2, ground_))
            {
                wall_ = true;
            }
            if (chipm(3, ground_) != 0)
            {
                gcopy(
                    2,
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
                gcopy(2, ground_ % 33 * inf_tiles, ground_ / 33 * inf_tiles);
            }
            gmode(2, inf_tiles, inf_tiles);
            if (map(x_, y, 7) != 0 && mapsync(x_, y) == msync)
            {
                p_(0) = map(x_, y, 7) % 10;
                p_(1) = map(x_, y, 7) / 10;
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
            if (efmap(1, x_, y) > 0 && mapsync(x_, y) == msync)
            {
                p_ = efmap(0, x_, y);
                if (scrturnnew_ == 1)
                {
                    --efmap(1, x_, y);
                }
                if (mefsubref(2, p_) == 1)
                {
                    gmode(4, 32, 32, efmap(1, x_, y) * 12 + 30);
                    pos(dx_ + 24, dy_ + 24);
                    grotate(
                        3,
                        mefsubref(0, p_) + efmap(3, x_, y) * 32,
                        mefsubref(1, p_),
                        0.785 * efmap(2, x_, y),
                        32,
                        32);
                }
                else
                {
                    gmode(4, 32, 32, 150);
                    pos(dx_ + 8, dy_ + 8);
                    gcopy(
                        3,
                        mefsubref(0, p_) + efmap(1, x_, y) * 32,
                        mefsubref(1, p_));
                }
                gmode(2, inf_tiles, inf_tiles);
            }
            if (map(x_, y, 6) != 0 && map(x_, y, 2) == map(x_, y, 0))
            {
                p_ = map(x_, y, 6) % 1000;
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
                    p_ = map(x_, y, 6) / 100000 % 100
                        + map(x_, y, 6) / 10000000 * 100;
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
            if (map(x_, y, 8) != 0 && mapsync(x_, y) == msync)
            {
                const int p2_ = map(x_, y, 8) - 1;
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
                    gcopy(1, chipi(0, p_), chipi(1, p_), inf_tiles, inf_tiles);
                }
            }
            if (map(x_, y, 5) != 0)
            {
                const bool mode_6_or_9 = mode == 6 || mode == 9;
                int i_;
                if (mode_6_or_9)
                {
                    i_ = 0;
                    p_ = 363;
                }
                else
                {
                    i_ = wpeek(map(x_, y, 5), 2);
                    p_ = wpeek(map(x_, y, 5), 0);
                }
                if (map(x_, y, 5) < 0 && !mode_6_or_9)
                {
                    elona_vector1<int> flooritem_;
                    p_ = -map(x_, y, 5);
                    flooritem_(0) = p_ % 1000 + 5080;
                    flooritem_(1) = p_ / 1000 % 1000 + 5080;
                    flooritem_(2) = p_ / 1000000 % 1000 + 5080;
                    int stackh_ = 0;
                    for (int i = 2; i >= 0; --i)
                    {
                        if (flooritem_(i) == 6079)
                        {
                            continue;
                        }
                        p_ = inv[flooritem_(i)].image;
                        i_ = inv[flooritem_(i)].color;
                        prepare_item_image(p_, i_, inv[flooritem_(i)].param1);
                        if (mdata(6) == 1)
                        {
                            gmode(2, chipi(2, p_), chipi(3, p_));
                            pos(dx_ + 24, dy_ + 24 - stackh_ / 2);
                            grotate(1, 0, 960, 0, 24, 24);
                        }
                        else
                        {
                            if (config::instance().objectshadow && chipi(6, p_))
                            {
                                gmode(2, chipi(2, p_), chipi(3, p_), 70);
                                if (chipi(3, p_) == inf_tiles)
                                {
                                    pos(dx_ + chipi(2, p_) / 2
                                            + chipi(6, p_) / 80 + 2,
                                        dy_ - chipi(4, p_) + 22 - stackh_);
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
                                        dy_ - chipi(4, p_) + 46 - stackh_);
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
                            pos(dx_, dy_ - chipi(4, p_) - stackh_);
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
                        stackh_ += chipi(5, p_);
                        if (p_ == 531 && chipc(3, i_) == 96)
                        {
                            stackh_ += 44;
                        }
                    }
                }
                else
                {
                    if (p_ == 528 || p_ == 531)
                    {
                        prepare_item_image(
                            p_,
                            i_,
                            inv[cell_itemoncell({x_, y}).second].param1);
                    }
                    else
                    {
                        prepare_item_image(p_, i_);
                    }
                    if (mdata(6) == 1)
                    {
                        gmode(2, chipi(2, p_), chipi(3, p_));
                        pos(dx_ + 24, dy_ + 24);
                        grotate(1, 0, 960, 0, 24, 24);
                    }
                    else
                    {
                        if (config::instance().objectshadow && chipi(6, p_))
                        {
                            gmode(2, chipi(2, p_), chipi(3, p_), 80);
                            if (chipi(3, p_) == inf_tiles)
                            {
                                pos(dx_ + chipi(2, p_) / 2 + chipi(6, p_) / 80
                                        + 2,
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
                                pos(dx_ + chipi(2, p_) / 2 + chipi(6, p_) / 4,
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
            if (map(x_, y, 1) != 0)
            {
                const int c_ = map(x_, y, 1) - 1;
                if (c_ != 0 && is_in_fov(c_)
                    && (cdata[c_].is_invisible() == 0
                        || cdata[0].can_see_invisible() == 1
                        || cdata[c_].wet != 0))
                {
                    if (cdata[c_].has_own_sprite() == 1)
                    {
                        if (mdata(6) == 1)
                        {
                            gmode(6, 32, 16, 85);
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
                        const int col_ = cdata[c_].image / 1000;
                        p_ = cdata[c_].image % 1000;
                        if (cdata[c_].is_hung_on_sand_bag())
                        {
                            gmode(2, 48, 96, 80);
                            pos(dx_ + 26 - 11, dy_ - 32 + 11);
                            func_2(1, 96, 816, -80, 48, 96);
                            gmode(2, -1, -1, 255);
                            pos(dx_, dy_ - 63);
                            gcopy(1, 96, 816, 48, 96);
                            chipc(4, p_) += 24;
                        }
                        gsel(5);
                        boxf(0, 960, chipc(2, p_), chipc(3, p_) + 960);
                        pos(0, 960);
                        set_color_mod(
                            255 - c_col(0, col_),
                            255 - c_col(1, col_),
                            255 - c_col(2, col_));
                        gcopy(
                            5,
                            chipc(0, p_),
                            chipc(1, p_),
                            chipc(2, p_),
                            chipc(3, p_));
                        set_color_mod(255, 255, 255);
                        gfini(chipc(2, p_), chipc(3, p_));
                        gfdec2(c_col(0, col_), c_col(1, col_), c_col(2, col_));
                        gsel(0);
                        if (mdata(6) == 1)
                        {
                            gmode(6, 32, 16, 85);
                            pos(dx_ + 24, dy_ + 32);
                            grotate(3, 240, 384, 0, 20, 10);
                            gmode(2, chipc(2, p_), chipc(3, p_));
                            pos(dx_ + 24, dy_ + 24 - chipc(4, p_) / 4);
                            grotate(5, 0, 960, 0, 24, chipc(3, p_) / 2);
                            if (cdata[c_].emotion_icon != 0)
                            {
                                draw_emo(
                                    c_, dx_ + 4, dy_ - chipc(4, p_) / 4 - 16);
                            }
                        }
                        else
                        {
                            if (chipm(0, ground_) == 3)
                            {
                                gmode(4, inf_tiles, inf_tiles, 100);
                                pos(dx_,
                                    dy_ + 16 - chipc(4, p_)
                                        - (chipm(0, ground_) == 3) * -16);
                                gcopy(
                                    5, 0, 976, chipc(2, p_), chipc(3, p_) - 16);
                                gmode(2, inf_tiles, inf_tiles);
                                pos(dx_,
                                    dy_ - chipc(4, p_)
                                        - (chipm(0, ground_) == 3) * -16);
                                gcopy(
                                    5, 0, 960, chipc(2, p_), chipc(3, p_) - 16);
                            }
                            else
                            {
                                gmode(6, -1, -1, 110);
                                pos(dx_ + 8, dy_ + 20);
                                gcopy(3, 240, 384, 32, 16);
                                gmode(2, inf_tiles, inf_tiles);
                                pos(dx_,
                                    dy_ - chipc(4, p_)
                                        - (chipm(0, ground_) == 3) * -16);
                                gcopy(5, 0, 960, chipc(2, p_), chipc(3, p_));
                            }
                            if (cdata[c_].furious != 0)
                            {
                                pos(dx_ + 12, dy_ - chipc(4, p_) - 12);
                                gcopy(3, 32, 608, 16, 16);
                            }
                            if (cdata[c_].emotion_icon != 0)
                            {
                                draw_emo(c_, dx_ + 4, dy_ - chipc(4, p_) - 16);
                            }
                        }
                        if (cdata[c_].is_hung_on_sand_bag())
                        {
                            pos(dx_, dy_ - 26);
                            gcopy(1, 96, 768, 48, 48);
                            chipc(4, p_) -= 24;
                        }
                    }
                    if (cdata[c_].has_been_used_stethoscope() == 1
                        || gdata(94) == c_ || debug::voldemort)
                    {
                        draw_hp_bar(c_, dx_, dy_);
                    }
                }
            }
            if (map(x_, y, 9) != 0)
            {
                p_ = map(x_, y, 9);
                if ((gdata_hour > 17 || gdata_hour < 6 || lightdata[p_]._6)
                    && mapsync(x_, y) == msync)
                {
                    light_ -= (6
                               - clamp(
                                     dist(
                                         cdata[0].position.x,
                                         cdata[0].position.y,
                                         x_,
                                         y),
                                     0,
                                     6))
                        * lightdata[p_]._4;
                    pos(dx_, dy_ - lightdata[p_]._3);
                    gmode(
                        5,
                        inf_tiles,
                        inf_tiles,
                        lightdata[p_]._2 + rnd((lightdata[p_]._5 + 1)));
                    gcopy(
                        3,
                        192 + lightdata[p_]._0 * 48
                            + rnd(lightdata[p_]._1 + 1) * inf_tiles,
                        704);
                }
            }
            if (wall_)
            {
                gmode(0);
                if (y > 0)
                {
                    p_ = map(x_, y - 1, 2);
                    if (chipm(2, p_) != 2 && p_ != tile_fog && dy_ > 20)
                    {
                        pos(dx_, dy_ - 12);
                        gcopy(
                            2,
                            ground_ % 33 * inf_tiles,
                            ground_ / 33 * inf_tiles,
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                                + std::min(dx_, 0),
                            12);
                        pos(std::max(dx_, 0), dy_ - 20);
                        gfini(
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                                + std::min(dx_, 0),
                            8);
                        gfdec2(25, 25, 25);
                    }
                }
            }
            else
            {
                if (ground_ != tile_fog && y > 0 && dy_ > 48)
                {
                    ground_ = map(x_, y - 1, 0);
                    if (chipm(2, ground_))
                    {
                        pos(std::max(dx_, 0), dy_);
                        gfini(
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                                + std::min(dx_, 0),
                            24);
                        gfdec2(16, 16, 16);
                        pos(std::max(dx_, 0), dy_ + 24);
                        gfini(
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                                + std::min(dx_, 0),
                            12);
                        gfdec2(12, 12, 12);
                    }
                }
            }
        }
    }

    if (light_ < 25)
    {
        light_ = 25;
    }

    if (mdata(6) == 1)
    {
        render_cloud();
    }

    // Work around
    light_ *= 1.3;

    if (config::instance().shadow != 0)
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
