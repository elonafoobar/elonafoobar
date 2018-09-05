#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct Item;

namespace ui
{

class UIMenuItemDesc : public UIMenu<DummyResult>
{
public:
    UIMenuItemDesc(const Item& the_item)
        : _the_item(the_item)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuItemDesc::ResultType> on_key(const std::string& key);

private:
    const Item& _the_item;
};

} // namespace ui
} // namespace elona
