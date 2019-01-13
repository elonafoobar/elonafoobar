#include "lua_api_chara.hpp"
#include "../../character.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../lua_env/interface.hpp"

namespace elona
{
namespace lua
{

bool LuaApiChara::is_alive(LuaCharacterHandle handle)
{
    if (!lua::lua->get_handle_manager().handle_is_valid(handle))
    {
        return false;
    }

    auto& LuaApiChara =
        lua::lua->get_handle_manager().get_ref<Character>(handle);
    return LuaApiChara.state() == Character::State::alive;
}

bool LuaApiChara::is_player(LuaCharacterHandle handle)
{
    auto& LuaApiChara =
        lua::lua->get_handle_manager().get_ref<Character>(handle);
    return LuaApiChara.index == 0;
}

bool LuaApiChara::is_ally(LuaCharacterHandle handle)
{
    auto& LuaApiChara =
        lua::lua->get_handle_manager().get_ref<Character>(handle);
    return !LuaApiChara::is_player(handle) && LuaApiChara.index <= 16;
}

int LuaApiChara::count()
{
    return game_data.crowd_density;
}

bool LuaApiChara::flag(LuaCharacterHandle handle, const EnumString& flag_name)
{
    auto& LuaApiChara =
        lua::lua->get_handle_manager().get_ref<Character>(handle);
    int flag = LuaEnums::CharaFlagTable.ensure_from_string(flag_name);
    return LuaApiChara._flags[flag] == 1;
}

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
