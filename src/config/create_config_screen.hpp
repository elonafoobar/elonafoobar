#pragma once

#include <memory>
#include <string>
#include <vector>

namespace elona
{
using SpecKey = std::string;
using I18NKey = std::string;

class Config;
class ConfigDef;
class ConfigMenu;

using ConfigScreen = std::vector<std::unique_ptr<ConfigMenu>>;

class ConfigScreenCreator
{
public:
    ConfigScreenCreator(Config& config)
        : config_(config)
    {
    }

    ConfigScreen create();

private:
    void visit_config_item(const SpecKey& current_key);
    void visit_section(const SpecKey& current_key);
    void visit_toplevel();

    Config& config_;
    ConfigScreen result_;
};

ConfigScreen create_config_screen();
} // namespace elona
