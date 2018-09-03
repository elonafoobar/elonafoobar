namespace elona
{
namespace snail
{

TouchInput& TouchInput::instance()
{
    static TouchInput the_instance;
    return the_instance;
}

void TouchInput::initialize(const fs::path& asset_path)
{
}

void TouchInput::initialize_quick_actions()
{
}

void TouchInput::draw_quick_actions()
{
}

void TouchInput::draw_quick_action(const quick_action&)
{
}

void TouchInput::on_touch_event(::SDL_TouchFingerEvent)
{
}

} // namespace snail
} // namespace elona
