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



std::unordered_map<data::InstanceId, int> convert_id_number_table(
    const lua::ConfigTable& data,
    const std::string& id)
{
    std::unordered_map<data::InstanceId, int> ret;

    if (auto it = data.optional<sol::table>(id))
    {
        for (const auto& kvp : *it)
        {
            data::InstanceId key{kvp.first.as<std::string>()};
            int value = kvp.second.as<int>();
            ret.emplace(key, value);
        }
    }

    return ret;
}

} // namespace data
} // namespace elona
