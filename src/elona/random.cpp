#include "random.hpp"

#include "game.hpp"



namespace elona
{

namespace detail
{
xoshiro256::xoshiro256_engine engine{std::random_device{}()};
} // namespace detail



void randomize()
{
    ++game()->random_seed_offset;
    randomize(game()->random_seed + game()->random_seed_offset);
}



int roll(int x, int y, int z)
{
    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;
    int ret = 0;
    for (int i = 0; i < x; ++i)
    {
        ret += rnd_capped(y) + 1;
    }
    return ret + z;
}



int roll_max(int x, int y, int z)
{
    return x * y + z;
}



int roundmargin(int x, int y)
{
    if (x > y)
        return x - rnd_capped(x - y);
    else if (x < y)
        return x + rnd_capped(y - x);
    else
        return x;
}

} // namespace elona
