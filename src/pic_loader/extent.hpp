#pragma once



namespace elona
{


struct Extent
{
    Extent()
        : Extent(0, 0, 0, 0){};

    Extent(int x, int y, int width, int height)
        : x(x)
        , y(y)
        , width(width)
        , height(height)
        , frame_width(width)
    {
    }

    Extent(int x, int y, int width, int height, int frame_width)
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
