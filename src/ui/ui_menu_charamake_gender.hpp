#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_charamake_gender : public ui_menu<int>
{
public:
    ui_menu_charamake_gender()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_gender::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
