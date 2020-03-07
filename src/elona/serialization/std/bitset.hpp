#pragma once

#include <bitset>

#include "../concepts.hpp"



namespace elona::serialization
{

template <size_t N, typename Archive>
void serialize(std::bitset<N>& value, Archive& ar)
{
    if constexpr (concepts::is_iarchive_v<Archive>)
    {
        if constexpr (N <= 32)
        {
            uint32_t tmp;
            ar.scalar(tmp);
            value = tmp;
        }
        else if constexpr (N <= 64)
        {
            uint64_t tmp;
            ar.scalar(tmp);
            value = tmp;
        }
        else
        {
            std::string tmp;
            ar.str(tmp);
            value = std::bitset<N>(tmp);
        }
    }
    else
    {
        if constexpr (N <= 32)
        {
            uint32_t tmp = value.to_ulong();
            ar.scalar(tmp);
        }
        else if constexpr (N <= 64)
        {
            uint64_t tmp = value.to_ulong();
            ar.scalar(tmp);
        }
        else
        {
            std::string tmp = value.to_string();
            ar.str(tmp);
        }
    }
}

} // namespace elona::serialization
