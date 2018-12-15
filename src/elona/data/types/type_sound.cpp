#include "type_sound.hpp"

namespace elona
{

SoundDB the_sound_db;
const constexpr char* data::LuaLazyCacheTraits<SoundDB>::type_id;


SoundData SoundDB::convert(const lua::ConfigTable& data, const std::string& id_)
{
    auto legacy_id = data.required<int>("id");
    DATA_REQ(file, std::string);

    const fs::path sound_file = filesystem::resolve_path_for_mod(file);
    if (!fs::exists(sound_file))
    {
        throw std::runtime_error(
            id_ + ": Sound file doesn't exist: " + sound_file.string());
    }

    return SoundData{legacy_id, sound_file};
}

} // namespace elona
