#include "tileset_export_progress_prompt.hpp"
#include "../../util/stopwatch.hpp"
#include "../config/config.hpp"
#include "../i18n.hpp"
#include "../lua_env/data_manager.hpp"
#include "../lua_env/lua_env.hpp"
#include "../lua_env/mod_manager.hpp"

namespace elona
{
namespace ui
{

static fs::path _tiled_plugin_path()
{
    return filesystem::get_home_directory() / ".tiled";
}

static fs::path _tileset_path()
{
    return _tiled_plugin_path() / "Elona_foobar";
}

/**
 * Writes the mods used at the time of export to the tileset output folder, to
 * allow detecting incompatibilities.
 */
static void _write_mods_list()
{
    auto mods_file = _tileset_path() / "mods.txt";
    std::ofstream out{mods_file.native()};

    for (const auto& pair : lua::lua->get_mod_manager().enabled_mods())
    {
        if (!lua::ModManager::mod_id_is_reserved(pair.second->manifest.id))
        {
            out << pair.second->manifest.id << " "
                << pair.second->manifest.version.to_string() << "\n";
        }
    }
}

void TilesetExportProgressPrompt::init()
{
    SimplePrompt<bool>::init();

    export_tsx(*_tileset_itr);

    auto data = lua::lua->get_data_manager().get();

    _total_tiles = 0;
    _current_tile = 0;

    for (const auto& tileset : _tilesets)
    {
        _total_tiles += data.get_by_order_table(tileset.data_type)->size();
    }
}

void TilesetExportProgressPrompt::draw()
{
    if (_current_tile < _total_tiles && _current_tile % 500 != 0)
        return;

    draw_window();

    mes(_x + _width / 2 - (strlen_u(_message) * 8) / 2,
        _y + _font_size + 20,
        _message);

    constexpr int progress_bar_width = 300;
    constexpr int progress_bar_height = 20;

    float progress = 0;
    if (_total_tiles > 0)
    {
        progress = ((float)_current_tile / (float)_total_tiles);
    }

    std::string progress_string = ""s + _current_tile + "/" + _total_tiles;

    mes(_x + _width / 2 - (strlen_u(progress_string) * 8) / 2,
        _y + _height / 2 + 10 + 2 + _font_size,
        progress_string);

    boxl(
        _x + (_width / 2) - (progress_bar_width / 2) + 2,
        _y + _height / 2 - 10 + 2,
        (progress_bar_width - 4),
        progress_bar_height - 4,
        {0, 0, 0, 255});

    boxf(
        _x + (_width / 2) - (progress_bar_width / 2) + 2,
        _y + _height / 2 - 10 + 2,
        (progress_bar_width - 4) * progress,
        progress_bar_height - 4,
        {0, 0, 0, 255});

    redraw();
}

void TilesetExportProgressPrompt::export_tsx(
    const TilesetExportProgressPrompt::TilesetOptions& opts)
{
    lib::Stopwatch watch;

    ELONA_LOG("map.tsx") << "writing tileset " << opts.filename << " for "
                         << opts.data_type;

    _table =
        *lua::lua->get_data_manager().get().get_by_order_table(opts.data_type);

    fs::create_directories(_tileset_path());

    // Copy Tiled plugin
    fs::copy_file(filesystem::dir::data() / "tiled" / "elona_foobar.py",
                  _tiled_plugin_path(),
                  fs::copy_option::overwrite_if_exists);
    fs::copy_file(filesystem::dir::data() / "tiled" / "elona122.py",
                  _tiled_plugin_path(),
                  fs::copy_option::overwrite_if_exists);

    auto filepath = _tileset_path() / opts.filename;
    _exporter =
        std::make_unique<fmp::TsxExporter>(filepath, opts.columns, opts.opts);
    _exporter->open_tsx(opts.data_type);
    _index = 1;
}

optional<bool> TilesetExportProgressPrompt::update()
{
    if (_tileset_itr == _tilesets.end())
    {
        auto action = key_check();

        if (action != ""s)
        {
            return true;
        }

        return none;
    }

    if (_index > _table.size())
    {
        _exporter->close_tsx();
        _write_mods_list();
        _tileset_itr++;

        ELONA_LOG("map.tsx") << "wrote " << _table.size() << " tiles in "
                             << _watch.measure() << "ms";

        if (_tileset_itr == _tilesets.end())
        {
            _message = i18n::s.get("core.locale.main_menu.mods.extra.finished");

            draw();

            return none;
        }

        export_tsx(*_tileset_itr);
    }

    _exporter->write_tile(_table[_index].get<std::string>());
    _index++;
    _current_tile++;
    _message = i18n::s.get(
        "core.locale.main_menu.mods.extra.exporting", _tileset_itr->data_type);

    draw();

    return none;
}


} // namespace ui
} // namespace elona
