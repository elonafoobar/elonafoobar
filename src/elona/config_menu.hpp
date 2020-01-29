#pragma once

#include "config.hpp"
#include "i18n.hpp"
#include "macro.hpp"
#include "ui/ui_menu_config.hpp"
#include "ui/ui_menu_keybindings.hpp"



namespace elona
{

class ConfigMenuItemBase
{
public:
    virtual ~ConfigMenuItemBase() noexcept = default;



    virtual void change(int delta)
    {
        (void)delta;
    }


    virtual std::string get_message()
    {
        return "";
    }


    virtual optional<int> submenu()
    {
        return none;
    }


    const std::string name() const noexcept
    {
        return _name;
    }


    std::string get_desc() const
    {
        if (auto text = i18n::s.get_optional(_locale_key + ".doc"))
        {
            return *text;
        }
        else
        {
            return i18n::s.get("core.config.common.no_desc");
        }
    }



protected:
    std::string _key;
    I18NKey _locale_key;
    std::string _name;



    ConfigMenuItemBase(const std::string& key, const I18NKey& locale_key)
        : _key(key)
        , _locale_key(locale_key)
        , _name(i18n::s.get(locale_key + ".name"))
    {
    }
};



class ConfigMenuItemSection : public ConfigMenuItemBase
{
public:
    ConfigMenuItemSection(
        const std::string& key,
        const I18NKey& locale_key,
        int submenu_index)
        : ConfigMenuItemBase(key, locale_key)
        , _submenu_index(submenu_index)
    {
    }



    virtual optional<int> submenu() override
    {
        return _submenu_index;
    }



private:
    int _submenu_index;
};



class ConfigMenuItemBoolean : public ConfigMenuItemBase
{
public:
    ConfigMenuItemBoolean(
        const std::string& key,
        const I18NKey& locale_key,
        bool value,
        const std::string& yes_text,
        const std::string& no_text)
        : ConfigMenuItemBase(key, locale_key)
        , _value(value)
        , _yes_text(yes_text)
        , _no_text(no_text)
    {
    }



    virtual void change(int delta) override
    {
        _value = delta == 1;
        config_set_boolean(_key, _value);
    }



    virtual std::string get_message() override
    {
        return _value ? _yes_text : _no_text;
    }



    virtual ~ConfigMenuItemBoolean() noexcept = default;



private:
    bool _value;
    std::string _yes_text;
    std::string _no_text;
};



class ConfigMenuItemInteger : public ConfigMenuItemBase
{
public:
    ConfigMenuItemInteger(
        const std::string& key,
        const I18NKey& locale_key,
        int value,
        int min,
        int max,
        int step,
        const std::string& text)
        : ConfigMenuItemBase(key, locale_key)
        , _value(value)
        , _min(min)
        , _max(max)
        , _step(step)
        , _text(text)
    {
    }



    virtual void change(int delta) override
    {
        _value = clamp(_value + delta * _step, _min, _max);
        config_set_integer(_key, _value);
    }



    virtual std::string get_message() override
    {
        // return i18n::fmt_hil(_text, _value);
        return std::to_string(_value);
    }



    virtual ~ConfigMenuItemInteger() noexcept = default;



private:
    int _value;
    int _min;
    int _max;
    int _step;
    std::string _text;
};



class ConfigMenuItemChoice : public ConfigMenuItemBase
{
public:
    struct Choice
    {
        std::string value;
        I18NKey message_key;


        Choice(const std::string& value, const I18NKey& message_key)
            : value(value)
            , message_key(message_key)
        {
        }
    };



    ConfigMenuItemChoice(
        const std::string& key,
        const I18NKey& locale_key,
        const std::vector<Choice>& choices,
        const std::string& default_value)
        : ConfigMenuItemBase(key, locale_key)
        , _choices(choices)
    {
        // Since all options have thier own schema and are validated, this
        // iterator must point the default value.
        const auto itr = std::find_if(
            std::begin(_choices), std::end(_choices), [&](const auto& c) {
                return c.value == default_value;
            });
        assert(itr != std::end(_choices));

        _index = static_cast<int>(std::distance(std::begin(_choices), itr));
    }



    virtual void change(int delta) override
    {
        _index =
            clamp(_index + delta, 0, static_cast<int>(_choices.size() - 1));
        config_set_string(_key, _choices[_index].value);
    }



    virtual std::string get_message() override
    {
        const auto locale_key = _choices[_index].message_key;
        // Try getting a locale key, and if it doesn't exist use
        // the enum value itself as the readable text.
        if (auto text = i18n::s.get_optional(locale_key))
        {
            return *text;
        }
        else
        {
            return _choices[_index].value;
        }
    }



    virtual ~ConfigMenuItemChoice() noexcept = default;



private:
    int _index;
    std::vector<Choice> _choices;
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



using ConfigScreen = std::vector<std::unique_ptr<ConfigMenu>>;

ConfigScreen config_build_menu();

} // namespace elona
