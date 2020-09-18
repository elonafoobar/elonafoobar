#include "ui_menu_town_chart.hpp"

#include "../area.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../game.hpp"
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
    cs_bk = -1;
    snd("core.chat");
    asset_load("core.deco_politics");
    gsel(0);
    draw_bg("core.deco_politics_a");
    render_hud();
    windowshadow = 1;

    _city = area_data[game()->current_map].quest_town_id;

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
    static const std::vector<std::vector<int>> posts{
        {2},
        {3, 4},
        {5, 6},
    };

    ui_display_window(
        i18n::s.get("core.ui.town_chart.title"),
        strhint3b,
        (windoww - 580) / 2 + inf_screenx,
        winposy(400),
        580,
        400);
    keyrange = 0;
    cs_listbk();
    if (area_data[game()->current_map].quest_town_id == 0 ||
        game()->current_dungeon_level != 1)
    {
        font(14 - en * 2);
        mes(wx + 40, wy + 50, i18n::s.get("core.ui.town_chart.no_economy"));
    }
    else
    {
        display_topic(
            i18n::s.get(
                "core.ui.town_chart.chart",
                mapname(area_data[game()->current_map].id)),
            wx + 40,
            wy + 34);

        size_t post_count = 0;
        size_t row_count = 0;
        for (const auto& row : posts)
        {
            size_t column_count = 0;
            for (const auto& column : row)
            {
                const auto x =
                    wx + (ww - 70) / (row.size() + 1) * (column_count + 1);
                const auto y = wy + 70 + row_count * 55;

                elona::draw("core.deco_politics_b", x - 26, y - 3);

                key_list(post_count) = key_select(post_count);
                ++keyrange;
                display_key(x - 30, y + 21, post_count);

                font(12 + sizefix - en * 2);
                bmes(
                    i18n::s.get_enum("core.politics.post", column),
                    x - 2,
                    y + jp * 2);

                font(14 - en * 2);
                std::string assigned;
                if (podata(post_count, _city) == 0)
                {
                    assigned = i18n::s.get("core.ui.town_chart.empty");
                }
                cs_list(
                    cs == static_cast<int>(post_count),
                    assigned,
                    x - 2,
                    y + 20);

                ++column_count;
                ++post_count;
            }
            ++row_count;
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
        update_screen();
        return UIMenuTownChart::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
