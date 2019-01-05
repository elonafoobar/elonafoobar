#include "lua_api_debug.hpp"
#include <sstream>
#include "../../character.hpp"
#include "../../enums.hpp"
#include "../../item.hpp"
#include "../../log.hpp"
#include "../../message.hpp"



namespace elona
{
namespace lua
{

void LuaApiDebug::log(const std::string& message)
{
    ELONA_LOG(message);
}

void LuaApiDebug::report_error(const std::string& message)
{
    std::istringstream sstream(message);
    std::string line;

    txt("Script error: ", Message::color{ColorIndex::red});
    while (getline(sstream, line, '\n'))
    {
        txt(line + "  ", Message::color{ColorIndex::red});
    }

    ELONA_LOG("Script error: " << message);
    std::cerr << "Script error: " << message << std::endl;
}

void LuaApiDebug::dump_characters()
{
    ELONA_LOG("===== Charas =====")
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (elona::cdata[cnt].state() != Character::State::empty)
            ELONA_LOG(
                elona::cdata[cnt].index
                << ") Name: " << elona::name(cnt)
                << ", Pos: " << elona::cdata[cnt].position);
    }
}

void LuaApiDebug::dump_items()
{
    ELONA_LOG("===== Items  =====")
    for (const auto& cnt : items(-1))
    {
        if (elona::inv[cnt].number() != 0)
            ELONA_LOG(
                elona::inv[cnt].index
                << ") Name: " << elona::itemname(cnt)
                << ", Pos: " << elona::inv[cnt].position << ", Curse: "
                << static_cast<int>(elona::inv[cnt].curse_state) << ", Ident: "
                << static_cast<int>(elona::inv[cnt].identification_state)
                << ", Count: " << elona::inv[cnt].count);
    }
}

void LuaApiDebug::bind(sol::table& api_table)
{
    LUA_API_BIND_FUNCTION(api_table, LuaApiDebug, log);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDebug, report_error);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDebug, dump_characters);
    LUA_API_BIND_FUNCTION(api_table, LuaApiDebug, dump_items);
}

} // namespace lua
} // namespace elona
