#include "ui_menu_composite_character.hpp"
#include "ui_menu_character_sheet.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_character::add_menus()
{
    push_back(
        std::make_unique<ui_menu_character_sheet>(0, false),
        9,
        "core.locale.ui.menu.chara.chara");
}

} // namespace ui
} // namespace elona
