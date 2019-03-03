#include "area.hpp"
#include "character.hpp"
#include "config/config.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "macro.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "random.hpp"
#include "variables.hpp"

using namespace elona;



namespace
{



int pcc_size(int shrinked, int fullscale)
{
    assert(shrinked < fullscale);

    const auto is_fullscale =
        Config::instance().pcc_graphic_scale == "fullscale";
    return is_fullscale ? fullscale : shrinked;
}



template <typename T>
struct XYIterator
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


    XYIterator(T width, T height)
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


template <typename T>
XYIterator<T> loop_xy(T width, T height)
{
    return {width, height};
}



struct LightData
{
    int x;
    int frame;
    int alpha_base;
    int dy;
    int brightness;
    int alpha_random;
    bool always_shines;
};


LightData lightdata[] = {
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



struct Deco
{
    int _0;
    int _1;
    int _2;
};


Deco deco[] = {
    {0, 0, 0},   {0, 1, 0},   {1, 2, 0},   {0, 0, 0},   {1, 0, 0},
    {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0},
    {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0},
    {3, 1, 0},   {-1, 1, 0},  {0, 1, 0},   {1, 2, 0},   {0, 2, 0},
    {1, 0, 0},   {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 1},
    {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0},
    {-1, 31, 0}, {3, 1, 0},   {-1, 2, 0},  {0, 1, 0},   {1, 2, 0},
    {0, 2, 0},   {1, 0, 0},   {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0},
    {2, 1, 0},   {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},
    {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, 5, 0},  {0, 1, 2},
    {1, 2, 1},   {0, 2, 0},   {1, 0, 2},   {0, 0, 2},   {-1, 21, 0},
    {-1, 30, 0}, {2, 1, 1},   {-1, 20, 0}, {2, 2, 1},   {-1, 33, 0},
    {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, 3, 0},
    {0, 1, 0},   {1, 2, 0},   {0, 2, 0},   {1, 0, 0},   {0, 0, 0},
    {-1, 21, 0}, {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0}, {2, 2, 0},
    {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},
    {-1, 9, 0},  {0, 1, 0},   {1, 2, 1},   {0, 2, 0},   {1, 0, 3},
    {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0},
    {2, 2, 0},   {0, 1, 0},   {2, 0, 0},   {0, 1, 0},   {-1, 31, 0},
    {3, 1, 0},   {-1, 7, 0},  {0, 1, 2},   {1, 2, 0},   {0, 2, 0},
    {1, 0, 0},   {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 3},
    {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0},
    {-1, 31, 0}, {3, 1, 0},   {-1, -1, 0}, {0, 1, 2},   {1, 2, 1},
    {0, 2, 0},   {1, 0, 0},   {0, 0, 2},   {-1, 21, 0}, {-1, 30, 0},
    {2, 1, 0},   {-1, 20, 0}, {2, 2, 1},   {-1, 33, 0}, {2, 0, 0},
    {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, 4, 0},  {0, 1, 0},
    {1, 2, 0},   {0, 2, 0},   {1, 0, 0},   {0, 0, 0},   {-1, 21, 0},
    {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0},
    {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, 8, 0},
    {0, 1, 4},   {1, 2, 0},   {0, 2, 0},   {1, 0, 0},   {0, 0, 0},
    {-1, 21, 0}, {-1, 30, 0}, {2, 1, 1},   {-1, 20, 0}, {2, 2, 0},
    {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},
    {-1, 10, 0}, {0, 1, 0},   {1, 2, 4},   {0, 2, 0},   {1, 0, 2},
    {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0},
    {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0},
    {3, 1, 0},   {-1, -1, 0}, {0, 1, 0},   {1, 2, 8},   {0, 2, 0},
    {1, 0, 2},   {0, 0, 2},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 1},
    {-1, 20, 0}, {2, 2, 1},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0},
    {-1, 31, 0}, {3, 1, 0},   {-1, 6, 0},  {0, 1, 0},   {1, 2, 4},
    {0, 2, 4},   {1, 0, 3},   {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0},
    {2, 1, 3},   {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0}, {2, 0, 3},
    {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, -1, 0}, {0, 1, 4},
    {1, 2, 0},   {0, 2, 0},   {1, 0, 3},   {0, 0, 0},   {-1, 21, 0},
    {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0}, {2, 2, 0},   {-1, 33, 0},
    {2, 0, 3},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},   {-1, -1, 0},
    {0, 1, 0},   {1, 2, 4},   {0, 2, 0},   {1, 0, 0},   {0, 0, 0},
    {-1, 21, 0}, {-1, 30, 0}, {2, 1, 3},   {-1, 20, 0}, {2, 2, 0},
    {-1, 33, 0}, {2, 0, 3},   {-1, 32, 0}, {-1, 31, 0}, {3, 1, 0},
    {-1, -1, 0}, {0, 1, 10},  {1, 2, 8},   {0, 2, 4},   {1, 0, 7},
    {0, 0, 0},   {-1, 21, 0}, {-1, 30, 0}, {2, 1, 0},   {-1, 20, 0},
    {2, 2, 0},   {-1, 33, 0}, {2, 0, 0},   {-1, 32, 0}, {-1, 31, 0},
    {3, 1, 0},   {-1, -1, 0}, {0, 0, 0},   {0, 0, 0},   {0, 2, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
    {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},   {0, 0, 0},
};


int shadowmap[] = {
    0,
    9,
    10,
    5,
    12,
    7,
    0,
    1,
    11,
    0,
    6,
    3,
    8,
    4,
    2,
    0,
    0,
};



void render_shadow_low(int light)
{
    gmode(2, light);

    for (const auto& pos : loop_xy(inf_screenw, inf_screenh))
    {
        const auto x = pos.first;
        const auto y = pos.second;
        if (slight(x + 2, y + 2) >= 1000)
        {
            draw_indexed_region(
                "shadow",
                x * inf_tiles + inf_screenx,
                y * inf_tiles + inf_screeny,
                6,
                4,
                inf_tiles / 24,
                inf_tiles / 24);
        }
    }
}



void render_shadow(int p_, int dx_, int dy_)
{
    if (p_ <= 0)
        return;
    if (p_ < 300)
    {
        for (int i = 0; i < 1 + (deco[p_]._2 != 0); ++i)
        {
            if (deco[p_]._0 < 0 || i == 1)
            {
                int deco2;
                if (i == 0)
                {
                    deco2 = deco[p_]._1;
                }
                else
                {
                    deco2 = deco[p_]._2;
                }
                switch (deco2)
                {
                case 1:
                    draw_indexed_region("shadow", dx_, dy_, 7, 1, 1, 1);
                    break;
                case 2:
                    draw_indexed_region(
                        "shadow", dx_ + 24, dy_ + 24, 6, 0, 1, 1);
                    break;
                case 3:
                    draw_indexed_region("shadow", dx_, dy_ + 24, 7, 0, 1, 1);
                    break;
                case 4:
                    draw_indexed_region("shadow", dx_ + 24, dy_, 6, 1, 1, 1);
                    break;
                case 5:
                    draw_indexed_region(
                        "shadow", dx_ + 24, dy_ + 24, 6, 0, 1, 1);
                    draw_indexed_region("shadow", dx_, dy_, 7, 1, 1, 1);
                    break;
                case 6:
                    draw_indexed_region("shadow", dx_, dy_ + 24, 7, 0, 1, 1);
                    draw_indexed_region("shadow", dx_ + 24, dy_, 6, 1, 1, 1);
                    break;
                case 7:
                    draw_indexed_region("shadow", dx_, dy_ + 24, 7, 0, 1, 1);
                    draw_indexed_region(
                        "shadow", dx_ + 24, dy_ + 24, 6, 0, 1, 1);
                    break;
                case 8:
                    draw_indexed_region("shadow", dx_, dy_, 7, 1, 1, 1);
                    draw_indexed_region("shadow", dx_ + 24, dy_, 6, 1, 1, 1);
                    break;
                case 9:
                    draw_indexed_region("shadow", dx_, dy_, 7, 1, 1, 1);
                    draw_indexed_region("shadow", dx_, dy_ + 24, 7, 0, 1, 1);
                    break;
                case 10:
                    draw_indexed_region("shadow", dx_ + 24, dy_, 6, 1, 1, 1);
                    draw_indexed_region(
                        "shadow", dx_ + 24, dy_ + 24, 6, 0, 1, 1);
                    break;
                case 20:
                    draw_indexed_region("shadow", dx_, dy_, 0, 2, 1, 2);
                    draw_indexed_region("shadow", dx_ + 24, dy_, 5, 2, 1, 2);
                    break;
                case 21:
                    draw_indexed_region("shadow", dx_, dy_, 2, 0, 2, 1);
                    draw_indexed_region("shadow", dx_, dy_ + 24, 2, 5, 2, 1);
                    break;
                case 30:
                    draw_indexed_region("shadow", dx_, dy_, 0, 0, 2, 1);
                    draw_indexed_region("shadow", dx_, dy_ + 24, 0, 5, 2, 1);
                    break;
                case 31:
                    draw_indexed_region("shadow", dx_, dy_, 4, 0, 2, 1);
                    draw_indexed_region("shadow", dx_, dy_ + 24, 4, 5, 2, 1);
                    break;
                case 32:
                    draw_indexed_region("shadow", dx_, dy_, 0, 0, 1, 2);
                    draw_indexed_region("shadow", dx_ + 24, dy_, 5, 0, 1, 2);
                    break;
                case 33:
                    draw_indexed_region("shadow", dx_, dy_, 0, 4, 1, 2);
                    draw_indexed_region("shadow", dx_ + 24, dy_, 5, 4, 1, 2);
                    break;
                default: break;
                }
            }
            else
            {
                draw_indexed("shadow_deco", dx_, dy_, deco[p_]._0, deco[p_]._1);
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
            i_ = shadowmap[p2_];
        }
        draw_indexed("shadow_edges", dx_, dy_, i_);
    }
}



void render_shadow_high(int light, int sxfix_, int syfix_)
{
    gmode(2, light);

    if (scrollanime == 0)
    {
        for (const auto& pos : loop_xy(inf_screenw, inf_screenh))
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
        if (scrollp > 3 || map_data.type == mdata_t::MapType::dungeon)
        {
            f_ = 1;
        }
        for (const auto& pos : loop_xy(inf_screenw + 2, inf_screenh + 2))
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



struct Cloud
{
    Cloud(int x0, int y0, int x, int y, int width, int height)
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

std::vector<Cloud> clouds;


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
        gmode(5, 7 + i * 2);
        int x = (clouds[i].x0 - cdata.player().position.x * inf_tiles + sxfix) *
                100 / (40 + i * 5) +
            scrturn * 100 / (50 + i * 20);
        int y = (clouds[i].y0 - cdata.player().position.y * inf_tiles + syfix) *
            100 / (40 + i * 5);
        x = x % (windoww + clouds[i].width) - clouds[i].width;
        y = y % (inf_very + clouds[i].height) - clouds[i].height;
        int height = clouds[i].height;
        if (y + height > inf_very)
        {
            height = inf_very - y;
        }
        if (y < inf_very)
        {
            gcopy(2, clouds[i].x, clouds[i].y, clouds[i].width, height, x, y);
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
        if (map_data.type != mdata_t::MapType::world_map)
        {
            draw_bar("hp_bar_ally", x + 9, y + 32, ratio, 3, ratio);
        }
    }
    else
    {
        draw_bar("hp_bar_other", x + 9, y + 32, ratio, 3, ratio);
    }
}



void draw_character_sprite_in_world_map(
    int c_,
    int x,
    int y,
    int frame,
    int direction)
{
    int texture_id = c_ + 20;

    // Shadow
    gmode(2, 85);
    draw_centered("character_shadow", x + 24, y + 27, 20, 10);

    // Character sprite
    gmode(2);
    gcopy_c(texture_id, frame, direction * 48, 32, 48, x + 24, y + 14, 16, 24);
}



void draw_character_sprite_in_water(
    int c_,
    int x,
    int y,
    int frame,
    int direction)
{
    int texture_id = c_ + 20;

    // Upper body
    gmode(2);
    gcopy_c(
        texture_id,
        frame,
        direction * 48,
        32,
        28,
        x + 24,
        y + 16,
        pcc_size(24, 32),
        pcc_size(24, 28));

    // Lower body
    gmode(2, 146);
    gcopy_c(
        texture_id,
        frame,
        direction * 48 + 28,
        32,
        20,
        x + 24,
        y + pcc_size(36, 40),
        pcc_size(24, 32),
        pcc_size(16, 20));
}



void draw_character_sprite(
    int c_,
    int x,
    int y,
    int frame,
    int direction,
    int dy = 0)
{
    int texture_id = c_ + 20;

    // Shadow
    gmode(2, 110);
    draw("character_shadow", x + 8, y + 20);

    // Character sprite
    gmode(2);
    gcopy_c(
        texture_id,
        frame,
        direction * 48,
        32,
        48,
        x + 24,
        y + dy + 8,
        pcc_size(24, 32),
        pcc_size(40, 48));
}



optional_ref<Extent> prepare_chara_chip(int c_, int dx, int dy)
{
    const int col_ = cdata[c_].image / 1000;
    const int p_ = cdata[c_].image % 1000;
    auto rect = draw_get_rect_chara(p_);
    if (cdata[c_].is_hung_on_sand_bag())
    {
        gmode(2, 80);
        func_2(1, 96, 816, -80, 48, 96);
        gmode(2);
        gcopy(1, 96, 816, 48, 96, dx, dy - 63);
        chara_chips[p_].offset_y += 24;
    }
    gsel(rect->buffer);
    boxf(0, 960, rect->width, rect->height);
    set_color_mod(
        255 - c_col(0, col_), 255 - c_col(1, col_), 255 - c_col(2, col_));
    gcopy(rect->buffer, rect->x, rect->y, rect->width, rect->height, 0, 960);
    set_color_mod(255, 255, 255);
    gsel(0);

    return rect;
}


void draw_chara_chip_sprite_in_world_map(
    int texture_id,
    int chip_id,
    int x,
    int y,
    int width,
    int height)
{
    gmode(2, 85);
    draw_centered("character_shadow", x + 24, y + 32, 20, 10);
    gmode(2);
    gcopy_c(
        texture_id,
        0,
        960,
        width,
        height,
        x + 24,
        y + 24 - chara_chips[chip_id].offset_y / 4,
        24,
        height / 2);
}


void draw_chara_chip_sprite_in_water(
    int texture_id,
    int chip_id,
    int x,
    int y,
    int width,
    int height,
    int ground_)
{
    int dy = (chipm(0, ground_) == 3) * -16;
    gmode(2, 100);
    gcopy(
        texture_id,
        0,
        976,
        width,
        height - 16,
        x,
        y + 16 - chara_chips[chip_id].offset_y - dy);
    gmode(2);
    gcopy(
        texture_id,
        0,
        960,
        width,
        height - 16,
        x,
        y - chara_chips[chip_id].offset_y - dy);
}

void draw_chara_chip_sprite(
    int texture_id,
    int chip_id,
    int x,
    int y,
    int width,
    int height,
    int ground_)
{
    int dy = (chipm(0, ground_) == 3) * -16;
    gmode(2, 110);
    draw("character_shadow", x + 8, y + 20);
    gmode(2);
    gcopy(
        texture_id,
        0,
        960,
        width,
        height,
        x,
        y - chara_chips[chip_id].offset_y - dy);
}

void draw_npc_own_sprite(int c_, int dx, int dy, int ani_, int ground_)
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        draw_character_sprite_in_world_map(
            c_, dx, dy, ani_, cdata[c_].direction);
    }
    else if (chipm(0, ground_) == 3)
    {
        draw_character_sprite_in_water(c_, dx, dy, ani_, cdata[c_].direction);
    }
    else
    {
        draw_character_sprite(c_, dx, dy, ani_, cdata[c_].direction);
    }
    gmode(2);
    if (cdata[c_].furious != 0)
    {
        draw("furious_icon", dx + 12, dy - 28);
    }
    if (cdata[c_].emotion_icon != 0)
    {
        draw_emo(c_, dx + 4, dy - 32);
    }
}

void draw_npc_chara_chip(int c_, int dx, int dy, int ground_)
{
    int p_ = cdata[c_].image % 1000;
    auto rect = prepare_chara_chip(c_, dx, dy);

    if (map_data.type == mdata_t::MapType::world_map)
    {
        draw_chara_chip_sprite_in_world_map(
            rect->buffer, p_, dx, dy, rect->width, rect->height);

        if (cdata[c_].emotion_icon != 0)
        {
            draw_emo(c_, x + 4, y - chara_chips[p_].offset_y / 4 - 16);
        }
    }
    else
    {
        if (chipm(0, ground_) == 3)
        {
            draw_chara_chip_sprite_in_water(
                rect->buffer, p_, dx, dy, rect->width, rect->height, ground_);
        }
        else
        {
            draw_chara_chip_sprite(
                rect->buffer, p_, dx, dy, rect->width, rect->height, ground_);
        }

        if (cdata[c_].furious != 0)
        {
            draw("furious_icon", dx + 12, dy - chara_chips[p_].offset_y - 12);
        }
        if (cdata[c_].emotion_icon != 0)
        {
            draw_emo(c_, dx + 4, dy - chara_chips[p_].offset_y - 16);
        }
    }
    if (cdata[c_].is_hung_on_sand_bag())
    {
        gcopy(1, 96, 768, 48, 48, dx, dy - 26);
        chara_chips[p_].offset_y -= 24;
    }
}


bool you_can_see(const Character& chara)
{
    return is_in_fov(chara) &&
        (!chara.is_invisible() || cdata.player().can_see_invisible() ||
         chara.wet != 0);
}

bool hp_bar_visible(const Character& chara)
{
    return chara.has_been_used_stethoscope() ||
        game_data.chara_last_attacked_by_player == chara.index ||
        debug::voldemort;
}

bool is_night()
{
    return game_data.date.hour > 17 || game_data.date.hour < 6;
}



void draw_one_map_tile(int x, int y, int tile, int dx = 0)
{
    gmode(0);
    gcopy(
        2,
        (tile % 33 + dx) * inf_tiles,
        tile / 33 * inf_tiles,
        inf_tiles,
        inf_tiles,
        x,
        y);
}



void draw_blood_pool_and_fragments(int x, int y, int dx, int dy)
{
    gmode(2);
    if (cell_data.at(x, y).blood_and_fragments != 0 && mapsync(x, y) == msync)
    {
        if (const auto fragments = cell_data.at(x, y).blood_and_fragments / 10)
        {
            gcopy(
                5,
                fragments * inf_tiles + 288,
                1152,
                inf_tiles,
                inf_tiles,
                dx,
                dy);
        }
        if (const auto blood = cell_data.at(x, y).blood_and_fragments % 10)
        {
            gcopy(
                5,
                std::min(6, blood) * inf_tiles,
                1152,
                inf_tiles,
                inf_tiles,
                dx,
                dy);
        }
    }
}



void draw_efmap(int x, int y, int dx, int dy, bool update_frame)
{
    if (efmap(1, x, y) > 0 && mapsync(x, y) == msync)
    {
        const auto p_ = efmap(0, x, y);
        if (update_frame)
        {
            --efmap(1, x, y);
        }
        if (mefsubref(2, p_) == 1)
        {
            gmode(2, efmap(1, x, y) * 12 + 30);
            draw_region_rotated(
                "mef_subref",
                dx + 24,
                dy + 24,
                (mefsubref(0, p_) - 144) + efmap(3, x, y) * 32,
                (mefsubref(1, p_) - 624),
                32,
                32,
                0.785 * efmap(2, x, y));
        }
        else
        {
            gmode(2, 150);
            draw_region(
                "mef_subref",
                dx + 8,
                dy + 8,
                (mefsubref(0, p_) - 144) + efmap(1, x, y) * 32,
                (mefsubref(1, p_) - 624),
                32,
                32);
        }
        gmode(2);
    }
}



void draw_nefia_icons(int x, int y, int dx, int dy)
{
    if (cell_data.at(x, y).feats != 0 &&
        cell_data.at(x, y).chip_id_memory == cell_data.at(x, y).chip_id_actual)
    {
        const auto p_ = cell_data.at(x, y).feats % 1000;
        if (p_ != 999 && p_ != 0)
        {
            gcopy(
                2,
                p_ % 33 * inf_tiles,
                p_ / 33 * inf_tiles,
                inf_tiles,
                48 + chipm(6, p_),
                dx,
                dy - chipm(5, p_));
        }
        if (map_data.type == mdata_t::MapType::world_map)
        {
            const auto q_ = cell_data.at(x, y).feats / 100000 % 100 +
                cell_data.at(x, y).feats / 10000000 * 100;
            if (area_data[q_].id == mdata_t::MapId::random_dungeon)
            {
                if (area_data[q_].visited_deepest_level ==
                    area_data[q_].deepest_level)
                {
                    draw("conquered_nefia_icon", dx + 16, dy - 16);
                }
                else if (area_data[q_].visited_deepest_level != 0)
                {
                    draw("invaded_nefia_icon", dx + 16, dy - 16);
                }
            }
        }
    }
}



void draw_mefs(int x, int y, int dx, int dy, int scrturn_)
{
    if (cell_data.at(x, y).mef_index_plus_one != 0 && mapsync(x, y) == msync)
    {
        const auto mef_id = cell_data.at(x, y).mef_index_plus_one - 1;
        auto item_chip_id = mef(1, mef_id) % 10000;
        int anim_frame = 0;
        const auto item_chip_color = mef(1, mef_id) / 10000;
        if (item_chips[item_chip_id].animation > 0)
        {
            anim_frame =
                (scrturn_ + mef_id) % item_chips[item_chip_id].animation;
        }
        if (mef(1, mef_id) > 10000)
        {
            // Colorized
            auto rect = prepare_item_image(item_chip_id, item_chip_color);
            gcopy(
                1,
                anim_frame * rect->frame_width,
                960,
                inf_tiles,
                rect->height,
                dx,
                dy - item_chips[item_chip_id].offset_y);
        }
        else
        {
            auto rect = draw_get_rect_item(item_chip_id);
            gcopy(
                rect->buffer,
                rect->x + anim_frame * rect->frame_width,
                rect->y,
                rect->frame_width,
                rect->height,
                dx,
                dy - item_chips[item_chip_id].offset_y);
        }
    }
}



void draw_item_chip_in_world_map(int x, int y, const Extent& rect)
{
    gmode(2);
    gcopy_c(
        1,
        0,
        960,
        rect.frame_width,
        rect.height,
        x,
        y,
        inf_tiles / 2,
        inf_tiles / 2);
}



void draw_item_chip_shadow(int x, int y, const Extent& rect, int p_, int alpha)
{
    (void)x;
    (void)y;

    gmode(2, alpha);
    if (rect.height == inf_tiles)
    {
        if (item_chips[p_].offset_y < 24)
        {
            func_2(
                1,
                0,
                960,
                item_chips[p_].shadow / 2,
                rect.frame_width,
                rect.height);
        }
    }
    else
    {
        func_2(
            1,
            0,
            960,
            item_chips[p_].shadow * 2,
            rect.frame_width,
            rect.height);
    }
    gmode(2);
}


void draw_item_chip_on_ground(
    int x,
    int y,
    const Extent& rect,
    int p_,
    int scrturn_)
{
    if (item_chips[p_].animation == 0)
    {
        gcopy(1, 0, 960, rect.frame_width, rect.height, x, y);
    }
    else
    {
        // Skip colorizing the item chip and copy directly from the
        // atlas buffer.
        gcopy(
            rect.buffer,
            rect.x + (scrturn_ % item_chips[p_].animation) * rect.frame_width,
            rect.y,
            rect.frame_width,
            rect.height,
            x,
            y);
    }
}



void draw_items(int x, int y, int dx, int dy, int scrturn_)
{
    elona_vector1<int> p_;

    if (cell_data.at(x, y).item_appearances_memory != 0)
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
            i_ = wpeek(cell_data.at(x, y).item_appearances_memory, 2);
            p_ = wpeek(cell_data.at(x, y).item_appearances_memory, 0);
        }

        if (cell_data.at(x, y).item_appearances_memory < 0 && !mode_6_or_9)
        {
            // Several items are stacked.
            std::array<int, 3> items;
            p_ = -cell_data.at(x, y).item_appearances_memory;
            items[0] = p_ % 1000 + 5080;
            items[1] = p_ / 1000 % 1000 + 5080;
            items[2] = p_ / 1000000 % 1000 + 5080;
            int stack_height{};
            for (int i = 2; i >= 0; --i)
            {
                if (items[i] == 6079) // 5080 + 999
                {
                    continue;
                }
                p_ = inv[items[i]].image;
                i_ = inv[items[i]].color;
                auto rect = prepare_item_image(p_, i_, inv[items[i]].param1);
                if (map_data.type == mdata_t::MapType::world_map)
                {
                    draw_item_chip_in_world_map(
                        dx + (inf_tiles / 2),
                        dy + (inf_tiles / 2) - (stack_height / 2),
                        **rect);
                }
                else
                {
                    if (Config::instance().object_shadow &&
                        item_chips[p_].shadow)
                    {
                        draw_item_chip_shadow(
                            dx, dy - stack_height, **rect, p_, 70);
                    }
                    draw_item_chip_on_ground(
                        dx,
                        dy - item_chips[p_].offset_y - stack_height,
                        **rect,
                        p_,
                        scrturn_);
                }
                stack_height += item_chips[p_].stack_height;
                if (p_ == 531 && draw_get_rect_chara(i_)->height == 96)
                {
                    stack_height += 44;
                }
            }
        }
        else
        {
            optional_ref<Extent> rect;
            if (p_ == 528 || p_ == 531)
            {
                rect = prepare_item_image(
                    p_, i_, inv[cell_itemoncell({x, y}).second].param1);
            }
            else
            {
                rect = prepare_item_image(p_, i_);
            }
            if (map_data.type == mdata_t::MapType::world_map)
            {
                draw_item_chip_in_world_map(
                    dx + (inf_tiles / 2), dy + (inf_tiles / 2), **rect);
            }
            else
            {
                if (Config::instance().object_shadow && item_chips[p_].shadow)
                {
                    draw_item_chip_shadow(dx, dy, **rect, p_, 80);
                }
                draw_item_chip_on_ground(
                    dx, dy - item_chips[p_].offset_y, **rect, p_, scrturn_);
            }
        }
    }
}



void draw_npc(int x, int y, int dx, int dy, int ani_, int ground_)
{
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        const int c_ = cell_data.at(x, y).chara_index_plus_one - 1;
        if (c_ != 0 && you_can_see(cdata[c_]))
        {
            if (cdata[c_].has_own_sprite())
            {
                draw_npc_own_sprite(c_, dx, dy, ani_, ground_);
            }
            else
            {
                draw_npc_chara_chip(c_, dx, dy, ground_);
            }

            if (hp_bar_visible(cdata[c_]))
            {
                draw_hp_bar(c_, dx, dy);
            }
        }
    }
}



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

    int light_ = game_data.light;
    randomize(scrturn_);

    if (game_data.torch == 1)
    {
        if (mdata_t::is_nefia(map_data.type))
        {
            light_ -= 50;
        }
    }
    int flick_ = 0;
    if (is_night())
    {
        flick_ = rnd(10);
    }
    else
    {
        flick_ = -15;
    }

    repw(2) = repw(1);
    reph(2) = cdata.player().position.y + (syfix < 0);
    reph(3) = reph(2) + 1;

    if (cdata.player().position.y == map_data.height - 2)
    {
        if (syfix < 0)
        {
            --reph(3);
        }
    }
    if (cdata.player().position.y == map_data.height - 1)
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

        // Out of screen
        if (dy_ <= -inf_tiles || dy_ >= windowh - inf_verh)
        {
            continue;
        }

        // Out of map
        if (y < 0 || y >= map_data.height)
        {
            for (int i = 0; i < repw; ++i, dx_ -= inf_tiles)
            {
                draw_one_map_tile(dx_, dy_, tile_fog);
            }
            continue;
        }

        for (int cnt = 0; cnt < repw; ++cnt, dx_ -= inf_tiles)
        {
            const int x_ = repw(1) + repw - 1 - cnt;
            int px_ = 0;
            int py_ = 0;

            // Spot light for PC (bottom a third)
            if (reph(3) == y && x_ == repw(2) &&
                cdata.player().state() == Character::State::alive)
            {
                px_ = (cdata.player().position.x - scx) * inf_tiles +
                    inf_screenx - 48;
                if (scxbk == scx)
                {
                    px_ -= sxfix;
                }
                py_ = (cdata.player().position.y + 1 - scy) * inf_tiles +
                    inf_screeny;
                if (scybk == scy)
                {
                    py_ -= syfix;
                }
                gmode(5, 50 + flick_);
                draw_region("spot_light", px_, py_, 0, 96, 144, 48);
            }

            if (reph(2) == y && x_ == repw(2) &&
                cdata.player().state() == Character::State::alive)
            {
                ground_ = cell_data
                              .at(cdata.player().position.x,
                                  cdata.player().position.y)
                              .chip_id_actual;
                px_ =
                    (cdata.player().position.x - scx) * inf_tiles + inf_screenx;
                if (scxbk == scx)
                {
                    px_ -= sxfix;
                }
                py_ =
                    (cdata.player().position.y - scy) * inf_tiles + inf_screeny;
                if (scybk == scy)
                {
                    py_ -= syfix;
                }

                // Spot light for PC (top 2 thirds)
                gmode(5, 50 + flick_);
                draw_region("spot_light", px_ - 48, py_ - 48, 0, 0, 144, 96);

                if (py_ < windowh - inf_verh - 24)
                {
                    if (cdata.player().continuous_action.type ==
                        ContinuousAction::Type::fish)
                    {
                        ani_ = 0;
                    }
                    else
                    {
                        ani_ = cdata.player().turn % 4 * 32;
                    }
                    if (map_data.type == mdata_t::MapType::world_map)
                    {
                        draw_character_sprite_in_world_map(
                            0, px_, py_, ani_, cdata.player().direction);
                    }
                    else if (chipm(0, ground_) == 3)
                    {
                        // TODO アイコン位置が不自然(ただし本家から)
                        draw_character_sprite_in_water(
                            0, px_, py_, ani_, cdata.player().direction);
                    }
                    else
                    {
                        int dy{};
                        if (fishanime == 3)
                        {
                            if (fishanime(1) % 8 < 4)
                            {
                                dy = -(fishanime(1) % 4 * (fishanime(1) % 4));
                            }
                            else
                            {
                                dy = fishanime(1) % 4 * (fishanime(1) % 4) - 9;
                            }
                        }
                        draw_character_sprite(
                            0, px_, py_, ani_, cdata.player().direction, dy);
                        py_ += dy;
                    }
                    gmode(2);
                }
                if (cdata.player().furious != 0)
                {
                    draw("furious_icon", px_, py_ - 24);
                }
                if (cdata.player().emotion_icon != 0)
                {
                    draw_emo(0, px_ + 4, py_ - 32);
                }
            }

            // Out of screen
            if (dx_ <= -inf_tiles || dx_ >= windoww)
            {
                continue;
            }

            // Out of map
            if (x_ < 0 || x_ >= map_data.width)
            {
                draw_one_map_tile(dx_, dy_, tile_fog);
                continue;
            }

            // Map tile
            ground_ = cell_data.at(x_, y).chip_id_memory;
            if (chipm(2, ground_) == 2 && y < map_data.height - 1 &&
                chipm(2, cell_data.at(x_, y + 1).chip_id_memory) != 2 &&
                cell_data.at(x_, y + 1).chip_id_memory != tile_fog)
            {
                ground_ += 33;
            }
            if (chipm(3, ground_) != 0)
            {
                draw_one_map_tile(
                    dx_,
                    dy_,
                    ground_,
                    scrturn_ % (chipm(3, ground_) + 1) -
                        (scrturn_ % (chipm(3, ground_) + 1) ==
                         chipm(3, ground_)) *
                            2 * (chipm(3, ground_) != 0));
            }
            else
            {
                draw_one_map_tile(dx_, dy_, ground_);
            }

            draw_blood_pool_and_fragments(x_, y, dx_, dy_);
            draw_efmap(x_, y, dx_, dy_, scrturnnew_ == 1);
            draw_nefia_icons(x_, y, dx_, dy_);
            draw_mefs(x_, y, dx_, dy_, scrturn_);
            draw_items(x_, y, dx_, dy_, scrturn_);
            draw_npc(x_, y, dx_, dy_, ani_, ground_);

            // Light
            if (cell_data.at(x_, y).light != 0)
            {
                const auto& light = lightdata[cell_data.at(x_, y).light];
                if ((is_night() || light.always_shines) &&
                    mapsync(x_, y) == msync)
                {
                    light_ -= (6 -
                               clamp(
                                   dist(
                                       cdata.player().position.x,
                                       cdata.player().position.y,
                                       x_,
                                       y),
                                   0,
                                   6)) *
                        light.brightness;
                    gmode(5, light.alpha_base + rnd(light.alpha_random + 1));
                    draw_indexed(
                        "light",
                        dx_,
                        dy_ - light.dy,
                        light.x + rnd(light.frame + 1));
                }
            }

            if (chipm(2, ground_))
            {
                gmode(0);
                if (y > 0)
                {
                    p_ = cell_data.at(x_, y - 1).chip_id_memory;
                    if (chipm(2, p_) != 2 && p_ != tile_fog && dy_ > 20)
                    {
                        gcopy(
                            2,
                            ground_ % 33 * inf_tiles,
                            ground_ / 33 * inf_tiles,
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0) +
                                std::min(dx_, 0),
                            12,
                            dx_,
                            dy_ - 12);
                        boxf(
                            std::max(dx_, 0),
                            dy_ - 20,
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0) +
                                std::min(dx_, 0),
                            8,
                            {0, 0, 0, 25});
                    }
                }
            }
            else if (ground_ != tile_fog && y > 0 && dy_ > 48)
            {
                ground_ = cell_data.at(x_, y - 1).chip_id_actual;
                if (chipm(2, ground_))
                {
                    boxf(
                        std::max(dx_, 0),
                        dy_,
                        inf_tiles - std::max(dx_ + inf_tiles - windoww, 0) +
                            std::min(dx_, 0),
                        24,
                        {0, 0, 0, 16});
                    boxf(
                        std::max(dx_, 0),
                        dy_ + 24,
                        inf_tiles - std::max(dx_ + inf_tiles - windoww, 0) +
                            std::min(dx_, 0),
                        12,
                        {0, 0, 0, 12});
                }
            }
        }
    }

    if (light_ < 25)
    {
        light_ = 25;
    }

    if (map_data.type == mdata_t::MapType::world_map)
    {
        render_cloud();
    }

    // Work around
    light_ *= 1.3;

    if (Config::instance().high_quality_shadow)
    {
        render_shadow_high(light_, sxfix_, syfix_);
    }
    else
    {
        render_shadow_low(light_);
    }

    gmode(2);
    randomize();
}



} // namespace elona
