#pragma once

#include <cstdint>



namespace elona::snail
{

/**
 * RGBA color
 */
struct Color
{
    /// Red
    uint8_t r;
    /// Green
    uint8_t g;
    /// Blue
    uint8_t b;
    /// Alpha
    uint8_t a;



    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }


    // Grayscale
    constexpr explicit Color(uint8_t v, uint8_t a = 255) noexcept
        : Color(v, v, v, a)
    {
    }


    constexpr bool operator==(const Color& other) const noexcept
    {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }


    constexpr bool operator!=(const Color& other) const noexcept
    {
        return !(*this == other);
    }
};



namespace palette
{
constexpr Color black = {0, 0, 0, 255};
constexpr Color white = {255, 255, 255, 255};
} // namespace palette

} // namespace elona::snail
