#include "random.hpp"
#include <algorithm>


namespace elona
{


namespace detail
{
std::mt19937 random_engine{std::random_device{}()};
// For exrand
std::mt19937 random_engine2{std::random_device{}()};
} // namespace detail


void randomize(std::random_device::result_type seed)
{
    detail::random_engine.seed(seed);
}


void exrand_randomize(std::random_device::result_type seed)
{
    detail::random_engine2.seed(seed);
}



void exrand_rnd(int& result, int max)
{
    if (max <= 0)
    {
        result = 0;
    }
    else
    {
        result =
            std::uniform_int_distribution<>{0, max - 1}(detail::random_engine2);
    }
}



int rnd(int n)
{
    std::uniform_int_distribution<> dist{0,
                                         std::clamp(n - 1, 0, (1 << 16) - 1)};
    return dist(detail::random_engine);
}


} // namespace elona
