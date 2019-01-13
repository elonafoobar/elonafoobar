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
    virtual optional<UIMenuSkills::ResultType> on_key(const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_skill_attribute(int, int);
    void _draw_skill_name(int, int);
    void _draw_spell_cost(int, int);
    void _draw_spell_desc_and_power(int, int);
    void _draw_single_list_entry(int, int);
    void _draw_list_entries();

    void _assign_shortcut(int, int);
};

} // namespace ui
} // namespace elona
