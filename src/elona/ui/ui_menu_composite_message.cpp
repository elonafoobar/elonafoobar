#include "ui_menu_composite_message.hpp"
#include "ui_menu_chat_history.hpp"
#include "ui_menu_journal.hpp"
#include "ui_menu_message_log.hpp"

namespace elona
{
namespace ui
{

void UIMenuCompositeMessage::add_menus()
{
    push_back(std::make_unique<UIMenuMessageLog>(), 15, "core.ui.menu.log.log");
    push_back(std::make_unique<UIMenuJournal>(), 3, "core.ui.menu.log.journal");
    push_back(
        std::make_unique<UIMenuChatHistory>(), 16, "core.ui.menu.log.chat");
}

} // namespace ui
} // namespace elona
