#include "config_def.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "defines.hpp"
#include "filesystem.hpp"
#include "hcl.hpp"
#include "optional.hpp"
#include "snail/application.hpp"

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
    else if (platform == "android")
    {
        dat.platform = config_def::option_platform::android;
    }
    else
    {
        dat.platform = config_def::option_platform::all;
    }
}

static void set_default_from_platform(
    config_def::metadata& dat,
    const hcl::Object& item)
{
    // NOTE: Could be generalized, if it were neeed.
    const constexpr char* platform =
        defines::is_android ? "android" : "desktop";
    auto platform_default = item.at("platform_default");

    hcl::Value* value = platform_default.find(platform);
    if (value)
    {
        dat.default_value = *value;
    }
}

} // namespace

#define CONFIG_DEF_METADATA(item, name) \
    if (item.find(#name) != item.end()) \
    { \
        dat.name = item.at(#name).as<bool>(); \
    }

void config_def::post_visit(
    const spec_key& current_key,
    const spec::section_def&)
{
    data.emplace(current_key, metadata{});
}

void config_def::pre_visit_section(
    const spec_key& current_key,
    const hcl::Object& section)
{
    metadata dat{};

    CONFIG_DEF_METADATA(section, visible);
    if (section.find("platform") != section.end())
    {
        add_platform(dat, section);
    }

    dat.visible = dat.visible && is_child_visible(current_key);

    data.emplace(current_key, dat);
}

void config_def::pre_visit_bare_value(
    const spec_key& current_key,
    const hcl::Value&)
{
    data.emplace(current_key, metadata{});
}

void config_def::pre_visit_item(
    const spec_key& current_key,
    const hcl::Object& item)
{
    metadata dat{};

    CONFIG_DEF_METADATA(item, visible);
    CONFIG_DEF_METADATA(item, preload);
    CONFIG_DEF_METADATA(item, translate_variants);

    if (item.find("platform") != item.end())
    {
        add_platform(dat, item);
    }
    if (item.find("platform_default") != item.end())
    {
        set_default_from_platform(dat, item);
    }

    dat.visible = dat.visible && is_child_visible(current_key);

    data.emplace(current_key, dat);
}


bool config_def::is_child_visible(const spec_key& child_key)
{
    spec_key parent_key = child_key;
    for (size_t i = parent_key.size() - 1; i > 0; i--)
    {
        if (parent_key[i] == '.')
        {
            // Break string at furthest period.
            parent_key = parent_key.substr(0, i);

            if (data.find(parent_key) == data.end())
            {
                continue;
            }
            else if (!data.at(parent_key).is_visible())
            {
                return false;
            }
        }
    }

    return true;
}

#undef CONFIG_DEF_METADATA

} // namespace elona
