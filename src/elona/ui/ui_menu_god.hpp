#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuGod : public UIMenu<int>
{
public:
    UIMenuGod(std::string god_id, bool already_believing)
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
    void _draw_title(const std::string&);
    void _draw_desc(const std::string&);
    void _draw_choice(int, const std::string&);
    void _draw_choices();

    std::string _god_id;
    bool _already_believing;
};

} // namespace ui
} // namespace elona
