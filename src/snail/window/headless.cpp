namespace elona
{
namespace snail
{


void window::move_to_center()
{
}

std::pair<int, int> window::get_size()
{
    return {800, 600};
}

void window::set_size(int width, int height)
{
}

void window::set_display_mode(::SDL_DisplayMode display_mode)
{
}

::SDL_DisplayMode window::get_display_mode()
{
    ::SDL_DisplayMode mode{};
    return mode;
}

void window::set_fullscreen_mode(FullscreenMode fullscreen_mode)
{
}

window::window(
    const std::string& title,
    int x,
    int y,
    int width,
    int height,
    int flag)
{
}



} // namespace snail
} // namespace elona
