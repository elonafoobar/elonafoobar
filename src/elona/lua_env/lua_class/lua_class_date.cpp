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
     * @luadoc year field num
     */
    LuaDate.set("year", &Date::year);

    /**
     * @luadoc month field num
     */
    LuaDate.set("month", &Date::month);

    /**
     * @luadoc day field num
     */
    LuaDate.set("day", &Date::day);

    /**
     * @luadoc hour field num
     */
    LuaDate.set("hour", &Date::hour);

    /**
     * @luadoc minute field num
     */
    LuaDate.set("minute", &Date::minute);

    /**
     * @luadoc second field num
     */
    LuaDate.set("second", &Date::second);

    // Methods

    /**
     * @luadoc hours function
     *
     * Returns the time in hours since year 0.
     * @treturn num
     */
    LuaDate.set("hours", &Date::hours);


    lua.set_usertype("LuaDate", LuaDate);
}

} // namespace lua
} // namespace elona
