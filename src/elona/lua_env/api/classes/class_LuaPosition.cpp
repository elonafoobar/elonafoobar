#include <sstream>

#include "../../../position.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Position)



/**
 * @luadoc
 *
 * Represents a 2-dimensional position. Intended for representing tile
 * locations.
 */
namespace elona::lua::api::classes::class_LuaPosition
{

void bind(sol::state& lua)
{
    /**
     * @luadoc new function
     *
     * Constructs a new LuaPosition.
     * @usage local LuaPosition = require("core.LuaPosition")
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

} // namespace elona::lua::api::classes::class_LuaPosition
