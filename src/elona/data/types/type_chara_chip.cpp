#include "type_chara_chip.hpp"

#include "../../lua_env/interface.hpp"
#include "../../variables.hpp"



namespace elona
{

const constexpr char* data::DatabaseTraits<CharaChipDB>::type_id;



CharaChipData CharaChipDB::convert(
    const lua::ConfigTable& data,
    const std::string& id)
{
    DATA_LEGACY_ID();
    DATA_OPT_OR(tall, bool, false);
    DATA_OPT_OR(offset_y, int, 16);

    int width = inf_tiles;
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
        filepath = lua::resolve_path_for_mod(filepath_str);
        if (!fs::exists(*filepath))
        {
            throw std::runtime_error(
                id + ": Image file doesn't exist: " + filepath->to_u8string());
        }
    }

    if (tall)
    {
        height = inf_tiles * 2;
        offset_y += inf_tiles;
    }

    return CharaChipData{
        data::InstanceId{id},
        legacy_id,
        Extent{x, y, width, height},
        CharaChip{
            SharedId(std::string(Traits::type_id) + data_id_separator + id),
            offset_y,
        },
        filepath,
    };
}

} // namespace elona
