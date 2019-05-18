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
    void _draw_normal_mark(int, int);
    void _draw_marks(int, int);
    void _draw_message(int, int, const std::string&);

    const Item& _the_item;
};

} // namespace ui
} // namespace elona
