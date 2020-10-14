#include "../../../skill.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Skill)



/**
 * @luadoc
 *
 * A reference to a skill on a LuaCharacter.
 */
namespace elona::lua::api::classes::class_LuaSkill
{

void bind(sol::state& lua)
{
    auto LuaSkill = lua.new_usertype<Skill>("LuaSkill", sol::no_constructor);

    /**
     * @luadoc level field num
     *
     * [RW] The skill's current level.
     */
    LuaSkill.set("level", &Skill::level);

    /**
     * @luadoc base_level field num
     *
     * [RW] The skill's base level.
     */
    LuaSkill.set("base_level", &Skill::base_level);

    /**
     * @luadoc experience field num
     *
     * [RW] The skill's current experience.
     */
    LuaSkill.set("experience", &Skill::experience);

    /**
     * @luadoc potential field num
     *
     * [RW] The skill's potential.
     */
    LuaSkill.set("potential", &Skill::potential);
}

} // namespace elona::lua::api::classes::class_LuaSkill
