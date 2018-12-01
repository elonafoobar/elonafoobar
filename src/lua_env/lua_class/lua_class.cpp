#include "lua_class.hpp"

#include "lua_class_ability.hpp"
#include "lua_class_character.hpp"
#include "lua_class_item.hpp"
#include "lua_class_position.hpp"

namespace elona
{
namespace lua
{

void LuaApiClasses::bind(sol::state& lua)
{
    LuaAbility::bind(lua);
    LuaCharacter::bind(lua);
    LuaPosition::bind(lua);
    LuaItem::bind(lua);
}

void LuaApiClasses::bind_api(sol::state& lua, sol::table& core)
{
    core["LuaPosition"] = lua["LuaPosition"];
}

} // namespace lua
} // namespace elona
