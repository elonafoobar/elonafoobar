#pragma once

#include <string>
#include <unordered_map>

#include "../../thirdparty/sol2/sol.hpp"
#include "../log.hpp"



namespace elona
{
namespace lua
{

using EnumString = std::string;



template <typename T>
class EnumMap
{
private:
    using MapType = std::unordered_map<EnumString, T>;



public:
    EnumMap(std::string name, MapType storage)
        : name(name)
        , storage(storage)
    {
    }



    const EnumString& convert_to_string(T val) const
    {
        for (const auto& pair : storage)
        {
            if (pair.second == val)
            {
                return pair.first;
            }
        }

        throw std::runtime_error("Could not convert a value of type " + name);
    }



    T get_from_string(const EnumString& key, T default_val) const
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



    T ensure_from_string(const EnumString& key) const
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            throw std::runtime_error(
                "Enum value " + key + " for " + name + " not found.");
        }

        return it->second;
    }



private:
    std::string name;
    MapType storage;
};

} // namespace lua
} // namespace elona
