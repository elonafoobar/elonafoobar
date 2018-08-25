#include "ui_menu_charamake_class.hpp"
#include "../audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_charamake_class::init()
{
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.select_class.caption");
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
    for (const auto& class_ : the_class_db.get_available_classes(false))
    {
        listn(1, listmax) = class_.get().id;
        ++listmax;
    }
    if (config::instance().extraclass)
    {
        for (const auto& class_ : the_class_db.get_available_classes(true))
        {
            listn(1, listmax) = class_.get().id;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        access_class_info(2, listn(1, cnt));
        listn(0, cnt) = classname;
    }
    windowshadow = 1;

    return true;
}

void ui_menu_charamake_class::update()
{
}

void ui_menu_charamake_class::draw()
{
    if (cs == cs_bk)
    {
        return;
    }

    s(0) = i18n::s.get("core.locale.chara_making.select_class.title");
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
        i18n::s.get("core.locale.chara_making.select_class.class"),
        wx + 28,
        wy + 30);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_class.detail"),
        wx + 188,
        wy + 30);
    font(14 - en * 2);
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
        if (jp)
        {
            s = listn(0, cnt);
        }
        else
        {
            s = cnven(listn(1, cnt));
        }
        cs_list(cs == cnt, s, wx + 64, wy + 66 + cnt * 19 - 1);
    }
    cs_bk = cs;
    pos(wx + 200, wy + 66);
    chara_delete(0);
    access_class_info(3, listn(1, cs));
    access_class_info(11, listn(1, cs));
    show_race_or_class_info(1);
    redraw();
}

optional<ui_menu_charamake_class::result_type> ui_menu_charamake_class::on_key(
    const std::string& key)
{
    ELONA_GET_SELECTED_INDEX(p);

    if (p != -1)
    {
        int class_id = p;
        std::string klass = listn(1, class_id);
        return ui_menu_charamake_class::result::finish(klass);
    }
    if (key == key_cancel)
    {
        return ui_menu_charamake_class::result::cancel();
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_class::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
