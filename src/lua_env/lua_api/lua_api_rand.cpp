#include "lua_api_rand.hpp"

namespace elona
{
namespace lua
{

int Rand::rnd(int n)
{
    return elona::rnd(n);
}

bool Rand::one_in(int n)
{
    return Rand::rnd(n) == 0;
}

bool Rand::coinflip()
{
    return Rand::one_in(2);
}

void Rand::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Rand, rnd);
    LUA_API_BIND_FUNCTION(api_table, Rand, one_in);
    LUA_API_BIND_FUNCTION(api_table, Rand, coinflip);
}

} // namespace lua
} // namespace elona
