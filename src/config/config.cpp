#include "config.hpp"
#include <cassert>
#include <fstream>
#include <functional>
#include <stdexcept>
#include <string>
#include "../elona.hpp"
#include "../hcl.hpp"
#include "../lib/fps_counter.hpp"
#include "../range.hpp"
#include "../snail/android.hpp"
#include "../snail/application.hpp"
#include "../snail/touch_input.hpp"
#include "../snail/window.hpp"
#include "../variables.hpp"


namespace
{


struct ConfigLoadingError : public std::runtime_error
{
    ConfigLoadingError(const std::string& message)
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
static void inject_display_modes(Config& conf)
{
    const auto display_modes =
        snail::Application::instance().get_display_modes();
    std::string default_display_mode =
        snail::Application::instance().get_default_display_mode();
    std::vector<std::string> display_mode_names;
    std::string current_display_mode = Config::instance().display_mode;

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

        if (Config::instance().display_mode == spec::unknown_enum_variant)
        {
            Config::instance().set(
                u8"core.config.screen.display_mode", default_display_mode);
        }
    }
}

/***
 * Initializes the list of save files that can be chosen at startup.
 */
static void inject_save_files(Config& conf)
{
    std::vector<std::string> saves;
    saves.push_back("");

    if (fs::exists(filesystem::dir::save()))
    {
        for (const auto& entry : filesystem::dir_entries(
                 filesystem::dir::save(), filesystem::DirEntryRange::Type::dir))
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
static void inject_languages(Config& conf)
{
    std::vector<std::string> locales;
    bool has_jp = false;
    bool has_en = false;

    for (const auto& entry : filesystem::dir_entries(
             filesystem::dir::locale(), filesystem::DirEntryRange::Type::dir))
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
        throw ConfigLoadingError(
            "Locale for English or Japanese is missing in locale/ folder.");
    }

    conf.inject_enum(
        "core.config.language.language", locales, spec::unknown_enum_variant);
}

static std::map<std::string, snail::android::Orientation> orientations = {
    {"sensor_landscape", snail::android::Orientation::sensor_landscape},
    {"sensor_portait", snail::android::Orientation::sensor_portrait},
    {"sensor", snail::android::Orientation::sensor},
    {"landscape", snail::android::Orientation::landscape},
    {"portrait", snail::android::Orientation::portrait},
    {"reverse_landscape", snail::android::Orientation::reverse_landscape},
    {"reverse_portrait", snail::android::Orientation::reverse_portrait}};

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
    snail::TouchInput::instance().set_quick_action_transparency(amount);
}

static void set_touch_quick_action_size(int factor)
{
    float size = (float)factor * 0.025f;
    snail::TouchInput::instance().set_base_quick_action_size(size);
    snail::TouchInput::instance().initialize_quick_actions();
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
        if (getkey(snail::Key::down))
        {
            p = 1;
        }
        if (getkey(snail::Key::keypad_2))
        {
            p = 1;
        }
        if (getkey(snail::Key::up))
        {
            p = 0;
        }
        if (getkey(snail::Key::keypad_8))
        {
            p = 0;
        }
        if (getkey(snail::Key::enter))
        {
            break;
        }
        if (getkey(snail::Key::keypad_enter))
        {
            break;
        }
        if (getkey(snail::Key::space))
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
    Config::instance().set(u8"core.config.language.language", locale);
}

#define CONFIG_OPTION(confkey, type, getter) \
    conf.bind_getter("core.config."s + confkey, [&]() { return (getter); }); \
    conf.bind_setter<type>( \
        "core.config."s + confkey, [&](auto value) { getter = value; })

#define CONFIG_KEY(confkey, keyname) \
    CONFIG_OPTION((confkey), std::string, keyname)

void load_config(const fs::path& hcl_file)
{
    auto& conf = Config::instance();

    // TODO do inversions
    // clang-format off
    CONFIG_OPTION("anime.alert_wait"s, int, Config::instance().alert);
    CONFIG_OPTION("anime.anime_wait"s, int, Config::instance().animewait);
    CONFIG_OPTION("anime.attack_anime"s, bool, Config::instance().attackanime);
    CONFIG_OPTION("anime.auto_turn_speed"s, std::string, Config::instance().autoturn);
    CONFIG_OPTION("anime.general_wait"s, int, Config::instance().wait1);
    CONFIG_OPTION("anime.screen_refresh"s, int, Config::instance().scrsync);
    CONFIG_OPTION("anime.scroll"s, bool, Config::instance().scroll);
    CONFIG_OPTION("anime.scroll_when_run"s, bool, Config::instance().runscroll);
    CONFIG_OPTION("anime.title_effect"s, bool, Config::instance().titleanime);
    CONFIG_OPTION("anime.weather_effect"s, bool, Config::instance().env);
    CONFIG_OPTION("anime.window_anime"s, bool, Config::instance().windowanime);
    CONFIG_OPTION("balance.restock_interval"s, int, Config::instance().restock_interval);
    CONFIG_OPTION("font.file"s, std::string, Config::instance().font_filename);
    CONFIG_OPTION("font.size_adjustment"s, int, sizefix);
    CONFIG_OPTION("font.vertical_offset"s, int, vfix);
    CONFIG_OPTION("foobar.autopick"s, bool, Config::instance().use_autopick);
    CONFIG_OPTION("foobar.autosave"s, bool, Config::instance().autosave);
    CONFIG_OPTION("foobar.damage_popup"s, bool, Config::instance().damage_popup);
    CONFIG_OPTION("foobar.hp_bar_position"s, std::string, Config::instance().hp_bar);
    CONFIG_OPTION("foobar.leash_icon"s, bool, Config::instance().leash_icon);
    CONFIG_OPTION("foobar.max_damage_popup"s, int, Config::instance().max_damage_popup);
    CONFIG_OPTION("foobar.allow_enhanced_skill_tracking"s, bool, Config::instance().allow_enhanced_skill);
    CONFIG_OPTION("foobar.enhanced_skill_tracking_lowerbound"s, int, Config::instance().enhanced_skill_lowerbound);
    CONFIG_OPTION("foobar.enhanced_skill_tracking_upperbound"s, int, Config::instance().enhanced_skill_upperbound);
    CONFIG_OPTION("foobar.startup_script"s, std::string, Config::instance().startup_script);
    CONFIG_OPTION("foobar.pcc_graphic_scale"s, std::string, Config::instance().pcc_graphic_scale);
    CONFIG_OPTION("foobar.skip_confirm_at_shop"s, bool, Config::instance().skip_confirm_at_shop);
    CONFIG_OPTION("game.attack_neutral_npcs"s, bool, Config::instance().attack_neutral_npcs);
    CONFIG_OPTION("game.extra_help"s, bool, Config::instance().extrahelp);
    CONFIG_OPTION("game.hide_autoidentify"s, bool, Config::instance().hideautoidentify);
    CONFIG_OPTION("game.hide_shop_updates"s, bool, Config::instance().hideshopresult);
    CONFIG_OPTION("game.story"s, bool, Config::instance().story);
    CONFIG_OPTION("input.attack_wait"s, int, Config::instance().attackwait);
    CONFIG_OPTION("input.autodisable_numlock"s, bool, Config::instance().autonumlock);
    CONFIG_OPTION("input.key_wait"s, int, Config::instance().keywait);
    CONFIG_OPTION("input.walk_wait"s, int, Config::instance().walkwait);
    CONFIG_OPTION("input.run_wait"s, int, Config::instance().runwait);
    CONFIG_OPTION("input.start_run_wait"s, int, Config::instance().startrun);
    CONFIG_OPTION("input.select_wait"s, int, Config::instance().select_wait);
    CONFIG_OPTION("input.select_fast_start_wait"s, int, Config::instance().select_fast_start);
    CONFIG_OPTION("input.select_fast_wait"s, int, Config::instance().select_fast_wait);
    CONFIG_OPTION("message.add_timestamps"s, bool, Config::instance().message_add_timestamps);
    CONFIG_OPTION("message.transparency"s, int, Config::instance().message_transparency);
    CONFIG_OPTION("net.chat"s, bool, Config::instance().netchat);
    CONFIG_OPTION("net.enabled"s, bool, Config::instance().net);
    CONFIG_OPTION("net.server_list"s, bool, Config::instance().serverlist);
    CONFIG_OPTION("net.wish"s, bool, Config::instance().netwish);
    CONFIG_OPTION("anime.always_center"s, bool, Config::instance().alwayscenter);
    CONFIG_OPTION("screen.music"s, std::string, Config::instance().music);
    CONFIG_OPTION("screen.sound"s, bool, Config::instance().sound);
    CONFIG_OPTION("screen.heartbeat"s, bool, Config::instance().heart);
    CONFIG_OPTION("screen.high_quality_shadows"s, bool, Config::instance().shadow);
    CONFIG_OPTION("screen.object_shadows"s, bool, Config::instance().objectshadow);
    CONFIG_OPTION("screen.skip_random_event_popups"s, bool, Config::instance().skiprandevents);
    // clang-format on

    conf.bind_setter<std::string>(
        "core.config.screen.orientation",
        &convert_and_set_requested_orientation);

    conf.bind_setter<bool>("core.config.foobar.show_fps", [](bool) {
        lib::g_fps_counter.clear();
    });

    std::ifstream ifs{
        filesystem::make_preferred_path_in_utf8(hcl_file.native())};
    conf.load(ifs, hcl_file.string(), false);

    if (Config::instance().runwait < 1)
    {
        Config::instance().runwait = 1;
    }
    if (Config::instance().attackwait < 1)
    {
        Config::instance().attackwait = 1;
    }
    if (Config::instance().startrun >= 20)
    {
        Config::instance().startrun = 1000;
    }
    if (Config::instance().language == spec::unknown_enum_variant)
    {
        config_query_language();
    }
    if (Config::instance().language == "jp")
    {
        jp = 1;
        vfix = 0;
        sizefix = 0;
    }
    else
    {
        en = 1;
    }
}

void initialize_config_preload(const fs::path& hcl_file)
{
    auto& conf = Config::instance();

    inject_display_modes(conf);
    inject_languages(conf);
    inject_save_files(conf);

    // clang-format off
    CONFIG_OPTION("language.language"s, std::string, Config::instance().language);
    CONFIG_OPTION("screen.fullscreen"s, std::string, Config::instance().fullscreen);
    CONFIG_OPTION("screen.music"s, std::string, Config::instance().music);
    CONFIG_OPTION("screen.sound"s, bool, Config::instance().sound);
    CONFIG_OPTION("balance.extra_race"s, bool, Config::instance().extrarace);
    CONFIG_OPTION("balance.extra_class"s, bool, Config::instance().extraclass);
    CONFIG_OPTION("input.joypad"s, bool, Config::instance().joypad);
    CONFIG_OPTION("input.key_wait"s, int, Config::instance().keywait);
    CONFIG_OPTION("ui.msg_line"s, int, inf_msgline);
    CONFIG_OPTION("ui.tile_size"s, int, inf_tiles);
    CONFIG_OPTION("ui.font_size"s, int, inf_mesfont);
    CONFIG_OPTION("ui.inf_ver_type"s, int, inf_vertype);
    CONFIG_OPTION("ui.window_x"s, int, windowx);
    CONFIG_OPTION("ui.window_y"s, int, windowy);
    CONFIG_OPTION("ui.clock_x"s, int, inf_clockx);
    CONFIG_OPTION("ui.clock_w"s, int, inf_clockw);
    CONFIG_OPTION("ui.clock_h"s, int, inf_clockh);
    CONFIG_OPTION("game.default_save"s, std::string, defload); // TODO runtime enum
    CONFIG_OPTION("debug.wizard"s, bool, Config::instance().wizard);
    CONFIG_OPTION("screen.display_mode"s, std::string, Config::instance().display_mode);
    //clang-format on

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

snail::Window::FullscreenMode config_get_fullscreen_mode()
{
    if (Config::instance().fullscreen == "fullscreen")
    {
        return snail::Window::FullscreenMode::fullscreen;
    }
    else if (Config::instance().fullscreen == "desktop_fullscreen")
    {
        return snail::Window::FullscreenMode::fullscreen_desktop;
    }
    else
    {
        return snail::Window::FullscreenMode::windowed;
    }
}

Config& Config::instance()
{
    static Config the_instance;
    return the_instance;
}

void Config::init(const fs::path& config_def_file)
{
    clear();
    def.init(config_def_file);
}

void Config::init(const ConfigDef def_)
{
    clear();
    def = def_;
}

void Config::load_defaults(bool preload)
{
    for (auto& pair : def)
    {
        const std::string& key = pair.first;

        // Sections don't have defaults, so trying to set them would
        // cause an error.
        if (!def.is<spec::SectionDef>(key))
        {
            if (preload == def.get_metadata(key).preload)
            {
                set(key, def.get_default(key));
            }
        }
    }
}

void Config::load(std::istream& is, const std::string& hcl_file, bool preload)
{
    load_defaults(preload);

    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid())
    {
        std::cerr << parseResult.errorReason << std::endl;
        throw ConfigLoadingError(
            u8"Failed to read " + hcl_file + u8": " + parseResult.errorReason);
    }

    // TODO: This pattern seems to be shared in various places in the
    // code.
    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("config"))
    {
        throw ConfigLoadingError(
            hcl_file + ": \"config\" object not found at top level");
    }

    const hcl::Value conf = value["config"];

    // TODO mod support
    if (!conf.is<hcl::Object>() || !conf.has("core"))
    {
        throw ConfigLoadingError(
            hcl_file + ": \"core\" object not found after \"config\"");
    }

    const hcl::Value core = conf["core"];
    visit_object(core.as<hcl::Object>(), "core.config", hcl_file, preload);
}

void Config::visit_object(
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

void Config::visit(
    const hcl::Value& value,
    const std::string& current_key,
    const std::string& hcl_file,
    bool preload)
{
    if (value.is<hcl::Object>())
    {
        if (def.is<spec::SectionDef>(current_key))
        {
            visit_object(
                value.as<hcl::Object>(), current_key, hcl_file, preload);
        }
    }
    else
    {
        if (def.exists(current_key))
        {
            if (preload == def.get_metadata(current_key).preload)
            {
                set(current_key, value);
            }
        }
    }
}

bool Config::verify_types(
    const hcl::Value& value,
    const std::string& current_key)
{
    if (def.is<spec::SectionDef>(current_key))
    {
        // It doesn't make sense to set a section as a value.
        return false;
    }
    if (value.is<bool>())
    {
        return def.is<spec::BoolDef>(current_key);
    }
    if (value.is<int>())
    {
        return def.is<spec::IntDef>(current_key);
    }
    if (value.is<hcl::List>())
    {
        return def.is<spec::ListDef>(current_key);
    }
    if (value.is<std::string>())
    {
        if (def.is<spec::EnumDef>(current_key))
        {
            auto EnumDef = def.get<spec::EnumDef>(current_key);
            if (EnumDef.pending)
            {
                // The key could be anything because the values are
                // not known yet, so don't attempt to check anything.
                return true;
            }
            else
            {
                return static_cast<bool>(
                    EnumDef.get_index_of(value.as<std::string>()));
            }
        }
        else
        {
            return def.is<spec::StringDef>(current_key);
        }
    }

    return false;
}

void Config::save()
{
    std::ofstream file{(filesystem::dir::exe() / u8"config.hcl").native(),
                       std::ios::binary};
    if (!file)
    {
        throw ConfigLoadingError{
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
        if (def.is<spec::EnumDef>(key)
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

        // Skip the "config" section name in "core.<config>.some.option".
        assert(advance());
        assert(token == "config");

        // Traverse the remaining namespaces ("some.option").
        while (advance())
        {
            set(token);
        }

        // Set the value in the bottommost object ("some { option = 'value' }")
        current->set(key, value);
    }

    file << out;
}

} // namespace elona
