#include "module_Calc.hpp"

#include "../../../calc.hpp"



namespace elona::lua::api::modules
{

/**
 * @luadoc
 *
 * Calculate object generation level.
 * @tparam num n The base object level.
 * @treturn num The object level.
 */
int LuaApiCalc::calc_objlv(int n)
{
    return elona::calcobjlv(n);
}



void LuaApiCalc::bind(sol::table api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiCalc, calc_objlv);
}

} // namespace elona::lua::api::modules
