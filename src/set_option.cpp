#include "audio.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "snail/application.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include <sstream>

using namespace elona;


namespace
{

class ConfigMenuItemBase
{
public:
    std::string name;
    std::string key;
    I18NKey locale_key;

    ConfigMenuItemBase(const std::string& key, const I18NKey& locale_key)
        : key(key)
        , locale_key(locale_key)
    {
        name = i18n::s.get(locale_key + ".name");
    }

    virtual ~ConfigMenuItemBase() noexcept = default;

    virtual void change(int)
    {
    }
    virtual std::string get_message()
    {
        return "";
    }

    std::string get_desc() const
    {
        if (auto text = i18n::s.get_optional(locale_key + ".doc"))
        {
            return *text;
        }
        else
        {
            return i18n::s.get("core.locale.config.common.no_desc");
        }
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

    void change(int delta)
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
    std::string get_message()
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

    std::string get_message()
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

    void change(int delta)
    {
        variable = clamp(variable + delta, min, max);
        Config::instance().set(key, variable);
    }

    std::string get_message()
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
                "No such enum variant \"" + default_choice + "\" in \"" + key
                + "\".");
        }
        // If the enum variant is injected, but the selected value is
        // still unknown, try to set its index to the first known
        // value if there is one.
        if (variants.size() >= 2 && index == 0
            && variants.at(index).value == spec::unknown_enum_variant)
        {
            index = 1;
            Config::instance().set(key, variants.at(index).value);
        }
    }

    void change(int p)
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
        if (variants.size() >= 2 && index == 0
            && variants.at(index).value == spec::unknown_enum_variant)
        {
            index = 1;
        }
        Config::instance().set(key, variants.at(index).value);
    }

    std::string get_message()
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

    ConfigMenu(const std::string& title, int width, int height)
        : title(title)
        , width(width)
        , height(height)
    {
    }

    virtual void draw() const
    {
    }
};

class ConfigMenuSubmenu : public ConfigMenu
{
public:
    ConfigMenuSubmenu(const std::string& title, int width, int height)
        : ConfigMenu(title, width, height)
    {
    }

    void draw() const
    {
        pos(wx + 40, wy + wh - 70);
        font(12 + sizefix - en * 2);
        mes(i18n::s.get("core.locale.config.common.require_restart"));
    }
};

class ConfigMenuJoypad : public ConfigMenu
{
public:
    void draw() const
    {
        pos(wx + 40, wy + wh - 110);
        font(12 + sizefix - en * 2);
        mes(i18n::s.get("core.locale.config.common.assign_button"));
    }
};


using ConfigScreen = std::vector<std::unique_ptr<ConfigMenu>>;


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


// Functions for visiting the parsed config structure.

void visit_section(Config&, const SpecKey&, ConfigScreen&);
void visit_config_item(Config&, const SpecKey&, ConfigScreen&);


void visit_toplevel(Config& conf, ConfigScreen& ret)
{
    SpecKey key = "core.config";
    I18NKey locale_key = conf.get_def().get_locale_root();
    I18NKey menu_name_key = locale_key + ".name";

    // Add the top level menu.
    add_config_menu<ConfigMenu>(key, menu_name_key, conf.get_def(), 370, ret);

    // Add the names of top-level config menu sections if they are visible.
    for (const auto& section_name : conf.get_def().get_children(key))
    {
        add_config_item_section(
            key, locale_key, section_name, conf.get_def(), ret);
    }

    // Add all sections and their config items.
    for (const auto& child : conf.get_def().get_children(key))
    {
        visit_section(conf, child, ret);
    }
}

void visit_section(
    Config& conf,
    const SpecKey& current_key,
    ConfigScreen& ret)
{
    // EX: "<core.config>.<language>"
    SpecKey key = "core.config." + current_key;

    // EX: "<core.locale.config.menu>.language"
    I18NKey locale_key = conf.get_def().get_locale_root() + "." + current_key;
    I18NKey menu_name_key = locale_key + ".name";

    // Ensure the section exists in the config definition.
    if (!conf.get_def().exists(key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    // Ignore this section if it is not user-visible.
    if (!conf.get_def().get_metadata(key).is_visible())
    {
        return;
    }

    // Add the submenu.
    add_config_menu<ConfigMenuSubmenu>(
        key, menu_name_key, conf.get_def(), 440, ret);

    // Visit child config items of this section.
    for (const auto& child : conf.get_def().get_children(key))
    {
        visit_config_item(conf, current_key + "." + child, ret);
    }
}

void visit_config_item(
    Config& conf,
    const SpecKey& current_key,
    ConfigScreen& ret)
{
    SpecKey key = "core.config." + current_key;
    I18NKey locale_key = conf.get_def().get_locale_root() + "." + current_key;

    if (!conf.get_def().exists(key))
    {
        throw std::runtime_error(
            "No such config option \"" + current_key + "\".");
    }
    if (!conf.get_def().get_metadata(key).is_visible())
    {
        return;
    }

    if (conf.get_def().is<spec::BoolDef>(key))
    {
        add_config_item_yesno(key, locale_key, conf.get<bool>(key), ret);
    }
    else if (conf.get_def().is<spec::IntDef>(key))
    {
        add_config_item_integer(
            key, locale_key, conf.get<int>(key), conf.get_def(), ret);
    }
    else if (conf.get_def().is<spec::EnumDef>(key))
    {
        add_config_item_choice(
            key, locale_key, conf.get<std::string>(key), conf.get_def(), ret);
    }
    else if (conf.get_def().is<spec::StringDef>(key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (conf.get_def().is<spec::ListDef>(key))
    {
        // ignore
    }
    else if (conf.get_def().is<spec::SectionDef>(key))
    {
        throw std::runtime_error(
            "You cannot currently define nested sections.");
    }
    else
    {
        throw std::runtime_error("Unknown config def item");
    }
}


ConfigScreen create_config_screen()
{
    ConfigScreen ret;
    auto& conf = Config::instance();

    visit_toplevel(conf, ret);

    return ret;
}

} // namespace



namespace elona
{

static void _show_config_item_desc(const std::string& desc)
{
    size_t width = 100;
    size_t height = 100;
    int font_size = 13 + sizefix - en * 2;
    std::string line;
    std::istringstream ss(desc);

    while (std::getline(ss, line))
    {
        width = std::max(width, strlen_u(line) * 8 + 40);
        height += font_size;
    }

    int x = promptx - (width / 2);
    int y = prompty - (height / 2);

    snd(26);

    while (true)
    {
        window(x + 8, y + 8, width, height, false);

        font(font_size);
        pos(x + 40, y + font_size + 36);
        mes(desc);

        redraw();
        await(Config::instance().wait1);
        key_check();

        if (key != ""s)
        {
            key = ""s;
            break;
        }
    }
}

int submenu = 0;

void set_option()
{
    const auto ConfigScreen = create_config_screen();

    cs = 0;
set_option_begin:
    listmax = 0;
    page = 0;
    pagesize = 18;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;

    int bg_variant_buffer = mode == 10 ? 2 : 4;
    load_background_variants(bg_variant_buffer);
    gsel(0);

    if (mode == 0)
    {
        screenupdate = -1;
        update_screen();
    }
    if (mode == 10)
    {
        gsel(4);
        gmode(0);
        pos(0, 0);
        picload(filesystem::dir::graphic() / u8"title.bmp", 1);
        gcopy(4, 0, 0, 800, 600, windoww, windowh);
        gsel(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
    }

    auto& menu_def = ConfigScreen[submenu];
    auto menu_title = menu_def->title;
    auto width = menu_def->width;
    auto height = menu_def->height;

    for (const auto& menu_item : menu_def->items)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = menu_item->name;
        ++listmax;
    }

    windowshadow = 1;

    bool reset_page = true;
    while (true)
    {
        if (reset_page)
        {
            cs_bk = -1;
            pagemax = (listmax - 1) / pagesize;

            if (page < 0)
            {
                page = pagemax;
            }
            else if (page > pagemax)
            {
                page = 0;
            }
            reset_page = false;
        }
        s(0) = menu_title;
        s(1) = strhint3 + key_mode2 + i18n::s.get("core.locale.ui.hint.help");
        pagesize = 0;
        if (mode == 1)
        {
            display_window(
                (windoww - width) / 2 + inf_screenx,
                winposy(height, 1),
                width,
                height);
        }
        else
        {
            display_window(
                (windoww - width) / 2 + inf_screenx,
                winposy(height) - 12,
                width,
                height);
        }
        pagesize = listmax;
        display_topic(
            i18n::s.get("core.locale.config.common.menu"), wx + 34, wy + 36);
        if (mode == 10)
        {
            p = 2;
        }
        else
        {
            p = 4;
        }
        x = ww / 5 * 3;
        y = wh - 80;
        pos(wx + ww / 3, wy + wh / 2);
        gmode(4, 50);
        gcopy_c(p, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
        gmode(2);
        keyrange = 0;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            if (submenu == 0)
            {
                key_list(cnt) = key_select(cnt);
                ++keyrange;
                display_key(wx + 32, wy + 66 + cnt * 19 - 2, cnt);
            }
            else
            {
                key_list(cnt) = key_cancel;
                ++keyrange;
            }
        }
        font(14 - en * 2);
        cs_listbk();

        int item_pos = 0;
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            auto item = ConfigScreen[submenu]->items[cnt].get();

            p = pagesize * page + cnt;
            if (p >= listmax)
            {
                break;
            }
            i = list(0, p);
            s = listn(0, p);
            if (submenu == 0)
            {
                x = 8;
            }
            else
            {
                x = 0;
            }
            // if (submenu == 3)
            // {
            //     if (Config::instance().net == 0)
            //     {
            //         if (cnt >= 1)
            //         {
            //             continue;
            //         }
            //     }
            // }
            cs_list(
                cs == item_pos, s, wx + 56 + x, wy + 66 + item_pos * 19 - 1, 0);
            if ((true || cnt <= 0) && submenu != 0)
            {
                pos(wx + 220, wy + 66 + item_pos * 19 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 358, wy + 66 + item_pos * 19 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            pos(wx + 250, wy + 66 + cnt * 19);

            mes(item->get_message());

            item_pos++;
        }

        ConfigScreen[submenu]->draw();

        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        await(Config::instance().wait1);
        key_check();
        cursor_check();
        ELONA_GET_SELECTED_ITEM(p, cs = i);
        if (p != -1)
        {
            if (submenu == 0)
            {
                submenu = p + 1;
                snd(20);
                cs = 0;
                goto set_option_begin;
            }
        }
        if (key == key_pageup || key == key_pagedown)
        {
            if (key == key_pageup)
            {
                p = 1;
            }
            else
            {
                p = -1;
            }

            ConfigScreen[submenu]->items[cs].get()->change(p);
            snd(20);
            reset_page = true;
            continue;
        }
        if (key == key_mode2)
        {
            auto desc = ConfigScreen[submenu]->items[cs].get()->get_desc();
            _show_config_item_desc(desc);
            goto set_option_begin;
        }
        if (key == key_cancel)
        {
            if (submenu != 0)
            {
                // TODO nested menus
                cs = submenu - 1;
                submenu = 0;
                goto set_option_begin;
            }
            else
            {
                Config::instance().write();
                if (mode == 0)
                {
                    if (Config::instance().net)
                    {
                        initialize_server_info();
                    }
                }
                return;
            }
        }
    }
}



} // namespace elona
