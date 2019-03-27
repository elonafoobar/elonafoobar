#pragma once
#include <memory>

template <typename T>
class TempIndexSetter
{
public:
    TempIndexSetter(T& value, T new_value)
        : location(std::addressof(value))
    {
        backup = *location;
        *location = new_value;
    }

    ~TempIndexSetter()
    {
        *location = backup;
    }

private:
    T backup;
    T* location;
};
