#pragma once

#define MICROHCL_MAP_TYPE tsl::ordered_map
#define MICROHCL_MAP_ACCESSOR &it.value()
#include "thirdparty/ordered_map/ordered_map.h"
#include "thirdparty/microhcl/hcl.hpp"

#include "filesystem.hpp"

namespace elona
{
namespace hclutil
{

inline hcl::Value load(std::istream& is)
{
    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid()) {
        throw std::runtime_error{parseResult.errorReason};
    }

    return parseResult.value;
}

inline hcl::Value load(const fs::path& filepath) {
    std::ifstream in{filepath.native()};

    if (!in)
    {
        throw std::runtime_error{
            "Failed to open "
            + filesystem::make_preferred_path_in_utf8(filepath)};
    }

    return load(in);
}


} // namespace hclutil
} // namespace elona
