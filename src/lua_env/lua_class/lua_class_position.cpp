#include "lua_class_position.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{

void LuaPosition::bind(sol::state& lua)
{
    sol::usertype<Position> LuaPosition(
        sol::constructors<Position(), Position(int, int)>(),
        "x",
        &Position::x,
        "y",
        &Position::y);

    lua.set_usertype("LuaPosition", LuaPosition);
}

} // namespace lua
} // namespace elona
