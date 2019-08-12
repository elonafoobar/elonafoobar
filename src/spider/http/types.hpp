#pragma once

#include <string>
#include <unordered_map>



namespace elona
{
namespace spider
{
namespace http
{

// HTTP status
using Status = int;

// HTTP request/response headers
using Headers = std::unordered_map<std::string, std::string>;

// HTTP request/response body
using Body = std::string;

// HTTP URL
using Url = std::string;



// HTTP verb (method)
enum class Verb
{
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    OPTIONS,
    PATCH,
    CONNECT,
    TRACE,
};

} // namespace http
} // namespace spider
} // namespace elona
