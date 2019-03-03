#include "lua_api_skill.hpp"
#include "../../ability.hpp"
#include "../../character.hpp"
#include "../enums/enums.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Obtains a character's skill level in a skill or spell.
 * @tparam num skill_id the skill/spell id
 * @tparam LuaCharacter chara the character to get skill information from
 * @treturn num the character's skill/spell level
 */
int LuaApiSkill::level(int skill_id, LuaCharacterHandle chara)
{
    if (skill_id < 0 || skill_id >= 600)
    {
        return -1;
    }
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    return elona::sdata(skill_id, chara_ref.index);
}


/**
 * @luadoc
 *
 * Obtains a character's resistance level for an element.
 * @tparam Enums.Element element the element
 * @tparam LuaCharacter chara the character to get resistance information from
 * @treturn num the character's resistance level
 */
int LuaApiSkill::resistance(const EnumString& element, LuaCharacterHandle chara)
{
    auto& chara_ref = lua::lua->get_handle_manager().get_ref<Character>(chara);
    Element element_value = LuaEnums::ElementTable.ensure_from_string(element);
    return elona::sdata(static_cast<int>(element_value), chara_ref.index);
}

void LuaApiSkill::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiSkill, level);
    LUA_API_BIND_FUNCTION(api_table, LuaApiSkill, resistance);
}

} // namespace lua
} // namespace elona
