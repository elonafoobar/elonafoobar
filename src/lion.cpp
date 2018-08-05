#include "lion.hpp"

namespace elona
{
namespace lion
{

std::string convert_tags(const sol::table& data, const std::string& id)
{
    std::string filter = "";
    sol::optional<sol::table> value = data[id];

    if (value)
    {
        for (const auto& pair : *value)
        {
            if (filter == ""s)
            {
                filter += "/";
            }
            filter += pair.second.as<std::string>() + "/";
        }
    }

    return filter;
}

} // namespace lion
} // namespace elona
