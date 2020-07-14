#pragma once

#include <boost/uuid/uuid.hpp>



namespace elona::serialization
{

template <typename Archive>
void serialize(boost::uuids::uuid& value, Archive& ar)
{
    for (auto&& byte : value)
    {
        ar(byte);
    }
}

} // namespace elona::serialization
