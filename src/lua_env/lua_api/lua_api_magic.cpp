#include "lua_api_magic.hpp"

namespace elona
{
namespace lua
{

void Magic::cast_self(
    lua_character_handle caster_handle,
    int effect_id,
    int effect_power,
    const Position& target_location)
{
    elona::tlocx = target_location.x;
    elona::tlocy = target_location.y;
    Magic::cast(caster_handle, caster_handle, effect_id, effect_power);
}

void Magic::cast(
    lua_character_handle caster_handle,
    lua_character_handle target_handle,
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

void Magic::bind(sol::table& api_table)
{
    api_table.set_function(
        "cast", sol::overload(Magic::cast_self, Magic::cast));
}

} // namespace lua
} // namespace elona
