#include "data_manager.hpp"

#include "../log.hpp"
#include "api_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

DataManager::DataManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    _data = DataTable(lua_state()->create_table());
    clear();
}



void DataManager::clear()
{
    sol::table data = safe_script_file_in_global_env(
        filesystem::dirs::data() / "script" / "kernel" / "data.lua");
    std::pair<sol::table, sol::table> result = data["new_registry"]();
    _public_interface = result.first;
    _data.storage() = result.second;
}



void DataManager::_init_from_mod(ModEnv& mod)
{
    // Bypass the metatable on the mod's environment preventing creation of
    // new global variables.
    mod.env.raw_set("data", _public_interface);

    if (!mod.manifest.path)
    {
        return; // psuedo-mod
    }

    // The name of the mod for which the current data script is being ran is
    // present in the mod's environment table. However, it is not present in
    // the chunk where the 'data' table originates from, as it originated
    // outside of a mod environment. To determine which mod is adding new
    // types/data in the data chunk, it has to be set on the global Lua
    // state temporarily during the data loading process.
    lua_state()->set("_MOD_ID", mod.manifest.id);

    // for (const auto filename : {"data.lua",
    //                             "extensions.lua",
    //                             "data-update.lua",
    //                             "extensions-update.lua"})
    for (const auto filename : {"data.lua", "data-update.lua"})
    {
        const auto script_filepath = *mod.manifest.path / filename;
        if (fs::exists(script_filepath))
        {
            auto result = safe_script_file(
                script_filepath, mod.env, sol::script_pass_on_error);

            if (!result.valid())
            {
                sol::error err = result;
                throw err;
            }
        }
    }
}



void DataManager::init_from_mods()
{
    for (const auto& mod_id : lua().get_mod_manager().sorted_mods())
    {
        _init_from_mod(*lua().get_mod_manager().get_mod(mod_id));
    }

    lua_state()->set("_MOD_ID", sol::lua_nil);

    // Prevent modifications to the 'data' table.
    sol::table metatable = _data.storage().create_with(
        sol::meta_function::new_index,
        sol::detail::fail_on_newindex,
        sol::meta_function::index,
        _data.storage());

    _data.storage()[sol::metatable_key] = metatable;
}

} // namespace lua
} // namespace elona
