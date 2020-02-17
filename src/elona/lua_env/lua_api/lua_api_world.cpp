#include "lua_api_world.hpp"

#include "../../deferred_event.hpp"
#include "../../gdata.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Gets the ID of the next deferred event that will run.
 * @treturn num
 */
int LuaApiWorld::deferred_event_id()
{
    return event_processing_event();
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

/**
 * @luadoc
 *
 * Sets the player's guild affiliation and resets guild quotas.
 * @tparam string guild_name One of "mages", "fighters" or "thieves"
 */
void LuaApiWorld::join_guild(const std::string& guild_name)
{
    game_data.guild.belongs_to_thieves_guild = 0;
    game_data.guild.belongs_to_fighters_guild = 0;
    game_data.guild.belongs_to_mages_guild = 0;
    game_data.guild.mages_guild_quota = 0;
    game_data.guild.thieves_guild_quota = 0;
    game_data.guild.joining_mages_guild = 0;
    game_data.guild.joining_thieves_guild = 0;
    game_data.guild.joining_fighters_guild = 0;
    game_data.guild.fighters_guild_quota_recurring = 0;
    game_data.guild.mages_guild_quota_recurring = 0;
    game_data.guild.thieves_guild_quota_recurring = 0;

    if (guild_name == "mages")
    {
        game_data.guild.joining_mages_guild = 1000;
        game_data.guild.belongs_to_mages_guild = 1;
    }
    else if (guild_name == "fighters")
    {
        game_data.guild.joining_fighters_guild = 1000;
        game_data.guild.belongs_to_fighters_guild = 1;
    }
    else if (guild_name == "thieves")
    {
        game_data.guild.joining_thieves_guild = 1000;
        game_data.guild.belongs_to_thieves_guild = 1;
    }
}

/**
 * @luadoc
 *
 * Returns the player's title for the given ranking.
 * @tparam num ranking_id
 */
std::string LuaApiWorld::ranking_title(int ranking_id)
{
    return ranktitle(ranking_id);
}

/**
 * @luadoc
 *
 * Modifies the player's rank in a given ranking.
 * @tparam num ranking_id
 * @tparam num amount
 * @tparam num min
 */
void LuaApiWorld::modify_ranking(int ranking_id, int amount, int min)
{
    modrank(ranking_id, amount, min);
}

/**
 * @luadoc
 *
 * Generates a random title.
 * @tparam Enums.RandomTitleType The type of title to generate.
 */
std::string LuaApiWorld::random_title(const EnumString& type)
{
    auto type_value = LuaEnums::RandomTitleTypeTable.ensure_from_string(type);
    return random_title(type_value);
}

void LuaApiWorld::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, deferred_event_id);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, add_deferred_event);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, belongs_to_guild);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, join_guild);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, ranking_title);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, modify_ranking);
    LUA_API_BIND_FUNCTION(api_table, LuaApiWorld, random_title);

    /**
     * @luadoc data field LuaGameData
     *
     * [R] Data for the current game save.
     */
    api_table.set("data", sol::property(&game_data));
}

} // namespace lua
} // namespace elona
