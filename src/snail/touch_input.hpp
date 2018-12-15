#pragma once
#include <string>
#include <vector>
#include "../elona/optional.hpp"
#include "../util/noncopyable.hpp"
#include "application.hpp"
#include "detail/sdl.hpp"
#include "filesystem.hpp"
#include "image.hpp"
#include "input.hpp"

namespace elona
{
namespace snail
{

struct QuickAction
{
    QuickAction(std::string text, snail::Key key, int center_x, int center_y)
        : center_x(center_x)
        , center_y(center_y)
        , key(key)
        , text(text)
    {
    }

    int center_x;
    int center_y;

    snail::Key key;
    std::string text;

    bool touched = false;
};

class TouchInput : public lib::noncopyable
{
    enum class EventType
    {
        motion = SDL_FINGERMOTION,
        down = SDL_FINGERDOWN,
        up = SDL_FINGERUP,
    };

public:
    virtual ~TouchInput() override = default;
    static TouchInput& instance();

    optional<QuickAction> last_touched_quick_action() const
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
        if (_quick_action_image)
        {
            _quick_action_image->set_alpha(quick_action_alpha());
        }
    }

    void initialize(const fs::path&);
    void initialize_quick_actions();
    void draw_quick_actions();
    void on_touch_event(::SDL_TouchFingerEvent);

private:
    TouchInput() = default;

    void draw_quick_action(const QuickAction&);
    int quick_action_size() const noexcept;
    bool is_touched(int, int, const QuickAction&);

    uint8_t quick_action_alpha() const noexcept
    {
        return static_cast<uint8_t>(_quick_action_transparency * 255);
    }

    std::vector<QuickAction> _quick_actions;
    optional<size_t> _last_touched_quick_action_idx = none;
    float _base_quick_action_size = 0.5;
    float _quick_action_transparency = 0.5;

    bool _initialized = false;

    static const constexpr float _base_font_size = 0.0089f;

    std::unique_ptr<BasicImage> _quick_action_image;
};

} // namespace snail
} // namespace elona
