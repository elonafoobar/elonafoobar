#pragma once
#include "spec.hpp"
#include "hcl.hpp"

namespace elona
{

/***
 * Contains a layout of valid config options, to be used by the config
 * class for validating values set on it.
 */
class config_def : public spec::object
{
public:
    struct metadata
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
    };

    config_def() : spec::object("config")
    {
        locale_root = "core.locale.config.menu";
    }

    ~config_def() = default;

    void clear()
    {
        spec::object::clear();
        data.clear();
    }

    const metadata& get_metadata(const std::string& key) const { return data.at(key); }

    const std::string& get_locale_root() const { return locale_root; }

    void post_visit(const std::string&, const spec::section_def&);
    void post_visit_item(const std::string&, const hcl::Object&);
    void post_visit_bare_value(const std::string&, const spec::item&);

private:
    std::string locale_root;
    std::map<std::string, metadata> data;
};
}
