#pragma once

namespace elona
{

struct extent
{
    extent() : extent(0, 0, 0, 0) {};
    extent(int x, int y, int width, int height)
        : x(x)
        , y(y)
        , width(width)
        , height(height) {}

    int x;
    int y;
    int width;
    int height;
    int buffer;

    inline int left() const { return x; }
    inline int right() const { return x + width - 1; }
    inline int bottom() const { return y + height -1; }
};

}
