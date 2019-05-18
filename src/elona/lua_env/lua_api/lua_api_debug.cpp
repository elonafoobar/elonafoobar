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

/**
 * @luadoc
 *
 * Logs a message to log.txt.
 * @tparam string message the message to log
 */
void LuaApiDebug::log(const std::string& message)
{
    ELONA_LOG("lua.debug") << message;
}

/**
 * @luadoc
 *
 * Reports an error to the game console and log file.
 * @tparam string message the error message to report
 */
void LuaApiDebug::report_error(const std::string& message)
{
    std::istringstream sstream(message);
    std::string line;

    txt("Script error: ", Message::color{ColorIndex::red});
    while (getline(sstream, line, '\n'))
    {
        txt(line + "  ", Message::color{ColorIndex::red});
    }

    ELONA_ERROR("lua.debug") << "Script error: " << message;
    std::cerr << "Script error: " << message << std::endl;
}

/**
 * @luadoc
 *
 * Dumps all characters to the log.
 */
void LuaApiDebug::dump_characters()
{
    ELONA_LOG("lua.debug") << "===== Charas =====";
    for (int cnt = 0; cnt < ELONA_MAX_CHARACTERS; ++cnt)
    {
        if (elona::cdata[cnt].state() != Character::State::empty)
            ELONA_LOG("lua.debug")
                << elona::cdata[cnt].index << ") Name: " << elona::name(cnt)
                << ", Pos: " << elona::cdata[cnt].position;
    }
}


/**
 * @luadoc
 *
 * Dumps all items to the log.
 */
void LuaApiDebug::dump_items()
{
    ELONA_LOG("lua.debug") << "===== Items  =====";
    for (const auto& cnt : items(-1))
    {
        if (elona::inv[cnt].number() != 0)
            ELONA_LOG("lua.debug")
                << elona::inv[cnt].index << ") Name: " << elona::itemname(cnt)
                << ", Pos: " << elona::inv[cnt].position
                << ", Curse: " << static_cast<int>(elona::inv[cnt].curse_state)
                << ", Ident: "
                << static_cast<int>(elona::inv[cnt].identification_state)
                << ", Count: " << elona::inv[cnt].count;
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
