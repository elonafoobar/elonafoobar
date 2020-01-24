#pragma once

#include "loaded_chunk_cache.hpp"
#include "mod_manifest.hpp"



namespace elona
{
namespace lua
{

/***
 * Stores the Lua environment and internal storage for a single mod.
 *
 * Mods each have a sanitized environment with a whitelist of safe functions,
 * so things like dofile can't be called. They also have storage object for
 * storing, serializing and deserializing mod data alongside the base game
 * data.
 */
struct ModEnv
{
    enum class StoreType
    {
        global,
        map,
    };



    explicit ModEnv(const ModManifest& manifest, sol::environment env)
        : manifest(manifest)
        , env(env)
    {
        if (manifest.path)
        {
            chunk_cache = LoadedChunkCache{*manifest.path};
        }
    }



    ModEnv(const ModEnv&) = delete;
    ModEnv(ModEnv&&) = delete;
    ModEnv& operator=(const ModEnv&) = delete;
    ModEnv& operator=(ModEnv&&) = delete;
    ~ModEnv() = default;



    sol::object get_store(StoreType store_type) const
    {
        const auto table_name = convert_store_type_to_table_name(store_type);
        return env.get<sol::object>(std::tie("mod", "store", table_name));
    }



    void set_store(StoreType store_type, sol::object data)
    {
        const auto table_name = convert_store_type_to_table_name(store_type);
        // bypass metatable that forces store table reference to be
        // unchangeable (set in mod_manager::bind_store)
        sol::table store = env.get<sol::table>(std::tie("mod", "store"));
        store.raw_set(table_name, data);
    }



    ModManifest manifest;
    optional<LoadedChunkCache> chunk_cache;
    sol::environment env;



private:
    static constexpr const char* convert_store_type_to_table_name(
        StoreType store_type)
    {
        switch (store_type)
        {
        case StoreType::global: return "global";
        case StoreType::map: return "map";
        default: assert(0); return nullptr;
        }
    }
};

} // namespace lua
} // namespace elona
