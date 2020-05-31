#include "../../../config.hpp"
#include "../../config_manager.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for getting and setting config values. See the topic on creating
 * config menus for more details.
 */
namespace elona::lua::api::modules::module_Config
{

/**
 * @luadoc set
 *
 * Sets config item's value.
 *
 * @tparam string key Option key
 * @tparam any value Option value
 * @raise if the config item does not exist or is not a boolean, an integer, or
 * a string.
 */
void Config_set(const std::string& key, sol::object value)
{
    lua->get_config_manager().set(key, value);
}



/**
 * @luadoc get
 *
 * Gets config item's value.
 *
 * @tparam string key Option key
 * @raise if the config item does not exist or is not a boolean, an integer, or
 * a string.
 */
sol::object Config_get(const std::string& key)
{
    return lua->get_config_manager().get<sol::object>(key);
}



/**
 * @luadoc save
 *
 * Saves the current sate of the config to the config options file. Be sure to
 * call this when you modify the config using this API.
 */
void Config_save()
{
    config_save();
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("set", Config_set);
    ELONA_LUA_API_BIND_FUNCTION("get", Config_get);
    ELONA_LUA_API_BIND_FUNCTION("save", Config_save);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Config
