#pragma once
#include <string>
#include <vector>

#include "../../thirdparty/sol2/sol.hpp"
#include "../lua_env/config_table.hpp"
#include "../optional.hpp"

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

} // namespace data
} // namespace elona
