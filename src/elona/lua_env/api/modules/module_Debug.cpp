#include "module_Debug.hpp"

#include <sstream>

#include "../../../log.hpp"
#include "../../../message.hpp"



namespace elona::lua::api::modules::module_Debug
{

/**
 * @luadoc log
 *
 * Logs a message to log.txt.
 *
 * @tparam string message the message to log
 */
void Debug_log(const std::string& message)
{
    ELONA_LOG("lua.debug") << message;
}



/**
 * @luadoc report_error
 *
 * Reports an error to the game console and log file.
 *
 * @tparam string message the error message to report
 */
void Debug_report_error(const std::string& message)
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



void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("log", Debug_log);
    ELONA_LUA_API_BIND_FUNCTION("report_error", Debug_report_error);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Debug
