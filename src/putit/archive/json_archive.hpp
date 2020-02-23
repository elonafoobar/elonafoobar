#pragma once

#include <cstdint>

#include <iostream>
#include <memory>
#include <vector>

#include "../../thirdparty/json5/json5.hpp"
#include "../../util/filepathutil.hpp"
#include "archive_base.hpp"



namespace elona
{
namespace putit
{

#define PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(type) \
    void operator()(type& data, const char* field_name) \
    { \
        _obj[field_name] = data; \
    } \
    void operator()(const type& data, const char* field_name) \
    { \
        _obj[field_name] = data; \
    }

#define PUTIT_DEFINE_PRIMITIVE_TYPES \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(bool) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(char) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(int8_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(uint8_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(int16_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(uint16_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(int32_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(uint32_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(int64_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(uint64_t) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(float) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(double) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(long double) \
    PUTIT_DEFINE_ONE_PRIMITIVE_TYPE(std::string)



// SFINAE idiom
#define PUTIT_ENABLE_IF(condition) \
    std::enable_if_t<(condition), std::nullptr_t> = nullptr



class JsonOArchive : public OArchiveBase
{
private:
    class JsonOArchiveInternal : OArchiveBase
    {
    public:
        JsonOArchiveInternal()
            : _obj()
        {
        }


        PUTIT_DEFINE_PRIMITIVE_TYPES



        template <typename E, PUTIT_ENABLE_IF(std::is_enum_v<E>)>
        void operator()(E& data, const char* field_name = nullptr)
        {
            _obj[field_name] = static_cast<std::underlying_type_t<E>>(data);
        }



        template <typename T, PUTIT_ENABLE_IF(!std::is_enum_v<T>)>
        void operator()(T& data, const char* field_name = nullptr)
        {
            JsonOArchiveInternal ar_;
            data.serialize(ar_);
            _obj[field_name] = ar_.object();
        }


        template <typename T, PUTIT_ENABLE_IF(std::is_class<T>::value)>
        void operator()(std::vector<T>& data, const char* field_name = nullptr)
        {
            json5::value::array_type array;
            for (auto&& element : data)
            {
                JsonOArchiveInternal ar_;
                element.serialize(ar_);
                array.push_back(ar_.object());
            }
            _obj[field_name] = array;
        }


        template <
            typename T,
            PUTIT_ENABLE_IF(!std::is_class<T>::value && !std::is_enum_v<T>)>
        void operator()(std::vector<T>& data, const char* field_name = nullptr)
        {
            json5::value::array_type array;
            for (auto&& element : data)
            {
                array.push_back(element);
            }
            _obj[field_name] = array;
        }


        template <typename E, PUTIT_ENABLE_IF(std::is_enum_v<E>)>
        void operator()(std::vector<E>& data, const char* field_name = nullptr)
        {
            json5::value::array_type array;
            for (auto&& element : data)
            {
                array.push_back(
                    static_cast<std::underlying_type_t<E>>(element));
            }
            _obj[field_name] = array;
        }


        template <size_t N, PUTIT_ENABLE_IF(N <= 32)>
        void operator()(std::bitset<N>& data, const char* field_name = nullptr)
        {
            _obj[field_name] = data.to_ulong();
        }



        template <size_t N, PUTIT_ENABLE_IF(32 < N && N <= 64)>
        void operator()(std::bitset<N>& data, const char* field_name = nullptr)
        {
            _obj[field_name] = data.to_ulong();
        }



        template <size_t N, PUTIT_ENABLE_IF(64 < N)>
        void operator()(std::bitset<N>& data, const char* field_name = nullptr)
        {
            _obj[field_name] = data.to_string();
        }


        const json5::value::object_type& object() const
        {
            return _obj;
        }


    private:
        json5::value::object_type _obj;
    };



public:
    JsonOArchive(std::ostream& out)
        : out(out)
    {
    }


    template <typename T>
    static void save(std::ostream& out, T& data)
    {
        JsonOArchive ar{out};
        ar(data);
    }


    template <typename T>
    static void save(const boost::filesystem::path& filepath, T& data)
    {
        std::ofstream out{filepath.native(), std::ios::binary};
        save(out, data);
    }


    template <typename T>
    void operator()(T& data, const char* field_name = nullptr)
    {
        (void)field_name;
        serialize(*this, data);
    }


    JsonOArchiveInternal _get_internal_archive()
    {
        return JsonOArchiveInternal{};
    }


    void _save(const JsonOArchiveInternal& ar_)
    {
        out << json5::stringify(ar_.object());
    }


private:
    std::ostream& out;
};



template <typename T, PUTIT_ENABLE_IF(!std::is_enum_v<T>)>
void serialize(JsonOArchive& ar, T& data)
{
    auto ar_ = ar._get_internal_archive();
    data.serialize(ar_);
    ar._save(ar_);
}



#undef PUTIT_ENABLE_IF
#undef PUTIT_DEFINE_PRIMITIVE_TYPES
#undef PUTIT_DEFINE_ONE_PRIMITIVE_TYPE

} // namespace putit
} // namespace elona
