#pragma once
#include <algorithm>
#include <iterator>


namespace elona::range
{


template <typename R, typename P>
auto count_if(const R& range, P predicate)
{
    using std::begin, std::end;
    return std::count_if(begin(range), end(range), predicate);
}



template <typename R>
auto distance(const R& range)
{
    using std::begin, std::end;
    return std::distance(begin(range), end(range));
}



template <typename R, typename F>
bool all_of(const R& range, F predicate)
{
    using std::begin, std::end;
    return std::all_of(begin(range), end(range), predicate);
}



template <typename R, typename F>
bool any_of(const R& range, F predicate)
{
    using std::begin, std::end;
    return std::any_of(begin(range), end(range), predicate);
}



} // namespace elona::range
