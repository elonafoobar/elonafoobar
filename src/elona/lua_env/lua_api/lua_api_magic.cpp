#include "lua_api_magic.hpp"
#include "../../character.hpp"
#include "../../magic.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{
/**
 * @luadoc cast
 *
 * Makes a character cast a spell targeting themselves or a position.
 * @tparam LuaCharacter caster (mut) the casting character
 * @tparam num effect_id the spell ID
 * @tparam num effect_power the power of the spell
 * @tparam LuaPosition target_location (const) the position the spell targets
 * @usage local pos = Map.random_pos()
 * Magic.cast(Chara.player(), 432, 100, pos) -- Ball magic
 */
void LuaApiMagic::cast_self(
    LuaCharacterHandle caster,
    int effect_id,
    int effect_power,
    const Position& target_location)
{
    elona::tlocx = target_location.x;
    elona::tlocy = target_location.y;
    LuaApiMagic::cast(caster, caster, effect_id, effect_power);
}

/**
 * @luadoc
 *
 * Makes a character cast a spell targeting another character.
 * @tparam LuaCharacter caster (mut) the casting character
 * @tparam LuaCharacter target (mut) the target character
 * @tparam num effect_id the spell ID
 * @tparam num effect_power the power of the spell
 * @usage local caster = Chara.player()
 * local target = Chara.create(0, 0, "core.putit")
 * Magic.cast(caster, target, 414, 100) -- Magic missile
 */
void LuaApiMagic::cast(
    LuaCharacterHandle caster,
    LuaCharacterHandle target,
    int effect_id,
    int effect_power)
{
    int ccbk = elona::cc;
    int tcbk = elona::tc;

    try
    {
        auto& caster_ref = lua::ref<Character>(caster);
        auto& target_ref = lua::ref<Character>(target);
        elona::cc = caster_ref.index;
        elona::tc = target_ref.index;
        elona::efid = effect_id;
        elona::efp = effect_power;
        elona::magic();
        elona::cc = ccbk;
        elona::tc = tcbk;
    }
    catch (std::exception& e)
    {
        // Always reset the values of cc/tc if a handle is invalid.
        elona::cc = ccbk;
        elona::tc = tcbk;

        // Throw the exception so the calling script receives it.
        throw e;
    }
}

void LuaApiMagic::bind(sol::table& api_table)
{
    api_table.set_function(
        "cast", sol::overload(LuaApiMagic::cast_self, LuaApiMagic::cast));
}

} // namespace lua
} // namespace elona
