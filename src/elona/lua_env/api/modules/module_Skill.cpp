#include "../../../ability.hpp"
#include "../../../character.hpp"
#include "../../enums/enums.hpp"
#include "../../handle_manager.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for working with skills or spells.
 * Both skills and spells are represented through the same experience
 * and leveling system. The only real difference is that spells have
 * an additional spell stock value.
 */
namespace elona::lua::api::modules::module_Skill
{

/**
 * @luadoc resistance
 *
 * Obtains a character's resistance level for an element.
 *
 * @tparam Enums.Element element the element
 * @tparam LuaCharacter chara the character to get resistance information from
 * @treturn num the character's resistance level
 */
int Skill_resistance(const EnumString& element, LuaCharacterHandle chara)
{
    auto& chara_ref = lua::ref<Character>(chara);
    Element element_value = LuaEnums::ElementTable.ensure_from_string(element);
    return sdata(static_cast<int>(element_value), chara_ref.index);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("resistance", Skill_resistance);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Skill
