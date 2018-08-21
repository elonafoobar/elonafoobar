#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_equipment : public ui_menu<dummy_result>
{
public:
    ui_menu_equipment()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_equipment::result_type> on_key(
        const std::string& key);

private:
    int _cs_prev = 0;
    int _mainhand = 0;
};

} // namespace ui
} // namespace elona
