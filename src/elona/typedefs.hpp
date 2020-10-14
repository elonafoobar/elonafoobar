#pragma once

#include <cstdint>

#include <type_traits>

#include "../thirdparty/sol2/sol.hpp"
#include "optional.hpp"



namespace elona
{

using lua_int = int64_t;
using lua_float = double;

using lua_table = sol::table;



/**
 * Numeric type for bridging between 0-based index in C++ and 1-based one in
 * Lua. It can be 0, which means pointing to nothing.
 */
struct lua_index
{
    /// Default constructor. It points to nothing.
    constexpr lua_index() noexcept = default;


    /// Returns nil index.
    constexpr static lua_index nil() noexcept
    {
        return lua_index{};
    }


    /// Make Lua index from C index (0-based).
    template <typename Int>
    constexpr static lua_index from_0_based(Int c_idx) noexcept
    {
        if constexpr (std::is_signed_v<Int>)
        {
            return lua_index{static_cast<lua_int>(c_idx < 0 ? 0 : c_idx + 1)};
        }
        else
        {
            return lua_index{static_cast<lua_int>(c_idx + 1)};
        }
    }


    /// Make Lua index from Lua index (1-based).
    constexpr static lua_index from_1_based(lua_int lua_idx) noexcept
    {
        return lua_index{lua_idx < 0 ? 0 : lua_idx};
    }


    constexpr bool is_nil() const noexcept
    {
        return _inner == 0;
    }


    /// Converts it to C index (0-based).
    constexpr optional<size_t> to_0_based() const noexcept
    {
        if (is_nil())
            return none;
        else
            return static_cast<size_t>(_inner) - 1;
    }


    /// Converts it to Lua index (1-based).
    constexpr lua_int to_1_based() const noexcept
    {
        return _inner;
    }


    /* clang-format off */
    constexpr bool operator==(lua_index other) const noexcept { return _inner == other._inner; }
    constexpr bool operator!=(lua_index other) const noexcept { return _inner != other._inner; }
    constexpr bool operator<(lua_index other)  const noexcept { return _inner <  other._inner; }
    constexpr bool operator<=(lua_index other) const noexcept { return _inner <= other._inner; }
    constexpr bool operator>(lua_index other)  const noexcept { return _inner >  other._inner; }
    constexpr bool operator>=(lua_index other) const noexcept { return _inner >= other._inner; }
    /* clang-format on */



private:
    lua_int _inner{}; // 1-based



    constexpr explicit lua_index(lua_int inner) noexcept
        : _inner(inner)
    {
    }
};

} // namespace elona
