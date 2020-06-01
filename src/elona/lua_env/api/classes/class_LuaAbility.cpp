#include "class_LuaAbility.hpp"

#include "../../../ability.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::lua::api::classes::LuaAbility)



/**
 * @luadoc
 *
 * A reference to a skill on a LuaCharacter.
 */
namespace elona::lua::api::classes::class_LuaAbility
{

#define ELONA_LUA_SKILL_PROPERTY_READONLY(name) \
    sol::property([](classes::LuaAbility& a) { \
        if (!a.is_valid()) \
        { \
            return 0; \
        } \
        return sdata.get(a.skill_id, a.index).name; \
    })

#define ELONA_LUA_SKILL_PROPERTY(name) \
    sol::property( \
        [](classes::LuaAbility& a) { \
            if (!a.is_valid()) \
            { \
                return 0; \
            } \
            return sdata.get(a.skill_id, a.index).name; \
        }, \
        [](classes::LuaAbility& a, int i) { \
            if (!a.is_valid()) \
            { \
                return; \
            } \
            sdata.get(a.skill_id, a.index).name = i; \
        })

void bind(sol::state& lua)
{
    auto LuaAbility = lua.new_usertype<classes::LuaAbility>(
        "LuaAbility", sol::no_constructor);

    /**
     * @luadoc experience field num
     *
     * [R] The skill's current experience. To modify it, use
     * LuaCharacter.gain_skill_exp, which will modify level and potential
     * appropriately.
     * @see LuaCharacter.gain_skill_exp
     */
    LuaAbility.set("experience", ELONA_LUA_SKILL_PROPERTY_READONLY(experience));

    /**
     * @luadoc current_level field num
     *
     * [RW] The skill's current level.
     */
    LuaAbility.set("current_level", ELONA_LUA_SKILL_PROPERTY(current_level));

    /**
     * @luadoc original_level field num
     *
     * [RW] The skill's original level.
     */
    LuaAbility.set("original_level", ELONA_LUA_SKILL_PROPERTY(original_level));

    /**
     * @luadoc potential field num
     *
     * [RW] The skill's potential.
     */
    LuaAbility.set("potential", ELONA_LUA_SKILL_PROPERTY(potential));
}

#undef ELONA_LUA_SKILL_PROPERTY

} // namespace elona::lua::api::classes::class_LuaAbility
