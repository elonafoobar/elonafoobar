#pragma once
#include <string>
#include <unordered_map>
#include "../element.hpp"
#include "../enums.hpp"
#include "../log.hpp"
#include "../map_cell.hpp"
#include "../status_ailment.hpp"

namespace elona
{
namespace lua
{

template <typename T>
class enum_map
{
    using map_type = std::unordered_map<std::string, T>;

public:
    enum_map(map_type storage)
        : storage(storage)
    {
    }

public:
    T get_from_string(const std::string& key, T default_val)
    {
        auto it = storage.find(key);
        if (it == storage.end())
        {
            ELONA_LOG("Enum value " << key << " not found, using default");
            return default_val;
        }

        return *it;
    }

private:
    map_type storage;
};

extern enum_map<damage_source_t> DamageSource;
extern enum_map<color_index_t> Color;
extern enum_map<identification_state_t> IdentifyState;
extern enum_map<status_ailment_t> StatusAilment;
extern enum_map<element_t> Element;
extern enum_map<tile_kind_t> TileKind;
// extern enum_map<chara_flag_t> CharaFlag;
// extern enum_map<item_flag_t> ItemFlag;
// extern enum_map<gender_t> Gender;
// extern enum_map<relation_t> Relation;

} // namespace lua
} // namespace elona
