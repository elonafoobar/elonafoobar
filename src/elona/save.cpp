#include "save.hpp"

#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "debug.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "map.hpp"
#include "save_fs.hpp"
#include "save_update.hpp"
#include "set_item_info.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

bool will_autosave = false;



void _do_save_game()
{
    ELONA_LOG("save") << "Save: " << playerid;

    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.misc.save.cannot_save_in_user_map"),
            Message::color{ColorIndex::red});
        update_screen();
        return;
    }

    ctrl_file_map_write();
    ctrl_file_map_items_write(fs::u8path(u8"inv_"s + mid + u8".s2"));

    const auto save_dir = filesystem::dirs::save(playerid);
    if (!fs::exists(save_dir))
    {
        fs::create_directory(save_dir);
    }
    save_fs_save(save_dir);
    ctrl_file_global_write(save_dir);
    save_fs_clear();

    ELONA_LOG("save") << "Save end:" << playerid;
}

} // namespace



void save_save_game(bool no_message, bool silent)
{
    if (!silent)
    {
        snd("core.write1");
    }

    _do_save_game();

    if (!no_message)
    {
        txt(i18n::s.get("core.ui.save"), Message::color{ColorIndex::orange});
    }
}



void save_load_game()
{
    ELONA_LOG("save") << "Load: " << playerid;

    save_fs_clear();

    ctrl_file_temp_dir_delete();
    const auto save_dir = filesystem::dirs::save(playerid);

    save_update(save_dir);
    ctrl_file_global_read(save_dir);

    chara_delete(cdata.tmp());
    set_item_info();
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.has_own_sprite() || chara.is_player())
        {
            create_pcpic(chara);
        }
    }
    refresh_speed(cdata.player());

    time_begin = timeGetTime() / 1000;

    ELONA_LOG("save") << "Load end: " << playerid;
}



void save_save_map_local_data()
{
    prepare_charas_for_map_unload();
    for (int y = 0; y < map_data.height; ++y)
    {
        for (int x = 0; x < map_data.width; ++x)
        {
            cell_data.at(x, y).blood_and_fragments = 0;
        }
    }

    // write map data and characters/skill data local to this map
    ctrl_file_map_write();

    // write data for items/character inventories local to this map
    ctrl_file_map_items_write(fs::u8path(u8"inv_"s + mid + u8".s2"));
}



void save_save_gene()
{
    // TODO
}



void save_load_gene()
{
    // TODO
}



void save_get_inheritance()
{
    // TODO
}



void save_trigger_autosaving()
{
    will_autosave = true;
}



void save_autosave_if_triggered()
{
    if (!will_autosave)
        return;

    will_autosave = false;
    if (!debug_is_wizard() &&
        game_data.current_map != mdata_t::MapId::show_house &&
        game_data.current_map != mdata_t::MapId::pet_arena &&
        g_config.autosave())
    {
        save_save_game();
    }
}

} // namespace elona
