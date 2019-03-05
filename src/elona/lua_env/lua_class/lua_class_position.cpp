#include "lua_class_position.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{

void LuaPosition::bind(sol::state& lua)
{
    sol::usertype<Position> LuaPosition(
        /**
         * @luadoc new function
         *
         * Constructs a new LuaPosition.
         * @usage local LuaPosition = Elona.require("LuaPosition")
         * local pos = LuaPosition.new()
         */
        sol::constructors<Position(), Position(int, int)>(),


        /**
         * @luadoc x field num
         *
         * [RW] The X coordinate of this position.
         */
        "x",
        &Position::x,

        /**
         * @luadoc y field num
         *
         * [RW] The Y coordinate of this position.
         */
        "y",
        &Position::y);

    lua.set_usertype("LuaPosition", LuaPosition);
}

} // namespace lua
} // namespace elona
