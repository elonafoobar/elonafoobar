#include "../../../time.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::time::Date)



/**
 * @luadoc
 *
 * Represents a date.
 */
namespace elona::lua::api::classes::class_LuaDate
{

void bind(sol::state& lua)
{
    auto LuaDate = lua.new_usertype<time::Date>("LuaDate", sol::no_constructor);

    // Properties

    /**
     * @luadoc year field num
     */
    LuaDate.set("year", sol::property([](const time::Date& self) {
                    return self.year();
                }));

    /**
     * @luadoc month field num
     */
    LuaDate.set("month", sol::property([](const time::Date& self) {
                    return self.month();
                }));

    /**
     * @luadoc day field num
     */
    LuaDate.set("day", sol::property([](const time::Date& self) {
                    return self.day();
                }));
}

} // namespace elona::lua::api::classes::class_LuaDate
