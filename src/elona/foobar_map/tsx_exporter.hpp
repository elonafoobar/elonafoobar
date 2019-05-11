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
    TsxExporter(const fs::path& filename)
    {
        _id = 0;
        _opened = false;
        _filename = filename;
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
    };

    optional<TileSource> get_source(
        const std::string& type,
        const std::string& data_id,
        sol::table tbl);

    std::unordered_map<std::string, snail::Surface> _cache;

    std::string _type;
    bool _opened;
    int _id;
    sol::table _table;
    sol::protected_function _exporter;
    pt::ptree _tree;
    fs::path _filename;
};

void export_tsx(const std::string& type, const fs::path& filename);

} // namespace fmp
} // namespace elona
