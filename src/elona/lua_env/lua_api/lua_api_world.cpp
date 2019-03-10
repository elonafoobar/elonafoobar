#include "lua_api_world.hpp"
#include "../../event.hpp"
#include "../../gdata.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Returns the time in hours since year 0.
 * @treturn num the time in hours
 */
int LuaApiWorld::time()
{
    return game_data.date.hours();
}

/**
 * @luadoc
 *
 * Gets the ID of the next deferred event that will run.
 * @treturn num
 */
int LuaApiWorld::deferred_event_id()
{
    return event_id();
}

/**
 * @luadoc
 *
 * Adds a deferred event.
 * @tparam num event_id the event id
 * @tparam[opt] num param1 An extra parameter.
 * @tparam[opt] num param2 An extra parameter.
 */
void LuaApiWorld::add_deferred_event(
    int event_id,
    sol::optional<int> param1,
    sol::optional<int> param2)
{
    if (!param1)
    {
        param1 = 0;
    }
    if (!param2)
    {
        param2 = 0;
    }
    event_add(event_id, *param1, *param2);
}

/**
 * @luadoc
 *
 * Returns true if the player is part of the provided guild.
 * @tparam string guild_name One of "mages", "fighters" or "thieves"
 */
bool LuaApiWorld::belongs_to_guild(const std::string& guild_name)
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

void LuaApiWorld::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, time);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, deferred_event_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, add_deferred_event);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, belongs_to_guild);

    /**
     * @luadoc data field LuaGameData
     *
     * [R] Data for the current game save.
     */
    api_table.set("data", sol::property(&game_data));
}

} // namespace lua
} // namespace elona
