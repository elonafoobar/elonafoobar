#include "lua_api_data.hpp"
#include "../../draw.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Reloads the UI assets defined in the <code>core.asset</code> table. Call this
 * if you want changes to the <code>core.asset</code> to be visible.
 */
void LuaApiData::reload_assets()
{
    init_assets();
}

void LuaApiData::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, reload_assets);
}

} // namespace lua
} // namespace elona
