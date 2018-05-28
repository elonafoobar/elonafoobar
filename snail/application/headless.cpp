#include <algorithm>
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


void application::set_title(const std::string& title)
{
}



void application::initialize(int width, int height, const std::string& title)
{
}





void application::quit()
{
    _will_quit = true;
}



void application::register_finalizer(std::function<void()> finalizer)
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


} // namespace snail
} // namespace elona
