#pragma once
#include "hcl.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include <cassert>
#include <map>
#include <sstream>
#include <vector>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include "thirdparty/ordered_map/ordered_map.h"

using namespace std::literals::string_literals;

namespace elona
{

class spec_error : public std::exception
{
public:
    spec_error(const std::string& key, std::string str)
        {
            std::ostringstream oss;
            oss << key << ": Config definition loading error: ";
            oss << str;
            what_ = oss.str();
        }
    spec_error(const std::string& file, const std::string& key, std::string str)
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


typedef std::string spec_key;


namespace spec
{

// Valid types a spec can have.

struct section_def
{
    std::vector<std::string> children;
};

struct bool_def
{
    bool default_value = true;
};

struct int_def
{
    int default_value = 0;
    int min = 0;
    int max = 0;
};

struct string_def
{
    std::string default_value = "";
};

struct list_def
{
    std::vector<hcl::Value> default_value;
};

struct enum_def
{
    int default_index;
    std::vector<std::string> variants;
    bool pending = false;

    std::string to_string() const
    {
        std::ostringstream ss;
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

    /***
     * Given a string, return its index in the enum's variants, if
     * found.
     */
    optional<int> get_index_of(std::string variant) const
    {
        auto it = std::find(variants.begin(), variants.end(), variant);
        if (it == variants.end())
            return none;

        return std::distance(variants.begin(), it);
    }

    std::string get_default() const
    {
        return variants.at(default_index);
    }
};

typedef boost::variant<section_def,
                       bool_def,
                       int_def,
                       string_def,
                       list_def,
                       enum_def> item;

static const constexpr char* unknown_enum_variant = "__unknown__";


/***
 * A schema-like object that holds a definition of valid values for an
 * HCL document. Used for validating the correctness of user-inputted
 * HCL files. For an example, see runtime/mods/core/config/config_def.hcl.
 */
class object
{
public:
    typedef tsl::ordered_map<std::string, item>::const_iterator const_iterator;

    object(std::string name_) : name(name_) {}
    ~object() = default;

    void init(const fs::path&);
    void load(std::istream&, const std::string&);

    const_iterator begin() const { return items.begin(); }
    const_iterator end() const { return items.end(); }
    virtual void clear() { items.clear(); }

    bool exists(const std::string& key) const
    {
        return items.find(key) != items.end();
    };

    /***
     * Adds values to an enum declared with type "runtime_enum".
     *
     * In some cases, it won't be possible to validate certain HCL
     * values with a list of variants because those variants are not
     * known until runtime. Some examples are screen resolution and
     * available languages.
     */
    void inject_enum(const std::string& key, std::vector<std::string> variants, std::string default_variant)
    {
        if (!exists(key) || !is<enum_def>(key))
        {
            throw spec_error(key, "No such enum " + key);
        }
        if (!get<enum_def>(key).pending)
        {
            throw spec_error(key, "Attempted to inject an enum, but it was not of type runtime_enum: " + key);
        }


        auto& def = get<enum_def>(key);
        def.variants = std::move(variants);
        def.variants.insert(def.variants.begin(), unknown_enum_variant);

        // The default variant provided must be contained in the list
        // of provided variants.
        optional<int> index = def.get_index_of(default_variant);
        if (!index)
        {
            def.variants = std::vector<std::string>();
            throw spec_error(key, "Default variant \"" + default_variant + "\" not found: " + key);
        }

        def.default_index = *index;
        def.pending = false;
    }

    template <typename T>
    bool is(const std::string& key) const { return exists(key) && items.at(key).type() == typeid(T); };

    template <typename T>
    T& get(const std::string& key) { return boost::get<T>(items.at(key)); }

    template <typename T>
    const T& get(const std::string& key) const { return boost::get<T>(items.at(key)); }

    inline std::string type_to_string(const std::string& key) const
    {
        if (is<section_def>(key))
        {
            return "section";
        }
        else if (is<int_def>(key))
        {
            return "integer";
        }
        else if (is<bool_def>(key))
        {
            return "boolean";
        }
        else if (is<string_def>(key))
        {
            return "string";
        }
        else if (is<list_def>(key))
        {
            return "list of strings";
        }
        else if (is<enum_def>(key))
        {
            return "enum variant: " + get<enum_def>(key).to_string();
        }
        else
        {
            return "unknown";
        }
    }

    virtual hcl::Value get_default(const std::string& key) const
    {
        if (is<section_def>(key))
        {
            throw spec_error(key, "Sections cannot have default values.");
        }
        else if (is<int_def>(key))
        {
            return get<int_def>(key).default_value;
        }
        else if (is<bool_def>(key))
        {
            return get<bool_def>(key).default_value;
        }
        else if (is<string_def>(key))
        {
            return get<string_def>(key).default_value;
        }
        else if (is<list_def>(key))
        {
            return get<list_def>(key).default_value;
        }
        else
        {
            return get<enum_def>(key).get_default();
        }
    }

    /***
     * Gets the children of a section. Only useable on section values.
     */
    std::vector<std::string> get_children(const std::string& key) const
    {
        if (!is<section_def>(key))
        {
            throw spec_error(key, "Cannot get children for non-section " + key);
        }
        return get<section_def>(key).children;
    }

    /***
     * Gets the variants of an enum. Only useable on enum values.
     */
    std::vector<std::string> get_variants(const std::string& key) const
    {
        if (!is<enum_def>(key))
        {
            throw spec_error(key, "Cannot get variants for non-enum " + key);
        }
        return get<enum_def>(key).variants;
    }

    /***
     * Gets the maximum value/index of an integer or enum.
     */
    int get_max(const std::string& key) const
    {
        if (is<enum_def>(key))
        {
            return static_cast<int>(get<enum_def>(key).variants.size() - 1);
        }
        if (!is<int_def>(key))
        {
            throw spec_error(key, "Cannot get max value for non-integer option " + key);
        }
        return get<int_def>(key).max;
    }

    /***
     * Gets the minumum value/index of an integer or enum.
     */
    int get_min(const std::string& key) const
    {
        if (is<enum_def>(key))
        {
            return 0;
        }
        if (!is<int_def>(key))
        {
            throw spec_error(key, "Cannot get min value for non-integer option " + key);
        }
        return get<int_def>(key).min;
    }

    // These functions allow for injecting more specific validations
    // or data in subclasses, like config option visibility based on
    // object properties.
    virtual void post_visit(const spec_key&, const section_def&) {}
    virtual void pre_visit_section(const spec_key&, const hcl::Object&) {}
    virtual void pre_visit_item(const spec_key&, const hcl::Object&) {}
    virtual void pre_visit_bare_value(const spec_key&, const hcl::Value&) {}

private:
    // Visitor methods for general object types
    section_def visit_object(const hcl::Object&, const std::string&, const std::string&);
    void visit(const hcl::Value&, const std::string&, const std::string&);
    item visit_bare_value(const hcl::Value&, const std::string&, const std::string&);
    void visit_item(const hcl::Object&, const std::string&, const std::string&);

    // Visitor methods for specific object types
    section_def visit_section(const hcl::Object&, const std::string&, const std::string&);
    int_def visit_int(int, const hcl::Object&, const std::string&, const std::string&);
    bool_def visit_bool(bool);
    string_def visit_string(const std::string&);
    list_def visit_list(const hcl::List&);
    enum_def visit_enum(const std::string&, const hcl::Object&, const std::string&, const std::string&);

    std::string name;
    tsl::ordered_map<std::string, item> items;
};
}
}
