#include "profiler.hpp"
#include <iostream>

namespace elona
{
namespace lib
{

Profiler g_profiler;

void Profiler::dump(std::ostream& out)
{
    int level = 0;
    for (const auto& record : _records)
    {
        switch (record.type)
        {
        case RecordType::enter:
            out << std::string(level, ' ') << "\\ " << record.name << std::endl;
            level++;
            break;
        case RecordType::leave:
            level--;
            level = level < 0 ? 0 : level;
            out << std::string(level + 1, ' ') << "= [[" << record.name << "]] "
                << record.us.count() << "us total" << std::endl;
            out << std::string(level, ' ') << "/" << std::endl;
            break;
        case RecordType::sample:
            out << std::string(level, ' ') << "| [" << record.name << "] "
                << record.us.count() << "us" << std::endl;
            break;
        }

        level = level < 0 ? 0 : level;
    }

    _records.clear();
    while (!_entries.empty())
    {
        _entries.pop();
    }
}

} // namespace lib
} // namespace elona
