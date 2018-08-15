#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_scene : public ui_menu<dummy_result>
{
public:
    ui_menu_scene()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_scene::result_type> on_key(const std::string& key);
};

} // namespace ui
} // namespace elona
