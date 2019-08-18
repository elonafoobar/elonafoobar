#include "mod_manifest.hpp"
#include "lson.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

namespace
{

std::string convert_id(const std::string& id)
{
    if (!is_valid_mod_id(id))
    {
        throw std::runtime_error{"Invalid mod ID: " + id};
    }

    return id;
}



semver::Version convert_version(const std::string& version)
{
    if (const auto result = semver::Version::parse(version))
    {
        return result.right();
    }
    else
    {
        throw std::runtime_error{result.left()};
    }
}



ModManifest::Dependencies convert_dependencies(
    std::unordered_map<std::string, std::string> deps)
{
    ModManifest::Dependencies result;

    for (const auto& kvp : deps)
    {
        std::string mod;
        std::string version;
        std::tie(mod, version) = kvp;

        if (const auto req = semver::VersionRequirement::parse(version))
        {
            result.emplace(convert_id(mod), req.right());
        }
        else
        {
            throw std::runtime_error{req.left()};
        }
    }

    return result;
}

} // namespace



ModManifest ModManifest::load(const fs::path& manifest_path)
{
    auto value = lson::parse_file(manifest_path);

    const auto get_required = [&](const char* key) {
        const auto opt = value.get<std::string>(key);
        return opt.value();
    };
    const auto get_optional = [&](const char* key) {
        return value.get<std::string>(key).value_or("");
    };

    const auto id = convert_id(get_required("id"));
    const auto name = get_required("name");
    const auto authors = get_optional("authors");
    const auto description = get_optional("description");
    const auto license = get_optional("license");
    const auto version = convert_version(get_required("version"));
    const auto path = manifest_path.parent_path();
    const auto dependencies = convert_dependencies(
        value.get_table<std::string, std::string>("dependencies"));

    return ModManifest{
        id, name, authors, description, license, version, path, dependencies};
}

} // namespace lua
} // namespace elona
