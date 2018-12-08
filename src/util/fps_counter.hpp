#pragma once
#include <chrono>

namespace lib
{
using namespace std::chrono;

class FpsCounter
{
public:
    double ms() const
    {
        return _current_avg_ms;
    }

    double fps() const
    {
        return 1000.0 / _current_avg_ms;
    }

    bool want_report() const
    {
        return _report;
    }

    void set_report()
    {
        _report = true;
    }


    void clear()
    {
        _frames = 1;
        _current_avg_ms = 0.0;
        _total = 0us;
        _now = steady_clock::now();
        _prev = _now;
        _last_report = _now;
        _report = false;
    }

    void count()
    {
        _prev = _now;
        _now = steady_clock::now();
        if (duration_cast<milliseconds>(_now - _last_report).count() > 500)
        {
            _update_average();
            _frames = 0;
            _report = true;
        }
        else
        {
            _report = false;
        }
        _total += duration_cast<microseconds>(_now - _prev);
        _frames++;
    }

private:
    void _update_average()
    {
        _last_report = _now;
        _current_avg_ms = (_total.count() / 1000.0) / _frames;
        _total = 0us;
    }

    bool _report = false;
    int _frames = 1;
    microseconds _total;
    double _current_avg_ms;
    steady_clock::time_point _now;
    steady_clock::time_point _prev;
    steady_clock::time_point _last_report;
};

extern FpsCounter g_fps_counter;

} // namespace lib
