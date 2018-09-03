#pragma once
#include "ui_menu.hpp"

namespace elona
{
namespace ui
{

class UIMenuChatHistory : public UIMenu<dummy_result>
{
public:
    UIMenuChatHistory()
    {
    }

protected:
    virtual bool init();
    virtual void update();
    virtual void draw();
    virtual optional<UIMenuChatHistory::result_type> on_key(
        const std::string& key);
};

} // namespace ui
} // namespace elona
