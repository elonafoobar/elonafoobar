#include "spec.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "filesystem.hpp"
#include "hcl.hpp"
#include "optional.hpp"

using namespace std::literals::string_literals;

namespace elona
{
namespace spec
{

namespace
{

static hcl::Value& skip_sections(
    hcl::Value& object,
    const std::vector<std::string> section_names,
    const std::string& hcl_file)
{
    std::string sections;
    hcl::Value* value = &object;

    for (auto it = section_names.begin(); it < section_names.end(); it++)
    {
        std::string name = *it;
        if (!value->is<hcl::Object>() || !value->has(name))
        {
            throw SpecError(
                hcl_file,
                "\"" + sections + "\" object not found at top level"s);
        }

        if (sections == "")
        {
            sections = name;
        }
        else
        {
            sections += "." + name;
        }
        value = value->find(name);
    }

    return *value;
}

} // namespace

void Object::init(const fs::path& path)
{
    clear();

    // TODO support loading multiple files.
    std::ifstream ifs(filesystem::make_preferred_path_in_utf8(path));
    load(ifs, path.string());
}

void Object::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);
    std::string top_level_key = "core." + name;

    if (!parseResult.valid())
    {
        std::cerr << parseResult.errorReason << std::endl;
        throw SpecError(
            hcl_file,
            u8"Failed to read " + hcl_file + u8": " + parseResult.errorReason);
    }

    hcl::Value& value = parseResult.value;
    const hcl::Value& def = skip_sections(value, {name, "def"}, hcl_file);
    auto result = visit_object(def.as<hcl::Object>(), top_level_key, hcl_file);

    post_visit(top_level_key, result);
    items.emplace(top_level_key, result);
}

SectionDef Object::visit_object(
    const hcl::Object& object,
    const std::string& current_key,
    const std::string& hcl_file)
{
    SectionDef def{};

    for (const auto& pair : object)
    {
        std::string key = current_key + "." + pair.first;
        visit(pair.second, key, hcl_file);
        def.children.emplace_back(pair.first);
    }

    return def;
}

void Object::visit(
    const hcl::Value& value,
    const std::string& current_key,
    const std::string& hcl_file)
{
    if (value.is<hcl::Object>())
    {
        visit_item(value.as<hcl::Object>(), current_key, hcl_file);
    }
    else
    {
        Item i = visit_bare_value(value, current_key, hcl_file);
        items.emplace(current_key, i);
    }
}

Item Object::visit_bare_value(
    const hcl::Value& default_value,
    const std::string& current_key,
    const std::string& hcl_file)
{
    Item i;

    pre_visit_bare_value(current_key, default_value);

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
        throw SpecError(hcl_file, current_key, "Invalid default value.");
    }

    return i;
}

void Object::visit_item(
    const hcl::Object& item,
    const std::string& current_key,
    const std::string& hcl_file)
{
    optional<spec::Item> i;

    pre_visit_item(current_key, item);

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
                throw SpecError(
                    hcl_file, current_key, "No default enum value provided.");
            }
            i = visit_enum(
                item.at("default").as<std::string>(),
                item,
                current_key,
                hcl_file);
        }
        else if (type == "runtime_enum")
        {
            i = EnumDef{0, {spec::unknown_enum_variant}, true};
        }
        else
        {
            throw SpecError(
                hcl_file, current_key, "Invalid type " + type + ".");
        }
    }
    else
    {
        if (item.find("default") == item.end())
        {
            throw SpecError(
                hcl_file, current_key, "No default value provided.");
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
        throw SpecError(hcl_file, current_key, "Could not parse value.");
    }

    items.emplace(current_key, *i);
}

SectionDef Object::visit_section(
    const hcl::Object& section,
    const std::string& current_key,
    const std::string& hcl_file)
{
    pre_visit_section(current_key, section);

    if (section.find("options") == section.end())
    {
        throw SpecError(
            hcl_file, current_key, "Section has no field named \"options\".");
    }
    const hcl::Object& options = section.at("options").as<hcl::Object>();

    return visit_object(options, current_key, hcl_file);
}

IntDef Object::visit_int(
    int default_value,
    const hcl::Object& item,
    const std::string& current_key,
    const std::string& hcl_file)
{
    IntDef def;

    if (item.find("min") == item.end())
    {
        throw SpecError(
            hcl_file, current_key, "Integer option has no \"min\" field.");
    }
    if (item.find("max") == item.end())
    {
        throw SpecError(
            hcl_file, current_key, "Integer option has no \"max\" field.");
    }

    def.min = item.at("min").as<int>();
    def.max = item.at("max").as<int>();
    def.default_value = default_value;

    return def;
}

BoolDef Object::visit_bool(bool default_value)
{
    return BoolDef{default_value};
}

StringDef Object::visit_string(const std::string& default_value)
{
    return StringDef{default_value};
}

ListDef Object::visit_list(const hcl::List& default_value)
{
    return ListDef{default_value};
}

EnumDef Object::visit_enum(
    const std::string& default_value,
    const hcl::Object& item,
    const std::string& current_key,
    const std::string& hcl_file)
{
    EnumDef def{};
    if (item.find("variants") == item.end())
    {
        throw SpecError(hcl_file, current_key, "No enum variants provided.");
    }

    hcl::List hcl_variants = item.at("variants").as<hcl::List>();
    std::vector<std::string> variants;
    optional<size_t> default_index;
    size_t i = 0;
    for (auto& item : hcl_variants)
    {
        std::string variant = item.as<std::string>();
        if (variant == default_value)
        {
            default_index = i;
        }
        variants.emplace_back(std::move(variant));
        ++i;
    }

    if (!default_index)
    {
        throw SpecError(
            hcl_file,
            current_key,
            "Default enum value " + default_value
                + " not provided in enum variant list.");
    }

    def.variants = variants;
    def.default_index = *default_index;

    return def;
}

} // namespace spec
} // namespace elona
