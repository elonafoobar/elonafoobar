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
     * Loads a mod manifest from a mod.hcl file.
     */
    static ModManifest load(const fs::path& path);

    std::string name;
    semver::Version version;
    optional<fs::path> path;
    Dependencies dependencies;
};

} // namespace lua
} // namespace elona
