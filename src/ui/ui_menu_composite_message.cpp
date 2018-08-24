#include "ui_menu_composite_message.hpp"
#include "ui_menu_chat_history.hpp"
#include "ui_menu_journal.hpp"
#include "ui_menu_message_log.hpp"

namespace elona
{
namespace ui
{

void ui_menu_composite_message::add_menus()
{
    push_back(
        std::make_unique<ui_menu_message_log>(),
        15,
        "core.locale.ui.menu.log.log");
    push_back(
        std::make_unique<ui_menu_journal>(),
        3,
        "core.locale.ui.menu.log.journal");
    push_back(
        std::make_unique<ui_menu_chat_history>(),
        16,
        "core.locale.ui.menu.log.chat");
}

} // namespace ui
} // namespace elona
