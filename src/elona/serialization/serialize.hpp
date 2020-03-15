#pragma once

#include <cstdint>

#include "concepts.hpp"



namespace elona::serialization
{

template <
    typename T,
    typename Archive,
    ELONA_SERIALIZATION_CONCEPTS_HAS_SERIALIZE_METHOD(T, Archive)>
void serialize(T& value, Archive& ar)
{
    value.serialize(ar);
}



template <typename Archive>
void serialize(bool& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(int8_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(int16_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(int32_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(int64_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(uint8_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(uint16_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(uint32_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(uint64_t& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(float& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(double& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(long double& value, Archive& ar)
{
    ar.scalar(value);
}



template <typename Archive>
void serialize(char& value, Archive& ar)
{
    ar.scalar(value);
}



template <
    typename T,
    typename Archive,
    ELONA_SERIALIZATION_ENABLE_IF(std::is_enum_v<T>)>
void serialize(T& value, Archive& ar)
{
    if constexpr (concepts::is_iarchive_v<Archive>)
    {
        std::underlying_type_t<T> tmp;
        ar.scalar(tmp);
        value = static_cast<T>(tmp);
    }
    else
    {
        auto tmp = static_cast<std::underlying_type_t<T>>(value);
        ar.scalar(tmp);
    }
}

} // namespace elona::serialization
