#include "../../../log.hpp"
#include "../common.hpp"



namespace elona::lua::api::modules::module_Log
{

void Log_log(
    log::LogLevel level,
    const std::string& mod_name,
    const std::string& message)
{
    return log::log(level, mod_name, message);
}



log::LogLevel Log_level()
{
    return log::level();
}



void Log_set_level(log::LogLevel new_level)
{
    log::set_level(new_level);
}



void Log_output_stderr(bool should_output)
{
    log::output_stderr(should_output);
}


void bind(sol::table api_table)
{
    /* clang-format off */

    ELONA_LUA_API_BIND_FUNCTION("log", Log_log);
    ELONA_LUA_API_BIND_FUNCTION("level", Log_level);
    ELONA_LUA_API_BIND_FUNCTION("set_level", Log_set_level);
    ELONA_LUA_API_BIND_FUNCTION("output_stderr", Log_output_stderr);

    /* clang-format on */
}

} // namespace elona::lua::api::modules::module_Log
