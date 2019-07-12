#pragma once
#include "../i18n.hpp"
#include "../macro.hpp"
#include "../ui/ui_menu_config.hpp"
#include "../ui/ui_menu_keybindings.hpp"
#include "config.hpp"

namespace elona
{

class ConfigMenuItemBase
{
public:
    std::string name;
    std::string key;
    I18NKey locale_key;

protected:
    ConfigMenuItemBase(const std::string& key, const I18NKey& locale_key)
        : key(key)
        , locale_key(locale_key)
    {
        name = i18n::s.get(locale_key + ".name");
    }

public:
    virtual ~ConfigMenuItemBase() noexcept = default;

    virtual void change(int)
    {
    }
    virtual std::string get_message()
    {
        return "";
    }
    virtual optional<int> submenu()
    {
        return none;
    }

    std::string get_desc() const
    {
        if (auto text = i18n::s.get_optional(locale_key + ".doc"))
        {
            return *text;
        }
        else
        {
            return i18n::s.get("core.config.common.no_desc");
        }
    }
};



class ConfigMenuItemSection : public ConfigMenuItemBase
{
public:
    int submenu_index;

    ConfigMenuItemSection(
        const std::string& key,
        const I18NKey& locale_key,
        int submenu_index)
        : ConfigMenuItemBase(key, locale_key)
        , submenu_index(submenu_index)
    {
    }

    optional<int> submenu() override
    {
        return submenu_index;
    }
};



class ConfigMenuItemYesNo : public ConfigMenuItemBase
{
public:
    bool variable;
    std::string yes;
    std::string no;

    ConfigMenuItemYesNo(
        const std::string& key,
        const I18NKey& locale_key,
        bool variable,
        const std::string& yes,
        const std::string& no)
        : ConfigMenuItemBase(key, locale_key)
        , variable(variable)
        , yes(yes)
        , no(no)
    {
    }

    void change(int delta) override
    {
        if (!variable && delta == 1)
        {
            variable = true;
        }
        else if (variable && delta == -1)
        {
            variable = false;
        }

        Config::instance().set(key, variable);
    }
    std::string get_message() override
    {
        return variable ? yes : no;
    }

    virtual ~ConfigMenuItemYesNo() noexcept = default;
};



class ConfigMenuItemInfo : public ConfigMenuItemBase
{
public:
    std::string info;

    ConfigMenuItemInfo(
        const std::string& key,
        const I18NKey& locale_key,
        const std::string& info)
        : ConfigMenuItemBase(key, locale_key)
        , info(info)
    {
    }

    virtual ~ConfigMenuItemInfo() noexcept = default;

    std::string get_message() override
    {
        return info;
    }
};



class ConfigMenuItemInteger : public ConfigMenuItemBase
{
public:
    int variable;
    int min;
    int max;
    std::string text;

    ConfigMenuItemInteger(
        const std::string& key,
        const I18NKey& locale_key,
        int variable,
        int min,
        int max,
        const std::string& text)
        : ConfigMenuItemBase(key, locale_key)
        , variable(variable)
        , min(min)
        , max(max)
        , text(text)
    {
    }

    void change(int delta) override
    {
        variable = clamp(variable + delta, min, max);
        Config::instance().set(key, variable);
    }

    std::string get_message() override
    {
        return i18n::fmt_hil(text, variable);
    }

    virtual ~ConfigMenuItemInteger() noexcept = default;
};



class ConfigMenuItemChoice : public ConfigMenuItemBase
{
public:
    struct Choice
    {
        Choice(std::string value, I18NKey message_key)
            : value(value)
            , message_key(message_key)
        {
        }

        std::string value;
        I18NKey message_key;
    };

    int index;
    bool translate_variants;
    std::vector<Choice> variants;

    ConfigMenuItemChoice(
        const std::string& key,
        const I18NKey& locale_key,
        std::string default_choice,
        const std::vector<Choice>& variants,
        bool translate_variants)
        : ConfigMenuItemBase(key, locale_key)
        , translate_variants(translate_variants)
        , variants(variants)
    {
        index = -1;
        int i = 0;
        for (auto it = variants.begin(); it != variants.end(); ++it)
        {
            if (it->value == default_choice)
            {
                index = i;
            }
            i++;
        }
        if (index == -1)
        {
            throw std::runtime_error(
                "No such enum variant \"" + default_choice + "\" in \"" + key +
                "\".");
        }
        // If the enum variant is injected, but the selected value is
        // still unknown, try to set its index to the first known
        // value if there is one.
        if (variants.size() >= 2 && index == 0 &&
            variants.at(index).value == spec::unknown_enum_variant)
        {
            index = 1;
            Config::instance().set(key, variants.at(index).value);
        }
    }

    void change(int p) override
    {
        index += p;
        if (index < 0)
        {
            index = 0;
        }
        if (index > static_cast<int>(variants.size() - 1))
        {
            index = static_cast<int>(variants.size() - 1);
        }
        // See above.
        if (variants.size() >= 2 && index == 0 &&
            variants.at(index).value == spec::unknown_enum_variant)
        {
            index = 1;
        }
        Config::instance().set(key, variants.at(index).value);
    }

    std::string get_message() override
    {
        I18NKey locale_key = variants.at(index).message_key;
        if (translate_variants)
        {
            return i18n::s.get(locale_key);
        }
        else
        {
            // Try getting a locale key, and if it doesn't exist use
            // the enum value itself as the readable text.
            if (auto text = i18n::s.get_optional(locale_key))
            {
                return *text;
            }
            else
            {
                return variants.at(index).value;
            }
        }
    }

    virtual ~ConfigMenuItemChoice() noexcept = default;
};



class ConfigMenu
{
public:
    std::string title;
    std::vector<std::unique_ptr<ConfigMenuItemBase>> items;
    int width;
    int height;
    int submenu;

    ConfigMenu(const std::string& title, int width, int height, int submenu)
        : title(title)
        , width(width)
        , height(height)
        , submenu(submenu)
    {
    }

    virtual ~ConfigMenu() = default;

    virtual void draw() const
    {
    }

    virtual optional<ui::UIMenuConfigResult> query()
    {
        auto result = ui::UIMenuConfig(*this, submenu).show();
        return result.value;
    }
};



class ConfigMenuSubmenu : public ConfigMenu
{
public:
    ConfigMenuSubmenu(
        const std::string& title,
        int width,
        int height,
        int submenu)
        : ConfigMenu(title, width, height, submenu)
    {
    }

    virtual ~ConfigMenuSubmenu() = default;

    void draw() const override
    {
        font(12 + sizefix - en * 2);
        mes(wx + 40,
            wy + wh - 70,
            i18n::s.get("core.config.common.require_restart"));
    }
};



class ConfigMenuKeybindings : public ConfigMenu
{
public:
    ConfigMenuKeybindings(int submenu)
        : ConfigMenu("Keybindings", 100, 100, submenu)
    {
    }

    virtual ~ConfigMenuKeybindings() = default;

    optional<ui::UIMenuConfigResult> query() override
    {
        auto result = ui::UIMenuKeybindings().show();
        return result.value;
    }
};

} // namespace elona
