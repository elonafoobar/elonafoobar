#pragma once
#include "ui_menu_composite.hpp"

namespace elona
{
namespace ui
{

class UIMenuCompositeTown : public UIMenuComposite<DummyResult>
{
public:
    enum class Index : size_t
    {
        chart = 0,
        economy = 1,
        politics = 2
    };

    UIMenuCompositeTown(size_t selected)
        : UIMenuComposite(selected)
    {
    }

protected:
    virtual void add_menus();
};

} // namespace ui
} // namespace elona
