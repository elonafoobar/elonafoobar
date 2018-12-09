#include "interface.hpp"
#include "config_table.hpp"
#include "data_manager.hpp"



namespace elona
{
namespace lua
{

optional<ConfigTable> data(const char* type, const std::string& id)
{
    if (auto table = lua::lua->get_data_manager().get().raw(type, id))
    {
        return ConfigTable(*table);
    }
    return none;
}



optional<ConfigTable> data(const char* type, int legacy_id)
{
    if (auto id = lua::lua->get_data_manager().get().by_legacy(type, legacy_id))
    {
        return data(type, *id);
    }

    return none;
}

} // namespace lua
} // namespace elona
