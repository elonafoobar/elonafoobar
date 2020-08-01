#include "save.hpp"

#include "ability.hpp"
#include "audio.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "inventory.hpp"
#include "item.hpp"
#include "lua_env/lua_env.hpp"
#include "map.hpp"
#include "message.hpp"
#include "save_fs.hpp"
#include "save_update.hpp"
#include "serialization/serialization.hpp"
#include "serialization/utils.hpp"
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

    int save_f = 0;
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.misc.save.cannot_save_in_user_map"),
            Message::color{ColorIndex::red});
        update_screen();
        return;
    }
    ctrl_file(FileOperation::map_write);
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
    save_f = 0;
    for (const auto& entry : filesystem::glob_dirs(filesystem::dirs::save()))
    {
        if (filepathutil::to_utf8_path(entry.path().filename()) == playerid)
        {
            save_f = 1;
            break;
        }
    }
    const auto save_dir = filesystem::dirs::save(playerid);
    if (save_f == 0)
    {
        fs::create_directory(save_dir);
    }
    save_fs_save(save_dir);
    ctrl_file(FileOperation2::global_write, save_dir);
    save_fs_clear();
    ELONA_LOG("save") << "Save end:" << playerid;
}

} // namespace



void load_save_data()
{
    ELONA_LOG("save") << "Load: " << playerid;

    save_fs_clear();

    ctrl_file(FileOperation::temp_dir_delete);
    const auto save_dir = filesystem::dirs::save(playerid);

    // TODO: Delete this line when the v1.0.0 stable is released!
    if (!fs::exists(save_dir / "version.s0"))
    {
        if (!fs::exists(save_dir / "foobar_data.s1"))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        int major;
        int minor;
        int patch;
        {
            std::ifstream in{
                (save_dir / "foobar_data.s1").native(), std::ios::binary};
            serialization::binary::IArchive ar{in};
            ar(major);
            ar(minor);
            ar(patch);
        }

        if (!(major == 0 && minor == 2 && patch == 7))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        Version v028 = {0, 2, 8, 0, "", "", ""};
        serialization::binary::save(save_dir / "version.s0", v028);
    }

    update_save_data(save_dir);
    ctrl_file(FileOperation2::global_read, save_dir);

    chara_delete(56);
    set_item_info();
    for (auto&& chara : cdata.player_and_allies())
    {
        if (chara.has_own_sprite() || chara.is_player())
        {
            create_pcpic(chara);
        }
    }
    if (game_data.wizard == 1)
    {
        cdata.player().alias = u8"*Debug*"s;
    }
    refresh_speed(cdata.player());
    time_begin = timeGetTime() / 1000;
    ELONA_LOG("save") << "Load end: " << playerid;
}



void save_game(bool no_message, bool silent)
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



void save_set_autosave()
{
    will_autosave = true;
}



void save_autosave_if_needed()
{
    if (will_autosave)
    {
        will_autosave = false;
        if (!game_data.wizard &&
            game_data.current_map != mdata_t::MapId::show_house &&
            game_data.current_map != mdata_t::MapId::pet_arena &&
            g_config.autosave())
        {
            save_game();
        }
    }
}



void load_gene_files()
{
    ctrl_file(FileOperation::gene_read);
    DIM2(spell, 200);
    DIM2(spact, 500);
    for (auto&& cnt : cdata.all())
    {
        cnt.set_state(Character::State::empty);
    }
    Character::copy(cdata.player(), cdata.tmp());
    cdata.player().clear();
    inv_open_tmp_inv_no_physical_file();
    for (const auto& item : g_inv.pc())
    {
        if (item->id == ItemId::secret_experience_of_lomias)
        {
            lomiaseaster = 1;
        }
        if (item->id == ItemId::deed_of_heirship ||
            the_item_db[itemid2int(item->id)]->subcategory == 53100)
        {
            continue;
        }
        if (item->id == ItemId::kitty_bank)
        {
            continue;
        }
        if (item->quality == Quality::special)
        {
            continue;
        }
        if (item->is_precious())
        {
            continue;
        }
        if (the_item_db[itemid2int(item->id)]->category == ItemCategory::ammo)
        {
            item->count = -1;
        }
        item->body_part = 0;
        item_separate(
            item, inv_make_free_slot_force(g_inv.tmp()), item->number());
    }
    for (auto&& cnt : cdata.all())
    {
        chara_delete(cnt.index);
    }
    game_data.play_time = genetemp(805);
}



void save_gene()
{
    ctrl_file(FileOperation::gene_write);
}



void save_map_local_data()
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
    ctrl_file(FileOperation::map_write);

    // write data for items/character inventories local to this map
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
}



void get_inheritance()
{
    inv_close_tmp_inv("shop3.s2");
    p = 0;
    i = 0;
    for (int cnt = 0; cnt < 600; ++cnt)
    {
        if (cnt >= 10 && cnt < 20)
        {
            p += cdata.tmp().get_skill(cnt).base_level;
        }
        if (cnt >= 100 && cnt < 400)
        {
            i += cdata.tmp().get_skill(cnt).base_level;
        }
    }
    p = (p - 250) / 7;
    if (p < 5)
    {
        p = 5;
    }
    else if (p > 50)
    {
        p = 50;
    }
    i = (p - 250) / 8;
    if (i < 5)
    {
        i = 5;
    }
    else if (i > 40)
    {
        i = 40;
    }
    earn_gold(cdata.player(), clamp(cdata.tmp().gold / 100, 1000, 100000));
    earn_platinum(cdata.player(), p);
    cdata.player().skill_bonus += i;
    for (int cnt = 0; cnt < 400; ++cnt)
    {
        mat(cnt) = mat(cnt) / 3;
    }
}

} // namespace elona
