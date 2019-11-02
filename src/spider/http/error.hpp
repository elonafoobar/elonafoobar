#pragma once

#include <stdexcept>
#include <string>



namespace elona
{
namespace spider
{
namespace http
{

struct Error : public std::runtime_error
{
    Error(const std::string& error_message)
        : std::runtime_error(error_message)
    {
    }
};

} // namespace http
} // namespace spider
} // namespace elona
