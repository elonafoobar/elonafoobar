#include "lua_api_calc.hpp"
#include "../../calc.hpp"

namespace elona
{
namespace lua
{

int Calc::calc_objlv(int n)
{
    return elona::calcobjlv(n);
}

void Calc::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, Calc, calc_objlv);
}

} // namespace lua
} // namespace elona
