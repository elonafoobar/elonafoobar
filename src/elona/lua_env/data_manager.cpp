#include "data_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

DataManager::DataManager(LuaEnv* lua)
{
    _lua = lua;
    _data = DataTable(_lua->get_state()->create_table());
    clear();
}

void DataManager::clear()
{
    sol::table data = _lua->get_state()->script_file(filepathutil::to_utf8_path(
        filesystem::dir::data() / "script" / "kernel" / "data.lua"));
    _data.storage() = data;
}

void DataManager::_init_from_mod(ModInfo& mod)
{
    // Bypass the metatable on the mod's environment preventing creation of
    // new global variables.
    mod.env.raw_set("data", _data.storage());

    if (mod.manifest.path)
    {
        // The name of the mod for which the current data script is being ran is
        // present in the mod's environment table. However, it is not present in
        // the chunk where the 'data' table originates from, as it originated
        // outside of a mod environment. To determine which mod is adding new
        // types/data in the data chunk, it has to be set on the global Lua
        // state temporarily during the data loading process.
        _lua->get_state()->set("_MOD_NAME", mod.manifest.name);

        const auto data_script = *mod.manifest.path / "data.lua";
        if (fs::exists(data_script))
        {
            auto result = _lua->get_state()->safe_script_file(
                filepathutil::to_utf8_path(data_script),
                mod.env,
                sol::script_pass_on_error);

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
    for (const auto& mod_name :
         _lua->get_mod_manager().calculate_loading_order())
    {
        const auto& mod = _lua->get_mod_manager().get_mod(mod_name);
        _init_from_mod(*mod);
    }

    _lua->get_state()->set("_MOD_NAME", sol::lua_nil);

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
