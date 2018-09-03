#include "db_music.hpp"

namespace elona
{

MusicDB the_music_db;

MusicData
MusicDB::convert(const std::string& id_, const sol::table& data, lua::LuaEnv&)
{
    ELONA_LION_DB_FIELD(_mod, std::string, "");
    ELONA_LION_DB_FIELD(id, int, -1);
    ELONA_LION_DB_FIELD(file, std::string, "");
    ELONA_LION_DB_FIELD(predefined, bool, false);

    assert(id != -1); // TODO

    fs::path music_dir;
    if (predefined)
    {
        music_dir = filesystem::dir::sound();
    }
    else
    {
        assert(music_dir != ""); // TODO
        music_dir = filesystem::dir::for_mod(_mod);
    }

    const fs::path music_file = music_dir / filesystem::u8path(file);
    if (!fs::exists(music_file))
    {
        throw std::runtime_error(
            id_ + ": Music file doesn't exist: " + music_file.string());
    }

    return MusicData{id, music_file};
}

} // namespace elona
