#include "lua_class_date_time.hpp"

#include "../../gdata.hpp"
#include "../../map.hpp"

namespace elona
{
namespace lua
{

void LuaDateTime::bind(sol::state& lua)
{
    auto LuaDateTime = lua.create_simple_usertype<DateTime>();
    LuaDateTime.set("new", sol::no_constructor);

    // Properties

    /**
     * @luadoc year field num
     */
    LuaDateTime.set("year", &DateTime::year);

    /**
     * @luadoc month field num
     */
    LuaDateTime.set("month", &DateTime::month);

    /**
     * @luadoc day field num
     */
    LuaDateTime.set("day", &DateTime::day);

    /**
     * @luadoc hour field num
     */
    LuaDateTime.set("hour", &DateTime::hour);

    /**
     * @luadoc minute field num
     */
    LuaDateTime.set("minute", &DateTime::minute);

    /**
     * @luadoc second field num
     */
    LuaDateTime.set("second", &DateTime::second);

    // Methods

    /**
     * @luadoc hours function
     *
     * Returns the time in hours since year 0.
     * @treturn num
     */
    LuaDateTime.set("hours", &DateTime::hours);

    LuaDateTime.set("__tostring", &DateTime::to_string);

    lua.set_usertype("LuaDateTime", LuaDateTime);
}

} // namespace lua
} // namespace elona
