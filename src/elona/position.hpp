#pragma once

#include <cmath>

#include <string>

#include "typedefs.hpp"



namespace elona
{

struct Position
{
    lua_int x{};
    lua_int y{};



    constexpr Position() noexcept = default;


    constexpr Position(lua_int x, lua_int y) noexcept
        : x(x)
        , y(y)
    {
    }



    constexpr bool operator==(const Position& other) const noexcept
    {
        return x == other.x && y == other.y;
    }



    constexpr bool operator!=(const Position& other) const noexcept
    {
        return !(*this == other);
    }



    std::string to_string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};



inline int direction(int x1, int y1, int x2, int y2)
{
    if (std::abs(x1 - x2) > std::abs(y1 - y2))
    {
        return x1 > x2 ? 1 : 2;
    }
    else
    {
        return y1 > y2 ? 3 : 0;
    }
}



/**
 * Calculate a distance between (@a x1, @a y1) and (@a x2, @a y2).
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param x2 The X coordinate of the end position.
 * @param y2 The Y coordinate of the end position.
 * @return The distance between the two positions.
 */
inline double fdist(lua_int x1, lua_int y1, lua_int x2, lua_int y2)
{
    // TODO potential overflow
    const double dx = x1 - x2;
    const double dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}



/**
 * Calculate a distance between (@a x1, @a y1) and @a p2.
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param p2 The end position.
 * @return The distance between the two positions.
 */
inline double fdist(lua_int x1, lua_int y1, const Position& p2)
{
    return fdist(x1, y1, p2.x, p2.y);
}



/**
 * Calculate a distance between @a p1 and (@a x2, @a y2).
 *
 * @param p1 The starting position.
 * @param x2 The X coordinate of the end position.
 * @param y2 The Y coordinate of the end position.
 * @return The distance between the two positions.
 */
inline double fdist(const Position& p1, lua_int x2, lua_int y2)
{
    return fdist(p1.x, p1.y, x2, y2);
}



/**
 * Calculate a distance between @a p1 and @a p2.
 *
 * @param p1 The starting position.
 * @param p2 The end position.
 * @return The distance between the two positions.
 */
inline double fdist(const Position& p1, const Position& p2)
{
    return fdist(p1.x, p1.y, p2.x, p2.y);
}



/**
 * Calculate a distance between (@a x1, @a y1) and (@a x2, @a y2) in tiles.
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param x2 The X coordinate of the end position.
 * @param y2 The Y coordinate of the end position.
 * @return The distance between the two positions in tiles.
 */
inline lua_int dist(lua_int x1, lua_int y1, lua_int x2, lua_int y2)
{
    return static_cast<lua_int>(fdist(x1, y1, x2, y2));
}



/**
 * Calculate a distance between (@a x1, @a y1) and @a p2 in tiles.
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param p2 The end position.
 * @return The distance between the two positions in tiles.
 */
inline lua_int dist(lua_int x1, lua_int y1, const Position& p2)
{
    return dist(x1, y1, p2.x, p2.y);
}



/**
 * Calculate a distance between @a p1 and (@a x2, @a y2) in tiles.
 *
 * @param p1 The starting position.
 * @param x2 The X coordinate of the end position.
 * @param y2 The Y coordinate of the end position.
 * @return The distance between the two positions in tiles.
 */
inline lua_int dist(const Position& p1, lua_int x2, lua_int y2)
{
    return dist(p1.x, p1.y, x2, y2);
}



/**
 * Calculate a distance between @a p1 and @a p2 in tiles.
 *
 * @param p1 The starting position.
 * @param p2 The end position.
 * @return The distance between the two positions in tiles.
 */
inline lua_int dist(const Position& p1, const Position& p2)
{
    return dist(p1.x, p1.y, p2.x, p2.y);
}

} // namespace elona
