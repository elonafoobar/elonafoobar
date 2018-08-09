#pragma once
#include <string>
#include <unordered_map>
#include "../element.hpp"
#include "../enums.hpp"
#include "../log.hpp"
#include "../map_cell.hpp"
#include "../optional.hpp"
#include "../status_ailment.hpp"

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
            if (pair->second == val)
            {
                return pair->first;
            }
        }

        assert(false);
        return "";
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

        return *it;
    }

    T ensure_from_string(const std::string& key)
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            throw std::runtime_error(
                "Enum value " + key + " for " + name + " not found.");
        }

        return *it;
    }

private:
    std::string name;
    map_type storage;
};

namespace enums
{
extern enum_map<damage_source_t> DamageSource;
extern enum_map<color_index_t> Color;
extern enum_map<curse_state_t> CurseState;
extern enum_map<identification_state_t> IdentifyState;
extern enum_map<status_ailment_t> StatusAilment;
extern enum_map<element_t> Element;
extern enum_map<tile_kind_t> TileKind;
extern enum_map<int> Gender;
extern enum_map<int> Relation;
extern enum_map<int> CharaFlag;
} // namespace enums

} // namespace lua
} // namespace elona
