#pragma once

#include <string>
#include <vector>

#include "time.hpp"



namespace elona
{

struct AdventurerLog
{
    /// Time when the log is recorded.
    time::Instant timestamp;

    /// News headline
    std::string headline;

    /// News content
    std::string content;
};



/// List of @ref AdventurerLog
struct AdventurerLogList
{
    using storage_type = std::vector<AdventurerLog>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;



    bool empty() const noexcept
    {
        return _logs.empty();
    }


    size_t size() const noexcept
    {
        return _logs.size();
    }


    void append(const AdventurerLog& new_log_entry)
    {
        _logs.push_back(new_log_entry);
    }


    iterator begin()
    {
        return _logs.begin();
    }

    iterator end()
    {
        return _logs.end();
    }

    const_iterator begin() const
    {
        return _logs.begin();
    }

    const_iterator end() const
    {
        return _logs.end();
    }

    const_iterator cbegin() const
    {
        return _logs.cbegin();
    }

    const_iterator cend() const
    {
        return _logs.cend();
    }


    void shrink(size_t new_size)
    {
        if (size() <= new_size)
            return;

        // Remove first (size - new_size) entries.
        _logs.erase(begin(), begin() + (size() - new_size));
    }



private:
    std::vector<AdventurerLog> _logs;
};

} // namespace elona
