#pragma once
#include <string>
#include <vector>
#include "../lib/noncopyable.hpp"
#include "../optional.hpp"
#include "application.hpp"
#include "detail/sdl.hpp"
#include "filesystem.hpp"
#include "image.hpp"
#include "input.hpp"

namespace elona
{
namespace snail
{

struct quick_action
{
    quick_action(std::string text, optional<snail::key> key, int center_x, int center_y)
        : center_x(center_x)
        , center_y(center_y)
        , key(key)
        , text(text) {}

    int center_x;
    int center_y;

    // If "key" is none, then "text" will be sent to the input text
    // buffer (as if SDL_TextInputEvent was received). Otherwise, said
    // key will be pressed/released. This is because key detection for
    // alphanumeric keys is handled through SDL_TextInputEvent, but
    // non-alphanumeric keys use SDL_KeyboardEvent. This is a result
    // of the use of HSP's "mesbox" function to check if alphanumeric
    // keys are pressed by checking the string input it receives.
    optional<snail::key> key;
    std::string text;

    bool touched = false;
};

// TODO
// portrait(classic), portrait(fullscreen), landscape(classic), landscape(fullscreen)
// screen magni for fullscreen (x1, x2, x3, x4)
// screen resolution for classic (800x600, 1024x768, etc.)
// show/hide on-screen buttons
// joystick or tenkey buttons
// toggle or hold shift(/alt?)
// quick action functions/positions
// quick action sizes
// vibration
// automatic saving/loading of quick action buttons (needs custom config value type)

class touch_input : public lib::noncopyable
{
    enum event_type {
        motion = SDL_FINGERMOTION,
        down = SDL_FINGERDOWN,
        up = SDL_FINGERUP,
    };

public:
    virtual ~touch_input() override = default;
    static touch_input& instance();

    optional<quick_action> last_touched_quick_action() const
    {
        if (last_touched_quick_action_idx_)
        {
            return quick_actions_.at(*last_touched_quick_action_idx_);
        }
        return none;
    }

    void initialize(const fs::path&);
    void initialize_quick_actions();
    void draw_quick_actions();
    void on_touch_event(::SDL_TouchFingerEvent);

private:
    touch_input() = default;
    void draw_quick_action(const quick_action&);
    std::vector<quick_action> quick_actions_;
    optional<size_t> last_touched_quick_action_idx_ = none;
    bool initialized_ = false;

    std::unique_ptr<basic_image> quick_action_image_ = nullptr;
    std::unique_ptr<basic_image> joystick_image_ = nullptr;
};

} // namespace snail
} // namespace elona
