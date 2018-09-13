#pragma once

#include <iostream>
#include <memory>
#include <vector>



namespace elona
{
namespace putit
{


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


    template <
        typename T,
        std::enable_if_t<sizeof(T) <= sizeof(long long), std::nullptr_t> =
            nullptr>
    void primitive(T& data)
    {
        in.read(memory, sizeof(T));
        data = *reinterpret_cast<T*>(memory);
    }


    template <
        typename T,
        std::enable_if_t<(sizeof(T) > sizeof(long long)), std::nullptr_t> =
            nullptr>
    void primitive(T& data)
    {
        char* buf;
        buf = new char[sizeof(T)];

        in.read(buf, sizeof(T));
        data = *reinterpret_cast<T*>(buf);

        delete[] buf;
    }



    template <typename T>
    void primitive_array(T* data, size_t size)
    {
        if (size == 0)
        {
            return;
        }

        char* buf = new char[sizeof(T) * size];

        in.read(buf, sizeof(T) * size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = reinterpret_cast<T*>(buf)[i];
        }

        delete[] buf;
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
        out.write(reinterpret_cast<const char*>(&data), sizeof(data));
    }


    template <typename T>
    void primitive_array(const T* data, size_t size)
    {
        if (size == 0)
        {
            return;
        }

        out.write(reinterpret_cast<const char*>(data), sizeof(T) * size);
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
