#include "init.hpp"
#include "ability.hpp"
#include "adventurer.hpp"
#include "audio.hpp"
#include "autopick.hpp"
#include "blending.hpp"
#include "buff.hpp"
#include "building.hpp"
#include "cat.hpp"
#include "character.hpp"
#include "character_status.hpp"
#include "class.hpp"
#include "config.hpp"
#include "crafting.hpp"
#include "ctrl_file.hpp"
#include "defines.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "event.hpp"
#include "filesystem.hpp"
#include "fish.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "item.hpp"
#include "item_db.hpp"
#include "item_material.hpp"
#include "itemgen.hpp"
#include "log.hpp"
#include "lua_env/lua_env.hpp"
#include "macro.hpp"
#include "main.hpp"
#include "main_menu.hpp"
#include "mef.hpp"
#include "network.hpp"
#include "race.hpp"
#include "random.hpp"
#include "range.hpp"
#include "snail/touch_input.hpp"
#include "trait.hpp"
#include "ui.hpp"
#include "variables.hpp"
#include "version.hpp"


using namespace elona;


namespace
{


void main_loop()
{
    lua::lua->get_event_manager()
        .run_callbacks<lua::event_kind_t::game_initialized>();

    while (true)
    {
        bool finished = turn_wrapper();
        if (finished)
        {
            break;
        }
    }
}



void load_musiclist()
{
    const auto filepath = filesystem::dir::user() / u8"music/musiclist.txt";
    if (!fs::exists(filepath))
        return;

    size_t i = 0;
    for (auto&& line : fileutil::read_by_line{filepath})
    {
        if (line.empty())
            continue;
        musicfile(i + 50) = strmid(line, 0, instr(line, 0, u8"\t"));
        ++i;
    }
}



void backup_config_files()
{
    std::pair<const char*, const char*> files[] = {
        {u8"./original/export.txt", u8"./user/export.txt"},
        {u8"./original/lastwords.txt", u8"./user/lastwords.txt"},
        {u8"./original/lastwords-e.txt", u8"./user/lastwords-e.txt"},
        {u8"./original/musiclist.txt", u8"./user/music/musiclist.txt"},
        {u8"./original/face1.bmp", u8"./user/graphic/face1.bmp"},
    };

    for (const auto& from_to : files)
    {
        const auto from_path = filesystem::path(from_to.first);
        const auto to_path = filesystem::path(from_to.second);
        if (!fs::exists(to_path))
        {
            if (!fs::exists(from_path))
            {
                throw std::runtime_error(
                    "Original config file " + from_path.string()
                    + " didn't exist.");
            }
            fs::copy_file(from_path, to_path);
        }
    }
}



void initialize_directories()
{
    const boost::filesystem::path paths[] = {filesystem::dir::save(),
                                             filesystem::dir::tmp()};

    for (const auto& path : paths)
    {
        if (!fs::exists(path))
        {
            fs::create_directory(path);
        }
    }
}



void load_character_sprite()
{
    usernpcmax = 0;
    DIM3(userdata, 70, 1);
    SDIM4(userdatan, 40, 10, 1);
    SDIM1(untaglist);
    gdata(86) = 0;
    buffer(5, 1584, (25 + (usernpcmax / 33 + 1) * 2) * 48);

    pos(0, 0);
    picload(filesystem::dir::graphic() / u8"character.bmp", 1);
    pos(640, 1120);
    picload(filesystem::dir::graphic() / u8"bufficon.png", 1);

    gmode(0);
    gsel(5);
    for (const auto& entry :
         filesystem::dir_entries{filesystem::dir::user() / u8"graphic",
                                 filesystem::dir_entries::type::file,
                                 std::regex{u8R"(chara_.*\.bmp)"}})
    {
        const auto file = filesystem::to_utf8_path(entry.path().filename());
        p = elona::stoi(strmid(file, 6, instr(file, 6, u8"."s)));
        pos(p % 33 * inf_tiles, p / 33 * inf_tiles);
        picload(entry.path(), 1);
    }
    gsel(0);
}



void start_elona()
{
    gdata_year = 517;
    gdata_month = 8;
    gdata_day = 12;
    gdata_hour = 16;
    gdata_minute = 10;
    quickpage = 1;
    if (config::instance().noadebug)
    {
        mode = 4;
        initialize_game();
        main_loop();
        return;
    }
    else if (config::instance().startup_script != ""s)
    {
        mode = 6;
        initialize_game();
        main_loop();
        return;
    }
    else if (defload != ""s)
    {
        if (!fs::exists(filesystem::dir::save(defload) / u8"header.txt"))
        {
            if (fs::exists(
                    filesystem::dir::save(u8"sav_" + defload) / u8"header.txt"))
            {
                // TODO: Delete it when v1.0.0 stable is released.
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
            initialize_game();
            main_loop();
            return;
        }
    }
    main_title_loop();
}



} // namespace


namespace elona
{

template <typename Class, typename T, T Class::*Pointer>
int cat_get_field(lua_State* L)
{
    const int argc = lua_gettop(L);

    auto self = static_cast<cat::userdata<Class>*>(lua_touserdata(L, 1))->ptr();
    if (!self)
        throw std::runtime_error(u8"Error: in cat_get_field()");

    if (argc == 1) // only "self"
    {
        // Get
        // push(self->*Pointer); TODO
        lua_pushinteger(L, self->*Pointer);
        return 1;
    }
    else
    {
        // Set
        // self->*Pointer = to_cpp_type<T>(2); TODO
        self->*Pointer = luaL_checkinteger(L, 2);
        return 0;
    }
}



// TODO DRY
template <typename Class, typename T, std::vector<T> Class::*Pointer>
int cat_get_field_with_index(lua_State* L)
{
    const int argc = lua_gettop(L);

    auto self = static_cast<cat::userdata<Class>*>(lua_touserdata(L, 1))->ptr();
    if (!self)
        throw std::runtime_error(u8"Error: in cat_get_field_with_index()");
    auto index = luaL_checkinteger(L, 2);

    if (argc == 2) // "self" and index
    {
        // Get
        // push(self->*Pointer); TODO
        lua_pushinteger(L, (self->*Pointer)[index]);
        return 1;
    }
    else
    {
        // Set
        // self->*Pointer = to_cpp_type<T>(3); TODO
        (self->*Pointer)[index] = luaL_checkinteger(L, 3);
        return 0;
    }
}



const luaL_Reg cdata_functions[] = {
    {u8"pv", &cat_get_field<character, int, &character::pv>},
    {u8"fear", &cat_get_field<character, int, &character::fear>},
    {u8"confused", &cat_get_field<character, int, &character::confused>},
    {u8"dv", &cat_get_field<character, int, &character::dv>},
    {u8"hit_bonus", &cat_get_field<character, int, &character::hit_bonus>},
    {u8"growth_buffs",
     &cat_get_field_with_index<character, int, &character::growth_buffs>},
    {nullptr, nullptr},
};


const luaL_Reg sdata_functions[] = {
    {u8"current_level", &cat_get_field<ability, int, &ability::current_level>},
    {u8"original_level",
     &cat_get_field<ability, int, &ability::original_level>},
    {u8"experience", &cat_get_field<ability, int, &ability::experience>},
    {u8"potential", &cat_get_field<ability, int, &ability::potential>},
    {nullptr, nullptr},
};



void export_to_cat_world(lua_State* L)
{
#define DEFINE(name) \
    luaL_newmetatable(L, u8"elona__" #name); \
    lua_pushvalue(L, -1); \
    lua_setfield(L, -2, u8"__index"); \
    luaL_setfuncs(L, name##_functions, 0); \
    lua_pop(L, 1);

    DEFINE(cdata);
    DEFINE(sdata);

#undef DEFINE
}


int cat_cdata(lua_State* L)
{
    int cc = luaL_checknumber(L, 1);

    cat::userdata<character>::push_new(L, &cdata(cc));
    luaL_setmetatable(L, "elona__cdata");

    return 1;
}


int cat_sdata(lua_State* L)
{
    int id = luaL_checknumber(L, 1);
    int cc = luaL_checknumber(L, 2);

    cat::userdata<ability>::push_new(L, &sdata.get(id, cc));
    luaL_setmetatable(L, "elona__sdata");

    return 1;
}


int cat_cbitmod(lua_State* L)
{
    int id = luaL_checknumber(L, 1);
    int cc = luaL_checknumber(L, 2);
    int flag = luaL_checknumber(L, 3);

    cdata[cc]._flags[id] = flag;

    return 0;
}

void initialize_cat_db()
{
    cat::global.initialize();

    export_to_cat_world(cat::global.ptr());
    cat::global.register_function(u8"cdata", cat_cdata);
    cat::global.register_function(u8"sdata", cat_sdata);
    cat::global.register_function(u8"cbitmod", cat_cbitmod);

    the_ability_db.initialize();
    the_buff_db.initialize();
    the_class_db.initialize();
    the_fish_db.initialize();
    the_item_db.initialize();
    the_item_material_db.initialize();
    the_race_db.initialize();
    the_trait_db.initialize();
}

sol::table initialize_single_lion_db(
    const std::string& type,
    const fs::path& data_file)
{
    lua::lua->get_registry_manager().register_datatype("core", type);
    // lua::lua->get_registry_manager().register_data("core", type, data_file);
    auto table = lua::lua->get_registry_manager().get_table("core", type);
    if (!table)
    {
        throw std::runtime_error(
            "Could not load data for type " + type + " at"
            + data_file.string());
    }
    return *table;
}

static std::vector<lua::registry_manager::location>
collect_mod_datafile_locations()
{
    std::vector<lua::registry_manager::location> locations;

    for (const auto& pair : lua::lua->get_mod_manager())
    {
        const auto& mod = pair.second;
        if (mod->path)
        {
            locations.emplace_back(*mod->path / "data.hcl", mod->name);
        }
    }

    return locations
}

void initialize_lion_db()
{
    // Register base game data types. Without these, it wouldn't be
    // possible to run the game, so they're baked in.
    lua::lua->get_registry_manager().register_core_datatype(
        "chara", [](auto table) { the_character_db.initialize(table); });
    lua::lua->get_registry_manager().register_core_datatype(
        "sound", [](auto table) { the_sound_db.initialize(table); });
    lua::lua->get_registry_manager().register_core_datatype(
        "music", [](auto table) { the_music_db.initialize(table); });

    auto locations = collect_mod_datafile_locations();
    lua::lua->get_registry_manager().load_mod_data(locations);
}

void initialize_config(const fs::path& config_file)
{
    windoww = snail::application::instance().width();
    windowh = snail::application::instance().height();

    if (defines::is_android)
    {
        snail::touch_input::instance().initialize(filesystem::dir::graphic());
    }

    time_warn = timeGetTime() / 1000;
    time_begin = timeGetTime() / 1000;

    mesbox(keylog);

    backup_config_files();

    initialize_directories();

    // The config setup routine needs these variables allocated to
    // handle the language selection menu.
    SDIM3(s, 160, 40);
    DIM2(p, 100);
    DIM2(rtval, 10);
    SDIM3(rtvaln, 50, 10);
    SDIM3(key_select, 2, 20);
    SDIM2(buff, 10000);
    initialize_jkey();

    load_config(config_file);
}

void initialize_i18n()
{
    const std::string language = jp ? "jp" : "en";
    i18n::load(language);

    // Load built-in translations in data/locale/(jp|en).
    std::vector<i18n::store::location> locations{
        {filesystem::dir::locale() / language, "core"}};

    // Load translations for each mod.
    for (const auto& pair : lua::lua->get_mod_manager())
    {
        const auto& mod = pair.second;
        if (mod->path)
        {
            locations.emplace_back(*mod->path / "locale" / language, mod->name);
        }
    }
    i18n::s.init(locations);
}

void initialize_elona()
{
    initialize_i18n();
    initialize_ui_constants();
    gsel(0);
    boxf();
    redraw();
    buffer(3, 1440, 800);
    picload(filesystem::dir::graphic() / u8"interface.bmp", 1);

    pos(0, 656);
    picload(filesystem::dir::graphic() / u8"interface_ex1.png", 1);
    pos(144, 656);
    picload(filesystem::dir::graphic() / u8"interface_ex2.png", 1);
    pos(144, 752);
    picload(filesystem::dir::graphic() / u8"interface_ex3.png", 1);

    buffer(4, windoww, windowh);
    buffer(8, windoww, windowh);
    gsel(0);
    buffer(1, 1584, 1200);
    picload(filesystem::dir::graphic() / u8"item.bmp", 1);
    if (inf_tiles != 48)
    {
        pos(0, 0);
        gcopy(1, 0, 0, 1584, 1200, 33 * inf_tiles, 25 * inf_tiles);
    }
    buffer(2, 33 * inf_tiles, 25 * inf_tiles);
    buffer(6, 33 * inf_tiles, 25 * inf_tiles);
    buffer(7, 24, 24);
    buffer(9, 24, 24);

    DIM3(cmapdata, 5, 400);
    DIM2(fixeditemenc, 20);
    DIM2(dir, 5);
    DIM3(dblist, 2, 800);
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
    SDIM1(msgtempprev);
    DIM3(mef, 9, MEF_MAX);
    DIM3(adata, 40, 500);
    DIM3(qdata, 20, 500);
    SDIM3(qname, 40, 500);
    DIM2(gdata, 1000);
    DIM2(genetemp, 1000);
    SDIM3(gdatan, 40, 50);
    DIM2(mdatatmp, 100);
    DIM2(mdata, 100);
    SDIM3(mdatan, 20, 2);
    SDIM4(cdatan, 40, 10, ELONA_MAX_CHARACTERS);
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
    c_col(0, 1) = 0;
    c_col(1, 1) = 0;
    c_col(2, 1) = 0;
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
    SDIM3(musicfile, 30, 97);
    DIM3(slight, inf_screenw + 4, inf_screenh + 4);

    gsel(3);
    gmode(0);
    font(15 - en * 2);
    for (int i = 0; i < 18; ++i)
    {
        draw("select_key", i * 24 + 72, 30);
        bmes(key_select(i), i * 24 + 77, 31, {250, 240, 230}, {50, 60, 80});
    }
    gsel(0);
    gmode(2);
    text_set();
    ctrl_file(file_operation_t::_10);
    tc = 0;
    tcol_at_txtfunc(0) = 255;
    tcol_at_txtfunc(1) = 255;
    tcol_at_txtfunc(2) = 255;
    invctrl(0) = 0;
    invctrl(1) = 0;
    pos(-40, -40);
    SDIM1(buffboard);
    notesel(buffboard);
    {
        buffboard(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"board.txt").native(),
                         std::ios::binary};
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
    DIM2(trate, 8);
    SDIM1(filtern);
    SDIM1(filter_creature);
    initialize_character_filters();
    initialize_all_chips();
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
    initialize_ego_data();
    initialize_enchantment_data();
    initialize_set_of_random_generation();
    initialize_picfood();
    initialize_recipe();
    initialize_nefia_names();
    initialize_home_adata();
    initialize_damage_popups();
    load_character_sprite();
    if (config::instance().music == "direct_music" && DMINIT() == 0)
    {
        config::instance().music = "mci";
    }
    DSINIT();
    if (config::instance().joypad == 1)
    {
        DIINIT();
        if (DIGETJOYNUM() == 0)
        {
            config::instance().joypad = 0;
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

    if (config::instance().autonumlock)
    {
        snail::input::instance().disable_numlock();
    }
}

static void initialize_screen()
{
    std::string display_mode = config::instance().display_mode;

    if (defines::is_android)
    {
        display_mode = config::instance().get<std::string>(
            "core.config.screen.window_mode");
    }

    title(
        u8"Elona foobar version "s + latest_version.short_string(),
        display_mode,
        config_get_fullscreen_mode());
}

static void initialize_lua()
{
    lua::lua->get_mod_manager().load_mods(filesystem::dir::mods());
    lua::lua->get_api_manager().lock();
}

int run()
{
    const fs::path config_file = filesystem::dir::exe() / u8"config.hcl";
    const fs::path config_def_file =
        filesystem::dir::mods() / u8"core"s / u8"config"s / u8"config_def.hcl"s;

    lua::lua = std::make_unique<lua::lua_env>();
    initialize_cat_db();

    config::instance().init(config_def_file);
    initialize_config_preload(config_file);
    initialize_screen();

    filesystem::dir::set_base_save_directory(filesystem::path("save"));

    initialize_config(config_file);
    init_assets();

    initialize_lua();
    initialize_lion_db();

    initialize_elona();

    config::instance().write();

    start_elona();

    return 0;
}



void initialize_debug_globals()
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
    gdata_pc_x_in_world_map = 22;
    gdata_pc_y_in_world_map = 21;
    gdata_previous_map = -1;
    gdata_random_seed = rnd(800) + 2;
    gdata(9) = rnd(200) + 2;
    gdata_current_map = mdata_t::map_id_t::north_tyris;
    gdata_current_dungeon_level = 0;
    gdata_entrance_type = 7;
    mapstartx = 22;
    mapstarty = 21;
    gdata_current_map = mdata_t::map_id_t::vernis;
    gdata_current_dungeon_level = 1;
    gdata_entrance_type = 7;
    mapstartx = 10;
    mapstarty = 23;
    initlv = 50;
    rc = 0;
    flt(100);
    chara_create(0, 84, -3, 0);
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
    earn_gold(cdata[0], 1000000);
    cdata[0].platinum_coin = 30;
    cdata[0].fame = 65000;
    gdata_main_quest_flag = 100;
    chara_refresh(0);

    cdata[0].can_cast_rapid_magic() = true;
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
}

void initialize_noa_items()
{
    flt();
    itemcreate(0, 284, -1, -1, 0);
    inv[ci].set_number(20);
    inv[ci].curse_state = curse_state_t::blessed;
    flt();
    itemcreate(0, 127, -1, -1, 0);
    inv[ci].set_number(20);
    inv[ci].curse_state = curse_state_t::blessed;
    flt();
    itemcreate(0, 617, -1, -1, 0);
    inv[ci].set_number(20);
    flt();
    itemcreate(0, 671, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 749, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 748, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 601, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 342, -1, -1, 0);
    inv[ci].set_number(12);
    flt();
    itemcreate(0, 343, -1, -1, 0);
    inv[ci].set_number(50);
    flt();
    itemcreate(0, 519, -1, -1, 0);
    inv[ci].set_number(50);
    inv[ci].color = 4;
    flt();
    itemcreate(0, 622, -1, -1, 0);
    inv[ci].set_number(50000);
    flt();
    itemcreate(0, 603, -1, -1, 0);
    inv[ci].set_number(5);
    flt();
    itemcreate(0, 620, -1, -1, 0);
    inv[ci].set_number(5);
    flt();
    itemcreate(0, 736, -1, -1, 0);
    inv[ci].set_number(5);
    flt();
    itemcreate(0, 566, -1, -1, 0);
    inv[ci].set_number(5);
    flt();
    itemcreate(0, 516, -1, -1, 0);
    inv[ci].set_number(5);
    inv[ci].curse_state = curse_state_t::blessed;
    flt();
    itemcreate(0, 262, -1, -1, 0);
    inv[ci].set_number(5);
    flt();
    itemcreate(0, 632, -1, -1, 0);
    inv[ci].set_number(10);
    inv[ci].curse_state = curse_state_t::cursed;
    flt();
    itemcreate(0, 632, -1, -1, 0);
    inv[ci].set_number(10);
    inv[ci].curse_state = curse_state_t::none;
    flt();
    itemcreate(0, 204, -1, -1, 0);
    inv[ci].subname = 330;
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 636, -1, -1, 0);
    inv[ci].set_number(3);
    inv[ci].curse_state = curse_state_t::none;
    flt();
    itemcreate(0, 342, -1, -1, 0);
    inv[ci].count = 100;
    flt();
    itemcreate(0, 350, -1, -1, 0);
    inv[ci].set_number(20);
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
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 786, -1, -1, 0);
    inv[ci].set_number(10);
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
    inv[ci].set_number(100);
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
    inv[ci].set_number(10);
    inv[ci].curse_state = curse_state_t::blessed;
    flt();
    itemcreate(0, 566, -1, -1, 0);
    inv[ci].set_number(10);
    inv[ci].curse_state = curse_state_t::cursed;
    flt();
    itemcreate(0, 566, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 55, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 385, -1, -1, 0);
    inv[ci].set_number(10);
    flt();
    itemcreate(0, 672, -1, -1, 0);
    inv[ci].set_number(10);
    inv[ci].param1 = 169;
    flt();
    itemcreate(0, 672, -1, -1, 0);
    inv[ci].set_number(10);
    inv[ci].param1 = 162;
    flt();
    itemcreate(0, 771, -1, -1, 0);
    inv[ci].set_number(100);
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
            inv[ci].set_number(50);
        }
    }
    flt();
    {
        int stat = itemcreate(0, 755, -1, -1, 0);
        if (stat != 0)
        {
            inv[ci].param3 = 240;
            inv[ci].set_number(50);
        }
    }
    flt();
    {
        int stat = itemcreate(0, 756, -1, -1, 0);
        if (stat != 0)
        {
            inv[ci].param3 = 240;
            inv[ci].set_number(50);
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
}


void initialize_world()
{
    gdata_year = 517;
    gdata_month = 8;
    gdata_day = 12;
    gdata_hour = 1;
    gdata_minute = 10;
    gdata_pc_x_in_world_map = 22;
    gdata_pc_y_in_world_map = 21;
    gdata_previous_map = -1;
    gdata(850) = 4;
    ghelp = 1;
    gdata_current_map = mdata_t::map_id_t::your_home;
    gdata_current_dungeon_level = 1;
    gdata_entrance_type = 4;
    gdata_version = 1220;
    gdata_home_scale = 0;
    initialize_adata();
    gdata_weather = 3;
    gdata_hours_until_weather_changes = 6;
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        gdata(120 + cnt) = 10000;
    }
}

void initialize_testbed()
{
    gdata_current_map = 9999;
    gdata_current_dungeon_level = 2;
}

void initialize_game()
{
    bool script_loaded = false;
    autopick::instance().load(playerid);

    mtilefilecur = -1;
    firstturn = 1;
    msgtemp = u8"  Lafrontier presents Elona ver 1.22. Welcome traveler! "s;
    if (config::instance().net)
    {
        initialize_server_info();
    }
    if (mode == 4)
    {
        playerid = u8"sav_noa"s;
        initialize_debug_globals();
        initialize_noa_items();
        mode = 2;
    }
    if (mode == 5)
    {
        initialize_world();
        create_all_adventurers();
        mode = 2;
        event_add(2);
        event_add(24);
        sceneid = 0;
        do_play_scene();
    }
    if (mode == 6)
    {
        playerid = u8"sav_testbed"s;
        initialize_debug_globals();
        initialize_testbed();
        if (config::instance().startup_script != ""s)
        {
            lua::lua->get_mod_manager().run_startup_script(
                config::instance().startup_script);
            script_loaded = true;
        }
        mode = 2;
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
    init_fovlist();
    initialize_map();

    if (script_loaded)
    {
        lua::lua->get_event_manager()
            .run_callbacks<lua::event_kind_t::script_loaded>();
    }
}

void main_title_loop()
{
    main_menu_result_t result = main_menu_wrapper();
    bool finished = false;
    while (!finished)
    {
        switch (result)
        {
        case main_menu_result_t::main_title_menu:
            result = main_menu_wrapper();
            break;
        case main_menu_result_t::initialize_game:
            initialize_game();
            finished = true;
            break;
        case main_menu_result_t::finish_elona:
            finish_elona();
            finished = true;
            break;
        default: assert(0); break;
        }
    }

    if (result == main_menu_result_t::initialize_game)
    {
        main_loop();
    }
}



} // namespace elona
