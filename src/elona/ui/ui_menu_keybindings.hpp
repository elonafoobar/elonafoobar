#pragma once
#include "../keybind/keybind.hpp"
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuKeybindings : public UIMenu<int>
{
public:
    UIMenuKeybindings()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuKeybindings::ResultType> on_key(
        const std::string& key);

private:
    void _draw_background();
    void _draw_window();
    void _draw_topics();
    void _draw_keys();
    void _draw_keybind_entry(int, const std::string&);
    void _draw_text_entry(int, const std::string&);
    void _draw_single_list_entry(int, int, const std::string&);
    void _draw_list_entries();
};

} // namespace ui
} // namespace elona
