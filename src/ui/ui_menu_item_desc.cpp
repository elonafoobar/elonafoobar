#include "ui_menu_item_desc.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../item.hpp"
#include "../snail/color.hpp"

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

static snail::color _desc_to_color(int desc)
{
    switch (desc)
    {
    case desc_entry_t::raises_skill: return {0, 100, 0};
    case desc_entry_t::raises_stat: return {0, 0, 100};
    case desc_entry_t::raises_resist: return {80, 100, 0};
    case desc_entry_t::enchantment: return {80, 50, 0};
    case desc_entry_t::maintains_skill: return {0, 100, 100};
    case desc_entry_t::negative_effect: return {180, 0, 0};
    }

    return {0, 0, 0};
}

static void _set_color(int list_item)
{
    int desc = list_item % 10000;
    auto col = _desc_to_color(desc);
    color(col.r, col.g, col.b);
}

static void _set_font(int list_item)
{
    if (list_item == desc_entry_t::small_font)
    {
        font(13 - en * 2);
    }
    else if (list_item == desc_entry_t::small_font_italic)
    {
        font(13 - en * 2, snail::font_t::style_t::italic);
    }
    else
    {
        font(14 - en * 2);
    }
}

static void _set_pos(int cnt, int list_item, const std::string& list_text)
{
    if (list_item == desc_entry_t::small_font_italic)
    {
        pos(wx + ww - strlen_u(list_text) * 6 - 80, wy + 68 + cnt * 18);
    }
    else
    {
        pos(wx + 68, wy + 68 + cnt * 18);
    }
}

static void _draw_normal_mark(int cnt, int list_item)
{
    int desc = list_item % 10000;
    int mark_pos_x = desc * 24;
    pos(wx + 40, wy + 61 + cnt * 18);
    gcopy(3, 72 + mark_pos_x, 336, 24, 24);
}

static void _draw_marks(int cnt, int list_item)
{
    if (list_item > desc_entry_t::normal)
    {
        _draw_normal_mark(cnt, list_item);
    }
    if (list_item > 10000)
    {
        elona::draw("inheritance_mark", wx + 15, wy + 63 + cnt * 18);
    }
}

static void _draw_message(int cnt, int list_item, const std::string& list_text)
{
    _set_color(list_item);
    _set_font(list_item);
    _set_pos(cnt, list_item, list_text);

    mes(list_text);
    color(0, 0, 0);

    _draw_marks(cnt, list_item);
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

        _draw_message(cnt, list(0, p), listn(0, p));
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
