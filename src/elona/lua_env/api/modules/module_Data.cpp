#include "../../../data/types/type_character.hpp"
#include "../../../draw.hpp"
#include "../../data_manager.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for managing the asset system. With this module it is possible to
 * reload built-in assets like textures and music.
 */
namespace elona::lua::api::modules::module_Data
{

/**
 * @luadoc reload_assets
 *
 * Reloads the UI assets defined in the <code>core.asset</code> table. Call this
 * if you want changes to the <code>core.asset</code> table to be visible.
 */
void Data_reload_assets()
{
    init_assets();
}



/**
 * @luadoc reload_charas
 *
 * Reloads the UI assets defined in the <code>core.chara</code> table. Call this
 * if you want changes to the <code>core.chara</code> table to be visible.
 */
void Data_reload_charas()
{
    the_character_db.initialize(lua::lua->get_data_manager().get());
}



/**
 * @luadoc get
 *
 * Get the data for the prototype ID and the data ID.
 *
 * @tparam string prototype_id a namespaced prototype ID.
 * @tparam string data_id a namespaced data ID.
 * @treturn[1] table the data.
 * @treturn[2] nil if not found.
 */
sol::optional<sol::table> Data_get(
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
 * @luadoc get_table
 *
 * Get the data table for the prototype ID.
 *
 * @tparam string prototype_id a namespaced prototype ID.
 * @treturn[1] table the table which stores data.
 * @treturn[2] nil if not found.
 */
sol::optional<sol::table> Data_get_table(const std::string& prototype_id)
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
 * @luadoc get_id_by_legacy
 *
 * Get new ID by legacy ID.
 *
 * @tparam string prototype_id a namespaced prototype ID.
 * @tparam num legacy_data_id a legacy data ID.
 * @treturn[1] string the corresponding new ID.
 * @treturn[2] nil if not found.
 */
sol::optional<std::string> Data_get_id_by_legacy(
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



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("reload_assets", Data_reload_assets);
    ELONA_LUA_API_BIND_FUNCTION("reload_charas", Data_reload_charas);
    ELONA_LUA_API_BIND_FUNCTION("get", Data_get);
    ELONA_LUA_API_BIND_FUNCTION("get_table", Data_get_table);
    ELONA_LUA_API_BIND_FUNCTION("get_id_by_legacy", Data_get_id_by_legacy);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Data
