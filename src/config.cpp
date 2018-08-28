#include "config.hpp"
#include <cassert>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include "elona.hpp"
#include "hcl.hpp"
#include "range.hpp"
#include "snail/android.hpp"
#include "snail/application.hpp"
#include "snail/touch_input.hpp"
#include "snail/window.hpp"
#include "variables.hpp"


namespace
{


struct config_loading_error : public std::runtime_error
{
    config_loading_error(const std::string& message)
        : std::runtime_error(message)
    {
    }
};



template <typename Iterator, typename Function>
void for_each_with_index(Iterator first, Iterator last, Function f)
{
    for (size_t index = 0; first != last; ++first, ++index)
    {
        (void)f(index, *first);
    }
}


static void write_default_config(const fs::path& location)
{
    std::ofstream out{location.native(), std::ios::binary};
    hcl::Object object;
    object["config"] = hcl::Object();
    object["config"]["core"] = hcl::Object();
    out << object << std::endl;
}


/***
 * Initializes the list of available display modes. To be called after
 * the application has been initialized by calling title().
 */
static void inject_display_modes(config& conf)
{
    const auto display_modes =
        snail::application::instance().get_display_modes();
    std::string default_display_mode =
        snail::application::instance().get_default_display_mode();
    std::vector<std::string> display_mode_names;
    std::string current_display_mode = config::instance().display_mode;

    bool config_display_mode_found = false;
    int index = 0;

    for (const auto pair : display_modes)
    {
        // First pair member contains identifier string, second is SDL
        // display mode struct.
        display_mode_names.emplace_back(pair.first);

        // If this is the display mode currently selected in the
        // config, mark that it's been found.
        if (pair.first == current_display_mode)
        {
            config_display_mode_found = true;
        }
        index++;
    }

    // If the display mode in the config was not found, reconfigure it to
    // the application's default.
    if (!config_display_mode_found || current_display_mode == "")
    {
        current_display_mode = default_display_mode;
    }

    // If the display_mode is still unknown, we're probably in
    // headless mode, so don't try to set any config options (or
    // "invalid enum variant" will be generated).
    if (current_display_mode != "")
    {
        conf.inject_enum(
            "core.config.screen.display_mode",
            display_mode_names,
            default_display_mode);

        if (config::instance().display_mode == spec::unknown_enum_variant)
        {
            config::instance().set(
                u8"core.config.screen.display_mode", default_display_mode);
        }
    }
}

/***
 * Initializes the list of save files that can be chosen at startup.
 */
static void inject_save_files(config& conf)
{
    std::vector<std::string> saves;
    saves.push_back("");

    if (fs::exists(filesystem::dir::save()))
    {
        for (const auto& entry : filesystem::dir_entries{
                 filesystem::dir::save(), filesystem::dir_entries::type::dir})
        {
            std::string folder =
                filesystem::to_utf8_path(entry.path().filename());
            saves.push_back(folder);
        }
    }

    conf.inject_enum("core.config.game.default_save", saves, "");
}

/***
 * Initializes the list of languages by adding the names of folders in
 * the locale/ directory.
 *
 * TODO: Support mods which add their own languages.
 */
static void inject_languages(config& conf)
{
    std::vector<std::string> locales;
    bool has_jp = false;
    bool has_en = false;

    for (const auto& entry : filesystem::dir_entries{
             filesystem::dir::locale(), filesystem::dir_entries::type::dir})
    {
        std::string identifier =
            filesystem::to_utf8_path(entry.path().filename());
        locales.push_back(identifier);

        if (identifier == "en")
        {
            has_en = true;
        }
        if (identifier == "jp")
        {
            has_jp = true;
        }
    }

    // Not having English or Japanese loaded will cause weird things
    // to happen, since many parts of the code depend on one or the
    // other being loaded. This can be removed after those parts of
    // the code are refactored.
    if (!has_en || !has_jp)
    {
        throw config_loading_error(
            "Locale for English or Japanese is missing in locale/ folder.");
    }

    conf.inject_enum(
        "core.config.language.language", locales, spec::unknown_enum_variant);
}

static std::map<std::string, snail::android::orientation> orientations = {
    {"sensor_landscape", snail::android::orientation::sensor_landscape},
    {"sensor_portait", snail::android::orientation::sensor_portrait},
    {"sensor", snail::android::orientation::sensor},
    {"landscape", snail::android::orientation::landscape},
    {"portrait", snail::android::orientation::portrait},
    {"reverse_landscape", snail::android::orientation::reverse_landscape},
    {"reverse_portrait", snail::android::orientation::reverse_portrait}};

static void convert_and_set_requested_orientation(std::string variant)
{
    auto it = orientations.find(variant);
    if (it == orientations.end())
        return;

    snail::android::set_requested_orientation(it->second);
}

static void set_touch_quick_action_transparency(int factor)
{
    float amount = (float)factor * 0.05f;
    snail::touch_input::instance().set_quick_action_transparency(amount);
}

static void set_touch_quick_action_size(int factor)
{
    float size = (float)factor * 0.025f;
    snail::touch_input::instance().set_base_quick_action_size(size);
    snail::touch_input::instance().initialize_quick_actions();
}


} // namespace



namespace elona
{


void config_query_language()
{
    buffer(4);
    picload(filesystem::dir::graphic() / u8"lang.bmp");
    gsel(0);
    gmode(0);
    p = 0;

    while (1)
    {
        boxf();
        pos(160, 170);
        gcopy(4, 0, 0, 340, 100);
        pos(180, 220 + p * 20);
        gcopy(4, 360, 6, 20, 18);
        redraw();
        await(30);
        if (getkey(snail::key::down))
        {
            p = 1;
        }
        if (getkey(snail::key::keypad_2))
        {
            p = 1;
        }
        if (getkey(snail::key::up))
        {
            p = 0;
        }
        if (getkey(snail::key::keypad_8))
        {
            p = 0;
        }
        if (getkey(snail::key::enter))
        {
            break;
        }
        if (getkey(snail::key::keypad_enter))
        {
            break;
        }
        if (getkey(snail::key::space))
        {
            break;
        }
    }

    std::string locale = spec::unknown_enum_variant;
    if (p == 0)
    {
        locale = "jp";
    }
    else
    {
        locale = "en";
    }
    config::instance().set(u8"core.config.language.language", locale);
}

#define CONFIG_OPTION(confkey, type, getter) \
    conf.bind_getter("core.config."s + confkey, [&]() { return (getter); }); \
    conf.bind_setter<type>( \
        "core.config."s + confkey, [&](auto value) { getter = value; })

#define CONFIG_KEY(confkey, keyname) \
    CONFIG_OPTION((confkey), std::string, keyname)

void load_config(const fs::path& hcl_file)
{
    auto& conf = config::instance();

    // TODO do inversions
    CONFIG_OPTION("anime.alert_wait"s, int, config::instance().alert);
    CONFIG_OPTION("anime.anime_wait"s, int, config::instance().animewait);
    CONFIG_OPTION("anime.attack_anime"s, bool, config::instance().attackanime);
    CONFIG_OPTION(
        "anime.auto_turn_speed"s, std::string, config::instance().autoturn);
    CONFIG_OPTION("anime.general_wait"s, int, config::instance().wait1);
    CONFIG_OPTION("anime.screen_refresh"s, int, config::instance().scrsync);
    CONFIG_OPTION("anime.scroll"s, bool, config::instance().scroll);
    CONFIG_OPTION("anime.scroll_when_run"s, bool, config::instance().runscroll);
    CONFIG_OPTION("anime.title_effect"s, bool, config::instance().titleanime);
    CONFIG_OPTION("anime.weather_effect"s, bool, config::instance().env);
    CONFIG_OPTION("anime.window_anime"s, bool, config::instance().windowanime);
    CONFIG_OPTION(
        "balance.restock_interval"s, int, config::instance().restock_interval);
    CONFIG_OPTION("debug.noa_debug"s, bool, config::instance().noadebug);
    CONFIG_OPTION("font.file"s, std::string, config::instance().font_filename);
    CONFIG_OPTION("font.size_adjustment"s, int, sizefix);
    CONFIG_OPTION("font.vertical_offset"s, int, vfix);
    CONFIG_OPTION("foobar.autopick"s, bool, config::instance().use_autopick);
    CONFIG_OPTION("foobar.autosave"s, bool, config::instance().autosave);
    CONFIG_OPTION(
        "foobar.damage_popup"s, bool, config::instance().damage_popup);
    CONFIG_OPTION(
        "foobar.hp_bar_position"s, std::string, config::instance().hp_bar);
    CONFIG_OPTION("foobar.leash_icon"s, bool, config::instance().leash_icon);
    CONFIG_OPTION(
        "foobar.max_damage_popup"s, int, config::instance().max_damage_popup);
    CONFIG_OPTION(
        "foobar.allow_enhanced_skill_tracking"s,
        bool,
        config::instance().allow_enhanced_skill);
    CONFIG_OPTION(
        "foobar.enhanced_skill_tracking_lowerbound"s,
        int,
        config::instance().enhanced_skill_lowerbound);
    CONFIG_OPTION(
        "foobar.enhanced_skill_tracking_upperbound"s,
        int,
        config::instance().enhanced_skill_upperbound);
    CONFIG_OPTION(
        "foobar.startup_script"s,
        std::string,
        config::instance().startup_script);
    CONFIG_OPTION(
        "foobar.pcc_graphic_scale"s,
        std::string,
        config::instance().pcc_graphic_scale);
    CONFIG_OPTION(
        "game.attack_neutral_npcs"s,
        bool,
        config::instance().attack_neutral_npcs);
    CONFIG_OPTION("game.extra_help"s, bool, config::instance().extrahelp);
    CONFIG_OPTION(
        "game.hide_autoidentify"s, bool, config::instance().hideautoidentify);
    CONFIG_OPTION(
        "game.hide_shop_updates"s, bool, config::instance().hideshopresult);
    CONFIG_OPTION("game.story"s, bool, config::instance().story);
    CONFIG_OPTION("input.attack_wait"s, int, config::instance().attackwait);
    CONFIG_OPTION(
        "input.autodisable_numlock"s, bool, config::instance().autonumlock);
    CONFIG_OPTION("input.key_wait"s, int, config::instance().keywait);
    CONFIG_OPTION("input.walk_wait"s, int, config::instance().walkwait);
    CONFIG_OPTION("input.run_wait"s, int, config::instance().runwait);
    CONFIG_OPTION("input.start_run_wait"s, int, config::instance().startrun);
    CONFIG_OPTION("input.select_wait"s, int, config::instance().select_wait);
    CONFIG_OPTION(
        "input.select_fast_start_wait"s,
        int,
        config::instance().select_fast_start);
    CONFIG_OPTION(
        "input.select_fast_wait"s, int, config::instance().select_fast_wait);
    CONFIG_OPTION(
        "message.add_timestamps"s, bool, config::instance().msgaddtime);
    CONFIG_OPTION("message.transparency"s, int, config::instance().msgtrans);
    CONFIG_OPTION("net.chat"s, bool, config::instance().netchat);
    CONFIG_OPTION("net.enabled"s, bool, config::instance().net);
    CONFIG_OPTION("net.server_list"s, bool, config::instance().serverlist);
    CONFIG_OPTION("net.wish"s, bool, config::instance().netwish);
    CONFIG_OPTION(
        "anime.always_center"s, bool, config::instance().alwayscenter);
    CONFIG_OPTION("screen.music"s, std::string, config::instance().music);
    CONFIG_OPTION("screen.sound"s, bool, config::instance().sound);
    CONFIG_OPTION("screen.heartbeat"s, bool, config::instance().heart);
    CONFIG_OPTION(
        "screen.high_quality_shadows"s, bool, config::instance().shadow);
    CONFIG_OPTION(
        "screen.object_shadows"s, bool, config::instance().objectshadow);
    CONFIG_OPTION(
        "screen.skip_random_event_popups"s,
        bool,
        config::instance().skiprandevents);

    CONFIG_KEY("key.north"s, key_north);
    CONFIG_KEY("key.south"s, key_south);
    CONFIG_KEY("key.west"s, key_west);
    CONFIG_KEY("key.east"s, key_east);
    CONFIG_KEY("key.northwest"s, key_northwest);
    CONFIG_KEY("key.northeast"s, key_northeast);
    CONFIG_KEY("key.southwest"s, key_southwest);
    CONFIG_KEY("key.southeast"s, key_southeast);
    CONFIG_KEY("key.wait"s, key_wait);
    CONFIG_KEY("key.cancel"s, key_cancel);
    CONFIG_KEY("key.esc"s, key_esc);
    CONFIG_KEY("key.alter"s, key_alter);
    CONFIG_KEY("key.pageup"s, key_pageup);
    CONFIG_KEY("key.pagedown"s, key_pagedown);
    CONFIG_KEY("key.mode"s, key_mode);
    CONFIG_KEY("key.mode2"s, key_mode2);
    CONFIG_KEY("key.quick_menu"s, key_quick);
    CONFIG_KEY("key.zap"s, key_zap);
    CONFIG_KEY("key.inventory"s, key_inventory);
    CONFIG_KEY("key.quick_inventory"s, key_quickinv);
    CONFIG_KEY("key.get"s, key_get);
    CONFIG_KEY("key.get2"s, key_get2);
    CONFIG_KEY("key.drop"s, key_drop);
    CONFIG_KEY("key.chara_info"s, key_charainfo);
    CONFIG_KEY("key.enter"s, key_enter);
    CONFIG_KEY("key.eat"s, key_eat);
    CONFIG_KEY("key.wear"s, key_wear);
    CONFIG_KEY("key.cast"s, key_cast);
    CONFIG_KEY("key.drink"s, key_drink);
    CONFIG_KEY("key.read"s, key_read);
    CONFIG_KEY("key.fire"s, key_fire);
    CONFIG_KEY("key.go_down"s, key_godown);
    CONFIG_KEY("key.go_up"s, key_goup);
    CONFIG_KEY("key.save"s, key_save);
    CONFIG_KEY("key.search"s, key_search);
    CONFIG_KEY("key.interact"s, key_interact);
    CONFIG_KEY("key.identify"s, key_identify);
    CONFIG_KEY("key.skill"s, key_skill);
    CONFIG_KEY("key.close"s, key_close);
    CONFIG_KEY("key.rest"s, key_rest);
    CONFIG_KEY("key.target"s, key_target);
    CONFIG_KEY("key.dig"s, key_dig);
    CONFIG_KEY("key.use"s, key_use);
    CONFIG_KEY("key.bash"s, key_bash);
    CONFIG_KEY("key.open"s, key_open);
    CONFIG_KEY("key.dip"s, key_dip);
    CONFIG_KEY("key.pray"s, key_pray);
    CONFIG_KEY("key.offer"s, key_offer);
    CONFIG_KEY("key.journal"s, key_journal);
    CONFIG_KEY("key.material"s, key_material);
    CONFIG_KEY("key.trait"s, key_trait);
    CONFIG_KEY("key.look"s, key_look);
    CONFIG_KEY("key.give"s, key_give);
    CONFIG_KEY("key.throw"s, key_throw);
    CONFIG_KEY("key.ammo"s, key_ammo);
    CONFIG_KEY("key.autodig"s, key_autodig);
    CONFIG_KEY("key.quicksave"s, key_quicksave);
    CONFIG_KEY("key.quickload"s, key_quickload);
    CONFIG_KEY("key.help"s, key_help);
    CONFIG_KEY("key.message_log"s, key_msglog);

    conf.bind_setter<hcl::List>("core.config.key.key_set", [&](auto values) {
        for_each_with_index(
            std::begin(values),
            std::end(values),
            [&](auto index, hcl::Value value) {
                std::string s = value.as<std::string>();
                key_select(index) = s;
            });
    });

    conf.bind_setter<std::string>(
        "core.config.input.assign_z_key", [&](auto value) {
            if (value == "quick_menu")
            {
                key_quick = u8"z"s;
                key_zap = u8"Z"s;
            }
            else if (value == "zap")
            {
                key_zap = u8"z"s;
                key_quick = u8"Z"s;
            }
        });

    conf.bind_setter<std::string>(
        "core.config.input.assign_x_key", [&](auto value) {
            if (value == "quick_inv")
            {
                key_quickinv = u8"x"s;
                key_inventory = u8"X"s;
            }
            else if (value == "identify")
            {
                key_inventory = u8"x"s;
                key_quickinv = u8"X"s;
            }
        });

    conf.bind_setter<std::string>(
        "core.config.screen.orientation",
        &convert_and_set_requested_orientation);

    conf.bind_setter<int>(
        "core.config.android.quick_action_repeat_start_wait", [](auto value) {
            snail::input::instance().set_quick_action_repeat_start_wait(value);
        });

    conf.bind_setter<int>(
        "core.config.android.quick_action_repeat_wait", [](auto value) {
            snail::input::instance().set_quick_action_repeat_wait(value);
        });

    std::ifstream ifs{
        filesystem::make_preferred_path_in_utf8(hcl_file.native())};
    conf.load(ifs, hcl_file.string(), false);

    key_prev = key_northwest;
    key_next = key_northeast;

    // Keys set in assign_<...>_key may have been overwritten by other
    // config values in the "key" section. To account for this, run
    // the setters for assign_<...>_key again. This will do nothing if
    // either option is "none", so the keys can stil be set to
    // something else.
    conf.run_setter("core.config.input.assign_x_key");
    conf.run_setter("core.config.input.assign_z_key");

    if (config::instance().runwait < 1)
    {
        config::instance().runwait = 1;
    }
    if (config::instance().attackwait < 1)
    {
        config::instance().attackwait = 1;
    }
    if (config::instance().startrun >= 20)
    {
        config::instance().startrun = 1000;
    }
    if (config::instance().language == spec::unknown_enum_variant)
    {
        config_query_language();
    }
    if (config::instance().language == "jp")
    {
        jp = 1;
        vfix = 0;
        sizefix = 0;
    }
    else
    {
        en = 1;
    }
    if (key_mode == ""s)
    {
        key_mode = u8"z"s;
        conf.set("core.config.key.mode", key_mode);
    }
    if (key_mode2 == ""s)
    {
        key_mode2 = u8"*"s;
        conf.set("core.config.key.mode2", key_mode2);
    }
    if (key_ammo == ""s)
    {
        key_ammo = u8"A"s;
        conf.set("core.config.key.ammo", key_ammo);
    }
}

void initialize_config_preload(const fs::path& hcl_file)
{
    auto& conf = config::instance();

    inject_display_modes(conf);
    inject_languages(conf);
    inject_save_files(conf);

    CONFIG_OPTION(
        "language.language"s, std::string, config::instance().language);
    CONFIG_OPTION(
        "screen.fullscreen"s, std::string, config::instance().fullscreen);
    CONFIG_OPTION("screen.music"s, std::string, config::instance().music);
    CONFIG_OPTION("screen.sound"s, bool, config::instance().sound);
    CONFIG_OPTION("balance.extra_race"s, bool, config::instance().extrarace);
    CONFIG_OPTION("balance.extra_class"s, bool, config::instance().extraclass);
    CONFIG_OPTION("input.joypad"s, bool, config::instance().joypad);
    CONFIG_OPTION("input.key_wait"s, int, config::instance().keywait);
    CONFIG_OPTION("ui.msg_line"s, int, inf_msgline);
    CONFIG_OPTION("ui.tile_size"s, int, inf_tiles);
    CONFIG_OPTION("ui.font_size"s, int, inf_mesfont);
    CONFIG_OPTION("ui.inf_ver_type"s, int, inf_vertype);
    CONFIG_OPTION("ui.window_x"s, int, windowx);
    CONFIG_OPTION("ui.window_y"s, int, windowy);
    CONFIG_OPTION("ui.clock_x"s, int, inf_clockx);
    CONFIG_OPTION("ui.clock_w"s, int, inf_clockw);
    CONFIG_OPTION("ui.clock_h"s, int, inf_clockh);
    CONFIG_OPTION(
        "game.default_save"s, std::string, defload); // TODO runtime enum
    CONFIG_OPTION("debug.wizard"s, bool, config::instance().wizard);
    CONFIG_OPTION(
        "screen.display_mode"s, std::string, config::instance().display_mode);

    conf.bind_setter<int>(
        "core.config.android.quick_action_size", &set_touch_quick_action_size);

    conf.bind_setter<int>(
        "core.config.android.quick_action_transparency",
        &set_touch_quick_action_transparency);

    if (!fs::exists(hcl_file))
    {
        write_default_config(hcl_file);
    }

    std::ifstream ifs{
        filesystem::make_preferred_path_in_utf8(hcl_file.native())};
    conf.load(ifs, hcl_file.string(), true);

    snail::android::set_navigation_bar_visibility(
        !conf.get<bool>("core.config.android.hide_navigation"));
}

#undef CONFIG_OPTION
#undef CONFIG_KEY

snail::window::fullscreen_mode_t config_get_fullscreen_mode()
{
    if (config::instance().fullscreen == "fullscreen")
    {
        return snail::window::fullscreen_mode_t::fullscreen;
    }
    else if (config::instance().fullscreen == "desktop_fullscreen")
    {
        return snail::window::fullscreen_mode_t::fullscreen_desktop;
    }
    else
    {
        return snail::window::fullscreen_mode_t::windowed;
    }
}

config& config::instance()
{
    static config the_instance;
    return the_instance;
}

void config::init(const fs::path& config_def_file)
{
    clear();
    def.init(config_def_file);
}

void config::init(const config_def def_)
{
    clear();
    def = def_;
}

void config::load_defaults(bool preload)
{
    for (auto& pair : def)
    {
        const std::string& key = pair.first;

        // Sections don't have defaults, so trying to set them would
        // cause an error.
        if (!def.is<spec::section_def>(key))
        {
            if (preload == def.get_metadata(key).preload)
            {
                set(key, def.get_default(key));
            }
        }
    }
}

void config::load(std::istream& is, const std::string& hcl_file, bool preload)
{
    load_defaults(preload);

    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid())
    {
        std::cerr << parseResult.errorReason << std::endl;
        throw config_loading_error(
            u8"Failed to read " + hcl_file + u8": " + parseResult.errorReason);
    }

    // TODO: This pattern seems to be shared in various places in the
    // code.
    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("config"))
    {
        throw config_loading_error(
            hcl_file + ": \"config\" object not found at top level");
    }

    const hcl::Value conf = value["config"];

    // TODO mod support
    if (!conf.is<hcl::Object>() || !conf.has("core"))
    {
        throw config_loading_error(
            hcl_file + ": \"core\" object not found after \"config\"");
    }

    const hcl::Value core = conf["core"];
    visit_object(core.as<hcl::Object>(), "core.config", hcl_file, preload);
}

void config::visit_object(
    const hcl::Object& object,
    const std::string& current_key,
    const std::string& hcl_file,
    bool preload)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file, preload);
    }
}

void config::visit(
    const hcl::Value& value,
    const std::string& current_key,
    const std::string& hcl_file,
    bool preload)
{
    if (value.is<hcl::Object>())
    {
        if (!def.is<spec::section_def>(current_key))
        {
            throw config_loading_error(
                hcl_file + ": No such config section \"" + current_key + "\".");
        }
        visit_object(value.as<hcl::Object>(), current_key, hcl_file, preload);
    }
    else
    {
        if (!def.exists(current_key))
        {
            throw config_loading_error(
                hcl_file + ": No such config value \"" + current_key + "\".");
        }
        if (preload == def.get_metadata(current_key).preload)
        {
            set(current_key, value);
        }
    }
}

bool config::verify_types(
    const hcl::Value& value,
    const std::string& current_key)
{
    if (def.is<spec::section_def>(current_key))
    {
        // It doesn't make sense to set a section as a value.
        return false;
    }
    if (value.is<bool>())
    {
        return def.is<spec::bool_def>(current_key);
    }
    if (value.is<int>())
    {
        return def.is<spec::int_def>(current_key);
    }
    if (value.is<hcl::List>())
    {
        return def.is<spec::list_def>(current_key);
    }
    if (value.is<std::string>())
    {
        if (def.is<spec::enum_def>(current_key))
        {
            auto enum_def = def.get<spec::enum_def>(current_key);
            if (enum_def.pending)
            {
                // The key could be anything because the values are
                // not known yet, so don't attempt to check anything.
                return true;
            }
            else
            {
                return static_cast<bool>(
                    enum_def.get_index_of(value.as<std::string>()));
            }
        }
        else
        {
            return def.is<spec::string_def>(current_key);
        }
    }

    return false;
}

void config::write()
{
    std::ofstream file{(filesystem::dir::exe() / u8"config.hcl").native(),
                       std::ios::binary};
    if (!file)
    {
        throw config_loading_error{
            u8"Failed to open: "s
            + filesystem::make_preferred_path_in_utf8(
                  filesystem::dir::exe() / u8"config.hcl")};
    }

    // Create a top level "config" section.
    hcl::Value out = hcl::Value(hcl::Object());
    out.set("config", hcl::Object());
    hcl::Value* parent = out.find("config");
    assert(parent);

    // Create sections under the top-level "config" section for each
    // mod that has config options (for now, only "core"), then write
    // their individual config sections.
    for (auto&& pair : storage)
    {
        std::string key = pair.first;
        hcl::Value value = pair.second;

        // Don't save hidden options if their value is the same as the default.
        if (!def.get_metadata(key).is_visible()
            && value == def.get_default(key))
        {
            continue;
        }

        // Don't save injected enum values that are still unknown
        // (though this should never happen)
        if (def.is<spec::enum_def>(key)
            && value.as<std::string>() == spec::unknown_enum_variant)
        {
            continue;
        }

        size_t pos = 0;
        std::string token;
        hcl::Value* current = parent;

        // Function to split the flat key ("core.config.some.option")
        // on the next period and set the token to the split section
        // name ("some" or "option").
        auto advance = [&pos, &key, &token]() {
            pos = key.find(".");
            if (pos == std::string::npos)
            {
                return false;
            }
            token = key.substr(0, pos);
            key.erase(0, pos + 1);
            return true;
        };

        // Function that either creates a new object for holding the
        // nested config value or finds an existing one.
        auto set = [&current](std::string key) {
            hcl::Value* existing = current->find(key);
            if (existing)
            {
                current = existing;
            }
            else
            {
                current->set(key, hcl::Object());
                current = current->find(key);
                assert(current);
            }
        };

        // Get the mod-level scope ("core").
        assert(advance());
        std::string scope = token;
        set(token);

        // Skip the "config" section name.
        assert(advance());
        assert(token == "config");

        while (advance())
        {
            set(token);
        }

        current->set(key, value);
    }

    file << out;
}

} // namespace elona
