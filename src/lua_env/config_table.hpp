#pragma once
#include "../optional.hpp"
#include "../shared_id.hpp"
#include "../thirdparty/sol2/sol.hpp"
#include "lua_enums.hpp"

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

    ConfigTable(sol::table storage, SharedId id)
        : storage(storage)
        , id(id.get())
    {
    }

public:
    template <typename T>
    elona::optional<T> optional(const std::string& name) const
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
    T optional_or(const std::string& name, T default_) const
    {
        if (auto it = optional<T>(name))
            return *it;

        return default_;
    }

    template <typename T>
    T required(const std::string& name) const
    {
        elona::optional<T> it = optional<T>(name);

        if (!it)
        {
            throw std::runtime_error(
                id + ": Expected required field \"" + name + "\"");
        }

        return *it;
    }

    template <typename T>
    T required(const char* name) const
    {
        return required<T>(std::string(name));
    }

    template <typename T>
    T enum_or(const char* name, const lua::EnumMap<T>& map, T default_value)
        const
    {
        auto value_ = optional<std::string>(name);
        if (value_)
        {
            return map.get_from_string(*value_, default_value);
        }
        else
        {
            return default_value;
        }
    }

    template <typename T>
    std::vector<T> vector(const char* name) const
    {
        std::vector<T> result;

        if (auto it = optional<sol::table>(name))
        {
            for (const auto& kvp : *it)
            {
                T v = kvp.second.as<T>();
                result.push_back(v);
            }
        }
        return result;
    }

private:
    sol::table storage;
    std::string id;
};

} // namespace lua
} // namespace elona
