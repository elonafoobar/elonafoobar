#include "lua_class_position.hpp"
#include "../../position.hpp"

namespace elona
{
namespace lua
{

void LuaPosition::bind(sol::state& lua)
{
    sol::usertype<position_t> LuaPosition(
        sol::constructors<position_t(), position_t(int, int)>(),
        "x",
        &position_t::x,
        "y",
        &position_t::y);

    lua.set_usertype("LuaPosition", LuaPosition);
}

} // namespace lua
} // namespace elona
