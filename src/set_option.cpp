#include "audio.hpp"
#include "config.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "macro.hpp"
#include "menu.hpp"
#include "network.hpp"
#include "ui.hpp"
#include "variables.hpp"

#include <sstream>

using namespace elona;


namespace
{

class config_menu_item_base
{
public:
    std::string name;
    std::string key;

    config_menu_item_base(const std::string& key, const i18n_key& locale_key)
        : key(key)
    {
        name = i18n::s.get(locale_key + ".name");
    }

    virtual ~config_menu_item_base() noexcept = default;

    virtual void change(int) {}
    virtual std::string get_message() { return ""; }
};


class config_menu_item_yesno : public config_menu_item_base
{
public:
    bool variable;
    std::string yes;
    std::string no;

    config_menu_item_yesno(
        const std::string& key,
        const i18n_key& locale_key,
        bool variable,
        const std::string& yes,
        const std::string& no)
        : config_menu_item_base(key, locale_key)
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

        config::instance().set(key, variable);
    }
    std::string get_message() { return variable ? yes : no; }

    virtual ~config_menu_item_yesno() noexcept = default;
};


class config_menu_item_info : public config_menu_item_base
{
public:
    std::string info;

    config_menu_item_info(const std::string& key,
                          const i18n_key& locale_key,
                          const std::string& info)
        : config_menu_item_base(key, locale_key)
        , info(info)
    {
    }

    virtual ~config_menu_item_info() noexcept = default;

    std::string get_message() { return info; }
};


class config_menu_item_integer : public config_menu_item_base
{
public:
    int variable;
    int min;
    int max;
    std::string text;

    config_menu_item_integer(
        const std::string& key,
        const i18n_key& locale_key,
        int variable,
        int min,
        int max,
        const std::string& text)
        : config_menu_item_base(key, locale_key)
        , variable(variable)
        , min(min)
        , max(max)
        , text(text)
    {
    }

    void change(int delta)
    {
        variable = clamp(variable + delta, min, max);
        config::instance().set(key, variable);
    }

    std::string get_message()
    {
        return i18n::fmt_hil(text, variable);
    }

    virtual ~config_menu_item_integer() noexcept = default;
};


class config_menu_item_choice : public config_menu_item_base
{
public:
    struct choice
    {
        choice(std::string value, i18n_key message_key)
            : value(value)
            , message_key(message_key) {}

        std::string value;
        i18n_key message_key;
    };

    int index;
    bool translate_variants;
    std::vector<choice> variants;

    config_menu_item_choice(
        const std::string& key,
        const i18n_key& locale_key,
        std::string default_choice,
        const std::vector<choice>& variants,
        bool translate_variants)
        : config_menu_item_base(key, locale_key)
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
            throw std::runtime_error("No such enum variant \"" + default_choice + "\" in \"" + key + "\".");
        }
        // If the enum variant is injected, but the selected value is
        // still unknown, try to set its index to the first known
        // value if there is one.
        if (variants.size() >= 2 && index == 0
            && variants.at(index).value == spec::unknown_enum_variant)
        {
            index = 1;
            config::instance().set(key, variants.at(index).value);
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
        config::instance().set(key, variants.at(index).value);
    }

    std::string get_message()
    {
        i18n_key locale_key = variants.at(index).message_key;
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

    virtual ~config_menu_item_choice() noexcept = default;
};

class config_menu
{
public:
    std::string title;
    std::vector<std::unique_ptr<config_menu_item_base>> items;
    int width;
    int height;

    config_menu(const std::string& title, int width, int height)
        : title(title)
        , width(width)
        , height(height)
    {
    }

    virtual void draw() const
    {
    }
};

class config_menu_submenu : public config_menu
{
public:
    config_menu_submenu(const std::string& title, int width, int height)
        : config_menu(title, width, height) {}

    void draw() const
    {
        pos(wx + 40, wy + wh - 70);
        font(12 + sizefix - en * 2);
        mes(i18n::s.get("core.locale.config.common.require_restart"));
    }
};

class config_menu_joypad : public config_menu
{
public:
    void draw() const
    {
        pos(wx + 40, wy + wh - 110);
        font(12 + sizefix - en * 2);
        mes(i18n::s.get("core.locale.config.common.assign_button"));
    }
};


typedef std::vector<std::unique_ptr<config_menu>> config_screen;


// Functions for adding items to the config screen.

template <class M>
static void add_config_menu(const spec_key& key,
                            const i18n_key& menu_name_key,
                            const config_def& def,
                            int width,
                            config_screen& ret)
{
    auto children = def.get_children(key);
    int w = width;
    int h = 165 + (19 * children.size());
    ret.emplace_back(std::make_unique<M>(i18n::s.get(menu_name_key), w, h));
}


static void add_config_item_yesno(const spec_key& key,
                                  const i18n_key& locale_key,
                                  bool default_value,
                                  config_screen& ret)
{
    i18n_key yes_no;

    // Determine which text to use for true/false ("Yes"/"No", "Play"/"Don't Play", etc.)
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

    ret.back()->items.emplace_back(
        std::make_unique<config_menu_item_yesno>(
            key, locale_key,
            default_value,
            yes_text, no_text)
        );
}

static void add_config_item_integer(const spec_key& key,
                                    const i18n_key& locale_key,
                                    int default_value,
                                    const config_def& def,
                                    config_screen& ret)
{
    int min = def.get_min(key);
    int max = def.get_max(key);

    ret.back()->items.emplace_back(
        std::make_unique<config_menu_item_integer>(
            key, locale_key,
            default_value,
            min, max, "${_1}")
        );
}

static void add_config_item_choice(const spec_key& key,
                                   const i18n_key& locale_key,
                                   const std::string& default_value,
                                   const config_def& def,
                                   config_screen& ret)
{
    // Add the translated names of all variants.
    const auto& variants = def.get_variants(key);
    std::vector<config_menu_item_choice::choice> choices;

    for (const auto& variant : variants)
    {
        auto choice = config_menu_item_choice::choice{
            variant, locale_key + ".variants." + variant
        };
        choices.emplace_back(choice);
    }

    bool translate_variants = def.get_metadata(key).translate_variants;

    ret.back()->items.emplace_back(
        std::make_unique<config_menu_item_choice>(
            key, locale_key,
            default_value, choices,
            translate_variants)
        );
}

static void add_config_item_section(const spec_key& key,
                                    const i18n_key& locale_key,
                                    const std::string section_name,
                                    const config_def& def,
                                    config_screen& ret)
{
    // EX: "<core.config>.<language>"
    spec_key section_key = key + "." + section_name;

    if (def.get_metadata(section_key).visible)
    {
        // EX: "<core.locale.config.menu>.<language>"
        i18n_key section_locale_key = locale_key + "." + section_name;

        ret.back()->items.emplace_back(
            std::make_unique<config_menu_item_base>(section_key, section_locale_key));
    }
}


// Functions for visiting the parsed config structure.

void visit_section(config&, const spec_key&, config_screen&);
void visit_config_item(config&, const spec_key&, config_screen&);


void visit_toplevel(config& conf, config_screen& ret)
{
    spec_key key = "core.config";
    i18n_key locale_key = conf.get_def().get_locale_root();
    i18n_key menu_name_key = locale_key + ".name";

    // Add the top level menu.
    add_config_menu<config_menu>(key, menu_name_key, conf.get_def(), 370, ret);

    // Add the names of top-level config menu sections if they are visible.
    for (const auto& section_name : conf.get_def().get_children(key))
    {
        add_config_item_section(key, locale_key, section_name, conf.get_def(), ret);
    }

    // Add all sections and their config items.
    for (const auto& child : conf.get_def().get_children(key))
    {
        visit_section(conf, child, ret);
    }
}

void visit_section(config& conf, const spec_key& current_key, config_screen& ret)
{
    // EX: "<core.config>.<language>"
    spec_key key = "core.config." + current_key;

    // EX: "<core.locale.config.menu>.language"
    i18n_key locale_key = conf.get_def().get_locale_root() + "." + current_key;
    i18n_key menu_name_key = locale_key + ".name";

    // Ensure the section exists in the config definition.
    if (!conf.get_def().exists(key))
    {
        throw std::runtime_error("No such config option \"" + current_key + "\".");
    }
    // Ignore this section if it is not user-visible.
    if (!conf.get_def().get_metadata(key).visible)
    {
        return;
    }

    // Add the submenu.
    add_config_menu<config_menu_submenu>(key, menu_name_key, conf.get_def(), 440, ret);

    // Visit child config items of this section.
    for (const auto& child : conf.get_def().get_children(key))
    {
        visit_config_item(conf, current_key + "." + child, ret);
    }
}

void visit_config_item(config& conf, const spec_key& current_key, config_screen& ret)
{
    spec_key key = "core.config." + current_key;
    i18n_key locale_key = conf.get_def().get_locale_root() + "." + current_key;

    if (!conf.get_def().exists(key))
    {
        throw std::runtime_error("No such config option \"" + current_key + "\".");
    }
    if (!conf.get_def().get_metadata(key).visible)
    {
        return;
    }

    if (conf.get_def().is<spec::bool_def>(key))
    {
        add_config_item_yesno(key, locale_key, conf.get<bool>(key), ret);
    }
    else if (conf.get_def().is<spec::int_def>(key))
    {
        add_config_item_integer(key, locale_key, conf.get<int>(key), conf.get_def(), ret);
    }
    else if (conf.get_def().is<spec::enum_def>(key))
    {
        add_config_item_choice(key, locale_key, conf.get<std::string>(key), conf.get_def(), ret);
    }
    else if (conf.get_def().is<spec::string_def>(key))
    {
        // ignore
        // TODO: don't ignore, allow text input
    }
    else if (conf.get_def().is<spec::list_def>(key))
    {
        // ignore
    }
    else if (conf.get_def().is<spec::section_def>(key))
    {
        throw std::runtime_error("You cannot currently define nested sections.");
    }
    else
    {
        throw std::runtime_error("Unknown config def item");
    }
}


config_screen create_config_screen()
{
    config_screen ret;
    auto& conf = config::instance();

    visit_toplevel(conf, ret);

    return ret;
}

} // namespace



namespace elona
{

int submenu = 0;

void set_option()
{
    const auto config_screen = create_config_screen();

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

    auto& menu_def = config_screen[submenu];
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
        s(1) = strhint3;
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
        display_topic(i18n::s.get("core.locale.config.common.menu"), wx + 34, wy + 36);
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
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
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
            //     if (config::instance().net == 0)
            //     {
            //         if (cnt >= 1)
            //         {
            //             continue;
            //         }
            //     }
            // }
            cs_list(cs == cnt, s, wx + 56 + x, wy + 66 + cnt * 19 - 1, 0);
            if ((true || cnt <= 0) && submenu != 0)
            {
                pos(wx + 220, wy + 66 + cnt * 19 - 5);
                gcopy(3, 312, 336, 24, 24);
                pos(wx + 358, wy + 66 + cnt * 19 - 5);
                gcopy(3, 336, 336, 24, 24);
            }
            pos(wx + 250, wy + 66 + cnt * 19);

            mes(config_screen[submenu]->items[cnt].get()->get_message());
        }

        config_screen[submenu]->draw();

        if (keyrange != 0)
        {
            cs_bk = cs;
        }
        redraw();
        await(config::instance().wait1);
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

            config_screen[submenu]->items[cs].get()->change(p);
            snd(20);
            reset_page = true;
            continue;
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
                config::instance().write();
                if (mode == 0)
                {
                    if (config::instance().net)
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
