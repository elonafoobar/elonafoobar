#pragma once
#include "../lua_env/data_table.hpp"

namespace elona
{
namespace data
{

/// To be called after loading all mod data in LuaEnv.
void initialize(lua::DataTable& data);

} // namespace data
} // namespace elona
