#pragma once

#include <memory>
#include <boost/optional.hpp>



namespace elona
{


template <typename T>
using optional = boost::optional<T>;

using none_t = boost::none_t;
const none_t none = boost::none;



template <typename T>
struct optional_ref
{
    optional_ref()
    {
    }


    optional_ref(none_t)
    {
    }


    optional_ref(std::nullptr_t)
    {
    }


    optional_ref(const T& value)
        : data(std::addressof(value))
    {
    }


    explicit operator bool() const noexcept
    {
        return data;
    }


    const T* operator->() const noexcept
    {
        assert(data);
        return data;
    }

    const T* operator*() const noexcept
    {
        assert(data);
        return data;
    }


private:
    const T* data = nullptr;
};


} // namespace elona
