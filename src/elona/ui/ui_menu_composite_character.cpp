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

void UIMenuCompositeCharacter::add_menus()
{
    push_back(
        std::make_unique<UIMenuCharacterSheet>(CharacterSheetOperation::normal),
        9,
        "core.ui.menu.chara.chara");
    push_back(
        std::make_unique<UIMenuEquipment>(), 10, "core.ui.menu.chara.wear");
    push_back(
        std::make_unique<UIMenuFeats>(UIMenuFeats::Operation::normal),
        11,
        "core.ui.menu.chara.feat");
    push_back(
        std::make_unique<UIMenuMaterials>(), 12, "core.ui.menu.chara.material");
}

} // namespace ui
} // namespace elona
