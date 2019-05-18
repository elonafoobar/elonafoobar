#pragma once
#include <unordered_map>

#include "../../thirdparty/sol2/sol.hpp"
#include "../../util/stopwatch.hpp"
#include "../ui/simple_prompt.hpp"
#include "tsx_exporter.hpp"

namespace elona
{
namespace ui
{

class TilesetExportProgressPrompt : public SimplePrompt<bool>
{
public:
    struct TilesetOptions
    {
        std::string data_type;
        std::string filename;
        int columns;
        std::unordered_map<std::string, std::string> opts;
    };

    using Tilesets = std::vector<TilesetOptions>;

    TilesetExportProgressPrompt(Tilesets tilesets)
        : SimplePrompt(400, 150)
        , _tilesets(tilesets)
    {
        _tileset_itr = _tilesets.begin();
    }

protected:
    void init() override;
    optional<bool> update() override;
    void draw() override;

private:
    void export_tsx(const TilesetOptions& opts);

    sol::table _table;
    size_t _index = 1;
    int _total_tiles = 0;
    int _current_tile = 0;
    lib::Stopwatch _watch;
    std::unique_ptr<fmp::TsxExporter> _exporter;

    std::vector<TilesetOptions> _tilesets;
    std::vector<TilesetOptions>::iterator _tileset_itr;
};

} // namespace ui
} // namespace elona
