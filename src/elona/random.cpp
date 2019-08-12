#include "random.hpp"
#include "gdata.hpp"



namespace elona
{

namespace detail
{
xoshiro256::xoshiro256_engine engine{std::random_device{}()};
} // namespace detail



void randomize()
{
    ++game_data.random_seed_offset;
    randomize(game_data.random_seed + game_data.random_seed_offset);
}

} // namespace elona
