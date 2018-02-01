#pragma once

#include <memory>
#include <optional>



namespace elona
{



template <typename T>
struct optional_ref
{
    optional_ref()
    {
    }


    optional_ref(std::nullopt_t)
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
        return data;
    }


private:
    const T* data = nullptr;
};



} // namespace elona
