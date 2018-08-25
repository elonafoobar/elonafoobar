#include "ui_menu_composite_town.hpp"
#include "ui_menu_town_chart.hpp"
#include "ui_menu_town_economy.hpp"
#include "ui_menu_town_politics.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_town::add_menus()
{
    push_back(
        std::make_unique<ui_menu_town_chart>(),
        19,
        "core.locale.ui.menu.town.chart");
    push_back(
        std::make_unique<ui_menu_town_economy>(),
        20,
        "core.locale.ui.menu.town.economy");
    push_back(
        std::make_unique<ui_menu_town_politics>(),
        21,
        "core.locale.ui.menu.town.politics");
}

} // namespace ui
} // namespace elona
