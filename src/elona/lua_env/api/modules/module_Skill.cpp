#include "module_Skill.hpp"

#include "../../../ability.hpp"
#include "../../../character.hpp"
#include "../../enums/enums.hpp"
#include "../../handle_manager.hpp"



namespace elona
{
namespace lua
{

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
    auto& chara_ref = lua::ref<Character>(chara);
    Element element_value = LuaEnums::ElementTable.ensure_from_string(element);
    return elona::sdata(static_cast<int>(element_value), chara_ref.index);
}

void LuaApiSkill::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiSkill, resistance);
}

} // namespace lua
} // namespace elona
