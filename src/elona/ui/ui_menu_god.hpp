#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuGod : public UIMenu<int>
{
public:
    UIMenuGod(data::InstanceId religion, bool already_believing)
        : _god_id(religion)
        , _already_believing(already_believing)
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuGod::ResultType> on_key(const std::string& key);

private:
    void _draw_window();
    void _draw_title(data::InstanceId);
    void _draw_desc(data::InstanceId);
    void _draw_choice(int, const std::string&);
    void _draw_choices();

    data::InstanceId _god_id;
    bool _already_believing;
};

} // namespace ui
} // namespace elona
