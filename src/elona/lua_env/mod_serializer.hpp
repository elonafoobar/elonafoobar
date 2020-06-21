#pragma once

#include "../../thirdparty/sol2/sol.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"
#include "handle_manager.hpp"
#include "lua_submodule.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

std::pair<int, int> get_start_end_indices(
    const std::string& kind,
    ModEnv::StoreType store_type);

std::string get_store_name(ModEnv::StoreType store_type);



class ModSerializer : public LuaSubmodule
{
public:
    explicit ModSerializer(LuaEnv& lua)
        : LuaSubmodule(lua)
    {
        // Load the Lua chunk for saving/loading data.
        safe_script(R"(Serial = require("serial"))");
    }

    template <typename Archive>
    void save_mod_store_data(
        Archive& putit_archive,
        ModEnv::StoreType store_type)
    {
        const auto& mod_mgr = lua().get_mod_manager();

        unsigned mod_count = static_cast<unsigned>(mod_mgr.mods().size());
        putit_archive(mod_count);

        for (const auto& pair : mod_mgr.mods())
        {
            std::string mod_id = pair.second.manifest.id;
            semver::Version mod_version = pair.second.manifest.version;

            putit_archive(mod_id);
            putit_archive(mod_version);

            sol::object data = pair.second.get_store(store_type);
            save(data, putit_archive);

            ELONA_LOG("lua.mod")
                << "Saved " << get_store_name(store_type) << " store data for "
                << mod_id << " " << mod_version.to_string();
        }
    }

    template <typename Archive>
    void load_mod_store_data(
        Archive& putit_archive,
        ModEnv::StoreType store_type)
    {
        auto& mod_mgr = lua().get_mod_manager();

        unsigned mod_count;
        putit_archive(mod_count);

        for (unsigned i = 0; i < mod_count; i++)
        {
            std::string mod_id;
            semver::Version mod_version;

            putit_archive(mod_id);
            putit_archive(mod_version);

            auto mod = mod_mgr.get_mod(mod_id);
            if (!mod)
            {
                // Skip this piece of data.
                ELONA_WARN("lua.mod")
                    << "WARNING: skipping mod store loading as mod wasn't loaded: "
                    << mod_id;

                std::string raw_data;
                putit_archive(raw_data);

                continue;
            }
            if (mod->manifest.version != mod_version)
            {
                // TODO: implement migration
                ELONA_WARN("lua.mod")
                    << "WARNING: skipping mod store loading as mod is upgraded or downgraded: "
                    << mod_id;

                std::string raw_data;
                putit_archive(raw_data);

                continue;
            }
            ELONA_LOG("lua.mod")
                << "Loaded " << get_store_name(store_type) << " store data for "
                << mod_id << " " << mod_version.to_string();

            sol::object data = load(putit_archive);

            mod->set_store(store_type, data);
        }
    }

private:
    template <typename Archive>
    void save(sol::object data, Archive& ar)
    {
        env()["_TO_SERIALIZE"] = data;
        auto result = safe_script(R"(return Serial.save(_TO_SERIALIZE))");
        env()["_TO_SERIALIZE"] = sol::lua_nil;

        if (result.valid())
        {
            std::string dump = result.get<std::string>();
            ar(dump);
        }
        else
        {
            sol::error err = result;
            throw err;
        }
    }

    template <typename Archive>
    sol::object load(Archive& ar)
    {
        std::string dump;
        ar(dump);

        env()["_TO_DESERIALIZE"] = dump;
        auto result = safe_script(R"(return Serial.load(_TO_DESERIALIZE))");
        env()["_TO_DESERIALIZE"] = sol::lua_nil;

        if (result.valid())
        {
            return result.get<sol::object>();
        }
        else
        {
            sol::error err = result;
            throw err;
        }
    }
};

} // namespace lua
} // namespace elona
