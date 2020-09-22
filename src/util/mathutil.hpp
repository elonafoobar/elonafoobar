#pragma once

#include <limits>



namespace mathutil
{

template <typename T>
constexpr T& saturating_inc(T& x, T max = std::numeric_limits<T>::max())
{
    if (x < max)
        return ++x;
    else
        return x;
}



template <typename T>
constexpr T& saturating_dec(T& x, T min = std::numeric_limits<T>::min())
{
    if (min < x)
        return --x;
    else
        return x;
}

} // namespace mathutil
