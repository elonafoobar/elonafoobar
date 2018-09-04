#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_skills.hpp"

namespace elona
{
namespace ui
{

class UIMenuSkills : public UIMenu<UIMenuCompositeSkillsResult>
{
public:
    UIMenuSkills()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuSkills::ResultType> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
