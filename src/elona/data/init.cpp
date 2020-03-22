#include <string>
#include <vector>

#include "types.hpp"

using namespace elona;



namespace
{

// Certain lua data caches cannot currently use lazy loading, because they are
// iterated at some point in native code. At the time of iteration, all of the
// entries would have to be loaded into the cache.
// TODO: Determine the iterator type of sol::table, so it can be wrapped in the
// Data cache.
void _initialize_iterable_dbs(lua::DataTable& data)
{
    the_ability_db.initialize(data);
    the_buff_db.initialize(data);
    the_character_db.initialize(data);
    the_class_db.initialize(data);
    the_fish_db.initialize(data);
    the_god_db.initialize(data);
    the_item_db.initialize(data);
    the_item_material_db.initialize(data);
    the_mapdef_db.initialize(data);
    the_music_db.initialize(data);
    the_race_db.initialize(data);
    the_sound_db.initialize(data);
    the_trait_db.initialize(data);
}



// TODO: Make some way to load textures lazily during runtime.
void _initialize_chip_dbs(lua::DataTable& data)
{
    draw_clear_loaded_chips();

    {
        ItemChipDB the_item_chip_db;
        the_item_chip_db.initialize(data);
        initialize_item_chips(the_item_chip_db);
    }

    {
        CharaChipDB the_chara_chip_db;
        the_chara_chip_db.initialize(data);
        initialize_chara_chips(the_chara_chip_db);
    }

    {
        the_portrait_db.initialize(data);
        the_portrait_db.cache_sorted_portrait_table();
        initialize_portraits(the_portrait_db);
    }

    {
        MapChipDB the_map_chip_db;
        the_map_chip_db.initialize(data);
        initialize_map_chips(the_map_chip_db);
    }

    {
        the_asset_db.initialize(data);
        init_assets();
    }
}

} // namespace



namespace elona
{
namespace data
{

void initialize(lua::DataTable& data)
{
    _initialize_iterable_dbs(data);
    _initialize_chip_dbs(data);
}

} // namespace data
} // namespace elona
