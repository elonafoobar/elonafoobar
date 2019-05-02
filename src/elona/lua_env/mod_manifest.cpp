#include "mod_manifest.hpp"

#include "../hcl.hpp"

namespace elona
{
namespace lua
{

namespace
{

std::string _read_string(
    const std::string key,
    const hcl::Value& value,
    const fs::path& path)
{
    std::string result;

    // TODO: Clean up, as with lua::ConfigTable
    const hcl::Value* object = value.find(key);
    if (object && object->is<std::string>())
    {
        result = object->as<std::string>();
    }
    else
    {
        throw std::runtime_error(
            filepathutil::to_utf8_path(path) + ": Missing \"" + key +
            "\" in mod manifest");
    }

    return result;
}



semver::Version _read_mod_version(const hcl::Value& value, const fs::path& path)
{
    // TODO: Clean up, as with lua::ConfigTable
    const hcl::Value* object = value.find("version");
    if (!object)
    {
        return semver::Version{};
    }

    if (object->is<std::string>())
    {
        if (const auto result =
                semver::Version::parse(object->as<std::string>()))
        {
            return result.right();
        }
        else
        {
            throw std::runtime_error{result.left()};
        }
    }
    else
    {
        throw std::runtime_error(
            filepathutil::to_utf8_path(path) +
            ": Missing \"version\" in mod manifest");
    }
}



ModManifest::Dependencies _read_dependencies(
    const hcl::Value& value,
    const fs::path& path)
{
    ModManifest::Dependencies result;

    const hcl::Value* object = value.find("dependencies");
    if (object)
    {
        if (object->is<hcl::Object>())
        {
            const auto& dependencies = object->as<hcl::Object>();

            for (const auto& kvp : dependencies)
            {
                hcl::Value mod;
                hcl::Value version;
                std::tie(mod, version) = kvp;

                if (mod.is<std::string>() && version.is<std::string>())
                {
                    if (const auto req = semver::VersionRequirement::parse(
                            version.as<std::string>()))
                    {
                        result.emplace(mod.as<std::string>(), req.right());
                    }
                    else
                    {
                        throw std::runtime_error(
                            filepathutil::to_utf8_path(path) + ": " +
                            req.left());
                    }
                }
                else
                {
                    throw std::runtime_error(
                        filepathutil::to_utf8_path(path) +
                        ": \"dependencies\" field must be an object.");
                }
            }
        }
        else
        {
            throw std::runtime_error(
                filepathutil::to_utf8_path(path) +
                ": \"dependencies\" field must be an object.");
        }
    }

    return result;
}

} // namespace



ModManifest ModManifest::load(const fs::path& path)
{
    auto parsed = hclutil::load(path);
    const auto& value = hclutil::skip_sections(
        parsed, {"mod"}, filepathutil::to_utf8_path(path));

    const auto mod_name = _read_string("name", value, path);
    const auto mod_author = _read_string("author", value, path);
    const auto mod_description = _read_string("description", value, path);
    const auto mod_license = _read_string("license", value, path);
    const auto version = _read_mod_version(value, path);
    const auto mod_path = path.parent_path();
    const auto dependencies = _read_dependencies(value, path);

    return ModManifest{mod_name,
                       mod_author,
                       mod_description,
                       mod_license,
                       version,
                       mod_path,
                       dependencies};
}

} // namespace lua
} // namespace elona
