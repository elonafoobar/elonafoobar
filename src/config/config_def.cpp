#include "config_def.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "../defines.hpp"
#include "../filesystem.hpp"
#include "../hcl.hpp"
#include "../optional.hpp"
#include "../snail/application.hpp"

namespace elona
{

namespace
{


static void add_platform(ConfigDef::MetaData& dat, const hcl::Object& item)
{
    std::string platform = item.at("platform").as<std::string>();

    if (platform == "desktop")
    {
        dat.platform = ConfigDef::Platform::desktop;
    }
    else if (platform == "android")
    {
        dat.platform = ConfigDef::Platform::android;
    }
    else
    {
        dat.platform = ConfigDef::Platform::all;
    }
}

static void set_default_from_platform(
    ConfigDef::MetaData& dat,
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

void ConfigDef::post_visit(const SpecKey& current_key, const spec::SectionDef&)
{
    data.emplace(current_key, MetaData{});
}

void ConfigDef::pre_visit_section(
    const SpecKey& current_key,
    const hcl::Object& section)
{
    MetaData dat{};

    CONFIG_DEF_METADATA(section, visible);
    if (section.find("platform") != section.end())
    {
        add_platform(dat, section);
    }

    dat.visible = dat.visible && is_child_visible(current_key);

    data.emplace(current_key, dat);
}

void ConfigDef::pre_visit_bare_value(
    const SpecKey& current_key,
    const hcl::Value&)
{
    data.emplace(current_key, MetaData{});
}

void ConfigDef::pre_visit_item(
    const SpecKey& current_key,
    const hcl::Object& item)
{
    MetaData dat{};

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


bool ConfigDef::is_child_visible(const SpecKey& child_key)
{
    SpecKey parent_key = child_key;
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
