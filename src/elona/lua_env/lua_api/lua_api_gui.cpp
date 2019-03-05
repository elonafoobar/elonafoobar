#include "lua_api_gui.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../message.hpp"

namespace elona
{
namespace lua
{

/**
 * @luadoc
 *
 * Prints some text in the HUD message window.
 * @tparam string message the message to print
 */
void LuaApiGUI::txt(const std::string& message)
{
    elona::txt(message);
}

/**
 * @luadoc txt
 *
 * Prints some text in the HUD message window.
 * @tparam string message the message to print
 * @tparam Color color of the message
 */
void LuaApiGUI::txt_txtef(const std::string& message, const EnumString& color)
{
    auto color_value = LuaEnums::ColorIndexTable.ensure_from_string(color);
    elona::Message::instance().txtef(color_value);
    elona::txt(message, color);
}

/**
 * @luadoc
 *
 * Starts a new message line in the HUD message window.
 */
void LuaApiGUI::txtnew()
{
    elona::Message::instance().linebreak();
}

void LuaApiGUI::bind(sol::table& api_table)
{
    api_table.set_function(
        "txt", sol::overload(LuaApiGUI::txt, LuaApiGUI::txt_txtef));
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, txtnew);
}

} // namespace lua
} // namespace elona
