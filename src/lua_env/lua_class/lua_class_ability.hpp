#pragma once
#include "../lua_api/lua_api_common.hpp"

namespace elona
{
namespace lua
{

/**
 * Userdata object used to validate the handle reference it was created from.
 * For example, when a skill reference is retrieved from a character, it can be
 * tested for validity by comparing the UUID of the reference to that of the
 * handle corresponding to the index on the reference. If they don't match, then
 * the handle is out of date and any method calls on the reference can be safely
 * ignored.
 */
struct LuaRef
{
    LuaRef()
        : index(-1)
        , type("")
        , uuid("")
    {
    }

    LuaRef(int index, std::string type, std::string uuid)
        : index(index)
        , type(type)
        , uuid(uuid)
    {
    }

    bool is_valid()
    {
        if (index == -1)
        {
            return false;
        }

        auto handle = lua::lua->get_handle_manager().get_handle(index, type);
        if (handle == sol::lua_nil)
        {
            return false;
        }

        std::string handle_uuid = handle["__uuid"];
        return handle_uuid == uuid;
    }

    int index;
    std::string type;
    std::string uuid;
};

struct LuaAbility : LuaRef
{
    LuaAbility(int skill_id_, int index, std::string type, std::string uuid)
        : LuaRef(index, type, uuid)
    {
        skill_id = skill_id_;
    }

    static void bind(sol::state& lua);

    int skill_id;
};

} // namespace lua
} // namespace elona
