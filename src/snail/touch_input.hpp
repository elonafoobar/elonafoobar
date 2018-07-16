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

    // If "key" is none, when the action is triggered "text" will be
    // sent to the input text buffer (as if SDL_TextInputEvent was
    // received). Otherwise, said key will be pressed/released. This
    // is because key detection for alphanumeric keys is handled
    // through SDL_TextInputEvent, but non-alphanumeric keys use
    // SDL_KeyboardEvent. This is a result of the use of HSP's
    // "mesbox" function to check if alphanumeric keys are pressed by
    // checking the string input it receives.
    optional<snail::key> key;
    std::string text;

    bool touched = false;
};

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
        if (_last_touched_quick_action_idx)
        {
            return _quick_actions.at(*_last_touched_quick_action_idx);
        }
        return none;
    }

    void set_base_quick_action_size(float size) noexcept
    {
        _base_quick_action_size = size;
    }

    void set_quick_action_transparency(float amount) noexcept
    {
        _quick_action_transparency = amount;
        _quick_action_image->set_alpha(quick_action_alpha());
    }

    void initialize(const fs::path&);
    void initialize_quick_actions();
    void draw_quick_actions();
    void on_touch_event(::SDL_TouchFingerEvent);

private:
    touch_input() = default;

    void draw_quick_action(const quick_action&);
    int quick_action_size() const noexcept;
    bool is_touched(int, int, const quick_action&);

    uint8_t quick_action_alpha() const noexcept
    {
        return static_cast<uint8_t>(_quick_action_transparency * 255);
    }

    std::vector<quick_action> _quick_actions;
    optional<size_t> _last_touched_quick_action_idx = none;
    float _base_quick_action_size = 0.5;
    float _quick_action_transparency = 0.5;

    bool _initialized = false;

    static const constexpr float _base_font_size = 0.0089f;

    std::unique_ptr<basic_image> _quick_action_image;
};

} // namespace snail
} // namespace elona
