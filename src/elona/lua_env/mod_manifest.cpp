#include "mod_manifest.hpp"

#include "../../thirdparty/json5/json5.hpp"



namespace elona
{
namespace lua
{

namespace
{

std::string _read_string(
    const std::string key,
    const json5::value::object_type& obj,
    const fs::path& path)
{
    // TODO: Clean up, as with lua::ConfigTable
    const auto itr = obj.find(key);
    if (itr != std::end(obj) && itr->second.is_string())
    {
        return itr->second.get_string();
    }
    else
    {
        throw std::runtime_error(
            path.to_u8string() + ": Missing \"" + key + "\" in mod manifest");
    }
}



semver::Version _read_mod_version(
    const json5::value::object_type& obj,
    const fs::path& path)
{
    // TODO: Clean up, as with lua::ConfigTable
    const auto itr = obj.find("version");
    if (itr == std::end(obj))
    {
        return semver::Version{};
    }

    if (itr->second.is_string())
    {
        if (const auto result =
                semver::Version::parse(itr->second.get_string()))
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
            path.to_u8string() + ": Missing \"version\" in mod manifest");
    }
}



ModManifest::Dependencies _read_dependencies(
    const json5::value::object_type& obj,
    const fs::path& path)
{
    ModManifest::Dependencies result;

    const auto itr = obj.find("dependencies");
    if (itr != std::end(obj))
    {
        if (itr->second.is_object())
        {
            const auto& dependencies = itr->second.get_object();

            for (const auto& kvp : dependencies)
            {
                const auto& mod = kvp.first;
                const auto& version = kvp.second;
                if (version.is_string())
                {
                    if (const auto req = semver::VersionRequirement::parse(
                            version.get_string()))
                    {
                        result.emplace(mod, req.right());
                    }
                    else
                    {
                        throw std::runtime_error(
                            path.to_u8string() + ": " + req.left());
                    }
                }
                else
                {
                    throw std::runtime_error(
                        path.to_u8string() +
                        ": \"dependencies\" field must be an object.");
                }
            }
        }
        else
        {
            throw std::runtime_error(
                path.to_u8string() +
                ": \"dependencies\" field must be an object.");
        }
    }

    return result;
}

} // namespace



ModManifest ModManifest::load(const fs::path& path)
{
    // TODO loading error handling.
    std::ifstream in{path.native()};
    std::string source{
        std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
    const auto value = json5::parse(source);
    const auto& obj = value.get_object();

    const auto mod_id = _read_string("id", obj, path);
    const auto mod_name = _read_string("name", obj, path);
    const auto mod_author = _read_string("author", obj, path);
    const auto mod_description = _read_string("description", obj, path);
    const auto mod_license = _read_string("license", obj, path);
    const auto version = _read_mod_version(obj, path);
    const auto mod_path = path.parent_path();
    const auto dependencies = _read_dependencies(obj, path);

    return {
        mod_id,
        mod_name,
        mod_author,
        mod_description,
        mod_license,
        version,
        mod_path,
        dependencies,
    };
}



void ModManifest::save() const
{
    if (!path)
    {
        throw std::runtime_error{
            "attempt to save mod manifest having no physical path"};
    }

    json5::value::object_type root_obj;
    root_obj["id"] = id;
    root_obj["name"] = name;
    root_obj["author"] = author;
    root_obj["description"] = description;
    root_obj["license"] = license;
    root_obj["version"] = version.to_string();

    json5::value::object_type deps;
    for (const auto& dep : dependencies)
    {
        deps[dep.first] = dep.second.to_string();
    }
    root_obj["dependencies"] = deps;

    json5::stringify_options opts;
    opts.prettify = true;
    opts.insert_trailing_comma = true;
    opts.unquote_key = true;
    opts.sort_by_key = true;

    const auto manifest_filepath = (*path) / "mod.json";
    std::ofstream out{manifest_filepath.native()};
    if (!out)
    {
        throw std::runtime_error{
            "failed to open mod manifest file to write: " +
            manifest_filepath.to_u8string()};
    }
    out << json5::stringify(root_obj, opts) << std::endl;
}

} // namespace lua
} // namespace elona
