#pragma once
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "../../snail/surface.hpp"
#include "../../thirdparty/sol2/sol.hpp"
#include "../filesystem.hpp"

namespace elona
{
namespace fmp
{

namespace pt = boost::property_tree;

class TsxExporter
{
public:
    TsxExporter(
        const fs::path& filename,
        int columns,
        const std::unordered_map<std::string, std::string>& opts)
    {
        _id = 0;
        _opened = false;
        _filename = filename;
        _columns = columns;
        _opts = opts;
    }

    void open_tsx(const std::string& type);
    void write_tile(const std::string& data_id);
    void close_tsx();

private:
    struct TileSource
    {
        int width;
        int height;
        std::string filename;
        sol::optional<sol::table> properties;
    };

    TsxExporter::TileSource crop_atlas_source(
        const std::string& type,
        const std::string& data_id,
        sol::table result_tbl,
        sol::table source_tbl);
    TsxExporter::TileSource get_file_source(const std::string& source_str);
    optional<TileSource> get_source(
        const std::string& type,
        const std::string& data_id,
        sol::table tbl);
    std::vector<TsxExporter::TileSource> get_sources(
        const std::string& type,
        const std::string& data_id,
        sol::table tbl);

    std::unordered_map<std::string, snail::Surface> _cache;

    std::string _type;
    bool _opened;
    int _id;
    int _columns;
    sol::table _data_table;
    std::unordered_map<std::string, std::string> _opts;
    sol::table _opts_table;
    sol::protected_function _exporter;
    pt::ptree _tree;
    fs::path _filename;
};

void export_tsx(
    const std::string& type,
    const fs::path& filename,
    int columns,
    std::unordered_map<std::string, std::string> opts);

} // namespace fmp
} // namespace elona
