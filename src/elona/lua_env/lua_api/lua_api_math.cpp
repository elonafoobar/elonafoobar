#include "lua_api_math.hpp"

namespace elona
{
namespace lua
{

int LuaApiMath::clamp(int n, int min, int max)
{
    return elona::clamp(n, min, max);
}

void LuaApiMath::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiMath, clamp);
}

} // namespace lua
} // namespace elona
