#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuEquipment : public UIMenu<ui_menu_composite_character_result>
{
public:
    UIMenuEquipment()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuEquipment::result_type> on_key(
        const std::string& key);

private:
    int _cs_prev = 0;
    int _mainhand = 0;

    bool _show_resistances = false;
};

} // namespace ui
} // namespace elona
