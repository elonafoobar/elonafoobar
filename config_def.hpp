#pragma once
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

class config_def_error : public std::exception
{
public:
    config_def_error(const std::string& key, std::string str)
        {
            std::ostringstream oss;
            oss << key << ": Config definition loading error: ";
            oss << str;
            what_ = oss.str();
        }
    config_def_error(const std::string& file, const std::string& key, std::string str)
        {
            std::ostringstream oss;
            oss << file << ": Config definition loading error at " << key << ": ";
            oss << str;
            what_ = oss.str();
        }

    const char* what() const noexcept {
        return what_.c_str();
    }
private:
    std::string what_;
};
class config_def
{
public:
    struct config_section_def
    {
        std::vector<std::string> children;
    };

    struct config_bool_def
    {
        bool default_value = true;
    };

    struct config_int_def
    {
        int default_value = 0;
        int min = 0;
        int max = 0;
    };

    struct config_string_def
    {
        std::string default_value = "";
    };

    struct config_list_def
    {
        std::vector<hcl::Value> default_value;
    };

    struct config_enum_def
    {
        int default_index;
        std::vector<std::string> variants;
        bool pending = false;

        std::string to_string() const
        {
            std::stringstream ss;
            ss << "[";
            for (auto it = variants.begin(); it != variants.end(); ++it)
            {
                ss << *it;
                if (it != std::prev(variants.end()))
                {
                    ss << ", ";
                }
            }
            ss << "]";
            return ss.str();
        }
    };

    struct config_def_item_data
    {
        bool visible = true;
        bool preload = false;
        std::string doc = "";
    };

    typedef boost::variant<config_section_def,
                           config_bool_def,
                           config_int_def,
                           config_string_def,
                           config_list_def,
                           config_enum_def> item;

    typedef std::map<std::string, item>::const_iterator const_iterator;

    config_def()
    {
        locale_root = "core.locale.config.menu";
    }

    ~config_def() = default;

    void init(const fs::path&);
    void load(std::istream&, const std::string&);

    const_iterator begin() const { return items.begin(); }
    const_iterator end() const { return items.end(); }

    void clear()
    {
        items.clear();
        data.clear();
    }

    bool exists(const std::string& key) const
    {
        return items.find(key) != items.end()
            && data.find(key) != data.end();
    };

    void inject_enum(const std::string& key, std::vector<std::string> variants, int default_index)
    {
        if(!exists(key) || !is<config_enum_def>(key))
        {
            throw config_def_error(key, "No such enum " + key);
        }

        auto& def = get<config_enum_def>(key);
        def.variants = std::move(variants);
        def.default_index = default_index;
        def.pending = false;
    }

    template <typename T>
    bool is(const std::string& key) const { return exists(key) && items.at(key).type() == typeid(T); };

    template <typename T>
    T& get(const std::string& key) { return boost::get<T>(items.at(key)); }

    template <typename T>
    const T& get(const std::string& key) const { return boost::get<T>(items.at(key)); }

    bool is_visible(const std::string& key) const { return data.at(key).visible; }
    bool is_preload(const std::string& key) const { return data.at(key).preload; }
    bool is_valid_enum_variant(const std::string& key, int index)
    {
        if(!is<config_enum_def>(key))
        {
            return false;
        }
        auto variants = get<config_enum_def>(key).variants;
        return index >= 0 && index < static_cast<int>(variants.size());
    }

    inline std::string type_to_string(const std::string& key)
    {
        if (is<config_section_def>(key))
        {
            return "section";
        }
        else if (is<config_int_def>(key))
        {
            return "integer";
        }
        else if (is<config_bool_def>(key))
        {
            return "boolean";
        }
        else if (is<config_string_def>(key))
        {
            return "string";
        }
        else if (is<config_list_def>(key))
        {
            return "list of strings";
        }
        else if (is<config_enum_def>(key))
        {
            return "enum variant: " + get<config_enum_def>(key).to_string();
        }
        else
        {
            return "unknown";
        }
    }

    hcl::Value get_default(const std::string& key)
    {
        if (is<config_section_def>(key))
        {
            throw config_def_error(key, "Sections cannot have default values.");
        }
        else if (is<config_int_def>(key))
        {
            return get<config_int_def>(key).default_value;
        }
        else if (is<config_bool_def>(key))
        {
            return get<config_bool_def>(key).default_value;
        }
        else if (is<config_string_def>(key))
        {
            return get<config_string_def>(key).default_value;
        }
        else if (is<config_list_def>(key))
        {
            return get<config_list_def>(key).default_value;
        }
        else
        {
            return get<config_enum_def>(key).default_index;
        }
    }

    std::vector<std::string> get_children(const std::string& key) const
    {
        if (!is<config_section_def>(key))
        {
            throw config_def_error(key, "Cannot get children for non-section " + key);
        }
        return get<config_section_def>(key).children;
    }

    std::vector<std::string> get_variants(const std::string& key) const
    {
        if (!is<config_enum_def>(key))
        {
            throw config_def_error(key, "Cannot get variants for non-enum " + key);
        }
        return get<config_enum_def>(key).variants;
    }

    int get_max(const std::string& key)
    {
        if (is<config_enum_def>(key))
        {
            return static_cast<int>(get<config_enum_def>(key).variants.size() - 1);
        }
        if (!is<config_int_def>(key))
        {
            throw config_def_error(key, "Cannot get max value for non-integer option " + key);
        }
        return get<config_int_def>(key).max;
    }

    int get_min(const std::string& key)
    {
        if (is<config_enum_def>(key))
        {
            return 0;
        }
        if (!is<config_int_def>(key))
        {
            throw config_def_error(key, "Cannot get min value for non-integer option " + key);
        }
        return get<config_int_def>(key).min;
    }

    optional<std::string> get_doc(const std::string& key)
    {
        if (data.find(key) == data.end())
        {
            return none;
        }
        return data[key].doc;
    }

    const std::string& get_locale_root() const { return locale_root; }

private:
    void visit(const hcl::Value&, const std::string&, const std::string&);
    config_section_def visit_object(const hcl::Object&, const std::string&, const std::string&);

    void visit_item(const hcl::Object&, const std::string&, const std::string&);
    item visit_bare_value(const hcl::Value&, const std::string&, const std::string&);
    config_section_def visit_section(const hcl::Object&, const std::string&, const std::string&);
    config_int_def visit_int(int, const hcl::Object&, const std::string&, const std::string&);
    config_bool_def visit_bool(bool);
    config_string_def visit_string(const std::string&);
    config_list_def visit_list(const hcl::List&);
    config_enum_def visit_enum(const std::string&,
                               const hcl::Object&,
                               const std::string&,
                               const std::string&);

    std::string locale_root;
    std::map<std::string, item> items;
    std::map<std::string, config_def_item_data> data;
};
}
