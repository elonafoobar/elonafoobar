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
        , height(height)
        , frame_width(width) {}
    extent(int x, int y, int width, int height, int frame_width)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , frame_width(frame_width) {}

    int x;
    int y;
    int width;
    int height;
    int frame_width;
    int buffer;

    inline int left() const { return x; }
    inline int right() const { return x + width - 1; }
    inline int bottom() const { return y + height -1; }
};

}
