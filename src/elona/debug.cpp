#include "debug.hpp"

#include "config.hpp"



namespace elona
{

namespace
{

constexpr const char* wizard_option_name = "core.wizard.is_enabled";

}



void debug_enable_wizard()
{
    config_set(wizard_option_name, true);
}



void debug_disable_wizard()
{
    config_set(wizard_option_name, false);
}



bool debug_is_wizard()
{
    return config_get<bool>(wizard_option_name);
}



bool debug_has_wizard_flag(const std::string& flag_name)
{
    if (!debug_is_wizard())
        return false;

    return config_get<bool>(flag_name);
}

} // namespace elona
