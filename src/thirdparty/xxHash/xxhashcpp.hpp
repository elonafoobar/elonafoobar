/*
 * Wrapper interface of xxHash in C++.
 *
 * The license is the same as the core of xxHash, BSD 2-Clause.
 * Copyright (c) 2019 KI
 */
#pragma once

#include <string>

#define XXH_INLINE_ALL
#include "xxhash.h"



namespace xxhash
{

// Define wrapper interface of N-bit version xxHash.
#define XXHCPP_DEFINE_WRAPPER(N, DEFAULT_SEED) \
    using hash##N##_t = ::XXH##N##_hash_t; \
    using seed##N##_t = uint##N##_t; \
\
    constexpr seed##N##_t default_seed##N = DEFAULT_SEED; \
\
    inline hash##N##_t xxhash##N( \
        const void* input, size_t length, seed##N##_t seed = default_seed##N) \
    { \
        return XXH##N(input, length, seed); \
    } \
\
    inline hash##N##_t xxhash##N( \
        const char* zero_terminated_string, \
        seed##N##_t seed = default_seed##N) \
    { \
        return XXH##N( \
            zero_terminated_string, strlen(zero_terminated_string), seed); \
    } \
\
    template < \
        class charT, \
        class traits = std::char_traits<charT>, \
        class Allocator = std::allocator<charT>> \
    hash##N##_t xxhash##N( \
        const std::basic_string<charT, traits, Allocator>& str, \
        seed##N##_t seed = default_seed##N) \
    { \
        return XXH##N(str.c_str(), str.size(), seed); \
    } \
\
    struct state##N##_t \
    { \
    public: \
        state##N##_t() \
            : _state(XXH##N##_createState()) \
        { \
        } \
\
        state##N##_t(const state##N##_t& other) \
        { \
            XXH##N##_copyState(_state, other._state); \
        } \
\
        state##N##_t(state##N##_t&& other) \
        { \
            XXH##N##_copyState(_state, other._state); \
        } \
\
        ~state##N##_t() \
        { \
            XXH##N##_freeState(_state); \
        } \
\
        void reset(seed##N##_t seed = default_seed##N) \
        { \
            XXH##N##_reset(_state, seed); \
        } \
\
        void update(const void* input, size_t length) \
        { \
            assert(input); \
            XXH##N##_update(_state, input, length); \
        } \
\
        hash##N##_t operator()() const \
        { \
            return XXH##N##_digest(_state); \
        } \
\
    private: \
        XXH##N##_state_t* _state; \
    }; \
\
    using hash##N##_canonical_t = ::XXH##N##_canonical_t; \
\
    hash##N##_canonical_t hash2canonical(hash##N##_t hash) \
    { \
        hash##N##_canonical_t ret; \
        XXH##N##_canonicalFromHash(&ret, hash); \
        return ret; \
    } \
\
    hash##N##_t canonical2hash(const hash##N##_canonical_t& hash_canonical) \
    { \
        return XXH##N##_hashFromCanonical(&hash_canonical); \
    }



// This default seed is the result of xxhash32("Eternal League of Nefia", 0).
XXHCPP_DEFINE_WRAPPER(32, 363048679)

// This default seed is the result of xxhash64("Eternal League of Nefia", 0).
XXHCPP_DEFINE_WRAPPER(64, 7319253023958396250)


#undef XXHCPP_DEFINE_WRAPPER

} // namespace xxhash
