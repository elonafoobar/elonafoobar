#pragma once

#include <string>



namespace elona::serialization
{

template <typename Archive>
void serialize(std::string& value, Archive& ar)
{
    ar.str(value);
}

} // namespace elona::serialization
