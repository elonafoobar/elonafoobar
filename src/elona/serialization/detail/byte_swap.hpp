#pragma once

#include <cstdint>

#include <utility>

#include "../../defines.hpp"



namespace elona::serialization::detail
{

template <typename T>
T byte_swap(T value)
{
#if defined(ELONA_BIG_ENDIAN)
    union
    {
        uint8_t bytes[sizeof(T)];
        T value;
    } as;
    as.value = value;
    for (size_t i = 0; i < sizeof(T) / 2; ++i)
    {
        std::swap(as.bytes[i], as.bytes[sizeof(T) - i - 1]);
    }
    return as.value;
#elif defined(ELONA_LITTLE_ENDIAN)
    return value;
#else
#error "Unsupported endianness"
#endif
}

} // namespace elona::serialization::detail
