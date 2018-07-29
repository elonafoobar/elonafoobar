#include "lua_env.hpp"
#include "../config.hpp"

namespace elona
{
namespace lua
{

std::unique_ptr<lua_env> lua;

lua_env::lua_env()
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
    fs::path exe_path = filesystem::dir::data() / "lua";
    std::string normalized = filesystem::to_forward_slashes(exe_path);
    lua_->safe_script(u8"package.path = \""s + normalized + u8"/?.lua;\"..package.path"s);

    // Make sure the API environment is initialized first so any
    // dependent managers can add new internal C++ methods to it (like
    // the event manager registering Elona.Event)
    api_mgr = std::make_unique<api_manager>(this);
    event_mgr = std::make_unique<event_manager>(this);
    mod_mgr = std::make_unique<mod_manager>(this);
    handle_mgr = std::make_unique<handle_manager>(this);
    registry_mgr = std::make_unique<registry_manager>(this);
    export_mgr = std::make_unique<export_manager>(this);
    serial_mgr = std::make_unique<serial_manager>(this);
}

void lua_env::clear()
{
    for (int i = 0; i < ELONA_MAX_ITEMS; i++)
    {
        if (inv[i].number != 0)
        {
            handle_mgr->remove_item_handle(inv[i]);
        }
    }

    for (int i = 0; i < ELONA_MAX_CHARACTERS; i++)
    {
        if (cdata[i].state != 0)
        {
            handle_mgr->remove_chara_handle(cdata[i]);
        }
    }

    event_mgr->clear();
    mod_mgr->clear_mod_stores();
    lua_->collect_garbage();
}

void lua_env::reload()
{
    clear(); // Unload character/item handles while they're still available.
    get_state()->set("_IS_TEST", config::instance().is_test);
}

} // namespace lua
} // namespace elona
