#include "type_item_chip.hpp"
#include "../../variables.hpp"

namespace elona
{

const constexpr char* data::LuaLazyCacheTraits<ItemChipDB>::type_id;


ItemChipData ItemChipDB::convert(
    const lua::ConfigTable& data,
    const std::string& id_)

{
    DATA_REQ(id, int);
    DATA_OPT_OR(tall, bool, false);
    DATA_OPT_OR(offset_y, int, 0);
    DATA_OPT_OR(stack_height, int, 8);
    DATA_OPT_OR(shadow, int, 40);
    DATA_OPT_OR(animation, int, 0);

    int width = inf_tiles;
    int frame_width = inf_tiles;
    int height = inf_tiles;
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

    if (tall)
    {
        height = inf_tiles * 2;
        offset_y += inf_tiles;
    }

    if (animation > 0)
    {
        // Animation frames are laid out from left to right. The
        // region width represents the entire set of frames, while
        // frame_width represents the width per frame.
        width = inf_tiles * animation;
    }

    return ItemChipData{id,
                        Extent{x, y, width, height, frame_width},
                        ItemChip{SharedId(std::string(Traits::type_id + id_)),
                                 offset_y,
                                 stack_height,
                                 shadow,
                                 animation},
                        filepath};
}

} // namespace elona
