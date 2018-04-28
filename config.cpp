#include "config.hpp"
#include <fstream>
#include <functional>
#include <stdexcept>
#include "elona.hpp"
#include "json.hpp"
#include "range.hpp"
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



struct config_base
{
    virtual void set(const picojson::object& options) = 0;
};



// TODO: rename
template <typename T>
struct config_value : public config_base
{
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


using config_integer = config_value<int64_t>;
using config_string = config_value<std::string>;



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



void load_config()
{
    // FIXME std::string{value} => value
    std::unique_ptr<config_base> config_list[] = {
        std::make_unique<config_integer>(
            u8"alert_wait",
            50,
            [&](auto value) { config::instance().alert = value; }),
        std::make_unique<config_integer>(
            u8"anime_wait",
            20,
            [&](auto value) { config::instance().animewait = value; }),
        std::make_unique<config_integer>(
            u8"ignoreDislike",
            1,
            [&](auto value) { config::instance().ignoredislike = value; }),
        std::make_unique<config_integer>(
            u8"wait1",
            30,
            [&](auto value) { config::instance().wait1 = value; }),
        std::make_unique<config_string>(
            u8"font1",
            "",
            [&](auto value) { config::instance().font1 = std::string{value}; }),
        std::make_unique<config_string>(
            u8"font2",
            "",
            [&](auto value) { config::instance().font2 = std::string{value}; }),
        std::make_unique<config_integer>(
            u8"fontVfix1",
            -1,
            [&](auto value) { vfix = value; }),
        std::make_unique<config_integer>(
            u8"fontSfix1",
            1,
            [&](auto value) { sizefix = value; }),
        std::make_unique<config_integer>(
            u8"story",
            1,
            [&](auto value) { config::instance().story = value; }),
        std::make_unique<config_integer>(
            u8"heartbeat",
            1,
            [&](auto value) { config::instance().heart = value; }),
        std::make_unique<config_integer>(
            u8"extraHelp",
            1,
            [&](auto value) { config::instance().extrahelp = value; }),
        std::make_unique<config_integer>(
            u8"hpBar",
            2,
            [&](auto value) { config::instance().hp_bar = value; }),
        std::make_unique<config_integer>(
            u8"leashIcon",
            1,
            [&](auto value) { config::instance().leash_icon = value; }),
        std::make_unique<config_integer>(
            u8"alwaysCenter",
            1,
            [&](auto value) { config::instance().alwayscenter = value; }),
        std::make_unique<config_integer>(
            u8"scroll",
            1,
            [&](auto value) { config::instance().scroll = value; }),
        std::make_unique<config_integer>(
            u8"startRun",
            2,
            [&](auto value) { config::instance().startrun = value; }),
        std::make_unique<config_integer>(
            u8"walkWait",
            5,
            [&](auto value) { config::instance().walkwait = value; }),
        std::make_unique<config_integer>(
            u8"runWait",
            2,
            [&](auto value) { config::instance().runwait = value; }),
        std::make_unique<config_integer>(
            u8"autoTurnType",
            0,
            [&](auto value) { config::instance().autoturn = value; }),
        std::make_unique<config_integer>(
            u8"autoNumlock",
            1,
            [&](auto value) { config::instance().autonumlock = value; }),
        std::make_unique<config_integer>(
            u8"attackWait",
            4,
            [&](auto value) { config::instance().attackwait = value; }),
        std::make_unique<config_integer>(
            u8"attackAnime",
            1,
            [&](auto value) { config::instance().attackanime = value; }),
        std::make_unique<config_integer>(
            u8"envEffect",
            1,
            [&](auto value) { config::instance().env = value; }),
        std::make_unique<config_integer>(
            u8"titleEffect",
            1,
            [&](auto) { /* Unsupported option */ }),
        std::make_unique<config_integer>(
            u8"net",
            1,
            [&](auto value) { config::instance().net = value; }),
        std::make_unique<config_integer>(
            u8"netWish",
            1,
            [&](auto value) { config::instance().netwish = value; }),
        std::make_unique<config_integer>(
            u8"netChat",
            1,
            [&](auto value) { config::instance().netchat = value; }),
        std::make_unique<config_integer>(
            u8"serverList",
            0,
            [&](auto value) { config::instance().serverlist = value; }),
        std::make_unique<config_integer>(
            u8"shadow",
            0,
            [&](auto value) { config::instance().shadow = value; }),
        std::make_unique<config_integer>(
            u8"objectShadow",
            1,
            [&](auto value) { config::instance().objectshadow = value; }),
        std::make_unique<config_integer>(
            u8"windowAnime",
            0,
            [&](auto value) { config::instance().windowanime = value; }),
        std::make_unique<config_integer>(
            u8"hide_autoIdentify",
            0,
            [&](auto value) { config::instance().hideautoidentify = value; }),
        std::make_unique<config_integer>(
            u8"hide_shopResult",
            0,
            [&](auto value) { config::instance().hideshopresult = value; }),
        std::make_unique<config_integer>(
            u8"msg_trans",
            4,
            [&](auto value) { config::instance().msgtrans = value; }),
        std::make_unique<config_integer>(
            u8"msg_addTime",
            0,
            [&](auto value) { config::instance().msgaddtime = value; }),
        std::make_unique<config_key>(
            u8"key_cancel",
            u8"\\",
            [&](auto value, auto jk) {
                key_cancel = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_esc",
            u8"^",
            [&](auto value, auto jk) {
                key_esc = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_alter",
            u8"[",
            [&](auto value, auto jk) {
                key_alter = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_north",
            u8"8 ",
            [&](auto value) { key_north = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_south",
            u8"2 ",
            [&](auto value) { key_south = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_west",
            u8"4 ",
            [&](auto value) { key_west = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_east",
            u8"6 ",
            [&](auto value) { key_east = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_northwest",
            u8"7 ",
            [&](auto value) { key_northwest = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_northeast",
            u8"9 ",
            [&](auto value) { key_northeast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_southwest",
            u8"1 ",
            [&](auto value) { key_southwest = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_southeast",
            u8"3 ",
            [&](auto value) { key_southeast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_wait",
            u8"5 ",
            [&](auto value) { key_wait = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_inventory",
            u8"X",
            [&](auto value) { key_inventory = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_help",
            u8"?",
            [&](auto value, auto jk) {
                key_help = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_msglog",
            u8"/",
            [&](auto value) { key_msglog = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pageup",
            u8"+",
            [&](auto value) { key_pageup = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pagedown",
            u8"-",
            [&](auto value) { key_pagedown = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_get",
            u8"g",
            [&](auto value, auto jk) {
                key_get = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_get2",
            u8"0",
            [&](auto value) { key_get2 = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_drop",
            u8"d",
            [&](auto value) { key_drop = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_charainfo",
            u8"c",
            [&](auto value, auto jk) {
                key_charainfo = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_enter",
            u8" ",
            [&](auto value, auto jk) {
                key_enter = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_eat",
            u8"e",
            [&](auto value) { key_eat = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_wear",
            u8"w",
            [&](auto value) { key_wear = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_cast",
            u8"v",
            [&](auto value) { key_cast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_drink",
            u8"q",
            [&](auto value) { key_drink = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_read",
            u8"r",
            [&](auto value) { key_read = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_zap",
            u8"z",
            [&](auto value) { key_zap = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_fire",
            u8"f",
            [&](auto value, auto jk) {
                key_fire = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_goDown",
            u8">",
            [&](auto value) { key_godown = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_goUp",
            u8"<",
            [&](auto value) { key_goup = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_save",
            u8"S",
            [&](auto value) { key_save = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_search",
            u8"s",
            [&](auto value) { key_search = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_interact",
            u8"i",
            [&](auto value) { key_interact = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_identify",
            u8"x",
            [&](auto value) { key_identify = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_skill",
            u8"a",
            [&](auto value) { key_skill = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_close",
            u8"c",
            [&](auto value) { key_close = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_rest",
            u8"R",
            [&](auto value) { key_rest = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_target",
            u8"*",
            [&](auto value, auto jk) {
                key_target = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_dig",
            u8"D",
            [&](auto value) { key_dig = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_use",
            u8"t",
            [&](auto value) { key_use = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_bash",
            u8"b",
            [&](auto value) { key_bash = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_open",
            u8"o",
            [&](auto value) { key_open = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_dip",
            u8"B",
            [&](auto value) { key_dip = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pray",
            u8"p",
            [&](auto value) { key_pray = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_offer",
            u8"O",
            [&](auto value) { key_offer = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_journal",
            u8"j",
            [&](auto value) { key_journal = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_material",
            u8"m",
            [&](auto value) { key_material = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_quick",
            u8"z",
            [&](auto value, auto jk) {
                key_quick = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_trait",
            u8"F",
            [&](auto value) { key_trait = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_look",
            u8"l",
            [&](auto value) { key_look = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_give",
            u8"G",
            [&](auto value) { key_give = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_throw",
            u8"T",
            [&](auto value) { key_throw = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_mode",
            u8"z",
            [&](auto value) { key_mode = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_mode2",
            u8"*",
            [&](auto value) { key_mode2 = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_ammo",
            u8"A",
            [&](auto value, auto jk) {
                key_ammo = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_quickinv",
            u8"x",
            [&](auto value, auto jk) {
                key_quickinv = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_quicksave",
            u8"F1",
            [&](auto value) { key_quicksave = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_quickload",
            u8"F2",
            [&](auto value) { key_quickload = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_autodig",
            u8"H",
            [&](auto value) { key_autodig = std::string{value}; }),
        std::make_unique<config_integer>(
            u8"zkey",
            0,
            [&](auto value) { config::instance().zkey = value; }),
        std::make_unique<config_integer>(
            u8"xkey",
            0,
            [&](auto value) { config::instance().xkey = value; }),
        std::make_unique<config_integer>(
            u8"scr_sync",
            2,
            [&](auto value) { config::instance().scrsync = value; }),
        std::make_unique<config_integer>(
            u8"scroll_run",
            1,
            [&](auto value) { config::instance().runscroll = value; }),
        std::make_unique<config_integer>(
            u8"skipRandEvents",
            0,
            [&](auto value) { config::instance().skiprandevents = value; }),
        std::make_unique<config_key_sequence>(
            u8"key_set",
            std::vector<std::string>{
                u8"a",
                u8"b",
                u8"c",
                u8"d",
                u8"e",
                u8"f",
                u8"g",
                u8"h",
                u8"i",
                u8"j",
                u8"k",
                u8"l",
                u8"m",
                u8"n",
                u8"o",
                u8"p",
                u8"q",
                u8"r",
                u8"s",
            },
            [&](const auto& values) {
                for_each_with_index(
                    std::begin(values),
                    std::end(values),
                    [&](auto index, auto value) { key_select(index) = value; });
            }),
    };

    picojson::value value;

    {
        std::ifstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }

        file >> value;
    }

    const picojson::object& options = value.get<picojson::object>();
    for (const auto& config : config_list)
    {
        config->set(options);
    }

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
        buffer(4);
        picload(filesystem::path(u8"./graphic/lang.bmp"));
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
            if (getkey(snail::key::space))
            {
                break;
            }
        }

        config::instance().language = p;
        set_config(u8"language", p);
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
        set_config("key_mode", key_mode);
    }
    if (key_mode2 == ""s)
    {
        key_mode2 = u8"*"s;
        set_config("key_mode2", key_mode2);
    }
    if (key_ammo == ""s)
    {
        key_ammo = u8"A"s;
        set_config("key_mode2", key_ammo);
    }
}



void set_config(const std::string& key, int value)
{
    picojson::value options;

    {
        std::ifstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        file >> options;
    }

    options.get(key) = picojson::value{int64_t{value}};

    {
        std::ofstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void set_config(const std::string& key, const std::string& value)
{
    picojson::value options;

    {
        std::ifstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        file >> options;
    }

    options.get(key) = picojson::value{value};

    {
        std::ofstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void set_config(const std::string& key, const std::string& value1, int value2)
{
    picojson::value options;

    {
        std::ifstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        file >> options;
    }

    options.get(key) = picojson::value{value1};
    (void)value2; // TODO

    {
        std::ofstream file{filesystem::path(u8"./config.json").native(),
                           std::ios::binary};
        if (!file)
        {
            throw config_loading_error{
                u8"Failed to open: "s
                + filesystem::make_preferred_path_in_utf8(
                      filesystem::path(u8"./config.json"))};
        }
        options.serialize(std::ostream_iterator<char>(file), true);
    }
}



void load_config2()
{
    std::unique_ptr<config_base> config_list[] = {
        std::make_unique<config_integer>(
            u8"language",
            -1,
            [&](auto value) { config::instance().language = value; }),
        std::make_unique<config_integer>(
            u8"fullscreen",
            0,
            [&](auto value) { config::instance().fullscreen = value; }),
        std::make_unique<config_integer>(
            u8"music",
            1,
            [&](auto value) { config::instance().music = value; }),
        std::make_unique<config_integer>(
            u8"sound",
            1,
            [&](auto value) { config::instance().sound = value; }),
        std::make_unique<config_integer>(
            u8"extraRace",
            0,
            [&](auto value) { config::instance().extrarace = value; }),
        std::make_unique<config_integer>(
            u8"extraClass",
            0,
            [&](auto value) { config::instance().extraclass = value; }),
        std::make_unique<config_integer>(
            u8"joypad",
            1,
            [&](auto value) { config::instance().joypad = value; }),
        std::make_unique<config_integer>(
            u8"msgLine", 4, [&](auto value) { inf_msgline = value; }),
        std::make_unique<config_integer>(
            u8"tileSize", 48, [&](auto value) { inf_tiles = value; }),
        std::make_unique<config_integer>(
            u8"fontSize", 14, [&](auto value) { inf_mesfont = value; }),
        std::make_unique<config_integer>(
            u8"infVerType", 1, [&](auto value) { inf_vertype = value; }),
        std::make_unique<config_integer>(
            u8"windowX", 0, [&](auto value) { windowx = value; }),
        std::make_unique<config_integer>(
            u8"windowY", 0, [&](auto value) { windowy = value; }),
        std::make_unique<config_integer>(
            u8"windowW", 800, [&](auto value) { windoww = value; }),
        std::make_unique<config_integer>(
            u8"windowH", 600, [&](auto value) { windowh = value; }),
        std::make_unique<config_integer>(
            u8"clockX", 0, [&](auto value) { inf_clockx = value; }),
        std::make_unique<config_integer>(
            u8"clockW", 120, [&](auto value) { inf_clockw = value; }),
        std::make_unique<config_integer>(
            u8"clockH", 96, [&](auto value) { inf_clockh = value; }),
        std::make_unique<config_string>(
            u8"defLoadFolder", "", [&](auto value) { defload = value; }),
        std::make_unique<config_integer>(
            u8"charamake_wiz",
            0,
            [&](auto value) { config::instance().wizard = value; }),
    };

    std::ifstream file{filesystem::path(u8"./config.json").native(),
                       std::ios::binary};
    if (!file)
    {
        throw config_loading_error{u8"Failed to open: "s
                                   + filesystem::make_preferred_path_in_utf8(
                                         filesystem::path(u8"./config.json"))};
    }

    picojson::value value;
    file >> value;

    const picojson::object& options = value.get<picojson::object>();
    for (const auto& config : config_list)
    {
        config->set(options);
    }
}


config& config::instance()
{
    static config the_instance;
    return the_instance;
}



} // namespace elona
