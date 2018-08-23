#pragma once
#include <string>
#include <unordered_map>
#include "../element.hpp"
#include "../enums.hpp"
#include "../log.hpp"
#include "../map_cell.hpp"
#include "../optional.hpp"
#include "../status_ailment.hpp"
#include "../thirdparty/sol2/sol.hpp"

namespace elona
{
namespace lua
{

typedef std::string enum_string;

template <typename T>
class enum_map
{
    using map_type = std::unordered_map<std::string, T>;

public:
    enum_map(std::string name, map_type storage)
        : name(name)
        , storage(storage)
    {
    }

public:
    enum_string convert_to_string(T val)
    {
        for (const auto& pair : storage)
        {
            if (pair.second == val)
            {
                return pair.first;
            }
        }

        assert(false);
        return "<invalid enum>";
    }

    T get_from_string(const std::string& key, T default_val)
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            ELONA_LOG(
                "Enum value " << key << " for " << name
                              << " not found, using default");
            return default_val;
        }

        return it->second;
    }

    T ensure_from_string(const std::string& key)
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
    map_type storage;
};

namespace LuaEnums
{
extern enum_map<DamageSource> DamageSourceTable;
extern enum_map<ColorIndex> ColorIndexTable;
extern enum_map<CurseState> CurseStateTable;
extern enum_map<IdentifyState> IdentifyStateTable;
extern enum_map<StatusAilment> StatusAilmentTable;
extern enum_map<Element> ElementTable;
extern enum_map<TileKind> TileKindTable;
extern enum_map<int> GenderTable;
extern enum_map<int> RelationTable;
extern enum_map<int> CharaFlagTable;

void bind(sol::table&);
} // namespace LuaEnums

} // namespace lua
} // namespace elona
