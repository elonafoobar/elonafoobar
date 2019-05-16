#include "init_map.hpp"
#include "../../util/stopwatch.hpp"
#include "../data/types/type_map_chip.hpp"
#include "../data/types/type_music.hpp"
#include "../lua_env/data_manager.hpp"
#include "../lua_env/interface.hpp"
#include "../lua_env/lua_env.hpp"
#include "../lua_env/wrapped_function.hpp"
#include "../map.hpp"
#include "../mapgen.hpp"
#include "../variables.hpp"
#include "foobar_map.hpp"
#include "map_loader.hpp"

namespace elona
{
namespace fmp
{

class PropertyPusherVisitor : public boost::static_visitor<>
{
public:
    PropertyPusherVisitor(const std::string& key, sol::table tbl)
        : _key(key)
        , _tbl(tbl)
    {
    }

    void operator()(const int& i)
    {
        _tbl[_key] = i;
    }

    void operator()(const std::string& str)
    {
        _tbl[_key] = str;
    }

    void operator()(const bool& b)
    {
        _tbl[_key] = b;
    }

private:
    std::string _key;
    sol::table _tbl;
};

mdata_t::MapType _get_map_type(FoobarMap& map)
{
    std::string map_type = map.props.get_or<std::string>("map_type", "");

    if (map_type == "world_map")
        return mdata_t::MapType::world_map;
    if (map_type == "guild")
        return mdata_t::MapType::guild;
    if (map_type == "town")
        return mdata_t::MapType::town;
    if (map_type == "field")
        return mdata_t::MapType::field;
    if (map_type == "player_owned")
        return mdata_t::MapType::player_owned;
    if (map_type == "shelter")
        return mdata_t::MapType::shelter;
    if (map_type == "temporary")
        return mdata_t::MapType::temporary;
    if (map_type == "dungeon")
        return mdata_t::MapType::dungeon;
    if (map_type == "dungeon_tower")
        return mdata_t::MapType::dungeon_tower;
    if (map_type == "dungeon_forest")
        return mdata_t::MapType::dungeon_forest;
    if (map_type == "dungeon_castle")
        return mdata_t::MapType::dungeon_castle;

    return mdata_t::MapType::field;
}

int _get_bgm(FoobarMap& map)
{
    auto id = map.props.get_optional<std::string>("bgm");

    if (!id)
        return 0;

    if (auto data = the_music_db[*id])
        return data->legacy_id;

    return 0;
}

sol::table _build_instantiator_args_table(
    const FoobarMap::Object& object,
    const std::string& layer_name)
{
    sol::table args = lua::create_table(
        "id",
        object.data_id.get(),
        "x",
        object.x,
        "y",
        object.y,
        "name",
        object.name,
        "layer_name",
        layer_name);

    sol::table props = lua::create_table();

    for (auto& pair : object.props)
    {
        auto v = PropertyPusherVisitor(pair.first, props);
        boost::apply_visitor(v, pair.second);
    }

    for (auto& pair : object.tile_props)
    {
        auto v = PropertyPusherVisitor(pair.first, props);
        boost::apply_visitor(v, pair.second);
    }

    props["is_updating"] = mapupdate == 1;

    args["props"] = props;

    return args;
}

static void _instantiate_map(FoobarMap& map)
{
    lib::Stopwatch watch;

    // clang-format off
    map_data.width                = map.width;
    map_data.height               = map.height;
    map_data.tileset              = map.props.get_or<int>("tileset", 0);
    map_data.atlas_number         = map.props.get<int>("atlas");
    map_data.next_regenerate_date = map.props.get<int>("next_regenerate_date");
    map_data.turn_cost            = map.props.get_or<int>("turn_cost", 10000);
    map_data.max_crowd_density    = map.props.get_or<int>("max_crowd_density", map_data.width * map_data.height / 100);
    map_data.user_map_flag        = 0;
    map_data.type                 = static_cast<int>(_get_map_type(map));
    map_data.refresh_type         = map.props.get_or<int>("refresh_type", 1);
    map_data.stair_up_pos         = map.props.get_or<int>("stair_up_pos", 0); // TODO make into map object
    map_data.stair_down_pos       = map.props.get_or<int>("stair_down_pos", 0); // TODO make into map object
    map_data.bgm                  = _get_bgm(map);
    map_data.indoors_flag         = map.props.get_or<bool>("is_indoors", true) ? 1 : 2;
    map_data.designated_spawns    = map.props.get_or<bool>("is_generated_every_time", false) ? 1 : 0;
    map_data.max_item_count       = map.props.get_or<int>("max_item_count", 400);
    map_data.play_campfire_sound  = map.props.get_or<bool>("play_campfire_sound", false) ? 1 : 0;
    map_data.should_regenerate    = map.props.get_or<bool>("should_regenerate", false) ? 0 : 1;
    map_data.refresh_type         = map.props.get_or<bool>("is_temporary", false) ? 0 : 1;
    // clang-format on

    map_initialize();

    ELONA_LOG("map.fmp") << "initialized map properties in " << watch.measure()
                         << "ms";

    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            auto id = map.tiles.at(y * map_data.width + x);
            auto legacy_id = chip_data.for_id(id);
            cell_data.at(x, y).chip_id_actual = legacy_id;
        }
    }

    ELONA_LOG("map.fmp") << "initialized " << (map_data.width * map_data.height)
                         << " map tiles in " << watch.measure() << "ms";

    auto exporters =
        *lua::lua->get_data_manager().get().get_table("core.tile_exporter");

    std::unordered_map<SharedId, lua::WrappedFunction> instantiators;
    int object_count = 0;

    for (const auto& layer : map.layers)
    {
        if (layer.type == FoobarMap::Layer::Type::object)
        {
            for (const auto& object : layer.objects)
            {
                if (instantiators.find(object.data_type) == instantiators.end())
                {
                    // TODO: lookup by "base" field across all exporters
                    sol::optional<sol::table> it =
                        exporters[object.data_type.get()];
                    if (!it)
                    {
                        throw std::runtime_error(
                            "No tile exporter registered for \"" +
                            object.data_type.get() + "\"");
                    }
                    instantiators[object.data_type] = lua::WrappedFunction(
                        object.data_type,
                        it->get<sol::protected_function>("instantiate"));
                }

                auto inst = instantiators.at(object.data_type);

                sol::table args =
                    _build_instantiator_args_table(object, layer.name);

                std::cerr << "load object " << object.data_type << " "
                          << object.data_id << std::endl;

                inst.call(args);

                object_count++;
            }
        }
    }

    ELONA_LOG("map.fmp") << "initialized " << object_count << " map objects in "
                         << watch.measure() << "ms";

    // TODO make into map objects
    mapstartx = map.props.get_or<int>("start_x", map_data.width / 2);
    mapstarty = map.props.get_or<int>("start_y", map_data.height / 2);
    map_placeplayer();

    ELONA_LOG("map.fmp") << "load complete";
}

void init_map(const std::string& map_name)
{
    auto map_file = (filesystem::dir::map() / (map_name + ".fmp"));

    ELONA_LOG("map.fmp") << "loading map file "
                         << filepathutil::make_preferred_path_in_utf8(map_file);

    auto map = MapLoader().load(map_file);

    _instantiate_map(map);
}

} // namespace fmp
} // namespace elona
