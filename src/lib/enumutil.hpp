#pragma once

#include <type_traits>


// This library does not use template and SFINAE to reduce compile time.


#define ENUMUTIL_INTERNAL_DEFINE_BINARY_OPERATOR(Enum, op) \
    inline constexpr Enum operator op(Enum lhs, Enum rhs) \
    { \
        using underlying_type = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(static_cast<underlying_type>(lhs) \
                                     op static_cast<underlying_type>(rhs)); \
    } \
    inline Enum& operator op##=(Enum& lhs, Enum rhs) \
    { \
        return lhs = (lhs op rhs); \
    }


#define ENUMUTIL_INTERNAL_DEFINE_UNARY_OPERATOR(Enum, op) \
    inline constexpr Enum operator op(Enum operand) \
    { \
        using underlying_type = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(op static_cast<underlying_type>(operand)); \
    }


/// Define operator& and operator&= between two Enums.
#define ENUMUTIL_DEFINE_BITWISE_AND_OPERATOR(Enum) \
    ENUMUTIL_INTERNAL_DEFINE_BINARY_OPERATOR(Enum, &)

/// Define operator| and operator|= between two Enums.
#define ENUMUTIL_DEFINE_BITWISE_OR_OPERATOR(Enum) \
    ENUMUTIL_INTERNAL_DEFINE_BINARY_OPERATOR(Enum, |)

/// Define operator^ and operator^= between two Enums.
#define ENUMUTIL_DEFINE_BITWISE_XOR_OPERATOR(Enum) \
    ENUMUTIL_INTERNAL_DEFINE_BINARY_OPERATOR(Enum, ^)

/// Define operator~ against a Enum.
#define ENUMUTIL_DEFINE_BITWISE_NOT_OPERATOR(Enum) \
    ENUMUTIL_INTERNAL_DEFINE_UNARY_OPERATOR(Enum, ~)

/// Define all bitwise operators mentioned above.
#define ENUMUTIL_DEFINE_BITWISE_OPERATORS(Enum) \
    ENUMUTIL_DEFINE_BITWISE_AND_OPERATOR(Enum) \
    ENUMUTIL_DEFINE_BITWISE_OR_OPERATOR(Enum) \
    ENUMUTIL_DEFINE_BITWISE_XOR_OPERATOR(Enum) \
    ENUMUTIL_DEFINE_BITWISE_NOT_OPERATOR(Enum)

