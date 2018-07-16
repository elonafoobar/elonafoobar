#include "config_def.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include "hcl.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace elona
{

void config_def::post_visit(const std::string& current_key, const spec::section_def&)
{
    data.emplace(current_key, metadata{});
}

void config_def::post_visit_bare_value(const std::string& current_key, const spec::item&)
{
    data.emplace(current_key, metadata{});
}

void config_def::post_visit_item(const std::string& current_key, const hcl::Object& item)
{
    metadata dat{};

    if (item.find("visible") != item.end())
    {
        dat.visible = item.at("visible").as<bool>();
    }
    if (item.find("preload") != item.end())
    {
        dat.preload = item.at("preload").as<bool>();
    }
    if (item.find("translate_variants") != item.end())
    {
        dat.translate_variants = item.at("translate_variants").as<bool>();
    }

    data.emplace(current_key, dat);
}

} // namespace elona
