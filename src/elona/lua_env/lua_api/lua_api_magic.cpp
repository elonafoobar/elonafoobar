#include "lua_api_magic.hpp"
#include "../../character.hpp"
#include "../handle_manager.hpp"



namespace elona
{
namespace lua
{

void LuaApiMagic::cast_self(
    LuaCharacterHandle caster_handle,
    int effect_id,
    int effect_power,
    const Position& target_location)
{
    elona::tlocx = target_location.x;
    elona::tlocy = target_location.y;
    LuaApiMagic::cast(caster_handle, caster_handle, effect_id, effect_power);
}

void LuaApiMagic::cast(
    LuaCharacterHandle caster_handle,
    LuaCharacterHandle target_handle,
    int effect_id,
    int effect_power)
{
    int ccbk = elona::cc;
    int tcbk = elona::tc;

    try
    {
        auto& caster =
            lua::lua->get_handle_manager().get_ref<Character>(caster_handle);
        auto& target =
            lua::lua->get_handle_manager().get_ref<Character>(target_handle);
        elona::cc = caster.index;
        elona::tc = target.index;
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
