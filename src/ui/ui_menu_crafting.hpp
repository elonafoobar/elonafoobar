#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuCrafting : public UIMenu<int>
{
public:
    UIMenuCrafting(int prodtype, int invctrl)
        : _prodtype(prodtype)
        , _invctrl(invctrl)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCrafting::ResultType> on_key(
        const std::string& key);

private:
    int _prodtype;
    int _invctrl;
};

} // namespace ui
} // namespace elona
