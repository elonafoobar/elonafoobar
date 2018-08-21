#include "ui_menu_materials.hpp"
#include "audio.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_materials::init()
{
    listmax = 0;
    page = 0;
    pagesize = 15;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    curmenu = 3;
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        if (mat(cnt) != 0)
        {
            list(0, listmax) = cnt;
            ++listmax;
        }
    }
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp");
    gsel(0);
    snd(92);
    drawmenu();
    wx = (windoww - 600) / 2 + inf_screenx;
    wy = winposy(430);
    ww = 600;
    wh = 430;
    window_animation(wx, wy, ww, wh, 9, 4);
    windowshadow = 1;
}

void ui_menu_materials::update()
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
    drawmenu();
}

void ui_menu_materials::draw()
{
    s = strhint2 + strhint3b;
    showscroll(s, wx, wy, ww, wh);
    display_topic(
        i18n::s.get("core.locale.ui.material.name"), wx + 38, wy + 36);
    display_topic(
        i18n::s.get("core.locale.ui.material.detail"), wx + 296, wy + 36);
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
            boxf(wx + 70, wy + 66 + cnt * 19, 490, 18, {12, 14, 16, 16});
        }
        display_key(wx + 68, wy + 66 + cnt * 19 - 2, cnt);
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
        i = list(0, p);
        s = ""s + matname(i) + " " + i18n::s.get("core.locale.crafting.menu.x")
            + " " + mat(i);
        cs_list(cs == cnt, s, wx + 96, wy + 66 + cnt * 19 - 1, 0, 0);
        s = matdesc(i);
        pos(wx + 308, wy + 66 + cnt * 19 + 2);
        mes(s);

        draw_item_material(matref(2, i), wx + 47, wy + 69 + cnt * 19 + 2);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_materials::result_type> ui_menu_materials::on_key(
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
        update_screen();
        return ui_menu_materials::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
