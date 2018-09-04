#include "db_chara_chip.hpp"
#include "macro.hpp"
#include "variables.hpp"

namespace elona
{

CharaChipData CharaChipDB::convert(
    const std::string& id_,
    const sol::table& data,
    lua::LuaEnv& lua)
{
    UNUSED(lua);
    ELONA_LION_DB_FIELD_REQUIRED(_mod, std::string);
    ELONA_LION_DB_FIELD_REQUIRED(id, int);
    ELONA_LION_DB_FIELD(tall, bool, false);
    ELONA_LION_DB_FIELD(offset_y, int, 16);

    int width = inf_tiles;
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

    return CharaChipData{id,
                           Extent{x, y, width, height},
                           CharaChip{SharedId(id_), offset_y},
                           filepath};
}

} // namespace elona
