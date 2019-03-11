#include "lua_class_game_data.hpp"

namespace elona
{
namespace lua
{

#define ELONA_LUA_GUILD_PROPERTY(field) \
    sol::property( \
        [](GameData& it) { return it.guild.field; }, \
        [](GameData& it, int value) { it.guild.field = value; })

#define ELONA_LUA_GUILD_FLAG(field) \
    sol::property( \
        [](GameData& it) { return it.guild.field == 1; }, \
        [](GameData& it, bool value) { it.guild.field = value ? 1 : 0; })


void LuaGameData::bind(sol::state& lua)
{
    auto LuaGameData = lua.create_simple_usertype<GameData>();
    LuaGameData.set("new", sol::no_constructor);

    /**
     * @luadoc initial_cart_limit field num
     *
     * [RW] The player's initial cargo capacity.
     */
    LuaGameData.set("initial_cart_limit", &GameData::initial_cart_limit);

    /**
     * @luadoc current_cart_limit field num
     *
     * [RW] The player's maximum cargo capacity.
     */
    LuaGameData.set("current_cart_limit", &GameData::current_cart_limit);

    /**
     * @luadoc field ranks table
     */
    LuaGameData.set("ranks", &GameData::ranks);

    /**
     * @luadoc field left_bill num
     *
     * [RW] The number of unpaid bills the player owns.
     */
    LuaGameData.set("left_bill", &GameData::left_bill);

    /**
     * @luadoc field date LuaDate
     *
     * [R] The current date.
     */
    LuaGameData.set("date", &GameData::date);


    /**
     * @luadoc field belongs_to_mages_guild num
     */
    LuaGameData.set(
        "belongs_to_mages_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_mages_guild));

    /**
     * @luadoc field belongs_to_fighters_guild num
     */
    LuaGameData.set(
        "belongs_to_fighters_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_fighters_guild));

    /**
     * @luadoc field belongs_to_thieves_guild num
     */
    LuaGameData.set(
        "belongs_to_thieves_guild",
        ELONA_LUA_GUILD_PROPERTY(belongs_to_thieves_guild));

    /**
     * @luadoc field mages_guild_quota num
     */
    LuaGameData.set(
        "mages_guild_quota", ELONA_LUA_GUILD_PROPERTY(mages_guild_quota));

    /**
     * @luadoc field fighters_guild_quota num
     */
    LuaGameData.set(
        "fighters_guild_quota", ELONA_LUA_GUILD_PROPERTY(fighters_guild_quota));

    /**
     * @luadoc field fighters_guild_target num
     */
    LuaGameData.set(
        "fighters_guild_target",
        ELONA_LUA_GUILD_PROPERTY(fighters_guild_target));

    /**
     * @luadoc field thieves_guild_quota num
     */
    LuaGameData.set(
        "thieves_guild_quota", ELONA_LUA_GUILD_PROPERTY(thieves_guild_quota));

    /**
     * @luadoc field joining_mages_guild num
     */
    LuaGameData.set(
        "joining_mages_guild", ELONA_LUA_GUILD_PROPERTY(joining_mages_guild));

    /**
     * @luadoc field joining_fighters_guild num
     */
    LuaGameData.set(
        "joining_fighters_guild",
        ELONA_LUA_GUILD_PROPERTY(joining_fighters_guild));

    /**
     * @luadoc field joining_thieves_guild num
     */
    LuaGameData.set(
        "joining_thieves_guild",
        ELONA_LUA_GUILD_PROPERTY(joining_thieves_guild));

    /**
     * @luadoc field mages_guild_quota_recurring bool
     */
    LuaGameData.set(
        "mages_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(mages_guild_quota_recurring));

    /**
     * @luadoc field fighters_guild_quota_recurring bool
     */
    LuaGameData.set(
        "fighters_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(fighters_guild_quota_recurring));

    /**
     * @luadoc field thieves_guild_quota_recurring bool
     */
    LuaGameData.set(
        "thieves_guild_quota_recurring",
        ELONA_LUA_GUILD_FLAG(thieves_guild_quota_recurring));


    lua.set_usertype("LuaGameData", LuaGameData);
}

} // namespace lua
} // namespace elona
