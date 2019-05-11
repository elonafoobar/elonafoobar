#pragma once

#include <string>



namespace elona
{
namespace spider
{
namespace http
{

struct Error
{
    Error(const std::string& what)
        : _what(what)
    {
    }


    const std::string& what() const
    {
        return _what;
    }



private:
    std::string _what;
};

} // namespace http
} // namespace spider
} // namespace elona
