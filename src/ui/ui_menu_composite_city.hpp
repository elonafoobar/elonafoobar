#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class ui_menu_composite_city : public ui_menu_composite<dummy_result>
{
public:
    enum index : size_t
    {
        chart = 0,
        city = 1,
        law = 2
    };

    ui_menu_composite_city(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
