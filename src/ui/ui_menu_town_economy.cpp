#include "ui_menu_town_economy.hpp"
#include "../audio.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

static void showeconomy(
    int prm_1086,
    int prm_1087,
    const std::string& prm_1088,
    int prm_1089,
    int prm_1090)
{
    int p_at_m195 = 0;
    pos(prm_1086, prm_1087);
    mes(prm_1088);
    pos(prm_1086 + 130, prm_1087);
    mes(""s + prm_1089);
    p_at_m195 = prm_1089 - prm_1090;
    if (p_at_m195 >= 0)
    {
        color(0, 0, 150);
    }
    else
    {
        color(150, 0, 0);
    }
    pos(prm_1086 + 130 + ginfo(14) + 12, prm_1087);
    mes(u8"("s + p_at_m195 + u8")"s);
    color(0, 0, 0);
    return;
}

bool ui_menu_town_economy::init()
{
    curmenu = 1;
    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 1;
    listmax = 2;
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
    drawmenu(3);
    city = 1;
    ww = 540;
    wh = 440;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);

    return true;
}

void ui_menu_town_economy::update()
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

void ui_menu_town_economy::draw()
{
    s = strhint2 + strhint3b;
    showscroll(s, wx, wy, ww, wh);
    font(14 - en * 2);
    if (adata(28, gdata_current_map) == 0 || gdata_current_dungeon_level != 1)
    {
        pos(wx + 40, wy + 60);
        mes(i18n::s.get("core.locale.ui.city_chart.no_economy"));
    }
    else
    {
        if (page == 0)
        {
            display_topic(
                i18n::s.get("core.locale.ui.economy.information"),
                wx + 65,
                wy + 50);
            display_topic(
                i18n::s.get("core.locale.ui.economy.finance"),
                wx + 65,
                wy + 150);
            font(14 - en * 2);
            x = wx + 50;
            y = wy + 80;
            showeconomy(
                x,
                y,
                i18n::s.get("core.locale.ui.economy.population"),
                podata(100, city),
                podata(101, city));
            x = wx + 50;
            y = wy + 180;
            showeconomy(
                x,
                y,
                i18n::s.get("core.locale.ui.economy.basic_tax") + u8" ("s
                    + gdata(820) + u8"%)"s,
                podata(102, city),
                podata(103, city));
            showeconomy(
                x,
                y + 16,
                i18n::s.get("core.locale.ui.economy.excise_tax") + u8" ("s
                    + podata(150, city) + u8"%)"s,
                podata(104, city),
                podata(105, city));
        }
        if (page == 1)
        {
            display_topic(
                i18n::s.get("core.locale.ui.economy.population_detail"),
                wx + 65,
                wy + 50);
            display_topic(
                i18n::s.get("core.locale.ui.economy.finance_detail"),
                wx + 65,
                wy + 200);
            font(14 - en * 2);
        }
    }
}

optional<ui_menu_town_economy::result_type> ui_menu_town_economy::on_key(
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
    else if (key != ""s)
    {
        update_screen();
        return ui_menu_town_economy::result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
