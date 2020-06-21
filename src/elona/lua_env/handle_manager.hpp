#pragma once

#include <set>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../../util/noncopyable.hpp"
#include "../eobject/eobject.hpp"
#include "lua_submodule.hpp"



namespace elona
{

struct Character;
struct Item;



namespace lua
{



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
 * See data/script/kernel/handle.lua for more information.
 */
class HandleManager : public LuaSubmodule
{
public:
    explicit HandleManager(LuaEnv&);

    /***
     * Creates a new handle in the isolated handle environment.
     *
     * If the handle already exists, handle_set is instead checked for
     * validity.
     */
    void create_chara_handle(Character& chara);
    void create_item_handle(Item& item);

    /***
     * Removes an existing handle in the isolated handle environment.
     *
     * If the handle doesn't exist in this manager's handle list, handle_set
     * is checked that the handle is invalid.
     */
    void remove_chara_handle(Character& chara);
    void remove_item_handle(Item& item);


    /***
     * Methods that will create/remove handles as well as run
     * creation/removal event callbacks using the event manager
     * instance.
     */
    void create_chara_handle_run_callbacks(Character&);
    void create_item_handle_run_callbacks(Item&);
    void remove_chara_handle_run_callbacks(Character&);
    void remove_item_handle_run_callbacks(Item&);


    /***
     * Looks up the C++ reference that a handle points to. Will throw
     * if the handle is invalid or of the wrong type.
     */
    template <typename T>
    sol::optional<T&> get_ref(sol::table handle)
    {
        sol::object obj = env()["Handle"]["get_ref"](handle, T::lua_type());
        if (obj == sol::lua_nil)
        {
            return sol::nullopt;
        }
        return obj.as<T&>();
    }

    template <typename T>
    bool handle_is(sol::table handle)
    {
        return handle["__kind"] == T::lua_type();
    }

    bool handle_is_valid(sol::table handle)
    {
        return env()["Handle"]["is_valid"](handle);
    }


    /***
     * Provides a Lua reference to a handle from the isolated handle
     * environment.
     */
    sol::table get_handle(int index, std::string type)
    {
        if (index < 0)
        {
            return sol::lua_nil;
        }

        sol::object handle = env()["Handle"]["get_handle"](index, type);
        if (!handle.is<sol::table>())
        {
            return sol::lua_nil;
        }
        return handle;
    }

    /***
     * Provides a Lua reference to a handle from the isolated handle
     * environment.
     */
    template <typename T>
    sol::table get_handle(T& obj)
    {
        if constexpr (std::is_same_v<std::remove_cv_t<T>, Item>)
        {
            return get_handle(obj.index(), T::lua_type());
        }
        else
        {
            return get_handle(obj.index, T::lua_type());
        }
    }


    void
    clear_handle_range(const std::string& kind, int index_start, int index_end)
    {
        env()["Handle"]["clear_handle_range"](kind, index_start, index_end);
    }

    void merge_handles(const std::string& kind, sol::table handles)
    {
        env()["Handle"]["merge_handles"](kind, handles);
    }

    template <typename T>
    void relocate_handle(T& source, T& destination, int new_index)
    {
        env()["Handle"]["relocate_handle"](
            source, destination, new_index, T::lua_type());
    }

    template <typename T>
    void swap_handles(T& obj_a, T& obj_b)
    {
        env()["Handle"]["swap_handles"](obj_a, obj_b, T::lua_type());
    }

    template <typename T>
    void resolve_handle(T& obj)
    {
        auto handle = get_handle<T>(obj);
        if (handle != sol::lua_nil)
        {
            env()["Handle"]["set_ref"](handle, obj);
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
        const auto new_id = ObjId::generate();
        obj.obj_id = new_id;
        env()["Handle"]["create_handle"](
            obj, T::lua_type(), new_id.to_string());
    }

    template <typename T>
    void remove_handle(T& obj)
    {
        env()["Handle"]["remove_handle"](obj, T::lua_type());
        obj.obj_id = ObjId::nil();
    }
};

} // namespace lua
} // namespace elona
