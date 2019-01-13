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
    virtual optional<UIMenuSpells::ResultType> on_key(const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_spell_attribute(int, int);
    void _draw_spell_name(int, int);
    void _draw_spell_cost(int, int);
    void _draw_spell_power(int, int);
    void _draw_single_list_entry(int, int);
    void _draw_list_entries();

    void _assign_shortcut(int, int);
};

} // namespace ui
} // namespace elona
