#pragma once

#include <queue>



namespace lib
{

/**
 * Note: it is iterable but unordered for human! A priority queue is mostly
 * implemented by using heap structure, and the order is not straightforward.
 * Its iteration is only for searching or existence checking.
 *
 * cf. https://en.wikipedia.org/wiki/Heap_(data_structure)
 */
template <typename T, typename Container, typename Compare>
class iterable_priority_queue
    : public std::priority_queue<T, Container, Compare>
{
public:
    // It provides only `const_iterator` because a mutation can change priority.
    using const_iterator = typename Container::const_iterator;



    const_iterator begin() const
    {
        using std::begin;
        return begin(internal_container());
    }

    const_iterator end() const
    {
        using std::end;
        return end(internal_container());
    }

    const_iterator cbegin() const
    {
        using std::cbegin;
        return cbegin(internal_container());
    }

    const_iterator cend() const
    {
        using std::cend;
        return cend(internal_container());
    }



private:
    const Container& internal_container() const
    {
        // It is portable because `std::priority_queue` has `c` of `Container`
        // as protected, which is required by C++ Standard.
        return this->c;
    }
};

} // namespace lib
