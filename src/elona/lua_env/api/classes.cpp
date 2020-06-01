// @noluadoc
#include "classes.hpp"

#include "classes/class_LuaAbility.cpp"
#include "classes/class_LuaArea.cpp"
#include "classes/class_LuaCharacter.cpp"
#include "classes/class_LuaDateTime.cpp"
#include "classes/class_LuaGameData.cpp"
#include "classes/class_LuaItem.cpp"
#include "classes/class_LuaMapData.cpp"
#include "classes/class_LuaMapGenerator.cpp"
#include "classes/class_LuaPosition.cpp"



namespace elona::lua::api::classes
{

void bind(sol::state& L)
{
    LuaAbility::bind(L);
    LuaArea::bind(L);
    LuaCharacter::bind(L);
    LuaDateTime::bind(L);
    LuaGameData::bind(L);
    LuaItem::bind(L);
    LuaMapData::bind(L);
    LuaMapGenerator::bind(L);
    LuaPosition::bind(L);
}



void bind_api(sol::state& L, sol::table core)
{
    core["LuaPosition"] = L["LuaPosition"];
}

} // namespace elona::lua::api::classes
