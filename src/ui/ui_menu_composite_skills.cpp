#include "ui_menu_composite_skills.hpp"
#include "ui_menu_skills.hpp"
#include "ui_menu_spells.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_skills::add_menus()
{
    push_back(
        std::make_unique<ui_menu_spells>(),
        13,
        102,
        "core.locale.ui.menu.spell.spell");
    push_back(
        std::make_unique<ui_menu_skills>(),
        14,
        101,
        "core.locale.ui.menu.spell.skill");
}

} // namespace ui
} // namespace elona
