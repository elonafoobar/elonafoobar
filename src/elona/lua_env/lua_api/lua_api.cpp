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
#include "lua_api_math.cpp"
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

void LuaApi::bind(sol::table& game)
{
    LUA_API_BIND(game, Animation);
    LUA_API_BIND(game, Calc);
    LUA_API_BIND(game, Chara);
    LUA_API_BIND(game, Config);
    LUA_API_BIND(game, Console);
    LUA_API_BIND(game, Data);
    LUA_API_BIND(game, Debug);
    LUA_API_BIND(game, Env);
    LUA_API_BIND(game, FOV);
    LUA_API_BIND(game, GUI);
    LUA_API_BIND(game, I18N);
    LUA_API_BIND(game, Input);
    LUA_API_BIND(game, Internal);
    LUA_API_BIND(game, Item);
    LUA_API_BIND(game, Magic);
    LUA_API_BIND(game, Map);
    LUA_API_BIND(game, Math);
    LUA_API_BIND(game, Pos);
    LUA_API_BIND(game, Rand);
    LUA_API_BIND(game, Skill);
    LUA_API_BIND(game, Trait);
    LUA_API_BIND(game, Wish);
    LUA_API_BIND(game, World);

    // TODO: move it to lib module.
    LUA_API_BIND(game, JSON5);
}

#undef LUA_API_BIND

} // namespace lua
} // namespace elona
