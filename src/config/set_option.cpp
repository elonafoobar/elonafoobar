#include "../audio.hpp"
#include "../draw.hpp"
#include "../elona.hpp"
#include "../i18n.hpp"
#include "../input.hpp"
#include "../macro.hpp"
#include "../menu.hpp"
#include "../network.hpp"
#include "../snail/application.hpp"
#include "../ui.hpp"
#include "../variables.hpp"
#include "config.hpp"
#include "config_menu.hpp"
#include "create_config_screen.hpp"

#include <sstream>

using namespace elona;


namespace
{


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

    // auto result = ui::UIMenuConfig(menu_def).show();

    // if (result.value)
    // {
    //     submenu = *result.value;
    //     goto set_option_begin;
    // }

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
