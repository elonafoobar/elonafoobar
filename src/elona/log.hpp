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
    // It is public, but DO NOT use this type directly!
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
    _OneLineLogger _get_one_line_logger();


private:
    std::ofstream _out;

    Logger() = default;
};

} // namespace log
} // namespace elona



#define ELONA_LOG(x) ::elona::log::Logger::instance()._get_one_line_logger()
