#pragma once
#include "../optional.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "export_manager.hpp"

namespace elona
{
namespace lua
{

/**
 * Wrapper around sol::table for easier obtaining of required/optional fields.
 */
class ConfigTable
{
public:
    ConfigTable(sol::table storage)
        : storage(storage)
        , id("<Lua table>")
    {
    }

    ConfigTable(sol::table storage, std::string id)
        : storage(storage)
        , id(id)
    {
    }

public:
    template <typename T>
    optional<T> get_optional(const std::string& name)
    {
        if (storage[name] == sol::lua_nil)
        {
            return none;
        }

        sol::optional<T> it = storage[name];

        if (!it)
        {
            return none;
        }

        return *it;
    }

    template <typename T>
    T get_required(const std::string& name)
    {
        optional<T> it = get_optional<T>(name);

        if (!it)
        {
            throw std::runtime_error(
                id + ": Expected required field \"" + name + "\"");
        }

        return *it;
    }

    optional<std::string> get_optional_callback(
        const std::string& name,
        lua::ExportManager& export_manager)
    {
        optional<std::string> callback_name = get_optional<std::string>(name);

        if (!callback_name)
        {
            return none;
        }

        if (!export_manager.has_function(*callback_name))
        {
            throw std::runtime_error(
                id + " (" + name + "): Unknown Lua callback " + *callback_name);
        }

        return *callback_name;
    }

private:
    sol::table storage;
    std::string id;
};

} // namespace lua
} // namespace elona
