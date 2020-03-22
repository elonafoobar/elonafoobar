#pragma once

#include <string>
#include <unordered_map>

#include "../lua_env/config_table.hpp"
#include "id.hpp"



namespace elona
{
namespace data
{

/**
 * Converts a tags list into a filter for use with flt().
 *
 * @param data data table
 * @param id member field inside data table containing a string list
 * (["man", "slime"])
 *
 * @return the filter list ("/man/slime/")
 */
std::string convert_tags(const lua::ConfigTable& data, const std::string& id);



/**
 * Converts a Lua table into a C++ ID-number table.
 *
 * @param data data table
 * @param id member field inside data table containing a table
 * @return the table
 */
std::unordered_map<data::InstanceId, int> convert_id_number_table(
    const lua::ConfigTable& data,
    const std::string& id);

} // namespace data
} // namespace elona
