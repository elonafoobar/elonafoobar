#pragma once

namespace lib
{

template <class MapType, class DataType>
class map_value_iterator
{
public:
    struct iterator
    {
    private:
        using base_iterator_type = typename MapType::const_iterator;

    public:
        using value_type = const DataType;
        using difference_type = typename base_iterator_type::difference_type;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category =
            typename base_iterator_type::iterator_category;


        iterator(const typename MapType::const_iterator& itr)
            : itr(itr)
        {
        }

        reference operator*() const
        {
            return itr->second;
        }

        pointer operator->() const
        {
            return itr.operator->();
        }

        void operator++()
        {
            ++itr;
        }

        bool operator!=(const iterator& other) const
        {
            return itr != other.itr;
        }

    private:
        typename MapType::const_iterator itr;
    };

public:
    map_value_iterator(const MapType& map_)
        : map(map_)
    {
    }

    iterator begin()
    {
        return iterator(map.begin());
    }

    iterator end()
    {
        return iterator(map.end());
    }

private:
    const MapType& map;
};

} // namespace lib
