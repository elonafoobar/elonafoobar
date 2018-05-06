#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace elona
{
namespace putit
{


class iarchive_base
{
};


class oarchive_base
{
};


class binary_iarchive : public iarchive_base
{
public:
    binary_iarchive(std::istream& in)
        : in(in)
        , memory(new char[sizeof(long long)])
    {
        fin.push(boost::iostreams::gzip_decompressor());
        fin.push(in);
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
        char* buf;
        buf = memory.get();

        fin.read(buf, sizeof(T));
        data = *reinterpret_cast<T*>(buf);
    }


    template <
        typename T,
        std::enable_if_t<(sizeof(T) > sizeof(long long)), std::nullptr_t> =
            nullptr>
    void primitive(T& data)
    {
        char* buf;
        buf = new char[sizeof(T)];

        fin.read(buf, sizeof(T));
        data = *reinterpret_cast<T*>(buf);

        delete[] buf;
    }



    template <typename T>
    void primitive_array(T* data, size_t size)
    {
        char* buf = new char[sizeof(T) * size];

        fin.read(buf, sizeof(T) * size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = reinterpret_cast<T*>(buf)[i];
        }

        delete[] buf;
    }


private:
    std::istream& in;
	boost::iostreams::filtering_istream fin;
    std::unique_ptr<char[]> memory;
};



class binary_oarchive : public oarchive_base
{
public:
    binary_oarchive(std::ostream& out)
        : out(out)
    {
        fout.push(boost::iostreams::gzip_compressor());
        fout.push(out);
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
        fout.write(reinterpret_cast<const char*>(&data), sizeof(data));
    }


    template <typename T>
    void primitive_array(const T* data, size_t size)
    {
        fout.write(reinterpret_cast<const char*>(data), sizeof(T) * size);
    }


private:
    std::ostream& out;
	boost::iostreams::filtering_ostream fout;
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
        std::is_base_of<iarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, E& data)
{
    using primitive_type = std::underlying_type_t<E>;

    primitive_type tmp;
    ar.primitive(tmp);
    data = static_cast<E>(tmp);
}



template <
    typename Archive,
    typename E,
    std::enable_if_t<std::is_enum<E>::value, std::nullptr_t> = nullptr,
    std::enable_if_t<
        std::is_base_of<oarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, E& data)
{
    using primitive_type = std::underlying_type_t<E>;

    primitive_type tmp = static_cast<primitive_type>(data);
    ar.primitive(tmp);
}



template <
    typename Archive,
    std::enable_if_t<
        std::is_base_of<iarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::string& data)
{
    std::string::size_type length;
    ar.primitive(length);
    std::unique_ptr<char[]> buf{new char[length]};
    ar.primitive_array(buf.get(), length);
    data = std::string(buf.get(), length);
}



template <
    typename Archive,
    std::enable_if_t<
        std::is_base_of<oarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::string& data)
{
    const auto length = data.size();
    ar.primitive(length);
    ar.primitive_array(data.c_str(), length);
}



template <
    typename Archive,
    typename T,
    std::enable_if_t<
        std::is_base_of<iarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::vector<T>& data)
{
    typename std::vector<T>::size_type length;
    ar.primitive(length);
    std::unique_ptr<T[]> buf{new T[length]};
    ar.primitive_array(buf.get(), length);
    data = std::vector<T>(buf.get(), buf.get() + length);
}



template <
    typename Archive,
    typename T,
    std::enable_if_t<
        std::is_base_of<oarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::vector<T>& data)
{
    const auto length = data.size();
    ar.primitive(length);
    if (length != 0)
    {
        ar.primitive_array(data.data(), length);
    }
}



template <
    typename Archive,
    size_t N,
    std::enable_if_t<
        std::is_base_of<iarchive_base, Archive>::value,
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
        std::is_base_of<oarchive_base, Archive>::value,
        std::nullptr_t> = nullptr>
void serialize(Archive& ar, std::bitset<N>& data)
{
    auto buf = data.to_string();
    serialize(ar, buf);
}


} // namespace putit
} // namespace elona
