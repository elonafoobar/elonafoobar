#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_skills.hpp"

namespace elona
{
namespace ui
{

class UIMenuSkills : public UIMenu<ui_menu_composite_skills_result>
{
public:
    UIMenuSkills()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuSkills::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
