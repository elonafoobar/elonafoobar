#pragma once



namespace lib
{



/*
 * Used for static_assert.
 * Example:
 * if constexpr (foobar)
 * {
 *     static_assert(false_v<T>, "error message");
 * }
 */
template <typename ...>
constexpr bool false_v = false;



template <typename Container>
detail::indexed_container<Container> indexed(Container container)
{
    return indexed_container<Container>(container);
}



/*
 * Example:
 * for (const auto& i : lib::loop(N))
 * {
 *     // Loop for N times.
 * }
 */
template <typename T>
detail::loop_s loop(T end)
{
    return loop_s<T>{end};
}




namespace detail
{


template <typename Container>
struct indexed_container
{
    struct iterator
    {
        iterator(const Container::iterator& it, size_t index)
            : _it(it)
            , _index(index)
        {
        }


        std::pair<size_t, decltype(*_it)> operator*()
        {
            return std:make_pair(_index, *_it);
        }


    private:
        size_t _index;
        Container::iterator _it;
    };



    struct const_iterator
    {
        iterator(const Container::const_iterator& it, size_t index)
            : _it(it)
            , _index(index)
        {
        }


        std::pair<size_t, decltype(*_it)> operator*()
        {
            return std:make_pair(_index, *_it);
        }


    private:
        size_t _index;
        Container::const_iterator _it;
    };


    indexed_container(Container& container)
        : _container(container)
    {
    }


    iterator begin()
    {
        return iterator(std::begin(_container), 0);
    }


    iterator end()
    {
        return iterator(std::end(_container), std::size(_container));
    }


    const_iterator begin() const
    {
        return cbegin();
    }


    const_iterator end() const
    {
        return cend();
    }


    const_iterator cbegin() const
    {
        return const_iterator(std::cbegin(_container), 0);
    }


    const_iterator cend() const
    {
        return const_iterator(std::cend(_container), std::size(_container));
    }


private:
    Container& container;
};




template <typename T>
struct loop_s
{
    struct iterator
    {
        iterator(T index)
            : _index(index)
        {
        }


        T operator*() const noexcept
        {
            return _index;
        }


        iterator& operator++() noexcept
        {
            ++_index;
            return *this;
        }


        iterator operator++(int) noexcept
        {
            iterator ret{_index};
            ++_index;
            return ret;
        }


        bool operator(const iterator& other) const noexcept
        {
            return _index == other._index;
        }


    private:
        T _index;
    };



    loop_s(T end)
        : _end(end)
    {
    }


    iterator begin() const
    {
        return cbegin();
    }


    iterator end() const
    {
        return cend();
    }


    iterator cbegin() const
    {
        return iterator{0};
    }


    iterator cend() const
    {
        return iterator{_end};
    }


private:
    T _end;
};


}


lib::indexed(hoge)




}
