#include "ui_menu_town_chart.hpp"
#include "../area.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

bool UIMenuTownChart::init()
{
    return true;
}

void UIMenuTownChart::update()
{
    listmax = 0;
    page = 0;
    pagesize = 16;
    cs = 0;
    cc = 0;
    cs_bk = -1;
    snd(99);
    curmenu = 0;
    gsel(3);
    pos(960, 96);
    picload(filesystem::dir::graphic() / u8"deco_politics.bmp", 1);
    gsel(0);
    fillbg(3, 960, 96, 128, 128);
    render_hud();
    windowshadow = 1;

    _city = area_data[game_data.current_map].quest_town_id;
    lv = 0;

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

void UIMenuTownChart::draw()
{
    s(0) = i18n::s.get("core.locale.ui.town_chart.title");
    s(1) = strhint3b;
    display_window((windoww - 580) / 2 + inf_screenx, winposy(400), 580, 400);
    keyrange = 0;
    int j0 = 0;
    int n = 0;
    cs_listbk();
    if (area_data[game_data.current_map].quest_town_id == 0
        || game_data.current_dungeon_level != 1)
    {
        font(14 - en * 2);
        pos(wx + 40, wy + 50);
        mes(i18n::s.get("core.locale.ui.town_chart.no_economy"));
    }
    else
    {
        display_topic(
            i18n::s.get(
                "core.locale.ui.town_chart.chart",
                mapname(area_data[game_data.current_map].id)),
            wx + 40,
            wy + 34);
        for (int cnt = 0;; ++cnt)
        {
            if (pochart(j0, n, lv) == 0 || cnt == 0)
            {
                if (cnt != 0)
                {
                    ++n;
                }
                j0 = 0;
                i = 0;
                for (int cnt = 0; cnt < 10; ++cnt)
                {
                    if (pochart(cnt, n, lv) != 0)
                    {
                        ++i;
                    }
                }
                if (i == 0)
                {
                    break;
                }
                y = wy + 70 + n * 55;
            }
            x = wx + (ww - 70) / (i + 1) * (j0 + 1);
            pos(x - 26, y - 3);
            gcopy(3, 960, 288, 144, 24);
            p = pochart(j0, n, lv);
            key_list(cnt) = key_select(cnt);
            ++keyrange;
            display_key(x - 30, y + 21, cnt);
            font(12 + sizefix - en * 2);
            bmes(
                i18n::s.get_enum("core.locale.politics.post", p),
                x - 2,
                y + jp * 2);
            font(14 - en * 2);
            if (podata(0 + cnt, _city) == 0)
            {
                s = i18n::s.get("core.locale.ui.town_chart.empty");
            }
            cs_list(cs == cnt, s, x - 2, y + 20);
            ++j0;
        }
        if (keyrange != 0)
        {
            cs_bk = cs;
        }
    }
}

optional<UIMenuTownChart::ResultType> UIMenuTownChart::on_key(
    const std::string& action)
{
    if (get_selected_index_this_page())
    {
        return UIMenuTownChart::Result::finish();
    }
    else if (action == "next_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            set_reupdate();
        }
    }
    else if (action == "previous_page")
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            set_reupdate();
        }
    }
    else if (action == "cancel")
    {
        update_screen();
        return UIMenuTownChart::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
