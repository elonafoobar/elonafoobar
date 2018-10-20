#include "lua_api_chara.hpp"
#include "../../character.hpp"
#include "../../lua_env/enums/enums.hpp"

namespace elona
{
namespace lua
{

bool Chara::is_alive(LuaCharacterHandle handle)
{
    if (!lua::lua->get_handle_manager().handle_is_valid(handle))
    {
        return false;
    }

    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    return chara.state() == Character::State::alive;
}

bool Chara::is_player(LuaCharacterHandle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    return chara.index == 0;
}

bool Chara::is_ally(LuaCharacterHandle handle)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    return !Chara::is_player(handle) && chara.index <= 16;
}

int Chara::count()
{
    return game_data.crowd_density;
}

bool Chara::flag(LuaCharacterHandle handle, const EnumString& flag_name)
{
    auto& chara = lua::lua->get_handle_manager().get_ref<Character>(handle);
    int flag = LuaEnums::CharaFlagTable.ensure_from_string(flag_name);
    return chara._flags[flag] == 1;
}

sol::optional<LuaCharacterHandle> Chara::player()
{
    if (elona::cdata.player().state() == Character::State::empty)
    {
        return sol::nullopt;
    }
    else
    {
        LuaCharacterHandle handle =
            lua::lua->get_handle_manager().get_handle(elona::cdata.player());
        return handle;
    }
}

sol::optional<LuaCharacterHandle> Chara::create(
    const Position& position,
    int id)
{
    return Chara::create_xy(position.x, position.y, id);
}

sol::optional<LuaCharacterHandle> Chara::create_xy(int x, int y, int id)
{
    elona::flt();
    if (elona::chara_create(-1, id, x, y) != 0)
    {
        LuaCharacterHandle handle =
            lua::lua->get_handle_manager().get_handle(elona::cdata[elona::rc]);
        return handle;
    }
    else
    {
        return sol::nullopt;
    }
}

sol::optional<LuaCharacterHandle> Chara::create_from_id(
    const Position& position,
    const std::string& id)
{
    return Chara::create_from_id_xy(position.x, position.y, id);
}

sol::optional<LuaCharacterHandle>
Chara::create_from_id_xy(int x, int y, const std::string& id)
{
    auto data = the_character_db[id];
    if (!data)
    {
        throw sol::error("No such character " + id);
    }
    return Chara::create_xy(x, y, data->id);
}

void Chara::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Chara, is_alive);
    LUA_API_BIND_FUNCTION(api_table, Chara, is_player);
    LUA_API_BIND_FUNCTION(api_table, Chara, is_ally);
    LUA_API_BIND_FUNCTION(api_table, Chara, count);
    LUA_API_BIND_FUNCTION(api_table, Chara, flag);
    LUA_API_BIND_FUNCTION(api_table, Chara, player);
    api_table.set_function(
        "create",
        sol::overload(
            Chara::create,
            Chara::create_xy,
            Chara::create_from_id,
            Chara::create_from_id_xy));
}

} // namespace lua
} // namespace elona
