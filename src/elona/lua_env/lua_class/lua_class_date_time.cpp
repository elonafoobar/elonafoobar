#include "lua_class_date_time.hpp"

#include "../../gdata.hpp"
#include "../../map.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::DateTime)



namespace elona
{
namespace lua
{

void LuaDateTime::bind(sol::state& lua)
{
    auto LuaDateTime =
        lua.new_usertype<DateTime>("LuaDateTime", sol::no_constructor);

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

    LuaDateTime.set(sol::meta_function::to_string, &DateTime::to_string);
}

} // namespace lua
} // namespace elona
