#include "ui_menu_item_desc.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../item.hpp"

namespace elona
{
namespace ui
{

void ui_menu_item_desc::init()
{
    snd(26);
    page_save();
    page = 0;
    pagesize = 15;
    listmax = 0;
    p = 0;
    s = "";

    item_dump_desc(_the_item);

    windowshadow = 1;
}

void ui_menu_item_desc::update()
{
    key_list = key_enter;
    keyrange = 0;
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

void ui_menu_item_desc::draw()
{
    s(0) = i18n::s.get("core.locale.item.desc.window.title");
    s(1) = strhint4 + strhint3;
    display_window((windoww - 600) / 2 + inf_screenx, winposy(408), 600, 408);
    display_topic(itemname(ci), wx + 28, wy + 34);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        font(14 - en * 2);
        color(0, 0, 0);
        pos(wx + 68, wy + 68 + cnt * 18);
        if (list(0, p) % 10000 == 1)
        {
            color(0, 100, 0);
        }
        if (list(0, p) % 10000 == 2)
        {
            color(0, 0, 100);
        }
        if (list(0, p) % 10000 == 3)
        {
            color(80, 100, 0);
        }
        if (list(0, p) % 10000 == 4)
        {
            color(80, 50, 0);
        }
        if (list(0, p) % 10000 == 9)
        {
            color(180, 0, 0);
        }
        if (list(0, p) % 10000 == 8)
        {
            color(0, 100, 100);
        }
        if (list(0, p) == -1)
        {
            font(13 - en * 2);
        }
        if (list(0, p) == -2)
        {
            font(13 - en * 2, snail::font_t::style_t::italic);
            pos(wx + ww - strlen_u(listn(0, p)) * 6 - 80, wy + 68 + cnt * 18);
        }
        mes(listn(0, p));
        color(0, 0, 0);
        if (list(0, p) > 0)
        {
            pos(wx + 40, wy + 61 + cnt * 18);
            gcopy(3, 72 + list(0, p) % 10000 * 24, 336, 24, 24);
        }
        if (list(0, p) > 10000)
        {
            elona::draw("inheritance_mark", wx + 15, wy + 63 + cnt * 18);
        }
    }
}

optional<ui_menu_item_desc::result_type> ui_menu_item_desc::on_key(
    const std::string& key)
{
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (key == key_cancel || key == key_enter)
    {
        return ui_menu_item_desc::result_type::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
