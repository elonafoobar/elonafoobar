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



struct lightdata_t
{
    int x;
    int frame;
    int alpha_base;
    int dy;
    int brightness;
    int alpha_random;
    bool always_shines;
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



struct deco_t
{
    int _0;
    int _1;
    int _2;
};


deco_t deco[] = {
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
    gmode(6, light);

    for (const auto& pos : loop_xy<int>(inf_screenw, inf_screenh))
    {
        const auto x = pos.first;
        const auto y = pos.second;
        if (slight(x + 2, y + 2) >= 1000)
        {
            elona::pos(
                x * inf_tiles + inf_screenx, y * inf_tiles + inf_screeny);
            gcopy(3, 144, 752, inf_tiles, inf_tiles);
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
                    0 + deco[p_]._0 * inf_tiles,
                    656 + deco[p_]._1 * inf_tiles,
                    inf_tiles,
                    inf_tiles);
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
        pos(dx_, dy_);
        gcopy(3, 144 + i_ * inf_tiles, 752, inf_tiles, inf_tiles);
    }
}



void render_shadow_high(int light, int sxfix_, int syfix_)
{
    gmode(6, light);

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
        if (scrollp > 3 || mdata_map_type == mdata_t::map_type_t::dungeon)
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
        gmode(5, 7 + i * 2);
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
        if (mdata_map_type != mdata_t::map_type_t::world_map)
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



void draw_character_sprite_in_world_map(
    int texture_id,
    int x,
    int y,
    int frame,
    int direction)
{
    // Shadow
    pos(x + 24, y + 27);
    gmode(6, 85);
    gcopy_c(3, 240, 384, 32, 16, 20, 10);

    // Character sprite
    pos(x + 24, y + 14);
    gmode(2);
    gcopy_c(texture_id, frame, direction * 48, 32, 48, 16, 24);
}



void draw_character_sprite_in_water(
    int texture_id,
    int x,
    int y,
    int frame,
    int direction)
{
    // Upper body
    pos(x + 24, y + 16);
    gmode(2);
    gcopy_c(texture_id, frame, direction * 48, 32, 28, 24, 24);

    // Lower body
    pos(x + 24, y + 36);
    gmode(4, 146);
    gcopy_c(texture_id, frame, direction * 48 + 28, 32, 20, 24, 16);
}



void draw_character_sprite(
    int texture_id,
    int x,
    int y,
    int frame,
    int direction,
    int dy = 0)
{
    // Shadow
    gmode(6, 110);
    draw("character_shadow", x + 8, y + 20);

    // Character sprite
    pos(x + 24, y + dy + 8);
    gmode(2);
    gcopy_c(texture_id, frame, direction * 48, 32, 48, 24, 40);
}



bool is_night()
{
    return gdata_hour > 17 || gdata_hour < 6;
}



void draw_one_map_tile(int x, int y, int tile, int dx = 0)
{
    gmode(0);
    pos(x, y);
    gcopy(
        2,
        (tile % 33 + dx) * inf_tiles,
        tile / 33 * inf_tiles,
        inf_tiles,
        inf_tiles);
}



void draw_blood_pool_and_fragments(int x, int y)
{
    gmode(2);
    if (map(x, y, 7) != 0 && mapsync(x, y) == msync)
    {
        if (const auto fragments = map(x, y, 7) / 10)
        {
            gcopy(5, fragments * inf_tiles + 288, 1152, inf_tiles, inf_tiles);
        }
        if (const auto blood = map(x, y, 7) % 10)
        {
            gcopy(
                5, std::min(6, blood) * inf_tiles, 1152, inf_tiles, inf_tiles);
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
            gmode(4, efmap(1, x, y) * 12 + 30);
            pos(dx + 24, dy + 24);
            grotate(3, mefsubref(0, p_) + efmap(3, x, y) * 32, mefsubref(1, p_), 32, 32, 0.785 * efmap(2, x, y));
        }
        else
        {
            gmode(4, 150);
            pos(dx + 8, dy + 8);
            gcopy(
                3,
                mefsubref(0, p_) + efmap(1, x, y) * 32,
                mefsubref(1, p_),
                32,
                32);
        }
        gmode(2);
    }
}



void draw_map6(int x, int y, int dx, int dy)
{
    if (map(x, y, 6) != 0 && map(x, y, 2) == map(x, y, 0))
    {
        const auto p_ = map(x, y, 6) % 1000;
        if (p_ != 999 && p_ != 0)
        {
            pos(dx, dy - chipm(5, p_));
            gcopy(
                2,
                p_ % 33 * inf_tiles,
                p_ / 33 * inf_tiles,
                inf_tiles,
                48 + chipm(6, p_));
        }
        if (mdata_map_type == mdata_t::map_type_t::world_map)
        {
            const auto q_ =
                map(x, y, 6) / 100000 % 100 + map(x, y, 6) / 10000000 * 100;
            if (adata(16, q_) == mdata_t::map_id_t::random_dungeon)
            {
                if (adata(6, q_) == adata(10, q_))
                {
                    draw("conquered_nefia_icon", dx + 16, dy - 16);
                }
                else if (adata(6, q_) != 0)
                {
                    draw("invaded_nefia_icon", dx + 16, dy - 16);
                }
            }
        }
    }
}



void draw_map8(int x, int y, int dx, int dy, int scrturn)
{
    if (map(x, y, 8) != 0 && mapsync(x, y) == msync)
    {
        const auto p2 = map(x, y, 8) - 1;
        auto p0 = mef(1, p2) % 10000;
        const auto p1 = mef(1, p2) / 10000;
        pos(dx, dy - item_chips[p0].offset_y);
        if (item_chips[p0].animation)
        {
            p0 += (scrturn + p2) % (item_chips[p0].animation + 1)
                - ((scrturn + p2) % (item_chips[p0].animation + 1)
                   == item_chips[p0].animation)
                    * 2 * (item_chips[p0].animation != 0);
        }
        if (mef(1, p2) > 10000)
        {
            prepare_item_image(p0, p1);
            gcopy(1, 0, 960, inf_tiles, inf_tiles);
        }
        else
        {
            gcopy(1, item_chips[p0].x, item_chips[p0].y, inf_tiles, inf_tiles);
        }
    }
}



void draw_items(int x, int y, int dx, int dy, int scrturn)
{
    elona_vector1<int> p_;

    if (map(x, y, 5) != 0)
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
            i_ = wpeek(map(x, y, 5), 2);
            p_ = wpeek(map(x, y, 5), 0);
        }

        if (map(x, y, 5) < 0 && !mode_6_or_9)
        {
            // Several items are stacked.
            std::array<int, 3> items;
            p_ = -map(x, y, 5);
            items[0] = p_ % 1000 + 5080;
            items[1] = p_ / 1000 % 1000 + 5080;
            items[2] = p_ / 1000000 % 1000 + 5080;
            int stack_height{};
            for (int i = 2; i >= 0; --i)
            {
                if (items[i] == 6079)
                {
                    continue;
                }
                p_ = inv[items[i]].image;
                i_ = inv[items[i]].color;
                prepare_item_image(p_, i_, inv[items[i]].param1);
                if (mdata_map_type == mdata_t::map_type_t::world_map)
                {
                    pos(dx + 24, dy + 24 - stack_height / 2);
                    gmode(2);
                    gcopy_c(
                        1,
                        0,
                        960,
                        item_chips[p_].width,
                        item_chips[p_].height,
                        24,
                        24);
                }
                else
                {
                    if (config::instance().objectshadow
                        && item_chips[p_].shadow)
                    {
                        gmode(2, 70);
                        if (item_chips[p_].height == inf_tiles)
                        {
                            pos(dx + item_chips[p_].width / 2
                                    + item_chips[p_].shadow / 80 + 2,
                                dy - item_chips[p_].offset_y + 22
                                    - stack_height);
                            if (item_chips[p_].offset_y < 24)
                            {
                                func_2(
                                    1,
                                    0,
                                    960,
                                    item_chips[p_].shadow / 2,
                                    item_chips[p_].width,
                                    item_chips[p_].height);
                            }
                        }
                        else
                        {
                            pos(dx + item_chips[p_].width / 2
                                    + item_chips[p_].shadow / 4,
                                dy - item_chips[p_].offset_y + 46
                                    - stack_height);
                            func_2(
                                1,
                                0,
                                960,
                                item_chips[p_].shadow * 2,
                                item_chips[p_].width,
                                item_chips[p_].height);
                        }
                        gmode(2);
                    }
                    pos(dx, dy - item_chips[p_].offset_y - stack_height);
                    if (item_chips[p_].animation == 0)
                    {
                        gcopy(
                            1,
                            0,
                            960,
                            item_chips[p_].width,
                            item_chips[p_].height);
                    }
                    else
                    {
                        gcopy(
                            1,
                            item_chips[p_].x
                                + (scrturn % (item_chips[p_].animation + 1)
                                   - (scrturn % (item_chips[p_].animation + 1)
                                      == item_chips[p_].animation)
                                       * 2 * (item_chips[p_].animation != 0))
                                    * inf_tiles,
                            item_chips[p_].y,
                            item_chips[p_].width,
                            item_chips[p_].height);
                    }
                }
                stack_height += item_chips[p_].stack_height;
                if (p_ == 531 && chara_chips[i_].height == 96)
                {
                    stack_height += 44;
                }
            }
        }
        else
        {
            if (p_ == 528 || p_ == 531)
            {
                prepare_item_image(
                    p_, i_, inv[cell_itemoncell({x, y}).second].param1);
            }
            else
            {
                prepare_item_image(p_, i_);
            }
            if (mdata_map_type == mdata_t::map_type_t::world_map)
            {
                pos(dx + 24, dy + 24);
                gmode(2);
                gcopy_c(
                    1,
                    0,
                    960,
                    item_chips[p_].width,
                    item_chips[p_].height,
                    24,
                    24);
            }
            else
            {
                if (config::instance().objectshadow && item_chips[p_].shadow)
                {
                    gmode(2, 80);
                    if (item_chips[p_].height == inf_tiles)
                    {
                        pos(dx + item_chips[p_].width / 2
                                + item_chips[p_].shadow / 80 + 2,
                            dy - item_chips[p_].offset_y + 22);
                        if (item_chips[p_].offset_y < 24)
                        {
                            func_2(
                                1,
                                0,
                                960,
                                item_chips[p_].shadow / 2,
                                item_chips[p_].width,
                                item_chips[p_].height);
                        }
                    }
                    else
                    {
                        pos(dx + item_chips[p_].width / 2
                                + item_chips[p_].shadow / 4,
                            dy - item_chips[p_].offset_y + 46);
                        func_2(
                            1,
                            0,
                            960,
                            item_chips[p_].shadow * 2,
                            item_chips[p_].width,
                            item_chips[p_].height);
                    }
                    gmode(2);
                }
                pos(dx, dy - item_chips[p_].offset_y);
                if (item_chips[p_].animation == 0)
                {
                    gcopy(
                        1, 0, 960, item_chips[p_].width, item_chips[p_].height);
                }
                else
                {
                    gcopy(
                        1,
                        item_chips[p_].x
                            + (scrturn % (item_chips[p_].animation + 1)
                               - (scrturn % (item_chips[p_].animation + 1)
                                  == item_chips[p_].animation)
                                   * 2 * (item_chips[p_].animation != 0))
                                * inf_tiles,
                        item_chips[p_].y,
                        item_chips[p_].width,
                        item_chips[p_].height);
                }
            }
        }
    }
}



void draw_npc(int x, int y, int dx, int dy, int ani_, int ground_)
{
    elona_vector1<int> p_;

    if (map(x, y, 1) != 0)
    {
        const int c_ = map(x, y, 1) - 1;
        if (c_ != 0 && is_in_fov(c_)
            && (!cdata[c_].is_invisible() || cdata[0].can_see_invisible()
                || cdata[c_].wet != 0))
        {
            if (cdata[c_].has_own_sprite())
            {
                if (mdata_map_type == mdata_t::map_type_t::world_map)
                {
                    draw_character_sprite_in_world_map(
                        10 + c_, dx, dy, ani_, cdata[c_].direction);
                }
                else if (chipm(0, ground_) == 3)
                {
                    draw_character_sprite_in_water(
                        10 + c_, dx, dy, ani_, cdata[c_].direction);
                }
                else
                {
                    draw_character_sprite(
                        10 + c_, dx, dy, ani_, cdata[c_].direction);
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
            else
            {
                const int col_ = cdata[c_].image / 1000;
                p_ = cdata[c_].image % 1000;
                if (cdata[c_].is_hung_on_sand_bag())
                {
                    gmode(2, 80);
                    pos(dx + 26 - 11, dy - 32 + 11);
                    func_2(1, 96, 816, -80, 48, 96);
                    gmode(2, 255);
                    pos(dx, dy - 63);
                    gcopy(1, 96, 816, 48, 96);
                    chara_chips[p_].offset_y += 24;
                }
                gsel(5);
                boxf(0, 960, chara_chips[p_].width, chara_chips[p_].height);
                pos(0, 960);
                set_color_mod(
                    255 - c_col(0, col_),
                    255 - c_col(1, col_),
                    255 - c_col(2, col_));
                gcopy(
                    5,
                    chara_chips[p_].x,
                    chara_chips[p_].y,
                    chara_chips[p_].width,
                    chara_chips[p_].height);
                set_color_mod(255, 255, 255);
                gsel(0);
                if (mdata_map_type == mdata_t::map_type_t::world_map)
                {
                    pos(dx + 24, dy + 32);
                    gmode(6, 85);
                    gcopy_c(3, 240, 384, 32, 16, 20, 10);
                    pos(dx + 24, dy + 24 - chara_chips[p_].offset_y / 4);
                    gmode(2);
                    gcopy_c(
                        5,
                        0,
                        960,
                        chara_chips[p_].width,
                        chara_chips[p_].height,
                        24,
                        chara_chips[p_].height / 2);
                    if (cdata[c_].emotion_icon != 0)
                    {
                        draw_emo(
                            c_, dx + 4, dy - chara_chips[p_].offset_y / 4 - 16);
                    }
                }
                else
                {
                    if (chipm(0, ground_) == 3)
                    {
                        gmode(4, 100);
                        pos(dx,
                            dy + 16 - chara_chips[p_].offset_y
                                - (chipm(0, ground_) == 3) * -16);
                        gcopy(
                            5,
                            0,
                            976,
                            chara_chips[p_].width,
                            chara_chips[p_].height - 16);
                        gmode(2);
                        pos(dx,
                            dy - chara_chips[p_].offset_y
                                - (chipm(0, ground_) == 3) * -16);
                        gcopy(
                            5,
                            0,
                            960,
                            chara_chips[p_].width,
                            chara_chips[p_].height - 16);
                    }
                    else
                    {
                        gmode(6, 110);
                        draw("character_shadow", dx + 8, dy + 20);
                        gmode(2);
                        pos(dx,
                            dy - chara_chips[p_].offset_y
                                - (chipm(0, ground_) == 3) * -16);
                        gcopy(
                            5,
                            0,
                            960,
                            chara_chips[p_].width,
                            chara_chips[p_].height);
                    }
                    if (cdata[c_].furious != 0)
                    {
                        draw("furious_icon",
                            dx + 12, dy - chara_chips[p_].offset_y - 12);
                    }
                    if (cdata[c_].emotion_icon != 0)
                    {
                        draw_emo(
                            c_, dx + 4, dy - chara_chips[p_].offset_y - 16);
                    }
                }
                if (cdata[c_].is_hung_on_sand_bag())
                {
                    pos(dx, dy - 26);
                    gcopy(1, 96, 768, 48, 48);
                    chara_chips[p_].offset_y -= 24;
                }
            }
            if (cdata[c_].has_been_used_stethoscope() || gdata(94) == c_
                || debug::voldemort)
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

    int light_ = gdata(89);
    randomize(scrturn_);

    if (gdata_torch == 1)
    {
        if (mdata_map_type >= mdata_t::map_type_t::dungeon
            && mdata_map_type <= mdata_t::map_type_t::dungeon_castle)
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
    reph(2) = cdata[0].position.y + (syfix < 0);
    reph(3) = reph(2) + 1;

    if (cdata[0].position.y == mdata_map_height - 2)
    {
        if (syfix < 0)
        {
            --reph(3);
        }
    }
    if (cdata[0].position.y == mdata_map_height - 1)
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
        if (y < 0 || y >= mdata_map_height)
        {
            for (int i = scx; i < scx + inf_screenw; ++i, dx_ -= inf_tiles)
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
                gmode(5, 50 + flick_);
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

                // Spot light for PC (top 2 thirds)
                gmode(5, 50 + flick_);
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
                    if (mdata_map_type == mdata_t::map_type_t::world_map)
                    {
                        draw_character_sprite_in_world_map(
                            10, px_, py_, ani_, cdata[0].direction);
                    }
                    else if (chipm(0, ground_) == 3)
                    {
                        // TODO アイコン位置が不自然(ただし本家から)
                        draw_character_sprite_in_water(
                            10, px_, py_, ani_, cdata[0].direction);
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
                            10, px_, py_, ani_, cdata[0].direction, dy);
                        py_ += dy;
                    }
                    gmode(2);
                }
                if (cdata[0].furious != 0)
                {
                    draw("furious_icon", px_, py_ - 24);
                }
                if (cdata[0].emotion_icon != 0)
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
            if (x_ < 0 || x_ >= mdata_map_width)
            {
                draw_one_map_tile(dx_, dy_, tile_fog);
                continue;
            }

            // Map tile
            ground_ = map(x_, y, 2);
            if (chipm(2, ground_) == 2 && y < mdata_map_height - 1
                && chipm(2, map(x_, y + 1, 2)) != 2
                && map(x_, y + 1, 2) != tile_fog)
            {
                ground_ += 33;
            }
            if (chipm(3, ground_) != 0)
            {
                draw_one_map_tile(
                    dx_,
                    dy_,
                    ground_,
                    scrturn_ % (chipm(3, ground_) + 1)
                        - (scrturn_ % (chipm(3, ground_) + 1)
                           == chipm(3, ground_))
                            * 2 * (chipm(3, ground_) != 0));
            }
            else
            {
                draw_one_map_tile(dx_, dy_, ground_);
            }

            draw_blood_pool_and_fragments(x_, y);
            draw_efmap(x_, y, dx_, dy_, scrturnnew_ == 1);
            draw_map6(x_, y, dx_, dy_);
            draw_map8(x_, y, dx_, dy_, scrturn_);
            draw_items(x_, y, dx_, dy_, scrturn_);
            draw_npc(x_, y, dx_, dy_, ani_, ground_);

            // Light
            if (map(x_, y, 9) != 0)
            {
                const auto& light = lightdata[map(x_, y, 9)];
                if ((is_night() || light.always_shines)
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
                        * light.brightness;
                    pos(dx_, dy_ - light.dy);
                    gmode(5, light.alpha_base + rnd(light.alpha_random + 1));
                    gcopy(
                        3,
                        192 + light.x * 48 + rnd(light.frame + 1) * inf_tiles,
                        704,
                        inf_tiles,
                        inf_tiles);
                }
            }

            if (chipm(2, ground_))
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
                        boxf(
                            std::max(dx_, 0),
                            dy_ - 20,
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                                + std::min(dx_, 0),
                            8,
                            {0, 0, 0, 25});
                    }
                }
            }
            else if (ground_ != tile_fog && y > 0 && dy_ > 48)
            {
                ground_ = map(x_, y - 1, 0);
                if (chipm(2, ground_))
                {
                    boxf(
                        std::max(dx_, 0),
                        dy_,
                        inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                            + std::min(dx_, 0),
                        24,
                        {0, 0, 0, 16});
                    boxf(
                        std::max(dx_, 0),
                        dy_ + 24,
                        inf_tiles - std::max(dx_ + inf_tiles - windoww, 0)
                            + std::min(dx_, 0),
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

    if (mdata_map_type == mdata_t::map_type_t::world_map)
    {
        render_cloud();
    }

    // Work around
    light_ *= 1.3;

    if (config::instance().shadow)
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
