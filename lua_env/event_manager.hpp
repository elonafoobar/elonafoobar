#pragma once

#include "../optional.hpp"
#include "lua_env.hpp"
#include <map>

namespace elona
{
namespace lua
{

class lua_env;

/***
 * Enumeration for all possible events that can be triggered.
 *
 * NOTE: If you change this, be sure to update the constructor for
 * event_manager so the event kind is bound to Lua.
 */
enum class event_kind_t : unsigned
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

    // Triggered when this slot becomes invalid (chara.state = 0 or item.number = 0).
    // Doesn't trigger if a character dies but can revive (chara.state != 0).
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

    COUNT // for iterating over all event kinds
};

/***
 * Contains a list of callbacks to be run in a defined order.
 */
class callbacks
{
public:
    struct callback_t
    {
        sol::protected_function function;
        sol::environment env;
        std::string mod_name;
        callback_t(sol::environment _env, sol::protected_function _function, std::string _mod_name)
        {
            env = _env;
            function = _function;
            mod_name = _mod_name;
        }
    };

    template<typename> struct retval_type {};

    typedef std::vector<callback_t> callback_container;
    typedef callback_container::iterator iterator;
    typedef callback_container::const_iterator const_iterator;

    const_iterator begin() const { return functions.begin(); }
    const_iterator end() const { return functions.end(); }

    void set_error_handler(sol::function error_handler) { this->error_handler_ = error_handler; }

    /***
     * Adds a callback to the callback list.
     *
     * Assumes the Lua environment passed in belongs to a mod, since
     * this will be bound to the Lua Event API.
     */
    void push(sol::environment &mod_env, sol::protected_function &function)
    {
        sol::optional<std::string> mod_name = mod_env["_MOD_NAME"];
        assert(mod_name != sol::nullopt);
        functions.emplace_back(mod_env, function, *mod_name);
    }

    template<typename... Args>
    void run(retval_type<void>, Args&&... args)
    {
        for (const auto iter : functions)
        {
            auto result = iter.function.call(std::forward<Args>(args)...);
            if(!result.valid())
            {
                sol::error err = result;
                error_handler_(err.what());
                return;
            }
        }
    }

    template<typename R, typename... Args>
    optional<R> run(retval_type<R>, Args&&... args)
    {
        R retval = none;

        for (const auto& iter : functions)
        {
            auto result = iter.function.call(std::forward<Args>(args)...);
            if(!result.valid())
            {
                sol::error err = result;
                error_handler_(err.what());
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
    callback_container functions;
    sol::function error_handler_;
};

/***
 * Manages a list of callbacks for each event type. Allows triggering
 * callbacks from C++ with any arguments needed.
 */
class event_manager
{

public:
    /***
     * Binds the Lua Event API and the EventKind enum to the lua_env's
     * API manager.
     */
    static void init(lua_env&);
public:
    explicit event_manager(lua_env*);

    /***
     * Registers a new event handler from a mod's environment.
     */
    void register_event(event_kind_t, sol::environment&, sol::protected_function&);

    /***
     * Runs all callbacks for this event in the order they were registered.
     */
    void trigger_event(event_kind_t, sol::table);

    const callbacks& get_callbacks(event_kind_t event) const
    {
        return events.at(event);
    }

    template<event_kind_t event, typename R = void, typename... Args>
    R run_callbacks(Args&&... args)
    {
        return events.at(event).run(callbacks::retval_type<R>{},
                                        std::forward<Args>(args)...);
    }

    template<event_kind_t event, typename R = void>
    R run_callbacks()
    {
        return events.at(event).run(callbacks::retval_type<R>{});
    }

    void clear();

    typedef std::unordered_map<event_kind_t, callbacks> container;
private:
    void init_events();
    container events;
    lua_env* lua;
};

} // namespace lua
} // namespace elona
