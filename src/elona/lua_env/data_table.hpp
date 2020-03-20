#pragma once

#include "../../thirdparty/sol2/sol.hpp"
#include "../data/id.hpp"
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
     * @param prototype_id the namespaced data prototype ID.
     * @param legacy_instance_id the legacy data instance ID.
     * @return the corresponding new ID or none if not found.
     */
    optional<data::InstanceId> by_legacy(
        data::PrototypeId prototype_id,
        int legacy_instance_id)
    {
        if (const auto id = _storage.traverse_get<sol::optional<std::string>>(
                "_by_legacy_id_tables",
                prototype_id.get(),
                legacy_instance_id,
                "id"))
        {
            return data::InstanceId{*id};
        }
        else
        {
            return none;
        }
    }



    /**
     * Get the data from the raw table.
     *
     * @param prototype_id the namespaced data prototype ID.
     * @param instance_id the namespaced data instance ID.
     * @return the data or none if not found.
     */
    optional<sol::table> raw(
        data::PrototypeId prototype_id,
        data::InstanceId instance_id)
    {
        if (const auto data = _storage.traverse_get<sol::optional<sol::table>>(
                "_instance_storages", prototype_id.get(), instance_id.get()))
        {
            return *data;
        }
        else
        {
            return none;
        }
    }



    /**
     * Get data table for @a prototype_id.
     *
     * @param prototype_id the namespaced data prototype ID.
     * @return the data table or none if not found.
     */
    optional<sol::table> get_table(data::PrototypeId prototype_id)
    {
        if (const auto data = _storage.traverse_get<sol::optional<sol::table>>(
                "_instance_storages", prototype_id.get()))
        {
            return *data;
        }
        else
        {
            return none;
        }
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
