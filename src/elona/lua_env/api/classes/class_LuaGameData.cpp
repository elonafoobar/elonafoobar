#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Game)



/**
 * @luadoc
 *
 * Contains parameters for the current game save.
 */
namespace elona::lua::api::classes::class_LuaGameData
{

#define ELONA_LUA_GUILD_PROPERTY(field) \
    sol::property( \
        [](Game& it) { return it.guild.field; }, \
        [](Game& it, int value) { it.guild.field = value; })

#define ELONA_LUA_GUILD_FLAG(field) \
    sol::property( \
        [](Game& it) { return it.guild.field == 1; }, \
        [](Game& it, bool value) { it.guild.field = value ? 1 : 0; })


void bind(sol::state& lua)
{
    auto LuaGameData =
        lua.new_usertype<Game>("LuaGameData", sol::no_constructor);

    /**
     * @luadoc holy_well_count field num
     *
     * [RW] The amount of the water which the the holy well has.
     */
    LuaGameData.set("holy_well_count", &Game::holy_well_count);

    /**
     * @luadoc home_scale field num
     *
     * [RW] The player's home scale.
     */
    LuaGameData.set("home_scale", &Game::home_scale);

    /**
     * @luadoc initial_cart_limit field num
     *
     * [RW] The player's initial cargo capacity.
     */
    LuaGameData.set("initial_cart_limit", &Game::initial_cart_limit);

    /**
     * @luadoc current_cart_limit field num
     *
     * [RW] The player's maximum cargo capacity.
     */
    LuaGameData.set("current_cart_limit", &Game::current_cart_limit);

    /**
     * @luadoc ranks field table
     */
    LuaGameData.set("ranks", &Game::ranks);

    /**
     * @luadoc left_bill field num
     *
     * [RW] The number of unpaid bills the player owns.
     */
    LuaGameData.set("left_bill", &Game::left_bill);

    /**
     * @luadoc date field LuaDateTime
     *
     * [R] The current date and time.
     */
    LuaGameData.set("date", &Game::date);


    /**
     * @luadoc belongs_to_mages_guild field num
     */
    LuaGameData.set(
        "belongs_to_mages_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_mages_guild));

    /**
     * @luadoc belongs_to_fighters_guild field num
     */
    LuaGameData.set(
        "belongs_to_fighters_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_fighters_guild));

    /**
     * @luadoc belongs_to_thieves_guild field num
     */
    LuaGameData.set(
        "belongs_to_thieves_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_thieves_guild));

    /**
     * @luadoc mages_guild_quota field num
     */
    LuaGameData.set(
        "mages_guild_quota", ELONA_LUA_GUILD_PROPERTY(mages_guild_quota));

    /**
     * @luadoc fighters_guild_quota field num
     */
    LuaGameData.set(
        "fighters_guild_quota", ELONA_LUA_GUILD_PROPERTY(fighters_guild_quota));

    /**
     * @luadoc fighters_guild_target field num
     */
    LuaGameData.set(
        "fighters_guild_target",
        ELONA_LUA_GUILD_PROPERTY(fighters_guild_target));

    /**
     * @luadoc thieves_guild_quota field num
     */
    LuaGameData.set(
        "thieves_guild_quota", ELONA_LUA_GUILD_PROPERTY(thieves_guild_quota));

    /**
     * @luadoc joining_mages_guild field num
     */
    LuaGameData.set(
        "joining_mages_guild", ELONA_LUA_GUILD_PROPERTY(joining_mages_guild));

    /**
     * @luadoc joining_fighters_guild field num
     */
    LuaGameData.set(
        "joining_fighters_guild",
        ELONA_LUA_GUILD_PROPERTY(joining_fighters_guild));

    /**
     * @luadoc joining_thieves_guild field num
     */
    LuaGameData.set(
        "joining_thieves_guild",
        ELONA_LUA_GUILD_PROPERTY(joining_thieves_guild));

    /**
     * @luadoc mages_guild_quota_recurring field bool
     */
    LuaGameData.set(
        "mages_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(mages_guild_quota_recurring));

    /**
     * @luadoc fighters_guild_quota_recurring field bool
     */
    LuaGameData.set(
        "fighters_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(fighters_guild_quota_recurring));

    /**
     * @luadoc thieves_guild_quota_recurring field bool
     */
    LuaGameData.set(
        "thieves_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(thieves_guild_quota_recurring));
}

} // namespace elona::lua::api::classes::class_LuaGameData
