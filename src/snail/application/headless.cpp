#include <algorithm>
#include <map>
#include "../input.hpp"


namespace elona
{
namespace snail
{



application& application::instance()
{
    static application the_instance;
    return the_instance;
}


void application::set_title(const std::string&)
{
}



void initialize(const std::string&)
{
}





void application::quit()
{
    _will_quit = true;
}



void application::register_finalizer(std::function<void()>)
{
}



void application::main_loop()
{
    while (1)
    {
        if (_will_quit)
            return;
    }
}



void application::proc_event()
{
}


void set_fullscreen_mode(window::fullscreen_mode_t)
{
}

void set_display_mode(const std::string&)
{
}

void set_display_mode(const ::SDL_DisplayMode)
{
}

} // namespace snail
} // namespace elona
