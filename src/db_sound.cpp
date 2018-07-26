#include "db_sound.hpp"

namespace elona
{


sound_db the_sound_db;


sound_data sound_db::convert(const std::string& id_,
                             const sol::table& data,
                             lua::lua_env&)
{
    ELONA_LION_DB_FIELD_REQUIRED(_mod,              std::string);
    ELONA_LION_DB_FIELD_REQUIRED(id,                int); // TODO remove at some point
    ELONA_LION_DB_FIELD_REQUIRED(file,              std::string);
    ELONA_LION_DB_FIELD(predefined,                 bool, false);

    fs::path sound_dir;
    if (predefined)
    {
        sound_dir = filesystem::dir::sound();
    }
    else
    {
        assert(_mod != "");
        sound_dir = filesystem::dir::for_mod(_mod) / filesystem::u8path(file);
    }

    const fs::path sound_file = sound_dir / filesystem::u8path(file);

    if (!fs::exists(sound_file))
    {
        throw std::runtime_error(id_ + ": Sound file doesn't exist: " + sound_file.string());
    }

    return sound_data{
        id,
        sound_file
    };
}

} // namespace elona
