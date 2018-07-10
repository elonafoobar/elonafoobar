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
    quick_action(int center_x, int center_y, snail::key key)
        : center_x(center_x)
        , center_y(center_y)
        , key(key)
    {
        name = "k";
    }

    int center_x;
    int center_y;
    snail::key key;
    std::string name;
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

public:
    virtual ~touch_input() override = default;
    static touch_input& instance();
    void initialize(const fs::path&);
    void draw_quick_actions();
    optional<snail::key> get_touched_quick_action(::SDL_TouchFingerEvent event);

private:
    touch_input() = default;
    void draw_quick_action(const quick_action&);
    std::vector<quick_action> quick_actions_;

    std::unique_ptr<basic_image> quick_action_image_ = nullptr;
    std::unique_ptr<basic_image> joystick_image_ = nullptr;
};

} // namespace snail
} // namespace elona
