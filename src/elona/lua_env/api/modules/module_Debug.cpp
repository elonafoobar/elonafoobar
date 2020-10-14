#include <sstream>

#include "../../../debug.hpp"
#include "../../../log.hpp"
#include "../../../message.hpp"
#include "../common.hpp"



/**
 * @luadoc
 *
 * Functions for debugging scripts.
 */
namespace elona::lua::api::modules::module_Debug
{

/**
 * @luadoc enable_wizard
 *
 * Enable Wizard mode. It is equivalent to turn `core.wizard.is_enabled` on.
 */
void Debug_enable_wizard()
{
    elona::debug_enable_wizard();
    ELONA_LOG("Debug.enable_wizard: enabled");
}



/**
 * @luadoc disable_wizard
 *
 * Disable Wizard mode. It is equivalent to turn `core.wizard.is_enabled` off.
 */
void Debug_disable_wizard()
{
    elona::debug_disable_wizard();
    ELONA_LOG("Debug.disable_wizard: disabled");
}



/**
 * @luadoc is_wizard
 *
 * Returns whether you are Wizard or not. It is opposite to `Debug.is_muggle`.
 *
 * Note: You might want to make a limitation of "unless you are Wizard". For
 * example, if you make an achievement system, Wizard players can obtain all of
 * them much easier than you expect. However, before calling `Debug.is_wizard`,
 * remember that Elona is a single-player game.
 *
 * @treturn boolean `true` if Wizard mode; otherwise `false`.
 */
bool Debug_is_wizard()
{
    return elona::debug_is_wizard();
}



/**
 * @luadoc is_muggle
 *
 * Returns whether you are Muggle or not. It is opposite to `Debug.is_wizard`.
 *
 * @treturn boolean `true` if Muggle mode; otherwise `false`.
 */
bool Debug_is_muggle()
{
    return !elona::debug_is_wizard();
}



/**
 * @luadoc has_wizard_flag
 *
 * Return if you are Wizard and `flag_name` is on.
 *
 * @tparam string flag_name The flag option's name.
 * @treturn boolean `true` if Muggle mode; otherwise `false`.
 * @treturn boolean `true` if you are Wizard and `flag_name` is on; if not,
 * `false`. Even if `flag_name` is not a boolean option, its value is
 * interpreted as boolean (e.g., check truthy or falsy).
 */
bool Debug_has_wizard_flag(const std::string& flag_name)
{
    return elona::debug_has_wizard_flag(flag_name);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("enable_wizard", Debug_enable_wizard);
    ELONA_LUA_API_BIND_FUNCTION("disable_wizard", Debug_disable_wizard);
    ELONA_LUA_API_BIND_FUNCTION("is_wizard", Debug_is_wizard);
    ELONA_LUA_API_BIND_FUNCTION("is_muggle", Debug_is_muggle);
    ELONA_LUA_API_BIND_FUNCTION("has_wizard_flag", Debug_has_wizard_flag);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Debug
