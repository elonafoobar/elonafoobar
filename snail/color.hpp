#pragma once

#include <cstdint>
#include "detail/sdl.hpp"



namespace elona::snail
{


struct color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;


    constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }


    // Grayscale
    explicit constexpr color(uint8_t v, uint8_t a = 255)
        : color(v, v, v, a)
    {
    }
};


inline bool operator==(const color& x, const color& y)
{
    return x.r == y.r && x.g == y.g && x.b == y.b && x.a == y.a;
}


inline bool operator!=(const color& x, const color& y)
{
    return !(x == y);
}



namespace palette
{
constexpr color black = {0, 0, 0};
constexpr color white = {255, 255, 255};
} // namespace palette



namespace detail
{

inline ::SDL_Color to_sdl_color(const color& c)
{
    return ::SDL_Color{c.r, c.g, c.b, c.a};
}

} // namespace detail


} // namespace elona::snail
