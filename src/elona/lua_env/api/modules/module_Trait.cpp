#include "module_Trait.hpp"

#include "../../../audio.hpp"
#include "../../../character.hpp"
#include "../../../message.hpp"
#include "../../../trait.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Obtains the player's level in a trait. It may be negative if the
 * trait is harmful.
 * @tparam num trait_id the trait id
 * @treturn[1] num the player's trait level
 * @treturn[2] nil
 */
sol::optional<int> LuaApiTrait::level(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::trait(trait_id);
}

/**
 * @luadoc
 *
 * Obtains the minimum possible level of a trait.
 * @tparam num trait_id the trait id
 * @treturn[1] num the trait's minimum level.
 * @treturn[2] nil
 */
sol::optional<int> LuaApiTrait::min(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(1);
}

/**
 * @luadoc
 *
 * Obtains the maximum possible level of a trait.
 * @tparam num trait_id the trait id
 * @treturn[1] num the trait's maximum level.
 * @treturn[2] nil
 */
sol::optional<int> LuaApiTrait::max(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(2);
}

/**
 * @luadoc
 *
 * Sets the level of a trait, bounded within its min and max.
 * @tparam num trait_id the trait id
 * @tparam num level the new trait level
 */
void LuaApiTrait::set(int trait_id, int level)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (elona::trait(trait_id) < level &&
        elona::trait(trait_id) < elona::traitref(2) && traitrefn(0) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(0), elona::Message::color{ColorIndex::green});
    }
    else if (
        elona::trait(trait_id) > level &&
        elona::trait(trait_id) > elona::traitref(1) && traitrefn(1) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(1), elona::Message::color{ColorIndex::red});
    }
    elona::trait(trait_id) =
        clamp(level, elona::traitref(1), elona::traitref(2));
    chara_refresh(cdata.player());
}

/**
 * @luadoc
 *
 * Modifies the level of a trait, bounded within its min and max.
 * @tparam num trait_id the trait id
 * @tparam num delta the amount to change the trait level by
 */
void LuaApiTrait::modify(int trait_id, int delta)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (delta > 0 && elona::trait(trait_id) < elona::traitref(2) &&
        traitrefn(0) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(0), elona::Message::color{ColorIndex::green});
    }
    else if (
        delta < 0 && elona::trait(trait_id) > elona::traitref(1) &&
        traitrefn(1) != "")
    {
        snd("core.ding3");
        elona::txt(traitrefn(1), elona::Message::color{ColorIndex::red});
    }
    elona::trait(trait_id) = clamp(
        elona::trait(trait_id) + delta, elona::traitref(1), elona::traitref(2));
    chara_refresh(cdata.player());
}

void LuaApiTrait::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiTrait, level);
    LUA_API_BIND_FUNCTION(api_table, LuaApiTrait, min);
    LUA_API_BIND_FUNCTION(api_table, LuaApiTrait, max);
    LUA_API_BIND_FUNCTION(api_table, LuaApiTrait, set);
    LUA_API_BIND_FUNCTION(api_table, LuaApiTrait, modify);
}

} // namespace lua
} // namespace elona
