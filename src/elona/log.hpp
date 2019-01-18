#pragma once

#include <fstream>
#include <iostream>
#include "../util/noncopyable.hpp"



namespace elona
{
namespace log
{

class Logger : lib::noncopyable
{
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
        _OneLineLogger(std::ofstream& out, bool output_stdout)
            : _out(out)
        {
        }


        ~_OneLineLogger()
        {
            _out << std::endl;
        }


        template <typename T>
        _OneLineLogger& operator<<(T&& value)
        {
            _out << value;

            return *this;
        }


    private:
        std::ofstream& _out;
    };



    static Logger& instance()
    {
        static Logger instance;
        return instance;
    }


    /// Initialize the logger with the default output file.
    void init();

    /// Initialize the logger with the passed output file.
    void init(std::ofstream&& out);

    // It is public, but DO NOT call this function directly!
    _OneLineLogger _get_one_line_logger(Level level);



private:
    std::ofstream _out;

    Logger() = default;
};

} // namespace log
} // namespace elona



#define ELONA_LOG() \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        ::elona::log::Logger::Level::log)

#define ELONA_WARN() \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        ::elona::log::Logger::Level::warn)

#define ELONA_ERROR() \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        ::elona::log::Logger::Level::error)

#define ELONA_FATAL() \
    ::elona::log::Logger::instance()._get_one_line_logger( \
        ::elona::log::Logger::Level::fatal)
