#include "tsx_exporter.hpp"

#include <boost/gil/extension/io/png/write.hpp>
#include <boost/gil/image.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "../../util/strutil.hpp"
#include "../lua_env/data_manager.hpp"
#include "../lua_env/lua_env.hpp"
#include "../macro.hpp"

namespace elona
{
namespace fmp
{

namespace bg = boost::gil;
namespace pt = boost::property_tree;
using namespace std::literals::string_literals;

static int _table_length(sol::table t)
{
    int i = 0;
    for (const auto kvp : t)
    {
        UNUSED(kvp);
        i++;
    }
    return i;
}

optional<TsxExporter::TileSource> TsxExporter::get_source(
    const std::string& type,
    const std::string& data_id,
    sol::table tbl)
{
    sol::optional<sol::table> source_table = tbl["source"];
    if (source_table)
    {
        fs::path atlas_path =
            filesystem::resolve_path_for_mod(tbl.get<std::string>("atlas"));
        std::string atlas_path_str =
            filepathutil::make_preferred_path_in_utf8(atlas_path);

        auto it = _cache.find(atlas_path_str);
        if (it == _cache.end())
        {
            _cache.emplace(
                atlas_path_str,
                snail::Surface{atlas_path,
                               snail::Color{0, 0, 0},
                               snail::Surface::Format::argb8888});
            it = _cache.find(atlas_path_str);
            assert(it != _cache.end());
        }

        std::string mod_id, name;
        std::tie(mod_id, name) = strutil::split_on_string(data_id, ".");
        fs::path cache_dir = _filename.parent_path() / "cache" / type / mod_id;

        fs::create_directories(cache_dir);

        bool tall = tbl.get_or("tall", false);
        int width = 48;
        int height = tall ? 96 : 48;
        int x = source_table->get<int>("x");
        int y = source_table->get<int>("y");

        auto& atlas_image = it->second;

        bg::bgra8_pixel_t* p =
            reinterpret_cast<bg::bgra8_pixel_t*>(atlas_image.pixels());

        bg::bgra8_view_t view = bg::interleaved_view(
            atlas_image.width(),
            atlas_image.height(),
            p,
            atlas_image.width() * sizeof(bg::bgra8_pixel_t));
        auto cropped_view = bg::subimage_view(view, x, y, width, height);

        std::string cache_file = filepathutil::make_preferred_path_in_utf8(
            cache_dir / (name + ".png"));
        bg::write_view(cache_file, cropped_view, bg::png_tag{});

        return TileSource{width, height, cache_file};
    }

    sol::optional<std::string> source_str = tbl["source"];
    if (source_str)
    {
        fs::path full_path = filesystem::resolve_path_for_mod(*source_str);
        snail::Surface tile(full_path);
        return TileSource{tile.width(),
                          tile.height(),
                          filepathutil::make_preferred_path_in_utf8(full_path)};
    }

    return none;
}

void TsxExporter::open_tsx(const std::string& type)
{
    if (_opened)
    {
        throw std::runtime_error("Already opened");
    }

    auto table = lua::lua->get_data_manager().get().get_table(type);

    if (!table)
    {
        throw std::runtime_error("No such type \"" + type + "\"");
    }

    auto exporters =
        *lua::lua->get_data_manager().get().get_table("core.tile_exporter");

    sol::optional<sol::table> it = exporters[type];
    if (!it)
    {
        throw std::runtime_error(
            "No tile exporter registered for \"" + type + "\"");
    }

    _exporter = it->get<sol::protected_function>("export");

    _tree = {};

    pt::ptree& attrs = _tree.put_child("tileset.<xmlattr>", {});
    attrs.put("version", "1.2");
    attrs.put("tiledversion", "1.2.3");
    attrs.put("name", type);
    attrs.put("tilewidth", 48);
    attrs.put("tileheight", 48);
    attrs.put("tilecount", _table_length(*table));
    attrs.put("columns", 8);

    pt::ptree grid = _tree.add("tileset.grid", "");
    grid.add("<xmlattr>.orientation", "orthogonal");
    grid.add("<xmlattr>.width", 1);
    grid.add("<xmlattr>.height", 1);

    _opened = true;
    _id = 0;
    _type = type;
    _table = *table;
}


void TsxExporter::write_tile(const std::string& data_id)
{
    if (!_opened)
    {
        throw std::runtime_error("Not opened");
    }

    sol::optional<sol::table> val = _table[data_id];

    if (!val)
    {
        throw std::runtime_error(
            "No such data \"" + _type + "#" + data_id + "\"");
    }

    auto result = _exporter(*val);
    if (!result.valid())
    {
        sol::error err = result;
        throw err;
    }

    sol::table result_tbl = result;
    auto source = get_source(_type, data_id, result_tbl);
    if (!source)
    {
        throw std::runtime_error(
            "Cannot determine tile source of \"" + _type + "#" + data_id +
            "\"");
    }

    pt::ptree& tile = _tree.add("tileset.tile", "");
    tile.add("<xmlattr>.id", _id);
    tile.add("<xmlattr>.type", _type);

    pt::ptree& properties = tile.add("properties", "");
    pt::ptree& property = properties.add("property", "");

    property.add("<xmlattr>.name", "data_id");
    property.add("<xmlattr>.value", data_id);

    pt::ptree& image = tile.add("image", "");
    image.put("<xmlattr>.width", source->width);
    image.put("<xmlattr>.height", source->height);
    image.put("<xmlattr>.trans", "000000");
    image.put("<xmlattr>.source", source->filename);

    _id++;
}

void TsxExporter::close_tsx()
{
    if (!_opened)
    {
        throw std::runtime_error("Not opened");
    }

    pt::write_xml(
        filepathutil::make_preferred_path_in_utf8(_filename),
        _tree,
        std::locale(),
        pt::xml_writer_settings<std::string>(' ', 4));

    _opened = false;
}

void export_tsx(const std::string& type, const fs::path& filename)
{
    auto table = *lua::lua->get_data_manager().get().get_table(type);

    auto exporter = TsxExporter(filename);
    exporter.open_tsx(type);

    for (const auto kvp : table)
    {
        exporter.write_tile(kvp.first.as<std::string>());
    }

    exporter.close_tsx();
}

} // namespace fmp
} // namespace elona
