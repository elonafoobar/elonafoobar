#include "lua_api_gui.hpp"

namespace elona
{
namespace lua
{

void GUI::txt(const std::string& message)
{
    elona::txt(message);
}

void GUI::txt_txtef(const std::string& message, const EnumString& color_name)
{
    GUI::txtef(color_name);
    elona::txt(message);
}

void GUI::txtef(const EnumString& color_name)
{
    ColorIndex color = LuaEnums::ColorIndexTable.ensure_from_string(color_name);
    elona::txtef(color);
}

void GUI::txtnew()
{
    elona::txtnew();
}

void GUI::bind(sol::table& api_table)
{
    api_table.set_function("txt", sol::overload(GUI::txt, GUI::txt_txtef));
    LUA_API_BIND_FUNCTION(api_table, GUI, txtef);
    LUA_API_BIND_FUNCTION(api_table, GUI, txtnew);
}

} // namespace lua
} // namespace elona
