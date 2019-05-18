#pragma once
#include <string>
#include <unordered_map>
#include "../../thirdparty/sol2/sol.hpp"
#include "../log.hpp"
#include "../optional.hpp"

namespace elona
{
namespace lua
{

using EnumString = std::string;

template <typename T>
class EnumMap
{
    using MapType = std::unordered_map<std::string, T>;

public:
    EnumMap(std::string name, MapType storage)
        : name(name)
        , storage(storage)
    {
    }

public:
    EnumString convert_to_string(T val) const
    {
        for (const auto& pair : storage)
        {
            if (pair.second == val)
            {
                return pair.first;
            }
        }

        throw std::runtime_error("Could not convert a value of type " + name);
        return "<invalid enum>";
    }

    T get_from_string(const std::string& key, T default_val) const
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            ELONA_WARN("lua.enum") << "Enum value " << key << " for " << name
                                   << " not found, using default";
            return default_val;
        }

        return it->second;
    }

    T ensure_from_string(const std::string& key) const
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            throw std::runtime_error(
                "Enum value " + key + " for " + name + " not found.");
        }

        return it->second;
    }

    void bind(sol::table& Enums)
    {
        sol::table enum_table = Enums.create();
        for (const auto& pair : storage)
        {
            // Enum values will always be strings in Lua.
            // Enums.EnumName.EnumMember = "EnumMember"
            enum_table.set(pair.first, pair.first);
        }

        // Make the enums table read-only. Taken from sol::table.new_enum.
        sol::table metatable = Enums.create_with(
            sol::meta_function::new_index,
            sol::detail::fail_on_newindex,
            sol::meta_function::index,
            enum_table);

        Enums.create_named(name, sol::metatable_key, metatable);
    }

private:
    std::string name;
    MapType storage;
};

} // namespace lua
} // namespace elona
