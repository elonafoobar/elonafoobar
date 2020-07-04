#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "serialization/macros.hpp"



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
        std::stringstream ss;
        ss << '(' << x << ", " << y << ')';
        return ss.str();
    }



    template <typename Archive>
    void serialize(Archive& ar)
    {
        /* clang-format off */
        ELONA_SERIALIZATION_STRUCT_BEGIN(ar, "Position");

        ELONA_SERIALIZATION_STRUCT_FIELD(*this, x);
        ELONA_SERIALIZATION_STRUCT_FIELD(*this, y);

        ELONA_SERIALIZATION_STRUCT_END();
        /* clang-format on */
    }
};


inline std::ostream& operator<<(std::ostream& out, const Position& pos)
{
    out << pos.to_string();
    return out;
}


int direction(int = 0, int = 0, int = 0, int = 0);
int dist(int = 0, int = 0, int = 0, int = 0);

} // namespace elona
