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
    virtual optional<UIMenuMaterials::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
