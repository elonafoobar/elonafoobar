#pragma once

#include <cassert>
#include <cmath>
#include "../types.hpp"
#include "./util.hpp"



namespace json5
{
namespace detail
{

enum class token_type
{
    eof,

    bracket_left,
    bracket_right,
    brace_left,
    brace_right,
    colon,
    comma,

    null,
    true_,
    false_,
    infinity,
    nan,

    integer,
    number,
    string,
    identifier,
};



struct token
{
public:
    token()
        : _type(token_type::eof)
        , _as(integer_type{}) // dummy
    {
    }



    token(token_type type)
        : _type(type)
        , _as(integer_type{}) // dummy
    {
    }



    token(integer_type value)
        : _type(token_type::integer)
        , _as(value)
    {
    }



    token(number_type value)
        : _type(token_type::number)
        , _as(value)
    {
    }



    token(token_type type, const string_type& value)
        : _type(type)
        , _as(new string_type(value))
    {
        assert(type == token_type::string || type == token_type::identifier);
    }



    token(token_type type, string_type&& value)
        : _type(type)
        , _as(new string_type(std::move(value)))
    {
        assert(type == token_type::string || type == token_type::identifier);
    }



    token(token_type type, const string_type::value_type* value)
        : _type(type)
        , _as(new string_type(value))
    {
        assert(type == token_type::string || type == token_type::identifier);
    }



    token(const token& other)
        : _type(other._type)
        , _as(other._as)
    {
        switch (_type)
        {
        case token_type::string:
        case token_type::identifier:
            _as.string = new string_type(*other._as.string);
            break;
        default: break;
        }
    }



    token(token&& other) noexcept
        : _type(other._type)
        , _as(other._as)
    {
        switch (_type)
        {
        case token_type::string:
        case token_type::identifier: other._as.string = nullptr; break;
        default: break;
        }
    }



    token& operator=(const token& other)
    {
        token tmp = other;
        tmp.swap(*this);
        return *this;
    }



    token& operator=(token&& other) noexcept
    {
        token tmp = std::move(other);
        tmp.swap(*this);
        return *this;
    }



    void swap(token& other)
    {
        std::swap(_type, other._type);
        std::swap(_as, other._as);
    }



    ~token()
    {
        if (_type == token_type::string || _type == token_type::identifier)
        {
            delete _as.string;
        }
    }



    constexpr token_type type() const noexcept
    {
        return _type;
    }



    constexpr integer_type get_integer() const noexcept
    {
        return _as.integer;
    }



    constexpr number_type get_number() const noexcept
    {
        return _as.number;
    }



    constexpr const string_type& get_string() const noexcept
    {
        return *_as.string;
    }



    std::string to_string() const
    {
        switch (_type)
        {
        case token_type::eof: return "<EOF>";
        case token_type::bracket_left: return "'['";
        case token_type::bracket_right: return "']'";
        case token_type::brace_left: return "'{'";
        case token_type::brace_right: return "'}'";
        case token_type::colon: return "':'";
        case token_type::comma: return "','";
        case token_type::null: return "null";
        case token_type::true_: return "true";
        case token_type::false_: return "false";
        case token_type::infinity: return "Infinity";
        case token_type::nan: return "NaN";
        case token_type::integer: return std::to_string(get_integer());
        case token_type::number:
        {
            const auto p = get_number();
            if (std::isnan(p))
            {
                return "NaN";
            }
            else if (std::isinf(p))
            {
                return p < 0 ? "-Infinity" : "Infinity";
            }
            else
            {
                return std::to_string(p);
            }
        }
        case token_type::string:
        case token_type::identifier: return get_string();
        default: return "<invalid>";
        }
    }



private:
    token_type _type;


    union _U
    {
        integer_type integer;
        number_type number;
        string_type* string;



        constexpr _U(integer_type v)
            : integer(v)
        {
        }


        constexpr _U(number_type v)
            : number(v)
        {
        }


        constexpr _U(string_type* v)
            : string(v)
        {
        }
    } _as;
};

} // namespace detail
} // namespace json5
