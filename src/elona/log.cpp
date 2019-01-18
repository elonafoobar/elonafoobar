#include "log.hpp"
#include "filesystem.hpp"


namespace elona
{
namespace log
{

void Logger::init()
{
    init(std::ofstream((filesystem::dir::exe() / u8"log.txt").native()));
}



void Logger::init(std::ofstream&& out)
{
    _out = std::move(out);
}



Logger::_OneLineLogger Logger::_get_one_line_logger()
{
    return {_out};
}

} // namespace log
} // namespace elona
