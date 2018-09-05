#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuChatHistory : public UIMenu<DummyResult>
{
public:
    UIMenuChatHistory()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuChatHistory::ResultType> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
