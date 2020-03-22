#include "position.hpp"

#include <cmath>



namespace elona
{

int dist(int x1, int y1, int x2, int y2)
{
    const auto dx = x1 - x2;
    const auto dy = y1 - y2;
    return int(std::sqrt(dx * dx + dy * dy));
}



int direction(int x1, int y1, int x2, int y2)
{
    if (std::abs(x1 - x2) > std::abs(y1 - y2))
    {
        return x1 > x2 ? 1 : 2;
    }
    else
    {
        return y1 > y2 ? 3 : 0;
    }
}

} // namespace elona
