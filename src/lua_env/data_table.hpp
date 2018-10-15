#pragma once
#include <string>
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{
namespace lua
{

struct DataTable
{
    DataTable()
    {
        storage = sol::lua_nil;
    }

    DataTable(sol::table data)
        : storage(data)
    {
    }

    optional<std::string> by_legacy(const std::string& type_id, int legacy_id)
    {
        if (auto it = storage.get<sol::optional<std::string>>(
                std::tie("by_legacy", type_id, legacy_id)))
            return *it;

        return none;
    }

    optional<sol::table> raw(const std::string& type_id, const std::string& id)
    {
        if (auto it = storage.get<sol::optional<sol::table>>(
                std::tie("raw", type_id, id)))
            return *it;

        return none;
    }

    sol::table storage;
};

} // namespace lua
} // namespace elona
