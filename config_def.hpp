#pragma once
#include "thirdparty/microhcl/hcl.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include <cassert>
#include <set>
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
    };

    struct config_bool_def
    {
        bool default_value = true;
    };

    struct config_int_def
    {
        int default_value = 0;
        optional<int> min = none;
        optional<int> max = none;
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
        std::string default_value;
        std::set<std::string> variants;

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

    config_def() {};
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

    bool exists(const std::string& key)
    {
        return items.find(key) != items.end()
            && data.find(key) != data.end();
    };

    template <typename T>
    bool is(const std::string& key) { return items.at(key).type() == typeid(T); };

    template <typename T>
    const T& get(const std::string& key){ return boost::get<T>(items.at(key)); }

    bool is_visible(const std::string& key) { return data.at(key).visible; }
    bool is_preload(const std::string& key) { return data.at(key).preload; }
    bool is_valid_enum_variant(const std::string& key, const std::string& variant)
    {
        if(!is<config_enum_def>(key))
        {
            return false;
        }
        auto variants = get<config_enum_def>(key).variants;
        return variants.find(variant) != variants.end();
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
            const config_enum_def& enum_def = get<config_enum_def>(key);
            if (!is_valid_enum_variant(key, enum_def.default_value))
            {
                throw new config_def_error(key, "Default enum value " + enum_def.default_value +
                                            " not included in valid enum variants.");
            }
            return enum_def.default_value;
        }
    }

    optional<int> get_max(const std::string& key)
    {
        if (!is<config_int_def>(key))
        {
            throw config_def_error(key, "Cannot get max value for non-integer option " + key);
        }
        return get<config_int_def>(key).max;
    }

    optional<int> get_min(const std::string& key)
    {
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

private:
    void visit(const hcl::Value&, const std::string&, const std::string&);
    void visit_object(const hcl::Object&, const std::string&, const std::string&);

    void visit_item(const hcl::Object&, const std::string&, const std::string&);
    item visit_bare_value(const hcl::Value&, const std::string&, const std::string&);
    config_section_def visit_section(const hcl::Object&, const std::string&, const std::string&);
    config_int_def visit_int(int, const hcl::Object&);
    config_bool_def visit_bool(bool);
    config_string_def visit_string(const std::string&);
    config_list_def visit_list(const hcl::List&);
    config_enum_def visit_enum(const std::string&,
                               const hcl::Object&,
                               const std::string&,
                               const std::string&);

    std::map<std::string, item> items;
    std::map<std::string, config_def_item_data> data;
};
}
