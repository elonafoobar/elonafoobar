#pragma once

#include <unordered_map>

#include "../../thirdparty/sol2/sol.hpp"
#include "../../util/strutil.hpp"
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

        const auto full_path = resolve_path(name, state);
        if (!file_contained_in_dir(full_path))
            return sol::lua_nil;

        sol::object result =
            state.script_file(filepathutil::to_utf8_path(full_path), env);

        if (result != sol::lua_nil)
            chunk_cache[name] = result;

        return result;
    }


private:
    fs::path base_path;
    std::unordered_map<std::string, sol::object> chunk_cache;



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



    // Resolve a relative path `filename`.
    // If `filename` starts with a slash, it is relative from the root directory
    // of the mod. If not, it is relative from the file where the caller is
    // defined.
    fs::path resolve_path(const std::string& filename, sol::state& state)
    {
        if (filename.empty())
        {
            return {}; // invalid filename.
        }

        if (filename[0] == '/')
        {
            // relative from the root directory of the mod.
            return base_path / filename;
        }
        else
        {
            // get the source file where the caller is defined.
            lua_State* L = state;
            lua_Debug dbg;
            // stack index 1 points to the caller.
            if (!lua_getstack(L, 1, &dbg))
            {
                return {};
            }
            // get the info related to source code.
            if (!lua_getinfo(L, "S", &dbg))
            {
                return {};
            }
            std::string source(dbg.source);
            if (source.empty())
            {
                return {}; // invalid source file.
            }
            if (source[0] != '@')
            {
                return {}; // the caller function is defined by evaluating a
                           // string.
            }
            const auto caller_path = filepathutil::u8path(
                source.substr(1) /* remove the head '@' */);
            return caller_path.parent_path() / filename;
        }
    }
};

} // namespace lua
} // namespace elona
