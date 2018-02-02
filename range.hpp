#pragma once
#include <algorithm>
#include <iterator>


namespace elona::range
{


namespace detail
{


template <typename R>
struct iterator_type
{
    using type = typename R::iterator;
};


template <typename R>
struct iterator_type<R*>
{
    using type = R*;
};


template <typename R>
using iterator_type_t = typename iterator_type<R>::type;


} // namespace detail



template <typename R, typename P>
typename std::iterator_traits<detail::iterator_type_t<R>>::difference_type
count_if(const R& range, P predicate)
{
    using std::begin, std::end;
    return std::count_if(begin(range), end(range), predicate);
}


template <typename R, typename F>
bool all_of(const R& range, F predicate)
{
    using std::begin, std::end;
    return std::all_of(begin(range), end(range), predicate);
}


} // namespace elona::range
