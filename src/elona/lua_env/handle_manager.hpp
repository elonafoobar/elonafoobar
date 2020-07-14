#pragma once

#include <set>

#include "../../util/noncopyable.hpp"
#include "../character.hpp"
#include "lua_submodule.hpp"



namespace elona
{

struct Character;



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

    /***
     * Removes an existing handle in the isolated handle environment.
     *
     * If the handle doesn't exist in this manager's handle list, handle_set
     * is checked that the handle is invalid.
     */
    void remove_chara_handle(Character& chara);


    /***
     * Methods that will create/remove handles as well as run
     * creation/removal event callbacks using the event manager
     * instance.
     */
    void create_chara_handle_run_callbacks(Character&);
    void remove_chara_handle_run_callbacks(Character&);


    /***
     * Looks up the C++ reference that a handle points to. Will throw
     * if the handle is invalid or of the wrong type.
     */
    sol::optional<Character&> get_ref(sol::table handle)
    {
        sol::object obj =
            env()["Handle"]["get_ref"](handle, Character::lua_type());
        if (obj == sol::lua_nil)
        {
            return sol::nullopt;
        }
        return obj.as<Character&>();
    }

    bool handle_is_valid(sol::table handle)
    {
        return env()["Handle"]["is_valid"](handle);
    }


    /***
     * Provides a Lua reference to a handle from the isolated handle
     * environment.
     */
    sol::table get_handle(const Character& obj)
    {
        sol::object handle = env()["Handle"]["get_handle"](
            pointer_arg(obj), Character::lua_type());
        if (!handle.is<sol::table>())
        {
            return sol::lua_nil;
        }
        return handle;
    }


    void merge_handles(const std::string& kind, sol::table handles)
    {
        env()["Handle"]["merge_handles"](kind, handles);
    }

    void relocate_handle(Character& source, Character& destination)
    {
        env()["Handle"]["relocate_handle"](
            source,
            pointer_arg(source),
            destination,
            pointer_arg(destination),
            Character::lua_type());
    }

    void swap_handles(Character& obj_a, Character& obj_b)
    {
        env()["Handle"]["swap_handles"](obj_a, obj_b, Character::lua_type());
    }

    void resolve_handle(Character& obj)
    {
        auto handle = get_handle(obj);
        if (handle != sol::lua_nil)
        {
            env()["Handle"]["set_ref"](handle, obj);
        }
    }


    void clear_all_handles();

    /***
     * Clears handles that are local to the current map without
     * running removal callbacks. Player and party character
     * handles are not cleared.
     */
    void clear_map_local_handles();

private:
    void create_handle(Character& obj)
    {
        const auto new_id = ObjId::generate();
        obj.obj_id = new_id;
        env()["Handle"]["create_handle"](
            obj, pointer_arg(obj), Character::lua_type(), new_id.to_string());
    }

    void remove_handle(Character& obj)
    {
        env()["Handle"]["remove_handle"](
            obj, pointer_arg(obj), Character::lua_type());
        obj.obj_id = ObjId::nil();
    }


    int64_t pointer_arg(const Character& obj)
    {
        static_assert(sizeof(Character*) <= sizeof(int64_t));
        return reinterpret_cast<int64_t>(std::addressof(obj));
    }
};

} // namespace lua
} // namespace elona
