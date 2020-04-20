#include "area.hpp"
#include "character.hpp"
#include "config.hpp"
#include "data/types/type_asset.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "fov.hpp"
#include "item.hpp"
#include "map.hpp"
#include "map_cell.hpp"
#include "pic_loader/pic_loader.hpp"
#include "pic_loader/tinted_buffers.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

int pcc_size(int shrinked, int fullscale)
{
    assert(shrinked < fullscale);

    const auto is_fullscale = g_config.pcc_graphic_scale() == "fullscale";
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


constexpr Deco shadow_deco[] = {
    // clang-format off
    { 0,  0,  0}, // 0
    { 0,  1,  0}, // 1
    { 1,  2,  0}, // 2
    { 0,  0,  0}, // 3
    { 1,  0,  0}, // 4
    { 0,  0,  0}, // 5
    {-1, 21,  0}, // 6
    {-1, 30,  0}, // 7
    { 2,  1,  0}, // 8
    {-1, 20,  0}, // 9
    { 2,  2,  0}, // 10
    {-1, 33,  0}, // 11
    { 2,  0,  0}, // 12
    {-1, 32,  0}, // 13
    {-1, 31,  0}, // 14
    { 3,  1,  0}, // 15
    {-1,  1,  0}, // 16
    { 0,  1,  0}, // 17
    { 1,  2,  0}, // 18
    { 0,  2,  0}, // 19
    { 1,  0,  0}, // 20
    { 0,  0,  0}, // 21
    {-1, 21,  0}, // 22
    {-1, 30,  0}, // 23
    { 2,  1,  1}, // 24
    {-1, 20,  0}, // 25
    { 2,  2,  0}, // 26
    {-1, 33,  0}, // 27
    { 2,  0,  0}, // 28
    {-1, 32,  0}, // 29
    {-1, 31,  0}, // 30
    { 3,  1,  0}, // 31
    {-1,  2,  0}, // 32
    { 0,  1,  0}, // 33
    { 1,  2,  0}, // 34
    { 0,  2,  0}, // 35
    { 1,  0,  0}, // 36
    { 0,  0,  0}, // 37
    {-1, 21,  0}, // 38
    {-1, 30,  0}, // 39
    { 2,  1,  0}, // 40
    {-1, 20,  0}, // 41
    { 2,  2,  0}, // 42
    {-1, 33,  0}, // 43
    { 2,  0,  0}, // 44
    {-1, 32,  0}, // 45
    {-1, 31,  0}, // 46
    { 3,  1,  0}, // 47
    {-1,  5,  0}, // 48
    { 0,  1,  2}, // 49
    { 1,  2,  1}, // 50
    { 0,  2,  0}, // 51
    { 1,  0,  2}, // 52
    { 0,  0,  2}, // 53
    {-1, 21,  0}, // 54
    {-1, 30,  0}, // 55
    { 2,  1,  1}, // 56
    {-1, 20,  0}, // 57
    { 2,  2,  1}, // 58
    {-1, 33,  0}, // 59
    { 2,  0,  0}, // 60
    {-1, 32,  0}, // 61
    {-1, 31,  0}, // 62
    { 3,  1,  0}, // 63
    {-1,  3,  0}, // 64
    { 0,  1,  0}, // 65
    { 1,  2,  0}, // 66
    { 0,  2,  0}, // 67
    { 1,  0,  0}, // 68
    { 0,  0,  0}, // 69
    {-1, 21,  0}, // 70
    {-1, 30,  0}, // 71
    { 2,  1,  0}, // 72
    {-1, 20,  0}, // 73
    { 2,  2,  0}, // 74
    {-1, 33,  0}, // 75
    { 2,  0,  0}, // 76
    {-1, 32,  0}, // 77
    {-1, 31,  0}, // 78
    { 3,  1,  0}, // 79
    {-1,  9,  0}, // 80
    { 0,  1,  0}, // 81
    { 1,  2,  1}, // 82
    { 0,  2,  0}, // 83
    { 1,  0,  3}, // 84
    { 0,  0,  0}, // 85
    {-1, 21,  0}, // 86
    {-1, 30,  0}, // 87
    { 2,  1,  0}, // 88
    {-1, 20,  0}, // 89
    { 2,  2,  0}, // 90
    { 0,  1,  0}, // 91
    { 2,  0,  0}, // 92
    { 0,  1,  0}, // 93
    {-1, 31,  0}, // 94
    { 3,  1,  0}, // 95
    {-1,  7,  0}, // 96
    { 0,  1,  2}, // 97
    { 1,  2,  0}, // 98
    { 0,  2,  0}, // 99
    { 1,  0,  0}, // 100
    { 0,  0,  0}, // 101
    {-1, 21,  0}, // 102
    {-1, 30,  0}, // 103
    { 2,  1,  3}, // 104
    {-1, 20,  0}, // 105
    { 2,  2,  0}, // 106
    {-1, 33,  0}, // 107
    { 2,  0,  0}, // 108
    {-1, 32,  0}, // 109
    {-1, 31,  0}, // 110
    { 3,  1,  0}, // 111
    {-1, -1,  37}, // 112
    { 0,  1,  2}, // 113
    { 1,  2,  1}, // 114
    { 0,  2,  0}, // 115
    { 1,  0,  0}, // 116
    { 0,  0,  2}, // 117
    {-1, 21,  0}, // 118
    {-1, 30,  0}, // 119
    { 2,  1,  0}, // 120
    {-1, 20,  0}, // 121
    { 2,  2,  1}, // 122
    {-1, 33,  0}, // 123
    { 2,  0,  0}, // 124
    {-1, 32,  0}, // 125
    {-1, 31,  0}, // 126
    { 3,  1,  0}, // 127
    {-1,  4,  0}, // 128
    { 0,  1,  0}, // 129
    { 1,  2,  0}, // 130
    { 0,  2,  0}, // 131
    { 1,  0,  0}, // 132
    { 0,  0,  0}, // 133
    {-1, 21,  0}, // 134
    {-1, 30,  0}, // 135
    { 2,  1,  0}, // 136
    {-1, 20,  0}, // 137
    { 2,  2,  0}, // 138
    {-1, 33,  0}, // 139
    { 2,  0,  0}, // 140
    {-1, 32,  0}, // 141
    {-1, 31,  0}, // 142
    { 3,  1,  0}, // 143
    {-1,  8,  0}, // 144
    { 0,  1,  4}, // 145
    { 1,  2,  0}, // 146
    { 0,  2,  0}, // 147
    { 1,  0,  0}, // 148
    { 0,  0,  0}, // 149
    {-1, 21,  0}, // 150
    {-1, 30,  0}, // 151
    { 2,  1,  1}, // 152
    {-1, 20,  0}, // 153
    { 2,  2,  0}, // 154
    {-1, 33,  0}, // 155
    { 2,  0,  0}, // 156
    {-1, 32,  0}, // 157
    {-1, 31,  0}, // 158
    { 3,  1,  0}, // 159
    {-1, 10,  0}, // 160
    { 0,  1,  0}, // 161
    { 1,  2,  4}, // 162
    { 0,  2,  0}, // 163
    { 1,  0,  2}, // 164
    { 0,  0,  0}, // 165
    {-1, 21,  0}, // 166
    {-1, 30,  0}, // 167
    { 2,  1,  0}, // 168
    {-1, 20,  0}, // 169
    { 2,  2,  0}, // 170
    {-1, 33,  0}, // 171
    { 2,  0,  0}, // 172
    {-1, 32,  0}, // 173
    {-1, 31,  0}, // 174
    { 3,  1,  0}, // 175
    {-1, -1,  36}, // 176
    { 0,  1,  0}, // 177
    { 1,  2,  8}, // 178
    { 0,  2,  0}, // 179
    { 1,  0,  2}, // 180
    { 0,  0,  2}, // 181
    {-1, 21,  0}, // 182
    {-1, 30,  0}, // 183
    { 2,  1,  1}, // 184
    {-1, 20,  0}, // 185
    { 2,  2,  1}, // 186
    {-1, 33,  0}, // 187
    { 2,  0,  0}, // 188
    {-1, 32,  0}, // 189
    {-1, 31,  0}, // 190
    { 3,  1,  0}, // 191
    {-1,  6,  0}, // 192
    { 0,  1,  0}, // 193
    { 1,  2,  4}, // 194
    { 0,  2,  4}, // 195
    { 1,  0,  3}, // 196
    { 0,  0,  0}, // 197
    {-1, 21,  0}, // 198
    {-1, 30,  0}, // 199
    { 2,  1,  3}, // 200
    {-1, 20,  0}, // 201
    { 2,  2,  0}, // 202
    {-1, 33,  0}, // 203
    { 2,  0,  3}, // 204
    {-1, 32,  0}, // 205
    {-1, 31,  0}, // 206
    { 3,  1,  0}, // 207
    {-1, -1,  35}, // 208
    { 0,  1,  4}, // 209
    { 1,  2,  0}, // 210
    { 0,  2,  0}, // 211
    { 1,  0,  3}, // 212
    { 0,  0,  0}, // 213
    {-1, 21,  0}, // 214
    {-1, 30,  0}, // 215
    { 2,  1,  0}, // 216
    {-1, 20,  0}, // 217
    { 2,  2,  0}, // 218
    {-1, 33,  0}, // 219
    { 2,  0,  3}, // 220
    {-1, 32,  0}, // 221
    {-1, 31,  0}, // 222
    { 3,  1,  0}, // 223
    {-1, -1,  34}, // 224
    { 0,  1,  0}, // 225
    { 1,  2,  4}, // 226
    { 0,  2,  0}, // 227
    { 1,  0,  0}, // 228
    { 0,  0,  0}, // 229
    {-1, 21,  0}, // 230
    {-1, 30,  0}, // 231
    { 2,  1,  3}, // 232
    {-1, 20,  0}, // 233
    { 2,  2,  0}, // 234
    {-1, 33,  0}, // 235
    { 2,  0,  3}, // 236
    {-1, 32,  0}, // 237
    {-1, 31,  0}, // 238
    { 3,  1,  0}, // 239
    {-1, -1,  0}, // 240
    { 0,  1, 10}, // 241
    { 1,  2,  8}, // 242
    { 0,  2,  4}, // 243
    { 1,  0,  7}, // 244
    { 0,  0,  0}, // 245
    {-1, 21,  0}, // 246
    {-1, 30,  0}, // 247
    { 2,  1,  0}, // 248
    {-1, 20,  0}, // 249
    { 2,  2,  0}, // 250
    {-1, 33,  0}, // 251
    { 2,  0,  0}, // 252
    {-1, 32,  0}, // 253
    {-1, 31,  0}, // 254
    { 3,  1,  0}, // 255
    // clang-format on
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
            draw_indexed(
                "core.shadow_edges",
                x * inf_tiles + inf_screenx,
                y * inf_tiles + inf_screeny,
                0);
        }
    }
}



void render_shadow(int l, int dx, int dy)
{
    // +-----------+
    // | a | b | c |
    // |---+---+---|
    // | d | x | e |
    // |---+---+---|
    // | f | g | h |
    // +-----------+
    // +-----------------+
    // |  32 |    2 | 64 |
    // |-----+------+----|
    // |   8 | 1000 |  1 |
    // |-----+------+----|
    // | 128 |    4 | 16 |
    // +-----------------+

    if (l == 0)
    {
        // You can see the cell (x) and all 8 cells around the cell (a-h).
        // Then, no shadow need rendering.
        return;
    }

    if (l < 1000)
    {
        // You can see the cell (x), buy cannot see at least one of the cells
        // around cell x (a-h).
        // l in [0, 256)
        for (int i = 0; i < 1 + (shadow_deco[l]._2 != 0); ++i)
        {
            if (shadow_deco[l]._0 < 0 || i == 1)
            {
                const auto deco2 =
                    i == 0 ? shadow_deco[l]._1 : shadow_deco[l]._2;
                switch (deco2)
                {
                case 1:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    break;
                case 2:
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                case 3:
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    break;
                case 4:
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    break;
                case 5:
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    break;
                case 6:
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    break;
                case 7:
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                case 8:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    break;
                case 9:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    break;
                case 10:
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                case 20:
                    draw_indexed_region("core.shadow", dx, dy, 0, 2, 1, 2);
                    draw_indexed_region("core.shadow", dx + 24, dy, 5, 2, 1, 2);
                    break;
                case 21:
                    draw_indexed_region("core.shadow", dx, dy, 2, 0, 2, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 2, 5, 2, 1);
                    break;
                case 30:
                    draw_indexed_region("core.shadow", dx, dy, 0, 0, 2, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 0, 5, 2, 1);
                    break;
                case 31:
                    draw_indexed_region("core.shadow", dx, dy, 4, 0, 2, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 4, 5, 2, 1);
                    break;
                case 32:
                    draw_indexed_region("core.shadow", dx, dy, 0, 0, 1, 2);
                    draw_indexed_region("core.shadow", dx + 24, dy, 5, 0, 1, 2);
                    break;
                case 33:
                    draw_indexed_region("core.shadow", dx, dy, 0, 4, 1, 2);
                    draw_indexed_region("core.shadow", dx + 24, dy, 5, 4, 1, 2);
                    break;
                case 34:
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                case 35:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    break;
                case 36:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx + 24, dy, 6, 1, 1, 1);
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                case 37:
                    draw_indexed_region("core.shadow", dx, dy, 7, 1, 1, 1);
                    draw_indexed_region("core.shadow", dx, dy + 24, 7, 0, 1, 1);
                    draw_indexed_region(
                        "core.shadow", dx + 24, dy + 24, 6, 0, 1, 1);
                    break;
                default: break;
                }
            }
            else
            {
                draw_indexed(
                    "core.shadow_deco",
                    dx,
                    dy,
                    shadow_deco[l]._0,
                    shadow_deco[l]._1);
            }
        }
    }
    else
    {
        // You cannot see the cell (x).
        const int l2 = (l - 1000) % 16; // check b, d, e and g.
        int i = 0;
        if (l2 == 15)
        {
            // You cannot see the cell (x) and all 4 cells around the cell (b,
            // d, e and g).
            const int l3 = (l - 1000) % 256 - 15; // check a, c, f and h.
            // clang-format off
            switch (l3)
            {
                                                    // You cannot see:
            case                  0: i =  0; break; // - - - -
            case                 16: i =  0; break; // - - - a
            case            32:      i =  0; break; // - - h -
            case            32 + 16: i = 17; break; // - - h a
            case       64:           i =  0; break; // - f - -
            case       64      + 16: i =  0; break; // - f - a
            case       64 + 32:      i =  0; break; // - f h -
            case       64 + 32 + 16: i = 13; break; // - f h a
            case 128:                i =  0; break; // c - - -
            case 128           + 16: i =  0; break; // c - - a
            case 128      + 32:      i =  0; break; // c - h -
            case 128      + 32 + 16: i = 15; break; // c - h a
            case 128 + 64:           i = 17; break; // c f - -
            case 128 + 64      + 16: i = 14; break; // c f - a
            case 128 + 64 + 32:      i = 16; break; // c f h -
            case 128 + 64 + 32 + 16: i =  0; break; // c f h a
            default: assert(0);      i =  0; break;
            }
            // clang-format on
        }
        else
        {
            assert(0 <= l2 && l2 <= 14);
            static const int shadow_map[] = {
                // clang-format off
                    //     You cannot see:
                 0, //  0; - - - - UNUSED
                 9, //  1; - d - -
                10, //  2; - - - g
                 5, //  3; - d - g
                12, //  4; b - - -
                 7, //  5; b d - -
                 0, //  6; b - - g
                 1, //  7; b d - g
                11, //  8; - - e -
                 0, //  9; - d e -
                 6, // 10; - - e g
                 3, // 11; - d e g
                 8, // 12; b - e -
                 4, // 13; b d e -
                 2, // 14; b - e g
                // clang-format on
            };
            i = shadow_map[l2];
        }
        draw_indexed("core.shadow_edges", dx, dy, i);
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
    Cloud(int x0, int y0, data::InstanceId asset)
        : x0(x0)
        , y0(y0)
        , asset(asset)
    {
    }

    int x0;
    int y0;
    data::InstanceId asset;
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
            clouds.emplace_back(x0, y0, "core.cloud1");
        }
        else
        {
            clouds.emplace_back(x0, y0, "core.cloud2");
        }
    }
}



void render_cloud()
{
    static int dummy = ((void)initialize_cloud_data(), 0);
    (void)dummy;

    for (size_t i = 0; i < clouds.size(); ++i)
    {
        const auto& rect = get_image_info(clouds[i].asset);

        gmode(5, 7 + i * 2);
        int x = (clouds[i].x0 - cdata.player().position.x * inf_tiles + sxfix) *
                100 / (40 + i * 5) +
            scrturn * 100 / (50 + i * 20);
        int y = (clouds[i].y0 - cdata.player().position.y * inf_tiles + syfix) *
            100 / (40 + i * 5);
        x = x % (windoww + rect.width) - rect.width;
        y = y % (inf_very + rect.height) - rect.height;
        int height = rect.height;
        if (y + height > inf_very)
        {
            height = inf_very - y;
        }
        if (y < inf_very)
        {
            gcopy(rect.window_id, rect.x, rect.y, rect.width, height, x, y);
        }
    }
}



void draw_hp_bar(const Character& chara, int x, int y)
{
    const int ratio = std::min(chara.hp * 30 / chara.max_hp, 30);
    if (ratio <= 0)
        return;

    if (chara.is_player_or_ally())
    {
        if (map_data.type != mdata_t::MapType::world_map)
        {
            draw_bar("core.hp_bar_ally", x + 9, y + 32, ratio, 3, ratio);
        }
    }
    else
    {
        draw_bar("core.hp_bar_other", x + 9, y + 32, ratio, 3, ratio);
    }
}



void draw_character_sprite_in_world_map(
    int c_,
    int x,
    int y,
    int frame,
    int direction)
{
    int texture_id =
        c_ + 10 + PicLoader::max_buffers + TintedBuffers::max_buffers;

    // Shadow
    gmode(2, 85);
    draw_centered("core.character_shadow", x + 24, y + 27, 20, 10);

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
    int texture_id =
        c_ + 10 + PicLoader::max_buffers + TintedBuffers::max_buffers;

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
    int texture_id =
        c_ + 10 + PicLoader::max_buffers + TintedBuffers::max_buffers;

    // Shadow
    gmode(2, 110);
    draw("core.character_shadow", x + 8, y + 20);

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



snail::Color color_index_to_snail_color(int color_index)
{
    const uint8_t r = 255 - c_col(0, color_index);
    const uint8_t g = 255 - c_col(1, color_index);
    const uint8_t b = 255 - c_col(2, color_index);
    return {r, g, b};
}



void draw_chara_chip_sprite_in_world_map(
    const Extent& ext,
    const snail::Color& tint,
    int x,
    int y,
    int offset_y)
{
    gmode(2, 85);
    draw_centered("core.character_shadow", x + 24, y + 32, 20, 10);
    gmode(2);
    set_color_mod(tint.r, tint.g, tint.b, ext.buffer);
    gcopy_c(
        ext.buffer,
        ext.x,
        ext.y,
        ext.width,
        ext.height,
        x + inf_tiles / 2,
        y + inf_tiles / 2 - offset_y / 4,
        ext.width / 2,
        ext.height / 2);
}



void draw_chara_chip_sprite_in_water(
    const Extent& ext,
    const snail::Color& tint,
    int x,
    int y,
    int offset_y)
{
    set_color_mod(tint.r, tint.g, tint.b, ext.buffer);
    // bottom (under water)
    gmode(2, 100);
    gcopy(
        ext.buffer,
        ext.x,
        ext.y + ext.height - 16,
        ext.width,
        16,
        x,
        y - offset_y + ext.height - 16 + 16);
    gmode(2);
    // top (above water)
    gcopy(
        ext.buffer,
        ext.x,
        ext.y,
        ext.width,
        ext.height - 16,
        x,
        y - offset_y + 16);
}



void draw_chara_chip_sprite(
    const Extent& ext,
    const snail::Color& tint,
    int x,
    int y,
    int offset_y)
{
    gmode(2, 110);
    draw("core.character_shadow", x + 8, y + 20);
    gmode(2);
    set_color_mod(tint.r, tint.g, tint.b, ext.buffer);
    gcopy(ext.buffer, ext.x, ext.y, ext.width, ext.height, x, y - offset_y);
}



void draw_npc_own_sprite(
    const Character& chara,
    int dx,
    int dy,
    int ani_,
    int ground_)
{
    if (map_data.type == mdata_t::MapType::world_map)
    {
        draw_character_sprite_in_world_map(
            chara.index, dx, dy, ani_, chara.direction);
    }
    else if (chip_data[ground_].kind == 3)
    {
        draw_character_sprite_in_water(
            chara.index, dx, dy, ani_, chara.direction);
    }
    else
    {
        draw_character_sprite(chara.index, dx, dy, ani_, chara.direction);
    }
    gmode(2);
    if (chara.furious != 0)
    {
        draw("core.furious_icon", dx + 12, dy - 28);
    }
    if (chara.emotion_icon != 0)
    {
        draw_emo(chara, dx + 4, dy - 32);
    }
}



void draw_npc_chara_chip(const Character& chara, int dx, int dy, int ground_)
{
    const auto color_index = chara.image / 1000;
    const auto image_legacy_id = chara.image % 1000;

    const auto ext_opt = draw_get_rect_chara(image_legacy_id);
    if (!ext_opt)
        return;
    const auto& ext = *ext_opt;

    auto offset_y = chara_chips[image_legacy_id].offset_y;

    if (chara.is_hung_on_sand_bag())
    {
        // gmode(2, 80);
        // func_2(1, 96, 816, -80, 48, 96);
        // gmode(2);
        gcopy(1, 96, 816, 48, 96, dx, dy - 63);
        offset_y += 24;
    }
    if (map_data.type == mdata_t::MapType::world_map)
    {
        draw_chara_chip_sprite_in_world_map(
            ext, color_index_to_snail_color(color_index), dx, dy, offset_y);

        if (chara.emotion_icon != 0)
        {
            draw_emo(chara, x + 4, y - offset_y / 4 - 16);
        }
    }
    else
    {
        if (chip_data[ground_].kind == 3)
        {
            draw_chara_chip_sprite_in_water(
                ext, color_index_to_snail_color(color_index), dx, dy, offset_y);
        }
        else
        {
            draw_chara_chip_sprite(
                ext, color_index_to_snail_color(color_index), dx, dy, offset_y);
        }

        if (chara.furious != 0)
        {
            draw("core.furious_icon", dx + 12, dy - offset_y - 12);
        }
        if (chara.emotion_icon != 0)
        {
            draw_emo(chara, dx + 4, dy - offset_y - 16);
        }
    }
    if (chara.is_hung_on_sand_bag())
    {
        gcopy(1, 96, 768, 48, 48, dx, dy - 26);
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
        debug_is_wizard();
}



bool is_night()
{
    return game_data.date.hour > 17 || game_data.date.hour < 6;
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
            draw_indexed_rotated(
                "core.mef_subref",
                dx + 24,
                dy + 24,
                mefsubref(0, p_) + efmap(3, x, y),
                mefsubref(1, p_),
                0.785 * efmap(2, x, y));
        }
        else
        {
            gmode(2, 150);
            draw_indexed(
                "core.mef_subref",
                dx + 8,
                dy + 8,
                mefsubref(0, p_) + efmap(1, x, y));
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
            const auto& chip = chip_data[p_];
            draw_map_tile(
                p_,
                dx,
                dy - chip.offset_top,
                inf_tiles,
                inf_tiles + chip.offset_bottom);
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
                    draw("core.conquered_nefia_icon", dx + 16, dy - 16);
                }
                else if (area_data[q_].visited_deepest_level != 0)
                {
                    draw("core.invaded_nefia_icon", dx + 16, dy - 16);
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



void draw_one_item(
    int dx,
    int dy,
    int item_chip_id,
    int color_id,
    int chara_chip_id,
    int stack_height,
    int scrturn_)
{
    const auto rect = prepare_item_image(item_chip_id, color_id, chara_chip_id);
    if (map_data.type == mdata_t::MapType::world_map)
    {
        draw_item_chip_in_world_map(
            dx + (inf_tiles / 2),
            dy + (inf_tiles / 2) - (stack_height / 2),
            *rect);
    }
    else
    {
        if (g_config.object_shadow() && item_chips[item_chip_id].shadow)
        {
            draw_item_chip_shadow(
                dx, dy - stack_height, *rect, item_chip_id, 80);
        }
        draw_item_chip_on_ground(
            dx,
            dy - item_chips[item_chip_id].offset_y - stack_height,
            *rect,
            item_chip_id,
            scrturn_);
    }
}



void draw_items(int x, int y, int dx, int dy, int scrturn_)
{
    const auto& item_info_memory = cell_data.at(x, y).item_info_memory;
    if (item_info_memory.is_empty())
        return;

    if (mode == 9)
        return; // TODO

    const auto stack_count = item_info_memory.stack_count();
    if (stack_count < 0)
    {
        const auto bag_icon = 363;
        for (int i = 0; i < (-stack_count); ++i)
        {
            draw_one_item(
                dx,
                dy,
                bag_icon,
                0,
                0,
                i * item_chips[bag_icon].stack_height,
                scrturn_);
        }
    }
    else
    {
        const auto item_indice = item_info_memory.item_indice();
        int stack_height = 0;
        for (const auto& item_index : item_indice)
        {
            if (item_index == 0)
                break;

            const auto item = item_index < 0
                ? g_inv.ground().at(0) /* TODO phantom ref */
                : g_inv.ground().at(item_index - 1);

            if (!item)
            {
                continue; /* TODO phantom ref */
            }

            const auto item_chip_id = item->image;
            const auto color_id = item->tint;
            const auto chara_chip_id = item->param1;
            draw_one_item(
                dx,
                dy,
                item_chip_id,
                color_id,
                chara_chip_id,
                stack_height,
                scrturn_);

            stack_height += item_chips[item_chip_id].stack_height;
            if (item_chip_id == 531 &&
                draw_get_rect_chara(chara_chip_id % 1000)->height == 96)
            {
                stack_height += 44;
            }
        }
    }
}



void draw_npc(int x, int y, int dx, int dy, int ani_, int ground_)
{
    if (cell_data.at(x, y).chara_index_plus_one != 0)
    {
        const int chara_index = cell_data.at(x, y).chara_index_plus_one - 1;
        if (chara_index != 0 && you_can_see(cdata[chara_index]))
        {
            if (cdata[chara_index].has_own_sprite())
            {
                draw_npc_own_sprite(cdata[chara_index], dx, dy, ani_, ground_);
            }
            else
            {
                draw_npc_chara_chip(cdata[chara_index], dx, dy, ground_);
            }

            if (hp_bar_visible(cdata[chara_index]))
            {
                draw_hp_bar(cdata[chara_index], dx, dy);
            }
        }
    }
}

} // namespace



void cell_draw()
{
    static int prev_scrturn = 0;

    elona_vector1<int> p_;
    int ground_ = 0;
    int ani_ = 0;

    const int syfix_ = (scy != scybk) * syfix;
    const int sxfix_ = (scx != scxbk) * sxfix;
    const int scrturn_ = scrturn / 5;

    const bool update_frame = scrturn_ != prev_scrturn;
    prev_scrturn = scrturn_;

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
                gmode(0);
                draw_map_tile(tile_fog, dx_, dy_);
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
                draw_region("core.spot_light", px_, py_, 0, 96, 144, 48);
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
                draw_region(
                    "core.spot_light", px_ - 48, py_ - 48, 0, 0, 144, 96);

                if (py_ < windowh - inf_verh - 24)
                {
                    if (cdata.player().activity.type == Activity::Type::fish)
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
                    else if (chip_data[ground_].kind == 3)
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
                    draw("core.furious_icon", px_, py_ - 24);
                }
                if (cdata.player().emotion_icon != 0)
                {
                    draw_emo(cdata.player(), px_ + 4, py_ - 32);
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
                gmode(0);
                draw_map_tile(tile_fog, dx_, dy_);
                continue;
            }

            // Map tile
            ground_ = cell_data.at(x_, y).chip_id_memory;
            if (chip_data[ground_].wall_kind == 2 && y < map_data.height - 1 &&
                chip_data[cell_data.at(x_, y + 1).chip_id_memory].wall_kind !=
                    2 &&
                cell_data.at(x_, y + 1).chip_id_memory != tile_fog)
            {
                ground_ += 33;
            }
            if (chip_data[ground_].anime_frame != 0)
            {
                auto cur_frame =
                    scrturn_ % (chip_data[ground_].anime_frame + 1);
                auto anim_frame = cur_frame -
                    (cur_frame == chip_data[ground_].anime_frame) * 2 *
                        (chip_data[ground_].anime_frame != 0);
                gmode(0);
                draw_map_tile(ground_, dx_, dy_, anim_frame);
            }
            else
            {
                gmode(0);
                draw_map_tile(ground_, dx_, dy_);
            }

            draw_blood_pool_and_fragments(x_, y, dx_, dy_);
            draw_efmap(x_, y, dx_, dy_, update_frame);
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
                    light_ -=
                        (6 -
                         clamp(dist(cdata.player().position, x_, y), 0, 6)) *
                        light.brightness;
                    gmode(5, light.alpha_base + rnd(light.alpha_random + 1));
                    draw_indexed(
                        "core.light",
                        dx_,
                        dy_ - light.dy,
                        light.x + rnd(light.frame + 1));
                }
            }

            if (chip_data[ground_].wall_kind)
            {
                gmode(0);
                if (y > 0)
                {
                    p_ = cell_data.at(x_, y - 1).chip_id_memory;
                    if (chip_data[p_].wall_kind != 2 && p_ != tile_fog &&
                        dy_ > 20)
                    {
                        draw_map_tile(
                            ground_,
                            dx_,
                            dy_ - 12,
                            inf_tiles - std::max(dx_ + inf_tiles - windoww, 0) +
                                std::min(dx_, 0),
                            12);
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
                if (chip_data[ground_].wall_kind)
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

    if (g_config.high_quality_shadow())
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
