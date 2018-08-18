#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

typedef dummy_result ui_menu_composite_skills_result;

class ui_menu_composite_skills
    : public ui_menu_composite<ui_menu_composite_skills_result>
{
public:
    enum index : size_t
    {
        spells = 0,
        skills = 1
    };

    ui_menu_composite_skills(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
