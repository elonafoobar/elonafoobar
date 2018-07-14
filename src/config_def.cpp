#include "config_def.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include "thirdparty/microhcl/hcl.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace elona
{

namespace
{

static void add_platform(config_def::metadata& dat, const hcl::Object& item)
{
    std::string platform = item.at("platform").as<std::string>();
    if (platform == "desktop")
    {
        dat.platform = config_def::option_platform::desktop;
    }
    else if (platform == "desktop")
    {
        dat.platform = config_def::option_platform::android;
    }
    else
    {
        dat.platform = config_def::option_platform::all;
    }
}

static void add_dependencies(config_def::metadata& dat, const hcl::Object item)
{
    auto dependencies = item.at("dependencies").as<hcl::Object>();
    for (auto& pair : dependencies)
    {
        std::string key = pair.first;
        bool value = pair.second.as<bool>();

        dat.dependencies[key] = value;
    }
}

}

void config_def::post_visit(const std::string& current_key, const spec::section_def&)
{
    data.emplace(current_key, metadata{});
}

void config_def::post_visit_bare_value(const std::string& current_key, const spec::item&)
{
    data.emplace(current_key, metadata{});
}

#define CONFIG_DEF_METADATA(name) \
    if (item.find(#name) != item.end()) \
    { \
        dat.name = item.at(#name).as<bool>(); \
    } \

void config_def::post_visit_item(const std::string& current_key, const hcl::Object& item)
{
    metadata dat{};

    CONFIG_DEF_METADATA(visible);
    CONFIG_DEF_METADATA(preload);
    CONFIG_DEF_METADATA(translate_variants);

    if (item.find("platform") != item.end())
    {
        add_platform(dat, item);
    }
    if (item.find("dependencies") != item.end())
    {
        add_dependencies(dat, item);
    }

    data.emplace(current_key, dat);
}

#undef CONFIG_DEF_METADATA

} // namespace elona
