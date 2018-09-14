#include "lua_api_world.hpp"

namespace elona
{
namespace lua
{

int World::time()
{
    return game_data.date.hours();
}

void World::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, World, time);
}

} // namespace lua
} // namespace elona
