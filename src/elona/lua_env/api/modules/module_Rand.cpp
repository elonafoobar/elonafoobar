#include "../../../random.hpp"
#include "../common.hpp"


/**
 * @luadoc
 *
 * Functions for working with randomness.
 */
namespace elona::lua::api::modules::module_Rand
{

/**
 * @luadoc rnd
 *
 * Returns a random number from 0 to n, exclusive.
 *
 * @tparam num n
 * @treturn num a number in [0, n)
 */
int Rand_rnd(int n)
{
    return rnd(n);
}



/**
 * @luadoc rnd_capped
 *
 * Returns a random number from 0 to min(n, 32768), exclusive. It emulates
 * vanilla's random number generation, capped by the upper limit.
 *
 * @tparam num n
 * @treturn num a number in [0, min(n, 32768))
 */
int Rand_rnd_capped(int n)
{
    return rnd_capped(n);
}



/**
 * @luadoc one_in
 *
 * Returns true one out of every n times.
 *
 * @tparam num n
 * @treturn bool true one out of every n times
 */
bool Rand_one_in(int n)
{
    return Rand_rnd(n) == 0;
}



/**
 * @luadoc coinflip
 *
 * Returns true 50% of the time.
 *
 * @treturn bool true 50% of the time
 */
bool Rand_coinflip()
{
    return Rand_one_in(2);
}



/**
 * @luadoc between
 *
 * Returns a random number from min to max, exclusive.
 *
 * @tparam num min
 * @tparam num max
 * @treturn num a number in [min, max)
 */
int Rand_between(int min, int max)
{
    if (max <= min)
    {
        return min;
    }

    return min + Rand_rnd(max - min);
}



/**
 * @luadoc choice
 *
 * Returns a random object from a table.
 *
 * @tparam table table a table
 * @treturn object an object from the table
 */
sol::object Rand_choice(sol::table table)
{
    if (table.size() == 0)
    {
        return sol::lua_nil;
    }

    return table[Rand_rnd(table.size()) + 1];
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("rnd", Rand_rnd);
    ELONA_LUA_API_BIND_FUNCTION("rnd_capped", Rand_rnd_capped);
    ELONA_LUA_API_BIND_FUNCTION("one_in", Rand_one_in);
    ELONA_LUA_API_BIND_FUNCTION("coinflip", Rand_coinflip);
    ELONA_LUA_API_BIND_FUNCTION("between", Rand_between);
    ELONA_LUA_API_BIND_FUNCTION("choice", Rand_choice);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Rand
