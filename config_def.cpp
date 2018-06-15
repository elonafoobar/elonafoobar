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

void config_def::init(const fs::path& path)
{
    clear();

    // TODO support loading multiple files.
    std::ifstream ifs(filesystem::make_preferred_path_in_utf8(path));
    load(ifs, path.string());
}

void config_def::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid()) {
        std::cerr << parseResult.errorReason << std::endl;
        throw config_def_error(hcl_file, u8"Failed to read " + hcl_file + u8": "
                                   + parseResult.errorReason);
    }

    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("config_def"))
    {
        throw config_def_error(hcl_file, "\"config_def\" object not found at top level");
    }

    const hcl::Value conf = value["config_def"];

    auto def = visit_object(conf.as<hcl::Object>(), "core.config", hcl_file);

    data.emplace("core.config", config_def_item_data{});
    items.emplace("core.config", def);
}

config_def::config_section_def config_def::visit_object(const hcl::Object& object,
                          const std::string& current_key,
                          const std::string& hcl_file)
{
    config_section_def def{};

    for (const auto& pair : object)
    {
        std::string key = current_key + "." + pair.first;
        visit(pair.second, key, hcl_file);
        def.children.emplace_back(pair.first);
    }

    return def;
}

void config_def::visit(const hcl::Value& value,
                       const std::string& current_key,
                       const std::string& hcl_file)
{
    if (value.is<hcl::Object>())
    {
        visit_item(value.as<hcl::Object>(), current_key, hcl_file);
    }
    else if (value.is<int>())
    {
        item i = config_int_def{value.as<int>(), none, none};
        data.emplace(current_key, config_def_item_data{});
        items.emplace(current_key, i);
    }
    else
    {
        item i = visit_bare_value(value, current_key, hcl_file);
        data.emplace(current_key, config_def_item_data{});
        items.emplace(current_key, i);
    }
    std::cout << current_key << ": " << type_to_string(current_key) << std::endl;
}

config_def::item config_def::visit_bare_value(const hcl::Value& default_value,
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
        throw config_def_error(hcl_file, current_key, "Invalid default value.");
    }

    return i;
}

void config_def::visit_item(const hcl::Object& item,
                       const std::string& current_key,
                       const std::string& hcl_file)
{
    config_def_item_data dat = config_def_item_data{};
    optional<config_def::item> i;

    if (item.find("doc") != item.end())
    {
        dat.doc = item.at("doc").as<std::string>();
    }
    if (item.find("visible") != item.end())
    {
        dat.visible = item.at("visible").as<bool>();
    }
    if (item.find("preload") != item.end())
    {
        dat.preload = item.at("preload").as<bool>();
    }

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
                throw config_def_error(hcl_file, current_key, "No default enum value provided.");
            }
            i = visit_enum(item.at("default").as<std::string>(), item, current_key, hcl_file);
        }
        else if (type == "runtime_enum")
        {
            i = config_def::config_enum_def{0, {""}, true};
        }
        else
        {
            throw config_def_error(hcl_file, current_key, "Invalid type " + type + ".");
        }
    }
    else
    {
        if (item.find("default") == item.end())
        {
            throw config_def_error(hcl_file, current_key, "No default value provided.");
        }

        auto default_value = item.at("default");
        if (default_value.is<int>())
        {
            i = visit_int(default_value.as<int>(), item);
        }
        else
        {
            i = visit_bare_value(default_value, current_key, hcl_file);
        }
    }

    if (!i)
    {
        throw config_def_error(hcl_file, current_key, "Could not parse value.");
    }

    data.emplace(current_key, dat);
    items.emplace(current_key, *i);
}

config_def::config_section_def config_def::visit_section(const hcl::Object& section,
                   const std::string& current_key,
                   const std::string& hcl_file)
{
    if (section.find("options") == section.end())
    {
        throw config_def_error(hcl_file, current_key, "Section has no field named \"options\".");
    }
    const hcl::Object& options = section.at("options").as<hcl::Object>();
    return visit_object(options, current_key, hcl_file);
}

config_def::config_int_def config_def::visit_int(int default_value,
               const hcl::Object& item)
{
    config_int_def def;

    if (item.find("min") != item.end())
    {
        def.min = item.at("min").as<int>();
    }
    if (item.find("max") != item.end())
    {
        def.max = item.at("max").as<int>();
    }

    def.default_value = default_value;

    return def;
}

config_def::config_bool_def config_def::visit_bool(bool default_value)
{
    return config_bool_def{default_value};
}

config_def::config_string_def config_def::visit_string(const std::string& default_value)
{
    return config_string_def{default_value};
}

config_def::config_list_def config_def::visit_list(const hcl::List& default_value)
{
    return config_list_def{default_value};
}

config_def::config_enum_def config_def::visit_enum(const std::string& default_value,
                           const hcl::Object& item,
                           const std::string& current_key,
                           const std::string& hcl_file)
{
    config_enum_def def{};
    if (item.find("variants") == item.end())
    {
        throw config_def_error(hcl_file, current_key, "No enum variants provided.");
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
        throw config_def_error(hcl_file, current_key,
                               "Default enum value " + default_value
                               + " not provided in enum variant list.");
    }

    def.variants = variants;
    def.default_index = default_index;

    return def;
}


} // namespace elona
