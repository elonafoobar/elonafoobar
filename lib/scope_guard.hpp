#pragma once

#include <functional>


namespace lib
{


struct scope_guard
{
    scope_guard(std::function<void()> finalizer)
        : finalizer(finalizer)
    {
    }


    scope_guard(const scope_guard&) = delete;

    scope_guard(scope_guard&& other)
        : finalizer(other.finalizer)
    {
        other.finalizer = nullptr;
    }


    ~scope_guard()
    {
        if (finalizer)
        {
            finalizer();
        }
    }

private:
    std::function<void()> finalizer;
};



}
