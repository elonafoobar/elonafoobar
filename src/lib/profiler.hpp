#pragma once
#include <chrono>
#include <iosfwd>
#include <stack>
#include <string>
#include <boost/circular_buffer.hpp>

namespace elona
{
namespace lib
{
using namespace std::chrono;

class Profiler
{
private:
    struct Entry
    {
        Entry(std::string name, steady_clock::time_point begin)
            : name(name)
            , begin(begin)
        {
            now = begin;
        }

        steady_clock::time_point now;
        std::string name;
        steady_clock::time_point begin;
    };

    enum class RecordType
    {
        enter,
        leave,
        sample
    };

    struct Record
    {
        Record(RecordType type, std::string name, std::chrono::microseconds us)
            : type(type)
            , name(name)
            , us(us)
        {
        }

        RecordType type;
        std::string name;
        std::chrono::microseconds us;
    };

public:
    Profiler()
    {
        _last = steady_clock::now();
        _records = boost::circular_buffer<Record>(1000);
    }

    void enter(std::string name)
    {
        auto now = steady_clock::now();
        _entries.emplace(std::move(name), now);
        _records.push_back(Record{RecordType::enter, name, 0us});
        _last = now;
    }

    void sample(std::string name)
    {
        steady_clock::time_point time;
        auto now = steady_clock::now();
        if (!_entries.empty())
        {
            time = _last;
            _last = now;
        }
        else
        {
            time = _entries.top().now;
            _entries.top().now = now;
        }
        _records.push_back(Record{
            RecordType::sample, name, duration_cast<microseconds>(now - time)});
    }

    void leave()
    {
        if (_entries.empty())
        {
            return;
        }
        const auto& entry = _entries.top();
        auto now = steady_clock::now();
        _records.push_back(
            Record{RecordType::leave,
                   entry.name,
                   duration_cast<microseconds>(now - entry.begin)});
        _entries.pop();
    }

    void dump(std::ostream& stream);

private:
    steady_clock::time_point _last;
    std::stack<Entry> _entries;
    boost::circular_buffer<Record> _records;
};

extern Profiler g_profiler;

class ScopedProfiler
{
public:
    ScopedProfiler(std::string name)
    {
        g_profiler.enter(name);
    }
    ~ScopedProfiler()
    {
        g_profiler.leave();
    }
};

#define PROFILE(name) elona::lib::ScopedProfiler __profile(name)
#define PROFILE_EVENT(name) elona::lib::g_profiler.sample(name)

} // namespace lib
} // namespace elona
