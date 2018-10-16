#include "data_manager.hpp"

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
    sol::table data =
        _lua->get_state()->script_file(filesystem::make_preferred_path_in_utf8(
            filesystem::dir::data() / "lua" / "data.lua"));
    _data.storage = data;
}

void DataManager::init_from_mods()
{
    for (const auto& pair : _lua->get_mod_manager())
    {
        const auto& mod = pair.second;

        // Bypass the metatable on the mod's environment preventing creation of
        // new global variables.
        mod->env.raw_set("data", _data.storage);

        if (mod->path)
        {
            // The name of the mod for which the current data script is being
            // ran is present in the mod's environment table. However, it is not
            // present in the chunk where the 'data' table originates from, as
            // it was ran outside of an environment on creation. To determine
            // which mod is adding new types/data in the data chunk, it has to
            // be set globally for each mod temporarily during the data loading
            // process.
            _lua->get_state()->set("_MOD_NAME", mod->name);

            const auto data_script = *mod->path / "data.lua";
            if (fs::exists(data_script))
            {
                auto result = _lua->get_state()->safe_script_file(
                    filesystem::make_preferred_path_in_utf8(data_script),
                    mod->env,
                    sol::script_pass_on_error);

                if (!result.valid())
                {
                    sol::error err = result;
                    throw err;
                }
            }
        }
    }

    _lua->get_state()->set("_MOD_NAME", sol::lua_nil);

    sol::table metatable = _data.storage.create_with(
        sol::meta_function::new_index,
        sol::detail::fail_on_newindex,
        sol::meta_function::index,
        _data.storage);

    _data.storage[sol::metatable_key] = metatable;
}

} // namespace lua
} // namespace elona
