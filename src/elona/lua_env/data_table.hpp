#pragma once
#include <string>
#include "../../thirdparty/sol2/sol.hpp"
#include "../optional.hpp"

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

    sol::optional<std::string> by_legacy(
        const std::string& type_id,
        int legacy_id)
    {
        return storage.get<sol::optional<std::string>>(
            std::tie("by_legacy", type_id, legacy_id));
    }

    sol::optional<sol::table> raw(
        const std::string& type_id,
        const std::string& id)
    {
        return storage.get<sol::optional<sol::table>>(
            std::tie("raw", type_id, id));
    }

    sol::table storage;
};

} // namespace lua
} // namespace elona
