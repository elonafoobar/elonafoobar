#pragma once

#include <iostream>

#include "../concepts.hpp"
#include "detail/byte_swap.hpp"



namespace elona::serialization::binary
{

class IArchive
{
public:
    IArchive(std::istream& in)
        : _in(in)
    {
    }


    template <typename T>
    void operator()(T& value)
    {
        using ::elona::serialization::serialize;
        serialize(value, *this);
    }



#define ELONA_SERIALIZATION_DEFINE_SCALAR(type) \
    void scalar(type& value) \
    { \
        _in.read(reinterpret_cast<char*>(&value), sizeof(type)); \
        value = detail::byte_swap(value); \
    }


    ELONA_SERIALIZATION_DEFINE_SCALAR(bool)

    ELONA_SERIALIZATION_DEFINE_SCALAR(int8_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(int16_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(int32_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(int64_t)

    ELONA_SERIALIZATION_DEFINE_SCALAR(uint8_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(uint16_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(uint32_t)
    ELONA_SERIALIZATION_DEFINE_SCALAR(uint64_t)

    ELONA_SERIALIZATION_DEFINE_SCALAR(float)
    ELONA_SERIALIZATION_DEFINE_SCALAR(double)
    ELONA_SERIALIZATION_DEFINE_SCALAR(long double)

    ELONA_SERIALIZATION_DEFINE_SCALAR(char)

#undef ELONA_SERIALIZATION_DEFINE_SCALAR



    void str(std::string& value)
    {
        uint64_t len = 0;
        scalar(len);
        value.resize(len, '\0');
        for (auto&& c : value)
        {
            scalar(c);
        }
    }



    IArchive& seq_begin(uint64_t& length)
    {
        scalar(length);
        return *this;
    }


    template <typename T>
    void seq_element([[maybe_unused]] uint64_t nth, T& element)
    {
        (*this)(element);
    }


    void seq_end()
    {
    }



    IArchive& map_begin(uint64_t& length)
    {
        scalar(length);
        return *this;
    }


    template <typename K, typename V>
    void map_element([[maybe_unused]] uint64_t nth, K& key, V& value)
    {
        (*this)(key);
        (*this)(value);
    }


    void map_end()
    {
    }



    IArchive& struct_begin([[maybe_unused]] const char* struct_name)
    {
        return *this;
    }


    template <typename T>
    void struct_field([[maybe_unused]] const char* field_name, T& value)
    {
        (*this)(value);
    }


    void struct_end()
    {
    }



    template <size_t Length>
    IArchive& tuple_begin()
    {
        return *this;
    }


    template <size_t Nth, typename T>
    void tuple_item(T& value)
    {
        (*this)(value);
    }


    void tuple_end()
    {
    }



private:
    std::istream& _in;
};

} // namespace elona::serialization::binary



ELONA_SERIALIZATION_CONCEPTS_IMPL_IS_IARCHIVE(
    ::elona::serialization::binary::IArchive);
