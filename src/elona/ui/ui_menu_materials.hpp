#pragma once
#include "ui_menu.hpp"
#include "ui_menu_composite_character.hpp"

namespace elona
{
namespace ui
{

class UIMenuMaterials : public UIMenu<UIMenuCompositeCharacterResult>
{
public:
    UIMenuMaterials()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuMaterials::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_key(int);
    void _draw_keys();
    void _draw_single_list_entry_name(int, int);
    void _draw_single_list_entry_desc(int, int);
    void _draw_single_list_entry(int, int);
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
