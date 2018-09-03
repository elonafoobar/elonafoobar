#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

struct ui_menu_skills_result
{
    int effect_id;
};

struct ui_menu_spells_result
{
    int effect_id;
};

typedef boost::variant<ui_menu_skills_result, ui_menu_spells_result>
    ui_menu_composite_skills_result;

class UIMenuCompositeSkills
    : public UIMenuComposite<ui_menu_composite_skills_result>
{
public:
    enum Index : size_t
    {
        spells = 0,
        skills = 1
    };

    UIMenuCompositeSkills(size_t selected)
        : UIMenuComposite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
