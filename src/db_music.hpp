#pragma once
#include "filesystem.hpp"
#include "lion.hpp"

namespace elona
{


struct music_data
{
    int id;
    fs::path file;
};


class music_db;


namespace lion
{

template <>
struct lion_db_traits<music_db>
{
    using data_type = music_data;
    using legacy_id_type = int;
    static constexpr const char* datatype_name = u8"music";
};

} // namespace cat



class music_db : public lion::lion_db<music_db>
{
public:
    music_db() = default;

    music_data convert(const std::string&, const sol::table&, lua::lua_env&);
};


extern music_db the_music_db;


} // namespace elona
