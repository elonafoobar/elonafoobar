#include "lua_class_game_data.hpp"

namespace elona
{
namespace lua
{

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

    lua.set_usertype("LuaGameData", LuaGameData);
}

} // namespace lua
} // namespace elona
