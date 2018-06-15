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
    config::instance().set(u8"language", p(0));
}

#define CONFIG_OPTION(confkey, type, getter) \
    conf.bind_getter("core.config."s + confkey, [&]() { return (getter); } );             \
    conf.bind_setter<type>("core.config."s + confkey, [&](auto value) { getter = value; } )

#define CONFIG_KEY(confkey, keyname) \
    CONFIG_OPTION((confkey), std::string, keyname)

void load_config(const fs::path& hcl_file)
{
    auto& conf = config::instance();

    // TODO do inversions
    CONFIG_OPTION("anime.alert_wait"s,                int,         config::instance().alert);
    CONFIG_OPTION("anime.anime_wait"s,                int,         config::instance().animewait);
    CONFIG_OPTION("anime.attack_anime"s,              bool,        config::instance().attackanime);
    CONFIG_OPTION("anime.auto_turn_speed"s,           int,         config::instance().autoturn);
    CONFIG_OPTION("anime.general_wait"s,              int,         config::instance().wait1);
    CONFIG_OPTION("anime.screen_refresh"s,            int,         config::instance().scrsync);
    CONFIG_OPTION("anime.scroll"s,                    bool,        config::instance().scroll);
    CONFIG_OPTION("anime.scroll_when_run"s,           bool,        config::instance().runscroll);
    CONFIG_OPTION("anime.title_effect"s,              bool,        config::instance().titleanime);
    CONFIG_OPTION("anime.weather_effect"s,            bool,        config::instance().env);
    CONFIG_OPTION("anime.window_anime"s,              bool,        config::instance().windowanime);
    CONFIG_OPTION("balance.restock_interval"s,        int,         config::instance().restock_interval);
    CONFIG_OPTION("debug.noa_debug"s,                 bool,        config::instance().noadebug);
    CONFIG_OPTION("font.english"s,                    std::string, config::instance().font2);
    CONFIG_OPTION("font.japanese"s,                   std::string, config::instance().font1);
    CONFIG_OPTION("font.size_adjustment"s,            int,         sizefix);
    CONFIG_OPTION("font.vertical_offset"s,            int,         vfix);
    CONFIG_OPTION("foobar.autopick"s,                 bool,        config::instance().use_autopick);
    CONFIG_OPTION("foobar.autosave"s,                 bool,        config::instance().autosave);
    CONFIG_OPTION("foobar.damage_popup"s,             bool,        config::instance().damage_popup);
    CONFIG_OPTION("foobar.hp_bar_position"s,          int,         config::instance().hp_bar);
    CONFIG_OPTION("foobar.leash_icon"s,               bool,        config::instance().leash_icon);
    CONFIG_OPTION("foobar.startup_script"s,           std::string, config::instance().startup_script);
    CONFIG_OPTION("game.attack_neutral_npcs"s,        bool,        config::instance().attack_neutral_npcs);
    CONFIG_OPTION("game.extra_help"s,                 bool,        config::instance().extrahelp);
    CONFIG_OPTION("game.hide_autoidentify"s,          bool,        config::instance().hideautoidentify);
    CONFIG_OPTION("game.hide_shop_updates"s,          bool,        config::instance().hideshopresult);
    CONFIG_OPTION("game.story"s,                      bool,        config::instance().story);
    CONFIG_OPTION("input.attack_wait"s,               int,         config::instance().attackwait);
    CONFIG_OPTION("input.autodisable_numlock"s,       bool,        config::instance().autonumlock);
    CONFIG_OPTION("input.key_wait"s,                  int,         config::instance().keywait);
    CONFIG_OPTION("input.run_wait"s,                  int,         config::instance().runwait);
    CONFIG_OPTION("input.start_run_wait"s,            int,         config::instance().startrun);
    CONFIG_OPTION("input.select_wait"s,               int,         config::instance().select_wait);
    CONFIG_OPTION("input.select_fast_start_wait"s,    int,         config::instance().select_fast_start);
    CONFIG_OPTION("input.select_fast_wait"s,          int,         config::instance().select_fast_wait);
    CONFIG_OPTION("message.add_timestamps"s,          bool,        config::instance().msgaddtime);
    CONFIG_OPTION("message.transparency"s,            int,         config::instance().msgtrans);
    CONFIG_OPTION("net.chat"s,                        bool,        config::instance().netchat);
    CONFIG_OPTION("net.enabled"s,                     bool,        config::instance().net);
    CONFIG_OPTION("net.server_list"s,                 bool,        config::instance().serverlist);
    CONFIG_OPTION("net.wish"s,                        bool,        config::instance().netwish);
    CONFIG_OPTION("anime.always_center"s,             bool,        config::instance().alwayscenter);
    CONFIG_OPTION("screen.music"s,                    int,         config::instance().music);
    CONFIG_OPTION("screen.sound"s,                    bool,        config::instance().sound);
    CONFIG_OPTION("screen.heartbeat"s,                bool,        config::instance().heart);
    CONFIG_OPTION("screen.high_quality_shadows"s,     bool,        config::instance().shadow);
    CONFIG_OPTION("screen.object_shadows"s,           bool,        config::instance().objectshadow);
    CONFIG_OPTION("screen.skip_random_event_popups"s, bool,        config::instance().skiprandevents);

    CONFIG_KEY("key.north"s,            key_north);
    CONFIG_KEY("key.south"s,            key_south);
    CONFIG_KEY("key.west"s,             key_west);
    CONFIG_KEY("key.east"s,             key_east);
    CONFIG_KEY("key.northwest"s,        key_northwest);
    CONFIG_KEY("key.northeast"s,        key_northeast);
    CONFIG_KEY("key.southwest"s,        key_southwest);
    CONFIG_KEY("key.southeast"s,        key_southeast);
    CONFIG_KEY("key.wait"s,             key_wait);
    CONFIG_KEY("key.cancel"s,           key_cancel);
    CONFIG_KEY("key.esc"s,              key_esc);
    CONFIG_KEY("key.alter"s,            key_alter);
    CONFIG_KEY("key.pageup"s,           key_pageup);
    CONFIG_KEY("key.pagedown"s,         key_pagedown);
    CONFIG_KEY("key.mode"s,             key_mode);
    CONFIG_KEY("key.mode2"s,            key_mode2);
    CONFIG_KEY("key.quick_menu"s,       key_quick);
    CONFIG_KEY("key.zap"s,              key_zap);
    CONFIG_KEY("key.inventory"s,        key_inventory);
    CONFIG_KEY("key.quick_inventory"s,  key_quickinv);
    CONFIG_KEY("key.get"s,              key_get);
    CONFIG_KEY("key.get2"s,             key_get2);
    CONFIG_KEY("key.drop"s,             key_drop);
    CONFIG_KEY("key.chara_info"s,       key_charainfo);
    CONFIG_KEY("key.enter"s,            key_enter);
    CONFIG_KEY("key.eat"s,              key_eat);
    CONFIG_KEY("key.wear"s,             key_wear);
    CONFIG_KEY("key.cast"s,             key_cast);
    CONFIG_KEY("key.drink"s,            key_drink);
    CONFIG_KEY("key.read"s,             key_read);
    CONFIG_KEY("key.fire"s,             key_fire);
    CONFIG_KEY("key.go_down"s,          key_godown);
    CONFIG_KEY("key.go_up"s,            key_goup);
    CONFIG_KEY("key.save"s,             key_save);
    CONFIG_KEY("key.search"s,           key_search);
    CONFIG_KEY("key.interact"s,         key_interact);
    CONFIG_KEY("key.identify"s,         key_identify);
    CONFIG_KEY("key.skill"s,            key_skill);
    CONFIG_KEY("key.close"s,            key_close);
    CONFIG_KEY("key.rest"s,             key_rest);
    CONFIG_KEY("key.target"s,           key_target);
    CONFIG_KEY("key.dig"s,              key_dig);
    CONFIG_KEY("key.use"s,              key_use);
    CONFIG_KEY("key.bash"s,             key_bash);
    CONFIG_KEY("key.open"s,             key_open);
    CONFIG_KEY("key.dip"s,              key_dip);
    CONFIG_KEY("key.pray"s,             key_pray);
    CONFIG_KEY("key.offer"s,            key_offer);
    CONFIG_KEY("key.journal"s,          key_journal);
    CONFIG_KEY("key.material"s,         key_material);
    CONFIG_KEY("key.trait"s,            key_trait);
    CONFIG_KEY("key.look"s,             key_look);
    CONFIG_KEY("key.give"s,             key_give);
    CONFIG_KEY("key.throw"s,            key_throw);
    CONFIG_KEY("key.ammo"s,             key_ammo);
    CONFIG_KEY("key.autodig"s,          key_autodig);
    CONFIG_KEY("key.quicksave"s,        key_quicksave);
    CONFIG_KEY("key.quickload"s,        key_quickload);
    CONFIG_KEY("key.help"s,             key_help);
    CONFIG_KEY("key.message_log"s,      key_msglog);

    conf.bind_setter<hcl::List>("core.config.key.key_set",
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
    conf.load(ifs, hcl_file.string(), false);

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



void load_config2(const fs::path& hcl_file)
{
    auto& conf = config::instance();

    conf.inject_enum("core.config.language.language", {"jp", "en"}, 1);
    //conf.inject_enum("core.config.screen.display_mode", {""}, 0);
    // conf.inject_enum("core.config.game.default_save", {""}, 0);

    CONFIG_OPTION("language.language"s,   int,         config::instance().language);
    CONFIG_OPTION("screen.fullscreen"s,   int,         config::instance().fullscreen);
    CONFIG_OPTION("screen.music"s,        int,         config::instance().music);
    CONFIG_OPTION("screen.sound"s,        bool,        config::instance().sound);
    CONFIG_OPTION("balance.extra_race"s,  bool,        config::instance().extrarace);
    CONFIG_OPTION("balance.extra_class"s, bool,        config::instance().extraclass);
    CONFIG_OPTION("input.joypad"s,        bool,        config::instance().joypad);
    CONFIG_OPTION("ui.msg_line"s,         int,         inf_msgline);
    CONFIG_OPTION("ui.tile_size"s,        int,         inf_tiles);
    CONFIG_OPTION("ui.font_size"s,        int,         inf_mesfont);
    CONFIG_OPTION("ui.inf_ver_type"s,     int,         inf_vertype);
    CONFIG_OPTION("ui.window_x"s,         int,         windowx);
    CONFIG_OPTION("ui.window_y"s,         int,         windowy);
    CONFIG_OPTION("ui.clock_x"s,          int,         inf_clockx);
    CONFIG_OPTION("ui.clock_w"s,          int,         inf_clockw);
    CONFIG_OPTION("ui.clock_h"s,          int,         inf_clockh);
    CONFIG_OPTION("game.default_save"s,   std::string, defload);    // TODO runtime enum
    CONFIG_OPTION("debug.wizard"s,        bool,        config::instance().wizard);
    CONFIG_OPTION("screen.display_mode"s, std::string, config::instance().display_mode);

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

void config::init()
{
    clear();
    const fs::path config_def_file =
        filesystem::dir::mods() / u8"core"s / u8"config"s / u8"config_def.hcl"s;
    def.init(config_def_file);
}

void config::load_defaults(bool preload)
{
    for (auto& pair : def)
    {
        const std::string& key = pair.first;

        // Sections don't have defaults, so trying to set them would
        // cause an error.
        if (!def.is<config_def::config_section_def>(key))
        {
            if (preload == def.is_preload(key))
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

    visit_object(conf.as<hcl::Object>(), "core.config", hcl_file, preload);
}

void config::visit_object(const hcl::Object& object,
                          const std::string& current_key,
                          const std::string& hcl_file,
                          bool preload)
{
    for (const auto& pair : object)
    {
        visit(pair.second, current_key + "." + pair.first, hcl_file, preload);
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
        visit_object(value.as<hcl::Object>(), current_key, hcl_file, preload);
    }
    else
    {
        if (!def.exists(current_key))
        {
            throw config_loading_error(hcl_file + ": No such config value \"" + current_key + "\".");
        }
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
    if (value.is<bool>())
    {
        return def.is<config_def::config_bool_def>(current_key);
    }
    if (value.is<int>())
    {
        return def.is<config_def::config_enum_def>(current_key)
            || def.is<config_def::config_int_def>(current_key);
    }
    if (value.is<hcl::List>())
    {
        return def.is<config_def::config_list_def>(current_key);
    }
    if (value.is<std::string>())
    {
        return def.is<config_def::config_string_def>(current_key);
    }

    return false;
}

void config::write()
{
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

        hcl::Value value = hcl::Value(hcl::Object());
        for (auto&& pair : storage)
        {
            value[pair.first] = pair.second;
        }
        file << value;
    }
}

} // namespace elona
