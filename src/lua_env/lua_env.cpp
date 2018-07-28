#include "lua_env.hpp"

namespace elona
{
namespace lua
{

void lua_env::initialize()
{
    lua = std::make_shared<sol::state>();
    lua->open_libraries(
        sol::lib::base,
        sol::lib::package,
        sol::lib::table,
        sol::lib::debug,
        sol::lib::string,
        sol::lib::math,
        sol::lib::io);

    // Add executable directory to package.path
    fs::path exe_path = filesystem::dir::data() / "lua";
    std::string normalized = filesystem::to_forward_slashes(exe_path);
    lua->safe_script(u8"package.path = \""s + normalized + u8"/?.lua;\"..package.path"s);

    // Make sure the API environment is initialized first so any
    // dependent managers can add new internal C++ methods to it (like
    // the event manager registering Elona.Event)
    api_mgr = std::make_unique<api_manager>(this);
    event_mgr = std::make_unique<event_manager>(this);
    mod_mgr = std::make_unique<mod_manager>(this);
    handle_mgr = std::make_unique<handle_manager>(this);
    registry_mgr = std::make_unique<registry_manager>(this);
}

void lua_env::clear()
{
    for (int i = 0; i < 5480; i++)
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
    lua->collect_garbage();

    // TODO needed?
    // mods.clear();
    // stage = mod_loading_stage_t::not_started;
}

void lua_env::reload()
{
    clear(); // Unload character/item handles while they're still available.
    get_state()->set("_IS_TEST", config::instance().is_test);

    // TODO needed?
    //mod_mgr->load_mods(filesystem::dir::mods());
}

} // namespace lua
} // namespace elona
