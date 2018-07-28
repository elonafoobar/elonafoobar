#pragma once
#include "event_manager.hpp"
#include "handle_manager.hpp"
#include "api_manager.hpp"
#include "lua_registry.hpp"
#include "mod_manager.hpp"
#include "../lib/noncopyable.hpp"
#include "../thirdparty/sol2/sol.hpp"

class api_manager;
class event_manager;
class mod_manager;
class handle_manager;
class registry_manager;

/***
 * Main singleton encapsulating various Lua subsystems. Delegates
 * responsibility for specific operations to invidual subsystems.
 */
class lua_env : public lib::noncopyable
{
    void initialize();

    /***
     * Returns a shared pointer to this mod_manager's internal Lua state.
     */
    std::shared_ptr<sol::state> get_state()
    {
        return lua;
    }

    //********** Individual API manager retrieval methods **********//

    api_manager& get_api_manager()
    {
        return api_mgr.get();
    }

    event_manager& get_event_manager()
    {
        return event_mgr.get();
    }

    handle_manager& get_handle_manager()
    {
        return handle_mgr.get();
    }

    mod_manager& get_mod_manager()
    {
        return mod_mgr.get();
    }

    registry_manager& get_registry_manager()
    {
        return registry_mgr.get();
    }

    /***
     * Clears and reset the Lua state to directly after loading the
     * core mod.
     *
     * Used when modifying startup scripts.
     */
    void reload();

private:
    /***
     * The underlying Lua state shared across all mod/API
     * environments.
     */
    std::shared_ptr<sol::state> lua;

    std::unique_ptr<mod_manager> mod_mgr;
    std::unique_ptr<api_manager> api_mgr;
    std::unique_ptr<event_manager> event_mgr;
    std::unique_ptr<handle_manager> handle_mgr;
    std::unique_ptr<registry_manager> registry_mgr;
};

extern std::unique_ptr<lua_env> lua;
