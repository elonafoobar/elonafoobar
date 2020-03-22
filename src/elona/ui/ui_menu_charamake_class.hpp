#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

struct UIMenuCharamakeClassResult
{
    data::InstanceId class_id;
};



class UIMenuCharamakeClass : public UIMenu<UIMenuCharamakeClassResult>
{
public:
    UIMenuCharamakeClass(data::InstanceId race_id)
        : _race_id(race_id)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuCharamakeClass::ResultType> on_key(
        const std::string& key);

private:
    void _draw_window();
    void _draw_choice(int, const std::string&);
    void _draw_choices();

    data::InstanceId _race_id;
};

} // namespace ui
} // namespace elona
