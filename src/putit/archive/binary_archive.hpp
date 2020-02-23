#pragma once

#include <cstdint>

#include <deque>
#include <iostream>
#include <memory>
#include <vector>

#include "../../util/filepathutil.hpp"
#include "archive_base.hpp"
#include "detail/byte_swap.hpp"



namespace elona
{
namespace putit
{

#define PUTIT_EMPTY_TOKEN

#define PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(type) \
    void operator()(type& data, const char* field_name = nullptr) \
    { \
        (void)field_name; \
        _primitive(data); \
    }

#define PUTIT_DEFINE_PRIMITIVE_TYPES_BASE(const_or_empty) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty bool) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty char) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty int8_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty uint8_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty int16_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty uint16_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty int32_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty uint32_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty int64_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty uint64_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty float) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty double) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(const_or_empty long double)

#define PUTIT_DEFINE_PRIMITIVE_TYPES \
    PUTIT_DEFINE_PRIMITIVE_TYPES_BASE(PUTIT_EMPTY_TOKEN)
#define PUTIT_DEFINE_PRIMITIVE_TYPES_CONST \
    PUTIT_DEFINE_PRIMITIVE_TYPES_BASE(const)



class BinaryIArchive : public IArchiveBase
{
public:
    BinaryIArchive(std::istream& in)
        : in(in)
    {
    }


    template <typename T>
    static void load(std::istream& in, T& data)
    {
        BinaryIArchive ar{in};
        ar(data);
    }


    template <typename T>
    static void load(const std::filesystem::path& filepath, T& data)
    {
        std::ifstream in{filepath, std::ios::binary};
        load(in, data);
    }


    PUTIT_DEFINE_PRIMITIVE_TYPES


    template <typename T>
    void operator()(T& data, const char* field_name = nullptr)
    {
        (void)field_name; // just ignore
        serialize(*this, data);
    }


    template <typename T>
    void primitive_array(T* data, size_t size)
    {
        if (size == 0)
        {
            return;
        }

        std::unique_ptr<char[]> buf{new char[sizeof(T) * size]};
        in.read(buf.get(), sizeof(T) * size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] =
                detail::byte_swap_if_needed(reinterpret_cast<T*>(buf.get())[i]);
        }
    }


private:
    static constexpr auto memory_size = sizeof(long double);

    std::istream& in;
    char memory[memory_size];


    template <typename T>
    void _primitive(T& data)
    {
        static_assert(memory_size >= sizeof(T), "T's size is too big.");

        in.read(memory, sizeof(T));
        data = detail::byte_swap_if_needed(*reinterpret_cast<T*>(memory));
    }
};



class BinaryOArchive : public OArchiveBase
{
public:
    BinaryOArchive(std::ostream& out)
        : out(out)
    {
    }


    template <typename T>
    static void save(std::ostream& out, T& data)
    {
        BinaryOArchive ar{out};
        ar(data);
    }


    template <typename T>
    static void save(const std::filesystem::path& filepath, T& data)
    {
        std::ofstream out{filepath, std::ios::binary};
        save(out, data);
    }


    PUTIT_DEFINE_PRIMITIVE_TYPES
    PUTIT_DEFINE_PRIMITIVE_TYPES_CONST


    template <typename T>
    void operator()(T& data, const char* field_name = nullptr)
    {
        (void)field_name; // just ignore
        serialize(*this, data);
    }


    template <typename T>
    void primitive_array(const T* data, size_t size)
    {
        if (size == 0)
        {
            return;
        }

        std::unique_ptr<T[]> buf{new T[size]};
        for (size_t i = 0; i < size; ++i)
        {
            buf.get()[i] = detail::byte_swap_if_needed(data[i]);
        }

        out.write(reinterpret_cast<char*>(buf.get()), sizeof(T) * size);
    }


private:
    std::ostream& out;


    template <typename T>
    void _primitive(const T& data)
    {
        T tmp = detail::byte_swap_if_needed(data);
        out.write(reinterpret_cast<const char*>(&tmp), sizeof(data));
    }
};



// SFINAE idiom
#define PUTIT_ENABLE_IF(condition) \
    std::enable_if_t<(condition), std::nullptr_t> = nullptr



template <typename T, PUTIT_ENABLE_IF(!std::is_enum_v<T>)>
void serialize(BinaryIArchive& ar, T& data)
{
    data.serialize(ar);
}



template <typename T, PUTIT_ENABLE_IF(!std::is_enum_v<T>)>
void serialize(BinaryOArchive& ar, T& data)
{
    data.serialize(ar);
}



template <typename E, PUTIT_ENABLE_IF(std::is_enum_v<E>)>
void serialize(BinaryIArchive& ar, E& data)
{
    using PrimitiveType = std::underlying_type_t<E>;

    PrimitiveType tmp;
    ar(tmp);
    data = static_cast<E>(tmp);
}



template <typename E, PUTIT_ENABLE_IF(std::is_enum_v<E>)>
void serialize(BinaryOArchive& ar, E& data)
{
    using PrimitiveType = std::underlying_type_t<E>;

    PrimitiveType tmp = static_cast<PrimitiveType>(data);
    ar(tmp);
}



inline void serialize(BinaryIArchive& ar, std::string& data)
{
    uint64_t length;
    ar(length);
    std::unique_ptr<char[]> buf{new char[length]};
    ar.primitive_array(buf.get(), length);
    data = std::string(buf.get(), length);
}



inline void serialize(BinaryOArchive& ar, std::string& data)
{
    const uint64_t length = data.size();
    ar(length);
    ar.primitive_array(data.c_str(), length);
}



template <typename T>
void serialize(BinaryIArchive& ar, std::vector<T>& data)
{
    uint64_t length;
    ar(length);
    std::unique_ptr<T[]> buf{new T[length]};
    ar.primitive_array(buf.get(), length);
    data = std::vector<T>(buf.get(), buf.get() + length);
}



template <typename T>
void serialize(BinaryOArchive& ar, std::vector<T>& data)
{
    const uint64_t length = data.size();
    ar(length);
    ar.primitive_array(data.data(), length);
}



template <typename T>
void serialize(BinaryIArchive& ar, std::deque<T>& data)
{
    uint64_t length;
    ar(length);
    std::unique_ptr<T[]> buf{new T[length]};
    ar.primitive_array(buf.get(), length);
    data = std::deque<T>(buf.get(), buf.get() + length);
}



template <typename T>
void serialize(BinaryOArchive& ar, std::deque<T>& data)
{
    const uint64_t length = data.size();
    ar(length);
    for (auto&& element : data)
    {
        ar(element);
    }
}



template <size_t N, PUTIT_ENABLE_IF(N <= 32)>
void serialize(BinaryIArchive& ar, std::bitset<N>& data)
{
    uint32_t tmp;
    ar(tmp);
    data = tmp;
}



template <size_t N, PUTIT_ENABLE_IF(N <= 32)>
void serialize(BinaryOArchive& ar, std::bitset<N>& data)
{
    const auto tmp = static_cast<uint32_t>(data.to_ulong());
    ar(tmp);
}



template <size_t N, PUTIT_ENABLE_IF(32 < N && N <= 64)>
void serialize(BinaryIArchive& ar, std::bitset<N>& data)
{
    uint64_t tmp;
    ar(tmp);
    data = tmp;
}



template <size_t N, PUTIT_ENABLE_IF(32 < N && N <= 64)>
void serialize(BinaryOArchive& ar, std::bitset<N>& data)
{
    const auto tmp = static_cast<uint64_t>(data.to_ulong());
    ar(tmp);
}



template <size_t N, PUTIT_ENABLE_IF(64 < N)>
void serialize(BinaryIArchive& ar, std::bitset<N>& data)
{
    std::string buf;
    serialize(ar, buf);
    data = std::bitset<N>(buf);
}



template <size_t N, PUTIT_ENABLE_IF(64 < N)>
void serialize(BinaryOArchive& ar, std::bitset<N>& data)
{
    auto buf = data.to_string();
    serialize(ar, buf);
}



#undef PUTIT_ENABLE_IF
#undef PUTIT_DEFINE_PRIMITIVE_TYPES_CONST
#undef PUTIT_DEFINE_PRIMITIVE_TYPES
#undef PUTIT_DEFINE_PRIMITIVE_TYPES_BASE
#undef PUTIT_DEFINE_ONE_PRIMITIVE_TYPE
#undef PUTIT_EMPTY_TOKEN

} // namespace putit
} // namespace elona
