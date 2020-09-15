#include "save_header.hpp"

#include <ctime>

#include <chrono>

#include "../version.hpp"
#include "character.hpp"
#include "class.hpp"
#include "game.hpp"
#include "json5util.hpp"
#include "race.hpp"
#include "serialization/serialization.hpp"
#include "text.hpp"



namespace elona
{

namespace
{

const fs::path vanilla_filename = "header.txt";
const fs::path foobar_filename = "header.json";



int64_t now_unix_time()
{
    using std::chrono::system_clock;

    return system_clock::to_time_t(system_clock::now());
}



int64_t get_played_seconds()
{
    return game_data.play_time;
}



std::string last_played_at_to_string(int64_t time)
{
    std::time_t time_ = static_cast<std::time_t>(time);
    const std::tm* local_time = std::localtime(&time_);

    // TODO: localize
    const auto y = local_time->tm_year + 1900;
    const auto M = local_time->tm_mon + 1;
    const auto d = local_time->tm_mday;
    const auto h = local_time->tm_hour;
    const auto m = local_time->tm_min;

    return i18n::s.get("core.ui.save_header.last_played_at", y, M, d, h, m);
}



std::string play_seconds_to_string(int64_t sec)
{
    if (sec < 3600) // less than 1 hour
    {
        return i18n::s.get(
            "core.ui.save_header.play_seconds.minutes",
            std::max(sec / 60, int64_t{1}));
    }
    else
    {
        return i18n::s.get(
            "core.ui.save_header.play_seconds.hours",
            sec / 3600,
            (sec % 3600) / 60);
    }
}



// TODO: not implemented yet
std::string detect_save_data_version()
{
    return "vanilla v1.22";
}

} // namespace



std::string SaveHeader::title() const
{
    return save_dir_name + "   " + version;
}



std::vector<std::string> SaveHeader::to_string() const
{
    if (format == Format::vanilla)
    {
        return {
            name + "  Lv: " + std::to_string(level) + "   " + location,
        };
    }
    else
    {
        return {
            last_played_at_to_string(last_played_at) + "   " +
                play_seconds_to_string(play_seconds),
            alias + " " + name + "  Lv: " + std::to_string(level) + "   " +
                race + " " + class_,
            ingame_time + "   " + location,
        };
    }
}



SaveHeader SaveHeader::load(const fs::path& save_dir)
{
    assert(SaveHeader::exists(save_dir));

    if (fs::exists(save_dir / foobar_filename))
    {
        return load_foobar(save_dir);
    }
    else
    {
        return load_vanilla(save_dir);
    }
}



void SaveHeader::save(const fs::path& save_dir)
{
    auto h = SaveHeader::current_state();

    {
        // Vanilla
        std::ofstream out{(save_dir / vanilla_filename).native()};
        out << h.name << " Lv:" << h.level << " " << h.location << std::endl;
    }
    {
        // foobar
        std::ofstream out{(save_dir / foobar_filename).native()};
        json5::value::object_type json;

        json["version"] = h.version;
        json["name"] = h.name;
        json["alias"] = h.alias;
        json["level"] = h.level;
        json["race"] = h.race;
        json["class"] = h.class_;
        json["location"] = h.location;
        json["ingame_time"] = h.ingame_time;
        json["last_played_at"] = h.last_played_at;
        json["play_seconds"] = h.play_seconds;

        json5::stringify_options opts;
        opts.prettify = true;
        opts.insert_trailing_comma = true;
        opts.unquote_key = true;
        opts.sort_by_key = true;

        out << json5::stringify(json, opts) << std::endl;
    }
}



bool SaveHeader::exists(const fs::path& save_dir)
{
    return fs::exists(save_dir / vanilla_filename) ||
        fs::exists(save_dir / foobar_filename);
}



SaveHeader SaveHeader::current_state()
{
    const auto play_seconds = get_played_seconds();
    const auto now = now_unix_time();

    SaveHeader h;

    // The format of the newly-saved header is always @ref
    // SaveHeader::Format::foobar.
    h.format = Format::foobar;
    // h.save_dir_name = no need to set here;

    h.version = "v" + latest_version.short_string();
    h.name = cdata.player().name;
    h.alias = cdata.player().alias;
    h.level = cdata.player().level;
    h.race = the_race_db.get_text(cdata.player().race, "name");
    h.class_ = class_get_name(cdata.player().class_);
    h.location = mdatan(0) + maplevel();
    h.ingame_time = game_data.date.to_string(); // TODO localize
    h.last_played_at = now;
    h.play_seconds = play_seconds;

    return h;
}



/*
 * <NAME> Lv:<LEVEL> <LOCATION>
 */
SaveHeader SaveHeader::load_vanilla(const fs::path& save_dir)
{
    std::string name = "<unknown>";
    int level = 1;
    std::string location = "<unknown>";
    {
        // TODO: handle parsing error
        std::string file_content;
        std::ifstream in{(save_dir / vanilla_filename).native()};
        std::getline(in, file_content);
        const auto lv_pos = file_content.find(" Lv:");
        name = file_content.substr(0, lv_pos);
        const auto space_pos = file_content.find(' ', lv_pos + 4);
        level = std::stoi(file_content.substr(lv_pos + 4, space_pos));
        location = file_content.substr(space_pos + 1);
    }

    SaveHeader h;

    h.format = Format::vanilla;
    h.save_dir_name = save_dir.filename().to_u8string();

    h.version = detect_save_data_version();
    h.name = name;
    h.alias = "<unknown>";
    h.level = level;
    h.race = "<unknown>";
    h.class_ = "<unknown>";
    h.location = location;
    h.ingame_time = "<unknown>";
    h.last_played_at = -1;
    h.play_seconds = 0;

    return h;
}



SaveHeader SaveHeader::load_foobar(const fs::path& save_dir)
{
    json5::value::object_type obj;
    {
        // TODO: handle parsing error
        std::ifstream in{(save_dir / foobar_filename).native()};
        auto raw_json = json5util::parse_stream(in).right();
        obj = raw_json.get_object();
    }

    SaveHeader h;

    h.format = Format::foobar;
    h.save_dir_name = save_dir.filename().to_u8string();

    h.version = obj["version"].get_string();
    h.name = obj["name"].get_string();
    h.alias = obj["alias"].get_string();
    h.level = obj["level"].get_integer();
    h.race = obj["race"].get_string();
    h.class_ = obj["class"].get_string();
    h.location = obj["location"].get_string();
    h.ingame_time = obj["ingame_time"].get_string();
    h.last_played_at = obj["last_played_at"].get_integer();
    h.play_seconds = obj["play_seconds"].get_integer();

    return h;
}

} // namespace elona
