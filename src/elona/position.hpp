#pragma once

#include <charconv>
#include <iostream>
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
        // `int64_t` can be represented by at most 20 bytes. The string
        // representation of `Position` consists of 2 integers and 4 additional
        // punctuations, '(', ',', ' ' and ')', so 20+20+4+1=45 is enough (+1
        // is NUL at the end of the string).
        // As `std::to_chars()` never fails unless the buffer provided is
        // smaller for the value, all calls of the function here will succeed.
        char buf[45];
        char* ptr = buf;

        auto putc = [&](char c) { // Put one character on `buf`.
            *ptr = c;
            ++ptr;
        };

        putc('(');
        ptr = std::to_chars(ptr, std::end(buf), x).ptr;
        putc(',');
        putc(' ');
        ptr = std::to_chars(ptr, std::end(buf), y).ptr;
        putc(')');
        *ptr = '\0';
        return std::string(buf, ptr);
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
