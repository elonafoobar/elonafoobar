#include <fstream>
#include <functional>
#include <stdexcept>
#include <string_view>
#include "elona.hpp"
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



std::vector<std::string_view> parse_records(std::string_view line)
{
    std::vector<std::string_view> ret;
    std::string_view::size_type pos = 0;

    while (1)
    {
        const auto open_dquote = line.find(u8'"', pos);
        if (open_dquote == std::string_view::npos)
        {
            break;
        }
        const auto closing_dquote = line.find(u8'"', open_dquote + 1);
        if (closing_dquote == std::string_view::npos)
        {
            throw config_loading_error{"Missing closing double quote: "s
                                       + std::string{line}};
        }
        ret.emplace_back(std::string_view{line}.substr(
            open_dquote + 1, closing_dquote - open_dquote - 1));
        pos = closing_dquote + 1;
    }

    return ret;
}



int stoi(std::string_view s)
{
    try
    {
        return std::stoi(std::string{s});
    }
    catch (std::invalid_argument&)
    {
        throw config_loading_error{"Cannot convert to an integer: "s
                                   + std::string{s}};
    }
    catch (std::out_of_range&)
    {
        throw config_loading_error{"Out of range: "s + std::string{s}};
    }
}



struct config_base
{
    config_base(std::string_view pattern)
        : pattern(pattern)
    {
    }


    virtual ~config_base() = default;


    bool matches(std::string_view line) const
    {
        return line.find(pattern) != std::string_view::npos;
    }


    virtual void set(std::string_view line) = 0;


private:
    std::string_view pattern;
};



struct config_integer : public config_base
{
    config_integer(std::string_view pattern, std::function<void(int)> callback)
        : config_base(pattern)
        , callback(callback)
    {
    }


    virtual ~config_integer() = default;


    virtual void set(std::string_view line) override
    {
        const auto records = parse_records(line);
        if (std::size(records) < 1)
        {
            throw config_loading_error{"Too few records: "s + s};
        }
        callback(stoi(records.front()));
    }


private:
    std::function<void(int)> callback;
};



struct config_string : public config_base
{
    config_string(
        std::string_view pattern,
        std::function<void(std::string_view)> callback)
        : config_base(pattern)
        , callback(callback)
    {
    }


    virtual ~config_string() = default;


    virtual void set(std::string_view line) override
    {
        const auto records = parse_records(line);
        if (std::size(records) < 1)
        {
            throw config_loading_error{"Too few records: "s + s};
        }
        callback(records.front());
    }


private:
    std::function<void(std::string_view)> callback;
};



struct config_key : public config_base
{
    config_key(
        std::string_view pattern,
        std::function<void(std::string_view, int)> callback)
        : config_base(pattern)
        , callback(callback)
    {
    }


    virtual ~config_key() = default;


    virtual void set(std::string_view line) override
    {
        const auto records = parse_records(line);
        if (std::size(records) < 2)
        {
            throw config_loading_error{"Too few records: "s + s};
        }
        callback(records[0], stoi(records[1]));
    }


private:
    std::function<void(std::string_view, int)> callback;
};



struct config_key_sequence : public config_base
{
    config_key_sequence(
        std::string_view pattern,
        std::function<void(std::vector<std::string_view>&)> callback)
        : config_base(pattern)
        , callback(callback)
    {
    }


    virtual ~config_key_sequence() = default;


    virtual void set(std::string_view line) override
    {
        std::vector<std::string_view> records;

        std::string_view::size_type pos = 0;
        while (1)
        {
            const auto comma = line.find(u8',', pos);
            if (comma == std::string_view::npos)
            {
                break;
            }
            records.emplace_back(std::string_view{line}.substr(comma + 1, 1));
            pos = comma + 1;
        }

        callback(records);
    }


private:
    std::function<void(std::vector<std::string_view>&)> callback;
};



} // namespace



namespace elona
{


void label_2716()
{
    // FIXME std::string{value} => value
    std::unique_ptr<config_base> config_list[] = {
        std::make_unique<config_integer>(
            u8"key_sCancel.",
            [&](auto value) { cfg_scancel = value; }),
        std::make_unique<config_integer>(
            u8"alert_wait.",
            [&](auto value) { cfg_alert = value; }),
        std::make_unique<config_integer>(
            u8"anime_wait.",
            [&](auto value) { cfg_animewait = value; }),
        std::make_unique<config_integer>(
            u8"ignoreDislike.",
            [&](auto value) { cfg_ignoredislike = value; }),
        std::make_unique<config_integer>(
            u8"wait1.",
            [&](auto value) { cfg_wait1 = value; }),
        std::make_unique<config_string>(
            u8"font1.",
            [&](auto value) { cfg_font1 = std::string{value}; }),
        std::make_unique<config_string>(
            u8"font2.",
            [&](auto value) { cfg_font2 = std::string{value}; }),
        std::make_unique<config_integer>(
            u8"fontVfix1.",
            [&](auto value) { vfix = value; }),
        std::make_unique<config_integer>(
            u8"fontSfix1.",
            [&](auto value) { sizefix = value; }),
        std::make_unique<config_integer>(
            u8"story.",
            [&](auto value) { cfg_story = value; }),
        std::make_unique<config_integer>(
            u8"heartbeat.",
            [&](auto value) { cfg_heart = value; }),
        std::make_unique<config_integer>(
            u8"extraHelp.",
            [&](auto value) { cfg_extrahelp = value; }),
        std::make_unique<config_integer>(
            u8"alwaysCenter.",
            [&](auto value) { cfg_alwayscenter = value; }),
        std::make_unique<config_integer>(
            u8"scroll.",
            [&](auto value) { cfg_scroll = value; }),
        std::make_unique<config_integer>(
            u8"startRun.",
            [&](auto value) { cfg_startrun = value; }),
        std::make_unique<config_integer>(
            u8"walkWait.",
            [&](auto value) { cfg_walkwait = value; }),
        std::make_unique<config_integer>(
            u8"runWait.",
            [&](auto value) { cfg_runwait = value; }),
        std::make_unique<config_integer>(
            u8"autoTurnType.",
            [&](auto value) { cfg_autoturn = value; }),
        std::make_unique<config_integer>(
            u8"autoNumlock.",
            [&](auto value) { cfg_autonumlock = value; }),
        std::make_unique<config_integer>(
            u8"attackWait.",
            [&](auto value) { cfg_attackwait = value; }),
        std::make_unique<config_integer>(
            u8"attackAnime.",
            [&](auto value) { cfg_attackanime = value; }),
        std::make_unique<config_integer>(
            u8"envEffect.",
            [&](auto value) { cfg_env = value; }),
        std::make_unique<config_integer>(
            u8"titleEffect.",
            [&](auto value) { cfg_titleeffect = value; }),
        std::make_unique<config_integer>(
            u8"net.",
            [&](auto value) { cfg_net = value; }),
        std::make_unique<config_integer>(
            u8"netWish.",
            [&](auto value) { cfg_netwish = value; }),
        std::make_unique<config_integer>(
            u8"netChat.",
            [&](auto value) { cfg_netchat = value; }),
        std::make_unique<config_integer>(
            u8"serverList.",
            [&](auto value) { cfg_serverlist = value; }),
        std::make_unique<config_integer>(
            u8"shadow.",
            [&](auto value) { cfg_shadow = value; }),
        std::make_unique<config_integer>(
            u8"objectShadow.",
            [&](auto value) { cfg_objectshadow = value; }),
        std::make_unique<config_integer>(
            u8"windowAnime.",
            [&](auto value) { cfg_windowanime = value; }),
        std::make_unique<config_integer>(
            u8"exAnime.",
            [&](auto value) { cfg_exanime = value; }),
        std::make_unique<config_integer>(
            u8"showSkillMod.",
            [&](auto value) { cfg_showskillmod = value; }),
        std::make_unique<config_integer>(
            u8"hide_autoIdentify.",
            [&](auto value) { cfg_hideautoidentify = value; }),
        std::make_unique<config_integer>(
            u8"hide_shopResult.",
            [&](auto value) { cfg_hideshopresult = value; }),
        std::make_unique<config_integer>(
            u8"msg_trans.",
            [&](auto value) { cfg_msgtrans = value; }),
        std::make_unique<config_integer>(
            u8"msg_addTime.",
            [&](auto value) { cfg_msgaddtime = value; }),
        std::make_unique<config_key>(
            u8"key_cancel.",
            [&](auto value, auto jk) {
                key_cancel = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_esc.",
            [&](auto value, auto jk) {
                key_esc = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_alter.",
            [&](auto value, auto jk) {
                key_alter = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_north.",
            [&](auto value) { key_north = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_south.",
            [&](auto value) { key_south = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_west.",
            [&](auto value) { key_west = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_east.",
            [&](auto value) { key_east = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_northwest.",
            [&](auto value) { key_northwest = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_northeast.",
            [&](auto value) { key_northeast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_southwest.",
            [&](auto value) { key_southwest = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_southeast.",
            [&](auto value) { key_southeast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_wait.",
            [&](auto value) { key_wait = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_inventory.",
            [&](auto value) { key_inventory = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_help.",
            [&](auto value, auto jk) {
                key_help = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_msglog.",
            [&](auto value) { key_msglog = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pageup.",
            [&](auto value) { key_pageup = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pagedown.",
            [&](auto value) { key_pagedown = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_get.",
            [&](auto value, auto jk) {
                key_get = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_get2.",
            [&](auto value) { key_get2 = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_drop.",
            [&](auto value) { key_drop = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_charainfo.",
            [&](auto value, auto jk) {
                key_charainfo = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_enter.",
            [&](auto value, auto jk) {
                key_enter = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_eat.",
            [&](auto value) { key_eat = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_wear.",
            [&](auto value) { key_wear = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_cast.",
            [&](auto value) { key_cast = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_drink.",
            [&](auto value) { key_drink = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_read.",
            [&](auto value) { key_read = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_zap.",
            [&](auto value) { key_zap = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_fire.",
            [&](auto value, auto jk) {
                key_fire = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_goDown.",
            [&](auto value) { key_godown = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_goUp.",
            [&](auto value) { key_goup = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_save.",
            [&](auto value) { key_save = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_search.",
            [&](auto value) { key_search = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_interact.",
            [&](auto value) { key_interact = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_identify.",
            [&](auto value) { key_identify = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_skill.",
            [&](auto value) { key_skill = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_close.",
            [&](auto value) { key_close = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_rest.",
            [&](auto value) { key_rest = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_target.",
            [&](auto value, auto jk) {
                key_target = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_dig.",
            [&](auto value) { key_dig = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_use.",
            [&](auto value) { key_use = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_bash.",
            [&](auto value) { key_bash = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_open.",
            [&](auto value) { key_open = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_dip.",
            [&](auto value) { key_dip = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_pray.",
            [&](auto value) { key_pray = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_offer.",
            [&](auto value) { key_offer = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_journal.",
            [&](auto value) { key_journal = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_material.",
            [&](auto value) { key_material = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_quick.",
            [&](auto value, auto jk) {
                key_quick = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_string>(
            u8"key_trait.",
            [&](auto value) { key_trait = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_look.",
            [&](auto value) { key_look = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_give.",
            [&](auto value) { key_give = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_throw.",
            [&](auto value) { key_throw = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_mode.",
            [&](auto value) { key_mode = std::string{value}; }),
        std::make_unique<config_string>(
            u8"key_mode2.",
            [&](auto value) { key_mode2 = std::string{value}; }),
        std::make_unique<config_key>(
            u8"key_ammo.",
            [&](auto value, auto jk) {
                key_ammo = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_key>(
            u8"key_quickinv.",
            [&](auto value, auto jk) {
                key_quickinv = std::string{value};
                jkey(jk) = std::string{value};
            }),
        std::make_unique<config_integer>(
            u8"zkey.",
            [&](auto value) { cfg_zkey = value; }),
        std::make_unique<config_integer>(
            u8"xkey.",
            [&](auto value) { cfg_xkey = value; }),
        std::make_unique<config_integer>(
            u8"scr_sync.",
            [&](auto value) { cfg_scrsync = value; }),
        std::make_unique<config_integer>(
            u8"scroll_run.",
            [&](auto value) { cfg_runscroll = value; }),
        std::make_unique<config_integer>(
            u8"skipRandEvents.",
            [&](auto value) { cfg_skiprandevents = value; }),
        std::make_unique<config_key_sequence>(
            u8"key_set.",
            [&](auto&& values) {
                for_each_with_index(
                    std::begin(values),
                    std::end(values),
                    [&](auto index, auto value) { key_select(index) = value; });
            }),
    };


    std::fstream file{fs::u8path(u8"./config.txt")};
    if (!file)
    {
        throw config_loading_error{u8"Failed to open: "s
                                   + fs::u8path(u8"./config.txt").u8string()};
    }

    std::string line;
    while (std::getline(file, line))
    {
        for (const auto& config : config_list)
        {
            if (config->matches(line))
            {
                config->set(line);
                break;
            }
        }
    }

    key_prev = key_northwest;
    key_next = key_northeast;

    if (cfg_zkey == 0)
    {
        key_quick = u8"z"s;
        key_zap = u8"Z"s;
    }
    else if (cfg_zkey == 1)
    {
        key_zap = u8"z"s;
        key_quick = u8"Z"s;
    }
    if (cfg_xkey == 0)
    {
        key_quickinv = u8"x"s;
        key_inventory = u8"X"s;
    }
    else if (cfg_xkey == 1)
    {
        key_inventory = u8"x"s;
        key_quickinv = u8"X"s;
    }
    if (cfg_scrsync == 0)
    {
        cfg_scrsync = 3;
    }
    if (cfg_walkwait == 0)
    {
        cfg_walkwait = 5;
    }
    if (cfg_runwait < 1)
    {
        cfg_runwait = 1;
    }
    if (cfg_attackwait < 1)
    {
        cfg_attackwait = 1;
    }
    if (cfg_startrun >= 20)
    {
        cfg_startrun = 1000;
    }

    if (cfg_language == -1)
    {
        redraw(0);
        buffer(4);
        picload(fs::u8path(u8"./graphic/lang.bmp"));
        gsel(0);
        gmode(0);
        p = 0;

        while (1)
        {
            redraw(0);
            color(0, 0, 0);
            boxf();
            pos(160, 170);
            gcopy(4, 0, 0, 340, 100);
            pos(180, 220 + p * 20);
            gcopy(4, 360, 6, 20, 18);
            redraw(1);
            await(30);
            getkey(a, 40);
            if (a)
            {
                p = 1;
            }
            getkey(a, 98);
            if (a)
            {
                p = 1;
            }
            getkey(a, 38);
            if (a)
            {
                p = 0;
            }
            getkey(a, 104);
            if (a)
            {
                p = 0;
            }
            getkey(a, 13);
            if (a)
            {
                break;
            }
            getkey(a, 32);
            if (a)
            {
                break;
            }
        }

        cfg_language = p;
        valn(0) = u8"language."s;
        valn(1) = ""s + p;
        label_2713();
        redraw(0);
    }
    if (cfg_language == 0)
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
        file << u8"key_mode.\t\"z\"" << std::endl;
    }
    if (key_mode2 == ""s)
    {
        key_mode2 = u8"*"s;
        file << u8"key_mode2.\t\"*\"" << std::endl;
    }
    if (key_ammo == ""s)
    {
        key_ammo = u8"A"s;
        file << u8"key_ammo.\t\"A\"" << std::endl;
    }
}


} // namespace elona
