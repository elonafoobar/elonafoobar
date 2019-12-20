#include "config_menu.hpp"
#include "../util/natural_order_comparator.hpp"
#include "../util/range.hpp"
#include "lua_env/config_manager.hpp"
#include "lua_env/mod_manager.hpp"



namespace elona
{

namespace
{

using I18NKey = std::string;



class ConfigScreenCreator
{
public:
    ConfigScreenCreator(lua::ConfigManager& conf)
        : _conf(conf)
    {
    }


    ConfigScreen create();



private:
    lua::ConfigManager& _conf;
    ConfigScreen _result;
    std::unordered_map<std::string, int> _config_key_to_submenu_index;
    int _menu_index;



    void visit_toplevel();
    bool visit_mod_config(const std::string& mod_id);
    bool visit_section_children(
        const std::string& mod_id,
        const I18NKey& locale_key);
    bool visit_section(
        const std::string& current_key,
        const I18NKey& locale_key);
    bool visit_config_item(
        const std::string& current_key,
        const I18NKey& locale_key);

    void add_keybindings_section();
    void add_mod_configs_section();

    void add_menu(
        const std::string& key,
        const I18NKey& menu_name_key,
        int width,
        int submenu);
    void add_submenu(
        const std::string& key,
        const I18NKey& menu_name_key,
        int width,
        int submenu);

    void add_item_boolean(
        const std::string& key,
        const I18NKey& locale_key,
        bool default_value);
    void add_item_integer(
        const std::string& key,
        const I18NKey& locale_key,
        int default_value);
    void add_item_choice(
        const std::string& key,
        const I18NKey& locale_key,
        const std::string& default_value);
    void add_item_section(
        const std::string& key,
        const I18NKey& locale_key,
        const std::string section_name,
        int submenu_index);

    std::vector<std::string> get_sorted_mod_list();
};



constexpr int menu_width = 370;
constexpr int submenu_width = 440;
constexpr int menu_height = 165;
constexpr int menu_item_height = 19;



ConfigScreen ConfigScreenCreator::create()
{
    visit_toplevel();
    return std::move(_result);
}



void ConfigScreenCreator::visit_toplevel()
{
    _menu_index = 0;

    // This menu will be created with index 0, which indicates the top-level
    // menu. The rest will have an index greater than zero.
    bool found_items = visit_mod_config("core");
    assert(found_items);
    (void)found_items; // suppress unused variable warning in release build.

    // Unconditionally add the keybindings section, since it has special
    // behavior for binding keys. It is not created like the other menu
    // sections, because it has no section definition in the config definition.
    add_keybindings_section();

    // Add a menu leading to a list of sections for each mod config.
    add_mod_configs_section();
}



bool ConfigScreenCreator::visit_mod_config(const std::string& mod_id)
{
    const auto locale_key = mod_id + ".config.menu";
    return visit_section_children(mod_id, locale_key);
}



bool ConfigScreenCreator::visit_section_children(
    const std::string& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core.section>"
    // locale_key is similar to "<core.config.menu.section>"
    const auto menu_name_key = locale_key + ".name";

    // Ignore this section if it contains no items.
    if (_conf.get_children_keys(current_key).empty())
        return false;

    bool found_items = false;
    int prev_index = _menu_index;

    // Add the section level menu.
    _menu_index = _result.size();
    _config_key_to_submenu_index[current_key] = _menu_index;
    add_menu(current_key, menu_name_key, menu_width, _menu_index);

    // Add all sections and their config items. This adds all the config
    // menus so their indices are available when the corresponding section
    // items are added below.
    for (const auto& kvp : _conf.get_children_keys(current_key))
    {
        const auto section_name = kvp.second.as<std::string>();
        bool result = visit_section(
            current_key + "." + section_name, locale_key + "." + section_name);
        if (result)
        {
            found_items = true;
            const auto submenu_index =
                _config_key_to_submenu_index[current_key + "." + section_name];
            add_item_section(
                current_key, locale_key, section_name, submenu_index);
        }
    }

    _menu_index = prev_index;

    return found_items;
}



bool ConfigScreenCreator::visit_section(
    const std::string& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core>.language"
    // locale_key is similar to "<core.config.menu>.language"
    const auto menu_name_key = locale_key + ".name";

    // Ignore this section if it is not user-visible.
    if (_conf.is_hidden(current_key))
        return false;

    // Ignore this section if it contains no items.
    if (_conf.get_children_keys(current_key).empty())
        return false;

    bool found_items = false;
    int prev_index = _menu_index;

    // Add the submenu and save its index.
    _menu_index = _result.size();
    _config_key_to_submenu_index[current_key] = _menu_index;
    add_submenu(current_key, menu_name_key, submenu_width, _menu_index);

    // Visit child config items of this section.
    for (const auto& kvp : _conf.get_children_keys(current_key))
    {
        const auto child = kvp.second.as<std::string>();
        bool result = visit_config_item(
            current_key + "." + child, locale_key + "." + child);
        if (result)
        {
            found_items = true;
        }
    }

    _menu_index = prev_index;

    return found_items;
}



bool ConfigScreenCreator::visit_config_item(
    const std::string& current_key,
    const I18NKey& locale_key)
{
    if (_conf.is_hidden(current_key))
        return false;

    if (_conf.is_boolean_option(current_key))
    {
        add_item_boolean(current_key, locale_key, _conf.get<bool>(current_key));
    }
    else if (_conf.is_integer_option(current_key))
    {
        add_item_integer(current_key, locale_key, _conf.get<int>(current_key));
    }
    else if (_conf.is_enum_option(current_key))
    {
        add_item_choice(
            current_key, locale_key, _conf.get<std::string>(current_key));
    }
    else if (_conf.is_string_option(current_key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (_conf.is_section(current_key))
    {
        int prev_index = _menu_index;
        bool result = visit_section_children(current_key, locale_key);
        _menu_index = prev_index;
        return result;
    }
    else
    {
        throw std::runtime_error("Unknown config def item");
    }

    return true;
}



void ConfigScreenCreator::add_keybindings_section()
{
    _menu_index = _result.size();

    // Bypasses the config schema mechanism for config menu generation. The
    // keybindings menu will be unconditionally added.
    _result.emplace_back(std::make_unique<ConfigMenuKeybindings>(_menu_index));
    _result.front()->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
        "core.keybindings", "core.config.menu.keybindings", _menu_index));
}



void ConfigScreenCreator::add_mod_configs_section()
{
    const auto mod_ids = get_sorted_mod_list();

    // Only add the section if there is at least one mod other than "core".
    if (mod_ids.size() <= 1)
        return;

    // Add the menu.
    const auto w = menu_width;
    const auto h = menu_height + (menu_item_height * (mod_ids.size() - 1));
    const auto mod_menu_index = _result.size();
    _result.emplace_back(std::make_unique<ConfigMenu>(
        i18n::s.get("core.config.menu.mods.name"), w, h, mod_menu_index));

    bool found_mods = false;
    for (const auto& mod_id : mod_ids)
    {
        if (mod_id == "core")
            continue;

        const auto found_items = visit_mod_config(mod_id);

        if (found_items)
        {
            found_mods = true;

            const auto locale_key = mod_id + ".config.menu";

            auto id = mod_id;
            const auto& children = _conf.get_children_keys(mod_id);
            if (children.size() == 1)
            {
                // If the mod has only one section, expand the section into
                // "Mod Settings" submenu.
                id += "." + children.get<std::string>(1);
            }

            const auto submenu_index = _config_key_to_submenu_index[id];
            _result.at(mod_menu_index)
                ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
                    id, locale_key, submenu_index));
        }
    }

    // Only add the mods section if any mods were found.
    if (found_mods)
    {
        _result.front()->items.emplace_back(
            std::make_unique<ConfigMenuItemSection>(
                "core.mods", "core.config.menu.mods", mod_menu_index));
    }
}



// Functions for visiting/building the config menu.
void ConfigScreenCreator::add_menu(
    const std::string& key,
    const I18NKey& menu_name_key,
    int width,
    int submenu)
{
    const auto children = _conf.get_children_keys(key);
    const auto w = width;
    const auto h = menu_height + (menu_item_height * children.size());
    _result.emplace_back(std::make_unique<ConfigMenu>(
        i18n::s.get(menu_name_key), w, h, submenu));
}



void ConfigScreenCreator::add_submenu(
    const std::string& key,
    const I18NKey& menu_name_key,
    int width,
    int submenu)
{
    const auto children = _conf.get_children_keys(key);
    const auto w = width;
    const auto h = menu_height + (menu_item_height * children.size());
    _result.emplace_back(std::make_unique<ConfigMenuSubmenu>(
        i18n::s.get(menu_name_key), w, h, submenu));
}



void ConfigScreenCreator::add_item_boolean(
    const std::string& key,
    const I18NKey& locale_key,
    bool default_value)
{
    I18NKey yes_no;

    // Determine which text to use for true/false ("Yes"/"No", "Play"/"Don't
    // Play", etc.)
    if (auto text = i18n::s.get_optional(locale_key + ".yes_no"))
    {
        yes_no = *text;
    }
    else
    {
        // Fall back to a hardcoded default.
        yes_no = "core.config.common.yes_no.default";
    }

    const auto yes_text = i18n::s.get(yes_no + ".yes");
    const auto no_text = i18n::s.get(yes_no + ".no");

    _result.at(_menu_index)
        ->items.emplace_back(std::make_unique<ConfigMenuItemBoolean>(
            key, locale_key, default_value, yes_text, no_text));
}



void ConfigScreenCreator::add_item_integer(
    const std::string& key,
    const I18NKey& locale_key,
    int default_value)
{
    const auto min = _conf.get_min(key);
    const auto max = _conf.get_max(key);
    const auto step = _conf.get_step(key);

    _result.at(_menu_index)
        ->items.emplace_back(std::make_unique<ConfigMenuItemInteger>(
            key, locale_key, default_value, min, max, step, "${_1}"));
}



void ConfigScreenCreator::add_item_choice(
    const std::string& key,
    const I18NKey& locale_key,
    const std::string& default_value)
{
    // Add the translated names of all variants.
    std::vector<ConfigMenuItemChoice::Choice> choices;
    for (const auto& kvp : _conf.get_enum(key))
    {
        const auto e = kvp.second.as<std::string>();
        choices.emplace_back(e, locale_key + ".enum." + e);
    }

    _result.at(_menu_index)
        ->items.emplace_back(std::make_unique<ConfigMenuItemChoice>(
            key, locale_key, choices, default_value));
}



void ConfigScreenCreator::add_item_section(
    const std::string& key,
    const I18NKey& locale_key,
    const std::string section_name,
    int submenu_index)
{
    // EX: "<core>.<language>"
    const auto section_key = key + "." + section_name;

    if (_conf.is_hidden(section_key))
        return;

    // EX: "<core.config.menu>.<language>"
    const auto section_locale_key = locale_key + "." + section_name;

    _result.at(_menu_index)
        ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
            section_key, section_locale_key, submenu_index));
}



std::vector<std::string> ConfigScreenCreator::get_sorted_mod_list()
{
    auto mods = lua::lua->get_mod_manager().enabled_mods();
    std::vector<std::string> ret;
    range::transform(mods, std::back_inserter(ret), [](const auto& m) {
        return m.second->manifest.id;
    });
    range::sort(ret, lib::natural_order_comparator{});
    return ret;
}

} // namespace



ConfigScreen config_build_menu()
{
    auto& conf = lua::lua->get_config_manager();
    return ConfigScreenCreator(conf).create();
}

} // namespace elona
