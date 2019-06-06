#pragma once

#include <memory>
#include <vector>



namespace elona
{

class ConfigMenu;
using ConfigScreen = std::vector<std::unique_ptr<ConfigMenu>>;

ConfigScreen create_config_screen();

} // namespace elona
