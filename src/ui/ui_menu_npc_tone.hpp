#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class ui_menu_npc_tone : public ui_menu<std::string>
{
public:
    ui_menu_npc_tone()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_npc_tone::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
