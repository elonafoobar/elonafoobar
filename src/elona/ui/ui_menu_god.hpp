#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuGod : public UIMenu<int>
{
public:
    UIMenuGod(int god_id, bool already_believing)
        : _god_id(god_id)
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
    void _draw_title(int);
    void _draw_desc(int);
    void _draw_choice(int, const std::string&);
    void _draw_choices();

    int _god_id;
    bool _already_believing;
};

} // namespace ui
} // namespace elona
