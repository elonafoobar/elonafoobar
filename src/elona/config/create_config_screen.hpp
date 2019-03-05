#pragma once

#include <memory>
#include <string>
#include <unordered_map>
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
    void visit_toplevel();
    bool visit_mod_config(const std::string& mod_name);
    bool visit_section_children(
        const std::string& mod_name,
        const I18NKey& locale_key);
    bool visit_section(const SpecKey& current_key, const I18NKey& locale_key);
    void visit_config_item(
        const SpecKey& current_key,
        const I18NKey& locale_key);

    void add_keybindings_section();
    void add_mod_configs_section();

    void add_menu(
        const SpecKey& key,
        const I18NKey& menu_name_key,
        int width,
        int submenu);
    void add_submenu(
        const SpecKey& key,
        const I18NKey& menu_name_key,
        int width,
        int submenu);

    void add_item_yesno(
        const SpecKey& key,
        const I18NKey& locale_key,
        bool default_value);
    void add_item_integer(
        const SpecKey& key,
        const I18NKey& locale_key,
        int default_value);
    void add_item_choice(
        const SpecKey& key,
        const I18NKey& locale_key,
        const std::string& default_value);
    void add_item_section(
        const SpecKey& key,
        const I18NKey& locale_key,
        const std::string section_name,
        int submenu_index);

    Config& config_;
    ConfigScreen result_;
    std::unordered_map<std::string, int> config_key_to_submenu_index_;
    int menu_index_;
};

ConfigScreen create_config_screen();
} // namespace elona
