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

#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <type_traits>
#include "../util/noncopyable.hpp"



namespace elona
{
namespace log
{

/// The logger class
class Logger : lib::noncopyable
{
private:
    using duration = std::chrono::duration<double>;


public:
    /// Log severity level
    enum class Level
    {
        /**
         * Normal; everything is okay.
         * E.g., launching, loading save, loading mod.
         */
        log,
        /**
         * Unusual, but easily recoverable; Elona will continue to run.
         * E.g., detected obsolete things, trivial errors.
         */
        warn,
        /**
         * Serious; Elona will handle the errors and continue to run, but the
         * error will be notified to let players know there are something wrong.
         * E.g., mod loading error, corrupted save.
         */
        error,
        /**
         * Unrecoverable; Elona will stop to run.
         * E.g., failure of loading core files.
         */
        fatal,
    };


    // It is public, but DO NOT use this type directly!
    // To insert a line break at the end of each log, use RAII idiom.
    class _OneLineLogger
    {
    public:
        _OneLineLogger(
            std::ofstream& out,
            duration elapsed_time,
            const std::string& tag,
            Level level)
            : _out(out)
        {
            *this << elapsed_time.count() << " " << _to_string(level) << u8"["
                  << tag << u8"] ";
        }


        ~_OneLineLogger()
        {
            // Need to explicit the template parameters of `std::endl` here
            // because a compiler cannot infer `T` of the below template
            // function (`operator<<`). Normal output stream classes like
            // `std::basic_ostream` have overloads of `operator<<()` which take
            // manipulators so that we usually don't have to specify
            // `std::endl`'s template parameters.
            using StreamT = std::remove_reference_t<decltype(_out)>;
            using CharT = StreamT::char_type;
            using CharTraitsT = StreamT::traits_type;

            *this << std::endl<CharT, CharTraitsT>;
        }


        template <typename T>
        _OneLineLogger& operator<<(T&& value)
        {
            _out << value;

            return *this;
        }


    private:
        std::ofstream& _out;


        std::string _to_string(Logger::Level level)
        {
            switch (level)
            {
            case Logger::Level::log: return "INFO  ";
            case Logger::Level::warn: return "WARN  ";
            case Logger::Level::error: return "ERROR ";
            case Logger::Level::fatal: return "FATAL ";
            default: assert(0); return "";
            }
        }
    };



    /// Get the singleton instance.
    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }


    /// Initialize the logger with the default output file.
    void init();

    // It is public, but DO NOT call this function directly!
    _OneLineLogger _get_one_line_logger(const std::string& tag, Level level);



private:
    std::ofstream _out;
    std::chrono::steady_clock::time_point _start_time;

    Logger() = default;
};

} // namespace log
} // namespace elona



#define ELONA_LOG(tag) \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        tag, ::elona::log::Logger::Level::log)

#define ELONA_WARN(tag) \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        tag, ::elona::log::Logger::Level::warn)

#define ELONA_ERROR(tag) \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        tag, ::elona::log::Logger::Level::error)

#define ELONA_FATAL(tag) \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        tag, ::elona::log::Logger::Level::fatal)
