#include "../../../deferred_event.hpp"
#include "../../../game.hpp"
#include "../../../text.hpp"
#include "../../../world.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with the state of the game world.
 */
namespace elona::lua::api::modules::module_World
{

/**
 * @luadoc deferred_event_id
 *
 * Gets the ID of the next deferred event that will run.
 *
 * @treturn string
 * @treturn nil
 */
sol::optional<std::string> World_deferred_event_id()
{
    if (const auto ret = deferred_event_processing_event())
        return ret->get();
    else
        return sol::nullopt;
}



/**
 * @luadoc add_deferred_event
 *
 * Adds a deferred event.
 *
 * @tparam string event_id the event id
 * @tparam[opt] num priority the event priority. The larger it is, the earlier
 * the event is fired. If not given, 0 is used.
 * @tparam[opt] table ext extra parameters.
 */
void World_add_deferred_event(
    const std::string& event_id,
    sol::optional<lua_int> priority,
    sol::table ext)
{
    deferred_event_add(
        DeferredEvent{data::InstanceId{event_id}, priority.value_or(0), ext});
}



/**
 * @luadoc belongs_to_guild
 *
 * Returns true if the player is part of the provided guild.
 *
 * @tparam string guild_name One of "mages", "fighters" or "thieves"
 */
bool World_belongs_to_guild(const std::string& guild_name)
{
    if (guild_name == "mages")
    {
        return game()->guild.belongs_to_mages_guild == 1;
    }
    else if (guild_name == "fighters")
    {
        return game()->guild.belongs_to_fighters_guild == 1;
    }
    else if (guild_name == "thieves")
    {
        return game()->guild.belongs_to_thieves_guild == 1;
    }

    return false;
}



/**
 * @luadoc join_guild
 *
 * Sets the player's guild affiliation and resets guild quotas.
 *
 * @tparam string guild_name One of "mages", "fighters" or "thieves"
 */
void World_join_guild(const std::string& guild_name)
{
    game()->guild.belongs_to_thieves_guild = 0;
    game()->guild.belongs_to_fighters_guild = 0;
    game()->guild.belongs_to_mages_guild = 0;
    game()->guild.mages_guild_quota = 0;
    game()->guild.thieves_guild_quota = 0;
    game()->guild.joining_mages_guild = 0;
    game()->guild.joining_thieves_guild = 0;
    game()->guild.joining_fighters_guild = 0;
    game()->guild.fighters_guild_quota_recurring = 0;
    game()->guild.mages_guild_quota_recurring = 0;
    game()->guild.thieves_guild_quota_recurring = 0;

    if (guild_name == "mages")
    {
        game()->guild.joining_mages_guild = 1000;
        game()->guild.belongs_to_mages_guild = 1;
    }
    else if (guild_name == "fighters")
    {
        game()->guild.joining_fighters_guild = 1000;
        game()->guild.belongs_to_fighters_guild = 1;
    }
    else if (guild_name == "thieves")
    {
        game()->guild.joining_thieves_guild = 1000;
        game()->guild.belongs_to_thieves_guild = 1;
    }
}



/**
 * @luadoc ranking_title
 *
 * Returns the player's title for the given ranking.
 *
 * @tparam num ranking_id
 */
std::string World_ranking_title(int ranking_id)
{
    return ranktitle(ranking_id);
}



/**
 * @luadoc modify_ranking
 *
 * Modifies the player's rank in a given ranking.
 *
 * @tparam num ranking_id
 * @tparam num amount
 * @tparam num min
 */
void World_modify_ranking(int ranking_id, int amount, int min)
{
    modrank(ranking_id, amount, min);
}



/**
 * @luadoc random_title
 *
 * Generates a random title.
 *
 * @tparam Enums.RandomTitleType The type of title to generate.
 */
std::string World_random_title(const EnumString& type)
{
    auto type_value = LuaEnums::RandomTitleTypeTable.ensure_from_string(type);
    return random_title(type_value);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("deferred_event_id", World_deferred_event_id);
    ELONA_LUA_API_BIND_FUNCTION("add_deferred_event", World_add_deferred_event);
    ELONA_LUA_API_BIND_FUNCTION("belongs_to_guild", World_belongs_to_guild);
    ELONA_LUA_API_BIND_FUNCTION("join_guild", World_join_guild);
    ELONA_LUA_API_BIND_FUNCTION("ranking_title", World_ranking_title);
    ELONA_LUA_API_BIND_FUNCTION("modify_ranking", World_modify_ranking);
    ELONA_LUA_API_BIND_FUNCTION("random_title", World_random_title);

    /**
     * @luadoc data field LuaGameData
     *
     * [R] Data for the current game save.
     */
    api_table.set("data", game().get());

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_World
