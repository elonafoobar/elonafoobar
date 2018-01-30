#pragma once

#include <cstdint>
#include "detail/sdl.hpp"



namespace snail
{
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;


    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }


    // Grayscale
    explicit constexpr Color(uint8_t v, uint8_t a = 255)
        : Color(v, v, v, a)
    {
    }
};



namespace Palette
{
constexpr Color alice_blue = {240, 248, 255};
constexpr Color antique_white = {250, 235, 215};
constexpr Color aqua = {0, 255, 255};
constexpr Color aquamarine = {127, 255, 212};
constexpr Color azure = {240, 255, 255};
constexpr Color beige = {245, 245, 220};
constexpr Color bisque = {255, 228, 196};
constexpr Color black = {0, 0, 0};
constexpr Color blanched_almond = {255, 235, 205};
constexpr Color blue = {0, 0, 255};
constexpr Color blue_violet = {138, 43, 226};
constexpr Color brown = {165, 42, 42};
constexpr Color burly_wood = {222, 184, 135};
constexpr Color cadet_blue = {95, 158, 160};
constexpr Color chartreuse = {127, 255, 0};
constexpr Color chocolate = {210, 105, 30};
constexpr Color coral = {255, 127, 80};
constexpr Color cornflower_blue = {100, 149, 237};
constexpr Color cornsilk = {255, 248, 220};
constexpr Color crimson = {220, 20, 60};
constexpr Color cyan = {0, 255, 255};
constexpr Color dark_blue = {0, 0, 139};
constexpr Color dark_cyan = {0, 139, 139};
constexpr Color dark_golden_rod = {184, 134, 11};
constexpr Color dark_gray = {169, 169, 169};
constexpr Color dark_green = {0, 100, 0};
constexpr Color dark_khaki = {189, 183, 107};
constexpr Color dark_magenta = {139, 0, 139};
constexpr Color dark_olive_green = {85, 107, 47};
constexpr Color dark_orange = {255, 140, 0};
constexpr Color dark_orchid = {153, 50, 204};
constexpr Color dark_red = {139, 0, 0};
constexpr Color dark_salmon = {233, 150, 122};
constexpr Color dark_sea_green = {143, 188, 143};
constexpr Color dark_slate_blue = {72, 61, 139};
constexpr Color dark_slate_gray = {47, 79, 79};
constexpr Color dark_turquoise = {0, 206, 209};
constexpr Color dark_violet = {148, 0, 211};
constexpr Color deep_pink = {255, 20, 147};
constexpr Color deep_sky_blue = {0, 191, 255};
constexpr Color dim_gray = {105, 105, 105};
constexpr Color dodger_blue = {30, 144, 255};
constexpr Color fire_brick = {178, 34, 34};
constexpr Color floral_white = {255, 250, 240};
constexpr Color forest_green = {34, 139, 34};
constexpr Color fuchsia = {255, 0, 255};
constexpr Color gainsboro = {220, 220, 220};
constexpr Color ghost_white = {248, 248, 255};
constexpr Color gold = {255, 215, 0};
constexpr Color golden_rod = {218, 165, 32};
constexpr Color gray = {128, 128, 128};
constexpr Color green = {0, 128, 0};
constexpr Color green_yellow = {173, 255, 47};
constexpr Color honey_dew = {240, 255, 240};
constexpr Color hot_pink = {255, 105, 180};
constexpr Color indian_red = {205, 92, 92};
constexpr Color indigo = {75, 0, 130};
constexpr Color ivory = {255, 255, 240};
constexpr Color khaki = {240, 230, 140};
constexpr Color lavender = {230, 230, 250};
constexpr Color lavender_blush = {255, 240, 245};
constexpr Color lawn_green = {124, 252, 0};
constexpr Color lemon_chiffon = {255, 250, 205};
constexpr Color light_blue = {173, 216, 230};
constexpr Color light_coral = {240, 128, 128};
constexpr Color light_cyan = {224, 255, 255};
constexpr Color light_golden_rod_yellow = {250, 250, 210};
constexpr Color light_gray = {211, 211, 211};
constexpr Color light_green = {144, 238, 144};
constexpr Color light_pink = {255, 182, 193};
constexpr Color light_salmon = {255, 160, 122};
constexpr Color light_sea_green = {32, 178, 170};
constexpr Color light_sky_blue = {135, 206, 250};
constexpr Color light_slate_gray = {119, 136, 153};
constexpr Color light_steel_blue = {176, 196, 222};
constexpr Color light_yellow = {255, 255, 224};
constexpr Color lime = {0, 255, 0};
constexpr Color lime_green = {50, 205, 50};
constexpr Color linen = {250, 240, 230};
constexpr Color magenta = {255, 0, 255};
constexpr Color maroon = {128, 0, 0};
constexpr Color medium_aqua_marine = {102, 205, 170};
constexpr Color medium_blue = {0, 0, 205};
constexpr Color medium_orchid = {186, 85, 211};
constexpr Color medium_purple = {147, 112, 219};
constexpr Color medium_sea_green = {60, 179, 113};
constexpr Color medium_slate_blue = {123, 104, 238};
constexpr Color medium_spring_green = {0, 250, 154};
constexpr Color medium_turquoise = {72, 209, 204};
constexpr Color medium_violet_red = {199, 21, 133};
constexpr Color midnight_blue = {25, 25, 112};
constexpr Color mint_cream = {245, 255, 250};
constexpr Color misty_rose = {255, 228, 225};
constexpr Color moccasin = {255, 228, 181};
constexpr Color navajo_white = {255, 222, 173};
constexpr Color navy = {0, 0, 128};
constexpr Color old_lace = {253, 245, 230};
constexpr Color olive = {128, 128, 0};
constexpr Color olive_drab = {107, 142, 35};
constexpr Color orange = {255, 165, 0};
constexpr Color orange_red = {255, 69, 0};
constexpr Color orchid = {218, 112, 214};
constexpr Color pale_golden_rod = {238, 232, 170};
constexpr Color pale_green = {152, 251, 152};
constexpr Color pale_turquoise = {175, 238, 238};
constexpr Color pale_violet_red = {219, 112, 147};
constexpr Color papaya_whip = {255, 239, 213};
constexpr Color peach_puff = {255, 218, 185};
constexpr Color peru = {205, 133, 63};
constexpr Color pink = {255, 192, 203};
constexpr Color plum = {221, 160, 221};
constexpr Color powder_blue = {176, 224, 230};
constexpr Color purple = {128, 0, 128};
constexpr Color rebecca_purple = {102, 51, 153};
constexpr Color red = {255, 0, 0};
constexpr Color rosy_brown = {188, 143, 143};
constexpr Color royal_blue = {65, 105, 225};
constexpr Color saddle_brown = {139, 69, 19};
constexpr Color salmon = {250, 128, 114};
constexpr Color sandy_brown = {244, 164, 96};
constexpr Color sea_green = {46, 139, 87};
constexpr Color sea_shell = {255, 245, 238};
constexpr Color sienna = {160, 82, 45};
constexpr Color silver = {192, 192, 192};
constexpr Color sky_blue = {135, 206, 235};
constexpr Color slate_blue = {106, 90, 205};
constexpr Color slate_gray = {112, 128, 144};
constexpr Color snow = {255, 250, 250};
constexpr Color spring_green = {0, 255, 127};
constexpr Color steel_blue = {70, 130, 180};
constexpr Color tan = {210, 180, 140};
constexpr Color teal = {0, 128, 128};
constexpr Color thistle = {216, 191, 216};
constexpr Color tomato = {255, 99, 71};
constexpr Color turquoise = {64, 224, 208};
constexpr Color violet = {238, 130, 238};
constexpr Color wheat = {245, 222, 179};
constexpr Color white = {255, 255, 255};
constexpr Color white_smoke = {245, 245, 245};
constexpr Color yellow = {255, 255, 0};
constexpr Color yellow_green = {154, 205, 50};
} // namespace Palette



namespace detail
{
inline ::SDL_Color to_sdl_color(const Color& color)
{
    return ::SDL_Color{color.r, color.g, color.b, color.a};
}

} // namespace detail


} // namespace snail
