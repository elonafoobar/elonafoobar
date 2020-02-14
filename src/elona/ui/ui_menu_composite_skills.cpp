#include "ui_menu_composite_skills.hpp"

#include "ui_menu_skills.hpp"
#include "ui_menu_spells.hpp"

namespace elona
{
namespace ui
{

void UIMenuCompositeSkills::add_menus()
{
    push_back(std::make_unique<UIMenuSpells>(), 13, "core.ui.menu.spell.spell");
    push_back(std::make_unique<UIMenuSkills>(), 14, "core.ui.menu.spell.skill");
}

} // namespace ui
} // namespace elona
