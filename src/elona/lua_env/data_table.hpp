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
    /// Initialize with an empty storage.
    DataTable()
        : _storage(sol::lua_nil)
    {
    }



    /// Initialize with @a data.
    DataTable(sol::table data)
        : _storage(data)
    {
    }



    /**
     * Get a new ID by a legacy ID.
     *
     * @param prototype_id the namespaced prototype ID.
     * @param legacy_data_id the legacy data ID.
     * @return the corresponding new ID or none if not found.
     */
    optional<std::string> by_legacy(
        const std::string& prototype_id,
        int legacy_data_id)
    {
        if (auto it = _storage.get<sol::optional<std::string>>(
                std::tie("by_legacy", prototype_id, legacy_data_id)))
            return *it;

        return none;
    }



    /**
     * Get the data from the raw table.
     *
     * @param prototype_id the namespaced prototype ID.
     * @param data_id the namespaced data ID.
     * @return the data or none if not found.
     */
    optional<sol::table> raw(
        const std::string& prototype_id,
        const std::string& data_id)
    {
        if (auto it = _storage.get<sol::optional<sol::table>>(
                std::tie("raw", prototype_id, data_id)))
            return *it;

        return none;
    }



    /**
     * Get data table for @a prototype_id.
     *
     * @param prototype_id the namespaced prototype ID.
     * @return the data table or none if not found.
     */
    optional<sol::table> get_table(const std::string& prototype_id)
    {
        if (auto it = _storage.get<sol::optional<sol::table>>(
                std::tie("raw", prototype_id)))
            return *it;

        return none;
    }



    sol::table& storage()
    {
        return _storage;
    }



private:
    sol::table _storage;
};

} // namespace lua
} // namespace elona
