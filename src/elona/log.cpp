#include "log.hpp"
#include <iomanip>
#include "filesystem.hpp"



namespace elona
{
namespace log
{

using namespace std::chrono;



void Logger::init()
{
    init(std::ofstream((filesystem::dir::exe() / u8"log.txt").native()));
}



void Logger::init(std::ofstream&& out)
{
    _start_time = steady_clock::now();
    _out = std::move(out);
    _out << std::fixed << std::setprecision(3);
}



Logger::_OneLineLogger Logger::_get_one_line_logger(
    const std::string& tag,
    Level level)
{
    const auto now = steady_clock::now();
    const auto elapsed_time = duration_cast<duration>(now - _start_time);
    return {_out, elapsed_time, tag, level};
}

} // namespace log
} // namespace elona
