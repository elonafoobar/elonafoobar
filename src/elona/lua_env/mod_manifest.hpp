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

    /**
     * Loads a mod manifest from a mod.json file.
     */
    static ModManifest load(const fs::path& path);

    /**
     * Save itself to `path`.
     * If you call it against the mod whose `path` is none, throws exception.
     */
    void save() const;

    std::string id;
    std::string name;
    std::string author;
    std::string description;
    std::string license;
    semver::Version version;
    optional<fs::path> path;
    Dependencies dependencies;
};

} // namespace lua
} // namespace elona
