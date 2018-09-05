#include "lua_api_world.hpp"

namespace elona
{
namespace lua
{

int World::time()
{
    return gdata_hour + gdata_day * 24 + gdata_month * 24 * 30
        + gdata_year * 24 * 30 * 12;
}

void World::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, World, time);
}

} // namespace lua
} // namespace elona
