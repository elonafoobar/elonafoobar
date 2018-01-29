#include "messagebox.hpp"

using namespace snail;



void show_message_box(MessageBox flag, const std::string& title, const std::string& message)
{
    ::SDL_ShowSimpleMessageBox(
        static_cast<::SDL_MessageBoxFlags>(flag),
        title.c_str(),
        message.c_str(),
        nullptr);
}
