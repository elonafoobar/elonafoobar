#include "i18n_manager.hpp"

#include "../character.hpp"
#include "../config.hpp"
#include "../item.hpp"
#include "../random.hpp"
#include "api_manager.hpp"
#include "fmt.hpp"
#include "handle_manager.hpp"
#include "lua_env.hpp"
#include "mod_env.hpp"



namespace elona
{
namespace lua
{

namespace
{

fmt::ParseResult parse_fmt(const std::string& src, sol::this_state state)
{
    fmt::FormatParser parser{src, state};
    return parser.parse();
}

} // namespace



I18NManager::I18NManager(LuaEnv& lua)
    : LuaSubmodule(lua)
{
    env().set_function("parse_fmt", &parse_fmt);
    env().set_function("rnd", &rnd<int>);
    env().set("Config", lua.get_api_manager().get_core_api_table()["Config"]);

    {
        const auto result = safe_script_file(
            filesystem::dirs::data() / "script" / "kernel" / "i18n.lua");
        if (!result.valid())
        {
            sol::error e = result;
            throw std::runtime_error{e.what()};
        }
    }

    {
        const auto result = safe_script(R"(
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

    const auto script_filepath =
        *mod.manifest.path / "locale" / g_config.language() / "i18n.lua";
    if (!fs::exists(script_filepath))
        return;

    env()["_MOD_ID"] = mod.manifest.id;
    mod.env["ELONA"]["i18n"] = env()["i18n"];
    const auto result =
        safe_script_file(script_filepath, mod.env, sol::script_pass_on_error);
    env()["_MOD_ID"] = sol::lua_nil;
    if (!result.valid())
    {
        sol::error e = result;
        throw std::runtime_error{e.what()};
    }
}



void I18NManager::load_string(const std::string& src, ModEnv& mod)
{
    env()["_MOD_ID"] = mod.manifest.id;
    mod.env["ELONA"]["i18n"] = env()["i18n"];
    const auto result = safe_script(src, mod.env, sol::script_pass_on_error);
    env()["_MOD_ID"] = sol::lua_nil;
    if (!result.valid())
    {
        sol::error e = result;
        throw std::runtime_error{e.what()};
    }
}



void I18NManager::register_function(
    const std::string& language,
    const std::string& name,
    sol::protected_function function)
{
    if (env()[language] == sol::lua_nil)
    {
        env()[language] = lua_state()->create_table();
    }

    env()[language][name] = function;
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
