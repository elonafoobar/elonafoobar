#pragma once

#include "../snail/color.hpp"



namespace elona
{

using Color = snail::Color;

Color color_index_to_color(int color_index);
int color_to_color_index(const Color& color);

} // namespace elona
