#pragma once



namespace elona
{


struct extent
{
    extent()
        : extent(0, 0, 0, 0){};

    extent(int x, int y, int width, int height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , frame_width(width)
    {
    }

    extent(int x, int y, int width, int height, int frame_width)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , frame_width(frame_width)
    {
    }

    int x;
    int y;
    int width;
    int height;
    int frame_width;
    int buffer;

    int left() const
    {
        return x;
    }

    int right() const
    {
        return x + width - 1;
    }

    int bottom() const
    {
        return y + height - 1;
    }
};


} // namespace elona
