#include "i18n.hpp"

#include <fstream>
#include <memory>

#include "../thirdparty/microhil/hil.hpp"
#include "config.hpp"
#include "defines.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "hcl.hpp"
#include "random.hpp"
#include "variables.hpp"



namespace elona
{
namespace i18n
{

i18n::Store s;



void Store::init(const std::vector<Store::Location>& locations)
{
    clear();

    for (const auto& loc : locations)
    {
        locale_dir_table[loc.mod_id] = loc.locale_dir;
        load(loc.locale_dir, loc.mod_id);
    }
}

void Store::load(const fs::path& path, const std::string& mod_id)
{
    for (const auto& entry : filesystem::glob_files(path))
    {
        std::ifstream ifs(entry.path().native());
        if (!ifs)
        {
            throw std::runtime_error{
                "Failed to open " +
                filepathutil::make_preferred_path_in_utf8(entry.path())};
        }

        load(ifs, filepathutil::to_utf8_path(entry.path()), mod_id);
    }
}

void Store::load(
    std::istream& is,
    const std::string& hcl_file,
    const std::string& mod_id)
{
    const hcl::Value& value = hclutil::load(is, hcl_file);

    if (!value.is<hcl::Object>() || !value.has("locale"))
    {
        throw I18NError(hcl_file, "\"locale\" object not found");
    }

    const hcl::Value locale = value["locale"];

    visit_object(locale.as<hcl::Object>(), mod_id, hcl_file);
}

void Store::visit_object(
    const hcl::Object& object,
    const std::string& current_key,
    const std::string& hcl_file)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file);
    }
}

void Store::visit_string(
    const std::string& string,
    const std::string& current_key,
    const std::string& hcl_file)
{
    std::stringstream ss(string);

    hil::ParseResult p = hil::parse(ss);
    // TODO validate ident names?
    if (!p.valid())
    {
        throw I18NError(hcl_file, "HIL parse error: " + p.errorReason);
    }

    storage.emplace(current_key, std::move(p.context));
}

void Store::visit_list(
    const hcl::List& list,
    const std::string& current_key,
    const std::string& hcl_file)
{
    std::vector<LocalizedText> parsed;

    for (const auto& item : list)
    {
        if (!item.is<std::string>())
        {
            throw I18NError(
                hcl_file,
                current_key + ": List must only contain string values.");
        }

        std::stringstream ss(item.as<std::string>());

        hil::ParseResult p = hil::parse(ss);
        // TODO validate ident names?
        if (!p.valid())
        {
            throw I18NError(hcl_file, "HIL parse error: " + p.errorReason);
        }
        parsed.emplace_back(std::move(p.context));
    }

    list_storage.emplace(current_key, std::move(parsed));
}

void Store::visit(
    const hcl::Value& value,
    const std::string& current_key,
    const std::string& hcl_file)
{
    if (value.is<std::string>())
    {
        visit_string(value.as<std::string>(), current_key, hcl_file);
    }
    if (value.is<hcl::List>())
    {
        visit_list(value.as<hcl::List>(), current_key, hcl_file);
    }
    else if (value.is<hcl::Object>())
    {
        visit_object(value.as<hcl::Object>(), current_key, hcl_file);
    }
}

std::string space_if_needed()
{
    if (jp)
    {
        return "";
    }
    else
    {
        return u8" ";
    }
}



} // namespace i18n
} // namespace elona
