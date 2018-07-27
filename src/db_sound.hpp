#pragma once
#include "lion.hpp"

namespace elona
{


struct sound_data
{
    int id;
    fs::path file;
};

class sound_db;


namespace lion
{
template <>
struct lion_db_traits<sound_db>
{
    using data_type = sound_data;
    using legacy_id_type = int;
    static constexpr const char* datatype_name = "sound";
};

} // namespace lion

class sound_db : public lion::lion_db<sound_db>
{
public:
    sound_db() = default;

    sound_data convert(const std::string&, const sol::table&, lua::lua_env&);
};


extern sound_db the_sound_db;

} // namespace elona
