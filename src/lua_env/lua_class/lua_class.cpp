#include "lua_class.hpp"

namespace elona
{
namespace lua
{

void LuaApiClasses::bind(sol::state& lua)
{
    LuaCharacter::bind(lua);
    LuaPosition::bind(lua);
    LuaItem::bind(lua);
}

void LuaApiClasses::bind_api(sol::state& lua, sol::table& core)
{
    core["LuaPosition"] = lua["LuaPosition"];
}

}
}
