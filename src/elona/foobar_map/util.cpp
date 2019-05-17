#include "util.hpp"
#include "../lua_env/data_manager.hpp"
#include "../lua_env/lua_env.hpp"

using namespace std::literals::string_literals;

namespace elona
{
namespace fmp
{


/**
 * Finds an instance of core.tile_exporter by comparing the "base" field with @a
 * type. It will find the last inserted tileset exporter defined if more than
 * one is found.
 */
sol::table get_tile_exporter(const std::string& type)
{
    auto data = lua::lua->get_data_manager().get();
    auto exporters = *data.get_table("core.tile_exporter");
    auto order = *data.get_by_order_table("core.tile_exporter");
    sol::optional<sol::table> exporter;

    for (const auto kvp : order)
    {
        sol::table entry = exporters[kvp.second];
        const auto base = entry.get_or("base"s, ""s);
        if (base == type)
        {
            exporter = entry;
        }
    }
    if (!exporter)
    {
        throw std::runtime_error(
            "No tile exporter registered for \"" + type + "\"");
    }

    return *exporter;
}

} // namespace fmp
} // namespace elona
