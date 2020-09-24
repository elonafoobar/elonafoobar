// @noluadoc
#include "classes.hpp"

#include "classes/class_LuaAbility.cpp"
#include "classes/class_LuaArea.cpp"
#include "classes/class_LuaCharacter.cpp"
#include "classes/class_LuaColor.cpp"
#include "classes/class_LuaDate.cpp"
#include "classes/class_LuaDateTime.cpp"
#include "classes/class_LuaGameData.cpp"
#include "classes/class_LuaInventory.cpp"
#include "classes/class_LuaItem.cpp"
#include "classes/class_LuaMapData.cpp"
#include "classes/class_LuaMapGenerator.cpp"
#include "classes/class_LuaPosition.cpp"
#include "classes/class_LuaTime.cpp"



namespace elona::lua::api::classes
{

void bind(sol::state& L)
{
#define ELONA_LUA_API_BIND_CLASS(ClassName) \
    { \
        class_##ClassName::bind(L); \
    }

    ELONA_LUA_API_BIND_CLASS(LuaAbility);
    ELONA_LUA_API_BIND_CLASS(LuaArea);
    ELONA_LUA_API_BIND_CLASS(LuaCharacter);
    ELONA_LUA_API_BIND_CLASS(LuaColor);
    ELONA_LUA_API_BIND_CLASS(LuaDateTime);
    ELONA_LUA_API_BIND_CLASS(LuaGameData);
    ELONA_LUA_API_BIND_CLASS(LuaInventory);
    ELONA_LUA_API_BIND_CLASS(LuaItem);
    ELONA_LUA_API_BIND_CLASS(LuaDate);
    ELONA_LUA_API_BIND_CLASS(LuaDateTime);
    ELONA_LUA_API_BIND_CLASS(LuaTime);
    ELONA_LUA_API_BIND_CLASS(LuaMapData);
    ELONA_LUA_API_BIND_CLASS(LuaMapGenerator);
    ELONA_LUA_API_BIND_CLASS(LuaPosition);

#undef ELONA_LUA_API_BIND_CLASS
}



void bind_api(sol::state& L, sol::table core)
{
    core["LuaPosition"] = L["LuaPosition"];
}

} // namespace elona::lua::api::classes
