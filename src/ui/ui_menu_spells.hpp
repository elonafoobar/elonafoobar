#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_skills.hpp"

namespace elona
{
namespace ui
{

class ui_menu_spells : public ui_menu<ui_menu_composite_skills_result>
{
public:
    ui_menu_spells()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<ui_menu_spells::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
