#include "mod_manifest.hpp"
#include "../hcl.hpp"

namespace elona
{
namespace lua
{

static std::string _read_mod_name(const hcl::Value& value, const fs::path& path)
{
    std::string result;

    // TODO: Clean up, as with lua::ConfigTable
    const hcl::Value* object = value.find("name");
    if (object && object->is<std::string>())
    {
        result = object->as<std::string>();
    }
    else
    {
        throw std::runtime_error(
            path.string() + ": Missing \"name\" in mod manifest");
    }

    return result;
}

static std::unordered_set<std::string> _read_dependencies(
    const hcl::Value& value,
    const fs::path& path)
{
    std::unordered_set<std::string> result;

    const hcl::Value* object = value.find("dependencies");
    if (object)
    {
        if (object->is<hcl::List>())
        {
            auto dependencies = object->as<hcl::List>();

            for (const auto& value : dependencies)
            {
                if (value.is<std::string>())
                {
                    result.insert(value.as<std::string>());
                }
                else
                {
                    throw std::runtime_error(
                        path.string()
                        + ": \"dependencies\" field must be a list of "
                          "strings.");
                }
            }
        }
        else
        {
            throw std::runtime_error(
                path.string()
                + ": \"dependencies\" field must be a list of strings.");
        }
    }

    return result;
}

ModManifest ModManifest::load(const fs::path& path)
{
    auto parsed = hclutil::load(path);
    const auto& value = hclutil::skip_sections(parsed, {"mod"}, path.string());

    std::string mod_name = _read_mod_name(value, path);
    fs::path mod_path = path.parent_path();
    auto dependencies = _read_dependencies(value, path);

    return ModManifest{mod_name, mod_path, dependencies};
}

} // namespace lua
} // namespace elona
