#pragma once
#include <chrono>

namespace lib
{

namespace chrono = std::chrono;

class Stopwatch
{
    using TimePoint = chrono::time_point<chrono::high_resolution_clock>;
    using Duration = long;

public:
    Stopwatch()
    {
        last = chrono::high_resolution_clock::now();
    }

    Duration measure()
    {
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = now - last;
        last = now;

        return chrono::duration_cast<chrono::milliseconds>(elapsed).count();
    }

private:
    TimePoint last;
};

} // namespace lib
