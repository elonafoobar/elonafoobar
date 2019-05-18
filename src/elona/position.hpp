#pragma once

#include <iostream>



namespace elona
{

/// @putit
struct Position
{
    /// @putit
    int x = 0;

    /// @putit
    int y = 0;

    Position()
    {
    }

    Position(int _x, int _y)
        : x(_x)
        , y(_y)
    {
    }


#include "_putit/position.cpp"
};


inline bool operator==(const Position& lhs, const Position& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}


inline bool operator!=(const Position& lhs, const Position& rhs)
{
    return !(lhs == rhs);
}


inline std::ostream& operator<<(std::ostream& out, const Position& pos)
{
    out << '(' << pos.x << ", " << pos.y << ')';
    return out;
}



} // namespace elona
