#include "lua_api.hpp"

#include "lua_api_animation.cpp"
#include "lua_api_chara.cpp"
#include "lua_api_debug.cpp"
#include "lua_api_fov.cpp"
#include "lua_api_gui.cpp"
#include "lua_api_i18n.cpp"
#include "lua_api_input.cpp"
#include "lua_api_item.cpp"
#include "lua_api_magic.cpp"
#include "lua_api_map.cpp"
#include "lua_api_math.cpp"
#include "lua_api_pos.cpp"
#include "lua_api_rand.cpp"
#include "lua_api_skill.cpp"
#include "lua_api_trait.cpp"
#include "lua_api_world.cpp"

namespace elona
{
namespace lua
{

#define LUA_API_BIND(core, name) \
    { \
        sol::table table = core.create_named(#name); \
        name::bind(table); \
    }

void LuaApi::bind(sol::table& core)
{
    LUA_API_BIND(core, LuaApiChara);
    LUA_API_BIND(core, LuaApiPos);
    LUA_API_BIND(core, LuaApiWorld);
    LUA_API_BIND(core, LuaApiFOV);
    LUA_API_BIND(core, LuaApiMagic);
    LUA_API_BIND(core, LuaApiRand);
    LUA_API_BIND(core, LuaApiItem);
    LUA_API_BIND(core, LuaApiSkill);
    LUA_API_BIND(core, LuaApiTrait);
    LUA_API_BIND(core, LuaApiInput);
    LUA_API_BIND(core, LuaApiGUI);
    LUA_API_BIND(core, LuaApiI18N);
    LUA_API_BIND(core, LuaApiMap);
    LUA_API_BIND(core, LuaApiAnimation);
    LUA_API_BIND(core, LuaApiDebug);
}

#undef LUA_API_BIND

} // namespace lua
} // namespace elona
