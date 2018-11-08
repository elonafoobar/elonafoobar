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
    the_character_db.initialize(data);
    the_character_db.load_all();

    the_item_db.initialize(data);
    the_item_db.load_all();

    the_mapdef_db.initialize(data);
    the_mapdef_db.load_all();

    the_trait_db.initialize(data);
    the_trait_db.load_all();

    the_fish_db.initialize(data);
    the_fish_db.load_all();

    the_ability_db.initialize(data);
    the_ability_db.load_all();

    the_item_material_db.initialize(data);
    the_item_material_db.load_all();
}



// TODO: Make some way to load textures lazily during runtime.
void _initialize_chip_dbs(lua::DataTable& data)
{
    draw_clear_loaded_chips();

    {
        ItemChipDB the_item_chip_db;
        the_item_chip_db.initialize(data);
        the_item_chip_db.load_all();
        initialize_item_chips(the_item_chip_db);
    }

    {
        CharaChipDB the_chara_chip_db;
        the_chara_chip_db.initialize(data);
        the_chara_chip_db.load_all();
        initialize_chara_chips(the_chara_chip_db);
    }
}



void _initialize_lazy_dbs(lua::DataTable& data)
{
    the_music_db.initialize(data);
    the_sound_db.initialize(data);
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
    _initialize_lazy_dbs(data);
}

} // namespace data
} // namespace elona
