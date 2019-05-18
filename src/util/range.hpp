#pragma once

#include <algorithm>
#include <iterator>



namespace range
{

template <typename Range, typename Predicate>
auto count_if(Range&& range, Predicate&& predicate)
{
    using std::begin;
    using std::end;
    return std::count_if(
        begin(range), end(range), std::forward<Predicate>(predicate));
}



template <typename Range>
auto distance(Range&& range)
{
    using std::begin;
    using std::end;
    return std::distance(begin(range), end(range));
}



template <typename Range, typename Predicate>
bool all_of(Range&& range, Predicate&& predicate)
{
    using std::begin;
    using std::end;
    return std::all_of(
        begin(range), end(range), std::forward<Predicate>(predicate));
}



template <typename Range, typename Predicate>
bool any_of(Range&& range, Predicate&& predicate)
{
    using std::begin;
    using std::end;
    return std::any_of(
        begin(range), end(range), std::forward<Predicate>(predicate));
}



template <typename Range, typename OutputIterator, typename UnaryFunc>
auto transform(Range&& src, OutputIterator dst, UnaryFunc func)
{
    using std::begin;
    using std::end;
    return std::transform(begin(src), end(src), dst, func);
}



template <typename Range, typename OutputIterator>
auto copy(Range&& src, OutputIterator dst)
{
    using std::begin;
    using std::end;
    return std::copy(begin(src), end(src), dst);
}



template <typename Range, typename UnaryFunc>
auto for_each(Range&& range, UnaryFunc func)
{
    using std::begin;
    using std::end;
    return std::for_each(begin(range), end(range), func);
}



template <typename Range, typename T>
auto find(Range&& range, const T& value)
{
    using std::begin;
    using std::end;
    return std::find(begin(range), end(range), value);
}



template <typename Range, typename Predicate>
auto find_if(Range&& range, Predicate&& predicate)
{
    using std::begin;
    using std::end;
    return std::find_if(
        begin(range), end(range), std::forward<Predicate>(predicate));
}



template <typename Range, typename T>
auto fill(Range&& range, const T& value)
{
    using std::begin;
    using std::end;
    return std::fill(begin(range), end(range), value);
}



template <typename Range1, typename Range2>
bool equal(Range1&& range1, Range2&& range2)
{
    using std::begin;
    using std::end;
    return std::equal(begin(range1), end(range1), begin(range2));
}



template <typename Range>
void sort(Range&& range)
{
    using std::begin;
    using std::end;
    std::sort(begin(range), end(range));
}



template <typename Range, typename Comparator>
void sort(Range&& range, Comparator less)
{
    using std::begin;
    using std::end;
    std::sort(begin(range), end(range), less);
}



// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Erase-Remove
template <typename Range, typename T>
void remove_erase(Range& range, const T& element)
{
    using std::begin;
    using std::end;
    range.erase(std::remove(begin(range), end(range), element), end(range));
}



// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Erase-Remove
template <typename Range, typename Predicate>
void remove_erase_if(Range& range, Predicate&& predicate)
{
    using std::begin;
    using std::end;
    range.erase(
        std::remove_if(
            begin(range), end(range), std::forward<Predicate>(predicate)),
        end(range));
}



template <typename T>
struct iota
{
    iota(T first, T last)
        : first(first)
        , last(last)
    {
    }


    iota(T last)
        : iota(0, last)
    {
    }


    struct iterator
    {
        using value_type = const T;
        using difference_type = size_t;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;


        iterator(T n)
            : n(n)
        {
        }


        void operator++()
        {
            ++n;
        }


        reference operator*() const
        {
            return n;
        }


        bool operator!=(const iterator& other) const
        {
            return n != other.n;
        }


    private:
        T n;
    };


    iterator begin() const
    {
        return {first};
    }


    iterator end() const
    {
        return {last};
    }


private:
    const T first;
    const T last;
};

} // namespace range
