#include "ability.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "class.hpp"
#include "config.hpp"
#include "ctrl_file.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "i18n.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "main.hpp"
#include "race.hpp"
#include "range.hpp"
#include "trait.hpp"
#include "variables.hpp"

using namespace elona;



namespace elona
{


elona_vector1<int> keybd_st;
elona_vector1<std::string> cmrace;
std::string cmclass;
elona_vector1<int> cmstats;


} // namespace elona



namespace
{


void main_loop()
{
redo:
    try
    {
        turn_begin();
    }
    catch (elona_turn_sequence&)
    {
        goto redo;
    }
}



void load_musiclist()
{
    const auto filepath = fs::u8path(u8"./user/music/musiclist.txt");
    if (!fs::exists(filepath))
        return;

    size_t i = 0;
    for (auto&& line : fileutil::read_by_line{filepath})
    {
        if (std::empty(line))
            continue;
        musicfile(i + 50) = strmid(line, 0, instr(line, 0, u8"\t"));
        ++i;
    }
}



void backup_config_files()
{
    std::tuple<const char*, const char*> files[] = {
        {u8"./original/config.txt", u8"./config.txt"},
        {u8"./original/export.txt", u8"./user/export.txt"},
        {u8"./original/lastwords.txt", u8"./user/lastwords.txt"},
        {u8"./original/lastwords-e.txt", u8"./user/lastwords-e.txt"},
        {u8"./original/musiclist.txt", u8"./user/music/musiclist.txt"},
        {u8"./original/face1.bmp", u8"./user/graphic/face1.bmp"},
    };

    for (const auto& [from, to] : files)
    {
        const auto from_path = fs::u8path(from);
        const auto to_path = fs::u8path(to);
        if (!fs::exists(to_path))
        {
            fs::copy_file(from_path, to_path);
        }
    }
}



void check_double_launching()
{
    mutex_handle = CreateMutexA(0, 0, u8"Elona"s);
    if (func_3() == 183)
    {
        dialog(
            lang(
                u8"二重起動のため終了します。"s,
                u8"The program is already running."s),
            1);
        end();
        return;
    }
    return;
}



void initialize_elona()
{
    time_warn = timeGetTime() / 1000;
    time_begin = timeGetTime() / 1000;

    backup_config_files();

    check_double_launching();

    SDIM3(s, 160, 40);
    DIM2(p, 100);
    DIM2(rtval, 10);
    SDIM3(rtvaln, 50, 10);
    SDIM3(key_select, 2, 20);
    SDIM2(buff, 10000);
    initialize_jkey();
    load_config2();
    load_config();
    initialize_ui_constants();
    if (cfg_fullscreen)
    {
        chgdisp(1, windoww, windowh);
        bgscr(0, windoww, windowh, 0, 0);
        width(windoww, windowh, 0, 0);
    }
    else
    {
        screen(0, windoww, windowh, 0, windowx, windowy);
    }
    gsel(0);
    redraw(0);
    boxf();
    redraw(1);
    buffer(3, 1440, 800);
    picload(fs::u8path(u8"./graphic/interface.bmp"), 1);
    buffer(4, windoww, windowh);
    buffer(8, windoww, windowh);
    gsel(0);
    folder = fs::u8path(u8"./user/graphic/");
    buffer(1, 1584, 1200);
    picload(fs::u8path(u8"./graphic/item.bmp"), 1);
    if (inf_tiles != 48)
    {
        pos(0, 0);
        gzoom(33 * inf_tiles, 25 * inf_tiles, 1, 0, 0, 1584, 1200);
    }
    buffer(2, 33 * inf_tiles, 25 * inf_tiles);
    buffer(6, 33 * inf_tiles, 25 * inf_tiles);
    buffer(7, 24, 24);
    buffer(9, 24, 24);

    DIM3(cmapdata, 5, 400);
    DIM2(fixeditemenc, 20);
    DIM2(dir, 5);
    DIM3(dblist, 2, 800);
    SDIM1(filemod);
    SDIM2(inputlog, 100);
    SDIM2(key, 20);
    SDIM2(keylog, 20);
    SDIM3(msg, 120, inf_maxlog);
    SDIM2(msgtemp, 1000);
    SDIM3(randn1, 30, 20);
    DIM2(rtval, 10);
    DIM3(list, 3, 500);
    SDIM4(listn, 40, 2, 500);
    DIM2(invctrl, 2);
    SDIM4(promptl, 50, 3, 20);
    SDIM3(description, 1000, 3);
    SDIM2(folder, 1000);
    SDIM1(msgtempprev);
    DIM3(mef, 9, 200);
    DIM3(adata, 40, 500);
    DIM3(qdata, 20, 500);
    SDIM3(qname, 40, 500);
    DIM2(gdata, 1000);
    DIM2(genetemp, 1000);
    SDIM3(gdatan, 40, 50);
    DIM2(mdatatmp, 100);
    DIM2(mdata, 100);
    SDIM3(mdatan, 20, 2);
    SDIM4(cdatan, 40, 10, 245);
    SDIM2(s1, 1000);
    DIM2(spell, 200);
    DIM2(spact, 500);
    DIM2(mat, 400);
    DIM2(trait, 500);
    DIM3(itemmemory, 3, 800);
    DIM3(npcmemory, 2, 800);
    DIM2(recipememory, 1200);
    DIM2(invmark, 35);
    DIM2(commark, 3);
    DIM2(feat, 5);
    DIM3(dirchk, 3, 2);

    dirchk(0, 0) = -1;
    dirchk(1, 0) = 0;
    dirchk(2, 0) = 1;
    dirchk(0, 1) = 1;
    dirchk(1, 1) = 0;
    dirchk(2, 1) = -1;

    DIM2(chatval, 5);
    DIM2(evlist, 10);
    DIM2(matneed, 20);
    DIM3(pcc, 30, 20);

    maxrain = windoww * windowh / 3500;

    DIM2(rainx, maxrain * 2);
    DIM2(rainy, maxrain * 2);
    SDIM1(fltnrace);
    DIM3(card, 4, 1000);
    DIM2(deck, 1000);

    initialize_craft_material_data();

    DIM3(dirxy, 2, 4);

    dirxy(0, 3) = 0;
    dirxy(1, 3) = -1;
    dirxy(0, 0) = 0;
    dirxy(1, 0) = 1;
    dirxy(0, 1) = -1;
    dirxy(1, 1) = 0;
    dirxy(0, 2) = 1;
    dirxy(1, 2) = 0;

    DIM3(c_col, 3, 30);

    c_col(0, 0) = 0;
    c_col(1, 0) = 0;
    c_col(2, 0) = 0;
    c_col(0, 2) = 80;
    c_col(1, 2) = 0;
    c_col(2, 2) = 80;
    c_col(0, 3) = 0;
    c_col(1, 3) = 100;
    c_col(2, 3) = 100;
    c_col(0, 4) = 80;
    c_col(1, 4) = 80;
    c_col(2, 4) = 0;
    c_col(0, 6) = 0;
    c_col(1, 6) = 40;
    c_col(2, 6) = 80;
    c_col(0, 5) = 0;
    c_col(1, 5) = 0;
    c_col(2, 5) = 80;
    c_col(0, 7) = 100;
    c_col(1, 7) = 101;
    c_col(2, 7) = 102;
    c_col(0, 8) = 70;
    c_col(1, 8) = 100;
    c_col(2, 8) = 40;
    c_col(0, 9) = 100;
    c_col(1, 9) = 50;
    c_col(2, 9) = 50;
    c_col(0, 10) = 0;
    c_col(1, 10) = 60;
    c_col(2, 10) = 70;
    c_col(0, 11) = 20;
    c_col(1, 11) = 40;
    c_col(2, 11) = 100;
    c_col(0, 12) = 0;
    c_col(1, 12) = 0;
    c_col(2, 12) = 0;
    c_col(0, 13) = 30;
    c_col(1, 13) = 40;
    c_col(2, 13) = 70;
    c_col(0, 14) = 150;
    c_col(1, 14) = 20;
    c_col(2, 14) = 150;
    c_col(0, 15) = 50;
    c_col(1, 15) = 50;
    c_col(2, 15) = 50;
    c_col(0, 16) = 0;
    c_col(1, 16) = 30;
    c_col(2, 16) = 30;
    c_col(0, 17) = 30;
    c_col(1, 17) = 30;
    c_col(2, 17) = 0;
    c_col(0, 18) = 30;
    c_col(1, 18) = 60;
    c_col(2, 18) = 0;
    c_col(0, 19) = 40;
    c_col(1, 19) = 0;
    c_col(2, 19) = 40;
    c_col(0, 20) = 45;
    c_col(1, 20) = 5;
    c_col(2, 20) = 95;

    DIM3(dirchk, 3, 2);

    dirchk(0, 0) = -1;
    dirchk(1, 0) = 0;
    dirchk(2, 0) = 1;
    dirchk(0, 1) = 1;
    dirchk(1, 1) = 0;
    dirchk(2, 1) = -1;

    DIM2(floorstack, 400);
    SDIM3(key_list, 2, 20);
    SDIM2(playerheader, 100);
    artifactlocation.clear();
    SDIM1(newsbuff);
    SDIM3(soundfile, 30, 122);
    SDIM3(musicfile, 30, 97);
    DIM3(slight, inf_screenw + 4, inf_screenh + 4);

    gsel(3);
    gmode(0);
    redraw(0);
    font(lang(cfg_font1, cfg_font2), 15 - en * 2, 0);
    for (int i = 0; i < 18; ++i)
    {
        pos(i * 24 + 72, 30);
        gcopy(3, 0, 30, 24, 18);
        pos(i * 24 + 77, 31);
        color(50, 60, 80);
        bmes(key_select(i), 250, 240, 230);
        color(0, 0, 0);
    }
    gsel(0);
    gmode(2);
    text_set();
    ctrl_file(10);
    tc = 0;
    tcol_at_txtfunc(0) = 255;
    tcol_at_txtfunc(1) = 255;
    tcol_at_txtfunc(2) = 255;
    invctrl(0) = 0;
    invctrl(1) = 0;
    pos(-40, -40);
    mesbox(keylog, 0, 0, 1, 10);
    SDIM1(buffboard);
    notesel(buffboard);
    {
        buffboard(0).clear();
        std::ifstream in{fs::u8path(u8"./data/board.txt")};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buffboard(0) += tmp + '\n';
        }
    }
    SDIM1(ioriginalnameref);
    SDIM1(ioriginalnameref2);
    SDIM1(iknownnameref);
    SDIM1(ialphanameref);
    DIM2(irandomname, 800);
    DIM1(icolref);
    DIM2(keybd_st, 256);
    DIM2(trate, 8);
    SDIM1(filtern);
    SDIM1(filter_creature);
    SDIM2(netbuf, 20000);
    delete_temporary_npc_files();
    delete_temporary_user_files();
    initialize_character_filters();
    initialize_cbit_filters();
    initialize_item_chip();
    initialize_building_daga();
    initialize_adata();
    initialize_cell_object_data();
    load_random_name_table();
    load_random_title_table();
    gdata_random_seed = rnd(800) + 2;
    gdata(9) = rnd(200) + 2;
    set_item_info();
    clear_trait_data();
    initialize_rankn();
    initialize_post_data();
    initialize_item_material_data();
    initialize_ego_data();
    initialize_enchantment_data();
    initialize_set_of_random_generation();
    initialize_picfood();
    initialize_recipe();
    initialize_fish_data();
    initialize_nefia_names();
    initialize_home_adata();
    load_cnpc_data();
    if (cfg_music == 1 && DMINIT() == 0)
    {
        cfg_music = 2;
    }
    if (cfg_sound == 1 && DSINIT() == 0)
    {
        cfg_sound = 2;
    }
    if (cfg_joypad == 1)
    {
        DIINIT();
        if (DIGETJOYNUM() == 0)
        {
            cfg_joypad = 0;
        }
    }
    initialize_sound_file();
    load_musiclist();
    mainskill(0) = 173;
    mainskill(1) = 106;
    mainskill(2) = 108;

    DIM3(cycle, 15, 5);
    cycle(0, 0) = 1;
    cycle(1, 0) = 2;
    cycle(2, 0) = 5;
    cycle(3, 0) = 7;
    cycle(4, 0) = 8;
    cycle(5, 0) = 9;
    cycle(6, 0) = 14;
    cycle(7, 0) = 15;
    cycle(8, 0) = 17;
    cycle(9, 0) = 26;
    cycle(10, 0) = -1;
    cycle(0, 1) = 1;
    cycle(1, 1) = 5;
    cycle(2, 1) = 7;
    cycle(3, 1) = 8;
    cycle(4, 1) = 14;
    cycle(5, 1) = -1;
    cycle(0, 2) = 10;
    cycle(1, 2) = 25;
    cycle(2, 2) = -1;
    cycle(0, 3) = 22;
    cycle(1, 3) = 24;
    cycle(2, 3) = -1;
    cycle(0, 4) = 2;
    cycle(1, 4) = -1;

    cyclemax(0) = 9;
    cyclemax(1) = 4;
    cyclemax(2) = 1;
    cyclemax(3) = 1;
    cyclemax(4) = 0;

    shadowmap(0) = 0;
    shadowmap(1) = 9;
    shadowmap(2) = 10;
    shadowmap(3) = 5;
    shadowmap(4) = 12;
    shadowmap(5) = 7;
    shadowmap(6) = 0;
    shadowmap(7) = 1;
    shadowmap(8) = 11;
    shadowmap(9) = 0;
    shadowmap(10) = 6;
    shadowmap(11) = 3;
    shadowmap(12) = 8;
    shadowmap(13) = 4;
    shadowmap(14) = 2;
    shadowmap(15) = 0;
    shadowmap(16) = 0;

    lastctrl = 1;

    DIM2(invicon, 40);
    SDIM3(invkey, 4, 40);
    invkey(0) = "";
    invkey(1) = ""s + key_inventory;
    invkey(2) = ""s + key_drop;
    invkey(3) = "";
    invkey(4) = "";
    invkey(5) = ""s + key_eat;
    invkey(6) = "";
    invkey(7) = ""s + key_read;
    invkey(8) = ""s + key_drink;
    invkey(9) = ""s + key_zap;
    invkey(10) = "";
    invkey(11) = "";
    invkey(12) = "";
    invkey(13) = "";
    invkey(14) = ""s + key_use;
    invkey(15) = ""s + key_open;
    invkey(16) = "";
    invkey(17) = ""s + key_dip;
    invkey(26) = ""s + key_throw;
    invicon(0) = -1;
    invicon(1) = 7;
    invicon(2) = 8;
    invicon(3) = -1;
    invicon(4) = -1;
    invicon(5) = 2;
    invicon(6) = -1;
    invicon(7) = 3;
    invicon(8) = 0;
    invicon(9) = 1;
    invicon(10) = 17;
    invicon(11) = -1;
    invicon(12) = -1;
    invicon(13) = -1;
    invicon(14) = 5;
    invicon(15) = 4;
    invicon(16) = -1;
    invicon(17) = 6;
    invicon(18) = -1;
    invicon(19) = -1;
    invicon(20) = -1;
    invicon(21) = -1;
    invicon(22) = 17;
    invicon(23) = -1;
    invicon(24) = 17;
    invicon(25) = 17;
    invicon(26) = 18;
    invicon(27) = -1;
    invicon(28) = -1;
    invicon(29) = -1;

    if (cfg_autonumlock)
    {
        // TODO
        // if NumLock key is pressed, send an event to release the key.
    }
}



void start_elona()
{
    gdata_year = 517;
    gdata_month = 8;
    gdata_day = 12;
    gdata_hour = 16;
    gdata_minute = 10;
    quickpage = 1;
    if (dirinfo(4) == u8"medit"s)
    {
        medit = 1;
        std::exit(1);
        return;
    }
    if (defload != ""s)
    {
        if (!fs::exists(fs::u8path(u8"./save/"s + defload + u8"/header.txt")))
        {
            if (fs::exists(
                    fs::u8path(u8"./save/sav_"s + defload + u8"/header.txt")))
            {
                defload = u8"sav_"s + defload;
            }
            else
            {
                defload = "";
            }
        }
        if (defload == ""s)
        {
            dialog(u8"Invalid defLoadFolder. name"s);
        }
        else
        {
            playerid = defload;
            mode = 3;
            music = 0;
            initialize_game();
            return;
        }
    }
    main_title_menu();
    return;
}



} // namespace


namespace elona
{


int main()
{
    cat::global.initialize();

    the_ability_db.initialize();
    the_character_db.initialize();
    the_class_db.initialize();
    the_item_db.initialize();
    the_race_db.initialize();
    the_trait_db.initialize();

    i18n::load();

    title(u8"Elona ver 1.22"s);
    try
    {
        initialize_elona();
        start_elona();
    }
    catch (elona_turn_sequence&)
    {
        main_loop();
    }
    return 0;
}



void main_title_menu()
{
    mode = 10;
    lomiaseaster = 0;
    music = 65;
    play_music();
    cs = 0;
    cs_bk = -1;
    keyrange = 6;
    key_list(0) = u8"a"s;
    key_list(1) = u8"b"s;
    key_list(2) = u8"c"s;
    key_list(3) = u8"d"s;
    key_list(4) = u8"e"s;
    key_list(5) = u8"f"s;
    pagesize = 0;
    redraw(0);
    gsel(2);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        pos(cnt % 4 * 180, cnt / 4 * 300);
        picload(fs::u8path(u8"./graphic/g"s + (cnt + 1) + u8".bmp"), 1);
    }
    gsel(4);
    gmode(0);
    pos(0, 0);
    picload(fs::u8path(u8"./graphic/title.bmp"), 1);
    gzoom(windoww, windowh, 4, 0, 0, 800, 600);
    gmode(2);
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 0);
    color(255, 255, 255);
    pos(20, 20);
    mes(u8"Elona version 1.22  Developed by Noa"s);
    color(0, 0, 0);
    pos(20, 38);
    if (jp)
    {
        mes(u8"Contributor MSL / View the credits for more"s);
    }
    else
    {
        mes(u8"Contributor f1r3fly, Sunstrike, Schmidt, Elvenspirit / View the credits for more"s);
    }
    if (jp)
    {
        s(0) = u8"冒険の道標"s;
        s(1) = strhint1;
    }
    else
    {
        s(0) = u8"Starting Menu"s;
        s(1) = strhint1;
    }
    windowshadow = 1;
    display_window(80, winposy(308, 1), 320, 320);
    cmbg = 4;
    x = ww / 5 * 4;
    y = wh - 80;
    gmode(4, 180, 300, 50);
    pos(wx + 160, wy + wh / 2);
    grotate(2, cmbg / 2 * 180, cmbg % 2 * 300, 0, x, y);
    gmode(2);
    if (jp)
    {
        s(0) = u8"Restore an adventurer"s;
        s(1) = u8"冒険を再開する"s;
        s(2) = u8"Generate an adventurer"s;
        s(3) = u8"新しい冒険者を作成する"s;
        s(4) = u8"Incarnate an adventurer"s;
        s(5) = u8"冒険者の引継ぎ"s;
        s(6) = u8"View the homepage"s;
        s(7) = u8"ホームページを開く"s;
        s(8) = u8"Configure"s;
        s(9) = u8"設定の変更"s;
        s(10) = u8"Exit"s;
        s(11) = u8"終了"s;
    }
    if (en)
    {
        s(0) = u8"Restore an Adventurer"s;
        s(1) = u8"Generate an Adventurer"s;
        s(2) = u8"Incarnate an Adventurer"s;
        s(3) = u8"View the Homepage"s;
        s(4) = u8"Options"s;
        s(5) = u8"Exit"s;
    }
    gsel(3);
    pos(960, 96);
    picload(fs::u8path(u8"./graphic/deco_title.bmp"), 1);
    gsel(0);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
label_2116_internal:
    if (cfg_autonumlock)
    {
        // TODO
        // if NumLock key is pressed, send an event to release the key.
    }
    redraw(0);
    tx += (rnd(10) + 2) * p(1);
    ty += (rnd(10) + 2) * p(2);
    if (rnd(10) == 0)
    {
        tx = rnd(800);
        ty = rnd(600);
        p(1) = rnd(9) - 4;
        p(2) = rnd(9) - 4;
    }
    f = 0;
    if (tx > 40 && tx < 500 && ty > 100 && ty < 450)
    {
        f = 1;
    }
    if (f == 0)
    {
        if (rnd(10) == 0)
        {
            f = 2;
        }
    }
    for (int cnt = 0; cnt < 6; ++cnt)
    {
        x = wx + 40;
        y = cnt * 35 + wy + 50;
        display_customkey(key_list(cnt), x, y);
        if (jp)
        {
            font(lang(cfg_font1, cfg_font2), 11 - en * 2, 0);
            pos(x + 40, y - 4);
            mes(s(cnt * 2));
            font(lang(cfg_font1, cfg_font2), 13 - en * 2, 0);
            cs_list(cs == cnt, s(cnt * 2 + 1), x + 40, y + 8);
        }
        else
        {
            font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
            cs_list(cs == cnt, s(cnt), x + 40, y + 1);
        }
    }
    cs_bk = cs;
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    if (key == u8"b"s)
    {
        snd(20);
        geneuse = "";
        main_menu_new_game();
        return;
    }
    if (key == u8"a"s)
    {
        snd(20);
        main_menu_continue();
        return;
    }
    if (key == u8"c"s)
    {
        snd(20);
        main_menu_incarnate();
        return;
    }
    if (key == u8"d"s)
    {
        snd(20);
        exec(homepage, 16);
    }
    if (key == u8"e"s)
    {
        snd(20);
        set_option();
        return;
    }
    if (key == u8"f"s)
    {
        snd(20);
        await(400);
        finish_elona();
        return;
    }
    goto label_2116_internal;
}



void main_menu_new_game()
{
    if (cfg_wizard)
    {
        gdata_wizard = 1;
    }
    if (geneuse != ""s)
    {
        load_gene_files();
    }
    redraw(0);
    rc = 0;
    mode = 1;
    cm = 1;
    gsel(4);
    pos(0, 0);
    picload(fs::u8path(u8"./graphic/void.bmp"), 1);
    gzoom(windoww, windowh, 4, 0, 0, 800, 600);
    gsel(2);
    for (int cnt = 0; cnt < 8; ++cnt)
    {
        pos(cnt % 4 * 180, cnt / 4 * 300);
        picload(fs::u8path(u8"./graphic/g"s + (cnt + 1) + u8".bmp"), 1);
    }
    gsel(3);
    pos(960, 96);
    picload(fs::u8path(u8"./graphic/deco_cm.bmp"), 1);
    gsel(0);
    if (range::distance(filesystem::dir_entries{
            fs::u8path(u8"./save"), filesystem::dir_entries::type::dir})
        >= 5)
    {
        redraw(0);
        keyrange = 0;
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        s = lang(
            u8"これ以上は冒険者を保存できない。"s,
            u8"Save slots are full. You have to delete some of your adventurers."s);
        draw_caption();
        redraw(1);
    label_1542_internal:
        key_check();
        cursor_check();
        await(cfg_wait1);
        if (key != ""s)
        {
            main_title_menu();
            return;
        }
        goto label_1542_internal;
        main_title_menu();
        return;
    }
    character_making_select_race();
    return;
}



void character_making_select_race()
{
    redraw(0);
    cs = 0;
    cs_bk = -1;
    pagesize = 16;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"やあ、待っていたよ。早速旅の支度をしようか。"s,
        u8"Welcome traveler, I've been looking for you."s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    listmax = 0;
    for (const auto& race : the_race_db.get_available_races(false))
    {
        listn(1, listmax) = race.get().id;
        list(0, listmax) = 0;
        ++listmax;
    }
    if (cfg_extrarace)
    {
        for (const auto& race : the_race_db.get_available_races(true))
        {
            listn(1, listmax) = race.get().id;
            list(0, listmax) = 1;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        listn(0, cnt) = i18n::_(u8"race", listn(1, cnt), u8"name");
        if (list(0, cnt) == 1)
        {
            listn(0, cnt) = u8"(extra)"s + listn(0, cnt);
        }
    }
    windowshadow = 1;
label_1545_internal:
    cs_bk = -1;
    pagemax = (listmax - 1) / pagesize;
    if (page < 0)
    {
        page = pagemax;
    }
    else if (page > pagemax)
    {
        page = 0;
    }
label_1546_internal:
    redraw(0);
    if (cs != cs_bk)
    {
        s(0) = lang(u8"種族の選択"s, u8"Race Selection"s);
        s(1) = strhint3b;
        display_window(
            (windoww - 680) / 2 + inf_screenx, winposy(500, 1) + 20, 680, 500);
        ++cmbg;
        x = ww / 5 * 2;
        y = wh - 80;
        gmode(4, 180, 300, 50);
        pos(wx + ww / 4, wy + wh / 2);
        grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
        gmode(2);
        display_topic(lang(u8"選択できる種族"s, u8"Race"s), wx + 28, wy + 30);
        display_topic(lang(u8"種族の説明"s, u8"Detail"s), wx + 188, wy + 30);
        font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        for (int cnt = 0, cnt_end = (pagesize); cnt < cnt_end; ++cnt)
        {
            p = page * pagesize + cnt;
            if (p >= listmax)
            {
                break;
            }
            key_list(cnt) = key_select(cnt);
            keyrange = cnt + 1;
            display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
            cs_list(cs == cnt, listn(0, p), wx + 64, wy + 66 + cnt * 19 - 1);
        }
        cs_bk = cs;
        pos(wx + 200, wy + 66);
        del_chara(0);
        access_race_info(3, listn(1, page * pagesize + cs));
        access_race_info(11, listn(1, page * pagesize + cs));
        show_race_or_class_info(0, 0);
    }
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = page * pagesize + cnt;
            break;
        }
        else
        {
            p = -1;
        }
    }
    if (p != -1)
    {
        cmrace(0) = listn(1, p);
        cmrace(1) = listn(0, p);
        access_race_info(11, cmrace);
        character_making_select_sex();
        return;
    }
    if (key == key_pageup)
    {
        if (pagemax != 0)
        {
            snd(1);
            ++page;
            goto label_1545_internal;
        }
    }
    if (key == key_pagedown)
    {
        if (pagemax != 0)
        {
            snd(1);
            --page;
            goto label_1545_internal;
        }
    }
    if (key == key_cancel)
    {
        main_title_menu();
        return;
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        character_making_select_race();
        return;
    }
    goto label_1546_internal;
}



void character_making_select_sex(bool label_1548_flg)
{
    if (label_1548_flg)
    {
        snd(102);
    }
    redraw(0);
    cs = 0;
    cs_bk = -1;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(u8"男性と女性に能力の違いはない。"s, u8"What's your gender?"s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    windowshadow = 1;
label_1549_internal:
    redraw(0);
    s(0) = lang(u8"性別の選択"s, u8"Gender Selection"s);
    s(1) = strhint3b;
    display_window(
        (windoww - 370) / 2 + inf_screenx, winposy(168, 1) - 20, 370, 168);
    x = ww / 2;
    y = wh - 60;
    gmode(4, 180, 300, 30);
    pos(wx + ww / 2, wy + wh / 2);
    grotate(2, 0, 0, 0, x, y);
    gmode(2);
    display_topic(lang(u8"性別の候補"s, u8"Gender"s), wx + 28, wy + 30);
    listn(0, 0) = cnven(i18n::_(u8"ui", u8"male"));
    listn(0, 1) = cnven(i18n::_(u8"ui", u8"female"));
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    for (int cnt = 0; cnt < 2; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        pos(wx + 38, wy + 66 + cnt * 19 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
    }
    cs_bk = cs;
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    if (key == key_select(0))
    {
        cmsex = 0;
        character_making_select_class();
        return;
    }
    if (key == key_select(1))
    {
        cmsex = 1;
        character_making_select_class();
        return;
    }
    if (key == key_cancel)
    {
        main_menu_new_game();
        return;
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        character_making_select_sex(false);
    }
    goto label_1549_internal;
}



void character_making_select_class(bool label_1551_flg)
{
    if (label_1551_flg)
    {
        snd(20);
    }
    redraw(0);
    cs = 0;
    cs_bk = -1;
    page = 0;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"職業や種族は、初期の能力だけでなく、成長の方向性に影響するんだ。"s,
        u8"Your class and race determine growth rate of your skills and attributes."s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    listmax = 0;
    for (const auto& class_ : the_class_db.get_available_classes(false))
    {
        listn(1, listmax) = class_.get().id;
        ++listmax;
    }
    if (cfg_extraclass)
    {
        for (const auto& class_ : the_class_db.get_available_classes(true))
        {
            listn(1, listmax) = class_.get().id;
            ++listmax;
        }
    }
    for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
    {
        access_class_info(2, listn(1, cnt));
        listn(0, cnt) = classname;
    }
    windowshadow = 1;
label_1552_internal:
    if (cs != cs_bk)
    {
        redraw(0);
        s(0) = lang(u8"職業の選択"s, u8"Class Selection"s);
        s(1) = strhint3b;
        display_window(
            (windoww - 680) / 2 + inf_screenx, winposy(500, 1) + 20, 680, 500);
        ++cmbg;
        x = ww / 5 * 2;
        y = wh - 80;
        gmode(4, 180, 300, 50);
        pos(wx + ww / 4, wy + wh / 2);
        grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
        gmode(2);
        display_topic(lang(u8"選択できる職業"s, u8"Class"s), wx + 28, wy + 30);
        display_topic(lang(u8"職業の説明"s, u8"Detail"s), wx + 188, wy + 30);
        font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        for (int cnt = 0, cnt_end = (listmax); cnt < cnt_end; ++cnt)
        {
            key_list(cnt) = key_select(cnt);
            keyrange = cnt + 1;
            display_key(wx + 38, wy + 66 + cnt * 19 - 2, cnt);
            if (jp)
            {
                s = listn(0, cnt);
            }
            else
            {
                s = cnven(listn(1, cnt));
            }
            cs_list(cs == cnt, s, wx + 64, wy + 66 + cnt * 19 - 1);
        }
        cs_bk = cs;
        pos(wx + 200, wy + 66);
        del_chara(0);
        access_class_info(3, listn(1, cs));
        access_class_info(11, listn(1, cs));
        show_race_or_class_info(0, 1);
        redraw(1);
    }
    await(cfg_wait1);
    key_check();
    cursor_check();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = page * pagesize + cnt;
            break;
        }
        else
        {
            p = -1;
        }
    }
    if (p != -1)
    {
        cmclass = listn(1, p);
        character_making_role_attributes();
        return;
    }
    if (key == key_cancel)
    {
        character_making_select_sex(false);
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        character_making_select_class(false);
    }
    goto label_1552_internal;
}



void character_making_role_attributes(bool label_1554_flg)
{
    elona_vector1<int> cmlock;
    if (label_1554_flg)
    {
        snd(101);
        DIM2(cmlock, 10);
        cmlock(8) = 2;
    }
label_1554:
    redraw(0);
    cs = 0;
    cs_bk = -1;
    pagesize = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"死にたくないなら、ある程度の能力は必要だね。"s,
        u8"You should prepare well, if you want to survive long enough in Irva."s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    del_chara(0);
    access_race_info(3, cmrace);
    access_class_info(3, cmclass);
    cdata[rc].level = 1;
    for (int cnt = 10, cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
    {
        if (cmlock(cnt - 10) == 0)
        {
            sdata.get(cnt, rc).original_level -=
                rnd(sdata.get(cnt, rc).original_level / 2 + 1);
            cmstats(cnt - 10) = sdata.get(cnt, rc).original_level * 1'000'000
                + sdata.get(cnt, rc).experience * 1'000
                + sdata.get(cnt, rc).potential;
        }
    }
    listmax = 0;
    list(0, 0) = 0;
    listn(0, 0) = lang(u8"リロール"s, u8"Reroll"s);
    ++listmax;
    list(0, 1) = 0;
    listn(0, 1) = lang(u8"決定"s, u8"Proceed"s);
    ++listmax;
    for (int cnt = 10, cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
    {
        list(0, listmax) = cmstats(cnt - 10);
        listn(0, listmax) = i18n::_(u8"ability", std::to_string(cnt), u8"name");
        ++listmax;
    }
    windowshadow = 1;
label_1555_internal:
    redraw(0);
    s(0) = lang(u8"能力のロール"s, u8"Attb Reroll"s);
    s(1) = strhint3b;
    display_window(
        (windoww - 360) / 2 + inf_screenx, winposy(352, 1) - 20, 360, 352);
    x = 150;
    y = 240;
    gmode(4, 180, 300, 30);
    pos(wx + 85, wy + wh / 2);
    grotate(2, 0, 0, 0, x, y);
    gmode(2);
    display_topic(lang(u8"能力"s, u8"Attributes"s), wx + 28, wy + 30);
    font(lang(cfg_font1, cfg_font2), 12 + sizefix - en * 2, 0);
    pos(wx + 175, wy + 52);
    mes(lang(
        u8"ロックされた能力は\n変化しません"s,
        u8"Locked items will\nnot change."s));
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(wx + 180, wy + 84);
    mes(lang(u8"残りロック: "s, u8"Locks left: "s) + cmlock(8));
    for (int cnt = 0; cnt < 10; ++cnt)
    {
        key_list(cnt) = key_select(cnt);
        keyrange = cnt + 1;
        pos(wx + 38, wy + 66 + cnt * 23 - 2);
        gcopy(3, cnt * 24 + 72, 30, 24, 18);
        font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 23 - 1);
        font(lang(cfg_font1, cfg_font2), 15 - en * 2, 1);
        if (cnt >= 2)
        {
            pos(wx + 198, wy + 76 + cnt * 23);
            gmode(2, inf_tiles, inf_tiles);
            grotate(1, (cnt - 2) * inf_tiles, 672, 0, inf_tiles, inf_tiles);
            pos(wx + 210, wy + 66 + cnt * 23);
            mes(""s + list(0, cnt) / 1000000);
            if (cmlock(cnt - 2) == 1)
            {
                font(lang(cfg_font1, cfg_font2), 12 - en * 2, 1);
                pos(wx + 240, wy + 66 + cnt * 23 + 2);
                color(20, 20, 140);
                mes(u8"Locked!"s);
                color(0, 0, 0);
            }
        }
    }
    cs_bk = cs;
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = cnt;
            break;
        }
        else
        {
            p = -1;
        }
    }
    if (p != -1)
    {
        if (p == 0)
        {
            snd(103);
            goto label_1554;
        }
        if (p == 1)
        {
            character_making_select_feats_and_alias();
            return;
        }
        if (cmlock(p - 2) != 0)
        {
            ++cmlock(8);
            cmlock(p - 2) = 0;
        }
        else if (cmlock(8) > 0)
        {
            cmlock(p - 2) = 1;
            --cmlock(8);
        }
        snd(20);
    }
    if (key == key_cancel)
    {
        character_making_select_class(false);
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        character_making_role_attributes(false);
    }
    goto label_1555_internal;
}



void character_making_select_feats_and_alias(bool label_1558_flg)
{
    if (label_1558_flg)
    {
        gdata_acquirable_feat_count = 3;
        DIM2(trait, 500);
        DIM2(spact, 500);
        gain_race_feat();
        redraw(0);
        gmode(0);
        pos(0, 0);
        gcopy(4, 0, 0, windoww, windowh);
        gmode(2);
        s = lang(
            u8"フィートとは、君の持っている有益な特徴だ。3つまで選べるよ。"s,
            u8"Choose your feats wisely."s);
        draw_caption();
        font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
        pos(20, windowh - 20);
        mes(u8"Press F1 to show help."s);
        if (geneuse != ""s)
        {
            pos(20, windowh - 36);
            mes(u8"Gene from "s + geneuse);
        }
        int stat = feat_menu();
        clear_background_in_character_making();
        if (stat == -1)
        {
            character_making_select_feats_and_alias();
            return;
        }
        if (stat == 0)
        {
            character_making_role_attributes(false);
        }
    }
    redraw(0);
    pagemax = 0;
    page = 0;
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"有名になると、名前とは別の通り名で呼ばれることがあるらしい。"s,
        u8"Choose your Alias."s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    windowshadow = 1;
    cs = 0;
    cs_bk = -1;
    list(0, 0) = -1;
label_1559_internal:
    redraw(0);
    if (cs != cs_bk)
    {
        s(0) = lang(u8"異名の選択"s, u8"Alias Selection"s);
        s(1) = strhint3b;
        display_window(
            (windoww - 400) / 2 + inf_screenx, winposy(458, 1) + 20, 400, 458);
        ++cmbg;
        x = ww / 3 * 2;
        y = wh - 80;
        gmode(4, 180, 300, 40);
        pos(wx + ww / 2, wy + wh / 2);
        grotate(2, cmbg / 4 % 4 * 180, cmbg / 4 / 4 % 2 * 300, 0, x, y);
        gmode(2);
        display_topic(lang(u8"異名の候補"s, u8"Alias List"s), wx + 28, wy + 30);
        font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
        for (int cnt = 0; cnt < 17; ++cnt)
        {
            key_list(cnt) = key_select(cnt);
            keyrange = cnt + 1;
            if (list(0, 0) == -1)
            {
                if (gdata_wizard == 1)
                {
                    listn(0, cnt) = u8"*Debug*"s;
                }
                else
                {
                    listn(0, cnt) = random_title();
                }
            }
            if (cnt == 0)
            {
                listn(0, cnt) = lang(u8"リロール"s, u8"Reroll"s);
            }
            pos(wx + 38, wy + 66 + cnt * 19 - 2);
            gcopy(3, cnt * 24 + 72, 30, 24, 18);
            cs_list(cs == cnt, listn(0, cnt), wx + 64, wy + 66 + cnt * 19 - 1);
        }
        cs_bk = cs;
        list(0, 0) = 0;
    }
    redraw(1);
    await(cfg_wait1);
    key_check();
    cursor_check();
    for (int cnt = 0, cnt_end = (keyrange); cnt < cnt_end; ++cnt)
    {
        if (key == key_select(cnt))
        {
            p = cnt;
            break;
        }
        else
        {
            p = -1;
        }
    }
    if (p != -1)
    {
        if (key == key_select(0))
        {
            list(0, 0) = -1;
            snd(103);
            cs_bk = -1;
        }
        else
        {
            cmaka = listn(0, p);
            character_making_final_phase();
            return;
        }
    }
    if (key == key_cancel)
    {
        character_making_select_feats_and_alias();
        return;
    }
    if (getkey(snail::key::f1))
    {
        show_game_help();
        character_making_select_feats_and_alias(false);
    }
    goto label_1559_internal;
}



void character_making_final_phase()
{
    int cmportrait = 0;
    std::string cmname;
    pcc(15, 0) = 0;
label_1561_internal:
    redraw(0);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"君の見た目を知っておきたいな。まあ、後からいつでも変えられるけどね。"s,
        u8"What you look like? Don't worry, you can change them later."s);
    draw_caption();
    font(lang(cfg_font1, cfg_font2), 13 - en * 2, 1);
    pos(20, windowh - 20);
    mes(u8"Press F1 to show help."s);
    if (geneuse != ""s)
    {
        pos(20, windowh - 36);
        mes(u8"Gene from "s + geneuse);
    }
    cbitmod(967, 0, 1);
    {
        int stat = change_appearance();
        if (stat == 0)
        {
            clear_background_in_character_making();
            character_making_select_feats_and_alias(false);
        }
        if (stat == -1)
        {
            show_game_help();
            clear_background_in_character_making();
            goto label_1561_internal;
        }
    }
    clear_background_in_character_making();
    cmportrait = cdata[rc].portrait;
label_1562_internal:
    snd(94);
label_1563_internal:
    redraw(0);
    gmode(0);
    pos(0, 0);
    gcopy(4, 0, 0, windoww, windowh);
    gmode(2);
    s = lang(
        u8"決定ｷｰを押すことで、生い立ちをリロールできる。"s,
        u8"Hit the enter key to reroll your personal history."s);
    draw_caption();
    del_chara(0);
    access_race_info(3, cmrace);
    access_class_info(3, cmclass);
    cdatan(0, rc) = u8"????"s;
    cdatan(1, rc) = cmaka;
    cdata[rc].level = 1;
    for (int cnt = 10, cnt_end = cnt + (8); cnt < cnt_end; ++cnt)
    {
        sdata.get(cnt, rc).original_level = cmstats(cnt - 10) / 1'000'000;
        sdata.get(cnt, rc).experience = cmstats(cnt - 10) % 1'000'000 / 1'000;
        sdata.get(cnt, rc).potential = cmstats(cnt - 10) % 1'000;
    }
    initialize_character();
    initialize_pc_character();
    cdata[rc].portrait = cmportrait;
    create_pcpic(0, true);
    mode = 1;
    csctrl = 1;
    menucycle = 0;
    {
        int stat = show_character_sheet();
        if (stat == 0)
        {
            nowindowanime = 1;
            clear_background_in_character_making();
            goto label_1563_internal;
        }
    }
    redraw(0);
    gsel(2);
    pos(0, 0);
    gmode(0);
    gcopy(0, 0, 100, windoww, windowh - 100);
    gsel(0);
    clear_background_in_character_making();
    s = lang(u8"満足できたかな？"s, u8"Are you satisfied now?"s);
    draw_caption();
    promptl(0, promptmax) = lang(u8"はい"s, u8"Yes"s);
    promptl(1, promptmax) = u8"a"s;
    promptl(2, promptmax) = ""s + promptmax;
    ++promptmax;
    promptl(0, promptmax) = lang(u8"いいえ"s, u8"No"s);
    promptl(1, promptmax) = u8"b"s;
    promptl(2, promptmax) = ""s + promptmax;
    ++promptmax;
    promptl(0, promptmax) = lang(u8"最初から"s, u8"Restart"s);
    promptl(1, promptmax) = u8"c"s;
    promptl(2, promptmax) = ""s + promptmax;
    ++promptmax;
    show_prompt(promptx, 240, 160);
    snd(20);
    if (rtval == 1 || rtval == -1)
    {
        goto label_1562_internal;
    }
    if (rtval == 2)
    {
        nowindowanime = 0;
        main_menu_new_game();
        return;
    }
    redraw(0);
    gmode(0);
    pos(0, 100);
    gcopy(2, 0, 0, windoww, windowh - 100);
    gmode(2);
    s = lang(
        u8"最後の質問だ。君の名前は？"s, u8"Last question. What's your name?"s);
    draw_caption();
label_1565_internal:
    inputlog = "";
    input_mode = 1;
    show_number_of_text_prompt(
        (windoww - 230) / 2 + inf_screenx, winposy(120), 10, 0);
    cmname = ""s + inputlog;
    if (cmname == ""s || cmname == u8" "s)
    {
        cmname = randomname();
    }
    playerid = u8"sav_"s + cmname;
    const auto save_dir = fs::u8path(u8"./save");
    if (range::any_of(
            filesystem::dir_entries{save_dir,
                                    filesystem::dir_entries::type::dir},
            [&](const auto& entry) {
                return entry.path().filename().generic_u8string() == playerid;
            }))
    {
        redraw(0);
        gmode(0);
        pos(0, 100);
        gcopy(2, 0, 0, windoww, windowh - 100);
        gmode(2);
        s = lang(
            u8"あいにく、その名前の冒険者はすでに存在する。"s,
            u8"Sorry, but the name is already taken."s);
        draw_caption();
        goto label_1565_internal;
    }
    snd(101);
    cdatan(0, rc) = cmname;
    cdata[0].gold = 400 + rnd(200);
    if (geneuse != ""s)
    {
        get_inheritance();
    }
    else
    {
        for (int i = 0; i < 400; ++i)
        {
            mat(i) = 0;
        }
    }
    await(250);
    mode = 5;
    initialize_game();
    return;
}



void show_race_or_class_info(int CNT, int val0)
{
    if (val0 == 1)
    {
        chara_preparepic(ref1, CNT);
        pos(wx + 380, wy - chipc(3, ref1) + 60);
        gcopy(5, 0, 960, inf_tiles, chipc(3, ref1));
        chara_preparepic(ref2, CNT);
        pos(wx + 350, wy - chipc(3, ref1) + 60);
        gcopy(5, 0, 960, inf_tiles, chipc(3, ref1));
        pos(wx + 460, wy + 38);
        mes(lang(u8"種族: "s, u8"Race: "s) + cmrace(1));
    }
    else
    {
        gmode(4, chipc(2, ref1), chipc(3, ref1), 40);
        chara_preparepic(ref1, CNT);
        pos(wx + 480, wy + 96);
        grotate(5, 0, 960, 0, chipc(2, ref1) * 2, chipc(3, ref1) * 2);
        chara_preparepic(ref2, CNT);
        pos(wx + 350, wy + 96);
        grotate(5, 0, 960, 0, chipc(2, ref1) * 2, chipc(3, ref1) * 2);
        gmode(2);
    }
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    tx = wx + 230;
    ty = wy + 62;
    talk_conv(buff, 60 + en * 2);
    pos(tx - 20, ty);
    mes(buff);
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    tx = wx + 200;
    ty = wy + 166;
    display_topic(lang(u8"能力ボーナス"s, u8"Attribute Bonus"s), tx, ty);
    ty += 34;
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    if (jp)
    {
        s(0) = u8"皆無"s;
        s(1) = u8"最高"s;
        s(2) = u8"理想的"s;
        s(3) = u8"高い"s;
        s(4) = u8"やや高い"s;
        s(5) = u8"普通"s;
        s(6) = u8"少し"s;
        s(7) = u8"微々"s;
    }
    if (en)
    {
        s(0) = u8"None"s;
        s(1) = u8"Best"s;
        s(2) = u8"Great"s;
        s(3) = u8"Good"s;
        s(4) = u8"Not bad"s;
        s(5) = u8"Normal"s;
        s(6) = u8"Little"s;
        s(7) = u8"Slight"s;
    }
    for (int cnt = 0; cnt < 3; ++cnt)
    {
        int cnt2 = cnt;
        for (int cnt = 0; cnt < 3; ++cnt)
        {
            if (cnt2 == 2)
            {
                if (cnt == 2)
                {
                    break;
                }
            }
            r = cnt2 * 3 + cnt + 10;
            p = 0;
            for (int cnt = 0; cnt < 1; ++cnt)
            {
                if (sdata.get(r, 0).original_level > 13)
                {
                    p = 1;
                    color(0, 0, 200);
                    break;
                }
                if (sdata.get(r, 0).original_level > 11)
                {
                    p = 2;
                    color(0, 0, 200);
                    break;
                }
                if (sdata.get(r, 0).original_level > 9)
                {
                    p = 3;
                    color(0, 0, 150);
                    break;
                }
                if (sdata.get(r, 0).original_level > 7)
                {
                    p = 4;
                    color(0, 0, 150);
                    break;
                }
                if (sdata.get(r, 0).original_level > 5)
                {
                    p = 5;
                    color(0, 0, 0);
                    break;
                }
                if (sdata.get(r, 0).original_level > 3)
                {
                    p = 6;
                    color(150, 0, 0);
                    break;
                }
                if (sdata.get(r, 0).original_level > 0)
                {
                    p = 7;
                    color(200, 0, 0);
                    break;
                }
                color(120, 120, 120);
            }
            pos(cnt * 150 + tx + 13, ty + 7);
            gmode(2, inf_tiles, inf_tiles);
            grotate(
                1, (cnt2 * 3 + cnt) * inf_tiles, 672, 0, inf_tiles, inf_tiles);
            pos(cnt * 150 + tx + 32, ty);
            mes(strmid(
                    i18n::_(u8"ability", std::to_string(r), u8"name"),
                    0,
                    jp ? 6 : 3)
                + u8": "s + s(p));
            color(0, 0, 0);
        }
        ty += 16;
    }
    ty = wy + 260;
    display_topic(lang(u8"獲得技能"s, u8"Trained Skill"s), tx, ty);
    ty += 34;
    font(lang(cfg_font1, cfg_font2), 14 - en * 2, 0);
    r = 0;
    s = lang(u8"武器の専門  "s, u8"Proficient in "s);
    for (int cnt = 100, cnt_end = cnt + (50); cnt < cnt_end; ++cnt)
    {
        if (sdata.get(cnt, 0).original_level != 0)
        {
            if (r != 0)
            {
                s += u8","s;
            }
            s += i18n::_(u8"ability", std::to_string(cnt), u8"name");
            ++r;
        }
    }
    if (r != 0)
    {
        pos(tx + 13, ty + 6);
        gmode(2, inf_tiles, inf_tiles);
        grotate(1, 0, 672, 0, inf_tiles, inf_tiles);
        pos(tx + 32, ty);
        mes(s);
        ty += 14;
    }
    for (int cnt = 150, cnt_end = cnt + (450); cnt < cnt_end; ++cnt)
    {
        if (sdata.get(cnt, 0).original_level != 0)
        {
            s = i18n::_(u8"ability", std::to_string(cnt), u8"name");
            if (jp)
            {
                lenfix(s, 12);
            }
            else
            {
                lenfix(s, 16);
            }
            pos(tx + 13, ty + 6);
            gmode(2, inf_tiles, inf_tiles);
            grotate(
                1,
                (the_ability_db[cnt].related_basic_attribute - 10) * inf_tiles,
                672,
                0,
                inf_tiles,
                inf_tiles);
            s(1) = i18n::_(u8"ability", std::to_string(cnt), u8"description");
            if (en)
            {
                if (strlen_u(s(1)) > 45)
                {
                    s(1) = strmid(s(1), 0, 42) + u8"..."s;
                }
            }
            pos(tx + 32, ty);
            mes(s + s(1));
            ty += 14;
        }
    }
    return;
}



void initialize_game()
{
    mtilefilecur = -1;
    firstturn = 1;
    msgtemp = u8"  Lafrontier presents Elona ver 1.22. Welcome traveler! "s;
    if (cfg_net)
    {
        initialize_server_info();
    }
    if (mode == 4)
    {
        for (int cnt = 0; cnt < 9; ++cnt)
        {
            gdata(120 + cnt) = 5000;
        }
        gdata_version = 1220;
        gdata(41) = 424;
        gdata(42) = 300;
        gdata(43) = 631;
        gdata_next_inventory_serial_id = 1000;
        gdata_next_shelter_serial_id = 100;
        playerid = u8"sav_noa"s;
        gdata_pc_home_x = 22;
        gdata_pc_home_y = 21;
        gdata_previous_map = -1;
        gdata_random_seed = rnd(800) + 2;
        gdata(9) = rnd(200) + 2;
        gdata_current_map = 4;
        gdata_current_dungeon_level = 0;
        gdata_entrance_type = 7;
        mapstartx = 22;
        mapstarty = 21;
        gdata_current_map = 5;
        gdata_current_dungeon_level = 1;
        gdata_entrance_type = 7;
        mapstartx = 10;
        mapstarty = 23;
        initlv = 50;
        rc = 0;
        flt(100);
        characreate(0, 84, -3, 0);
        initialize_pc_character();
        gdata_year = 517;
        gdata_month = 12;
        gdata_day = 30;
        gdata_hour = 1;
        gdata_minute = 10;
        gdata_played_scene = 50;
        gdata_has_not_been_to_vernis = 1;
        adata(30, 7) = 4;
        gdata(850) = adata(30, gdata_current_map);
        gdata_acquirable_feat_count = 2;
        gdata_save_count_of_little_sister = 1000;
        gdata_rights_to_succeed_to = 1000;
        gdata_home_scale = 0;
        gdata_number_of_waiting_guests = 2;
        gdata_charge_power = 1000;
        cdata[0].god_id = core_god::int2godid(2);
        cdata[0].piety_point = 1000;
        cdata[0].praying_point = 1000;
        gdata_pael_and_her_mom = 1000;
        cdata[0].gold += 1000000;
        cdata[0].platinum_coin = 30;
        cdata[0].fame = 65000;
        gdata_main_quest_flag = 100;
        r1 = 0;
        refresh_character();
        flt();
        itemcreate(0, 284, -1, -1, 0);
        inv[ci].number = 20;
        inv[ci].curse_state = 1;
        flt();
        itemcreate(0, 127, -1, -1, 0);
        inv[ci].number = 20;
        inv[ci].curse_state = 1;
        flt();
        itemcreate(0, 617, -1, -1, 0);
        inv[ci].number = 20;
        flt();
        itemcreate(0, 671, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 749, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 748, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 601, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 342, -1, -1, 0);
        inv[ci].number = 12;
        flt();
        itemcreate(0, 343, -1, -1, 0);
        inv[ci].number = 50;
        flt();
        itemcreate(0, 519, -1, -1, 0);
        inv[ci].number = 50;
        inv[ci].color = 4;
        flt();
        itemcreate(0, 622, -1, -1, 0);
        inv[ci].number = 50000;
        flt();
        itemcreate(0, 603, -1, -1, 0);
        inv[ci].number = 5;
        flt();
        itemcreate(0, 620, -1, -1, 0);
        inv[ci].number = 5;
        flt();
        itemcreate(0, 736, -1, -1, 0);
        inv[ci].number = 5;
        flt();
        itemcreate(0, 566, -1, -1, 0);
        inv[ci].number = 5;
        flt();
        itemcreate(0, 516, -1, -1, 0);
        inv[ci].number = 5;
        inv[ci].curse_state = 1;
        flt();
        itemcreate(0, 262, -1, -1, 0);
        inv[ci].number = 5;
        flt();
        itemcreate(0, 632, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].curse_state = -1;
        flt();
        itemcreate(0, 632, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].curse_state = 0;
        flt();
        itemcreate(0, 204, -1, -1, 0);
        inv[ci].subname = 330;
        inv[ci].number = 10;
        flt();
        itemcreate(0, 636, -1, -1, 0);
        inv[ci].number = 3;
        inv[ci].curse_state = 0;
        flt();
        itemcreate(0, 342, -1, -1, 0);
        inv[ci].count = 100;
        flt();
        itemcreate(0, 350, -1, -1, 0);
        inv[ci].number = 20;
        flt();
        itemcreate(0, 707, -1, -1, 0);
        flt();
        itemcreate(0, 719, -1, -1, 0);
        flt();
        itemcreate(0, 666, -1, -1, 0);
        flt();
        itemcreate(0, 686, -1, -1, 0);
        flt();
        itemcreate(0, 721, -1, -1, 0);
        flt();
        itemcreate(0, 772, -1, -1, 0);
        flt();
        itemcreate(0, 773, -1, -1, 0);
        flt();
        itemcreate(0, 774, -1, -1, 0);
        flt();
        itemcreate(0, 775, -1, -1, 0);
        flt();
        itemcreate(0, 776, -1, -1, 0);
        flt();
        itemcreate(0, 777, -1, -1, 0);
        flt();
        itemcreate(0, 778, -1, -1, 0);
        flt();
        itemcreate(0, 779, -1, -1, 0);
        flt();
        itemcreate(0, 780, -1, -1, 0);
        flt();
        itemcreate(0, 781, -1, -1, 0);
        flt();
        itemcreate(0, 782, -1, -1, 0);
        flt();
        itemcreate(0, 784, -1, -1, 0);
        flt();
        itemcreate(0, 785, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 786, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 787, -1, -1, 0);
        flt();
        itemcreate(0, 788, -1, -1, 0);
        flt();
        itemcreate(0, 789, -1, -1, 0);
        flt();
        itemcreate(0, 790, -1, -1, 0);
        flt();
        itemcreate(0, 791, -1, -1, 0);
        flt();
        itemcreate(0, 792, -1, -1, 0);
        flt();
        itemcreate(0, 260, -1, -1, 0);
        inv[ci].number = 100;
        gdata(41) = 140789;
        gdata(42) = 140790;
        for (int cnt = 0; cnt < 1200; ++cnt)
        {
            recipememory(cnt) = 1;
        }
        flt();
        itemcreate(0, 783, -1, -1, 0);
        flt();
        itemcreate(0, 783, -1, -1, 0);
        flt();
        itemcreate(0, 783, -1, -1, 0);
        inv[ci].subname = 1187;
        flt();
        itemcreate(0, 783, -1, -1, 0);
        inv[ci].subname = 955;
        itemcreate(0, 672, -1, -1, 0);
        inv[ci].param1 = 164;
        flt();
        itemcreate(0, 566, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].curse_state = 1;
        flt();
        itemcreate(0, 566, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].curse_state = -1;
        flt();
        itemcreate(0, 566, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 55, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 385, -1, -1, 0);
        inv[ci].number = 10;
        flt();
        itemcreate(0, 672, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].param1 = 169;
        flt();
        itemcreate(0, 672, -1, -1, 0);
        inv[ci].number = 10;
        inv[ci].param1 = 162;
        flt();
        itemcreate(0, 771, -1, -1, 0);
        inv[ci].number = 100;
        flt();
        itemcreate(0, 761, -1, -1, 0);
        flt();
        itemcreate(0, 769, -1, -1, 0);
        flt();
        itemcreate(0, 763, -1, -1, 0);
        flt();
        itemcreate(0, 764, -1, -1, 0);
        flt();
        itemcreate(0, 768, -1, -1, 0);
        flt();
        itemcreate(0, 766, -1, -1, 0);
        flt();
        {
            int stat = itemcreate(0, 752, -1, -1, 0);
            if (stat != 0)
            {
                inv[ci].param3 = 240;
                inv[ci].number = 50;
            }
        }
        flt();
        {
            int stat = itemcreate(0, 755, -1, -1, 0);
            if (stat != 0)
            {
                inv[ci].param3 = 240;
                inv[ci].number = 50;
            }
        }
        flt();
        {
            int stat = itemcreate(0, 756, -1, -1, 0);
            if (stat != 0)
            {
                inv[ci].param3 = 240;
                inv[ci].number = 50;
            }
        }
        for (int cnt = 0; cnt < 40; ++cnt)
        {
            flt(50, 5);
            flttypemajor = 56000;
            itemcreate(0, -1, -1, -1, 0);
            flt(50, 5);
            flttypemajor = 34000;
            itemcreate(0, -1, -1, -1, 0);
            flt(50, 5);
            flttypemajor = 32000;
            itemcreate(0, -1, -1, -1, 0);
        }
        cbitmod(20, 0, 1);
        mode = 0;
        refresh_burden_state();
        for (int cnt = 0; cnt < 55; ++cnt)
        {
            mat(cnt) = 200;
        }
        create_all_adventurers();
        create_pcpic(0, true);
        cdatan(1, 0) = random_title();
        cdatan(0, 0) = randomname();
        mode = 2;
    }
    if (mode == 5)
    {
        gdata_year = 517;
        gdata_month = 8;
        gdata_day = 12;
        gdata_hour = 1;
        gdata_minute = 10;
        gdata_pc_home_x = 22;
        gdata_pc_home_y = 21;
        gdata_previous_map = -1;
        gdata(850) = 4;
        ghelp = 1;
        gdata_current_map = 7;
        gdata_current_dungeon_level = 1;
        gdata_entrance_type = 4;
        gdata_version = 1220;
        gdata_weather = 3;
        gdata_hours_until_weather_changes = 6;
        for (int cnt = 0; cnt < 20; ++cnt)
        {
            gdata(120 + cnt) = 10000;
        }
        create_all_adventurers();
        mode = 2;
        evadd(2);
        evadd(24);
        sceneid = 0;
        do_play_scene();
    }
    if (mode == 2)
    {
        gdata_next_inventory_serial_id = 1000;
        gdata_next_shelter_serial_id = 100;
        initialize_recipememory();
    }
    if (mode == 3)
    {
        load_save_data();
    }
    initialize_fovmap_and_fovlist();
    initialize_map();
    return;
}



} // namespace elona
