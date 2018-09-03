#include "ui_menu_spell_writer.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

static void _populate_book_list()
{
    for (int cnt = 0; cnt < maxitemid; ++cnt)
    {
        if (itemmemory(2, cnt) == 0)
        {
            continue;
        }
        list(0, listmax) = cnt;
        list(1, listmax) = cnt;
        ++listmax;
    }
    sort_list_by_column1();
}

bool UIMenuSpellWriter::init()
{
    snd(26);
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    windowshadow = 1;

    _populate_book_list();

    return true;
}

void UIMenuSpellWriter::update()
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

static void _draw_window()
{
    s(0) = i18n::s.get("core.locale.ui.reserve.title");
    s(1) = strhint2 + strhint3;
    display_window((windoww - 540) / 2 + inf_screenx, winposy(448), 540, 448);
    display_topic(i18n::s.get("core.locale.ui.reserve.name"), wx + 28, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.reserve.status"), wx + 390, wy + 36);
}

static void _draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 440, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

static void _draw_keys()
{
    keyrange = 0;
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = pagesize * page + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        ++keyrange;
        _draw_key(cnt);
    }
}

static void _draw_list_entry_image(int cnt)
{
    const constexpr int _book_item_chip = 429;
    draw_item_material(_book_item_chip, wx + 38, wy + 73 + cnt * 19);
}

static void _draw_list_entry_name(int cnt, int item_index)
{
    std::string item_name = ioriginalnameref(item_index);
    cs_list(cs == cnt, item_name, wx + 84, wy + 66 + cnt * 19 - 1);
}

static void _draw_list_entry_reserve_status(int cnt, int item_index)
{
    pos(wx + 400, wy + 66 + cnt * 19 + 2);
    if (itemmemory(2, item_index) == 1)
    {
        color(120, 120, 120);
        mes(i18n::s.get("core.locale.ui.reserve.not_reserved"));
        color(0, 0, 0);
    }
    else
    {
        color(55, 55, 255);
        mes(i18n::s.get("core.locale.ui.reserve.reserved"));
        color(0, 0, 0);
    }
}

static void _draw_list_entry(int cnt, int item_index)
{
    _draw_list_entry_image(cnt);
    _draw_list_entry_name(cnt, item_index);
    _draw_list_entry_reserve_status(cnt, item_index);
}

static void _draw_list_entries()
{
    font(14 - en * 2);
    cs_listbk();
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        int index = pagesize * page + cnt;
        if (index >= listmax)
        {
            break;
        }
        int item_index = list(0, index);

        _draw_list_entry(cnt, item_index);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

void UIMenuSpellWriter::draw()
{
    _draw_window();
    _draw_keys();
    _draw_list_entries();
}

static bool _book_is_unavailable(int _p)
{
    return _p == 289 || _p == 732;
}

static void _toggle_book_reserve(int _p)
{
    if (itemmemory(2, _p) == 1)
    {
        itemmemory(2, _p) = 2;
    }
    else
    {
        itemmemory(2, _p) = 1;
    }
}

optional<UIMenuSpellWriter::result_type> UIMenuSpellWriter::on_key(
    const std::string& key)
{
    int _p;

    ELONA_GET_SELECTED_ITEM(_p, 0);

    if (_p != -1)
    {
        if (_book_is_unavailable(_p))
        {
            snd(27);
            txt(i18n::s.get("core.locale.ui.reserve.unavailable"));
            set_reupdate();
        }
        else
        {
            snd(20);
            _toggle_book_reserve(_p);
            set_reupdate();
        }
    }
    else if (key == key_pageup)
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
    else if (key == key_cancel)
    {
        return UIMenuSpellWriter::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
