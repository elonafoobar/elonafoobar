#pragma once

#include "../thirdparty/ordered_map/ordered_map.h"

#define MICROHCL_MAP_TYPE tsl::ordered_map
#define MICROHCL_MAP_ACCESSOR &it.value()
#include "../thirdparty/microhcl/hcl.hpp"
#include "filesystem.hpp"

using namespace std::literals::string_literals;

namespace elona
{
namespace hclutil
{

inline hcl::Value& skip_sections(
    hcl::Value& object,
    const std::vector<std::string> section_names,
    const std::string& hcl_file)
{
    std::string sections;
    hcl::Value* value = &object;

    for (auto it = section_names.begin(); it < section_names.end(); it++)
    {
        std::string name = *it;

        if (sections == "")
        {
            sections = name;
        }
        else
        {
            sections += "." + name;
        }

        if (!value->is<hcl::Object>() || !value->has(name))
        {
            throw std::runtime_error(
                hcl_file + ": \"" + sections +
                "\" object not found at top level"s);
        }
        value = value->find(name);
    }

    return *value;
}

inline hcl::Value load(std::istream& is, const std::string& filename)
{
    hcl::ParseResult parseResult = hcl::parse(is, filename);

    if (!parseResult.valid())
    {
        throw std::runtime_error{parseResult.errorReason};
    }

    return parseResult.value;
}

inline hcl::Value load(std::istream& is)
{
    return load(is, "[input stream]");
}

inline hcl::Value load(const fs::path& filepath)
{
    std::ifstream in{filepath.native()};
    std::string filepath_string =
        filepathutil::make_preferred_path_in_utf8(filepath);

    if (!in)
    {
        throw std::runtime_error{"Failed to open " + filepath_string};
    }

    return load(in, filepath_string);
}


} // namespace hclutil
} // namespace elona
