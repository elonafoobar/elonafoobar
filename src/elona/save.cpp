#include "save.hpp"
#include "audio.hpp"
#include "character_status.hpp"
#include "ctrl_file.hpp"
#include "draw.hpp"
#include "i18n.hpp"
#include "lua_env/lua_env.hpp"
#include "putit.hpp"
#include "save_update.hpp"
#include "ui.hpp"



namespace elona
{

void load_save_data()
{
    ELONA_LOG("save") << "Load: " << playerid;

    // TODO instead serialize/deserialize data
    lua::lua->get_handle_manager().clear_map_local_handles();

    Save::instance().clear();
    writeloadedbuff_clear();

    ctrl_file(FileOperation::temp_dir_delete);
    const auto save_dir = filesystem::dir::save(playerid);

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
            std::ifstream in{(save_dir / "foobar_data.s1").native(),
                             std::ios::binary};
            putit::BinaryIArchive ar{in};
            ar.load(major);
            ar.load(minor);
            ar.load(patch);
        }

        if (!(major == 0 && minor == 2 && patch == 7))
        {
            throw std::runtime_error{
                "Please update your save in v0.2.7 first."};
        }

        Version v028 = {0, 2, 8, 0, "", "", ""};
        putit::BinaryOArchive::save(save_dir / "version.s0", v028);
    }

    update_save_data(save_dir);
    ctrl_file(FileOperation2::global_read, save_dir);

    chara_delete(56);
    set_item_info();
    for (int cnt = 0; cnt < 16; ++cnt)
    {
        if (cdata[cnt].has_own_sprite() == 1 || cnt == 0)
        {
            create_pcpic(cnt);
        }
    }
    if (game_data.wizard == 1)
    {
        cdatan(1, 0) = u8"*Debug*"s;
    }
    refresh_speed(cdata.player());
    time_begin = timeGetTime() / 1000;
    ELONA_LOG("save") << "Load end: " << playerid;
}



void do_save_game()
{
    snd("core.write1");
    save_game();
    txt(i18n::s.get("core.locale.ui.save"), Message::color{ColorIndex::orange});
}



void save_game()
{
    ELONA_LOG("save") << "Save: " << playerid;

    int save_f = 0;
    if (game_data.current_map == mdata_t::MapId::show_house)
    {
        txt(i18n::s.get("core.locale.misc.save.cannot_save_in_user_map"),
            Message::color{ColorIndex::red});
        update_screen();
        return;
    }
    ctrl_file(FileOperation::map_write);
    ctrl_file(FileOperation2::map_items_write, u8"inv_"s + mid + u8".s2");
    save_f = 0;
    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::save(), filesystem::DirEntryRange::Type::dir))
    {
        if (filepathutil::to_utf8_path(entry.path().filename()) == playerid)
        {
            save_f = 1;
            break;
        }
    }
    const auto save_dir = filesystem::dir::save(playerid);
    if (save_f == 0)
    {
        fs::create_directory(save_dir);
    }
    Save::instance().save(save_dir);
    ctrl_file(FileOperation2::global_write, save_dir);
    Save::instance().clear();
    ELONA_LOG("save") << "Save end:" << playerid;
}

} // namespace elona
