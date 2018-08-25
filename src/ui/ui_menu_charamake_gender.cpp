#include "ui_menu_charamake_gender.hpp"
#include "../audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_charamake_gender::init()
{
    cs = 0;
    cs_bk = -1;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = i18n::s.get("core.locale.chara_making.select_gender.caption");
    draw_caption();
    font(13 - en * 2, snail::font_t::style_t::bold);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    windowshadow = 1;

    return true;
}

void ui_menu_charamake_gender::update()
{
}

void ui_menu_charamake_gender::draw()
{
    s(0) = i18n::s.get("core.locale.chara_making.select_gender.title");
    s(1) = strhint3b;
    display_window(
        (windoww - 370) / 2 + inf_screenx, winposy(168, 1) - 20, 370, 168);
    x = ww / 2;
    y = wh - 60;
    pos(wx + ww / 2, wy + wh / 2);
    gmode(4, 30);
    gcopy_c(2, 0, 0, 180, 300, x, y);
    gmode(2);
    display_topic(
        i18n::s.get("core.locale.chara_making.select_gender.gender"),
        wx + 28,
        wy + 30);
    listn(0, 0) = cnven(i18n::_(u8"ui", u8"male"));
    listn(0, 1) = cnven(i18n::_(u8"ui", u8"female"));
    font(14 - en * 2);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        pos(wx + 38, wy + 66 + cnt * 19 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
    }
    cs_bk = cs;
}

optional<ui_menu_charamake_gender::result_type>
ui_menu_charamake_gender::on_key(const std::string& key)
{
    if (key == key_select(0))
    {
        return ui_menu_charamake_gender::result::finish(0);
    }
    else if (key == key_select(1))
    {
        return ui_menu_charamake_gender::result::finish(1);
    }
    else if (key == key_cancel)
    {
        return ui_menu_charamake_gender::result::cancel();
    }
    else if (getkey(snail::key::f1))
    {
        show_game_help();
        return ui_menu_charamake_gender::result::finish();
    }

    return none;
}

} // namespace ui
} // namespace elona
