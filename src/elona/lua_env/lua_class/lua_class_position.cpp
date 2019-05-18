#include "lua_class_position.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{

void LuaPosition::bind(sol::state& lua)
{
    auto LuaPosition = lua.create_simple_usertype<Position>();

    /**
     * @luadoc new function
     *
     * Constructs a new LuaPosition.
     * @usage local LuaPosition = Elona.require("LuaPosition")
     * local pos = LuaPosition.new()
     */
    LuaPosition.set("new", sol::constructors<Position(), Position(int, int)>());

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

    lua.set_usertype("LuaPosition", LuaPosition);
}

} // namespace lua
} // namespace elona
