#pragma once

#include <iostream>



namespace elona
{


struct position_t
{
    int x = 0;
    int y = 0;

    position_t() {}
    position_t(int _x, int _y) : x(_x), y(_y) {}

    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(x);
        ar(y);
    }
};


inline bool operator==(const position_t& lhs, const position_t& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}


inline bool operator!=(const position_t& lhs, const position_t& rhs)
{
    return !(lhs == rhs);
}


inline std::ostream& operator<<(std::ostream& out, const position_t& pos)
{
    out << '(' << pos.x << ", " << pos.y << ')';
    return out;
}



} // namespace elona
