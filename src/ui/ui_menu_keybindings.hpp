#pragma once
#include "../keybind/keybind.hpp"
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuKeybindings : public UIMenu<DummyResult>
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
};

} // namespace ui
} // namespace elona
