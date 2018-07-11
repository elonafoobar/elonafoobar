#pragma once
#include "thirdparty/microhcl/hcl.hpp"
#include "filesystem.hpp"
#include "optional.hpp"
#include <cassert>
#include <vector>
#include <sstream>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

using namespace std::literals::string_literals;

namespace elona
{
namespace spec
{

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

typedef boost::variant<section_def,
                       bool_def,
                       int_def,
                       string_def,
                       list_def,
                       enum_def> item;

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

class object
{
public:
    typedef std::map<std::string, item>::const_iterator const_iterator;

    object(std::string name_) : name(name_) {}
    ~object() = default;

    void init(const fs::path& path)
    {
        clear();

        // TODO support loading multiple files.
        std::ifstream ifs(filesystem::make_preferred_path_in_utf8(path));
        load(ifs, path.string());
    }


    void load(std::istream& is, const std::string& hcl_file)
        {
            hcl::ParseResult parseResult = hcl::parse(is);

            if (!parseResult.valid()) {
                std::cerr << parseResult.errorReason << std::endl;
                throw spec_error(hcl_file, u8"Failed to read " + hcl_file + u8": "
                                 + parseResult.errorReason);
            }

            const hcl::Value& value = parseResult.value;

            if (!value.is<hcl::Object>() || !value.has(name))
            {
                throw spec_error(hcl_file, std::string(name) + " object not found at top level"s);
            }

            const hcl::Value val = value[name];

            auto def = visit_object(val.as<hcl::Object>(), "core."s + std::string(name), hcl_file);
        }


    const_iterator begin() const { return items.begin(); }
    const_iterator end() const { return items.end(); }
    virtual void clear() { items.clear(); }

    bool exists(const std::string& key) const
    {
        return items.find(key) != items.end();
    };

    void inject_enum(const std::string& key, std::vector<std::string> variants, int default_index)
    {
        if (!exists(key) || !is<enum_def>(key))
        {
            throw spec_error(key, "No such enum " + key);
        }
        if (!get<enum_def>(key).pending)
        {
            throw spec_error(key, "Attempted to inject an enum, but it was not of type runtime_enum: " + key);
        }
        if (default_index < 0 || default_index >= static_cast<int>(variants.size()))
        {
            throw spec_error(key, "Default index is out of bounds: " + key);
        }

        auto& def = get<enum_def>(key);
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

    bool is_valid_enum_variant(const std::string& key, std::string variant)
        {
            if(!is<enum_def>(key))
            {
                return false;
            }
            auto variants = get<enum_def>(key).variants;
            return std::find(variants.begin(), variants.end(), variant) != variants.end();
        }

    inline std::string type_to_string(const std::string& key)
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

    hcl::Value get_default(const std::string& key)
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
                auto def = get<enum_def>(key);
                return def.variants.at(def.default_index);
            }
        }

    std::vector<std::string> get_children(const std::string& key) const
        {
            if (!is<section_def>(key))
            {
                throw spec_error(key, "Cannot get children for non-section " + key);
            }
            return get<section_def>(key).children;
        }

    std::vector<std::string> get_variants(const std::string& key) const
        {
            if (!is<enum_def>(key))
            {
                throw spec_error(key, "Cannot get variants for non-enum " + key);
            }
            return get<enum_def>(key).variants;
        }

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

    const std::string& get_locale_root() const { return locale_root; }

    virtual void post_visit_item(const std::string&, const hcl::Object&) {}
    virtual void post_visit_bare_value(const std::string&, const item&) {}

private:
    section_def visit_object(const hcl::Object& object,
                            const std::string& current_key,
                            const std::string& hcl_file)
    {
        section_def def{};

        for (const auto& pair : object)
        {
            std::string key = current_key + "." + pair.first;
            visit(pair.second, key, hcl_file);
            def.children.emplace_back(pair.first);
        }

        return def;
    }

    void visit(const hcl::Value& value,
                        const std::string& current_key,
                        const std::string& hcl_file)
    {
        if (value.is<hcl::Object>())
        {
            visit_item(value.as<hcl::Object>(), current_key, hcl_file);
        }
        else
        {
            item i = visit_bare_value(value, current_key, hcl_file);
            post_visit_bare_value(current_key, i);
            items.emplace(current_key, i);
        }
    }

    item visit_bare_value(const hcl::Value& default_value,
                        const std::string& current_key,
                        const std::string& hcl_file)
    {
        item i;
        if (default_value.is<bool>())
        {
            i = visit_bool(default_value.as<bool>());
        }
        else if (default_value.is<std::string>())
        {
            i = visit_string(default_value.as<std::string>());
        }
        else if (default_value.is<hcl::List>())
        {
            i = visit_list(default_value.as<hcl::List>());
        }
        else
        {
            throw spec_error(hcl_file, current_key, "Invalid default value.");
        }

        return i;
    }

    void visit_item(const hcl::Object& item,
                                const std::string& current_key,
                                const std::string& hcl_file)
    {
        optional<spec::item> i;

        if (item.find("type") != item.end())
        {
            std::string type = item.at("type").as<std::string>();
            if (type == "section")
            {
                i = visit_section(item, current_key, hcl_file);
            }
            else if (type == "enum")
            {
                if (item.find("default") == item.end())
                {
                    throw spec_error(hcl_file, current_key, "No default enum value provided.");
                }
                i = visit_enum(item.at("default").as<std::string>(), item, current_key, hcl_file);
            }
            else if (type == "runtime_enum")
            {
                i = enum_def{0, {}, true};
            }
            else
            {
                throw spec_error(hcl_file, current_key, "Invalid type " + type + ".");
            }
        }
        else
        {
            if (item.find("default") == item.end())
            {
                throw spec_error(hcl_file, current_key, "No default value provided.");
            }

            auto default_value = item.at("default");
            if (default_value.is<int>())
            {
                i = visit_int(default_value.as<int>(), item, current_key, hcl_file);
            }
            else
            {
                i = visit_bare_value(default_value, current_key, hcl_file);
            }
        }

        if (!i)
        {
            throw spec_error(hcl_file, current_key, "Could not parse value.");
        }

        post_visit_item(current_key, item);
        items.emplace(current_key, *i);
    }

    section_def visit_section(const hcl::Object& section,
                    const std::string& current_key,
                    const std::string& hcl_file)
    {
        if (section.find("options") == section.end())
        {
            throw spec_error(hcl_file, current_key, "Section has no field named \"options\".");
        }
        const hcl::Object& options = section.at("options").as<hcl::Object>();
        return visit_object(options, current_key, hcl_file);
    }

    int_def visit_int(int default_value,
                                                    const hcl::Object& item,
                                                    const std::string& current_key,
                                                    const std::string& hcl_file)
    {
        int_def def;

        if (item.find("min") == item.end())
        {
            throw spec_error(hcl_file, current_key, "Integer option has no \"min\" field.");
        }
        if (item.find("max") == item.end())
        {
            throw spec_error(hcl_file, current_key, "Integer option has no \"max\" field.");
        }

        def.min = item.at("min").as<int>();
        def.max = item.at("max").as<int>();
        def.default_value = default_value;

        return def;
    }

    bool_def visit_bool(bool default_value)
    {
        return bool_def{default_value};
    }

    string_def visit_string(const std::string& default_value)
    {
        return string_def{default_value};
    }

    list_def visit_list(const hcl::List& default_value)
    {
        return list_def{default_value};
    }

    enum_def visit_enum(const std::string& default_value,
                            const hcl::Object& item,
                            const std::string& current_key,
                            const std::string& hcl_file)
    {
        enum_def def{};
        if (item.find("variants") == item.end())
        {
            throw spec_error(hcl_file, current_key, "No enum variants provided.");
        }

        hcl::List hcl_variants = item.at("variants").as<hcl::List>();
        std::vector<std::string> variants;
        int default_index = -1;
        int i = 0;
        for (auto& item : hcl_variants)
        {
            std::string variant = item.as<std::string>();
            if (variant == default_value)
            {
                default_index = i;
            }
            variants.emplace_back(std::move(variant));
            i++;
        }

        if (default_index == -1)
        {
            throw spec_error(hcl_file, current_key,
                                "Default enum value " + default_value
                                + " not provided in enum variant list.");
        }

        def.variants = variants;
        def.default_index = default_index;

        return def;
    }

    std::string name;
    std::string locale_root;
    std::map<std::string, item> items;
};
}
}
