#pragma once

#include <cmath>

#include <iosfwd>
#include <string>



namespace elona
{

struct Position
{
    int x = 0;
    int y = 0;

    Position()
    {
    }

    Position(int _x, int _y)
        : x(_x)
        , y(_y)
    {
    }



    bool operator==(const Position& other) const noexcept
    {
        return x == other.x && y == other.y;
    }



    bool operator!=(const Position& other) const noexcept
    {
        return !(*this == other);
    }



    std::string to_string() const
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }



    friend std::ostream& operator<<(std::ostream& out, const Position& pos);
};



int direction(int = 0, int = 0, int = 0, int = 0);



/**
 * Calculate a distance between (@a x1, @a y1) and (@a x2, @a y2).
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param x2 The X coordinate of the end position.
 * @param y2 The Y coordinate of the end position.
 * @return The distance between the two positions.
 */
inline double fdist(int x1, int y1, int x2, int y2)
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
inline double fdist(int x1, int y1, const Position& p2)
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
inline double fdist(const Position& p1, int x2, int y2)
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
inline int dist(int x1, int y1, int x2, int y2)
{
    return static_cast<int>(fdist(x1, y1, x2, y2));
}



/**
 * Calculate a distance between (@a x1, @a y1) and @a p2 in tiles.
 *
 * @param x1 The X coordinate of the starting position.
 * @param y1 The Y coordinate of the starting position.
 * @param p2 The end position.
 * @return The distance between the two positions in tiles.
 */
inline int dist(int x1, int y1, const Position& p2)
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
inline int dist(const Position& p1, int x2, int y2)
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
inline int dist(const Position& p1, const Position& p2)
{
    return dist(p1.x, p1.y, p2.x, p2.y);
}

} // namespace elona
