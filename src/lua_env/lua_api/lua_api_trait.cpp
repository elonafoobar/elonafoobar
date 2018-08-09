#include "lua_api_trait.hpp"
#include "../../trait.hpp"
#include "../../audio.hpp"

namespace elona
{
namespace lua
{

sol::optional<int> Trait::level(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::trait(trait_id);
}

sol::optional<int> Trait::min(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(1);
}

sol::optional<int> Trait::max(int trait_id)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return sol::nullopt;
    }
    return elona::traitref(2);
}

void Trait::set(int trait_id, int level)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (elona::trait(trait_id) < level
        && elona::trait(trait_id) < elona::traitref(2) && traitrefn(0) != "")
    {
        snd(61);
        elona::txtef(2);
        elona::txt(traitrefn(0));
    }
    else if (
        elona::trait(trait_id) > level
        && elona::trait(trait_id) > elona::traitref(1) && traitrefn(1) != "")
    {
        snd(61);
        elona::txtef(3);
        elona::txt(traitrefn(1));
    }
    elona::trait(trait_id) =
        clamp(level, elona::traitref(1), elona::traitref(2));
    chara_refresh(0);
}

void Trait::modify(int trait_id, int delta)
{
    if (trait_get_info(0, trait_id) == 0)
    {
        return;
    }
    if (delta > 0 && elona::trait(trait_id) < elona::traitref(2)
        && traitrefn(0) != "")
    {
        snd(61);
        elona::txtef(2);
        elona::txt(traitrefn(0));
    }
    else if (
        delta < 0 && elona::trait(trait_id) > elona::traitref(1)
        && traitrefn(1) != "")
    {
        snd(61);
        elona::txtef(3);
        elona::txt(traitrefn(1));
    }
    elona::trait(trait_id) = clamp(
        elona::trait(trait_id) + delta, elona::traitref(1), elona::traitref(2));
    chara_refresh(0);
}

void Trait::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Trait, level);
    LUA_API_BIND_FUNCTION(api_table, Trait, min);
    LUA_API_BIND_FUNCTION(api_table, Trait, max);
    LUA_API_BIND_FUNCTION(api_table, Trait, set);
    LUA_API_BIND_FUNCTION(api_table, Trait, modify);
}

} // namespace lua
} // namespace elona
