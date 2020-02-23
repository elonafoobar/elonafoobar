#pragma once

#include <iostream>
#include <sstream>
#include <string>



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



    std::string to_string() const
    {
        std::stringstream ss;
        ss << '(' << x << ", " << y << ')';
        return ss.str();
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
    out << pos.to_string();
    return out;
}

} // namespace elona
