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
namespace spec
{

void object::init(const fs::path& path)
{
    clear();

    // TODO support loading multiple files.
    std::ifstream ifs(filesystem::make_preferred_path_in_utf8(path));
    load(ifs, path.string());
}

void object::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);
    std::string top_level_key = "core." + name;

    if (!parseResult.valid()) {
        std::cerr << parseResult.errorReason << std::endl;
        throw spec_error(hcl_file, u8"Failed to read " + hcl_file + u8": "
                         + parseResult.errorReason);
    }

    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has(name))
    {
        throw spec_error(hcl_file, "\"" + name + "\" object not found at top level"s);
    }

    const hcl::Value top_level = value[name];
    if (!top_level.is<hcl::Object>() || !top_level.has("def"))
    {
        throw spec_error(hcl_file, "\"def\" object not found at top level after \"" + name + "\""s);
    }

    const hcl::Value def = top_level["def"];
    auto result = visit_object(def.as<hcl::Object>(), top_level_key, hcl_file);

    post_visit(top_level_key, result);
    items.emplace(top_level_key, result);
}

section_def object::visit_object(const hcl::Object& object,
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

void object::visit(const hcl::Value& value,
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

item object::visit_bare_value(const hcl::Value& default_value,
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

void object::visit_item(const hcl::Object& item,
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
            i = enum_def{0, {"__unknown__"}, true};
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

section_def object::visit_section(const hcl::Object& section,
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

int_def object::visit_int(int default_value,
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

bool_def object::visit_bool(bool default_value)
{
    return bool_def{default_value};
}

string_def object::visit_string(const std::string& default_value)
{
    return string_def{default_value};
}

list_def object::visit_list(const hcl::List& default_value)
{
    return list_def{default_value};
}

enum_def object::visit_enum(const std::string& default_value,
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

}
} // namespace elona
