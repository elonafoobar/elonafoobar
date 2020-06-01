#include "class_LuaPosition.hpp"

#include <sstream>

#include "../../../position.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Position)



namespace elona
{
namespace lua
{

void LuaPosition::bind(sol::state& lua)
{
    /**
     * @luadoc new function
     *
     * Constructs a new LuaPosition.
     * @usage local LuaPosition = ELONA.require("core.LuaPosition")
     * local pos = LuaPosition.new()
     */
    auto LuaPosition = lua.new_usertype<Position>(
        "LuaPosition", sol::constructors<Position(), Position(int, int)>());

    /**
     * @luadoc x field num
     *
     * [RW] The X coordinate of this position.
     */
    LuaPosition.set("x", &Position::x);

    /**
     * @luadoc y field num
     *
     * [RW] The Y coordinate of this position.
     */
    LuaPosition.set("y", &Position::y);

    LuaPosition.set(sol::meta_function::to_string, &Position::to_string);
}

} // namespace lua
} // namespace elona
