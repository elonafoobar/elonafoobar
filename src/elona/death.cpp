#include "../thirdparty/json5/json5.hpp"
#include "audio.hpp"
#include "calc.hpp"
#include "character.hpp"
#include "draw.hpp"
#include "enums.hpp"
#include "game.hpp"
#include "i18n.hpp"
#include "input.hpp"
#include "input_prompt.hpp"
#include "message.hpp"
#include "net.hpp"
#include "quest.hpp"
#include "text.hpp"
#include "ui.hpp"
#include "variables.hpp"



namespace elona
{

namespace
{

struct Bone
{
    int score;
    std::string alias;
    std::string name;
    std::string last_words;
    std::string date;
    std::string cause;
    int image;
};



std::vector<Bone> parse_bone_file(const fs::path& filepath)
{
    std::vector<Bone> result;
    std::ifstream in{filepath.native()};
    if (!in)
        return {};

    const std::string content{
        std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};

    try
    {
        const auto value = json5::parse(content);
        for (const auto bone : value.get_array())
        {
            const auto& bone_obj = bone.get_object();
            Bone b;
            b.score = bone_obj.find("score")->second.get_integer();
            b.alias = bone_obj.find("alias")->second.get_string();
            b.name = bone_obj.find("name")->second.get_string();
            b.last_words = bone_obj.find("last_words")->second.get_string();
            b.date = bone_obj.find("date")->second.get_string();
            b.cause = bone_obj.find("cause")->second.get_string();
            b.image = std::stoi(bone_obj.find("image")->second.get_string());
            result.push_back(b);
        }
        return result;
    }
    catch (std::runtime_error&)
    {
        return {};
    }
}



void save_bone_file(const std::vector<Bone>& bones, const fs::path& filepath)
{
    std::ofstream out{filepath.native()};
    if (!out)
        return;

    json5::value::array_type array;
    for (const auto& bone : bones)
    {
        json5::value::object_type b;
        b["score"] = static_cast<json5::integer_type>(bone.score);
        b["alias"] = bone.alias;
        b["name"] = bone.name;
        b["last_words"] = bone.last_words;
        b["date"] = bone.date;
        b["cause"] = bone.cause;
        b["image"] = std::to_string(bone.image);
        array.push_back(b);
    }

    json5::stringify_options opts;
    opts.prettify = true;
    opts.insert_trailing_comma = true;
    opts.unquote_key = true;
    opts.sort_by_key = true;
    out << json5::stringify(array, opts) << std::endl;
}



void show_game_score_ranking(
    const std::vector<Bone>& bones,
    size_t this_death_index)
{
    constexpr size_t range_of_ranking = 8;

    gmode(0);
    draw("core.void", 0, 0, windoww, windowh);
    gmode(2);
    font(14 - en * 2);

    int x = 135;
    int y = 134;

    size_t index_offset;
    if (this_death_index < range_of_ranking / 2)
    {
        index_offset = 0;
    }
    else if (
        bones.size() <=
        this_death_index - range_of_ranking / 2 + range_of_ranking)
    {
        if (range_of_ranking < bones.size())
        {
            index_offset = bones.size() - range_of_ranking;
        }
        else
        {
            index_offset = 0;
        }
    }
    else
    {
        index_offset = this_death_index - range_of_ranking / 2;
    }

    for (size_t i = 0; i < range_of_ranking; ++i)
    {
        y += 46;
        const auto index = index_offset + i;

        std::string rank_string;
        if (index == this_death_index)
        {
            rank_string = "New!";
        }
        else
        {
            rank_string = " " + i18n::s.get("core.misc.score.rank", index + 1);
        }
        mes(x - 80, y + 10, rank_string, {10, 10, 10});

        if (bones.size() <= index)
        {
            mes(x, y, u8"no entry", {10, 10, 10});
            continue;
        }

        const auto& bone = bones[index];
        auto name_alias_date = bone.alias + " " + bone.name +
            i18n::space_if_needed() + bone.last_words;
        lenfix(name_alias_date, 60);
        name_alias_date += bone.date;
        mes(x, y, name_alias_date, {10, 10, 10});
        mes(x, y + 20, bone.cause, {10, 10, 10});
        mes(x + 480,
            y + 20,
            i18n::s.get("core.misc.score.score", bone.score),
            {10, 10, 10});

        draw_chara_scale_height(bone.image % 1000, x - 22, y + 12);
    }
}

} // namespace



TurnResult pc_died()
{
    snd("core.dead1");
    screenupdate = -1;
    update_screen();
    if (game_data.executing_immediate_quest_type)
    {
        return quest_pc_died_during_immediate_quest();
    }

    txt(i18n::s.get("core.misc.death.good_bye"));
    txt(i18n::s.get("core.misc.death.you_leave_dying_message"));

    inputlog = "";
    input_text_dialog((windoww - 310) / 2 + inf_screenx, winposy(90), 16);

    std::string last_words;
    if (inputlog == ""s)
    {
        last_words = i18n::s.get("core.system.last_words");
    }
    else
    {
        last_words = i18n::s.get("core.misc.death.dying_message", inputlog(0));
    }

    Bone this_death;
    this_death.score = calcscore();
    this_death.alias = cdata.player().alias;
    this_death.name = cdata.player().name;
    this_death.last_words = last_words;
    this_death.date = i18n::s.get(
        "core.misc.death.date",
        game_data.date.year,
        game_data.date.month,
        game_data.date.day);
    this_death.cause =
        i18n::s.get("core.misc.death.you_died", ndeathcause, mdatan(0));
    this_death.image = cdata.player().image;

    const auto bone_filepath = filesystem::dirs::save() / "bone.json";
    auto bones = parse_bone_file(bone_filepath);
    bones.push_back(this_death);
    // Sort bones by score in descending.
    range::sort(
        bones, [](const auto& a, const auto& b) { return a.score > b.score; });

    const auto this_death_index = std::distance(
        std::begin(bones), range::find_if(bones, [&](const auto& b) {
            return this_death.score == b.score && this_death.date == b.date;
        }));

    save_bone_file(bones, bone_filepath);

    asset_load("core.void");
    gsel(0);
    show_game_score_ranking(bones, this_death_index);
    ui_draw_caption(i18n::s.get("core.misc.death.you_are_about_to_be_buried"));

    Prompt prompt("core.misc.death");
    prompt.append("crawl_up", snail::Key::key_a);
    prompt.append("lie_on_your_back", snail::Key::key_b);
    rtval = prompt.query(promptx, 100, 240);

    if (rtval == 1)
    {
        show_game_score_ranking(bones, this_death_index);
        ui_draw_caption(i18n::s.get("core.misc.death.you_have_been_buried"));
        redraw();
        wait_key_pressed();
        return TurnResult::finish_elona;
    }
    net_send_death(ndeathcause, mdatan(0), last_words);
    screenupdate = -1;
    update_entire_screen();
    levelexitby = 3;
    return TurnResult::exit_map;
}

} // namespace elona
