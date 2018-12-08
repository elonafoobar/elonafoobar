#pragma once
#include <unordered_map>
#include "../../thirdparty/sol2/sol.hpp"
#include "../filesystem.hpp"

namespace elona
{
namespace lua
{


/**
 * Acts as Lua's package.loaded and require, but local to a single Lua
 * environment.
 *
 * This is needed since package.loaded is normally global to the entire Lua
 * state.
 */
class LoadedChunkCache
{
public:
    LoadedChunkCache(const fs::path& base_path_)
        : base_path(base_path_)
    {
        assert(fs::exists(base_path));
    }

public:
    sol::object
    require(const std::string& name, sol::environment env, sol::state& state)
    {
        auto it = chunk_cache.find(name);
        if (it != chunk_cache.end())
            return it->second;

        const fs::path full_path = base_path / (name + ".lua");
        if (!file_contained_in_dir(full_path))
            return sol::lua_nil;

        sol::object result = state.script_file(full_path.string(), env);

        if (result != sol::lua_nil)
            chunk_cache[name] = result;

        return result;
    }

private:
    bool file_contained_in_dir(fs::path file)
    {
        // Modifies filename, so copy is needed.
        if (!file.has_filename())
        {
            return false;
        }
        file.remove_filename();

        if (!fs::exists(file))
        {
            return false;
        }

        // Strip "." and ".."
        file = fs::canonical(file);
        fs::path dir = fs::canonical(base_path);

        std::size_t dir_len = std::distance(dir.begin(), dir.end());
        std::size_t file_len = std::distance(file.begin(), file.end());

        if (dir_len > file_len)
        {
            return false;
        }

        bool dir_is_prefix = std::equal(dir.begin(), dir.end(), file.begin());
        return dir_is_prefix;
    }

    fs::path base_path;
    std::unordered_map<std::string, sol::object> chunk_cache;
};

} // namespace lua
} // namespace elona
