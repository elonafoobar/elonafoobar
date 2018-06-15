#include "config.hpp"
#include <fstream>
#include <functional>
#include <string>
#include <stdexcept>
#include "elona.hpp"
#include "json.hpp"
#include "range.hpp"
#include "snail/window.hpp"
#include "variables.hpp"
#include "thirdparty/microhcl/hcl.hpp"


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



struct config_base
{
    virtual void set(const picojson::object& options) = 0;
};



// TODO: rename
template <typename T>
struct config_value : public config_base
{
    using value_type = T;


    config_value(
        const std::string& name,
        const T& default_value,
        std::function<void(const T&)> callback)
        : name(name)
        , default_value(default_value)
        , callback(callback)
    {
    }


    virtual ~config_value() = default;


    virtual void set(const picojson::object& options) override
    {
        const auto itr = options.find(name);
        if (itr == std::end(options) || !itr->second.template is<T>())
        {
            callback(default_value);
        }
        else
        {
            callback(options.at(name).template get<T>());
        }
    }


private:
    std::string name;
    T default_value;
    std::function<void(const T&)> callback;
};



using config_string = config_value<std::string>;


struct config_integer : public config_value<int64_t>
{
    config_integer(
        const std::string& name,
        const value_type& default_value,
        value_type min,
        value_type max,
        std::function<void(const value_type&)> callback)
        : config_value<value_type>(name, default_value, [=](auto& v) {
            callback(clamp(v, min, max));
        })
    {
    }
};


struct config_key : public config_base
{
    config_key(
        const std::string& name,
        const std::string& default_value,
        std::function<void(const std::string&, int)> callback)
        : name(name)
        , default_value(default_value)
        , callback(callback)
    {
    }


    virtual ~config_key() = default;


    virtual void set(const picojson::object& options) override
    {
        const auto itr = options.find(name);
        if (itr == std::end(options) || !itr->second.template is<std::string>())
        {
            callback(default_value, 0 /* TODO */);
        }
        else
        {
            callback(
                options.at(name).template get<std::string>(), 0 /* TODO */);
        }
    }


private:
    std::string name;
    std::string default_value;
    std::function<void(const std::string&, int)> callback;
};



struct config_key_sequence : public config_base
{
    config_key_sequence(
        const std::string& name,
        const std::vector<std::string>& default_value,
        std::function<void(const std::vector<std::string>&)> callback)
        : name(name)
        , default_value(default_value)
        , callback(callback)
    {
    }


    virtual ~config_key_sequence() = default;


    virtual void set(const picojson::object& options) override
    {
        const auto itr = options.find(name);
        if (itr == std::end(options)
            || !itr->second.template is<picojson::array>())
        {
            callback(default_value);
        }
        else
        {
            // FIXME: check type of each element.
            const auto keys = options.at(name).get<picojson::array>();
            std::vector<std::string> keys_;
            range::transform(
                keys,
                std::back_inserter(keys_),
                [](const picojson::value& key) {
                    return key.get<std::string>();
                });
            callback(keys_);
        }
    }


private:
    std::string name;
    std::vector<std::string> default_value;
    std::function<void(const std::vector<std::string>&)> callback;
};



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

    config::instance().language = p;
    set_config(u8"language", p);
}

#define CONFIG_OPTION(confkey, type, getter) \
    conf.bind_getter(confkey, [&]() { return (getter); } );             \
    conf.bind_setter<type>(confkey, [&](auto value) { getter = value; } )

#define CONFIG_KEY(confkey, keyname) \
    CONFIG_OPTION((confkey), std::string, config::instance().keyname)

void load_config(const fs::path& hcl_file)
{
    auto& conf = config::instance();

    // TODO do inversions
    CONFIG_OPTION("anime.alert_wait"s,                int,         config::instance().alert);
    CONFIG_OPTION("anime.anime_wait",                 int,         config::instance().animewait);
    CONFIG_OPTION("anime.attack_anime",               bool,        config::instance().attackanime);
    CONFIG_OPTION("anime.attack_wait",                int,         config::instance().attackwait);
    CONFIG_OPTION("anime.auto_turn_speed",            int,         config::instance().autoturn);
    CONFIG_OPTION("anime.general_wait",               int,         config::instance().wait1);
    CONFIG_OPTION("anime.scroll",                     bool,        config::instance().scroll);
    CONFIG_OPTION("anime.title_effect",               bool,        false); // Unsupported option
    CONFIG_OPTION("anime.weather_effect",             bool,        config::instance().env); // TODO change name
    CONFIG_OPTION("anime.window_anime",               bool,        config::instance().windowanime);
    CONFIG_OPTION("balance.restock_interval",         int,         config::instance().restock_interval);
    CONFIG_OPTION("debug.noa_debug",                  bool,        config::instance().noadeabug);
    CONFIG_OPTION("font.english",                     std::string, config::instance().font2);
    CONFIG_OPTION("font.japanese",                    std::string, config::instance().font1);
    CONFIG_OPTION("font.size_adjustment",             int,         sizefix);
    CONFIG_OPTION("font.vertical_offset",             int,         vfix);
    CONFIG_OPTION("foobar.hp_bar_position",           int,         config::instance().hp_bar);
    CONFIG_OPTION("foobar.leash_icon",                bool,        config::instance().leash_icon);
    CONFIG_OPTION("game.attack_neutral_npcs",         bool,        config::instance().ignoredislike); // TODO INVERT
    CONFIG_OPTION("game.extra_help",                  bool,        config::instance().extrahelp);
    CONFIG_OPTION("game.show_sense_quality_updates",  bool,        config::instance().hideautoidentify); // TODO INVERT
    CONFIG_OPTION("game.show_shop_updates",           bool,        config::instance().hideshopresult); // TODO INVERT
    CONFIG_OPTION("game.story",                       bool,        config::instance().story);
    CONFIG_OPTION("input.autodisable_numlock",        bool,        config::instance().autonumlock);
    CONFIG_OPTION("input.run_wait",                   int,         config::instance().runwait);
    CONFIG_OPTION("input.start_run_wait",             int,         config::instance().start_run_wait);
    CONFIG_OPTION("input.walk_wait",                  int,         config::instance().walkwait);
    CONFIG_OPTION("message.add_timestamps",           bool,        config::instance().msgaddtime);
    CONFIG_OPTION("message.transparency",             int,         config::instance().msgtrans);
    CONFIG_OPTION("net.chat",                         bool,        config::instance().netchat);
    CONFIG_OPTION("net.enabled",                      bool,        config::instance().net);
    CONFIG_OPTION("net.serverlist",                   bool,        config::instance().serverlist);
    CONFIG_OPTION("net.wish",                         bool,        config::instance().netwish);
    CONFIG_OPTION("screen.always_center",             bool,        config::instance().always_center);
    CONFIG_OPTION("screen.enable_music",              bool,        config::instance().music);
    CONFIG_OPTION("screen.enable_sound",              bool,        config::instance().sound);
    CONFIG_OPTION("screen.heartbeat",                 bool,        config::instance().heartbeat);
    CONFIG_OPTION("screen.high_quality_shadows",      bool,        config::instance().shadow); // TODO change name
    CONFIG_OPTION("screen.object_shadows",            bool,        config::instance().objectshadow);
    CONFIG_OPTION("anime.screen_refresh",             int,         config::instance().scrsync);
    CONFIG_OPTION("anime.scroll_when_run",            bool,        config::instance().runscroll);
    CONFIG_OPTION("screen.skip_random_event_popups",  bool,        config::instance().skiprandevents);
    CONFIG_OPTION("foobar.autopick",                  bool,        config::instance().use_autopick);
    CONFIG_OPTION("foobar.autosave",                  bool,        config::instance().autosave);
    CONFIG_OPTION("foobar.startup_script",            std::string, config::instance().startup_script);
    CONFIG_OPTION("foobar.damage_popup",              bool,        config::instance().damage_popup);
    CONFIG_OPTION("input.key_wait",                   int,         config::instance().keywait);

    CONFIG_KEY("key.north", key_north);
    CONFIG_KEY("key.south", key_south);
    CONFIG_KEY("key.west", key_west);
    CONFIG_KEY("key.east", key_east);
    CONFIG_KEY("key.northwest", key_northwest);
    CONFIG_KEY("key.northeast", key_northeast);
    CONFIG_KEY("key.southwest", key_southwest);
    CONFIG_KEY("key.southeast", key_southeast);
    CONFIG_KEY("key.wait", key_wait);
    CONFIG_KEY("key.cancel", key_cancel);
    CONFIG_KEY("key.esc", key_esc);
    CONFIG_KEY("key.alter", key_alter);
    CONFIG_KEY("key.pageup", key_pageup);
    CONFIG_KEY("key.pagedown", key_pagedown);
    CONFIG_KEY("key.mode", key_mode);
    CONFIG_KEY("key.mode2", key_mode2);
    CONFIG_KEY("key.quick_menu", key_quick_menu);
    CONFIG_KEY("key.zap", key_zap);
    CONFIG_KEY("key.inventory", key_inventory);
    CONFIG_KEY("key.quick_inventory", key_quick_inventory);
    CONFIG_KEY("key.get", key_get);
    CONFIG_KEY("key.get2", key_get2);
    CONFIG_KEY("key.drop", key_drop);
    CONFIG_KEY("key.chara_info", key_chara_info);
    CONFIG_KEY("key.enter", key_enter);
    CONFIG_KEY("key.eat", key_eat);
    CONFIG_KEY("key.wear", key_wear);
    CONFIG_KEY("key.cast", key_cast);
    CONFIG_KEY("key.drink", key_drink);
    CONFIG_KEY("key.read", key_read);
    CONFIG_KEY("key.fire", key_fire);
    CONFIG_KEY("key.go_down", key_go_down);
    CONFIG_KEY("key.go_up", key_go_up);
    CONFIG_KEY("key.save", key_save);
    CONFIG_KEY("key.search", key_search);
    CONFIG_KEY("key.interact", key_interact);
    CONFIG_KEY("key.identify", key_identify);
    CONFIG_KEY("key.skill", key_skill);
    CONFIG_KEY("key.close", key_close);
    CONFIG_KEY("key.rest", key_rest);
    CONFIG_KEY("key.target", key_target);
    CONFIG_KEY("key.dig", key_dig);
    CONFIG_KEY("key.use", key_use);
    CONFIG_KEY("key.bash", key_bash);
    CONFIG_KEY("key.open", key_open);
    CONFIG_KEY("key.dip", key_dip);
    CONFIG_KEY("key.pray", key_pray);
    CONFIG_KEY("key.offer", key_offer);
    CONFIG_KEY("key.journal", key_journal);
    CONFIG_KEY("key.material", key_material);
    CONFIG_KEY("key.trait", key_trait);
    CONFIG_KEY("key.look", key_look);
    CONFIG_KEY("key.give", key_give);
    CONFIG_KEY("key.throw", key_throw);
    CONFIG_KEY("key.ammo", key_ammo);
    CONFIG_KEY("key.autodig", key_autodig);
    CONFIG_KEY("key.quicksave", key_quicksave);
    CONFIG_KEY("key.quickload", key_quickload);
    CONFIG_KEY("key.help", key_help);
    CONFIG_KEY("key.message_log", key_message_log);

    conf.bind_setter<hcl::List>("key.key_set",
                    [&](auto values)
                        {
                            for_each_with_index(
                                std::begin(values),
                                std::end(values),
                                [&](auto index, hcl::Value value) {
                                    std::string s = value.as<std::string>();
                                    key_select(index) = s;
                                });
                        });

    std::ifstream ifs{filesystem::make_preferred_path_in_utf8(hcl_file.native())};
    conf.load(ifs, hcl_file.string());

    key_prev = key_northwest;
    key_next = key_northeast;

    if (config::instance().zkey == 0)
    {
        key_quick = u8"z"s;
        key_zap = u8"Z"s;
    }
    else if (config::instance().zkey == 1)
    {
        key_zap = u8"z"s;
        key_quick = u8"Z"s;
    }
    if (config::instance().xkey == 0)
    {
        key_quickinv = u8"x"s;
        key_inventory = u8"X"s;
    }
    else if (config::instance().xkey == 1)
    {
        key_inventory = u8"x"s;
        key_quickinv = u8"X"s;
    }
    if (config::instance().scrsync == 0)
    {
        config::instance().scrsync = 3;
    }
    if (config::instance().walkwait == 0)
    {
        config::instance().walkwait = 5;
    }
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
    if (config::instance().language == -1)
    {
        config_query_language();
    }
    if (config::instance().language == 0)
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
        conf.set("key.mode", key_mode);
    }
    if (key_mode2 == ""s)
    {
        key_mode2 = u8"*"s;
        conf.set("key.mode2", key_mode2);
    }
    if (key_ammo == ""s)
    {
        key_ammo = u8"A"s;
        conf.set("key.ammo", key_ammo);
    }
}



void set_config(const std::string& key, int value)
{
    picojson::value options;

    {
        std::ifstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        fileutil::skip_bom(file);
        file >> options;
    }

    options.get<picojson::object>()[key] = picojson::value{int64_t{value}};

    {
        std::ofstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void set_config(const std::string& key, const std::string& value)
{
    picojson::value options;

    {
        std::ifstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        fileutil::skip_bom(file);
        file >> options;
    }

    options.get<picojson::object>()[key] = picojson::value{value};

    {
        std::ofstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void set_config(const std::string& key, const std::string& value1, int value2)
{
    picojson::value options;

    {
        std::ifstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        fileutil::skip_bom(file);
        file >> options;
    }

    options.as<hcl::Object>()[key] = hcl::Value{value1};

    {
        std::ofstream file{(filesystem::dir::exe() / u8"config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.json")};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void load_config2(const fs::path& json_file)
{
    auto& conf = config::instance();

    conf.load_defaults();
    conf.inject_enum("core.config.language.language", {"none", "en", "jp"}, 0);
    conf.inject_enum("core.config.screen.display_mode", {""}, 0);
    conf.inject_enum("core.config.game.default_save", {""}, 0);

    CONFIG_OPTION("language.language"s,   int,         config::instance().language);
    CONFIG_OPTION("screen.fullscreen"s,   int,         config::instance().fullscreen);
    CONFIG_OPTION("screen.music"s,        int,         config::instance().music);
    CONFIG_OPTION("screen.sound"s,        bool,        config::instance().sound);
    CONFIG_OPTION("balance.extra_race"s,  bool,        config::instance().extrarace);
    CONFIG_OPTION("balance.extra_class"s, bool,        config::instance().extraclass);
    CONFIG_OPTION("input.joypad"s,        bool,        config::instance().joypad);
    CONFIG_OPTION("ui.msg_line"s,         int,         inf_msgline);
    CONFIG_OPTION("ui.tile_size"s,        int,         inf_tiles);
    CONFIG_OPTION("ui.font_size",         int,         inf_mesfont);
    CONFIG_OPTION("ui.inf_ver_type",      int,         inf_vertype);
    CONFIG_OPTION("ui.window_x",          int,         windowx);
    CONFIG_OPTION("ui.window_y",          int,         windowy);
    CONFIG_OPTION("ui.clock_x",           int,         inf_clockx);
    CONFIG_OPTION("ui.clock_w",           int,         inf_clockw);
    CONFIG_OPTION("ui.clock_h",           int,         inf_clockh);
    CONFIG_OPTION("game.default_save",         std::string, defload);    // TODO runtime enum
    CONFIG_OPTION("debug.wizard",         int,         config::instance().wizard);
    CONFIG_OPTION("screen.display_mode",  std::string, config::instance().display_mode);

    std::ifstream ifs{filesystem::make_preferred_path_in_utf8(hcl_file.native())};
    conf.load(ifs, hcl_file.string(), true);
}

#undef CONFIG_OPTION
#undef CONFIG_KEY

snail::window::fullscreen_mode_t config_get_fullscreen_mode()
{
    snail::window::fullscreen_mode_t mode;

    switch (config::instance().fullscreen)
    {
    case 0: mode = snail::window::fullscreen_mode_t::windowed; break;
    case 1: mode = snail::window::fullscreen_mode_t::fullscreen; break;
    case 2: mode = snail::window::fullscreen_mode_t::fullscreen_desktop; break;
    default: throw std::runtime_error("Invalid fullscreen mode");
    }

    return mode;
}

config& config::instance()
{
    static config the_instance;
    return the_instance;
}

void config::init(const fs::path& path)
{
    clear();
    const fs::path config_def_file =
        filesystem::dir::mods() / u8"core"s / u8"config"s / u8"config_def.hcl"s;
    def.init(config_def_file);
}

void config::load_defaults()
{
    for (auto& pair : def)
    {
        const std::string& key = pair.first;

        // Sections don't have defaults, so trying to set them would
        // cause an error.
        if (!def.is<config_def::config_section_def>(key))
        {
            set(pair.first, def.get_default(key));
        }
    }
}

void config::load(std::istream& is, const std::string& hcl_file)
{
    hcl::ParseResult parseResult = hcl::parse(is);

    if (!parseResult.valid()) {
        std::cerr << parseResult.errorReason << std::endl;
        throw config_loading_error(u8"Failed to read " + hcl_file + u8": "
                                   + parseResult.errorReason);
    }

    const hcl::Value& value = parseResult.value;

    if (!value.is<hcl::Object>() || !value.has("config"))
    {
        throw config_loading_error(hcl_file + ": \"config\" object not found at top level");
    }

    const hcl::Value conf = value["config"];

    visit_object(conf.as<hcl::Object>(), "core.config", hcl_file);
}

void config::visit_object(const hcl::Object& object,
                          const std::string& current_key,
                          const std::string& hcl_file,
                          bool preload)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file);
    }
}

void config::visit(const hcl::Value& value,
                   const std::string& current_key,
                   const std::string& hcl_file,
                   bool preload)
{
    if (value.is<hcl::Object>())
    {
        if (!def.is<config_def::config_section_def>(current_key))
        {
            throw config_loading_error(hcl_file + ": No such config section \"" + current_key + "\".");
        }
        visit_object(value.as<hcl::Object>(), current_key, hcl_file);
    }
    else
    {
        if (preload == def.is_preload(current_key))
        {
            set(current_key, value);
        }
    }
}

bool config::verify_types(const hcl::Value& value, const std::string& current_key)
{
    if (def.is<config_def::config_section_def>(current_key))
    {
        // It doesn't make sense to set a section as a value.
        return false;
    }
    if (value.is<bool>() && !def.is<config_def::config_bool_def>(current_key))
    {
        return false;
    }
    if (value.is<int>() && !def.is<config_def::config_int_def>(current_key))
    {
        return false;
    }
    if (value.is<hcl::List>() && !def.is<config_def::config_list_def>(current_key))
    {
        return false;
    }
    if (value.is<std::string>())
    {
        if (def.is<config_def::config_enum_def>(current_key))
        {
            return def.is_valid_enum_variant(current_key, value.as<int>());
        }
        else if (!def.is<config_def::config_string_def>(current_key))
        {
            return false;
        }
    }

    return true;
}

void config::write()
{
    {
        std::ifstream file{(filesystem::dir::exe() / u8"config.hcl").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                    + filesystem::make_preferred_path_in_utf8(
                        filesystem::dir::exe() / u8"config.hcl")};
        }
        fileutil::skip_bom(file);

        for (auto&& pair : storage)
        {
            // TODO write
            // file << storage;
        }
    }
}

} // namespace elona
