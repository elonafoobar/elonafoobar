#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_message_log : public ui_menu<dummy_result>
{
public:
    ui_menu_message_log()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_message_log::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
