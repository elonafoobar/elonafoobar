#include "api_manager.hpp"

#include <iterator>

#include "../../util/strutil.hpp"
#include "api/classes.hpp"
#include "api/modules.hpp"
#include "enums/enums.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

APIManager::APIManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    load_native();
    load_prelude();

    safe_script(R"EOS(
register_api = function(mod_id, exports)
   if not api_table[mod_id] then
      api_table[mod_id] = {}
   end

   local root = api_table[mod_id]
   for k, v in pairs(exports) do
      if type(k) ~= "string" then
         error("Error loading mod '"..mod_id.."': mod API tables must only have string keys.")
      end
      root[k] = v
   end
end
)EOS");

    load_kernel();
    load_core();
}



void APIManager::load_native()
{
    // Bind the API tables at e.g. api_table["core"]["Chara"]
    sol::table api_table = env().create_named("api_table");
    sol::table core = api_table.create_named("core");

    api::modules::bind(core);

    // Register usertype classes globally, and add APIs for constructors.
    api::classes::bind(*lua_state());
    api::classes::bind_api(*lua_state(), core);

    lua_state()->globals()["native"] = core;
}



void APIManager::load_prelude()
{
    load_library(fs::u8path("prelude") / "init.lua", "prelude");
}



void APIManager::load_kernel()
{
    load_library(fs::u8path("kernel") / "init.lua", "kernel");
}



void APIManager::load_core()
{
    load_library(fs::u8path("core") / "init.lua", "core");

    safe_script(R"(
for k, v in pairs(core) do
   api_table.core[k] = v
end
)");
}



void APIManager::load_library(
    const fs::path& path,
    const std::string& library_name)
{
    auto result = safe_script_file(filesystem::dirs::data() / "script" / path);
    if (!result.valid())
    {
        sol::error err = result;
        ELONA_ERROR("API: "s + err.what());
        throw std::runtime_error{
            "Failed initializing internal Lua library '" + library_name + "'."};
    }

    lua_state()->globals()[library_name] = result;
}



void APIManager::clear()
{
    // TODO
}



void APIManager::register_api(const std::string& mod_id, sol::table exports)
{
    env()["register_api"](mod_id, exports);
}



sol::optional<sol::table> APIManager::try_find_api(
    const std::string& name) const
{
    const auto pair = strutil::split_on_string(name, ".");
    return env().traverse_get<sol::optional<sol::table>>(
        "api_table", pair.first, pair.second);
}



void APIManager::lock()
{
    safe_script(
        R"(
api_table = kernel.ReadOnly.make_read_only(api_table)
)");
}



sol::table APIManager::get_master_api_table()
{
    return env()["api_table"];
}



sol::table APIManager::get_core_api_table()
{
    return env()["api_table"]["core"];
}

} // namespace lua
} // namespace elona
