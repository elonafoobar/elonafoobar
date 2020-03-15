#pragma once

#include <deque>

#include "../concepts.hpp"



namespace elona::serialization
{

template <typename T, typename Archive>
void serialize(std::deque<T>& value, Archive& ar)
{
    if constexpr (concepts::is_iarchive_v<Archive>)
    {
        uint64_t len = 0;
        auto&& ar_seq = ar.seq_begin(len);
        value.resize(len);
        uint64_t i = 0;
        for (auto&& element : value)
        {
            ar_seq.seq_element(i, element);
            ++i;
        }
        ar_seq.seq_end();
    }
    else
    {
        uint64_t len = value.size();
        auto&& ar_seq = ar.seq_begin(len);
        uint64_t i = 0;
        for (auto&& element : value)
        {
            ar_seq.seq_element(i, element);
            ++i;
        }
        ar_seq.seq_end();
    }
}

} // namespace elona::serialization
