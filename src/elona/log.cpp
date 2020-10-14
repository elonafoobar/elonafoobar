#include "log.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>



namespace elona::log
{

namespace
{

constexpr int max_log_files = 10;
constexpr const char* log_file_extension = ".log";



LogLevel _current_log_level;
std::chrono::steady_clock::time_point _start_time;
std::ofstream _out;
bool _output_stderr;



void safe_mkdir(const fs::path dir)
{
    if (!fs::exists(dir))
    {
        fs::create_directory(dir);
    }
}



void safe_rm(const fs::path file)
{
    if (fs::exists(file))
    {
        fs::remove(file);
    }
}



void safe_mv(const fs::path& src, const fs::path& dst)
{
    if (fs::exists(src) && !fs::exists(dst))
    {
        fs::rename(src, dst);
    }
}



// Returns {root_dir}/{nth}.log.
fs::path get_log_file_path(const fs::path& root_dir, int nth)
{
    const auto filename = fs::u8path(std::to_string(nth) + log_file_extension);
    return root_dir / filename;
}



void rotate_log_files(const fs::path& root_dir)
{
    const auto oldest = max_log_files - 1;
    safe_rm(get_log_file_path(root_dir, oldest));

    for (int nth = oldest - 1; nth >= 0; --nth)
    {
        const auto src = get_log_file_path(root_dir, nth);
        const auto dst = get_log_file_path(root_dir, nth + 1);
        safe_mv(src, dst);
    }
}



void setup_file_stream(const fs::path& root_dir)
{
    // Open the file.
    const auto log_file_path = get_log_file_path(root_dir, 0);
    _out.open(log_file_path.native());
    if (!_out)
    {
        throw std::runtime_error{
            "failed to open log file: " + log_file_path.to_u8string()};
    }

    // Set floating point number's precision.
    _out << std::fixed << std::setprecision(3);
}



auto now()
{
    return std::chrono::steady_clock::now();
}



double time_stamp()
{
    using namespace std::chrono;

    const auto elapsed_time =
        duration_cast<duration<double>>(now() - _start_time);
    return elapsed_time.count();
}



const char* to_string(LogLevel level)
{
    switch (level)
    {
    case LogLevel::error: return "ERROR ";
    case LogLevel::warn: return "WARN  ";
    case LogLevel::info: return "INFO  ";
    case LogLevel::debug: return "DEBUG ";
    case LogLevel::trace: return "TRACE ";
    default: assert(0); return "";
    }
}



// To string with ANSI escape sequence
const char* to_string_with_coloring(LogLevel level)
{
    switch (level)
    {
    case LogLevel::error: return "\e[31mERROR\e[m ";
    case LogLevel::warn: return "\e[33mWARN\e[m  ";
    case LogLevel::info: return "INFO  ";
    case LogLevel::debug: return "DEBUG ";
    case LogLevel::trace: return "TRACE ";
    default: assert(0); return "";
    }
}

} // namespace



void init(const fs::path& log_dir, LogLevel initial_level)
{
    _current_log_level = initial_level;
    _start_time = now();
#if defined(DEBUG) || defined(_DEBUG)
    _output_stderr = true;
#else
    _output_stderr = false;
#endif

    safe_mkdir(log_dir);
    rotate_log_files(log_dir);
    setup_file_stream(log_dir);
}



void log(
    LogLevel level,
    const std::string& mod_name,
    const std::string& message)
{
    if (level < _current_log_level) // is trivial
        return;

    _out << time_stamp() << " " << to_string(level) << "[" << mod_name << "] "
         << message << std::endl;
    if (_output_stderr)
    {
        std::cerr << time_stamp() << " " << to_string_with_coloring(level)
                  << "[" << mod_name << "] " << message << std::endl;
    }
}



LogLevel level()
{
    return _current_log_level;
}



void set_level(LogLevel new_level)
{
    _current_log_level = new_level;
}



void output_stderr(bool should_output)
{
    _output_stderr = should_output;
}

} // namespace elona::log
