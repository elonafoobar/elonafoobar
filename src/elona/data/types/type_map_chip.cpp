#include "type_map_chip.hpp"
#include "../../variables.hpp"

namespace elona
{

const constexpr char* data::LuaLazyCacheTraits<MapChipDB>::type_id;


MapChip MapChipDB::convert(const lua::ConfigTable& data, const std::string& id_)
{
    auto legacy_id = data.required<int>("id");
    DATA_REQ(atlas, int);
    DATA_OPT_OR(is_feat, bool, false);
    DATA_OPT_OR(kind, int, 0);
    DATA_OPT_OR(kind2, int, 0);
    DATA_OPT_OR(wall_kind, int, 0);
    DATA_OPT_OR(anime_frame, int, 0);
    DATA_OPT_OR(offset_top, int, 0);
    DATA_OPT_OR(offset_bottom, int, 0);
    DATA_OPT_OR(effect, int, 0);

    int height = inf_tiles + offset_bottom;
    int frame_width = inf_tiles;
    int width = inf_tiles;
    if (anime_frame > 0)
    {
        width = frame_width * anime_frame;
    }
    int x = 0;
    int y = 0;
    optional<fs::path> filepath = none;

    auto source = data.required<sol::object>("source");
    if (source.is<sol::table>())
    {
        sol::table source_from_atlas = source;
        x = source_from_atlas["x"];
        y = source_from_atlas["y"];
    }
    else
    {
        std::string filepath_str = source.as<std::string>();
        filepath = filesystem::resolve_path_for_mod(filepath_str);
        if (!fs::exists(*filepath))
        {
            throw std::runtime_error(
                id_ + ": Image file doesn't exist: " + filepath->string());
        }
    }

    return MapChip{
        legacy_id,
        atlas,
        SharedId(std::string(Traits::type_id) + data_id_separator + id_),
        Extent{x, y, width, height, frame_width},
        filepath,
        is_feat,
        kind,
        kind2,
        wall_kind,
        anime_frame,
        offset_top,
        offset_bottom,
        effect};
}

} // namespace elona
