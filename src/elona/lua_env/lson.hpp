#pragma once

#include "../../thirdparty/sol2/sol.hpp"
#include "../filesystem.hpp"



namespace elona
{
namespace lua
{
namespace lson
{

struct Value
{
    Value(sol::table table)
        : _table(table)
    {
    }



    template <typename T>
    sol::optional<T> get(const std::string& key)
    {
        return _table[key];
    }



    template <typename K, typename V>
    auto get_table(const std::string& key)
        -> sol::optional<std::unordered_map<K, V>>
    {
        using Map = std::unordered_map<K, V>;

        sol::optional<sol::table> table = _table[key];
        if (table)
        {
            Map ret;
            for (const auto& kvp : *table)
            {
                sol::optional<K> key = kvp.first.as<sol::optional<K>>();
                sol::optional<V> value = kvp.second.as<sol::optional<V>>();
                if (key && value)
                {
                    ret.insert(std::make_pair(*key, *value));
                }
                else
                {
                    return sol::nullopt;
                }
            }
            return ret;
        }
        else
        {
            return sol::nullopt;
        }
    }



private:
    sol::table _table;
};



inline Value parse_file(const fs::path& path);

} // namespace lson
} // namespace lua
} // namespace elona
