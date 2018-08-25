#include "ui_menu_town_politics.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

bool ui_menu_town_politics::init()
{
    // TODO: untranslated
    listmax = 0;
    page = 0;
    pagesize = 13;
    cs = 0;
    cs_bk = -1;
    curmenu = 2;
    city = adata(28, gdata_current_map);
    list(0, listmax) = 1;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.name", mapname(gdata(815)));
    ++listmax;
    if (mdata_map_type != mdata_t::map_type_t::town)
    {
        goto label_2281_internal;
    }
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.taxes", podata(150, city));
    ++listmax;
    p = rnd(1000);
    list(0, listmax) = 0;
    listn(0, listmax) =
        i18n::s.get("core.locale.ui.politics.well_pollution", p(0));
    ++listmax;
    list(0, listmax) = 0;
    listn(0, listmax) = i18n::s.get("core.locale.ui.politics.lawless");
    ++listmax;

label_2281_internal:
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_politics.bmp", 1);
    gsel(0);
    fillbg(3, 960, 96, 128, 128);
    render_hud();
    gsel(7);
    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp");
    gsel(0);
    windowshadow = 1;
    snd(92);
    city = 1;
    ww = 480;
    wh = 400;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);

    return true;
}

void ui_menu_town_politics::update()
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

void ui_menu_town_politics::draw()
{
    s = strhint2 + strhint3b;
    showscroll(s, wx, wy, ww, wh);
    display_topic(i18n::s.get("core.locale.ui.politics.law"), wx + 65, wy + 45);
    font(12 + sizefix - en * 2);
    pos(wx + 185, wy + 52);
    mes(i18n::s.get("core.locale.ui.politics.global"));
    if (mdata_map_type == mdata_t::map_type_t::town)
    {
        pos(wx + 285, wy + 52);
        mes(i18n::s.get(
            "core.locale.ui.politics.law_of", mapname(gdata_current_map)));
    }
    pos(wx + 155, wy + 46);
    gmode(2);
    gcopy(3, 312, 360, 24, 24);
    pos(wx + 255, wy + 46);
    gmode(2);
    gcopy(3, 288, 360, 24, 24);
    font(14 - en * 2);
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
            boxf(wx + 74, wy + 76 + cnt * 19, 365, 18, {12, 14, 16, 16});
        }
        display_key(wx + 72, wy + 76 + cnt * 19 - 2, cnt);
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
        s = listn(0, p);
        cs_list(cs == cnt, s, wx + 100, wy + 76 + cnt * 19 - 1, 0, 0);
        pos(wx + 42, wy + 68 + cnt * 19 + 2);
        gmode(2);
        gcopy(3, 288 + list(0, p) * 24, 360, 24, 24);
    }
    if (keyrange != 0)
    {
        cs_bk = cs;
    }
}

optional<ui_menu_town_politics::result_type> ui_menu_town_politics::on_key(
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
        return ui_menu_town_politics::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
