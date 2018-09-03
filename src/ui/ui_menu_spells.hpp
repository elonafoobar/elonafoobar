#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_skills.hpp"

namespace elona
{
namespace ui
{

class UIMenuSpells : public UIMenu<UIMenuCompositeSkillsResult>
{
public:
    UIMenuSpells()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuSpells::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
