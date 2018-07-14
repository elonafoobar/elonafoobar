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
    quick_action(std::string name, snail::key key, int center_x, int center_y)
        : name(name)
        , key(key)
        , center_x(center_x)
        , center_y(center_y) {}

    int center_x;
    int center_y;
    snail::key key;
    std::string name;

    bool touched = false;
};

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

    optional<snail::key> last_touched_key() const { return last_touched_key_; }

    void initialize(const fs::path&);
    void initialize_quick_actions();
    void draw_quick_actions();
    void on_touch_event(::SDL_TouchFingerEvent);

private:
    touch_input() = default;
    void draw_quick_action(const quick_action&);
    std::vector<quick_action> quick_actions_;
    bool initialized_ = false;
    optional<snail::key> last_touched_key_ = none;

    std::unique_ptr<basic_image> quick_action_image_ = nullptr;
    std::unique_ptr<basic_image> joystick_image_ = nullptr;
};

} // namespace snail
} // namespace elona
