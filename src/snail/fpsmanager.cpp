#include "fpsmanager.hpp"
#include <numeric>
#include "detail/sdl.hpp"
#include "hsp.hpp"



namespace
{


int sum(const std::vector<int>& v)
{
    return std::accumulate(std::begin(v), std::end(v), 0);
}


} // namespace



namespace elona
{
namespace snail
{


void FPSManager::set_fps(int new_fps)
{
    _fps = new_fps;
    _history = std::vector<int>(new_fps, 1000 / _fps);
}


double FPSManager::actual_fps()
{
    return _fps * 1000.0 / sum(_history);
}



FPSManager::FPSManager(int fps)
{
    set_fps(fps);
}



void FPSManager::wait()
{
    int duration_to_wait;

    if (_frame_count == 0)
    {
        if (_previous_time == 0)
        {
            duration_to_wait = 0;
        }
        else
        {
            duration_to_wait = _t0 + 1000 - hsp::timeGetTime();
        }
    }
    else
    {
        duration_to_wait =
            _t0 + _frame_count * 1000 / fps() - hsp::timeGetTime();
    }

    if (duration_to_wait > 0)
    {
        ::SDL_Delay(duration_to_wait);
    }

    const auto now = hsp::timeGetTime();

    if (_frame_count == 0)
    {
        _t0 = now;
    }

    _history[_frame_count] = now - _previous_time;
    _previous_time = now;

    ++_frame_count;
    if (_frame_count == fps())
    {
        _frame_count = 0;
    }
}



} // namespace snail
} // namespace elona
