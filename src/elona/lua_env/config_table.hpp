#pragma once
#include "../../thirdparty/sol2/sol.hpp"
#include "../optional.hpp"
#include "../position.hpp"
#include "../shared_id.hpp"
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
    template <typename T, typename N>
    elona::optional<T> optional(const N& name) const
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

    template <typename T, typename N>
    T optional_or(const N& name, T default_) const
    {
        if (auto it = optional<T>(name))
            return *it;

        return default_;
    }

    template <typename T, typename N>
    T required(const N& name) const
    {
        elona::optional<T> it = optional<T>(name);

        if (!it)
        {
            throw std::runtime_error(
                id + ": Expected required field \"" + name + "\"");
        }

        return *it;
    }

    template <typename T, typename N>
    T enum_or(const N& name, const lua::EnumMap<T>& map, T default_value) const
    {
        auto value_ = optional<std::string>(name);
        if (value_)
        {
            // If the enum field is at least declared, fail loudly if it is not
            // found in the enum mapping.
            return map.ensure_from_string(*value_);
        }
        else
        {
            return default_value;
        }
    }

    template <typename T, typename N>
    std::vector<T> vector(const N& name) const
    {
        std::vector<T> result;

        if (auto it = optional<sol::table>(name))
        {
            for (const auto& kvp : *it)
            {
                T v = kvp.second.template as<T>();
                result.push_back(v);
            }
        }
        return result;
    }



    template <typename KeyType, typename ValueType, typename N>
    std::unordered_map<KeyType, ValueType> unordered_map(const N& name) const
    {
        std::unordered_map<KeyType, ValueType> result;

        if (auto it = optional<sol::table>(name))
        {
            for (const auto& kvp : *it)
            {
                result.emplace(
                    kvp.first.template as<KeyType>(),
                    kvp.second.template as<ValueType>());
            }
        }
        return result;
    }

    sol::table storage;
    std::string id;
};

} // namespace lua
} // namespace elona
