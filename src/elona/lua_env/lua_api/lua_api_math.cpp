#include "lua_api_math.hpp"

namespace elona
{
namespace lua
{

int Math::clamp(int n, int min, int max)
{
    return elona::clamp(n, min, max);
}

void Math::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Math, clamp);
}

} // namespace lua
} // namespace elona
