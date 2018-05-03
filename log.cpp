#include "log.hpp"
#include "filesystem.hpp"


namespace elona
{
namespace log
{

namespace detail
{
std::ofstream out;
}



void initialize()
{
    detail::out.open((filesystem::dir::exe() / u8"log.txt").native());
}


} // namespace log
} // namespace elona
