#pragma once

#include <type_traits>



namespace elona
{
namespace putit
{
namespace detail
{

inline uint16_t byte_swap(uint16_t n)
{
    return n << 8 | n >> 8;
}



/* clang-format off */
inline uint32_t byte_swap(uint32_t n)
{
    return 0
        | (n & 0x0000'00FF) << (8 * 3)
        | (n & 0x0000'FF00) << (8 * 1)
        | (n & 0x00FF'0000) >> (8 * 1)
        | (n & 0xFF00'0000) >> (8 * 3);
}



inline uint64_t byte_swap(uint64_t n)
{
    return 0
        | (n & 0x0000'0000'0000'00FF) << (8 * 7)
        | (n & 0x0000'0000'0000'FF00) << (8 * 5)
        | (n & 0x0000'0000'00FF'0000) << (8 * 3)
        | (n & 0x0000'0000'FF00'0000) << (8 * 1)
        | (n & 0x0000'00FF'0000'0000) >> (8 * 1)
        | (n & 0x0000'FF00'0000'0000) >> (8 * 3)
        | (n & 0x00FF'0000'0000'0000) >> (8 * 5)
        | (n & 0xFF00'0000'0000'0000) >> (8 * 7);
}
/* clang-format on */



template <
    typename Integer,
    std::enable_if_t<(sizeof(Integer) > 1), std::nullptr_t> = nullptr>
Integer byte_swap_if_needed(Integer n)
{
#if defined(PUTIT_BIG_ENDIAN)
    using UInt = std::make_unsigned_t<Integer>;
    return static_cast<Integer>(byte_swap(static_cast<UInt>(n)));
#elif defined(PUTIT_LITTLE_ENDIAN)
    return n;
#else
#error "Unsupported endianness"
#endif
}



template <
    typename Integer,
    std::enable_if_t<sizeof(Integer) == 1, std::nullptr_t> = nullptr>
Integer byte_swap_if_needed(Integer n)
{
    return n;
}

} // namespace detail
} // namespace putit
} // namespace elona
