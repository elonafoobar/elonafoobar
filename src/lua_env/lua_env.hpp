#pragma once
#include "../thirdparty/sol2/sol.hpp"
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

class APIManager;
class DataManager;
class EventManager;
class ExportManager;
class HandleManager;
class I18NFunctionManager;
class ModManager;
class LuaConsole;

/***
 * Main singleton encapsulating various Lua subsystems. Delegates
 * responsibility for specific Lua-related operations to invidual
 * subsystems.
 */
class LuaEnv
{
public:
    explicit LuaEnv();

    /***
     * Returns a shared pointer to the Lua environment's internal Lua
     * state.
     */
    std::shared_ptr<sol::state> get_state()
    {
        return lua_;
    }

    //********** Individual API manager retrieval methods **********//

    APIManager& get_api_manager()
    {
        return *api_mgr;
    }

    EventManager& get_event_manager()
    {
        return *event_mgr;
    }

    ExportManager& get_export_manager()
    {
        return *export_mgr;
    }

    HandleManager& get_handle_manager()
    {
        return *handle_mgr;
    }

    I18NFunctionManager& get_i18n_function_manager()
    {
        return *i18n_function_mgr;
    }

    ModManager& get_mod_manager()
    {
        return *mod_mgr;
    }

    DataManager& get_data_manager()
    {
        return *data_mgr;
    }

    LuaConsole& get_console()
    {
        return *lua_console;
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

    std::unique_ptr<ModManager> mod_mgr;
    std::unique_ptr<APIManager> api_mgr;
    std::unique_ptr<EventManager> event_mgr;
    std::unique_ptr<ExportManager> export_mgr;
    std::unique_ptr<HandleManager> handle_mgr;
    std::unique_ptr<DataManager> data_mgr;
    std::unique_ptr<I18NFunctionManager> i18n_function_mgr;
    std::unique_ptr<LuaConsole> lua_console;
};

extern std::unique_ptr<LuaEnv> lua;

} // namespace lua
} // namespace elona
