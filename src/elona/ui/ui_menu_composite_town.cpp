#include "ui_menu_composite_town.hpp"

#include "ui_menu_town_chart.hpp"
#include "ui_menu_town_economy.hpp"
#include "ui_menu_town_politics.hpp"

namespace elona
{
namespace ui
{

void UIMenuCompositeTown::add_menus()
{
    push_back(
        std::make_unique<UIMenuTownChart>(), 19, "core.ui.menu.town.chart");
    push_back(
        std::make_unique<UIMenuTownEconomy>(), 20, "core.ui.menu.town.economy");
    push_back(
        std::make_unique<UIMenuTownPolitics>(),
        21,
        "core.ui.menu.town.politics");
}

} // namespace ui
} // namespace elona
