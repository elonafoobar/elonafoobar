#pragma once

#include <set>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../item.hpp"
#include "../lib/noncopyable.hpp"
#include "lua_env.hpp"

namespace elona
{

struct Character;

namespace lua
{

class LuaEnv;

/***
 * Provides and manages references to C++ objects as Lua tables
 * (handles) that can be checked for validity on access. Works around
 * the problem of users storing references to C++ things somewhere and
 * forgetting to check they're still valid.
 *
 * The handles are represented as Lua tables stored in an isolated Lua
 * environment. Each handle acts as a reference to an object whose
 * memory is managed by C++. The C++ reference is not stored on the
 * handle; it acts as a unique identifier for that object instance,
 * but to gain access to the C++ reference the handle manager must be
 * used, where it will check for validity. The handle manager also
 * acts as the interface for providing handles to other Lua
 * environments.
 *
 * See data/lua/handle.lua for more information.
 */
class HandleManager : public lib::noncopyable
{
public:
    explicit HandleManager(LuaEnv*);

    /***
     * Creates a new handle in the isolated handle environment.
     *
     * If the handle already exists, handle_set is instead checked for
     * validity.
     */
    void create_chara_handle(const Character& chara);
    void create_item_handle(const Item& item);

    /***
     * Removes an existing handle in the isolated handle environment.
     *
     * If the handle doesn't exist in this manager's handle list, handle_set
     * is checked that the handle is invalid.
     */
    void remove_chara_handle(const Character& chara);
    void remove_item_handle(const Item& item);


    /***
     * Methods that will create/remove handles as well as run
     * creation/removal event callbacks using the event manager
     * instance.
     */
    void create_chara_handle_run_callbacks(const Character&);
    void create_item_handle_run_callbacks(const Item&);
    void remove_chara_handle_run_callbacks(const Character&);
    void remove_item_handle_run_callbacks(const Item&);


    /***
     * Looks up the C++ reference that a handle points to. Will throw
     * if the handle is invalid or of the wrong type.
     */
    template <typename T>
    T& get_ref(sol::table handle)
    {
        sol::object obj =
            handle_env["Handle"]["get_ref"](handle, T::lua_type());
        return obj.as<T&>();
    }

    template <typename T>
    bool handle_is(sol::table handle)
    {
        return handle["__kind"] == T::lua_type();
    }

    bool handle_is_valid(sol::table handle)
    {
        return handle_env["Handle"]["is_valid"](handle);
    }


    /***
     * Provides a Lua reference to a handle from the isolated handle
     * environment.
     */
    template <typename T>
    sol::table get_handle(T& obj)
    {
        if (obj.index == -1)
        {
            return sol::lua_nil;
        }

        // NOTE: currently indexes by the object's integer ID, but
        // this may be phased out in the future.
        sol::object handle =
            handle_env["Handle"]["get_handle"](obj, T::lua_type());
        if (!handle.is<sol::table>())
        {
            return sol::lua_nil;
        }
        return handle;
    }


    sol::table
    get_handle_range(const std::string& kind, int index_start, int index_end)
    {
        return handle_env["Handle"]["get_handle_range"](
            kind, index_start, index_end);
    }

    void
    clear_handle_range(const std::string& kind, int index_start, int index_end)
    {
        handle_env["Handle"]["clear_handle_range"](
            kind, index_start, index_end);
    }

    void merge_handles(const std::string& kind, sol::table handles)
    {
        handle_env["Handle"]["merge_handles"](kind, handles);
    }

    template <typename T>
    void relocate_handle(const T& source, const T& destination, int new_index)
    {
        handle_env["Handle"]["relocate_handle"](
            source, destination, new_index, T::lua_type());
    }

    template <typename T>
    void swap_handles(const T& obj_a, const T& obj_b)
    {
        handle_env["Handle"]["swap_handles"](obj_a, obj_b, T::lua_type());
    }

    template <typename T>
    void resolve_handle(T& obj)
    {
        auto handle = get_handle<T>(obj);
        if (handle != sol::lua_nil)
        {
            handle_env["Handle"]["set_ref"](handle, obj);
        }
    }


    void clear_all_handles();

    /***
     * Clears handles that are local to the current map without
     * running removal callbacks. Player and party character/item
     * handles are not cleared.
     */
    void clear_map_local_handles();

private:
    template <typename T>
    void create_handle(T& obj)
    {
        std::string uuid = boost::lexical_cast<std::string>(uuid_generator());
        handle_env["Handle"]["create_handle"](obj, T::lua_type(), uuid);
    }

    template <typename T>
    void remove_handle(T& obj)
    {
        handle_env["Handle"]["remove_handle"](obj, T::lua_type());
    }

    void bind(LuaEnv&);

    boost::uuids::random_generator uuid_generator;

    /***
     * The isolated Lua environment where the handles are stored and
     * managed.
     */
    sol::environment handle_env;

    LuaEnv* lua;
};

} // namespace lua
} // namespace elona
