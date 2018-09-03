#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuCharamakeGender : public UIMenu<int>
{
public:
    UIMenuCharamakeGender()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharamakeGender::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
