#include "create_config_screen.hpp"
#include "../spec.hpp"
#include "config_def.hpp"
#include "config_menu.hpp"

namespace elona
{

// Functions for adding items to the config screen.

template <class M>
static void add_config_menu(
    const SpecKey& key,
    const I18NKey& menu_name_key,
    const ConfigDef& def,
    int width,
    ConfigScreen& ret)
{
    auto children = def.get_children(key);
    int w = width;
    int h = 165 + (19 * children.size());
    ret.emplace_back(std::make_unique<M>(i18n::s.get(menu_name_key), w, h));
}


static void add_config_item_yesno(
    const SpecKey& key,
    const I18NKey& locale_key,
    bool default_value,
    ConfigScreen& ret)
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

    ret.back()->items.emplace_back(std::make_unique<ConfigMenuItemYesNo>(
        key, locale_key, default_value, yes_text, no_text));
}

static void add_config_item_integer(
    const SpecKey& key,
    const I18NKey& locale_key,
    int default_value,
    const ConfigDef& def,
    ConfigScreen& ret)
{
    int min = def.get_min(key);
    int max = def.get_max(key);

    ret.back()->items.emplace_back(std::make_unique<ConfigMenuItemInteger>(
        key, locale_key, default_value, min, max, "${_1}"));
}

static void add_config_item_choice(
    const SpecKey& key,
    const I18NKey& locale_key,
    const std::string& default_value,
    const ConfigDef& def,
    ConfigScreen& ret)
{
    // Add the translated names of all variants.
    const auto& variants = def.get_variants(key);
    std::vector<ConfigMenuItemChoice::Choice> choices;

    for (const auto& variant : variants)
    {
        auto Choice = ConfigMenuItemChoice::Choice{
            variant, locale_key + ".variants." + variant};
        choices.emplace_back(Choice);
    }

    bool translate_variants = def.get_metadata(key).translate_variants;

    ret.back()->items.emplace_back(std::make_unique<ConfigMenuItemChoice>(
        key, locale_key, default_value, choices, translate_variants));
}

static void add_config_item_section(
    const SpecKey& key,
    const I18NKey& locale_key,
    const std::string section_name,
    const ConfigDef& def,
    ConfigScreen& ret)
{
    // EX: "<core.config>.<language>"
    SpecKey section_key = key + "." + section_name;

    if (def.get_metadata(section_key).is_visible())
    {
        // EX: "<core.locale.config.menu>.<language>"
        I18NKey section_locale_key = locale_key + "." + section_name;

        ret.back()->items.emplace_back(std::make_unique<ConfigMenuItemBase>(
            section_key, section_locale_key));
    }
}



void ConfigScreenCreator::visit_toplevel()
{
    SpecKey key = "core.config";
    I18NKey locale_key = config_.get_def().get_locale_root();
    I18NKey menu_name_key = locale_key + ".name";

    // Add the top level menu.
    add_config_menu<ConfigMenu>(
        key, menu_name_key, config_.get_def(), 370, result_);

    // Add the names of top-level config menu sections if they are visible.
    for (const auto& section_name : config_.get_def().get_children(key))
    {
        add_config_item_section(
            key, locale_key, section_name, config_.get_def(), result_);
    }

    // Add all sections and their config items.
    for (const auto& child : config_.get_def().get_children(key))
    {
        visit_section(child);
    }

    // Unconditionally add the keybindings menu, since it has special behavior
    // for binding keys.
    result_.emplace_back(std::make_unique<ConfigMenuKeybindings>());
}

void ConfigScreenCreator::visit_section(const SpecKey& current_key)
{
    // EX: "<core.config>.<language>"
    SpecKey key = "core.config." + current_key;

    // EX: "<core.locale.config.menu>.language"
    I18NKey locale_key =
        config_.get_def().get_locale_root() + "." + current_key;
    I18NKey menu_name_key = locale_key + ".name";

    // Ensure the section exists in the config definition.
    if (!config_.get_def().exists(key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    // Ignore this section if it is not user-visible.
    if (!config_.get_def().get_metadata(key).is_visible())
    {
        return;
    }

    // Add the submenu.
    add_config_menu<ConfigMenuSubmenu>(
        key, menu_name_key, config_.get_def(), 440, result_);

    // Visit child config items of this section.
    for (const auto& child : config_.get_def().get_children(key))
    {
        visit_config_item(current_key + "." + child);
    }
}

void ConfigScreenCreator::visit_config_item(const SpecKey& current_key)
{
    SpecKey key = "core.config." + current_key;
    I18NKey locale_key =
        config_.get_def().get_locale_root() + "." + current_key;

    if (!config_.get_def().exists(key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    if (!config_.get_def().get_metadata(key).is_visible())
    {
        return;
    }

    if (config_.get_def().is<spec::BoolDef>(key))
    {
        add_config_item_yesno(key, locale_key, config_.get<bool>(key), result_);
    }
    else if (config_.get_def().is<spec::IntDef>(key))
    {
        add_config_item_integer(
            key, locale_key, config_.get<int>(key), config_.get_def(), result_);
    }
    else if (config_.get_def().is<spec::EnumDef>(key))
    {
        add_config_item_choice(
            key,
            locale_key,
            config_.get<std::string>(key),
            config_.get_def(),
            result_);
    }
    else if (config_.get_def().is<spec::StringDef>(key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (config_.get_def().is<spec::ListDef>(key))
    {
        // ignore
    }
    else if (config_.get_def().is<spec::SectionDef>(key))
    {
        throw std::runtime_error(
            "You cannot currently define nested sections.");
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
