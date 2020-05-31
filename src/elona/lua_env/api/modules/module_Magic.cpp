#include "module_Magic.hpp"

#include "../../../character.hpp"
#include "../../../magic.hpp"
#include "../../handle_manager.hpp"



namespace elona::lua::api::modules::module_Magic
{

/**
 * @luadoc cast
 *
 * Makes a character cast a spell targeting another character.
 *
 * @tparam LuaCharacter caster (mut) the casting character
 * @tparam LuaCharacter target (mut) the target character
 * @tparam num effect_id the spell ID
 * @tparam num effect_power the power of the spell
 * @usage local caster = Chara.player()
 * local target = Chara.create(0, 0, "core.putit")
 * Magic.cast(caster, target, 414, 100) -- Magic missile
 */
void Magic_cast(
    LuaCharacterHandle caster,
    LuaCharacterHandle target,
    int effect_id,
    int effect_power)
{
    auto& caster_ref = lua::ref<Character>(caster);
    auto& target_ref = lua::ref<Character>(target);
    efid = effect_id;
    efp = effect_power;
    magic(caster_ref, target_ref);
}



/**
 * @luadoc cast
 *
 * Makes a character cast a spell targeting themselves or a position.
 *
 * @tparam LuaCharacter caster (mut) the casting character
 * @tparam num effect_id the spell ID
 * @tparam num effect_power the power of the spell
 * @tparam LuaPosition target_location (const) the position the spell targets
 * @usage local pos = Map.random_pos()
 * Magic.cast(Chara.player(), 432, 100, pos) -- Ball magic
 */
void Magic_cast_self(
    LuaCharacterHandle caster,
    int effect_id,
    int effect_power,
    const Position& target_location)
{
    tlocx = target_location.x;
    tlocy = target_location.y;
    Magic_cast(caster, caster, effect_id, effect_power);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("cast", Magic_cast_self, Magic_cast);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Magic
