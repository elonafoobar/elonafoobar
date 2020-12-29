#include "config.hpp"

#include <cassert>

#include <fstream>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../snail/application.hpp"
#include "../thirdparty/json5/json5.hpp"
#include "../util/fps_counter.hpp"
#include "../util/range.hpp"
#include "draw.hpp"
#include "elona.hpp"
#include "filesystem.hpp"
#include "log.hpp"
#include "lua_env/config_manager.hpp"
#include "lua_env/mod_manager.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

struct ConfigLoadingError : public std::runtime_error
{
    ConfigLoadingError(const std::string& message)
        : std::runtime_error(message)
    {
    }
};



constexpr const char* unknown_language = "__unknown__";



snail::Window::FullscreenMode convert_to_fullscreen(const std::string& str)
{
    using namespace snail;
    if (str == "fullscreen")
    {
        return Window::FullscreenMode::fullscreen;
    }
    else if (str == "desktop_fullscreen")
    {
        return Window::FullscreenMode::fullscreen_desktop;
    }
    else
    {
        return Window::FullscreenMode::windowed;
    }
}



// Option setters
namespace setters
{

void font_quality(const std::string& variant)
{
    if (variant == "low")
    {
        snail::Application::instance()
            .get_renderer()
            .disable_blended_text_rendering();
    }
    else
    {
        if (variant != "high")
        {
            // Unknown font quality; fallback to the default value, "high".
            ELONA_WARN("Config: unsupported font quality '" + variant + "'");
        }
        snail::Application::instance()
            .get_renderer()
            .enable_blended_text_rendering();
    }
}



void font_size_adjustment(const int& value)
{
    elona::sizefix = value;
}



void font_vertical_offset(const int& value)
{
    elona::vfix = value;
}



void foobar_show_fps(const bool&)
{
    lib::g_fps_counter.clear();
}



void screen_fullscreen(const std::string& value)
{
    g_config.set_fullscreen(convert_to_fullscreen(value));
}

} // namespace setters



std::string read_whole_file(std::istream& in)
{
    assert(in);
    using stream_itr = std::istreambuf_iterator<char>;
    return std::string{stream_itr{in}, stream_itr{}};
}



json5::value::object_type parse_json5_file(
    std::istream& in,
    const std::string& filepath)
{
    if (!in)
        return {};

    const auto file_content = read_whole_file(in);
    try
    {
        return json5::parse(file_content).get_object();
    }
    catch (json5::syntax_error& err)
    {
        ELONA_WARN(
            "Config: JSON5 syntax error in '" + filepath + "': " + err.what());
        return {};
    }
    catch (json5::invalid_type_error& err)
    {
        ELONA_WARN(
            "Config: JSON5 type error in '" + filepath + "': " + err.what());
        return {};
    }
}



template <typename T>
T get_value_by_nesting_key(
    const json5::value::object_type& obj,
    const std::vector<std::string>& keys,
    const T& default_value)
{
    assert(!keys.empty());

    const json5::value::object_type* cur = &obj;
    for (size_t i = 0; i < keys.size() - 1; ++i)
    {
        const auto& key = keys[i];
        const auto itr = cur->find(key);
        if (itr == std::end(*cur))
            return default_value;

        if (!itr->second.is_object())
            return default_value;

        cur = &itr->second.get_object();
    }

    const auto itr = cur->find(keys.back());
    if (itr != std::end(*cur) && itr->second.is<T>())
    {
        return itr->second.get<T>();
    }
    else
    {
        return default_value;
    }
}



/**
 * Initializes the list of available display modes.
 */
void inject_display_modes()
{
    const auto display_modes =
        snail::Application::instance().get_display_modes();
    const auto default_display_mode =
        snail::Application::instance().get_default_display_mode();

    // If there is no available display mode, we're probably in headless mode,
    // so don't try to set any config options (or "invalid enum variant" will
    // be generated).
    if (!display_modes.empty())
    {
        std::vector<std::string> display_mode_names;
        display_mode_names.reserve(display_modes.size());
        for (const auto& pair : display_modes)
        {
            display_mode_names.push_back(pair.first);
        }
        lua::lua->get_config_manager().inject_enum(
            "core.screen.display_mode",
            display_mode_names,
            default_display_mode);
    }
}



/**
 * Initializes the list of save files that can be chosen at startup.
 */
void inject_save_files()
{
    std::vector<std::string> saves;
    saves.push_back("");

    if (fs::exists(filesystem::dirs::save()))
    {
        for (const auto& entry :
             filesystem::glob_dirs(filesystem::dirs::save()))
        {
            saves.push_back(entry.path().filename().to_u8string());
        }
    }

    lua::lua->get_config_manager().inject_enum(
        "core.game.default_save", saves, "");
}



/**
 * Initializes the list of languages by adding the names of folders in
 * the locale/ directory.
 *
 * TODO: Support mods which add their own languages.
 */
void inject_languages()
{
    auto& conf = lua::lua->get_config_manager();

    std::vector<std::string> locales;
    bool has_ja = false;
    bool has_en = false;

    // TODO
    locales.push_back("en");
    locales.push_back("ja");
    has_en = true;
    has_ja = true;

    // Not having English or Japanese loaded will cause weird things
    // to happen, since many parts of the code depend on one or the
    // other being loaded. This can be removed after those parts of
    // the code are refactored.
    if (!has_en || !has_ja)
    {
        throw ConfigLoadingError(
            "Locale for English or Japanese is missing in locale/ folder.");
    }

    conf.inject_enum("core.language.language", locales, unknown_language);
}



/**
 * Validate the display mode setting. If the display mode is unavailable, set
 * the default value.
 */
std::string validate_display_mode(const std::string& current_value)
{
    auto& app = snail::Application::instance();
    const auto display_modes = app.get_display_modes();
    const auto default_display_mode = app.get_default_display_mode();

    const auto found = range::any_of(
        display_modes, [&](const auto& d) { return d.first == current_value; });

    return found ? current_value : default_display_mode;
}



void bind_setters()
{
    auto& conf = lua::lua->get_config_manager();

#define CONFIG_OPTION(key, type, name) \
    conf.bind_setter( \
        "core."s + key, \
        +[](const type& value) { g_config.set_##name(value); })

    // clang-format off
    CONFIG_OPTION("anime.alert_wait", int, alert_wait);
    CONFIG_OPTION("anime.always_center", bool, always_center);
    CONFIG_OPTION("anime.anime_wait", int, animation_wait);
    CONFIG_OPTION("anime.attack_anime", bool, attack_animation);
    CONFIG_OPTION("anime.auto_turn_speed", std::string, auto_turn_speed);
    CONFIG_OPTION("anime.general_wait", int, general_wait);
    CONFIG_OPTION("anime.screen_refresh", int, screen_refresh_wait);
    CONFIG_OPTION("anime.scroll", bool, scroll);
    CONFIG_OPTION("anime.scroll_when_run", bool, scroll_when_run);
    CONFIG_OPTION("anime.title_effect", bool, title_effect);
    CONFIG_OPTION("anime.weather_effect", bool, weather_effect);
    CONFIG_OPTION("anime.window_anime", bool, window_animation);
    CONFIG_OPTION("balance.extra_class", bool, extra_class);
    CONFIG_OPTION("balance.extra_race", bool, extra_race);
    CONFIG_OPTION("balance.restock_interval", int, restock_interval);
    CONFIG_OPTION("font.file", std::string, font_filename);
    CONFIG_OPTION("foobar.allow_enhanced_skill_tracking", bool, allow_enhanced_skill);
    CONFIG_OPTION("foobar.autopick", bool, autopick);
    CONFIG_OPTION("foobar.autosave", bool, autosave);
    CONFIG_OPTION("foobar.auto_target", bool, auto_target);
    CONFIG_OPTION("foobar.damage_popup", bool, damage_popup);
    CONFIG_OPTION("foobar.digital_clock", bool, digital_clock);
    CONFIG_OPTION("foobar.enhanced_skill_tracking_lowerbound", int, enhanced_skill_lowerbound);
    CONFIG_OPTION("foobar.enhanced_skill_tracking_upperbound", int, enhanced_skill_upperbound);
    CONFIG_OPTION("foobar.hp_bar_position", std::string, hp_bar_position);
    CONFIG_OPTION("foobar.leash_icon", bool, leash_icon);
    CONFIG_OPTION("foobar.max_damage_popup", int, max_damage_popup);
    CONFIG_OPTION("foobar.pcc_graphic_scale", std::string, pcc_graphic_scale);
    CONFIG_OPTION("foobar.skip_confirm_at_shop", bool, skip_confirm_at_shop);
    CONFIG_OPTION("foobar.skip_overcasting_warning", bool, skip_overcasting_warning);
    CONFIG_OPTION("foobar.startup_script", std::string, startup_script);
    CONFIG_OPTION("game.attack_neutral_npcs", bool, attack_neutral_npcs);
    CONFIG_OPTION("game.extra_help", bool, extra_help);
    CONFIG_OPTION("game.hide_autoidentify", bool, hide_autoidentify);
    CONFIG_OPTION("game.hide_shop_updates", bool, hide_shop_updates);
    CONFIG_OPTION("game.story", bool, story);
    CONFIG_OPTION("input.attack_wait", int, attack_wait);
    CONFIG_OPTION("input.autodisable_numlock", bool, autodisable_numlock);
    CONFIG_OPTION("input.initial_key_repeat_wait", int, initial_key_repeat_wait);
    CONFIG_OPTION("input.joypad", bool, joypad);
    CONFIG_OPTION("input.key_repeat_wait", int, key_repeat_wait);
    CONFIG_OPTION("input.key_wait", int, key_wait);
    CONFIG_OPTION("input.run_wait", int, run_wait);
    CONFIG_OPTION("input.select_fast_start_wait", int, select_fast_start_wait);
    CONFIG_OPTION("input.select_fast_wait", int, select_fast_wait);
    CONFIG_OPTION("input.select_wait", int, select_wait);
    CONFIG_OPTION("input.start_run_wait", int, start_run_wait);
    CONFIG_OPTION("input.walk_wait", int, walk_wait);
    CONFIG_OPTION("language.language", std::string, language);
    CONFIG_OPTION("message.add_timestamps", bool, message_add_timestamps);
    CONFIG_OPTION("message.transparency", int, message_transparency);
    CONFIG_OPTION("net.is_enabled", bool, net);
    CONFIG_OPTION("screen.display_mode", std::string, display_mode);
    CONFIG_OPTION("screen.heartbeat", bool, heartbeat);
    CONFIG_OPTION("screen.high_quality_shadows", bool, high_quality_shadow);
    CONFIG_OPTION("screen.music", bool, music);
    CONFIG_OPTION("screen.music_volume", int, music_volume);
    CONFIG_OPTION("screen.object_shadows", bool, object_shadow);
    CONFIG_OPTION("screen.skip_random_event_popups", bool, skip_random_event_popups);
    CONFIG_OPTION("screen.sound", bool, sound);
    CONFIG_OPTION("screen.sound_volume", int, sound_volume);
    // clang-format on

    conf.bind_setter("core.font.quality", &setters::font_quality);
    conf.bind_setter(
        "core.font.size_adjustment", &setters::font_size_adjustment);
    conf.bind_setter(
        "core.font.vertical_offset", &setters::font_vertical_offset);
    conf.bind_setter("core.foobar.show_fps", &setters::foobar_show_fps);
    conf.bind_setter("core.screen.fullscreen", &setters::screen_fullscreen);

#undef CONFIG_OPTION
} // namespace



void query_language()
{
    constexpr snail::Color bg_color{160, 145, 128};
    constexpr snail::Color fg_color{71, 64, 55};

    gsel(0);
    gmode(0);
    int cursor = 0;

    const auto prev_font = g_config.font_filename();
    // Because this Japanese font has more glyph than English one does, it can
    // display language names more correctly.
    g_config.set_font_filename(
        "GenShinGothic/GenShinGothic-Monospace-Regular.ttf");
    font(16);

    while (true)
    {
        boxf(0, 0, windoww, windowh, bg_color);
        mes(40, 40, "Choose your language and press Enter key.", fg_color);
        mes(40, 60, "言語を選びENTERキーを押してください。", fg_color);
        mes(50, 90, "Japanese (日本語)", fg_color);
        mes(50, 110, "English", fg_color);
        mes(35, cursor == 0 ? 90 : 110, ">", fg_color);
        redraw();
        await(30);
        if (getkey(snail::Key::down))
        {
            cursor = 1;
        }
        if (getkey(snail::Key::keypad_2))
        {
            cursor = 1;
        }
        if (getkey(snail::Key::up))
        {
            cursor = 0;
        }
        if (getkey(snail::Key::keypad_8))
        {
            cursor = 0;
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

    std::string locale;
    if (cursor == 0)
    {
        locale = "ja";
    }
    else
    {
        locale = "en";
    }
    lua::lua->get_config_manager().set("core.language.language", locale);

    g_config.set_font_filename(prev_font);
}



void load_options_internal(std::istream& in, const std::string& filepath)
{
    windoww = snail::Application::instance().width();
    windowh = snail::Application::instance().height();

    time_warn = timeGetTime() / 1000;
    time_begin = timeGetTime() / 1000;

    g_config.set_key_wait(30);
    mesbox(keylog);

    // The config setup routine needs these variables allocated to
    // handle the language selection menu.
    SDIM3(s, 160, 40);
    DIM2(p, 100);
    DIM2(rtval, 10);
    SDIM3(key_select, 2, 20);
    SDIM2(buff, 10000);

    bind_setters();

    inject_display_modes();
    inject_languages();
    inject_save_files();

    lua::lua->get_config_manager().load_options(in, filepath);

    if (g_config.language() == unknown_language)
    {
        query_language();
    }
    if (g_config.language() == "ja")
    {
        jp = 1;
    }
    else
    {
        en = 1;
    }
}

} // namespace



Config g_config;



PreinitConfigOptions PreinitConfigOptions::from_file(const fs::path& path)
{
    std::ifstream in{path.native()};
    return from_stream(in, path.to_u8string());
}



PreinitConfigOptions PreinitConfigOptions::from_string(const std::string& str)
{
    std::istringstream in{str};
    return from_stream(in, "[string]");
}



PreinitConfigOptions PreinitConfigOptions::from_stream(
    std::istream& in,
    const std::string& filepath)
{
    const auto obj = parse_json5_file(in, filepath);

    // screen.fullscreen (default: "windowed")
    auto fullscreen = convert_to_fullscreen(get_value_by_nesting_key(
        obj, {"core", "screen", "fullscreen"}, json5::string_type{"windowed"}));

    // screen.display_mode (default: "")
    auto display_mode = get_value_by_nesting_key(
        obj, {"core", "screen", "display_mode"}, json5::string_type{""});

    display_mode = validate_display_mode(display_mode);


    // TODO: move it somewhere else or make it constant. "inf_tiles" is too
    // frequently used to find out where it should be initialized. Thus, it is
    // initialized as close to the previous position as possilbe.
    inf_tiles = 48;


    return PreinitConfigOptions{fullscreen, display_mode};
}



void config_load_all_schema()
{
    for (const auto& pair : lua::lua->get_mod_manager().mods())
    {
        const auto& mod_manifest = pair.second.manifest;
        if (mod_manifest.path)
        {
            const auto schema_path = *mod_manifest.path / "config-schema.lua";
            if (fs::exists(schema_path))
            {
                std::ifstream in{schema_path.native()};
                lua::lua->get_config_manager().load_schema(
                    in, schema_path.to_u8string(), mod_manifest.id);
            }
        }
    }
}



void config_load_schema(
    const std::string& config_schema,
    const std::string& mod_id)
{
    std::istringstream in{config_schema};
    lua::lua->get_config_manager().load_schema(in, "[string stream]", mod_id);
}



void config_load_options()
{
    const auto path = filesystem::files::profile_local_config();
    std::ifstream in{path.native()};
    load_options_internal(in, path.to_u8string());
}



void config_load_options(const std::string& config)
{
    std::istringstream in{config};
    load_options_internal(in, "[string stream]");
}



void config_save()
{
    lua::lua->get_config_manager().save(
        filesystem::files::profile_local_config());
}



void config_clear()
{
    g_config = Config{};
    lua::lua->get_config_manager().clear();
}



template <typename T>
T config_get(const std::string& key)
{
    return lua::lua->get_config_manager().get<T>(key);
}

// explicit template instantiation
template bool config_get<bool>(const std::string&);
template int config_get<int>(const std::string&);
template std::string config_get<std::string>(const std::string&);



template <typename T>
void config_set(const std::string& key, const T& value)
{
    lua::lua->get_config_manager().set(key, value);
}

// explicit template instantiation
template void config_set<bool>(const std::string&, const bool&);
template void config_set<int>(const std::string&, const int&);
template void config_set<std::string>(const std::string&, const std::string&);

} // namespace elona
