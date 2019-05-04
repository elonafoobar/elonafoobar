#pragma once

#include <type_traits>



// This library does not use template and SFINAE to reduce compile time.


#define ENUMUTIL_INTERNAL_DEFINE_BINARY_OPERATOR(Enum, op) \
    inline constexpr Enum operator op(Enum lhs, Enum rhs) \
    { \
        using T = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(static_cast<T>(lhs) op static_cast<T>(rhs)); \
    } \
    inline Enum& operator op##=(Enum& lhs, Enum rhs) \
    { \
        return lhs = (lhs op rhs); \
    }


#define ENUMUTIL_INTERNAL_DEFINE_UNARY_OPERATOR(Enum, op) \
    inline constexpr Enum operator op(Enum operand) \
    { \
        using T = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(op static_cast<T>(operand)); \
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



#define ENUMUTIL_INTERNAL_DEFINE_COMPARISON_OPERATOR(Enum, op) \
    inline constexpr bool operator op(Enum lhs, Enum rhs) \
    { \
        using T = std::underlying_type_t<Enum>; \
        return static_cast<T>(lhs) op static_cast<T>(rhs); \
    }


/// Define 4 comparison operators.
#define ENUMUTIL_DEFINE_COMPARISON_OPERATORS(Enum) \
    ENUMUTIL_INTERNAL_DEFINE_COMPARISON_OPERATOR(Enum, <) \
    ENUMUTIL_INTERNAL_DEFINE_COMPARISON_OPERATOR(Enum, <=) \
    ENUMUTIL_INTERNAL_DEFINE_COMPARISON_OPERATOR(Enum, >) \
    ENUMUTIL_INTERNAL_DEFINE_COMPARISON_OPERATOR(Enum, >=)



/// Define get_next_enum() and get_prev_enum() functions.
/// Note that they do not check the boundaries.
#define ENUMUTIL_DEFINE_NEXT_PREV_FUNCTIONS(Enum) \
    inline constexpr Enum get_next_enum(Enum x) \
    { \
        using T = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(static_cast<T>(x) + 1); \
    } \
    inline constexpr Enum get_prev_enum(Enum x) \
    { \
        using T = std::underlying_type_t<Enum>; \
        return static_cast<Enum>(static_cast<T>(x) - 1); \
    }



/// Define get_next_enum() and get_prev_enum() functions (looped version).
/// The macro parameter max is inclusive: [min, max]
#define ENUMUTIL_DEFINE_NEXT_PREV_FUNCTIONS_LOOPED_INCLUSIVE_RANGE( \
    Enum, min, max) \
    inline constexpr Enum get_next_enum(Enum x) \
    { \
        /* return x==max ? min : x+1 */ \
        using T = std::underlying_type_t<Enum>; \
        if (static_cast<T>(x) == static_cast<T>(Enum::max)) \
        { \
            return Enum::min; \
        } \
        else \
        { \
            return static_cast<Enum>(static_cast<T>(x) + 1); \
        } \
    } \
    inline constexpr Enum get_prev_enum(Enum x) \
    { \
        /* return x==min ? max : x-1 */ \
        using T = std::underlying_type_t<Enum>; \
        if (static_cast<T>(x) == static_cast<T>(Enum::min)) \
        { \
            return Enum::max; \
        } \
        else \
        { \
            return static_cast<Enum>(static_cast<T>(x) - 1); \
        } \
    }



/// Define get_next_enum() and get_prev_enum() functions (looped version).
/// The macro parameter max is exclusive: [min, max)
#define ENUMUTIL_DEFINE_NEXT_PREV_FUNCTIONS_LOOPED_EXCLUSIVE_RANGE( \
    Enum, min, max) \
    inline constexpr Enum get_next_enum(Enum x) \
    { \
        /* return x==max-1 ? min : x+1 */ \
        using T = std::underlying_type_t<Enum>; \
        if (static_cast<T>(x) == static_cast<T>(Enum::max) - 1) \
        { \
            return Enum::min; \
        } \
        else \
        { \
            return static_cast<Enum>(static_cast<T>(x) + 1); \
        } \
    } \
    inline constexpr Enum get_prev_enum(Enum x) \
    { \
        /* return x==min ? max-1 : x-1 */ \
        using T = std::underlying_type_t<Enum>; \
        if (static_cast<T>(x) == static_cast<T>(Enum::min)) \
        { \
            return static_cast<Enum>(static_cast<T>(Enum::max) - 1); \
        } \
        else \
        { \
            return static_cast<Enum>(static_cast<T>(x) - 1); \
        } \
    }
