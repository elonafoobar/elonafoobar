#pragma once
#include <unordered_set>
#include "../filesystem.hpp"
#include "../optional.hpp"

namespace elona
{
namespace lua
{

struct ModManifest
{
    /**
     * Loads a mod manifest from a mod.hcl file.
     */
    static ModManifest load(const fs::path& path);

    std::string name;
    optional<fs::path> path;
    std::unordered_set<std::string> dependencies;
};

} // namespace lua
} // namespace elona
