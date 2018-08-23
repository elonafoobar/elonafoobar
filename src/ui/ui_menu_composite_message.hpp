#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class ui_menu_composite_message : public ui_menu_composite<dummy_result>
{
public:
    enum Index : size_t
    {
        message_log = 0,
        journal = 1,
        chat_history = 2
    };

    ui_menu_composite_message(size_t selected)
        : ui_menu_composite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
