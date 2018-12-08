#include "lua_class_ability.hpp"
#include "../../ability.hpp"

namespace elona
{
namespace lua
{

#define ELONA_LUA_SKILL_PROPERTY_READONLY(name) \
    sol::property([](lua::LuaAbility& a) { \
        if (!a.is_valid()) \
        { \
            return 0; \
        } \
        return sdata.get(a.skill_id, a.index).name; \
    })

#define ELONA_LUA_SKILL_PROPERTY(name) \
    sol::property( \
        [](lua::LuaAbility& a) { \
            if (!a.is_valid()) \
            { \
                return 0; \
            } \
            return sdata.get(a.skill_id, a.index).name; \
        }, \
        [](lua::LuaAbility& a, int i) { \
            if (!a.is_valid()) \
            { \
                return; \
            } \
            sdata.get(a.skill_id, a.index).name = i; \
        })

void LuaAbility::bind(sol::state& lua)
{
    sol::usertype<lua::LuaAbility> LuaAbility(
        // Should use LuaCharacter::gain_skill_exp instead.
        "experience",
        ELONA_LUA_SKILL_PROPERTY_READONLY(experience),

        "current_level",
        ELONA_LUA_SKILL_PROPERTY(current_level),
        "original_level",
        ELONA_LUA_SKILL_PROPERTY(original_level),
        "potential",
        ELONA_LUA_SKILL_PROPERTY(potential));

    lua.set_usertype("LuaAbility", LuaAbility);
}

#undef ELONA_LUA_SKILL_PROPERTY

} // namespace lua
} // namespace elona
