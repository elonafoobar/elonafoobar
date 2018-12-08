#include "lua_api_world.hpp"
#include "../../gdata.hpp"

namespace elona
{
namespace lua
{

int World::time()
{
    return game_data.date.hours();
}

bool World::belongs_to_guild(const std::string& guild_name)
{
    if (guild_name == "mages")
    {
        return game_data.guild.belongs_to_mages_guild == 1;
    }
    else if (guild_name == "fighters")
    {
        return game_data.guild.belongs_to_fighters_guild == 1;
    }
    else if (guild_name == "thieves")
    {
        return game_data.guild.belongs_to_thieves_guild == 1;
    }

    return false;
}

void World::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, World, time);
    LUA_API_BIND_FUNCTION(api_table, World, belongs_to_guild);
}

} // namespace lua
} // namespace elona
