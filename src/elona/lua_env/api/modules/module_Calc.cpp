#include "module_Calc.hpp"

#include "../../../calc.hpp"



namespace elona::lua::api::modules::module_Calc
{

/**
 * @luadoc calc_objlv
 *
 * Calculate object generation level.
 *
 * @tparam num n The base object level.
 * @treturn num The object level.
 */
int Calc_calc_objlv(int n)
{
    return calcobjlv(n);
}



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("calc_objlv", Calc_calc_objlv);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Calc
