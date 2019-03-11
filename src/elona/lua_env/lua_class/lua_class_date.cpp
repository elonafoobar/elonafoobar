#include "lua_class_date.hpp"
#include "../../gdata.hpp"
#include "../../map.hpp"

namespace elona
{
namespace lua
{

void LuaDate::bind(sol::state& lua)
{
    auto LuaDate = lua.create_simple_usertype<Date>();
    LuaDate.set("new", sol::no_constructor);

    // Properties

    /**
     * @luadoc field year num
     */
    LuaDate.set("year", &Date::year);

    /**
     * @luadoc field month num
     */
    LuaDate.set("month", &Date::month);

    /**
     * @luadoc field day num
     */
    LuaDate.set("day", &Date::day);

    /**
     * @luadoc field hour num
     */
    LuaDate.set("hour", &Date::hour);

    /**
     * @luadoc field minute num
     */
    LuaDate.set("minute", &Date::minute);

    /**
     * @luadoc field second num
     */
    LuaDate.set("second", &Date::second);

    // Methods

    /**
     * @luadoc function hours
     *
     * Returns the time in hours since year 0.
     * @treturn num
     */
    LuaDate.set("hours", &Date::hours);


    lua.set_usertype("LuaDate", LuaDate);
}

} // namespace lua
} // namespace elona
