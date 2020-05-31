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



namespace elona::lua::api::modules
{

void bind(sol::table core)
{
#define ELONA_LUA_API_BIND(ModuleName) \
    { \
        sol::table api_table = core.create_named(#ModuleName); \
        module_##ModuleName::bind(api_table); \
    }

    ELONA_LUA_API_BIND(Animation);
    ELONA_LUA_API_BIND(Calc);
    ELONA_LUA_API_BIND(Chara);
    ELONA_LUA_API_BIND(Config);
    ELONA_LUA_API_BIND(Console);
    ELONA_LUA_API_BIND(Data);
    ELONA_LUA_API_BIND(Debug);
    ELONA_LUA_API_BIND(Enchantment);
    ELONA_LUA_API_BIND(Env);
    ELONA_LUA_API_BIND(FOV);
    ELONA_LUA_API_BIND(GUI);
    ELONA_LUA_API_BIND(I18N);
    ELONA_LUA_API_BIND(Input);
    ELONA_LUA_API_BIND(Internal);
    ELONA_LUA_API_BIND(Item);
    ELONA_LUA_API_BIND(JSON5);
    ELONA_LUA_API_BIND(Magic);
    ELONA_LUA_API_BIND(Map);
    ELONA_LUA_API_BIND(Pos);
    ELONA_LUA_API_BIND(Rand);
    ELONA_LUA_API_BIND(Skill);
    ELONA_LUA_API_BIND(Trait);
    ELONA_LUA_API_BIND(Wish);
    ELONA_LUA_API_BIND(World);

#undef ELONA_LUA_API_BIND
}

} // namespace elona::lua::api::modules
