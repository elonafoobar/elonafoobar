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

static sol::table _make_opts_table(
    const std::unordered_map<std::string, std::string> opts)
{
    sol::table result = lua::lua->get_state()->create_table();
    for (const auto kvp : opts)
    {
        result[kvp.first] = kvp.second;
    }
    return result;
}

static void _add_properties(pt::ptree& properties, sol::table tbl)
{
    for (const auto kvp : tbl)
    {
        pt::ptree& property = properties.add("property", "");
        property.add("<xmlattr>.name", kvp.first.as<std::string>());
        property.add("<xmlattr>.value", kvp.second.as<std::string>());
    }
}

TsxExporter::TileSource TsxExporter::crop_atlas_source(
    const std::string& type,
    const std::string& data_id,
    sol::table result_tbl,
    sol::table source_tbl)
{
    fs::path atlas_path =
        filesystem::resolve_path_for_mod(result_tbl.get<std::string>("atlas"));
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

    if (auto name_opt =
            result_tbl.get<sol::optional<std::string>>("image_name"))
    {
        name = *name_opt;
    }

    fs::create_directories(cache_dir);

    bool tall = result_tbl.get_or("tall", false);
    int width = 48;
    int height = tall ? 96 : 48;
    int x = source_tbl.get<int>("x");
    int y = source_tbl.get<int>("y");

    auto& atlas_image = it->second;

    bg::bgra8_pixel_t* p =
        reinterpret_cast<bg::bgra8_pixel_t*>(atlas_image.pixels());

    bg::bgra8_view_t view = bg::interleaved_view(
        atlas_image.width(),
        atlas_image.height(),
        p,
        atlas_image.width() * sizeof(bg::bgra8_pixel_t));
    auto cropped_view = bg::subimage_view(view, x, y, width, height);

    // TODO: y offset

    std::string cache_file =
        filepathutil::make_preferred_path_in_utf8(cache_dir / (name + ".png"));
    bg::write_view(cache_file, cropped_view, bg::png_tag{});

    return TileSource{width, height, cache_file, sol::nullopt};
}

TsxExporter::TileSource TsxExporter::get_file_source(
    const std::string& source_str)
{
    fs::path full_path = filesystem::resolve_path_for_mod(source_str);
    snail::Surface tile(full_path);
    return TileSource{tile.width(),
                      tile.height(),
                      filepathutil::make_preferred_path_in_utf8(full_path),
                      sol::nullopt};
}

optional<TsxExporter::TileSource> TsxExporter::get_source(
    const std::string& type,
    const std::string& data_id,
    sol::table tbl)
{
    sol::optional<sol::table> source_table = tbl["source"];
    if (source_table)
    {
        return crop_atlas_source(type, data_id, tbl, *source_table);
    }

    sol::optional<std::string> source_str = tbl["source"];
    if (source_str)
    {
        return get_file_source(*source_str);
    }

    return none;
}

std::vector<TsxExporter::TileSource> TsxExporter::get_sources(
    const std::string& type,
    const std::string& data_id,
    sol::table tbl)
{
    std::vector<TsxExporter::TileSource> results;
    bool is_array = tbl[1] != sol::lua_nil;

    if (is_array)
    {
        for (const auto kvp : tbl)
        {
            if (auto tbl_item = kvp.second.as<sol::optional<sol::table>>())
            {
                if (auto result = get_source(type, data_id, *tbl_item))
                {
                    result->properties =
                        tbl_item->get<sol::optional<sol::table>>("properties");
                    results.emplace_back(*result);
                }
            }
        }
    }
    else
    {
        if (auto result = get_source(type, data_id, tbl))
        {
            result->properties =
                tbl.get<sol::optional<sol::table>>("properties");
            results.emplace_back(*result);
        }
    }

    return results;
}

void TsxExporter::open_tsx(const std::string& type)
{
    if (_opened)
    {
        throw std::runtime_error("Already opened");
    }

    auto data_table = lua::lua->get_data_manager().get().get_table(type);

    if (!data_table)
    {
        throw std::runtime_error("No such type \"" + type + "\"");
    }

    auto exporters =
        *lua::lua->get_data_manager().get().get_table("core.tile_exporter");

    // TODO: lookup by "base" field across all exporters
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
    attrs.put("tilecount", _table_length(*data_table));
    attrs.put("columns", _columns);

    pt::ptree grid = _tree.add("tileset.grid", "");
    grid.add("<xmlattr>.orientation", "orthogonal");
    grid.add("<xmlattr>.width", 1);
    grid.add("<xmlattr>.height", 1);

    _opened = true;
    _opts_table = _make_opts_table(_opts);
    _id = 0;
    _type = type;
    _data_table = *data_table;
}


void TsxExporter::write_tile(const std::string& data_id)
{
    if (!_opened)
    {
        throw std::runtime_error("Not opened");
    }

    sol::optional<sol::table> val = _data_table[data_id];

    if (!val)
    {
        throw std::runtime_error(
            "No such data \"" + _type + "#" + data_id + "\"");
    }

    auto result = _exporter(*val, _opts_table);
    if (!result.valid())
    {
        sol::error err = result;
        throw err;
    }

    sol::optional<sol::table> result_tbl = result;
    if (!result_tbl)
    {
        return;
    }

    // TODO: sort tiles

    auto sources = get_sources(_type, data_id, *result_tbl);

    for (const auto& source : sources)
    {
        pt::ptree& tile = _tree.add("tileset.tile", "");
        tile.add("<xmlattr>.id", _id);
        tile.add("<xmlattr>.type", _type);

        pt::ptree& properties = tile.add("properties", "");

        pt::ptree& property = properties.add("property", "");
        property.add("<xmlattr>.name", "data_id");
        property.add("<xmlattr>.value", data_id);

        if (source.properties)
        {
            _add_properties(properties, *source.properties);
        }

        pt::ptree& image = tile.add("image", "");
        image.put("<xmlattr>.width", source.width);
        image.put("<xmlattr>.height", source.height);
        image.put("<xmlattr>.trans", "000000");
        image.put("<xmlattr>.source", source.filename);

        _id++;
    }
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

void export_tsx(
    const std::string& type,
    const fs::path& filename,
    int columns,
    std::unordered_map<std::string, std::string> opts)
{
    auto table = *lua::lua->get_data_manager().get().get_by_order_table(type);

    auto exporter = TsxExporter(filename, columns, opts);
    exporter.open_tsx(type);

    for (const auto kvp : table)
    {
        exporter.write_tile(kvp.second.as<std::string>());
    }

    exporter.close_tsx();
}

} // namespace fmp
} // namespace elona
