#pragma once
#include "../thirdparty/sol2/sol.hpp"
#include "handle_manager.hpp"
#include "event_manager.hpp"
#include "export_manager.hpp"
#include "api_manager.hpp"
#include "registry_manager.hpp"
#include "mod_manager.hpp"
#include "serial_manager.hpp"

namespace elona
{
namespace lua
{

class api_manager;
class event_manager;
class export_manager;
class mod_manager;
class handle_manager;
class registry_manager;
class serial_manager;

/***
 * Main singleton encapsulating various Lua subsystems. Delegates
 * responsibility for specific Lua-related operations to invidual
 * subsystems.
 */
class lua_env
{
public:
    explicit lua_env();

    /***
     * Returns a shared pointer to the Lua environment's internal Lua
     * state.
     */
    std::shared_ptr<sol::state> get_state()
    {
        return lua_;
    }

    //********** Individual API manager retrieval methods **********//

    api_manager& get_api_manager()
    {
        return *api_mgr;
    }

    event_manager& get_event_manager()
    {
        return *event_mgr;
    }

    export_manager& get_export_manager()
    {
        return *export_mgr;
    }

    handle_manager& get_handle_manager()
    {
        return *handle_mgr;
    }

    mod_manager& get_mod_manager()
    {
        return *mod_mgr;
    }

    registry_manager& get_registry_manager()
    {
        return *registry_mgr;
    }

    serial_manager& get_serial_manager()
    {
        return *serial_mgr;
    }

    /***
     * Clears and reset the Lua state to directly after loading the
     * core mod.
     *
     * Used when modifying startup scripts.
     */
    void reload();


    //****************** Methods for testing use *******************//

    /***
     * Unloads all characters and items tracked by handles.
     *
     * For testing use only.
     */
    void clear();

private:
    /***
     * The underlying Lua state shared across all mod/API
     * environments.
     */
    std::shared_ptr<sol::state> lua_;

    std::unique_ptr<mod_manager> mod_mgr;
    std::unique_ptr<api_manager> api_mgr;
    std::unique_ptr<event_manager> event_mgr;
    std::unique_ptr<export_manager> export_mgr;
    std::unique_ptr<handle_manager> handle_mgr;
    std::unique_ptr<registry_manager> registry_mgr;
    std::unique_ptr<serial_manager> serial_mgr;
};

extern std::unique_ptr<lua_env> lua;

} // namespace lua
} // namespace elona
