#pragma once

#include <string>
#include "detail/sdl.hpp"


namespace snail
{


enum MessageBox
{
    error = SDL_MESSAGEBOX_ERROR,
    warning = SDL_MESSAGEBOX_WARNING,
    info = SDL_MESSAGEBOX_INFORMATION,
};


void show_message_box(MessageBox flag, const std::string& title, const std::string& message);



}
