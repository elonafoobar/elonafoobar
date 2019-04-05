#include "lua_api_registry.hpp"
#include "../data_manager.hpp"
#include "../lua_env.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Get the data table for the prototype ID.
 * @tparam string prototype_id a namespaced prototype ID.
 * @treturn[1] table the table which stores data.
 * @treturn[2] nil if not found.
 */
sol::optional<sol::table> LuaApiRegistry::get_table(
    const std::string& prototype_id)
{
    if (const auto ret = lua->get_data_manager().get().get_table(prototype_id))
    {
        return *ret;
    }
    else
    {
        return sol::nullopt;
    }
}



/**
 * @luadoc
 *
 * Get new ID by legacy ID.
 * @tparam string prototype_id a namespaced prototype ID.
 * @tparam num legacy_id a legacy data ID.
 * @treturn[1] string the corresponding new ID.
 * @treturn[2] nil if not found.
 */
sol::optional<std::string> LuaApiRegistry::get_id_by_legacy(
    const std::string& prototype_id,
    int legacy_id)
{
    if (const auto ret =
            lua->get_data_manager().get().by_legacy(prototype_id, legacy_id))
    {
        return *ret;
    }
    else
    {
        return sol::nullopt;
    }
}



void LuaApiRegistry::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiRegistry, get_table);
    LUA_API_BIND_FUNCTION(api_table, LuaApiRegistry, get_id_by_legacy);
}

} // namespace lua
} // namespace elona
