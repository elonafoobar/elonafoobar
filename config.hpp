#pragma once

#include "lib/noncopyable.hpp"



namespace elona
{


class config : public lib::noncopyable
{
public:
    static config& instance();

private:
    config() = default;
};


} // namespace elona
