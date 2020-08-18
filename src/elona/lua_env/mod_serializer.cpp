#include "mod_serializer.hpp"

#include "../character.hpp"
#include "../item.hpp"

namespace elona
{
namespace lua
{

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
