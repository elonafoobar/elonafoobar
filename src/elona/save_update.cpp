#include "save_update.hpp"

#include "serialization/serialization.hpp"
#include "serialization/utils.hpp"
#include "version.hpp"



namespace elona
{

void save_update(const fs::path& save_dir)
{
    const auto version_filepath = save_dir / "version.s0";
    if (!fs::exists(version_filepath))
    {
        return;
    }

    std::tuple<int, int, int, int> version;
    serialization::binary::load(version_filepath, version);

    const auto [_major, _minor, _patch, serial_id] = version;

    if (serial_id > latest_version.serial_id)
    {
        throw std::runtime_error{"Incompatible save data!"};
    }
    else if (serial_id <= 14)
    {
        throw std::runtime_error{
            "Too old save! Please update the save in v0.5.0 first."};
    }
    else if (serial_id <= 24)
    {
        throw std::runtime_error{
            "Too old save! Please update the save in v0.7.5 first."};
    }
}

} // namespace elona
