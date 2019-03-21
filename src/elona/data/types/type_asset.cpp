#include "type_asset.hpp"


namespace
{

std::unordered_map<std::string, int> window_id_table = {
    {"item", 1},
    {"map", 2},
    {"interface", 3},
    {"atx_background", 4},
    {"character", 5},
    {"background", 7},
};

}

namespace elona
{

namespace lua
{
namespace LuaEnums
{

EnumMap<AssetLoadType> AssetLoadTypeTable(
    "AssetLoadType",
    {
        {"Startup", AssetLoadType::Startup},
        {"Buffer", AssetLoadType::Buffer},
        {"BufferDeferred", AssetLoadType::BufferDeferred},
        {"None", AssetLoadType::None},
    });
}
} // namespace lua



AssetDB the_asset_db;
const constexpr char* data::LuaLazyCacheTraits<AssetDB>::type_id;



AssetData AssetDB::convert(const lua::ConfigTable& data, const std::string&)
{
    DATA_OPT_OR(source, std::string, "interface");
    DATA_OPT_OR(x, int, 0);
    DATA_OPT_OR(y, int, 0);
    DATA_REQ(width, int);
    DATA_REQ(height, int);
    DATA_OPT_OR(count_x, int, 1);
    DATA_OPT_OR(count_y, int, 1);
    DATA_OPT(file, std::string);
    DATA_ENUM(
        load_type, AssetLoadType, AssetLoadTypeTable, AssetLoadType::None);

    auto window_id = 3;
    auto it = window_id_table.find(source);
    if (it != window_id_table.end())
    {
        window_id = it->second;
    }

    optional<fs::path> file_path = none;
    if (file)
    {
        file_path = filesystem::resolve_path_for_mod(*file);
    }

    return AssetData{
        window_id, x, y, width, height, count_x, count_y, file_path, load_type};
}

} // namespace elona
