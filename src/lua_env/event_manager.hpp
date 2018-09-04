#pragma once

#include <map>
#include "../optional.hpp"
#include "lua_env.hpp"

namespace elona
{
namespace lua
{

class LuaEnv;

/***
 * Enumeration for all possible events that can be triggered.
 *
 * NOTE: If you change this, be sure to update the constructor for
 * EventManager so the event kind is bound to Lua.
 */
enum class EventKind : unsigned
{
    // Triggered when brand-new object instances are created (not loaded).
    map_created,
    character_created,
    item_created,

    // Triggered after either creation or loading.
    map_initialized,
    character_initialized,
    item_initialized,
    game_initialized,

    map_unloading,
    map_loaded,

    // Triggered when this slot becomes invalid (chara.state = 0 or item.number
    // = 0). Doesn't trigger if a character dies but can revive (chara.state !=
    // 0).
    character_removed,
    item_removed,

    character_refreshed,
    character_damaged,

    // Triggered when a character is killed, regardless of revive type.
    character_killed,

    // Turn lifecycle events
    character_moved,
    player_turn,
    all_turns_finished,

    all_mods_loaded,
    script_loaded,

    COUNT // for iterating over all event kinds
};

/***
 * Contains a list of callbacks to be run in a defined order.
 */
class Callbacks
{
public:
    struct Callback
    {
        sol::protected_function function;
        sol::environment env;
        std::string mod_name;
        Callback(
            sol::environment _env,
            sol::protected_function _function,
            std::string _mod_name)
        {
            env = _env;
            function = _function;
            mod_name = _mod_name;
        }
    };

    template <typename>
    struct RetValType
    {
    };

    using CallbackContainer = std::vector<Callback>;
    using iterator = CallbackContainer::iterator;
    using const_iterator = CallbackContainer::const_iterator;

    const_iterator begin() const
    {
        return functions.begin();
    }
    const_iterator end() const
    {
        return functions.end();
    }

    void set_error_handler(sol::function error_handler)
    {
        this->error_handler_ = error_handler;
    }

    /***
     * Adds a callback to the callback list.
     *
     * Assumes the Lua environment passed in belongs to a mod, since
     * this will be bound to the Lua Event API.
     */
    void push(sol::environment& mod_env, sol::protected_function& function)
    {
        sol::optional<std::string> mod_name = mod_env["_MOD_NAME"];
        assert(mod_name != sol::nullopt);
        functions.emplace_back(mod_env, function, *mod_name);
    }

    /***
     * Removes a callback from the callback list.
     */
    void remove(const std::string& mod_name, sol::protected_function& function)
    {
        for (auto it = functions.begin(); it != functions.end(); it++)
        {
            if (it->mod_name == mod_name && it->function == function)
            {
                functions.erase(it);
                return;
            }
        }
    }

    /***
     * Removes callbacks originating from the given mod.
     */
    void remove_all_from_mod(const std::string& mod_name)
    {
        for (auto it = functions.begin(); it != functions.end(); /*it++*/)
        {
            if (it->mod_name == mod_name)
            {
                it = functions.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    void clear()
    {
        functions.clear();
    }

    template <typename... Args>
    void run(RetValType<void>, Args&&... args)
    {
        for (const auto iter : functions)
        {
            auto result = iter.function.call(std::forward<Args>(args)...);
            if (!result.valid())
            {
                sol::error err = result;
                error_handler_(err.what());
            }
        }
    }

    template <typename R, typename... Args>
    optional<R> run(RetValType<R>, Args&&... args)
    {
        R retval = none;

        for (const auto& iter : functions)
        {
            auto result = iter.function.call(std::forward<Args>(args)...);
            if (!result.valid())
            {
                sol::error err = result;
                error_handler_(err.what());
                // TODO: Don't prevent later callbacks from running?
                return none;
            }
            else
            {
                retval = result.value();
            }
        }

        return retval;
    }

private:
    CallbackContainer functions;
    sol::function error_handler_;
};

/***
 * Manages a list of callbacks for each event type. Allows triggering
 * callbacks from C++ with any arguments needed.
 */
class EventManager
{

public:
    explicit EventManager(LuaEnv*);

    /***
     * Registers a new event handler from a mod's environment.
     */
    void
    register_event(EventKind, sol::environment&, sol::protected_function&);

    /***
     * Unregisters an event handler from a mod's environment by
     * comparing the function reference passed in.
     */
    void
    unregister_event(EventKind, sol::environment&, sol::protected_function&);

    /***
     * Clears all mod-local callbacks of the given event kind.
     */
    void clear_mod_callbacks(EventKind, sol::environment&);

    /***
     * Clears all mod-local callbacks.
     */
    void clear_mod_callbacks(sol::environment&);

    /***
     * Runs all callbacks for this event in the order they were registered.
     */
    void trigger_event(EventKind, sol::table);

    const Callbacks& get_callbacks(EventKind event) const
    {
        return events.at(event);
    }

    template <EventKind event, typename R = void, typename... Args>
    R run_callbacks(Args&&... args)
    {
        return events.at(event).run(
            Callbacks::RetValType<R>{}, std::forward<Args>(args)...);
    }

    template <EventKind event, typename R = void>
    R run_callbacks()
    {
        return events.at(event).run(Callbacks::RetValType<R>{});
    }

    void clear();

    using Container = std::unordered_map<EventKind, Callbacks>;

private:
    /***
     * Binds the Lua Event API and the EventKind enum to the LuaEnv's
     * API manager.
     */
    void bind_api(LuaEnv&);

    /**
     * Sets up event callback error handlers for each event type.
     */
    void init_events();

    /***
     * Creates the Event.EventKind enum table in Lua.
     */
    void init_event_kinds(sol::table&);

    Container events;
    LuaEnv* lua;
};

} // namespace lua
} // namespace elona
