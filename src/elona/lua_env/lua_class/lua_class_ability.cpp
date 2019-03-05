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
        /**
         * @luadoc experience field num
         *
         * [R] The skill's current experience. To modify it, use
         * LuaCharacter.gain_skill_exp, which will modify level and potential
         * appropriately.
         * @see LuaCharacter.gain_skill_exp
         */
        "experience",
        ELONA_LUA_SKILL_PROPERTY_READONLY(experience),

        /**
         * @luadoc current_level field num
         *
         * [RW] The skill's current level.
         */
        "current_level",
        ELONA_LUA_SKILL_PROPERTY(current_level),

        /**
         * @luadoc original_level field num
         *
         * [RW] The skill's original level.
         */
        "original_level",
        ELONA_LUA_SKILL_PROPERTY(original_level),

        /**
         * @luadoc potential field num
         *
         * [RW] The skill's potential.
         */
        "potential",
        ELONA_LUA_SKILL_PROPERTY(potential));

    lua.set_usertype("LuaAbility", LuaAbility);
}

#undef ELONA_LUA_SKILL_PROPERTY

} // namespace lua
} // namespace elona
