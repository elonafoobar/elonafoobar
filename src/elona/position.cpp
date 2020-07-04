#include "position.hpp"



namespace elona
{

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
