#pragma once

#include "../../handle_manager.hpp"
#include "../common.hpp"



namespace elona::lua::api::classes
{

/**
 * Userdata object used to validate the handle reference it was created from.
 * For example, when a skill reference is retrieved from a character, it can be
 * tested for validity by calling Handle.is_valid() against inner object ID. If
 * it has gone out of date, any method calls on the reference can be safely
 * ignored.
 */
template <typename T>
struct LuaRef
{
    ObjId obj_id;



    LuaRef() = default;


    LuaRef(const ObjId& obj_id)
        : obj_id(obj_id)
    {
    }



    bool is_valid() const
    {
        auto h = make_handle();
        return lua::lua->get_handle_manager().handle_is_valid(h);
    }


    decltype(auto) get_ref()
    {
        auto h = make_handle();
        return lua::lua->get_handle_manager().get_ref(h);
    }



private:
    sol::table make_handle() const
    {
        auto handle = lua::lua->get_state()->create_table();
        handle["__kind"] = T::lua_type();
        handle["__uuid"] = obj_id.to_string();
        handle["__handle"] = true;
        return handle;
    }
};

} // namespace elona::lua::api::classes
