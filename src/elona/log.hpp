#pragma once

/*
 * Elona foobar's log library
 *
 * Log format: elapsedtime LEVEL [tag] Message
 * - The elapsed time is recorded in second.
 * - There are 4 severity level: log, warn, error and fatal. See Logger::Level
 *   for details.
 * - Tag shows the module which outputs the log line. E.g., "system", "lua.mod".
 *
 * Example: 1.234 ERROR [Mod] Failed to load mod "api_nuts".
 *
 * Log files are saved in "/path/to/elonafoobar/log". These files are rotated
 * (https://en.wikipedia.org/wiki/Log_rotation) on every launching, and
 * "log/0.log" is the latest. The larger the digit is, the older the log file
 * is. Currently, Elona foobar stores up to 10 logs, including the latest.
 */

#include "filesystem.hpp"



namespace elona::log
{

/// Log severity level
enum class LogLevel
{
    /**
     * Serious; Elona will handle the errors and continue to run, but the
     * error will be notified to let players know there are something wrong.
     * E.g., mod loading error, corrupted save.
     */
    error = 5,

    /**
     * Unusual, but easily recoverable; Elona will continue to run.
     * E.g., detected obsolete things, trivial errors.
     */
    warn = 4,

    /**
     * Normal; everything is okay.
     * E.g., launching, loading save, loading mod.
     */
    info = 3,

    /**
     * For debugging.
     */
    debug = 2,

    /**
     * For more verbose debugging.
     */
    trace = 1,
};



/// Initialize logger.
/// @param log_dir Where all log files are placed.
/// @param initial_level Initial max log level
void init(const fs::path& log_dir, LogLevel initial_level);

/// Output log.
/// @param level Severity
/// @param mod_name Mod which calls this function.
/// @param message Message to output
void log(
    LogLevel level,
    const std::string& mod_name,
    const std::string& message);

/// Get log level
LogLevel level();

/// Set log level
void set_level(LogLevel new_level);

/// Set whether log should be output to stderr.
/// @param should_output Whether log should be output to stderr
void output_stderr(bool should_output);

} // namespace elona::log



#define ELONA_ERROR(msg) \
    ::elona::log::log(::elona::log::LogLevel::error, "_native_", msg)

#define ELONA_WARN(msg) \
    ::elona::log::log(::elona::log::LogLevel::warn, "_native_", msg)

#define ELONA_LOG(msg) \
    ::elona::log::log(::elona::log::LogLevel::info, "_native_", msg)
