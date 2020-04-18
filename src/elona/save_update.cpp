#include "save_update.hpp"

#include "../util/fileutil.hpp"
#include "../util/strutil.hpp"
#include "character.hpp"
#include "item.hpp"
#include "lua_env/handle_manager.hpp"
#include "lua_env/lua_env.hpp"
#include "lua_env/mod_serializer.hpp"
#include "serialization/serialization.hpp"



namespace
{

void _update_save_data(const fs::path& save_dir, int serial_id)
{
    (void)save_dir;
#define ELONA_CASE(n) \
    case n: _update_save_data_##n(save_dir); break;

    switch (serial_id)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        throw std::runtime_error{
            "Too old save! Please update the save in v0.5.0 first."};
    default: assert(0); break;
    }
#undef ELONA_CASE
}

} // namespace



namespace elona
{

void update_save_data(const fs::path& save_dir)
{
    const auto version_filepath = save_dir / "version.s0";

    Version version;
    serialization::binary::load(version_filepath, version);

    if (version.serial_id > latest_version.serial_id)
    {
        // FIXME:
        // It is far away from the best solution, but we do not have the way to
        // report a fatal error to end-users by GUI window, except for
        // OS-builtin exception handling.
        throw std::runtime_error{"Incompatible save data!"};
    }

    for (int serial_id = version.serial_id;
         serial_id != latest_version.serial_id;
         ++serial_id)
    {
        ELONA_LOG("save.update") << "Update save data from #" << serial_id
                                 << " to #" << (serial_id + 1) << ".";
        _update_save_data(save_dir, serial_id);
    }
    version = latest_version;
    serialization::binary::save(version_filepath, version);
}

} // namespace elona
