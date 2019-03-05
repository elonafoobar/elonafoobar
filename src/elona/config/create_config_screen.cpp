#include "create_config_screen.hpp"
#include "../spec.hpp"
#include "config_def.hpp"
#include "config_menu.hpp"

namespace elona
{

constexpr int menu_width = 370;
constexpr int submenu_width = 440;
constexpr int menu_height = 165;
constexpr int menu_item_height = 19;

// Functions for adding items to the config screen.

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
        yes_no = "core.locale.config.common.yes_no.default";
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

    result_.at(menu_index_)
        ->items.emplace_back(std::make_unique<ConfigMenuItemInteger>(
            key, locale_key, default_value, min, max, "${_1}"));
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
    std::cerr << "key" << section_key << std::endl;

    if (config_.get_def().get_metadata(section_key).is_visible())
    {
        // EX: "<core.locale.config.menu>.<language>"
        I18NKey section_locale_key = locale_key + "." + section_name;

        result_.at(menu_index_)
            ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
                section_key, section_locale_key, submenu_index));
    }
}


// Functions for visiting/building the config menu.

void ConfigScreenCreator::add_keybindings_section()
{
    menu_index_ = result_.size();

    // Bypasses the config_def mechanism for config menu generation. The
    // keybindings menu will be unconditionally added.
    result_.emplace_back(std::make_unique<ConfigMenuKeybindings>(menu_index_));
    result_.at(0)->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
        "core.keybindings",
        "core.locale.config.menu.keybindings",
        menu_index_));
}

void ConfigScreenCreator::add_mod_configs_section()
{
    const auto& mod_names = config_.get_mod_names();

    // Only add the section if there is at least one mod other than "core".
    if (mod_names.size() <= 1)
    {
        return;
    }

    // Bypasses the config_def mechanism for config menu generation. The mod
    // configs menu will be unconditionally added.
    int w = menu_width;
    int h = menu_height + (menu_item_height * (mod_names.size() - 1));
    menu_index_ = result_.size();

    bool found_mods = false;

    for (const auto& mod_name : mod_names)
    {
        if (mod_name == "core")
        {
            continue;
        }

        auto found_items = visit_mod_config(mod_name);

        if (found_items)
        {
            found_mods = true;

            I18NKey locale_key = mod_name + ".locale.config.menu";
            int submenu_index = config_key_to_submenu_index_[mod_name];
            std::cerr << "For error " << mod_name << " " << submenu_index
                      << std::endl;

            result_.at(menu_index_)
                ->items.emplace_back(std::make_unique<ConfigMenuItemSection>(
                    mod_name, locale_key, submenu_index));
        }
    }

    if (found_mods)
    {
        result_.emplace_back(std::make_unique<ConfigMenu>(
            i18n::s.get("core.locale.config.menu.mods.name"),
            w,
            h,
            menu_index_));
        result_.at(0)->items.emplace_back(
            std::make_unique<ConfigMenuItemSection>(
                "core.mods", "core.locale.config.menu.mods", menu_index_));
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

bool ConfigScreenCreator::visit_mod_config(const std::string& mod_name)
{
    I18NKey locale_key = mod_name + ".locale.config.menu";

    return visit_section_children(mod_name, locale_key);
}

bool ConfigScreenCreator::visit_section_children(
    const std::string& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core.section>"
    // locale_key is similar to "<core.locale.config.menu.section>"
    std::cerr << "children " << current_key << std::endl;

    I18NKey menu_name_key = locale_key + ".name";

    // Ignore this section if it contains no items.
    if (config_.get_def().get_children(current_key).size() == 0)
    {
        return false;
    }

    {
        int prev_index = menu_index_;

        // Add the section level menu.
        menu_index_ = result_.size();
        config_key_to_submenu_index_[current_key] = menu_index_;
        add_menu(current_key, menu_name_key, menu_width, menu_index_);
        std::cerr << "visit section " << menu_index_ << " " << current_key
                  << std::endl;

        // Add all sections and their config items. This adds all the config
        // menus so their indices are available when the corresponding section
        // items are added below.
        for (const auto& section_name :
             config_.get_def().get_children(current_key))
        {
            auto found_items = visit_section(
                current_key + "." + section_name,
                locale_key + "." + section_name);

            if (found_items)
            {
                int submenu_index = config_key_to_submenu_index_
                    [current_key + "." + section_name];
                add_item_section(
                    current_key, locale_key, section_name, submenu_index);
            }
        }

        menu_index_ = prev_index;
    }

    return true;
}

bool ConfigScreenCreator::visit_section(
    const SpecKey& current_key,
    const I18NKey& locale_key)
{
    // current_key is similar to "<core>.language"
    // locale_key is similar to "<core.locale.config.menu>.language"
    std::cerr << "section " << current_key << std::endl;

    I18NKey menu_name_key = locale_key + ".name";

    // Ensure the section exists in the config definition.
    if (!config_.get_def().exists(current_key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    // Ignore this section if it is not user-visible.
    if (!config_.get_def().get_metadata(current_key).is_visible())
    {
        return false;
    }
    // Ignore this section if it contains no items.
    if (config_.get_def().get_children(current_key).size() == 0)
    {
        return false;
    }

    {
        int prev_index = menu_index_;

        // Add the submenu and save its index.
        menu_index_ = result_.size();
        config_key_to_submenu_index_[current_key] = menu_index_;
        add_submenu(current_key, menu_name_key, submenu_width, menu_index_);
        std::cerr << "Section " << current_key << " " << menu_index_
                  << std::endl;

        // Visit child config items of this section.
        for (const auto& child : config_.get_def().get_children(current_key))
        {
            std::cerr << "Child " << current_key << " " << child << std::endl;
            visit_config_item(
                current_key + "." + child, locale_key + "." + child);
        }

        menu_index_ = prev_index;
    }

    return true;
}

void ConfigScreenCreator::visit_config_item(
    const SpecKey& current_key,
    const I18NKey& locale_key)
{
    std::cerr << "item " << current_key << std::endl;
    if (!config_.get_def().exists(current_key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    if (!config_.get_def().get_metadata(current_key).is_visible())
    {
        return;
    }

    if (config_.get_def().is<spec::BoolDef>(current_key))
    {
        add_item_yesno(current_key, locale_key, config_.get<bool>(current_key));
    }
    else if (config_.get_def().is<spec::IntDef>(current_key))
    {
        add_item_integer(
            current_key, locale_key, config_.get<int>(current_key)

        );
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
        std::cerr << "is_child " << current_key << std::endl;

        visit_section_children(current_key, locale_key);

        menu_index_ = prev_index;
    }
    else
    {
        throw std::runtime_error("Unknown config def item");
    }
}


ConfigScreen ConfigScreenCreator::create()
{
    visit_toplevel();
    return std::move(result_);
}


ConfigScreen create_config_screen()
{
    auto& conf = Config::instance();
    return ConfigScreenCreator(conf).create();
}

} // namespace elona
