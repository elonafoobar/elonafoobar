#pragma once

#include <stdexcept>
#include <string>
#include "./detail/token.hpp"
#include "./value_type.hpp"



namespace json5
{

struct invalid_type_error : public std::runtime_error
{
    invalid_type_error(value_type actual_type, value_type expected_type)
        : std::runtime_error(build_error_message(actual_type, expected_type))
        , _actual_type(actual_type)
        , _expected_type(expected_type)
    {
    }



    value_type actual_type() const noexcept
    {
        return _actual_type;
    }



    value_type expected_type() const noexcept
    {
        return _expected_type;
    }



private:
    value_type _actual_type;
    value_type _expected_type;



    static std::string build_error_message(
        value_type actual_type,
        value_type expected_type)
    {
        return std::string{"expect "} + to_string(expected_type) +
            ", but actually " + to_string(actual_type);
    }
};



struct parse_error : public std::runtime_error
{
    parse_error(const detail::token& actual_token, const char* expected_token)
        : std::runtime_error(build_error_message(actual_token, expected_token))
        , _actual_token(actual_token)
        , _expected_token(expected_token)
    {
    }



    const detail::token& actual_token() const noexcept
    {
        return _actual_token;
    }



    const char* expected_token() const noexcept
    {
        return _expected_token;
    }



private:
    const detail::token& _actual_token;
    const char* _expected_token;



    static std::string build_error_message(
        const detail::token& actual_token,
        const char* expected_token)
    {
        return std::string{"expect "} + expected_token + ", but actually " +
            actual_token.to_string();
    }
};



struct syntax_error : public std::runtime_error
{
    syntax_error(const char* error_message)
        : std::runtime_error(error_message)
    {
    }



    syntax_error(const std::string& error_message)
        : std::runtime_error(error_message)
    {
    }
};

} // namespace json5
