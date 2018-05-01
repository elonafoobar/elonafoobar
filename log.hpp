#pragma once

#include <fstream>

#define ELONA_LOG(msg) elona::log::detail::out << msg << std::endl;


namespace elona
{
namespace log
{

namespace detail
{
extern std::ofstream out;
}

void initialize();

} // namespace log
} // namespace elona
