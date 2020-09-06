#pragma once

#include <unordered_map>

#include "../filesystem.hpp"
#include "../optional.hpp"
#include "../semver.hpp"



namespace elona
{
namespace lua
{

struct ModManifest
{
    using Dependencies =
        std::unordered_map<std::string, semver::VersionRequirement>;


    struct LocalizableString
    {
        std::string default_text;
        std::unordered_map<std::string, std::string> localized_strings;


        LocalizableString() = default;


        std::string localize(const std::string& locale_id) const
        {
            if (const auto itr = localized_strings.find(locale_id);
                itr != localized_strings.end())
            {
                return itr->second;
            }
            else
            {
                return default_text;
            }
        }
    };



    /**
     * Loads a mod manifest from a mod.json file.
     */
    static ModManifest load(const fs::path& path);

    /**
     * Save itself to `path`.
     * If you call it against the mod whose `path` is none, throws exception.
     */
    void save() const;



    /// The ID. It must be unique. (Required field)
    std::string id;

    /// The display name. It can be localized. (Optional field)
    LocalizableString name;

    /// The author(s) name. (Optional field)
    std::string authors;

    /// The description. It can be localized. (Optional field)
    LocalizableString description;

    /// The license. (Optional field)
    std::string license;

    /// The version. (Required field)
    semver::Version version;

    /// The dependencies. (Optional field)
    Dependencies dependencies;

    /// The optional dependencies. (Optional field)
    Dependencies optional_dependencies;

    /// The homepage. (Optional field)
    std::string homepage;

    /// The tags. (Optional field)
    std::vector<std::string> tags;

    /// The folder where the mod is located. If it is `none`, the mod is a
    /// pseudo-mod and does not have phyisical folder.
    optional<fs::path> path;
};

} // namespace lua
} // namespace elona
