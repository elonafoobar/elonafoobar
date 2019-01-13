#include "lua_api_rand.hpp"

namespace elona
{
namespace lua
{

int LuaApiRand::rnd(int n)
{
    return elona::rnd(n);
}

bool LuaApiRand::one_in(int n)
{
    return LuaApiRand::rnd(n) == 0;
}

bool LuaApiRand::coinflip()
{
    return LuaApiRand::one_in(2);
}

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
    LUA_API_BIND_FUNCTION(api_table, LuaApiRand, choice);
}

} // namespace lua
} // namespace elona
