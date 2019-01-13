#include "lua_api_gui.hpp"
#include "../../lua_env/enums/enums.hpp"
#include "../../message.hpp"

namespace elona
{
namespace lua
{

void LuaApiGUI::txt(const std::string& message)
{
    elona::txt(message);
}

void LuaApiGUI::txt_txtef(
    const std::string& message,
    const EnumString& color_name)
{
    LuaApiGUI::txtef(color_name);
    elona::txt(message);
}

void LuaApiGUI::txtef(const EnumString& color_name)
{
    ColorIndex color = LuaEnums::ColorIndexTable.ensure_from_string(color_name);
    elona::Message::instance().txtef(color);
}

void LuaApiGUI::txtnew()
{
    elona::Message::instance().linebreak();
}

void LuaApiGUI::bind(sol::table& api_table)
{
    api_table.set_function(
        "txt", sol::overload(LuaApiGUI::txt, LuaApiGUI::txt_txtef));
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, txtef);
    LUA_API_BIND_FUNCTION(api_table, LuaApiGUI, txtnew);
}

} // namespace lua
} // namespace elona
