#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuEquipment : public UIMenu<UIMenuCompositeCharacterResult>
{
public:
    UIMenuEquipment()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuEquipment::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window_background();
    void _draw_window_deco(bool);
    void _draw_window_headers();
    void _draw_window(bool);
    void _draw_key(int, int, bool);
    void _draw_keys(int);
    void _draw_list_entries(bool);

    int _cs_prev = 0;
    int _mainhand = 0;
};

} // namespace ui
} // namespace elona
