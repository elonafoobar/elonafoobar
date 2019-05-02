#include "data_manager.hpp"

#include "../../util/natural_order_comparator.hpp"
#include "../log.hpp"
#include "api_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

namespace
{

std::vector<std::string> _list_files(
    const fs::path& root_dir,
    const std::regex& pattern)
{
    std::vector<std::string> ret;

    // glob
    range::transform(
        filesystem::dir_entries(
            root_dir, filesystem::DirEntryRange::Type::file, pattern),
        std::back_inserter(ret),
        [](const auto& entry) {
            return filepathutil::to_utf8_path(entry.path());
        });

    // sort
    range::sort(ret, lib::natural_order_comparator{});

    return ret;
}

} // namespace



DataManager::DataManager(LuaEnv* lua)
    : _lua(lua)
{
    _env = sol::environment(
        *(_lua->get_state()), sol::create, _lua->get_state()->globals());
    _data = DataTable(_lua->get_state()->create_table());
    clear();
}



void DataManager::clear()
{
    // Load registry.lua in kernel.
    _env["__Registry__"] = _lua->get_state()->script_file(
        filepathutil::to_utf8_path(
            filesystem::dir::data() / "script" / "kernel" / "registry.lua"),
        _env);

    // Create new instance of Registry.
    sol::table r =
        _lua->get_state()->safe_script(u8"return __Registry__.new()", _env);

    _registry = r;
    _data.storage() = r;

    // Clean up the environment.
    _env["__Registry__"] = sol::nil;
}



void DataManager::_init_from_mod(ModInfo& mod)
{
    if (!mod.manifest.path)
        return;

    struct
    {
        const char* dir;
        const char* load_func_name;
        bool is_prototype;
    } proto_data_dir_info[] = {
        {u8"prototypes", u8"_load_prototype_files", true},
        {u8"prototypes/extensions", u8"_load_extension_prototype_files", true},
        {u8"data", u8"_load_data_files", false},
        {u8"data/extensions", u8"_load_extension_files", false},
    };

    for (const auto& info : proto_data_dir_info)
    {
        const auto root_dir = *mod.manifest.path / info.dir;
        if (!fs::exists(root_dir))
            continue;

        const auto hcl_filepaths =
            _list_files(root_dir, std::regex{u8R"([0-9A-Za-z_]+\.hcl)"});

        // Compiles HCL files and generate Lua scripts.
        for (const auto& hcl_filepath : hcl_filepaths)
        {
            auto lua_filepath = hcl_filepath + u8".cache.lua";
            if (fs::exists(lua_filepath))
            {
                // TODO
                // if (the mod is NOT under development by the user)
                if (true)
                {
                    // Cache has already created, skipping.
                    continue;
                }
            }

            // Generate Lua file from HCL declaration file.
            sol::protected_function compile = _registry["_compile"];
            const auto result = compile(
                mod.manifest.name,
                hcl_filepath,
                lua_filepath,
                info.is_prototype);
            if (!result.valid())
            {
                sol::error err = result;
                ELONA_ERROR("lua.data") << "error occurs while compiling "
                                        << hcl_filepath << ": " << err.what();

                throw err;
            }
        }

        // Load Lua scripts.
        const auto lua_filepaths = _list_files(
            root_dir,
            std::regex{u8R"([0-9A-Za-z_]+(?:\.lua|\.hcl.cache.lua))"});

        // Sandboxed dofile() executed on mod's environment.
        const auto safe_dofile = [this, &mod](const std::string& filename) {
            sol::object ret = _lua->get_state()->script_file(filename, mod.env);
            return ret;
        };

        sol::protected_function load = _registry[info.load_func_name];
        const auto result = load(
            _registry /* self */,
            mod.manifest.name,
            lua_filepaths,
            safe_dofile);
        if (!result.valid())
        {
            sol::error err = result;
            ELONA_ERROR("lua.data") << "error occurs while loading data of "
                                    << mod.manifest.name << ": " << err.what();

            throw err;
        }
    }
}



void DataManager::init_from_mods()
{
    for (const auto& mod_name :
         _lua->get_mod_manager().calculate_loading_order())
    {
        const auto& mod = _lua->get_mod_manager().get_enabled_mod(mod_name);
        _init_from_mod(*mod);
    }

    // Prevent modifications to the 'Registry' table.
    sol::table metatable = _data.storage().create_with(
        sol::meta_function::new_index, sol::detail::fail_on_newindex);

    _data.storage()[sol::metatable_key] = metatable;
}

} // namespace lua
} // namespace elona
