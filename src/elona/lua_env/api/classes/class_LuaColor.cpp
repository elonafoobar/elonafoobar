#include "../../../color.hpp"
#include "../common.hpp"



LUA_API_OPTOUT_SOL_AUTOMAGIC(elona::Color)



/**
 * @luadoc
 *
 * Represents RGBA color.
 */
namespace elona::lua::api::classes::class_LuaColor
{

void bind(sol::state& lua)
{
    /**
     * @luadoc new function
     *
     * Constructs a new LuaColor.
     * @usage local LuaColor = require("core.LuaColor")
     * local c = LuaColor.new()
     */
    auto LuaColor = lua.new_usertype<Color>(
        "LuaColor",
        sol::constructors<
            Color(uint8_t, uint8_t, uint8_t),
            Color(uint8_t, uint8_t, uint8_t, uint8_t),
            Color(uint8_t),
            Color(uint8_t, uint8_t)>());

    /**
     * @luadoc r field num
     *
     * [RW] Red channel.
     */
    LuaColor.set("r", &Color::r);

    /**
     * @luadoc g field num
     *
     * [RW] Green channel.
     */
    LuaColor.set("g", &Color::g);

    /**
     * @luadoc b field num
     *
     * [RW] Blue channel.
     */
    LuaColor.set("b", &Color::b);

    /**
     * @luadoc a field num
     *
     * [RW] Alpha channel.
     */
    LuaColor.set("a", &Color::a);
}

} // namespace elona::lua::api::classes::class_LuaColor
