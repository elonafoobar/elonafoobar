#include "ui_menu_adventurers.hpp"
#include "../audio.hpp"
#include "../character.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

void ui_menu_adventurers::init()
{
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    for (int cnt = 0; cnt < 56; ++cnt)
    {
        if (cdata[cnt].state() == character::state_t::empty)
        {
            continue;
        }
        list(0, listmax) = cnt;
        list(1, listmax) = -cdata[cnt].fame;
        ++listmax;
    }
    sort_list_by_column1();
    windowshadow = 1;
}

void ui_menu_adventurers::update()
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

void ui_menu_adventurers::draw()
{
    s(0) = i18n::s.get("core.locale.ui.adventurers.title");
    s(1) = strhint2 + strhint3;
    display_window((windoww - 640) / 2 + inf_screenx, winposy(448), 640, 448);
    display_topic(
        i18n::s.get("core.locale.ui.adventurers.name_and_rank"),
        wx + 28,
        wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.adventurers.fame_lv"), wx + 320, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.adventurers.location"), wx + 420, wy + 36);
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
        if (cnt % 2 == 0)
        {
            boxf(wx + 70, wy + 66 + cnt * 19, 540, 18, {12, 14, 16, 16});
        }
        display_key(wx + 58, wy + 66 + cnt * 19 - 2, cnt);
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

        draw_chara_scale_height(
            cdata[list(0, p)], wx + 40, wy + 74 + cnt * 19 - 8);

        pos(wx + 84, wy + 66 + cnt * 19 + 2);
        mes(cnvrank(p + 1)
            + i18n::s.get("core.locale.ui.adventurers.rank_counter"));
        i = list(0, p);
        s = ""s + cdatan(1, i) + u8" "s + cdatan(0, i);
        cutname(s, 26);
        cs_list(cs == cnt, s, wx + 118, wy + 66 + cnt * 19 - 1);
        s = ""s + cdata[i].fame + u8"("s + cdata[i].level + u8")"s;
        pos(wx + 402 - strlen_u(s) * 7, wy + 66 + cnt * 19 + 2);
        mes(s);
        s = mapname(cdata[i].current_map);
        if (s == ""s)
        {
            s = i18n::s.get("core.locale.ui.adventurers.unknown");
        }
        if (cdata[i].state() == character::state_t::adventurer_dead)
        {
            s = i18n::s.get("core.locale.ui.adventurers.hospital");
        }
        pos(wx + 435, wy + 66 + cnt * 19 + 2);
        mes(s);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_adventurers::result_type> ui_menu_adventurers::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_ITEM(p, 0);

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
    else if (key == key_cancel)
    {
        return ui_menu_adventurers::result::finish();
    }

    return none;
}
} // namespace ui
} // namespace elona
