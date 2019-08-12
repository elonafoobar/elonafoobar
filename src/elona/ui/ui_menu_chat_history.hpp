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

private:
    std::vector<std::string> _chats;

    void _load_chat_history();
    void _draw_messages();
};

} // namespace ui
} // namespace elona
