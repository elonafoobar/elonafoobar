#include "mod_serializer.hpp"
#include "../character.hpp"
#include "../item.hpp"

namespace elona
{
namespace lua
{

std::pair<int, int> get_start_end_indices(
    const std::string& kind,
    ModEnv::StoreType store_type)
{
    if (kind == Character::lua_type())
    {
        switch (store_type)
        {
        case ModEnv::StoreType::global: return {0, ELONA_MAX_PARTY_CHARACTERS};
        case ModEnv::StoreType::map:
            return {ELONA_MAX_PARTY_CHARACTERS, ELONA_MAX_CHARACTERS};
        }
    }
    else if (kind == Item::lua_type())
    {
        switch (store_type)
        {
        case ModEnv::StoreType::global:
            return {0, ELONA_OTHER_INVENTORIES_INDEX};
        case ModEnv::StoreType::map:
            return {ELONA_OTHER_INVENTORIES_INDEX, ELONA_MAX_ITEMS};
        }
    }

    assert(false);
    return {0, 0};
}

std::string get_store_name(ModEnv::StoreType store_type)
{
    switch (store_type)
    {
    case ModEnv::StoreType::map: return "map local";
    case ModEnv::StoreType::global: return "global";
    }

    assert(false);
    return "";
}

} // namespace lua
} // namespace elona
