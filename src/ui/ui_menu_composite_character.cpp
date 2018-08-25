#include "ui_menu_composite_character.hpp"
#include "../menu.hpp"
#include "ui_menu_character_sheet.hpp"
#include "ui_menu_equipment.hpp"
#include "ui_menu_feats.hpp"
#include "ui_menu_materials.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_character::add_menus()
{
    push_back(
        std::make_unique<ui_menu_character_sheet>(
            character_sheet_operation::normal),
        9,
        "core.locale.ui.menu.chara.chara");
    push_back(
        std::make_unique<ui_menu_equipment>(),
        10,
        "core.locale.ui.menu.chara.wear");
    push_back(
        std::make_unique<ui_menu_feats>(ui_menu_feats::operation::normal),
        11,
        "core.locale.ui.menu.chara.feat");
    push_back(
        std::make_unique<ui_menu_materials>(),
        12,
        "core.locale.ui.menu.chara.material");
}

} // namespace ui
} // namespace elona
