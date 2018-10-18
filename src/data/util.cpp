#include "util.hpp"

using namespace std::literals::string_literals;

namespace elona
{
namespace data
{

std::string convert_tags(const lua::ConfigTable& data, const std::string& id)
{
    std::string filter = "";

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& pair : *it)
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

} // namespace data
} // namespace elona
