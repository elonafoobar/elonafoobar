#pragma once
#include "../../thirdparty/sol2/sol.hpp"
#include "../filesystem.hpp"
#include "../log.hpp"
#include "handle_manager.hpp"
#include "lua_env.hpp"
#include "mod_manager.hpp"

namespace elona
{
namespace lua
{

std::pair<int, int> get_start_end_indices(
    const std::string& kind,
    ModInfo::StoreType store_type);

std::string get_store_name(ModInfo::StoreType store_type);

class LuaEnv;

class ModSerializer
{
public:
    explicit ModSerializer(LuaEnv* lua)
        : _lua(lua)
    {
        _serial_env = sol::environment(
            *(_lua->get_state()), sol::create, _lua->get_state()->globals());

        // Load the Lua chunk for saving/loading data.
        _lua->get_state()->safe_script(
            R"(Serial = require "serial")", _serial_env);
    }

    template <typename T, typename Archive>
    void save_handles(Archive& putit_archive, ModInfo::StoreType store_type)
    {
        int index_start, index_end;
        std::tie(index_start, index_end) =
            get_start_end_indices(T::lua_type(), store_type);

        auto handles = _lua->get_handle_manager().get_handle_range(
            T::lua_type(), index_start, index_end);
        save(handles, putit_archive);

        ELONA_LOG("lua.mod")
            << "Saved handle data for " << T::lua_type() << " in ["
            << index_start << "," << index_end << "]";

        handles = sol::lua_nil;
    }

    template <typename T, typename Archive>
    std::pair<int, int> load_handles(
        Archive& putit_archive,
        ModInfo::StoreType store_type)
    {
        int index_start, index_end;
        std::tie(index_start, index_end) =
            get_start_end_indices(T::lua_type(), store_type);

        sol::table handles = _lua->get_state()->create_table();
        load(handles, putit_archive);

        auto& handle_mgr = _lua->get_handle_manager();
        handle_mgr.clear_handle_range(T::lua_type(), index_start, index_end);
        handle_mgr.merge_handles(T::lua_type(), handles);

        ELONA_LOG("lua.mod")
            << "Loaded handle data for " << T::lua_type() << " in ["
            << index_start << "," << index_end << "]";

        handles = sol::lua_nil;
        return {index_start, index_end};
    }

    template <typename Archive>
    void save_mod_store_data(
        Archive& putit_archive,
        ModInfo::StoreType store_type)
    {
        const auto& mod_mgr = _lua->get_mod_manager();

        unsigned mod_count = static_cast<unsigned>(mod_mgr.enabled_mod_count());
        putit_archive(mod_count);

        for (const auto& pair : mod_mgr.enabled_mods())
        {
            std::string mod_id = pair.second->manifest.id;
            semver::Version mod_version = pair.second->manifest.version;

            putit_archive(mod_id);
            putit_archive(mod_version);

            sol::table data = pair.second->get_store(store_type);
            save(data, putit_archive);

            ELONA_LOG("lua.mod")
                << "Saved " << get_store_name(store_type) << " store data for "
                << mod_id << " " << mod_version.to_string();
        }
    }

    template <typename Archive>
    void load_mod_store_data(
        Archive& putit_archive,
        ModInfo::StoreType store_type)
    {
        auto& mod_mgr = _lua->get_mod_manager();

        unsigned mod_count;
        putit_archive(mod_count);

        for (unsigned i = 0; i < mod_count; i++)
        {
            std::string mod_id;
            semver::Version mod_version;

            putit_archive(mod_id);
            putit_archive(mod_version);

            auto mod = mod_mgr.get_enabled_mod_optional(mod_id);
            if (!mod)
            {
                // Skip this piece of data.
                ELONA_WARN("lua.mod")
                    << "WARNING: skipping mod store loading as mod "
                       "wasn't loaded: "
                    << mod_id;

                std::string raw_data;
                putit_archive(raw_data);

                continue;
            }
            ELONA_LOG("lua.mod")
                << "Loaded " << get_store_name(store_type) << " store data for "
                << mod_id << " " << mod_version.to_string();

            sol::table data = _lua->get_state()->create_table();
            load(data, putit_archive);

            (*mod)->set_store(store_type, data);
        }
    }

private:
    template <typename Archive>
    void save(sol::table& data, Archive& ar)
    {
        _serial_env["_TO_SERIALIZE"] = data;
        auto result = _lua->get_state()->safe_script(
            R"(return Serial.save(_TO_SERIALIZE))", _serial_env);
        _serial_env["_TO_SERIALIZE"] = sol::lua_nil;

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
    void load(sol::table& data, Archive& ar)
    {
        std::string dump;
        ar(dump);

        _serial_env["_TO_DESERIALIZE"] = dump;
        auto result = _lua->get_state()->safe_script(
            R"(return Serial.load(_TO_DESERIALIZE))", _serial_env);
        _serial_env["_TO_DESERIALIZE"] = sol::lua_nil;

        if (result.valid())
        {
            data = result.get<sol::table>();
        }
        else
        {
            sol::error err = result;
            throw err;
        }
    }

    /***
     * The isolated Lua environment that loads the Lua serialization
     * code.
     */
    sol::environment _serial_env;

    LuaEnv* _lua;
};

} // namespace lua
} // namespace elona
