#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "defines.hpp"



namespace elona
{
namespace putit
{



namespace detail
{


uint8_t byte_swap(uint8_t n)
{
    return n;
}



uint16_t byte_swap(uint16_t n)
{
    return n << 8 | n >> 8;
}



/* clang-format off */
uint32_t byte_swap(uint32_t n)
{
    return 0
        | (n & 0x0000'00FF) << (8 * 3)
        | (n & 0x0000'FF00) << (8 * 1)
        | (n & 0x00FF'0000) >> (8 * 1)
        | (n & 0xFF00'0000) >> (8 * 3);
}



uint64_t byte_swap(uint64_t n)
{
    return 0
        | (n & 0x0000'0000'0000'00FF) << (8 * 7)
        | (n & 0x0000'0000'0000'FF00) << (8 * 5)
        | (n & 0x0000'0000'00FF'0000) << (8 * 3)
        | (n & 0x0000'0000'FF00'0000) << (8 * 1)
        | (n & 0x0000'00FF'0000'0000) >> (8 * 1)
        | (n & 0x0000'FF00'0000'0000) >> (8 * 3)
        | (n & 0x00FF'0000'0000'0000) >> (8 * 5)
        | (n & 0xFF00'0000'0000'0000) >> (8 * 7);
}
/* clang-format on */



template <
    typename Int,
    std::enable_if_t<(sizeof(Int) > 1), std::nullptr_t> = nullptr>
Int byte_swap_if_needed(Int n)
{
#ifdef ELONA_BIG_ENDIAN
    using UInt = std::make_unsigned_t<Int>;
    return static_cast<Int>(byte_swap(static_cast<UInt>(n)));
#else
    return n;
#endif
}



template <
    typename Int,
    std::enable_if_t<sizeof(Int) == 1, std::nullptr_t> = nullptr>
Int byte_swap_if_needed(Int n)
{
    return n;
}


} // namespace detail



class IArchiveBase
{
};



class OArchiveBase
{
};



class BinaryIArchive : public IArchiveBase
{
public:
    BinaryIArchive(std::istream& in)
        : in(in)
    {
    }


    template <typename T>
    void load(T& data)
    {
        serialize(*this, data);
    }


    template <typename T>
    void operator()(T& data)
    {
        load(data);
    }



    template <typename T>
    void primitive(T& data)
    {
        static_assert(memory_size >= sizeof(T), "T's size is too big.");

        in.read(memory, sizeof(T));
        data = detail::byte_swap_if_needed(*reinterpret_cast<T*>(memory));
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
    static constexpr auto memory_size = sizeof(long long);

    std::istream& in;
    char memory[memory_size];
};



class BinaryOArchive : public OArchiveBase
{
public:
    BinaryOArchive(std::ostream& out)
        : out(out)
    {
    }


    template <typename T>
    void save(T& data)
    {
        serialize(*this, data);
    }


    template <typename T>
    void operator()(T& data)
    {
        save(data);
    }


    template <typename T>
    void primitive(const T& data)
    {
        T tmp = detail::byte_swap_if_needed(data);
        out.write(reinterpret_cast<const char*>(&tmp), sizeof(data));
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
};



template <
    typename Archive,
    typename T,
    std::enable_if_t<!std::is_enum<T>::value, std::nullptr_t> = nullptr>
void serialize(Archive& ar, T& data)
{
    data.serialize(ar);
}


#define PRIMITIVE_TYPES(T) \
    template <typename Archive> \
    void serialize(Archive& ar, T& data) \
    { \
        ar.primitive(data); \
    }

PRIMITIVE_TYPES(bool)
PRIMITIVE_TYPES(char)
PRIMITIVE_TYPES(unsigned char)
PRIMITIVE_TYPES(short)
PRIMITIVE_TYPES(unsigned short)
PRIMITIVE_TYPES(int)
PRIMITIVE_TYPES(unsigned int)
PRIMITIVE_TYPES(long)
PRIMITIVE_TYPES(unsigned long)
PRIMITIVE_TYPES(long long)
PRIMITIVE_TYPES(unsigned long long)
PRIMITIVE_TYPES(float)
PRIMITIVE_TYPES(double)
PRIMITIVE_TYPES(long double)

#undef PRIMITIVE_TYPES



template <
    typename Archive,
    typename E,
    std::enable_if_t<std::is_enum<E>::value, std::nullptr_t> = nullptr,
    std::enable_if_t<
        std::is_base_of<IArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, E& data)
{
    using PrimitiveType = std::underlying_type_t<E>;

    PrimitiveType tmp;
    ar.primitive(tmp);
    data = static_cast<E>(tmp);
}



template <
    typename Archive,
    typename E,
    std::enable_if_t<std::is_enum<E>::value, std::nullptr_t> = nullptr,
    std::enable_if_t<
        std::is_base_of<OArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, E& data)
{
    using PrimitiveType = std::underlying_type_t<E>;

    PrimitiveType tmp = static_cast<PrimitiveType>(data);
    ar.primitive(tmp);
}



template <
    typename Archive,
    std::enable_if_t<
        std::is_base_of<IArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::string& data)
{
    uint64_t length;
    ar.primitive(length);
    std::unique_ptr<char[]> buf{new char[length]};
    ar.primitive_array(buf.get(), length);
    data = std::string(buf.get(), length);
}



template <
    typename Archive,
    std::enable_if_t<
        std::is_base_of<OArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::string& data)
{
    const uint64_t length = data.size();
    ar.primitive(length);
    ar.primitive_array(data.c_str(), length);
}



template <
    typename Archive,
    typename T,
    std::enable_if_t<
        std::is_base_of<IArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::vector<T>& data)
{
    uint64_t length;
    ar.primitive(length);
    std::unique_ptr<T[]> buf{new T[length]};
    ar.primitive_array(buf.get(), length);
    data = std::vector<T>(buf.get(), buf.get() + length);
}



template <
    typename Archive,
    typename T,
    std::enable_if_t<
        std::is_base_of<OArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::vector<T>& data)
{
    const uint64_t length = data.size();
    ar.primitive(length);
    ar.primitive_array(data.data(), length);
}



template <
    typename Archive,
    size_t N,
    std::enable_if_t<
        std::is_base_of<IArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::bitset<N>& data)
{
    std::string buf;
    serialize(ar, buf);
    data = std::bitset<N>(buf);
}



template <
    typename Archive,
    size_t N,
    std::enable_if_t<
        std::is_base_of<OArchiveBase, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::bitset<N>& data)
{
    auto buf = data.to_string();
    serialize(ar, buf);
}


} // namespace putit
} // namespace elona
