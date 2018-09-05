#pragma once

#include <vector>
#include "../lib/noncopyable.hpp"
#include "detail/sdl.hpp"
#include "hsp.hpp"


namespace elona
{
namespace snail
{


class FPSManager final : private lib::noncopyable
{
public:
    int fps() const noexcept
    {
        return _fps;
    }

    void set_fps(int new_fps);

    double actual_fps();


    explicit FPSManager(int fps = 60);
    virtual ~FPSManager() override = default;


    void wait();


private:
    using Time = decltype(snail::hsp::timeGetTime());

    int _fps;
    int _frame_count = 0; // [0, fps)
    Time _t0 = Time{0}; // The time when `_frame_count` was zero most recently.
    Time _previous_time = Time{0};
    std::vector<int> _history;
};


} // namespace snail
} // namespace elona
