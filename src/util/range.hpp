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



template <typename BeginIterator, typename EndIterator = BeginIterator>
struct iterator_pair_t
{
    using begin_iterator_type = BeginIterator;
    using end_iterator_type = EndIterator;



    iterator_pair_t(begin_iterator_type begin_itr, end_iterator_type end_itr)
        : _begin_itr(begin_itr)
        , _end_itr(end_itr)
    {
    }


    begin_iterator_type begin() const
    {
        return _begin_itr;
    }


    end_iterator_type end() const
    {
        return _end_itr;
    }


private:
    begin_iterator_type _begin_itr;
    end_iterator_type _end_itr;
};



template <typename BeginIterator, typename EndIterator = BeginIterator>
auto iterator_pair(BeginIterator begin_itr, EndIterator end_itr)
{
    return iterator_pair_t<BeginIterator, EndIterator>(begin_itr, end_itr);
}

} // namespace range
