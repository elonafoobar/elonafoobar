#include "lua_api_math.hpp"
#include "../../calc.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Clamps a number between two numbers.
 * @tparam num n
 * @tparam num min
 * @tparam num max
 * @treturn num a number between min and max
 */
int LuaApiMath::clamp(int n, int min, int max)
{
    return elona::clamp(n, min, max);
}

int LuaApiMath::calc_objlv(int level)
{
    return calcobjlv(level);
}

void LuaApiMath::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiMath, clamp);
    LUA_API_BIND_FUNCTION(api_table, LuaApiMath, calc_objlv);
}

} // namespace lua
} // namespace elona
