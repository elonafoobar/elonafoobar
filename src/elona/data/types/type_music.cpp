#include "type_music.hpp"

#include "../../lua_env/interface.hpp"

namespace elona
{

MusicData MusicDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_REQ(file, std::string);

    const fs::path music_file = lua::resolve_path_for_mod(file);
    if (!fs::exists(music_file))
    {
        throw std::runtime_error(
            id + ": Music file doesn't exist: " +
            filepathutil::to_utf8_path(music_file));
    }

    return MusicData{SharedId{id}, legacy_id, music_file};
}

} // namespace elona
