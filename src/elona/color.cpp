#include "color.hpp"

#include "variables.hpp"



namespace elona
{

Color color_index_to_color(int color_index)
{
    const uint8_t r = 255 - c_col(0, color_index);
    const uint8_t g = 255 - c_col(1, color_index);
    const uint8_t b = 255 - c_col(2, color_index);
    return {r, g, b};
}



int color_to_color_index(const Color& color)
{
    for (int i = 0; i < 21; ++i)
    {
        if (color.r == c_col(0, i) && color.g == c_col(1, i) &&
            color.b == c_col(2, i))
        {
            return i;
        }
    }
    return 0;
}

} // namespace elona
