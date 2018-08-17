#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_crafting : public ui_menu<int>
{
public:
    ui_menu_crafting(int prodtype, int invctrl)
        : _prodtype(prodtype)
        , _invctrl(invctrl)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_crafting::result_type> on_key(
        const std::string& key);

private:
    int _prodtype;
    int _invctrl;
};

} // namespace ui
} // namespace elona
