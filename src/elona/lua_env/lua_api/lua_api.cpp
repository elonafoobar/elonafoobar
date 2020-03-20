// @noluadoc
#include "lua_api.hpp"

#include "lua_api_animation.cpp"
#include "lua_api_calc.cpp"
#include "lua_api_chara.cpp"
#include "lua_api_config.cpp"
#include "lua_api_console.cpp"
#include "lua_api_data.cpp"
#include "lua_api_debug.cpp"
#include "lua_api_env.cpp"
#include "lua_api_fov.cpp"
#include "lua_api_gui.cpp"
#include "lua_api_i18n.cpp"
#include "lua_api_input.cpp"
#include "lua_api_internal.cpp"
#include "lua_api_item.cpp"
#include "lua_api_json5.cpp"
#include "lua_api_magic.cpp"
#include "lua_api_map.cpp"
#include "lua_api_pos.cpp"
#include "lua_api_rand.cpp"
#include "lua_api_skill.cpp"
#include "lua_api_trait.cpp"
#include "lua_api_wish.cpp"
#include "lua_api_world.cpp"



namespace elona
{
namespace lua
{

#define LUA_API_BIND(top_level_module, name) \
    { \
        sol::table table = top_level_module.create_named(#name); \
        LuaApi##name::bind(table); \
    }

void LuaApi::bind(sol::table& core)
{
    LUA_API_BIND(core, Animation);
    LUA_API_BIND(core, Calc);
    LUA_API_BIND(core, Chara);
    LUA_API_BIND(core, Config);
    LUA_API_BIND(core, Console);
    LUA_API_BIND(core, Data);
    LUA_API_BIND(core, Debug);
    LUA_API_BIND(core, Env);
    LUA_API_BIND(core, FOV);
    LUA_API_BIND(core, GUI);
    LUA_API_BIND(core, I18N);
    LUA_API_BIND(core, Input);
    LUA_API_BIND(core, Internal);
    LUA_API_BIND(core, Item);
    LUA_API_BIND(core, JSON5);
    LUA_API_BIND(core, Magic);
    LUA_API_BIND(core, Map);
    LUA_API_BIND(core, Pos);
    LUA_API_BIND(core, Rand);
    LUA_API_BIND(core, Skill);
    LUA_API_BIND(core, Trait);
    LUA_API_BIND(core, Wish);
    LUA_API_BIND(core, World);
}

#undef LUA_API_BIND

} // namespace lua
} // namespace elona
