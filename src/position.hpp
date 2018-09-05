#pragma once

#include <iostream>



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

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(x);
        ar(y);
    }
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
