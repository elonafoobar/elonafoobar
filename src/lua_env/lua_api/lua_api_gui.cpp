#include "lua_api_gui.hpp"

namespace elona
{
namespace lua
{

void GUI::txt(const std::string& message)
{
    elona::txt(message);
}

void GUI::txt_txtef(const std::string& message, color_index_t color)
{
    GUI::txtef(color);
    elona::txt(message);
}

void GUI::txtef(color_index_t color)
{
    if (color < color_index_t::none || color > color_index_t::yellow_green)
    {
        return;
    }
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
