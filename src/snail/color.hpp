#pragma once

#include <cstdint>

#include "detail/sdl.hpp"



namespace elona
{
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


inline bool operator==(const Color& x, const Color& y)
{
    return x.r == y.r && x.g == y.g && x.b == y.b && x.a == y.a;
}


inline bool operator!=(const Color& x, const Color& y)
{
    return !(x == y);
}



namespace palette
{
constexpr Color black = {0, 0, 0, 255};
constexpr Color white = {255, 255, 255, 255};
} // namespace palette



namespace detail
{

inline ::SDL_Color to_sdl_color(const Color& c)
{
    return ::SDL_Color{c.r, c.g, c.b, c.a};
}

} // namespace detail


} // namespace snail
} // namespace elona
