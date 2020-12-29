#include "i18n_manager.hpp"

#include "../character.hpp"
#include "../config.hpp"
#include "../item.hpp"
#include "../random.hpp"
#include "api_manager.hpp"
#include "handle_manager.hpp"
#include "lua_env.hpp"
#include "mod_env.hpp"



namespace elona
{
namespace lua
{

I18NManager::I18NManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    {
        const auto result = safe_script(R"(
local I18N = kernel.I18N

get_optional = I18N.get_optional
get_data_text_optional = I18N.get_data_text_optional
get_list = I18N.get_list
i18n = I18N.interface
format = I18N.format
)");
        if (!result.valid())
        {
            sol::error e = result;
            throw std::runtime_error{e.what()};
        }
    }
}



void I18NManager::load(ModEnv& mod)
{
    if (!mod.manifest.path)
        return;

    const auto script_filepath = *mod.manifest.path / "locale" /
        fs::u8path(g_config.language()) / "i18n.lua";
    if (!fs::exists(script_filepath))
        return;

    lua_state()->set("_MOD_ID", mod.manifest.id);
    mod.env["ELONA"]["i18n"] = env()["i18n"];
    const auto result =
        safe_script_file(script_filepath, mod.env, sol::script_pass_on_error);
    lua_state()->set("_MOD_ID", sol::lua_nil);
    if (!result.valid())
    {
        sol::error e = result;
        throw std::runtime_error{e.what()};
    }
}



void I18NManager::load_string(const std::string& src, ModEnv& mod)
{
    lua_state()->set("_MOD_ID", mod.manifest.id);
    mod.env["ELONA"]["i18n"] = env()["i18n"];
    const auto result = safe_script(src, mod.env, sol::script_pass_on_error);
    lua_state()->set("_MOD_ID", sol::lua_nil);
    if (!result.valid())
    {
        sol::error e = result;
        throw std::runtime_error{e.what()};
    }
}



void I18NManager::add_arg(sol::table args, const ItemRef& value)
{
    args.add(value);
}



void I18NManager::add_arg(sol::table args, const Character& value)
{
    args.add(lua::lua->get_handle_manager().get_handle(value));
}

} // namespace lua
} // namespace elona
