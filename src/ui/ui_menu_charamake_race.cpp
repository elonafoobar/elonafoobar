#include "ui_menu_charamake_race.hpp"
#include "../audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_charamake_race::init()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 16;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.select_race.caption");
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    listmax = 0;
    for (const auto& race : the_race_db.get_available_races(false))
    {
        listn(1, listmax) = race.get().id;
        list(0, listmax) = 0;
        ++listmax;
    }
    if (config::instance().extrarace)
    {
        for (const auto& race : the_race_db.get_available_races(true))
        {
            listn(1, listmax) = race.get().id;
            list(0, listmax) = 1;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = i18n::_(u8"race", listn(1, cnt), u8"name");
        if (list(0, cnt) == 1)
        {
            listn(0, cnt) = u8"(extra)"s + listn(0, cnt);
        }
    }
    windowshadow = 1;

    return true;
}

void ui_menu_charamake_race::update()
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

void ui_menu_charamake_race::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    s(0) = i18n::s.get("core.locale.chara_making.select_race.title");
    s(1) = strhint3b;
    display_window(
        (windoww - 680) / 2 + inf_screenx, winposy(500, 1) + 20, 680, 500);
    ++cmbg;
    x = ww / 5 * 2;
    y = wh - 80;
    pos(wx + ww / 4, wy + wh / 2);
    gmode(4, 50);
    gcopy_c(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.race"),
        wx + 28,
        wy + 30);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_race.detail"),
        wx + 188,
        wy + 30);
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
    {
        p = page * pagesize + cnt;
        if (p >= listmax)
        {
            break;
        }
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
        cs_list(cs == cnt, listn(0, p), wx + 64, wy + 66 + cnt * 19 - 1);
    }
    cs_bk = cs;
    pos(wx + 200, wy + 66);
    chara_delete(0);
    access_race_info(3, listn(1, page * pagesize + cs));
    access_race_info(11, listn(1, page * pagesize + cs));
    show_race_or_class_info(0);
}

optional<ui_menu_charamake_race::result_type> ui_menu_charamake_race::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_INDEX(p);

    if (p != -1)
    {
        return ui_menu_charamake_race::result::finish(p(0));
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
        return ui_menu_charamake_race::result::cancel();
    }
    else if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_race::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
