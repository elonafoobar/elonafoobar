#include "ui_menu_config.hpp"
#include "../audio.hpp"
#include "../config/config.hpp"
#include "../config/config_menu.hpp"
#include "../i18n.hpp"
#include "../menu.hpp"
#include "../network.hpp"
#include "simple_prompt.hpp"

namespace elona
{
namespace ui
{

static void _draw_background()
{
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
}

bool UIMenuConfig::init()
{
    listmax = 0;
    page = 0;
    pagesize = 18;
    cc = 0;
    cs_bk = -1;
    page_bk = 0;
    cs_bk2 = 0;

    _draw_background();

    for (const auto& menu_item : _menu.items)
    {
        list(0, listmax) = listmax;
        listn(0, listmax) = menu_item->name;
        ++listmax;
    }

    windowshadow = 1;

    return true;
}

void UIMenuConfig::update()
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
}

static void _draw_window(const std::string& title, int width, int height)
{
    s(0) = title;
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
}

static void _draw_deco()
{
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
}

static void _draw_keys(bool is_root_menu)
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        if (is_root_menu)
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
}

static void _draw_arrows(int item_pos)
{
    pos(wx + 220, wy + 66 + item_pos * 19 - 5);
    gcopy(3, 312, 336, 24, 24);
    pos(wx + 358, wy + 66 + item_pos * 19 - 5);
    gcopy(3, 336, 336, 24, 24);
}

static void _draw_items(ConfigMenu& menu, bool is_root_menu)
{
    font(14 - en * 2);
    cs_listbk();

    int item_pos = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        auto item = menu.items[cnt].get();

        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        i = list(0, p);
        s = listn(0, p);
        if (is_root_menu)
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
        cs_list(cs == item_pos, s, wx + 56 + x, wy + 66 + item_pos * 19 - 1, 0);
        if ((true || cnt <= 0) && !is_root_menu)
        {
            _draw_arrows(item_pos);
        }
        pos(wx + 250, wy + 66 + cnt * 19);

        mes(item->get_message());

        item_pos++;
    }
}

void UIMenuConfig::draw()
{
    _draw_window(_menu.title, _menu.width, _menu.height);
    _draw_deco();

    pagesize = listmax;

    _draw_keys(_submenu_index == 0);
    _draw_items(_menu, _submenu_index == 0);

    _menu.draw();

    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

class ConfigItemDescPrompt : public SimplePrompt<DummyResult>
{
public:
    ConfigItemDescPrompt(std::string message)
        : SimplePrompt(message)
    {
    }

protected:
    optional<DummyResult> update() override
    {
        await(Config::instance().wait1);
        auto action = key_check();

        if (action != ""s)
        {
            return DummyResult{};
        }

        return none;
    }
};

static void _show_config_item_desc(const std::string& desc)
{
    ConfigItemDescPrompt(desc).query();
}

optional<UIMenuConfig::ResultType> UIMenuConfig::on_key(
    const std::string& action)
{
    if (auto submenu = get_selected_item())
    {
        cs = _index;
        if (_submenu_index == 0)
        {
            cs = 0;
            snd("core.ok1");
            return UIMenuConfig::Result::finish(*submenu + 1);
        }
    }
    else if (action == "next_page" || action == "previous_page")
    {
        int delta{};
        if (action == "next_page")
        {
            delta = 1;
        }
        else
        {
            delta = -1;
        }

        _menu.items[cs].get()->change(delta);
        snd("core.ok1");
        set_reupdate();
        return none;
    }
    else if (action == "switch_mode_2")
    {
        auto desc = _menu.items[cs].get()->get_desc();
        _show_config_item_desc(desc);

        // Restart with same index so background can be redrawn again in the
        // title screen.
        return UIMenuConfig::Result::finish(_submenu_index);
    }
    if (action == "cancel")
    {
        if (_submenu_index != 0)
        {
            // TODO nested menus
            cs = _submenu_index - 1;
            return UIMenuConfig::Result::finish(0);
        }
        else
        {
            Config::instance().save();
            return UIMenuConfig::Result::finish();
        }
    }

    return none;
}

} // namespace ui
} // namespace elona
