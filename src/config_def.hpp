#pragma once
#include "spec.hpp"
#include "thirdparty/microhcl/hcl.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include <cassert>
#include <vector>
#include <sstream>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

namespace elona
{

class config_def : public spec::object
{
public:
    struct config_def_item_data
    {
        bool visible = true;
        bool preload = false;
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

    bool is_preload(const std::string& key) const { return data.at(key).preload; }
    bool is_visible(const std::string& key) const { return data.at(key).visible; }

    const std::string& get_locale_root() const { return locale_root; }

    void post_visit_item(const std::string&, const hcl::Object&);
    void post_visit_bare_value(const std::string&, const spec::item&);

private:
    std::string locale_root;
    std::map<std::string, config_def_item_data> data;
};
}
