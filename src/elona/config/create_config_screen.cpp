#include "create_config_screen.hpp"
#include <string>
#include <unordered_map>
#include "../../util/natural_order_comparator.hpp"
#include "../../util/range.hpp"
#include "../spec.hpp"
#include "config_def.hpp"
#include "config_menu.hpp"



namespace elona
{

namespace
{

using SpecKey = std::string;
using I18NKey = std::string;



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
    bool visit_mod_config(const std::string& mod_id);
    bool visit_section_children(
        const std::string& mod_id,
        const I18NKey& locale_key);
    bool visit_section(const SpecKey& current_key, const I18NKey& locale_key);
    bool visit_config_item(
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

    std::vector<std::string> get_sorted_mod_list();

    Config& config_;
    ConfigScreen result_;
    std::unordered_map<std::string, int> config_key_to_submenu_index_;
    int menu_index_;
};



constexpr int menu_width = 370;
constexpr int submenu_width = 440;
constexpr int menu_height = 165;
constexpr int menu_item_height = 19;



// Functions for visiting/building the config menu.
void ConfigScreenCreator::add_menu(
    const SpecKey& key,
    const I18NKey& menu_name_key,
    int width,
    int submenu)
{
    auto children = config_.get_def().get_children(key);
    int w = width;
    int h = menu_height + (menu_item_height * children.size());
    result_.emplace_back(std::make_unique<ConfigMenu>(
        i18n::s.get(menu_name_key), w, h, submenu));
}



void ConfigScreenCreator::add_submenu(
    const SpecKey& key,
    const I18NKey& menu_name_key,
    int width,
    int submenu)
{
    auto children = config_.get_def().get_children(key);
    int w = width;
    int h = menu_height + (menu_item_height * children.size());
    result_.emplace_back(std::make_unique<ConfigMenuSubmenu>(
        i18n::s.get(menu_name_key), w, h, submenu));
}



void ConfigScreenCreator::add_item_yesno(
    const SpecKey& key,
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

    std::string yes_text = i18n::s.get(yes_no + ".yes");
    std::string no_text = i18n::s.get(yes_no + ".no");

    result_.at(menu_index_)
        ->items.emplace_back(std::make_unique<ConfigMenuItemYesNo>(
            key, locale_key, default_value, yes_text, no_text));
}



void ConfigScreenCreator::add_item_integer(
    const SpecKey& key,
    const I18NKey& locale_key,
    int default_value)
{
    int min = config_.get_def().get_min(key);
    int max = config_.get_def().get_max(key);
    int step = config_.get_def().get_step(key);

    result_.at(menu_index_)
        ->items.emplace_back(std::make_unique<ConfigMenuItemInteger>(
            key, locale_key, default_value, min, max, step, "${_1}"));
}



void ConfigScreenCreator::add_item_choice(
    const SpecKey& key,
    const I18NKey& locale_key,
    const std::string& default_value)
{
    // Add the translated names of all variants.
    const auto& variants = config_.get_def().get_variants(key);
    std::vector<ConfigMenuItemChoice::Choice> choices;

    for (const auto& variant : variants)
    {
        auto Choice = ConfigMenuItemChoice::Choice{
            variant, locale_key + ".variants." + variant};
        choices.emplace_back(Choice);
    }

    bool translate_variants =
        config_.get_def().get_metadata(key).translate_variants;

    result_.at(menu_index_)
        ->items.emplace_back(std::make_unique<ConfigMenuItemChoice>(
            key, locale_key, default_value, choices, translate_variants));
}



void ConfigScreenCreator::add_item_section(
    const SpecKey& key,
    const I18NKey& locale_key,
    const std::string section_name,
    int submenu_index)
{
    // EX: "<core>.<language>"
    SpecKey section_key = key + "." + section_name;

    if (config_.get_def().get_metadata(section_key).is_visible())
    {
        // EX: "<core.config.menu>.<language>"
        I18NKey section_locale_key = locale_key + "." + section_name;

        result_.at(menu_index_)
            ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
                section_key, section_locale_key, submenu_index));
    }
}



void ConfigScreenCreator::add_keybindings_section()
{
    menu_index_ = result_.size();

    // Bypasses the config_def mechanism for config menu generation. The
    // keybindings menu will be unconditionally added.
    result_.emplace_back(std::make_unique<ConfigMenuKeybindings>(menu_index_));
    result_.at(0)->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
        "core.keybindings", "core.config.menu.keybindings", menu_index_));
}



void ConfigScreenCreator::add_mod_configs_section()
{
    const auto& mod_ids = get_sorted_mod_list();

    // Only add the section if there is at least one mod other than "core".
    if (mod_ids.size() <= 1)
    {
        return;
    }

    // Add the menu.
    int w = menu_width;
    int h = menu_height + (menu_item_height * (mod_ids.size() - 1));
    int mod_menu_index = result_.size();
    result_.emplace_back(std::make_unique<ConfigMenu>(
        i18n::s.get("core.config.menu.mods.name"), w, h, mod_menu_index));

    bool found_mods = false;

    for (const auto& mod_id : mod_ids)
    {
        if (mod_id == "core")
        {
            continue;
        }

        auto found_items = visit_mod_config(mod_id);

        if (found_items)
        {
            found_mods = true;

            I18NKey locale_key = mod_id + ".config.menu";

            std::string id = mod_id;
            const auto& children = config_.get_def().get_children(mod_id);
            if (children.size() == 1)
            {
                // If the mod has only one section, expand the section into
                // "Mod Settings" submenu.
                id += "." + children.front();
            }

            int submenu_index = config_key_to_submenu_index_[id];

            result_.at(mod_menu_index)
                ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
                    id, locale_key, submenu_index));
        }
    }

    // Only add the mods section if any mods were found.
    if (found_mods)
    {
        result_.at(0)->items.emplace_back(
            std::make_unique<ConfigMenuItemSection>(
                "core.mods", "core.config.menu.mods", mod_menu_index));
    }
}



void ConfigScreenCreator::visit_toplevel()
{
    menu_index_ = 0;

    // This menu will be created with index 0, which indicates the top-level
    // menu. The rest will have an index greater than zero.
    bool found_items = visit_mod_config("core");
    assert(found_items);

    // Unconditionally add the keybindings section, since it has special
    // behavior for binding keys. It is not created like the other menu
    // sections, because it has no section definition in the config definition.
    add_keybindings_section();

    // Add a menu leading to a list of sections for each mod config.
    add_mod_configs_section();
}



bool ConfigScreenCreator::visit_mod_config(const std::string& mod_id)
{
    I18NKey locale_key = mod_id + ".config.menu";

    return visit_section_children(mod_id, locale_key);
}



bool ConfigScreenCreator::visit_section_children(
    const std::string& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core.section>"
    // locale_key is similar to "<core.config.menu.section>"

    I18NKey menu_name_key = locale_key + ".name";

    // Ignore this section if it contains no items.
    if (config_.get_def().get_children(current_key).empty())
    {
        return false;
    }

    bool found_items = false;

    {
        int prev_index = menu_index_;

        // Add the section level menu.
        menu_index_ = result_.size();
        config_key_to_submenu_index_[current_key] = menu_index_;
        add_menu(current_key, menu_name_key, menu_width, menu_index_);

        // Add all sections and their config items. This adds all the config
        // menus so their indices are available when the corresponding section
        // items are added below.
        for (const auto& section_name :
             config_.get_def().get_children(current_key))
        {
            auto result = visit_section(
                current_key + "." + section_name,
                locale_key + "." + section_name);

            if (result)
            {
                found_items = true;

                int submenu_index = config_key_to_submenu_index_
                    [current_key + "." + section_name];
                add_item_section(
                    current_key, locale_key, section_name, submenu_index);
            }
        }

        menu_index_ = prev_index;
    }

    return found_items;
}



bool ConfigScreenCreator::visit_section(
    const SpecKey& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core>.language"
    // locale_key is similar to "<core.config.menu>.language"

    I18NKey menu_name_key = locale_key + ".name";

    // Ensure the section exists in the config definition.
    if (!config_.get_def().exists(current_key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\". ");
    }
    // Ignore this section if it is not user-visible.
    if (!config_.get_def().get_metadata(current_key).is_visible())
    {
        return false;
    }
    // Ignore this section if it contains no items.
    if (config_.get_def().get_children(current_key).empty())
    {
        return false;
    }

    bool found_items = false;

    {
        int prev_index = menu_index_;

        // Add the submenu and save its index.
        menu_index_ = result_.size();
        config_key_to_submenu_index_[current_key] = menu_index_;
        add_submenu(current_key, menu_name_key, submenu_width, menu_index_);

        // Visit child config items of this section.
        for (const auto& child : config_.get_def().get_children(current_key))
        {
            bool result = visit_config_item(
                current_key + "." + child, locale_key + "." + child);

            if (result)
            {
                found_items = true;
            }
        }

        menu_index_ = prev_index;
    }

    return found_items;
}



bool ConfigScreenCreator::visit_config_item(
    const SpecKey& current_key,
    const I18NKey& locale_key)
{
    if (!config_.get_def().exists(current_key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    if (!config_.get_def().get_metadata(current_key).is_visible())
    {
        return false;
    }

    if (config_.get_def().is<spec::BoolDef>(current_key))
    {
        add_item_yesno(current_key, locale_key, config_.get<bool>(current_key));
    }
    else if (config_.get_def().is<spec::IntDef>(current_key))
    {
        add_item_integer(
            current_key, locale_key, config_.get<int>(current_key));
    }
    else if (config_.get_def().is<spec::EnumDef>(current_key))
    {
        add_item_choice(
            current_key, locale_key, config_.get<std::string>(current_key));
    }
    else if (config_.get_def().is<spec::StringDef>(current_key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (config_.get_def().is<spec::ListDef>(current_key))
    {
        // ignore
    }
    else if (config_.get_def().is<spec::SectionDef>(current_key))
    {
        int prev_index = menu_index_;

        bool result = visit_section_children(current_key, locale_key);

        menu_index_ = prev_index;

        return result;
    }
    else
    {
        throw std::runtime_error("Unknown config def item");
    }

    return true;
}



std::vector<std::string> ConfigScreenCreator::get_sorted_mod_list()
{
    auto ret = config_.get_mod_ids();
    range::sort(ret, lib::natural_order_comparator{});
    return ret;
}



ConfigScreen ConfigScreenCreator::create()
{
    visit_toplevel();
    return std::move(result_);
}

} // namespace



ConfigScreen create_config_screen()
{
    auto& conf = Config::instance();
    return ConfigScreenCreator(conf).create();
}

} // namespace elona
