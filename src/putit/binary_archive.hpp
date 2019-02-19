#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../util/filepathutil.hpp"
#include "archive_base.hpp"
#include "detail/byte_swap.hpp"



namespace elona
{
namespace putit
{

class BinaryIArchive : public IArchiveBase
{
public:
    BinaryIArchive(std::istream& in)
        : in(in)
    {
    }


    template <typename T>
    static void load(const boost::filesystem::path& filepath, T& data)
    {
        std::ifstream in{filepath.native(), std::ios::binary};
        BinaryIArchive ar{in};
        ar.load(data);
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
    static void save(const boost::filesystem::path& filepath, T& data)
    {
        std::ofstream out{filepath.native(), std::ios::binary};
        BinaryOArchive ar{out};
        ar.save(data);
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



// SFINAE idiom
#define PUTIT_ENABLE_IF(condition) \
    std::enable_if_t<(condition), std::nullptr_t> = nullptr

// Double parens are necessary to make cpp (c preprocessor) pass arguments as
// one argument to PUTIT_ENABLE_IF.
#define PUTIT_IARCHIVE \
    PUTIT_ENABLE_IF((std::is_base_of<IArchiveBase, Archive>::value))
#define PUTIT_OARCHIVE \
    PUTIT_ENABLE_IF((std::is_base_of<OArchiveBase, Archive>::value))



template <
    typename Archive,
    typename T,
    PUTIT_ENABLE_IF(!std::is_enum<T>::value)>
void serialize(Archive& ar, T& data)
{
    data.serialize(ar);
}


#define PUTIT_PRIMITIVE_TYPES(T) \
    template <typename Archive> \
    void serialize(Archive& ar, T& data) \
    { \
        ar.primitive(data); \
    }

PUTIT_PRIMITIVE_TYPES(bool)
PUTIT_PRIMITIVE_TYPES(char)
PUTIT_PRIMITIVE_TYPES(unsigned char)
PUTIT_PRIMITIVE_TYPES(short)
PUTIT_PRIMITIVE_TYPES(unsigned short)
PUTIT_PRIMITIVE_TYPES(int)
PUTIT_PRIMITIVE_TYPES(unsigned int)
PUTIT_PRIMITIVE_TYPES(long)
PUTIT_PRIMITIVE_TYPES(unsigned long)
PUTIT_PRIMITIVE_TYPES(long long)
PUTIT_PRIMITIVE_TYPES(unsigned long long)
PUTIT_PRIMITIVE_TYPES(float)
PUTIT_PRIMITIVE_TYPES(double)
PUTIT_PRIMITIVE_TYPES(long double)

#undef PUTIT_PRIMITIVE_TYPES



template <
    typename Archive,
    typename E,
    PUTIT_ENABLE_IF(std::is_enum<E>::value),
    PUTIT_IARCHIVE>
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
    PUTIT_ENABLE_IF(std::is_enum<E>::value),
    PUTIT_OARCHIVE>
void serialize(Archive& ar, E& data)
{
    using PrimitiveType = std::underlying_type_t<E>;

    PrimitiveType tmp = static_cast<PrimitiveType>(data);
    ar.primitive(tmp);
}



template <typename Archive, PUTIT_IARCHIVE>
void serialize(Archive& ar, std::string& data)
{
    uint64_t length;
    ar.primitive(length);
    std::unique_ptr<char[]> buf{new char[length]};
    ar.primitive_array(buf.get(), length);
    data = std::string(buf.get(), length);
}



template <typename Archive, PUTIT_OARCHIVE>
void serialize(Archive& ar, std::string& data)
{
    const uint64_t length = data.size();
    ar.primitive(length);
    ar.primitive_array(data.c_str(), length);
}



template <typename Archive, typename T, PUTIT_IARCHIVE>
void serialize(Archive& ar, std::vector<T>& data)
{
    uint64_t length;
    ar.primitive(length);
    std::unique_ptr<T[]> buf{new T[length]};
    ar.primitive_array(buf.get(), length);
    data = std::vector<T>(buf.get(), buf.get() + length);
}



template <typename Archive, typename T, PUTIT_OARCHIVE>
void serialize(Archive& ar, std::vector<T>& data)
{
    const uint64_t length = data.size();
    ar.primitive(length);
    ar.primitive_array(data.data(), length);
}



template <typename Archive, size_t N, PUTIT_ENABLE_IF(N <= 32), PUTIT_IARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    uint32_t tmp;
    ar.primitive(tmp);
    data = tmp;
}



template <typename Archive, size_t N, PUTIT_ENABLE_IF(N <= 32), PUTIT_OARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    const auto tmp = static_cast<uint32_t>(data.to_ulong());
    ar.primitive(tmp);
}



template <
    typename Archive,
    size_t N,
    PUTIT_ENABLE_IF(32 < N && N <= 64),
    PUTIT_IARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    uint64_t tmp;
    ar.primitive(tmp);
    data = tmp;
}



template <
    typename Archive,
    size_t N,
    PUTIT_ENABLE_IF(32 < N && N <= 64),
    PUTIT_OARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    const auto tmp = static_cast<uint64_t>(data.to_ulong());
    ar.primitive(tmp);
}



template <typename Archive, size_t N, PUTIT_ENABLE_IF(64 < N), PUTIT_IARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    std::string buf;
    serialize(ar, buf);
    data = std::bitset<N>(buf);
}



template <typename Archive, size_t N, PUTIT_ENABLE_IF(64 < N), PUTIT_OARCHIVE>
void serialize(Archive& ar, std::bitset<N>& data)
{
    auto buf = data.to_string();
    serialize(ar, buf);
}



#undef PUTIT_ENABLE_IF
#undef PUTIT_IARCHIVE
#undef PUTIT_OARCHIVE

} // namespace putit
} // namespace elona
