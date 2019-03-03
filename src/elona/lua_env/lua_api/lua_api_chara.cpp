#include "lua_api_chara.hpp"
#include "../../character.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../lua_env/interface.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Checks if a character is alive.
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is alive
 */
bool LuaApiChara::is_alive(LuaCharacterHandle chara)
{
    if (!lua::lua->get_handle_manager().handle_is_valid(chara))
    {
        return false;
    }

    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return chara_ref.state() == Character::State::alive;
}

/**
 * @luadoc
 *
 * Checks if a character is the player (has index 0).
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is the player
 */
bool LuaApiChara::is_player(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return chara_ref.index == 0;
}

/**
 * @luadoc
 *
 * Checks if a character is a member of the player's party (has index < 16 and
 * @tparam LuaCharacter chara (const) a character
 * @treturn bool true if the character is in the player's party
 */
bool LuaApiChara::is_ally(LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return !LuaApiChara::is_player(chara) && chara_ref.index <= 16;
}

/**
 * @luadoc
 *
 * Returns the number of other characters in the current map.
 */
int LuaApiChara::count()
{
    return game_data.crowd_density;
}

/**
 * @luadoc
 *
 * Gets a flag on a character.
 * @tparam LuaCharacter chara (const) the character to get the flag from
 * @tparam Enums.CharaFlag flag the flag to get
 */
bool LuaApiChara::flag(LuaCharacterHandle chara, const EnumString& flag)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    int flag_value = LuaEnums::CharaFlagTable.ensure_from_string(flag);
    return chara_ref._flags[flag_value] == 1;
}

/**
 * @luadoc
 *
 * Returns a reference to the player. They might not be alive.
 * @treturn LuaCharacter (mut) a reference to the player
 */
sol::optional<LuaCharacterHandle> LuaApiChara::player()
{
    if (elona::cdata.player().state() == Character::State::empty)
    {
        return sol::nullopt;
    }
    else
    {
        return lua::handle(elona::cdata.player());
    }
}

sol::optional<LuaCharacterHandle> LuaApiChara::create(
    const Position& position,
    int id)
{
    return LuaApiChara::create_xy(position.x, position.y, id);
}

sol::optional<LuaCharacterHandle> LuaApiChara::create_xy(int x, int y, int id)
{
    elona::flt();
    if (elona::chara_create(-1, id, x, y) != 0)
    {
        return lua::handle(elona::cdata[elona::rc]);
    }
    else
    {
        return sol::nullopt;
    }
}

/**
 * @luadoc create
 *
 * Attempts to create a character at a given position.
 * Returns the character if creation succeeded, nil otherwise.
 * @tparam LuaPosition position (const) position to create the character at
 * @tparam string id the character prototype ID
 * @treturn[1] LuaCharacter the created character
 * @treturn[2] nil
 */
sol::optional<LuaCharacterHandle> LuaApiChara::create_from_id(
    const Position& position,
    const std::string& id)
{
    return LuaApiChara::create_from_id_xy(position.x, position.y, id);
}

sol::optional<LuaCharacterHandle>
LuaApiChara::create_from_id_xy(int x, int y, const std::string& id)
{
    auto data = the_character_db[id];
    if (!data)
    {
        throw sol::error("No such character " + id);
    }
    return LuaApiChara::create_xy(x, y, data->id);
}

/**
 * @luadoc
 *
 * Obtains the number of times the character type has been killed.
 * @tparam string id the character prototype ID
 */
int LuaApiChara::kill_count(const std::string& id)
{
    auto data = the_character_db[id];
    if (!data)
    {
        return 0;
    }
    return npcmemory(0, data->id);
}

void LuaApiChara::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_alive);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_player);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, is_ally);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, count);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, flag);
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, player);
    api_table.set_function(
        "create",
        sol::overload(
            LuaApiChara::create,
            LuaApiChara::create_xy,
            LuaApiChara::create_from_id,
            LuaApiChara::create_from_id_xy));
    LUA_API_BIND_FUNCTION(api_table, LuaApiChara, kill_count);
}

} // namespace lua
} // namespace elona
