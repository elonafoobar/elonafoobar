#ifdef ANDROID
#include "../touch_input.hpp"
#endif

namespace elona
{
namespace snail
{


#include <android/log.h>
#define  LOG_TAG    "ElonaFoobar"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

touch_input& touch_input::instance()
{
    static touch_input the_instance;
    return the_instance;
}

void touch_input::initialize(const fs::path& asset_path)
{
    int width = application::instance().actual_width();
    int height = application::instance().actual_height();
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
            quick_actions_.emplace_back(quick_action{size + (j * size), height - (i * size), keys.at(j + ((2-i) * 3))});
        }
    }

    quick_actions_.emplace_back(quick_action{ size * 1, height - size * 4, snail::key::enter });
    quick_actions_.emplace_back(quick_action{ size * 2, height - size * 4, snail::key::shift });
    quick_actions_.emplace_back(quick_action{ size * 3, height - size * 4, snail::key::escape });
    quick_actions_.emplace_back(quick_action{ size * 4, height - size * 4, snail::key::key_z });
    quick_actions_.emplace_back(quick_action{ size * 5, height - size * 4, snail::key::key_x });

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

static bool is_touched(int x, int y, const quick_action& action)
{
    const constexpr int size = 300/2;

    return x > action.center_x - size && y > action.center_y - size && x <= action.center_x + size && y <= action.center_y + size;
}

void touch_input::draw_quick_action(const quick_action& action)
{
    const constexpr int size = 300/2;
    int x = action.center_x - size;
    int y = action.center_y - size;

    // TODO application::instance

    application::instance().get_renderer().render_image(*quick_action_image_.get(), x, y, size, size);

    if (application::instance().get_renderer().has_font())
    {
        application::instance()
            .get_renderer()
            .set_text_alignment(renderer::text_alignment_t::center);
        application::instance()
            .get_renderer()
            .render_text(action.name, action.center_x, action.center_y, {255, 255, 255}, 7.0);
        application::instance()
            .get_renderer()
            .set_text_alignment(renderer::text_alignment_t::left);
    }

    if (last_touch_x_ && last_touch_y_
        && is_touched(*last_touch_x_, *last_touch_y_, action))
    {
        application::instance()
            .get_renderer()
            .set_blend_mode(snail::blend_mode_t::blend);
        application::instance()
            .get_renderer()
            .set_draw_color({192, 192, 192, 128});
        application::instance()
            .get_renderer()
            .fill_rect(x-(size/2), y-(size/2), size*2, size*2);
        last_touch_x_ = none;
        last_touch_y_ = none;
    }
}

optional<snail::key> touch_input::get_touched_quick_action(::SDL_TouchFingerEvent event)
{
    int norm_x = application::instance().actual_width() * event.x;
    int norm_y = application::instance().actual_height() * event.y;
    const constexpr int size = 300;

    for (auto it = quick_actions_.begin(); it < quick_actions_.end(); it++)
    {
        quick_action action = *it;
        if (is_touched(norm_x, norm_y, action))
        {
            last_touch_x_ = norm_x;
            last_touch_y_ = norm_y;
            return action.key;
        }
    }
    return none;
}

}
}
