#include "lua_api_world.hpp"

namespace elona
{
namespace lua
{

int World::time()
{
    return game_data.date.hour + game_data.date.day * 24
        + game_data.date.month * 24 * 30 + game_data.date.year * 24 * 30 * 12;
}

void World::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, World, time);
}

} // namespace lua
} // namespace elona
