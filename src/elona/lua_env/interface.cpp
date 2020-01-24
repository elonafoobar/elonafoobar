#include "interface.hpp"
#include "config_table.hpp"
#include "data_manager.hpp"
#include "mod_manager.hpp"



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



fs::path resolve_path_for_mod(const std::string& path)
{
    return lua::lua->get_mod_manager().resolve_path_for_mod(path);
}

} // namespace lua
} // namespace elona
