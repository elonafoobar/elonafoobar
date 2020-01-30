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
