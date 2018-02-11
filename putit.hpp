#pragma once

#include <iostream>
#include <memory>


namespace elona::putit
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
        char* buf;
        if constexpr (sizeof(T) <= sizeof(long long))
        {
            buf = memory.get();
        }
        else
        {
            buf = new char[sizeof(T)];
        }

        in.read(buf, sizeof(T));
        data = *reinterpret_cast<T*>(buf);

        if constexpr (sizeof(T) > sizeof(long long))
        {
            delete[] buf;
        }
    }



    template <typename T>
    void primitive_array(T* data, size_t size)
    {
        char* buf = new char[sizeof(T) * size];

        in.read(buf, sizeof(T) * size);
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = reinterpret_cast<T*>(buf)[i];
        }

        delete[] buf;
    }


private:
    std::istream& in;
    std::unique_ptr<char[]> memory;
};



class binary_oarchive : public oarchive_base
{
public:
    binary_oarchive(std::ostream& out)
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
        out.write(reinterpret_cast<const char*>(data), sizeof(T) * size);
    }


private:
    std::ostream& out;
};



template <typename Archive, typename T>
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



template <typename Archive>
void serialize(Archive& ar, std::string& data)
{
    if constexpr (std::is_base_of_v<iarchive_base, Archive>)
    {
        std::string::size_type length;
        ar.primitive(length);
        std::unique_ptr<char[]> buf{new char[length]};
        ar.primitive_array(buf.get(), length);
        data = std::string(buf.get(), length);
    }
    else
    {
        const auto length = std::size(data);
        ar.primitive(length);
        ar.primitive_array(data.c_str(), length);
    }
}


} // namespace elona::putit
