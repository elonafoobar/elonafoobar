#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct item;

namespace ui
{

class UIMenuItemDesc : public UIMenu<dummy_result>
{
public:
    UIMenuItemDesc(const item& the_item)
        : _the_item(the_item)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuItemDesc::result_type> on_key(
        const std::string& key);

private:
    const item& _the_item;
};

} // namespace ui
} // namespace elona
