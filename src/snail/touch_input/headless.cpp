namespace elona
{
namespace snail
{

touch_input& touch_input::instance()
{
    static touch_input the_instance;
    return the_instance;
}

void touch_input::initialize(const fs::path& asset_path)
{
}

void touch_input::initialize_quick_actions()
{
}

void touch_input::draw_quick_actions()
{
}

void touch_input::draw_quick_action(const quick_action&)

void touch_input::on_touch_event(::SDL_TouchFingerEvent)
{
}

}
}
