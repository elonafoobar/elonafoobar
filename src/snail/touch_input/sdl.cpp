#ifdef ANDROID
#include "../touch_input.hpp"
#endif

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
    const constexpr int size = 300;
    if (false)
    {
        joystick_image_ = std::make_unique<basic_image>(asset_path / "joystick.png");
    }
    quick_action_image_ = std::make_unique<basic_image>(asset_path / "quick_action.png");

    std::vector<snail::key> keys = {snail::key::keypad_7,
                                    snail::key::keypad_8,
                                    snail::key::keypad_9,
                                    snail::key::keypad_4,
                                    snail::key::keypad_5,
                                    snail::key::keypad_6,
                                    snail::key::keypad_1,
                                    snail::key::keypad_2,
                                    snail::key::keypad_3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            quick_actions_.emplace_back(quick_action{ size + (j * size), size + (i * size), keys.at(j + (i * 3))});
        }
    }

    quick_actions_.emplace_back(quick_action{ size * 4, size * 4, snail::key::enter });
    quick_actions_.emplace_back(quick_action{ size * 4, size * 5, snail::key::shift });

    initialized_ = true;
}

void touch_input::draw_quick_actions()
{
    if (!initialized_) {
        return;
    }
    for (auto it = quick_actions_.begin(); it < quick_actions_.end(); it++)
    {
        draw_quick_action(*it);
    }
}

void touch_input::draw_quick_action(const quick_action& action)
{
    const constexpr int size = 300;

    application::instance().get_renderer().render_image(*quick_action_image_.get(), action.center_x - (size/2), action.center_y - (size/2), size/2, size/2);
    // TODO: ttf not initialized
    //renderer.render_text(action.name, action.center_x, action.center_y, {255, 255, 255});
}

optional<snail::key> touch_input::get_touched_quick_action(::SDL_TouchFingerEvent event)
{
    int norm_x = application::instance().width() * event.x;
    int norm_y = application::instance().height() * event.y;
    const constexpr int size = 300;

    for (auto it = quick_actions_.begin(); it < quick_actions_.end(); it++)
    {
        quick_action action = *it;
        if (norm_x > action.center_x - (size/2) && norm_y > action.center_y - (size/2) && norm_x <= action.center_x + (size/2) && norm_y <= action.center_y + (size/2))
        {
            return action.key;
        }
    }

    return none;
}

}
}
