#pragma once

#include <string>
#include <vector>

#include "time.hpp"



namespace elona
{

/// Artifact generation log which records what artifact was generated when
/// and where.
struct ArtifactLog
{
    /// Time when the artifact is generated.
    time::Instant timestamp;

    /// Log content
    std::string content;
};



/// List of @ref ArtifactLog
struct ArtifactLogList
{
    using storage_type = std::vector<ArtifactLog>;
    using iterator = storage_type::iterator;
    using const_iterator = storage_type::const_iterator;



    bool empty() const noexcept
    {
        return _logs.empty();
    }


    void clear()
    {
        return _logs.clear();
    }


    void append(const ArtifactLog& new_log_entry)
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



private:
    std::vector<ArtifactLog> _logs;
};

} // namespace elona
