#pragma once
#include <string>
#include "../../thirdparty/sol2/sol.hpp"

namespace elona
{
namespace fmp
{

sol::table get_tile_exporter(const std::string& type);

}

} // namespace elona
