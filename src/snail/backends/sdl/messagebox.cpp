#include "../../messagebox.hpp"
#include "../../detail/sdl.hpp"



namespace elona
{
namespace snail
{

::SDL_MessageBoxFlags to_sdl_message_box_flags(MessageBox mb)
{
    switch (mb)
    {
    case MessageBox::error: return SDL_MESSAGEBOX_ERROR;
    case MessageBox::warning: return SDL_MESSAGEBOX_WARNING;
    case MessageBox::info: return SDL_MESSAGEBOX_INFORMATION;
    default: throw "unreachable";
    }
}



void show_message_box(
    MessageBox flag,
    const std::string& title,
    const std::string& message)
{
    ::SDL_ShowSimpleMessageBox(
        to_sdl_message_box_flags(flag),
        title.c_str(),
        message.c_str(),
        nullptr);
}

} // namespace snail
} // namespace elona
