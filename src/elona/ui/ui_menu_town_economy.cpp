#include "ui_menu_town_economy.hpp"
#include "../area.hpp"
#include "../audio.hpp"
#include "../draw.hpp"
#include "../i18n.hpp"

namespace elona
{
namespace ui
{

static void _show_economy_info(
    int x,
    int y,
    const std::string& text,
    int value,
    int prev_value)
{
    mes(x, y, text);

    mes(x + 130, y, ""s + value);

    const auto diff = value - prev_value;
    const auto text_color =
        diff >= 0 ? snail::Color{0, 0, 150} : snail::Color{150, 0, 0};
    mes(x + 130 + ginfo(14) + 12, y, u8"("s + diff + u8")"s, text_color);
}

bool UIMenuTownEconomy::init()
{

    key_list(0) = key_enter;
    keyrange = 0;
    pagesize = 1;
    listmax = 2;
    asset_load("deco_politics");
    gsel(0);
    draw_bg("deco_politics_a");
    render_hud();
    gsel(7);
    picload(filesystem::dir::graphic() / u8"ie_scroll.bmp", 0, 0, true);
    gsel(0);
    windowshadow = 1;
    snd("core.scroll");
    _city = 1;
    ww = 540;
    wh = 440;
    wx = (windoww - ww) / 2 + inf_screenx;
    wy = winposy(wh);

    return true;
}

void UIMenuTownEconomy::update()
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

void UIMenuTownEconomy::_draw_window()
{
    std::string hint = strhint2 + strhint3b;
    showscroll(hint, wx, wy, ww, wh);
    font(14 - en * 2);
}

void UIMenuTownEconomy::_draw_economy_info(int _city)
{
    display_topic(
        i18n::s.get("core.locale.ui.economy.information"), wx + 65, wy + 50);
    display_topic(
        i18n::s.get("core.locale.ui.economy.finance"), wx + 65, wy + 150);

    font(14 - en * 2);
    x = wx + 50;
    y = wy + 80;
    _show_economy_info(
        x,
        y,
        i18n::s.get("core.locale.ui.economy.population"),
        podata(100, _city),
        podata(101, _city));

    x = wx + 50;
    y = wy + 180;
    _show_economy_info(
        x,
        y,
        i18n::s.get("core.locale.ui.economy.basic_tax") + u8" ("s +
            game_data.politics_tax_amount + u8"%)"s,
        podata(102, _city),
        podata(103, _city));
    _show_economy_info(
        x,
        y + 16,
        i18n::s.get("core.locale.ui.economy.excise_tax") + u8" ("s +
            podata(150, _city) + u8"%)"s,
        podata(104, _city),
        podata(105, _city));
}

void UIMenuTownEconomy::_draw_economy_details()
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

static bool _map_has_economy()
{
    return area_data[game_data.current_map].quest_town_id != 0 &&
        game_data.current_dungeon_level == 1;
}

void UIMenuTownEconomy::draw()
{
    _draw_window();

    if (_map_has_economy())
    {
        if (page == 0)
        {
            _draw_economy_info(_city);
        }
        if (page == 1)
        {
            _draw_economy_details();
        }
    }
    else
    {
        mes(wx + 40,
            wy + 60,
            i18n::s.get("core.locale.ui.city_chart.no_economy"));
    }
}

optional<UIMenuTownEconomy::ResultType> UIMenuTownEconomy::on_key(
    const std::string& action)
{
    if (action == "next_page")
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
    else if (action != ""s)
    {
        update_screen();
        return UIMenuTownEconomy::Result::cancel();
    }

    return none;
}

} // namespace ui
} // namespace elona
