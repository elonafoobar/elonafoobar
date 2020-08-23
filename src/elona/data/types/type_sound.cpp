#include "type_sound.hpp"

#include "../../lua_env/interface.hpp"

namespace elona
{

SoundDB the_sound_db;
const constexpr char* data::DatabaseTraits<SoundDB>::type_id;



SoundData SoundDB::convert(const lua::ConfigTable& data, const std::string& id)
{
    DATA_LEGACY_ID();
    DATA_REQ(file, std::string);
    DATA_OPT_OR(volume, int, 128);

    const fs::path sound_file = lua::resolve_path_for_mod(file);
    if (!fs::exists(sound_file))
    {
        throw std::runtime_error(
            id + ": Sound file doesn't exist: " + sound_file.to_u8string());
    }

    return SoundData{
        data::InstanceId{id},
        legacy_id,
        sound_file,
        volume,
    };
}

} // namespace elona
