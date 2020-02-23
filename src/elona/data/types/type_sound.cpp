#include "type_sound.hpp"

#include "../../lua_env/interface.hpp"

namespace elona
{

SoundData SoundDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    auto legacy_id = data.required<int>("legacy_id");
    DATA_REQ(file, std::string);

    const fs::path sound_file = lua::resolve_path_for_mod(file);
    if (!fs::exists(sound_file))
    {
        throw std::runtime_error(
            id + ": Sound file doesn't exist: " +
            filepathutil::to_utf8_path(sound_file));
    }

    return SoundData{SharedId{id}, legacy_id, sound_file};
}

} // namespace elona
