#include "type_music.hpp"

namespace elona
{

MusicDB the_music_db;
const constexpr char* data::LuaLazyCacheTraits<MusicDB>::type_id;


MusicData MusicDB::convert(const lua::ConfigTable& data, const std::string& id_)
{
    auto legacy_id = data.required<int>("id");
    DATA_REQ(file, std::string);

    const fs::path music_file = filesystem::resolve_path_for_mod(file);
    if (!fs::exists(music_file))
    {
        throw std::runtime_error(
            id_ + ": Music file doesn't exist: " +
            filepathutil::to_utf8_path(music_file));
    }

    return MusicData{legacy_id, music_file};
}

} // namespace elona
