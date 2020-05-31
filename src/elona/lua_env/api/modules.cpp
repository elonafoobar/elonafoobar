// @noluadoc
#include "modules.hpp"

#include "modules/module_Animation.cpp"
#include "modules/module_Calc.cpp"
#include "modules/module_Chara.cpp"
#include "modules/module_Config.cpp"
#include "modules/module_Console.cpp"
#include "modules/module_Data.cpp"
#include "modules/module_Debug.cpp"
#include "modules/module_Enchantment.cpp"
#include "modules/module_Env.cpp"
#include "modules/module_FOV.cpp"
#include "modules/module_GUI.cpp"
#include "modules/module_I18N.cpp"
#include "modules/module_Input.cpp"
#include "modules/module_Internal.cpp"
#include "modules/module_Item.cpp"
#include "modules/module_JSON5.cpp"
#include "modules/module_Magic.cpp"
#include "modules/module_Map.cpp"
#include "modules/module_Pos.cpp"
#include "modules/module_Rand.cpp"
#include "modules/module_Skill.cpp"
#include "modules/module_Trait.cpp"
#include "modules/module_Wish.cpp"
#include "modules/module_World.cpp"



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
    LUA_API_BIND(core, Enchantment);
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
