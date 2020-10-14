#include "../../../time.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::time::DateTime)



/**
 * @luadoc
 *
 * Represents a date and time.
 */
namespace elona::lua::api::classes::class_LuaDateTime
{

void bind(sol::state& lua)
{
    auto LuaDateTime =
        lua.new_usertype<time::DateTime>("LuaDateTime", sol::no_constructor);

    // Properties

    /**
     * @luadoc year field num
     */
    LuaDateTime.set("year", sol::property([](const time::DateTime& self) {
                        return self.year();
                    }));

    /**
     * @luadoc month field num
     */
    LuaDateTime.set("month", sol::property([](const time::DateTime& self) {
                        return self.month();
                    }));

    /**
     * @luadoc day field num
     */
    LuaDateTime.set("day", sol::property([](const time::DateTime& self) {
                        return self.day();
                    }));

    /**
     * @luadoc hour field num
     */
    LuaDateTime.set("hour", sol::property([](const time::DateTime& self) {
                        return self.hour();
                    }));

    /**
     * @luadoc minute field num
     */
    LuaDateTime.set("minute", sol::property([](const time::DateTime& self) {
                        return self.minute();
                    }));

    /**
     * @luadoc second field num
     */
    LuaDateTime.set("second", sol::property([](const time::DateTime& self) {
                        return self.second();
                    }));

    /**
     * @luadoc millisecond field num
     */
    LuaDateTime.set(
        "millisecond", sol::property([](const time::DateTime& self) {
            return self.millisecond();
        }));
}

} // namespace elona::lua::api::classes::class_LuaDateTime
