#include "../../../time.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::time::Time)



/**
 * @luadoc
 *
 * Represents a time of day.
 */
namespace elona::lua::api::classes::class_LuaTime
{

void bind(sol::state& lua)
{
    auto LuaTime = lua.new_usertype<time::Time>("LuaTime", sol::no_constructor);

    // Properties

    /**
     * @luadoc hour field num
     */
    LuaTime.set("hour", sol::property([](const time::Time& self) {
                    return self.hour();
                }));

    /**
     * @luadoc minute field num
     */
    LuaTime.set("minute", sol::property([](const time::Time& self) {
                    return self.minute();
                }));

    /**
     * @luadoc second field num
     */
    LuaTime.set("second", sol::property([](const time::Time& self) {
                    return self.second();
                }));

    /**
     * @luadoc millisecond field num
     */
    LuaTime.set("millisecond", sol::property([](const time::Time& self) {
                    return self.millisecond();
                }));
}

} // namespace elona::lua::api::classes::class_LuaTime
