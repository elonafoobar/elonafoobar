#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_charamake_race : public ui_menu<int>
{
public:
    ui_menu_charamake_race()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_charamake_race::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
