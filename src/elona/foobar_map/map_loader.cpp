#include "map_loader.hpp"
#include "../../util/range.hpp"

#include <iostream>

namespace elona
{
namespace fmp
{

FoobarMap MapLoader::load(const fs::path& map_file)
{
    if (!fs::exists(map_file))
    {
        throw std::runtime_error(
            "Map file does not exist: " +
            filepathutil::make_preferred_path_in_utf8(map_file));
    }

    _map = {};

    _in = std::make_unique<zstr::ifstream>(filepathutil::make_preferred_path_in_utf8(map_file));

    char header[4];
    _in->read(header, 4);

    if (strncmp(header, "FMP ", 4) != 0)
    {
        throw std::runtime_error("Bad header");
    }

    _map.version = read_int();

    int mod_count = read_int();
    for (auto _i : range::iota<int>(mod_count))
    {
        _map.mods.emplace_back(read_string());
    }

    int mapping_count = read_int();
    for (auto _i : range::iota<int>(mapping_count))
    {
        std::string name = read_string();
        int id = read_int();
        _map.ids_to_names[id] = name;
    }

    _map.props = read_properties();

    _map.width = read_int();
    _map.height = read_int();

    _map.tiles = read_tiles();

    _map.layers = read_layers();

    return _map;
}

std::string MapLoader::read_string()
{
    std::string result;
    char ch;

    while ((ch = _in->get()))
    {
        result += ch;
        if (ch == '\0')
            break;
    }

    return result;
}

int MapLoader::read_int()
{
    int i;
    _in->read(reinterpret_cast<char*>(&i), sizeof(i));
    return i;
}

bool MapLoader::read_bool()
{
    char b;
    _in->read(&b, sizeof(b));
    return b == 1;
}

char MapLoader::read_char()
{
    char c;
    _in->read(&c, sizeof(c));
    return c;
}

SharedId MapLoader::read_mapped_name()
{
    auto i = read_int();
    auto it = _map.ids_to_names.at(i);
    return it;
}

FoobarMap::Properties MapLoader::read_properties()
{
    FoobarMap::Properties result;

    int property_count = read_int();
    for (auto _i : range::iota<int>(property_count))
    {
        SharedId key = read_mapped_name();
        FoobarMap::Property prop = read_property();
        result[key] = prop;
    }

    return result;
}

FoobarMap::Property MapLoader::read_property()
{
    FoobarMap::Property result;

    auto type = static_cast<FoobarMap::PropertyType>(read_char());

    switch (type)
    {
    case FoobarMap::PropertyType::int_type: result = read_int(); break;
    case FoobarMap::PropertyType::bool_type: result = read_bool(); break;
    case FoobarMap::PropertyType::string_type: result = read_string(); break;
    }

    return result;
}

std::vector<SharedId> MapLoader::read_tiles()
{
    std::vector<SharedId> result;

    for (auto _i : range::iota<int>(_map.width * _map.height))
    {
        result.emplace_back(read_mapped_name());
    }

    return result;
}

std::vector<FoobarMap::Layer> MapLoader::read_layers()
{
    std::vector<FoobarMap::Layer> result;

    int layer_count = read_int();
    for (auto _i : range::iota<int>(layer_count))
    {
        result.emplace_back(read_layer());
    }

    return result;
}

FoobarMap::Layer MapLoader::read_layer()
{
    FoobarMap::Layer result;

    result.id = read_int();
    result.type = static_cast<FoobarMap::Layer::Type>(read_int());
    result.name = read_string();
    result.props = read_properties();


    int count;

    switch (result.type)
    {
    case FoobarMap::Layer::Type::tile: break;
    case FoobarMap::Layer::Type::object:
        count = read_int();
        for (auto _i : range::iota<int>(count))
        {
            result.objects.emplace_back(read_object());
        }
        break;
    case FoobarMap::Layer::Type::group:
        count = read_int();
        for (auto _i : range::iota<int>(count))
        {
            result.child_layers.emplace_back(read_int());
        }
        break;
    case FoobarMap::Layer::Type::image: break;
    }

    return result;
}

FoobarMap::Object MapLoader::read_object()
{
    FoobarMap::Object result;

    result.data_id = read_mapped_name();
    result.data_type = read_mapped_name();
    result.name = read_mapped_name();
    result.x = read_int();
    result.y = read_int();
    result.props = read_properties();
    result.tile_props = read_properties();

    return result;
}

} // namespace fmp
} // namespace elona
