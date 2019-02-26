#include "lua_env.hpp"
#include "../config/config.hpp"
#include "api_manager.hpp"
#include "data_manager.hpp"
#include "event_manager.hpp"
#include "export_manager.hpp"
#include "handle_manager.hpp"
#include "i18n_function_manager.hpp"
#include "lua_console.hpp"
#include "mod_manager.hpp"

namespace elona
{
namespace lua
{

std::unique_ptr<LuaEnv> lua;

LuaEnv::LuaEnv()
{
    lua_ = std::make_shared<sol::state>();
    lua_->open_libraries(
        sol::lib::base,
        sol::lib::package,
        sol::lib::table,
        sol::lib::debug,
        sol::lib::string,
        sol::lib::math,
        sol::lib::io,
        sol::lib::os);

    // Add executable directory to package.path
    fs::path exe_path = filesystem::dir::data() / "script" / "kernel";
    std::string normalized = filepathutil::to_forward_slashes(exe_path);
    lua_->safe_script(
        u8"package.path = \""s + normalized + u8"/?.lua;\"..package.path"s);

    // Make sure the API environment is initialized first so any
    // dependent managers can add new internal C++ methods to it (like
    // the event manager registering Elona.Event)
    api_mgr = std::make_unique<APIManager>(this);
    event_mgr = std::make_unique<EventManager>(this);
    mod_mgr = std::make_unique<ModManager>(this);
    handle_mgr = std::make_unique<HandleManager>(this);
    data_mgr = std::make_unique<DataManager>(this);
    export_mgr = std::make_unique<ExportManager>(this);
    i18n_function_mgr = std::make_unique<I18NFunctionManager>(this);
    lua_console = std::make_unique<LuaConsole>(this);
}



// The destructor cannot be automatically defined because some "T" of
// "std::unique_ptr<T>" are incomplete types and just forward-declared in the
// header file to reduce compilation time.
LuaEnv::~LuaEnv() = default;



void LuaEnv::clear()
{
    for (int i = 0; i < 5480; i++)
    {
        if (inv[i].number() != 0)
        {
            handle_mgr->remove_item_handle(inv[i]);
        }
    }

    for (int i = 0; i < ELONA_MAX_CHARACTERS; i++)
    {
        if (cdata[i].state() != Character::State::empty)
        {
            handle_mgr->remove_chara_handle(cdata[i]);
        }
    }

    event_mgr->clear();
    mod_mgr->clear_mod_stores();
    data_mgr->clear();
    lua_->collect_garbage();
}

void LuaEnv::reload()
{
    clear(); // Unload character/item handles while they're still available.
    get_state()->set("_IS_TEST", Config::instance().is_test);
}

} // namespace lua
} // namespace elona
