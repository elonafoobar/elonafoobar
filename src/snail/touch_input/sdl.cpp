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
    if (false)
    {
        joystick_image_ = std::make_unique<basic_image>(asset_path / "joystick.png");
    }
    quick_action_image_ = std::make_unique<basic_image>(asset_path / "quick_action.png");

    std::vector<snail::key> keys = {snail::key::keypad_7, snail::key::keypad_8,
                                    snail::key::keypad_9,
                                    snail::key::keypad_4,
                                    snail::key::keypad_5,
                                    snail::key::keypad_6,
                                    snail::key::keypad_1,
                                    snail::key::keypad_2,
                                    snail::key::keypad_3
    };
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; i++)
        {
            quick_actions_.emplace_back(quick_action{ 128 + (i * 128), 128 + (j * 128), keys.at(j + (i * 3))});
        }
    }

    quick_actions_.emplace_back(quick_action{ 128, 1024, snail::key::enter });
}

void touch_input::draw_quick_actions()
{
    for (auto it = quick_actions_.begin(); it < quick_actions_.end(); it++)
    {
        draw_quick_action(*it);
    }
}

void touch_input::draw_quick_action(const quick_action& action)
{
    auto renderer = application::instance().get_renderer();
    const constexpr int size = 128;

    renderer.render_image(*quick_action_image_.get(), action.center_x - (size/2), action.center_y - (size/2), size/2, size/2);
    renderer.render_text(action.name, action.center_x, action.center_y, {255, 255, 255});
}

optional<snail::key> touch_input::get_touched_quick_action(::SDL_TouchFingerEvent event)
{
    for (auto it = quick_actions_.begin(); it < quick_actions_.end(); it++)
    {
        quick_action action = *it;
        if (event.x > action.center_x - 64 && event.y > action.center_y - 64 && event.x <= action.center_x + 64 && event.x <= action.center_y + 64)
        {
            return action.key;
        }
    }

    return none;
}

}
}
