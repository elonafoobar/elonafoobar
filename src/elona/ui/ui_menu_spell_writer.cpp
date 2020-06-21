#include "ui_menu_spell_writer.hpp"

#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"
#include "../message.hpp"

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
    snd("core.pop2");
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
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

void UIMenuSpellWriter::_draw_window()
{
    ui_display_window(
        i18n::s.get("core.ui.reserve.title"),
        strhint2 + strhint3,
        (windoww - 540) / 2 + inf_screenx,
        winposy(448),
        540,
        448);
    display_topic(i18n::s.get("core.ui.reserve.name"), wx + 28, wy + 36);
    display_topic(i18n::s.get("core.ui.reserve.status"), wx + 390, wy + 36);
}

void UIMenuSpellWriter::_draw_key(int cnt)
{
    if (cnt % 2 == 0)
    {
        boxf(wx + 70, wy + 66 + cnt * 19, 440, 18, {12, 14, 16, 16});
    }
    display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
}

void UIMenuSpellWriter::_draw_keys()
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

void UIMenuSpellWriter::_draw_list_entry_image(int cnt)
{
    const constexpr int _book_item_chip = 429;
    draw_item_material(_book_item_chip, wx + 38, wy + 73 + cnt * 19);
}

void UIMenuSpellWriter::_draw_list_entry_name(int cnt, int item_index)
{
    std::string item_name = ioriginalnameref(item_index);
    cs_list(cs == cnt, item_name, wx + 84, wy + 66 + cnt * 19 - 1);
}

void UIMenuSpellWriter::_draw_list_entry_reserve_status(int cnt, int item_index)
{
    if (itemmemory(2, item_index) == 1)
    {
        mes(wx + 400,
            wy + 66 + cnt * 19 + 2,
            i18n::s.get("core.ui.reserve.not_reserved"),
            {120, 120, 120});
    }
    else
    {
        mes(wx + 400,
            wy + 66 + cnt * 19 + 2,
            i18n::s.get("core.ui.reserve.reserved"),
            {55, 55, 255});
    }
}

void UIMenuSpellWriter::_draw_list_entry(int cnt, int item_index)
{
    _draw_list_entry_image(cnt);
    _draw_list_entry_name(cnt, item_index);
    _draw_list_entry_reserve_status(cnt, item_index);
}

void UIMenuSpellWriter::_draw_list_entries()
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

optional<UIMenuSpellWriter::ResultType> UIMenuSpellWriter::on_key(
    const std::string& action)
{
    if (auto selected = get_selected_item())
    {
        if (_book_is_unavailable(*selected))
        {
            snd("core.fail1");
            txt(i18n::s.get("core.ui.reserve.unavailable"));
            set_reupdate();
        }
        else
        {
            snd("core.ok1");
            _toggle_book_reserve(*selected);
            set_reupdate();
        }
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd("core.pop1");
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        return UIMenuSpellWriter::Result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
