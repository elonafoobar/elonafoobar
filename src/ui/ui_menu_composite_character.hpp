#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class ui_menu_composite_character : public ui_menu_composite<dummy_result>
{
public:
    enum index : size_t
    {
        character_sheet = 0,
        materials = 1,
        feats = 2,
        equipment = 3
    };

    ui_menu_composite_character(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
