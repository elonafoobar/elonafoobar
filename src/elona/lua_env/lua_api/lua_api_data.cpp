#include "lua_api_data.hpp"
#include "../../data/types/type_character.hpp"
#include "../../draw.hpp"
#include "../data_manager.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Reloads the UI assets defined in the <code>core.asset</code> table. Call this
 * if you want changes to the <code>core.asset</code> table to be visible.
 */
void LuaApiData::reload_assets()
{
    init_assets();
}

/**
 * @luadoc
 *
 * Reloads the UI assets defined in the <code>core.chara</code> table. Call this
 * if you want changes to the <code>core.chara</code> table to be visible.
 */
void LuaApiData::reload_charas()
{
    the_character_db.initialize(lua::lua->get_data_manager().get());
    the_character_db.load_all();
}

void LuaApiData::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, reload_assets);
    LUA_API_BIND_FUNCTION(api_table, LuaApiData, reload_charas);
}

} // namespace lua
} // namespace elona
