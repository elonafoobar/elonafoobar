#include "lua_api_data.hpp"

#include "../../data/types/type_character.hpp"
#include "../../draw.hpp"
#include "../data_manager.hpp"



namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Reloads the UI assets defined in the <code>core.asset</code> table. Call this
 * if you want changes to the <code>core.asset</code> table to be visible.
 */
void LuaApiData::reload_assets()
{
    init_assets();
}



/**
 * @luadoc
 *
 * Reloads the UI assets defined in the <code>core.chara</code> table. Call this
 * if you want changes to the <code>core.chara</code> table to be visible.
 */
void LuaApiData::reload_charas()
{
    the_character_db.initialize(lua::lua->get_data_manager().get());
}



/**
 * @luadoc
 *
 * Get the data for the prototype ID and the data ID.
 * @tparam string prototype_id a namespaced prototype ID.
 * @tparam string data_id a namespaced data ID.
 * @treturn[1] table the data.
 * @treturn[2] nil if not found.
 */
sol::optional<sol::table> LuaApiData::get(
    const std::string& prototype_id,
    const std::string& data_id)
{
    if (auto ret = lua->get_data_manager().get().raw(
            data::PrototypeId{prototype_id}, data::InstanceId{data_id}))
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
 * Get the data table for the prototype ID.
 * @tparam string prototype_id a namespaced prototype ID.
 * @treturn[1] table the table which stores data.
 * @treturn[2] nil if not found.
 */
sol::optional<sol::table> LuaApiData::get_table(const std::string& prototype_id)
{
    if (auto ret = lua->get_data_manager().get().get_table(
            data::PrototypeId{prototype_id}))
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
 * @tparam num legacy_data_id a legacy data ID.
 * @treturn[1] string the corresponding new ID.
 * @treturn[2] nil if not found.
 */
sol::optional<std::string> LuaApiData::get_id_by_legacy(
    const std::string& prototype_id,
    int legacy_data_id)
{
    if (const auto ret = lua->get_data_manager().get().by_legacy(
            data::PrototypeId{prototype_id}, legacy_data_id))
    {
        return ret->get();
    }
    else
    {
        return sol::nullopt;
    }
}



void LuaApiData::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, reload_assets);
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, reload_charas);
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, get);
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, get_table);
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, get_id_by_legacy);
}

} // namespace lua
} // namespace elona
