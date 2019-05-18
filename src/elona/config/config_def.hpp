#pragma once
#include "../defines.hpp"
#include "../hcl.hpp"
#include "../spec.hpp"

#include <iostream>

namespace elona
{

/***
 * Contains a layout of valid config options, to be used by the config
 * class for validating values set on it.
 */
class ConfigDef : public spec::Object
{
public:
    enum class Platform
    {
        all,
        desktop,
        android,
    };

    struct MetaData
    {
        // True if the config section/option is visible in the options menu.
        bool visible = true;

        // True if the config option is loaded before application is
        // initialized (screen size, language...)
        bool preload = false;

        // True if runtime enum variants should cause errors on
        // missing translations. Set to false when enum variants are
        // human-readable themselves.
        bool translate_variants = true;

        // Platform this option applies to. On other platforms it will
        // be hidden.
        Platform platform = Platform::all;

        // Overridden default value from platform_default field if the
        // specified platform matches ("android" or "desktop").
        optional<hcl::Value> default_value = none;

        bool is_visible() const
        {
            switch (platform)
            {
            case Platform::desktop: return visible && !defines::is_android;
            case Platform::android: return visible && defines::is_android;
            case Platform::all:
            default: return visible;
            }
        }
    };

    ConfigDef()
        : spec::Object("config")
    {
    }

    ~ConfigDef() = default;

    void clear()
    {
        spec::Object::clear();
        data.clear();
    }

    hcl::Value get_default(const std::string& key) const
    {
        if (data.find(key) != data.end())
        {
            auto value = data.at(key).default_value;
            if (value)
            {
                return *value;
            }
        }

        return spec::Object::get_default(key);
    }

    const MetaData& get_metadata(const SpecKey& key) const
    {
        return data.at(key);
    }

    void post_visit(const SpecKey&, const spec::SectionDef&);
    void pre_visit_section(const SpecKey&, const hcl::Object&);
    void pre_visit_item(const SpecKey&, const hcl::Object&);
    void pre_visit_bare_value(const SpecKey&, const hcl::Value&);

private:
    /***
     * Gets the visibility of a config item considering the visibility
     * of its parent sections. This is needed for determining whether
     * or not to save certain items based on visibility.
     */
    bool is_child_visible(const SpecKey&);

    std::map<std::string, MetaData> data;
};
} // namespace elona
