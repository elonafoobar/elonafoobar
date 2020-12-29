#include "interface.hpp"

#include "../item.hpp"
#include "config_table.hpp"
#include "data_manager.hpp"
#include "mod_manager.hpp"



namespace elona
{
namespace lua
{

optional<ConfigTable> get_data(
    data::PrototypeId prototype_id,
    data::InstanceId instance_id)
{
    if (auto table =
            lua->get_data_manager().get().raw(prototype_id, instance_id))
    {
        return ConfigTable(*table);
    }
    return none;
}



optional<ConfigTable> get_data(
    data::PrototypeId prototype_id,
    int integer_instance_id)
{
    if (auto id = lua->get_data_manager().get().by_integer(
            prototype_id, integer_instance_id))
    {
        return get_data(prototype_id, *id);
    }

    return none;
}



fs::path resolve_path_for_mod(const std::string& path)
{
    return lua->get_mod_manager().resolve_path_for_mod(path);
}



std::vector<fs::path> all_mod_dirs(const fs::path& base_dir)
{
    std::vector<fs::path> result;
    // E.g., lomias-1.2.3
    for (const auto& entry : filesystem::glob_dirs(
             base_dir, std::regex{R"([a-z][a-z0-9_]+-[0-9]\.[0-9]\.[0-9])"}))
    {
        if (fs::exists(entry.path() / "mod.json"))
        {
            result.push_back(entry.path());
        }
    }
    return result;
}

} // namespace lua
} // namespace elona
