#include "lua_api.hpp"

namespace elona
{
namespace lua
{

void LuaApi::bind(sol::table& core)
{
    LUA_API_BIND(core, Chara);
    LUA_API_BIND(core, Pos);
    LUA_API_BIND(core, World);
    LUA_API_BIND(core, FOV);
    LUA_API_BIND(core, Magic);
    LUA_API_BIND(core, Rand);
    LUA_API_BIND(core, Item);
    LUA_API_BIND(core, Skill);
    LUA_API_BIND(core, Trait);
    LUA_API_BIND(core, Input);
    LUA_API_BIND(core, GUI);
    LUA_API_BIND(core, I18N);
    LUA_API_BIND(core, Map);
    LUA_API_BIND(core, Animation);
    LUA_API_BIND(core, Debug);
}

} // namespace lua
} // namespace elona
