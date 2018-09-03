#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class UIMenuCompositeMessage : public UIMenuComposite<DummyResult>
{
public:
    enum Index : size_t
    {
        message_log = 0,
        journal = 1,
        chat_history = 2
    };

    UIMenuCompositeMessage(size_t selected)
        : UIMenuComposite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
