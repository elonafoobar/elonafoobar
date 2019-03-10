#include "lua_api_rand.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Returns a random number from 0 to n, exclusive.
 * @tparam num n
 * @treturn num a number in [0, n)
 */
int LuaApiRand::rnd(int n)
{
    return elona::rnd(n);
}

/**
 * @luadoc
 *
 * Returns true one out of every n times.
 * @tparam num n
 * @treturn bool true one out of every n times
 */
bool LuaApiRand::one_in(int n)
{
    return LuaApiRand::rnd(n) == 0;
}

/**
 * @luadoc
 *
 * Returns true 50% of the time.
 * @treturn bool true 50% of the time
 */
bool LuaApiRand::coinflip()
{
    return LuaApiRand::one_in(2);
}

/**
 * @luadoc
 *
 * Returns a random number from min to max, exclusive.
 * @tparam num min
 * @tparam num max
 * @treturn num a number in [min, max)
 */
int LuaApiRand::between(int min, int max)
{
    if (max <= min)
    {
        return min;
    }

    return min + elona::rnd(max - min);
}

/**
 * @luadoc
 *
 * Returns a random object from a table.
 * @tparam table table a table
 * @treturn object an object from the table
 */
sol::object LuaApiRand::choice(sol::table table)
{
    if (table.size() == 0)
    {
        return sol::lua_nil;
    }

    return table[elona::rnd(table.size()) + 1];
}

void LuaApiRand::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, rnd);
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, one_in);
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, coinflip);
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, between);
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, choice);
}

} // namespace lua
} // namespace elona
