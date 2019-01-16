#include <iostream>
#include "../application.hpp"

namespace elona
{
namespace snail
{
namespace hsp
{

int timeGetTime()
{
    return 0;
}

void mes(int, int, const std::string&, const snail::Color&)
{
}

void mesbox(std::string&, int, bool)
{
}

void picload(Image&, int, int, bool)
{
}



void redraw()
{
}

void set_color_mod(int, int, int, int)
{
}

void onkey_0()
{
}

void await(int)
{
}

void boxf(int, int, int, int, const snail::Color&)
{
}

void boxf(const snail::Color&)
{
}

void buffer(int, int, int)
{
}

void font(int, snail::Font::Style, const fs::path&)
{
}

void gcopy(int, int, int, int, int, int, int, int, int)
{
}

int ginfo(int)
{
    return 0;
}

void gmode(int, int)
{
}



void grotate(int, int, int, int, int, int, int, double)
{
}



void grotate(int, int, int, int, int, int, int, int, int, double)
{
}



void gsel(int)
{
}



void line(int, int, int, int, const snail::Color&)
{
}

void title(
    const std::string& title_str,
    const std::string&,
    Window::FullscreenMode)
{
    Application::instance().initialize(title_str);
}


} // namespace hsp
} // namespace snail
} // namespace elona
