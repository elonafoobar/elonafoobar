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
    virtual optional<UIMenuCharamakeGender::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_choice(int, const std::string&);
    void _draw_choices();
};

} // namespace ui
} // namespace elona
