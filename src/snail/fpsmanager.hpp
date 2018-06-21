#pragma once

#include <vector>
#include "../lib/noncopyable.hpp"
#include "detail/sdl.hpp"
#include "hsp.hpp"


namespace elona
{
namespace snail
{


class fps_manager final : private lib::noncopyable
{
public:
    int fps() const noexcept
    {
        return _fps;
    }

    void set_fps(int new_fps);

    double actual_fps();


    explicit fps_manager(int fps = 60);
    virtual ~fps_manager() override = default;


    void wait();


private:
    using time = decltype(snail::hsp::timeGetTime());

    int _fps;
    int _frame_count = 0; // [0, fps)
    time _t0 = time{0}; // The time when `_frame_count` was zero most recently.
    time _previous_time = time{0};
    std::vector<int> _history;
};


} // namespace snail
} // namespace elona
