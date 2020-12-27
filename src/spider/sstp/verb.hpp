#pragma once

#include <string>



namespace elona
{
namespace spider
{
namespace sstp
{
namespace Verb
{

struct Verb
{
    const char* method;
    const char* version;


    constexpr Verb(const char* method, const char* version)
        : method(method)
        , version(version)
    {
    }


    std::string to_string() const
    {
        return std::to_string(method) + "/" + version;
    }
};

constexpr Verb notify{"NOTIFY", "1.1"};
constexpr Verb send{"SEND", "1.4"};
constexpr Verb execute{"EXECUTE", "1.3"};
constexpr Verb communicate{"COMMUNICATE", "1.2"};

} // namespace Verb
} // namespace sstp
} // namespace spider
} // namespace elona
