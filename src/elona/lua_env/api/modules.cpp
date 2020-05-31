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
#define ELONA_BIND_API(ModuleName) \
    { \
        sol::table api_table = core.create_named(#ModuleName); \
        LuaApi##ModuleName::bind(api_table); \
    }

    ELONA_BIND_API(Animation);
    ELONA_BIND_API(Calc);
    ELONA_BIND_API(Chara);
    ELONA_BIND_API(Config);
    ELONA_BIND_API(Console);
    ELONA_BIND_API(Data);
    ELONA_BIND_API(Debug);
    ELONA_BIND_API(Enchantment);
    ELONA_BIND_API(Env);
    ELONA_BIND_API(FOV);
    ELONA_BIND_API(GUI);
    ELONA_BIND_API(I18N);
    ELONA_BIND_API(Input);
    ELONA_BIND_API(Internal);
    ELONA_BIND_API(Item);
    ELONA_BIND_API(JSON5);
    ELONA_BIND_API(Magic);
    ELONA_BIND_API(Map);
    ELONA_BIND_API(Pos);
    ELONA_BIND_API(Rand);
    ELONA_BIND_API(Skill);
    ELONA_BIND_API(Trait);
    ELONA_BIND_API(Wish);
    ELONA_BIND_API(World);

#undef ELONA_BIND_API
}

} // namespace elona::lua::api::modules
