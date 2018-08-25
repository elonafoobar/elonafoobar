#include "ui_menu_composite_city.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_city::add_menus()
{
    // push_back(
    //     std::make_unique<ui_menu_town_chart>(),
    //     19,
    //     "core.locale.ui.menu.town.chart");
    push_back(
        std::make_unique<ui_menu_city_chart>(),
        20,
        "core.locale.ui.menu.town.city");
    // push_back(
    //     std::make_unique<ui_menu_town_laws>(),
    //     21,
    //     "core.locale.ui.menu.town.law");
}

} // namespace ui
} // namespace elona
