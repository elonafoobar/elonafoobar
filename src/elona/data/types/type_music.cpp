#include "type_music.hpp"

#include "../../lua_env/interface.hpp"

namespace elona
{

MusicDB the_music_db;
const constexpr char* data::DatabaseTraits<MusicDB>::type_id;



MusicData MusicDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_LEGACY_ID();
    DATA_REQ(file, std::string);
    DATA_OPT_OR(volume, int, 128);

    const fs::path music_file = lua::resolve_path_for_mod(file);
    if (!fs::exists(music_file))
    {
        throw std::runtime_error(
            id + ": Music file doesn't exist: " + music_file.to_u8string());
    }

    return MusicData{
        data::InstanceId{id},
        legacy_id,
        music_file,
        volume,
    };
}

} // namespace elona
