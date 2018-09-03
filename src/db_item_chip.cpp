#include "db_item_chip.hpp"
#include "macro.hpp"
#include "variables.hpp"

namespace elona
{

item_chip_data ItemChipDB::convert(
    const std::string& id_,
    const sol::table& data,
    lua::LuaEnv& lua)
{
    UNUSED(lua);

    ELONA_LION_DB_FIELD_REQUIRED(_mod, std::string);
    ELONA_LION_DB_FIELD_REQUIRED(id, int);
    ELONA_LION_DB_FIELD(tall, bool, false);
    ELONA_LION_DB_FIELD(offset_y, int, 0);
    ELONA_LION_DB_FIELD(stack_height, int, 8);
    ELONA_LION_DB_FIELD(shadow, int, 40);
    ELONA_LION_DB_FIELD(animation, int, 0);

    int width = inf_tiles;
    int frame_width = inf_tiles;
    int height = inf_tiles;
    int x = 0;
    int y = 0;
    optional<fs::path> filepath = none;

    sol::object source = data["source"];
    if (source.is<sol::table>())
    {
        sol::table source_from_atlas = source;
        x = source_from_atlas["x"];
        y = source_from_atlas["y"];
    }
    else
    {
        std::string filepath_str = source.as<std::string>();
        filepath = filesystem::dir::for_mod(_mod) / filepath_str;
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

    return item_chip_data{
        id,
        extent{x, y, width, height, frame_width},
        item_chip_t{shared_id(id_), offset_y, stack_height, shadow, animation},
        filepath};
}

} // namespace elona
