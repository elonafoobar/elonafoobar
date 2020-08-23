#pragma once

#include <vector>

#include "../concepts.hpp"



namespace elona::serialization
{

template <typename T, typename Archive>
void serialize(std::vector<T>& value, Archive& ar)
{
    if constexpr (concepts::is_iarchive_v<Archive>)
    {
        uint64_t len = 0;
        ar(len);
        value.resize(len);
        for (auto&& element : value)
        {
            ar(element);
        }
    }
    else
    {
        uint64_t len = value.size();
        ar(len);
        for (auto&& element : value)
        {
            ar(element);
        }
    }
}

} // namespace elona::serialization
