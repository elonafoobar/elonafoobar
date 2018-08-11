#pragma once
#include "ui_menu.hpp"

namespace elona
{
struct item;

namespace ui
{

class ui_menu_item_desc : public ui_menu<dummy_result>
{
public:
    ui_menu_item_desc(const item& the_item)
        : _the_item(the_item)
    {
    }

protected:
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_item_desc::result_type> on_key(
        const std::string& key);

private:
    const item& _the_item;
};

} // namespace ui
} // namespace elona
