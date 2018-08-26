#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class ui_menu_composite_town : public ui_menu_composite<dummy_result>
{
public:
    enum index : size_t
    {
        chart = 0,
        economy = 1,
        politics = 2
    };

    ui_menu_composite_town(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
