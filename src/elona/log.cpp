#include "log.hpp"

#include <iomanip>

#include "filesystem.hpp"



namespace
{

constexpr int _max_log_files = 10;
constexpr const char* _log_file_extension = ".log";



// safe mkdir
void _mkdir(const fs::path& dir)
{
    if (!fs::exists(dir))
    {
        fs::create_directory(dir);
    }
}



// safe rm
void _rm(const fs::path file)
{
    if (fs::exists(file))
    {
        fs::remove(file);
    }
}



// safe mv
void _mv(const fs::path& src, const fs::path& dst)
{
    if (fs::exists(src) && !fs::exists(dst))
    {
        fs::rename(src, dst);
    }
}



// Returns {root_dir}/{nth}.log.
fs::path _get_log_filepath(const fs::path& root_dir, int nth = 0)
{
    const auto filename =
        filepathutil::u8path(std::to_string(nth) + _log_file_extension);
    return root_dir / filename;
}



void _rotate_log_files(const fs::path& root_dir)
{
    const auto oldest = _max_log_files - 1;
    _rm(_get_log_filepath(root_dir, oldest));

    for (int nth = oldest - 1; nth >= 0; --nth)
    {
        const auto src = _get_log_filepath(root_dir, nth);
        const auto dst = _get_log_filepath(root_dir, nth + 1);
        _mv(src, dst);
    }
}

} // namespace



namespace elona
{
namespace log
{

using namespace std::chrono;



void Logger::init()
{
    _start_time = steady_clock::now();

    const auto root_dir = filesystem::dirs::log();
    _mkdir(root_dir);
    _rotate_log_files(root_dir);

    _out.open(_get_log_filepath(root_dir).native());
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
