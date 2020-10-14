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
#include "modules/module_Input.cpp"
#include "modules/module_Internal.cpp"
#include "modules/module_Inventory.cpp"
#include "modules/module_Item.cpp"
#include "modules/module_JSON5.cpp"
#include "modules/module_Log.cpp"
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
#define ELONA_LUA_API_BIND_MODULE(ModuleName) \
    { \
        sol::table api_table = core.create_named(#ModuleName); \
        module_##ModuleName::bind(api_table); \
    }
#define ELONA_LUA_API_BIND_HIDDEN_MODULE(ModuleName) \
    { \
        sol::table api_table = core.create_named("__" #ModuleName); \
        module_##ModuleName::bind(api_table); \
    }

    ELONA_LUA_API_BIND_MODULE(Animation);
    ELONA_LUA_API_BIND_MODULE(Calc);
    ELONA_LUA_API_BIND_MODULE(Chara);
    ELONA_LUA_API_BIND_MODULE(Config);
    ELONA_LUA_API_BIND_MODULE(Console);
    ELONA_LUA_API_BIND_MODULE(Data);
    ELONA_LUA_API_BIND_MODULE(Debug);
    ELONA_LUA_API_BIND_MODULE(Enchantment);
    ELONA_LUA_API_BIND_MODULE(Env);
    ELONA_LUA_API_BIND_MODULE(FOV);
    ELONA_LUA_API_BIND_MODULE(GUI);
    ELONA_LUA_API_BIND_MODULE(Input);
    ELONA_LUA_API_BIND_MODULE(Internal);
    ELONA_LUA_API_BIND_MODULE(Inventory);
    ELONA_LUA_API_BIND_MODULE(Item);
    ELONA_LUA_API_BIND_MODULE(JSON5);
    ELONA_LUA_API_BIND_MODULE(Magic);
    ELONA_LUA_API_BIND_MODULE(Map);
    ELONA_LUA_API_BIND_MODULE(Pos);
    ELONA_LUA_API_BIND_MODULE(Rand);
    ELONA_LUA_API_BIND_MODULE(Skill);
    ELONA_LUA_API_BIND_MODULE(Trait);
    ELONA_LUA_API_BIND_MODULE(Wish);
    ELONA_LUA_API_BIND_MODULE(World);

    // TODO
    ELONA_LUA_API_BIND_HIDDEN_MODULE(Log);

#undef ELONA_LUA_API_BIND_MODULE
}

} // namespace elona::lua::api::modules
