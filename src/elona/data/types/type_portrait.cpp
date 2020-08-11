#include "type_portrait.hpp"

#include <iostream>

#include "../../lua_env/interface.hpp"



namespace
{

constexpr int _default_portrait_width = 80;
constexpr int _default_portrait_height = 112;

} // namespace



namespace elona
{

PortraitDB the_portrait_db;



const constexpr char* data::DatabaseTraits<_PortraitDBBase>::type_id;


PortraitData _PortraitDBBase::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    int x = 0;
    int y = 0;
    int width = _default_portrait_width;
    int height = _default_portrait_height;

    optional<fs::path> filepath = none;

    auto source = data.required<sol::object>("source");
    if (source.is<sol::table>())
    {
        sol::table source_from_atlas = source;
        x = source_from_atlas["x"];
        y = source_from_atlas["y"];
        width = source_from_atlas.get_or("width", width);
        height = source_from_atlas.get_or("height", height);
    }
    else
    {
        std::string filepath_str = source.as<std::string>();
        filepath = lua::resolve_path_for_mod(filepath_str);
        if (!fs::exists(*filepath))
        {
            throw std::runtime_error(
                id + ": Image file doesn't exist: " + filepath->to_u8string());
        }
    }

    return PortraitData{
        data::InstanceId{id},
        SharedId{std::string(Traits::type_id) + data_id_separator + id},
        Extent{x, y, width, height},
        filepath,
    };
}



std::string PortraitDB::get_next_portrait(const std::string& current)
{
    if (sorted_portrait_table.empty())
    {
        // No portraits loaded.
        return "";
    }

    const auto itr = sorted_portrait_table.find(current);
    if (itr == std::end(sorted_portrait_table))
    {
        // Not found; returns the current value.
        return current;
    }

    const auto next = std::next(itr, 1);
    if (next == std::end(sorted_portrait_table))
    {
        // Reached the end; loops back to the beginning.
        return *std::begin(sorted_portrait_table);
    }
    else
    {
        return *next;
    }
}



std::string PortraitDB::get_previous_portrait(const std::string& current)
{
    if (sorted_portrait_table.empty())
    {
        // No portraits loaded.
        return "";
    }

    const auto itr = sorted_portrait_table.find(current);
    if (itr == std::end(sorted_portrait_table))
    {
        // Not found; returns the current value.
        return current;
    }

    if (itr == std::begin(sorted_portrait_table))
    {
        // Reached the beginning; loops back to the end.
        return *std::prev(std::end(sorted_portrait_table), 1);
    }
    else
    {
        return *std::prev(itr, 1);
    }
}



void PortraitDB::cache_sorted_portrait_table()
{
    for (const auto& pair : *this)
    {
        sorted_portrait_table.insert(pair.first.get());
    }
}

} // namespace elona
