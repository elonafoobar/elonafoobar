#pragma once

#include <string>



namespace elona
{

/**
 * Enable Wizard mode.
 */
void debug_enable_wizard();


/**
 * Disable Wizard mode.
 */
void debug_disable_wizard();


/**
 * Return if you are in Wizard mode.
 *
 * @return True if you are Wizard; if not, false.
 */
bool debug_is_wizard();


/**
 * Return if you are in Wizard mode and @a flag_name is on.
 *
 * @param flag_name The flag option's name.
 * @return True if you are Wizard and @a flag_name is on; if not,
 * false.
 */
bool debug_has_wizard_flag(const std::string& flag_name);

} // namespace elona
