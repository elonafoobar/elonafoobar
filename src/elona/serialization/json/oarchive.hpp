#pragma once

#include <iostream>

#include "../concepts.hpp"



namespace elona::serialization::json
{

class OArchive
{
public:
    class _InternalOArchiveSeq
    {
    public:
        _InternalOArchiveSeq(OArchive& ar, uint64_t length)
            : _ar(ar)
            , _length(length)
        {
            _indent = _ar._indent;
            if (_length == 0)
            {
                _ar._out << "[]";
            }
            else
            {
                _ar._out << "[\n";
            }
            ++_ar._indent;
        }



        template <typename T>
        void seq_element(uint64_t nth, T& element)
        {
            _ar.indent();
            _ar(element);
            if (nth + 1 != _length)
            {
                _ar._out << ",\n";
            }
        }



        void seq_end()
        {
            --_ar._indent;
            if (_length != 0)
            {
                _ar._out << '\n';
                _ar.indent(_indent);
                _ar._out << ']';
            }
        }



    private:
        OArchive& _ar;
        uint64_t _length;
        size_t _indent;
    };



    class _InternalOArchiveMap
    {
    public:
        _InternalOArchiveMap(OArchive& ar, uint64_t length)
            : _ar(ar)
            , _length(length)
        {
            _indent = _ar._indent;
            if (_length == 0)
            {
                _ar._out << "{}";
            }
            else
            {
                _ar._out << "{\n";
            }
            ++_ar._indent;
        }



        template <typename K, typename V>
        void map_element(uint64_t nth, K& key, V& value)
        {
            _ar.indent();
            _ar(key);
            _ar._out << ": ";
            _ar(value);
            if (nth + 1 != _length)
            {
                _ar._out << ",\n";
            }
        }



        void map_end()
        {
            --_ar._indent;
            if (_length != 0)
            {
                _ar._out << '\n';
                _ar.indent(_indent);
                _ar._out << '}';
            }
        }



    private:
        OArchive& _ar;
        uint64_t _length;
        size_t _indent;
    };



    class _InternalOArchiveStruct
    {
    public:
        _InternalOArchiveStruct(OArchive& ar)
            : _ar(ar)
        {
            _indent = _ar._indent;
            _ar._out << "{";
            ++_ar._indent;
        }



        template <typename T>
        void struct_field(const char* field_name, T& value)
        {
            if (_is_first_field)
            {
                _is_first_field = false;
                _ar._out << "\n";
            }
            else
            {
                _ar._out << ",\n";
            }
            std::string field_name_{field_name};
            _ar.indent();
            _ar(field_name_);
            _ar._out << ": ";
            _ar(value);
        }



        void struct_end()
        {
            --_ar._indent;
            if (_is_first_field)
            {
                _ar._out << "}";
            }
            else
            {
                _ar._out << '\n';
                _ar.indent(_indent);
                _ar._out << '}';
            }
        }



    private:
        OArchive& _ar;
        bool _is_first_field = true;
        size_t _indent;
    };



    OArchive(std::ostream& out)
        : _out(out)
    {
    }



    template <typename T>
    void operator()(T& value)
    {
        using ::elona::serialization::serialize;
        serialize(value, *this);
    }



    void scalar(bool& value)
    {
        _out << (value ? "true" : "false");
    }


#define ELONA_SERIALIZATION_DEFINE_SCALAR(type) \
    void scalar(type& value) \
    { \
        _out << value; \
    }

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

#undef ELONA_SERIALIZATION_DEFINE_SCALAR



    void scalar(char& value)
    {
        std::string tmp{1, value};
        str(tmp);
    }



    void str(std::string& value)
    {
        // TODO: consider the case that `value` has non-printable character.
        std::string quoted;
        quoted.reserve(value.size() + 2);
        quoted += '"';
        for (const auto& c : value)
        {
            if (c == '"' || c == '\\')
            {
                quoted += '\\';
            }
            quoted += c;
        }
        quoted += '"';
        _out << quoted;
    }



    _InternalOArchiveSeq seq_begin(uint64_t& length)
    {
        return _InternalOArchiveSeq{*this, length};
    }



    _InternalOArchiveMap map_begin(uint64_t& length)
    {
        return _InternalOArchiveMap{*this, length};
    }



    _InternalOArchiveStruct struct_begin([
        [maybe_unused]] const char* struct_name)
    {
        return _InternalOArchiveStruct{*this};
    }



private:
    std::ostream& _out;
    size_t _indent = 0;



    void indent(size_t level)
    {
        _out << std::string(2 * level, ' ');
    }


    void indent()
    {
        indent(_indent);
    }
};

} // namespace elona::serialization::json
