#include "area.hpp"
#include "character.hpp"
#include "data/types/type_ability.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "fov.hpp"
#include "i18n.hpp"
#include "map.hpp"
#include "random.hpp"
#include "variables.hpp"


namespace elona
{


int p_at_m34 = 0;
int talkref = 0;
elona_vector1<int> p_at_m41;



std::string zentohan(const std::string& str)
{
    // TODO: Implement.
    return str;
}



std::string cnvrank(int n)
{
    if (jp)
        return std::to_string(n);

    if (n % 10 == 1 && n != 11)
        return std::to_string(n) + u8"st";
    else if (n % 10 == 2 && n != 12)
        return std::to_string(n) + u8"nd";
    else if (n % 10 == 3 && n != 13)
        return std::to_string(n) + u8"rd";
    else
        return std::to_string(n) + u8"th";
}



std::string cnvarticle(const std::string& str)
{
    return i18n::s.get("core.locale.ui.article", str);
}



std::string cnvitemname(int id)
{
    if (jp)
        return ioriginalnameref(id);

    if (ioriginalnameref2(id) == ""s)
    {
        return ioriginalnameref(id);
    }
    return ioriginalnameref2(id) + u8" of "s + ioriginalnameref(id);
}



std::string cnven(const std::string& source)
{
    if (jp)
        return source;
    if (source.empty())
        return source;

    std::string ret = source;
    if (ret[0] == '*')
    {
        if (source.size() == 1)
            return source;
        ret[1] = std::toupper(ret[1]);
    }
    else
    {
        ret[0] = std::toupper(ret[0]);
    }
    return ret;
}



std::string cnvfix(int n)
{
    return n >= 0 ? u8"+"s + std::to_string(n) : std::to_string(n);
}



std::string cnvdate(int datetime_id, bool show_hour)
{
    std::string ret;

    int hour = datetime_id % 24;
    int day = datetime_id / 24 % 30;
    if (day == 0)
    {
        day = 30;
        datetime_id -= 720;
    }
    int month = datetime_id / 24 / 30 % 12;
    if (month == 0)
    {
        month = 12;
        datetime_id -= 8640;
    }
    int year = datetime_id / 24 / 30 / 12;

    ret = i18n::s.get("core.locale.ui.date", year, month, day);
    if (show_hour)
    {
        ret += i18n::s.get("core.locale.ui.date_hour", hour);
    }

    return ret;
}



std::string cnvplaytime(int datetime_id)
{
    const int h = datetime_id / 60 / 60;
    const int m = datetime_id / 60 % 60;
    const int s = datetime_id % 60;
    return i18n::s.get("core.locale.ui.playtime", h, m, s);
}



// Get rid of the job and extract the name.
// Lomias the general vendor => Lomias
std::string sncnv(const std::string& name_with_job)
{
    return name_with_job.substr(0, name_with_job.find(' ')) + ' ';
}



std::string sngeneral(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.general_vendor", name);
}



std::string sninn(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.innkeeper", name);
}



std::string sntrade(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.trader", name);
}



std::string sngoods(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.goods_vendor", name);
}



std::string snbakery(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.baker", name);
}



std::string snmagic(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.magic_vendor", name);
}



std::string snarmor(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.blacksmith", name);
}



std::string sntrainer(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.trainer", name);
}



std::string snfish(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.fisher", name);
}



std::string snblack(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.blackmarket", name);
}



std::string snfood(const std::string& name)
{
    return i18n::s.get("core.locale.chara.job.food_vendor", name);
}



std::vector<std::string> txtsetwinword(int n)
{
    std::vector<std::string> ret;
    std::vector<std::string> choices;
    for (int cnt = 0; cnt < 6; cnt++)
    {
        choices.push_back(
            i18n::s.get_enum("core.locale.scenario.win_words", cnt));
    }
    sample(choices, std::back_inserter(ret), n);
    return ret;
}



void initialize_nefia_names()
{
    SDIM4(mapnamerd, 20, 2, 5);
    for (int cnt = 0; cnt < 5; cnt++)
    {
        mapnamerd(0, cnt) =
            i18n::s.get_enum("core.locale.map.nefia.prefix.type_a", cnt);
        mapnamerd(1, cnt) =
            i18n::s.get_enum("core.locale.map.nefia.prefix.type_b", cnt);
    }
}



std::string maplevel(int)
{
    if (game_data.current_map == mdata_t::MapId::your_home)
    {
        if (game_data.current_dungeon_level != 1)
        {
            if (game_data.current_dungeon_level > 0)
            {
                return u8"B."s + (game_data.current_dungeon_level - 1);
            }
            else
            {
                return u8"L."s + (game_data.current_dungeon_level - 2) * -1;
            }
        }
    }
    if (map_shows_floor_count_in_name())
    {
        return ""s +
            cnvrank(
                   (game_data.current_dungeon_level -
                    area_data[game_data.current_map].danger_level + 1)) +
            i18n::s.get("core.locale.map.nefia.level");
    }

    return "";
}


std::string mapname_dungeon(int id)
{
    int suffix_id = area_data[id].type;
    std::string name = mapnamerd(
        area_data[id].dungeon_prefix,
        std::min(area_data[id].danger_level / 5, int(mapnamerd.j_size() - 1)));

    if (mdata_t::is_nefia(suffix_id))
    {
        name += i18n::s.get_enum("core.locale.map.nefia.suffix", suffix_id);
    }
    return name;
}

std::string mapname(int id, bool description)
{
    std::string name;
    std::string desc;

    switch (static_cast<mdata_t::MapId>(area_data[id].id))
    {
    case mdata_t::MapId::quest:
        if (game_data.executing_immediate_quest_type == 1001)
        {
            name = i18n::s.get("core.locale.map.quest.outskirts");
        }
        if (game_data.executing_immediate_quest_type == 1010 ||
            game_data.executing_immediate_quest_type == 1008)
        {
            name = i18n::s.get("core.locale.map.quest.urban_area");
        }
        break;
    case mdata_t::MapId::random_dungeon: name = mapname_dungeon(id); break;
    default:
        auto name_opt = i18n::s.get_enum_property_opt(
            "core.locale.map.unique", "name", area_data[id].id);
        if (name_opt)
        {
            name = *name_opt;
        }
        else
        {
            name = "";
        }

        auto desc_opt = i18n::s.get_enum_property_opt(
            "core.locale.map.unique", "desc", area_data[id].id);
        if (desc_opt)
        {
            desc = *desc_opt;
        }
        else
        {
            desc = "";
        }
    }

    if (description)
    {
        if (area_data[id].id == mdata_t::MapId::mansion_of_younger_sister)
        {
            return "";
        }
        else if (desc != ""s)
        {
            return desc;
        }
        else if (mdata_t::is_nefia(area_data[id].type))
        {
            return i18n::s.get(
                "core.locale.map.you_see_an_entrance",
                name,
                area_data[id].danger_level);
        }
        else
        {
            return i18n::s.get("core.locale.map.you_see", name);
        }
    }
    else
    {
        return name;
    }
}



std::string txtbuilding(int prm_368, int prm_369)
{
    int p_at_m32 = 0;
    std::string s_at_m32;
    p_at_m32 = bddata(0, prm_368, prm_369);
    s_at_m32 = i18n::s.get(
        "core.locale.map.you_see",
        i18n::s.get_enum("core.locale.map.misc_location", p_at_m32));
    return s_at_m32;
}



std::string txtskillchange(int id, int cc, bool increase)
{
    if (auto text = i18n::s.get_enum_property_opt(
            "core.locale.skill",
            increase ? "increase" : "decrease",
            id,
            cdata[cc]))
    {
        return *text;
    }
    else
    {
        if (increase)
        {
            return i18n::s.get(
                "core.locale.skill.default.increase",
                cdata[cc],
                i18n::s.get_m(
                    "locale.ability",
                    the_ability_db.get_id_from_legacy(id)->get(),
                    "name"));
        }
        else
        {
            return i18n::s.get(
                "core.locale.skill.default.decrease",
                cdata[cc],
                i18n::s.get_m(
                    "locale.ability",
                    the_ability_db.get_id_from_legacy(id)->get(),
                    "name"));
        }
    }
}



std::string _yoro(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"よろしくお願いします", u8"どうぞ、よろしくです"},
         {u8"よろしくお願いしますわ", u8"よろしくです"}},
        {{u8"よろしく頼むぜ", u8"よろしくな"},
         {u8"よろしくね", u8"よろしくな"}},
        {{u8"よろしくね", u8"よろしくお願いするよ"},
         {u8"よろしくねっ", u8"よろしく〜"}},
        {{u8"よろしく…", u8"今後とも、よろしく…"},
         {u8"よろしくね…", u8"よろ…"}},
        {{u8"よろしく頼もう", u8"よろしく頼むぞよ"},
         {u8"よろしく頼むぞよ", u8"よろしく頼むぞな"}},
        {{u8"よしなに", u8"よろしく頼むでござる"},
         {u8"よろしくでござりまする", u8"どうぞよしなに"}},
        {{u8"よろしくッス"}, {u8"よろしくにゃの"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _dozo(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"はい、どうぞ", u8"お待ちどうさまです"},
         {u8"はい、どうぞ", u8"注文の品ですわ"}},
        {{u8"ほらよ", u8"ほれ"}, {u8"ほら", u8"待たせたね"}},
        {{u8"はい、お待ち", u8"さあ、どうぞ"},
         {u8"さあ、どうぞ", u8"お待ちどうさま"}},
        {{u8"ほら…", u8"待たせたな…"}, {u8"はい…", u8"どうぞ…"}},
        {{u8"ほうれ", u8"ほれ、受け取りたまえ"},
         {u8"ほれ、受け取るが良い", u8"ほれ、待たせたのう"}},
        {{u8"お待たせ申した", u8"待たせたでござる"},
         {u8"お待たせ致しました", u8"ささ、どうぞ"}},
        {{u8"お待たせッス"}, {u8"お待たせにゃん"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _thanks(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"感謝します", u8"ありがとうございます"},
         {u8"感謝します", u8"ありがとうございます"}},
        {{u8"ありがとよ", u8"ありがたい"}, {u8"礼を言うよ", u8"ありがたいね"}},
        {{u8"ありがとう", u8"感謝するよ"}, {u8"ありがとう〜", u8"感謝するわ"}},
        {{u8"礼を言う…", u8"感謝する…"}, {u8"ありがと…", u8"礼を言うわ…"}},
        {{u8"礼を申すぞ", u8"感謝してつかわす"},
         {u8"くるしゅうない", u8"礼をいってつかわす"}},
        {{u8"かたじけない", u8"恩に着る"},
         {u8"ありがたや", u8"お礼申し上げます"}},
        {{u8"アザーッス"}, {u8"にゃりーん"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _rob(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"悪いことは言わない。おやめなさい",
          u8"止めてください。きっと後悔しますよ"},
         {u8"止めてくださいませ",
          u8"こういう時のために、傭兵に金をかけているのです"}},
        {{u8"なんだ、貴様賊だったのか",
          u8"馬鹿な奴だ。後になって謝っても遅いぞ"},
         {u8"ふん、返り討ちにしてくれるよ", u8"ごろつき風情に何ができる"}},
        {{u8"おい、傭兵さんたち、このごろつきを追い払ってくれ",
          u8"馬鹿な真似をするな。こっちには屈強の傭兵がいるんだぞ"},
         {u8"やめて", u8"傭兵さんたち〜出番ですよ"}},
        {{u8"甘く見られたものだ…", u8"この護衛の数が見えないのか…"},
         {u8"おやめ…", u8"愚かな試みよ…"}},
        {{u8"なんたる無礼者か", u8"ほほほ、こやつめ"},
         {u8"下賤の者どもの分際で", u8"ほほほ、殺してあげなさい"}},
        {{u8"何をするでござるか"},
         {u8"ご無体な", u8"まあ、お戯れが過ぎますわ"}},
        {{u8"見損なったッス"}, {u8"にゃりーん"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _ka(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ですか"}, {u8"ですか"}},
        {{u8"かよ", u8"か"}, {u8"かい"}},
        {{u8"かい", u8"なの"}, {u8"なの"}},
        {{u8"か…", u8"かよ…"}, {u8"なの…"}},
        {{u8"かのう", u8"であるか"}, {u8"であるか"}},
        {{u8"でござるか"}, {u8"でござりまするか"}},
        {{u8"ッスか"}, {u8"かにゃ", u8"かニャン"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _da(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"です", u8"ですね"}, {u8"ですわ", u8"です"}},
        {{u8"だぜ", u8"だ"}, {u8"ね", u8"よ"}},
        {{u8"だよ"}, {u8"だわ", u8"よ"}},
        {{u8"だ…", u8"さ…"}, {u8"よ…", u8"ね…"}},
        {{u8"じゃ", u8"でおじゃる"}, {u8"じゃ", u8"でおじゃるぞ"}},
        {{u8"でござる", u8"でござるよ"}, {u8"でござりまする"}},
        {{u8"ッス"}, {u8"みゃん", u8"ミャ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _nda(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"のです", u8"んです"}, {u8"のですわ", u8"のです"}},
        {{"", u8"んだ"}, {u8"の"}},
        {{u8"んだよ", u8"んだ"}, {u8"わ", u8"のよ"}},
        {{u8"…", u8"んだ…"}, {u8"の…", u8"わ…"}},
        {{u8"のじゃ", u8"のだぞよ"}, {u8"のじゃわ", u8"のだぞよ"}},
        {{u8"のでござる"}, {u8"のでございます"}},
        {{u8"んだッス"}, {u8"のニャ", u8"のにゃん"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _noka(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"のですか", u8"んですか"}, {u8"のですか", u8"んですか"}},
        {{u8"のか", u8"のだな"}, {u8"の", u8"のかい"}},
        {{u8"のかい", u8"の"}, {u8"の"}},
        {{u8"のか…"}, {u8"の…"}},
        {{u8"のかのう", u8"のだな"}, {u8"のかね", u8"のだな"}},
        {{u8"のでござるか"}, {u8"のでございます"}},
        {{u8"のッスか"}, {u8"にゃんか", u8"ニャン"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _kana(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"でしょうか", u8"ですか"}, {u8"かしら", u8"でしょう"}},
        {{u8"か", u8"かい"}, {u8"か", u8"かい"}},
        {{u8"かな", u8"かなぁ"}, {u8"かな", u8"かなー"}},
        {{u8"かな…", u8"か…"}, {u8"かな…", u8"か…"}},
        {{u8"かのう", u8"かの"}, {u8"かのう", u8"かの"}},
        {{u8"でござるか"}, {u8"でございますか"}},
        {{u8"ッスか"}, {u8"かにゃん", u8"かニャ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _kimi(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"貴方"}, {u8"貴方"}},
        {{u8"お前"}, {u8"お前"}},
        {{u8"君"}, {u8"君"}},
        {{u8"君"}, {u8"君"}},
        {{u8"お主"}, {u8"お主"}},
        {{u8"そこもと"}, {u8"そなた様"}},
        {{u8"アンタ"}, {u8"あにゃた"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _ru(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ます", u8"ますよ"}, {u8"ますわ", u8"ますの"}},
        {{u8"るぜ", u8"るぞ"}, {u8"るわ", u8"るよ"}},
        {{u8"るよ", u8"るね"}, {u8"るの", u8"るわ"}},
        {{u8"る…", u8"るが…"}, {u8"る…", u8"るわ…"}},
        {{u8"るぞよ", u8"るぞ"}, {u8"るぞよ", u8"るぞ"}},
        {{u8"るでござる", u8"るでござるよ"}, {u8"るのでございます"}},
        {{u8"るッス"}, {u8"るのニャ", u8"るにゃん"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _tanomu(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"お願いします", u8"頼みます"},
         {u8"お願いしますわ", u8"頼みますわ"}},
        {{u8"頼む", u8"頼むな"}, {u8"頼むよ", u8"頼む"}},
        {{u8"頼むね", u8"頼むよ"}, {u8"頼むわ", u8"頼むね"}},
        {{u8"頼む…", u8"頼むぞ…"}, {u8"頼むわ…", u8"頼むよ…"}},
        {{u8"頼むぞよ"}, {u8"頼むぞよ"}},
        {{u8"頼み申す", u8"頼むでござる"}, {u8"お頼み申し上げます"}},
        {{u8"頼むッス"}, {u8"おねがいにゃ", u8"おねがいニャン"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _ore(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"私"}, {u8"私"}},
        {{u8"俺"}, {u8"あたし"}},
        {{u8"僕"}, {u8"わたし"}},
        {{u8"自分"}, {u8"自分"}},
        {{u8"麻呂"}, {u8"わらわ"}},
        {{u8"拙者"}, {u8"手前"}},
        {{u8"あっし"}, {u8"みゅー"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _ga(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ですが", u8"ですけど"}, {u8"ですが", u8"ですけど"}},
        {{u8"が", u8"がな"}, {u8"が"}},
        {{u8"けど", u8"が"}, {u8"が", u8"けど"}},
        {{u8"が…", u8"けど…"}, {u8"が…", u8"けど…"}},
        {{u8"であるが"}, {u8"であるが"}},
        {{u8"でござるが"}, {u8"でございますが"}},
        {{u8"ッスけど", u8"ッスが"}, {u8"ニャけど", u8"にゃが"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _dana(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ですね"}, {u8"ですわね", u8"ですね"}},
        {{u8"だな"}, {u8"だね", u8"ね"}},
        {{u8"だね"}, {u8"ね"}},
        {{u8"だな…"}, {u8"だね…", u8"ね…"}},
        {{u8"であるな"}, {u8"であるな"}},
        {{u8"でござるな"}, {u8"でございますね"}},
        {{u8"ッスね"}, {u8"にゃ", u8"みゃ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _kure(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ください", u8"くださいよ"}, {u8"くださいな", u8"ください"}},
        {{u8"くれ", u8"くれよ"}, {u8"くれ", u8"よ"}},
        {{u8"ね", u8"よ"}, {u8"ね", u8"ね"}},
        {{u8"くれ…", u8"…"}, {u8"よ…", u8"…"}},
        {{u8"つかわせ", u8"たもれ"}, {u8"つかわせ", u8"たもれ"}},
        {{u8"頂きたいでござる"}, {u8"くださいませ"}},
        {{u8"くれッス"}, {u8"にゃ", u8"みゃ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _daro(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"でしょう"}, {u8"でしょう"}},
        {{u8"だろ"}, {u8"だろうね"}},
        {{u8"だろうね"}, {u8"でしょ"}},
        {{u8"だろ…"}, {u8"でしょ…"}},
        {{u8"であろう"}, {u8"であろうな"}},
        {{u8"でござろうな"}, {u8"でございましょう"}},
        {{u8"ッスね"}, {u8"にゃ", u8"みゃ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _yo(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ですよ", u8"です"}, {u8"ですよ", u8"です"}},
        {{u8"ぜ", u8"ぞ"}, {u8"わ", u8"よ"}},
        {{u8"よ", u8"ぞ"}, {u8"わよ", u8"わ"}},
        {{u8"…", u8"ぞ…"}, {u8"わ…", u8"…"}},
        {{u8"であろう", u8"でおじゃる"}, {u8"であろうぞ", u8"でおじゃる"}},
        {{u8"でござろう"}, {u8"でございますわ"}},
        {{u8"ッスよ", u8"ッス"}, {u8"にゃぁ", u8"みゃぁ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _aru(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"あります", u8"ありますね"}, {u8"あります", u8"ありますわ"}},
        {{u8"ある", u8"あるな"}, {u8"あるね", u8"あるよ"}},
        {{u8"あるね", u8"あるよ"}, {u8"あるわ", u8"あるわね"}},
        {{u8"ある…", u8"あるぞ…"}, {u8"あるわ…"}},
        {{u8"あろう", u8"おじゃる"}, {u8"あろう", u8"おじゃる"}},
        {{u8"あるでござる", u8"あるでござるな"}, {u8"ござます"}},
        {{u8"あるッスよ", u8"あるッス"}, {u8"あにゅ", u8"あみぅ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _u(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"います", u8"いますよ"}, {u8"いますわ", u8"います"}},
        {{u8"うぜ", u8"うぞ"}, {u8"うわ", u8"うよ"}},
        {{u8"うよ", u8"う"}, {u8"うわ", u8"う"}},
        {{u8"う…", u8"うぞ…"}, {u8"うわ…", u8"う…"}},
        {{u8"うぞよ", u8"うぞ"}, {u8"うぞよ", u8"うぞ"}},
        {{u8"うでござる", u8"うでござるよ"}, {u8"うでございます"}},
        {{u8"うッスよ", u8"うッス"}, {u8"うにぁ", u8"うみぁ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _na(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ですね", u8"です"}, {u8"ですわ", u8"ですね"}},
        {{u8"ぜ", u8"な"}, {u8"ね", u8"な"}},
        {{u8"ね", u8"なぁ"}, {u8"わ", u8"わね"}},
        {{u8"…", u8"な…"}, {u8"…", u8"わ…"}},
        {{u8"でおじゃるな", u8"のう"}, {u8"でおじゃるな", u8"のう"}},
        {{u8"でござるな"}, {u8"でございますわ"}},
        {{u8"ッスね", u8"ッス"}, {u8"ニァ", u8"ミァ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string _ta(int mark)
{
    std::vector<std::string> candidates[][2] = {
        {{u8"ました", u8"ましたね"}, {u8"ました", u8"ましたわ"}},
        {{u8"た", u8"たな"}, {u8"たね", u8"たよ"}},
        {{u8"たね", u8"たよ"}, {u8"たよ", u8"たね"}},
        {{u8"た…", u8"たぞ…"}, {u8"たわ…"}},
        {{u8"たぞよ", u8"たぞな"}, {u8"たぞよ"}},
        {{u8"たでござる"}, {u8"ましてございます"}},
        {{u8"たッスよ", u8"たッス"}, {u8"たにゃぁ", u8"たみゃぁ"}},
    };
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex]) +
        i18n::s.get_enum("core.locale.ui.mark", mark);
}



std::string replace_tag(const std::string source)
{
    if (source == u8"ref"s && talkref == 1)
    {
        return i18n::s.get(
            "core.locale.talk.tag.ref", game_data.number_of_waiting_guests);
    }
    if (source == u8"you"s)
    {
        return _kimi(3);
    }
    if (source == u8"sex"s)
    {
        return i18n::s.get_enum("core.locale.ui.sex2", 0);
    }
    if (source == u8"player"s)
    {
        return cdatan(0, 0);
    }
    if (source == u8"aka"s)
    {
        return cdatan(1, 0);
    }
    if (source == u8"npc"s)
    {
        return cdatan(0, tc);
    }
    if (source == u8"ある"s)
    {
        return _aru(3);
    }
    if (source == u8"が"s)
    {
        return _ga(3);
    }
    if (source == u8"か"s)
    {
        return _ka(3);
    }
    if (source == u8"かな"s)
    {
        return _kana(3);
    }
    if (source == u8"だ"s)
    {
        return _da(3);
    }
    if (source == u8"よ"s)
    {
        return _yo(3);
    }
    if (source == u8"だな"s)
    {
        return _dana(3);
    }
    if (source == u8"だろ"s)
    {
        return _daro(3);
    }
    if (source == u8"る"s)
    {
        return _ru(3);
    }
    if (source == u8"のだ"s)
    {
        return _nda(3);
    }
    if (source == u8"な"s)
    {
        return _na(3);
    }
    if (source == u8"くれ"s)
    {
        return _kure(3);
    }
    return u8"Unknown Code"s;
}



void parse_talk_file()
{
    buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    if (noteinfo() <= 1)
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"talk.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
        p = instr(
            buff, 0, u8"%DEFAULT,"s + i18n::s.get("core.locale.meta.tag"));
        buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    }
    notedel(0);
    p = rnd(noteinfo());
    noteget(s, p);
    buff = s;
    text_replace_tags_in_quest_board();
}



void read_talk_file(const std::string& valn)
{
    buff = "";
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"talk.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = instr(buff, 0, valn + u8","s + i18n::s.get("core.locale.meta.tag"));
    parse_talk_file();
}



void get_npc_talk()
{
    buff = "";
    notesel(buff);
    {
        buff(0).clear();
        std::ifstream in{(filesystem::dir::data() / u8"talk.txt").native(),
                         std::ios::binary};
        std::string tmp;
        while (std::getline(in, tmp))
        {
            buff(0) += tmp + '\n';
        }
    }
    p = -1;
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        if (cdata[tc].character_role == 18)
        {
            if (game_data.number_of_waiting_guests > 0)
            {
                talkref = 1;
                p = instr(
                    buff, 0, u8"%MAID,"s + i18n::s.get("core.locale.meta.tag"));
                break;
            }
        }
        if (cdata[tc].interest <= 0)
        {
            p = instr(
                buff, 0, u8"%BORED,"s + i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if (tc < 16)
        {
            p = instr(
                buff,
                0,
                u8"%ALLY_DEFAULT,"s + i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if (cdata[tc].id == 335)
        {
            p = instr(
                buff, 0, u8"%BITCH,"s + i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if (cdata[tc].character_role == 1015)
        {
            p = instr(
                buff, 0, u8"%MOYER,"s + i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if (cdata[tc].character_role == 17)
        {
            p = instr(
                buff,
                0,
                u8"%SLAVEKEEPER,"s + i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if ((cdata[tc].character_role >= 1000 &&
             cdata[tc].character_role < 2000) ||
            cdata[tc].character_role == 2003)
        {
            if (rnd(3))
            {
                p = instr(
                    buff,
                    0,
                    u8"%SHOPKEEPER,"s + i18n::s.get("core.locale.meta.tag"));
                break;
            }
        }
        if (cdata[tc].impression >= 100)
        {
            if (rnd(3) == 0)
            {
                p = instr(
                    buff,
                    0,
                    u8"%RUMOR,LOOT,"s + i18n::s.get("core.locale.meta.tag"));
                break;
            }
        }
        if (area_data[game_data.current_map].christmas_festival)
        {
            if (game_data.current_map == mdata_t::MapId::noyel)
            {
                if (rnd(3))
                {
                    p = instr(
                        buff,
                        0,
                        u8"%FEST,"s + game_data.current_map + u8","s +
                            i18n::s.get("core.locale.meta.tag"));
                    break;
                }
            }
        }
        if (rnd(2))
        {
            p = instr(
                buff,
                0,
                u8"%PERSONALITY,"s + cdata[tc].personality + u8","s +
                    i18n::s.get("core.locale.meta.tag"));
            break;
        }
        if (rnd(3))
        {
            p = instr(
                buff,
                0,
                u8"%AREA,"s + game_data.current_map + u8","s +
                    i18n::s.get("core.locale.meta.tag"));
            break;
        }
    }
    if (p == -1)
    {
        p = instr(
            buff, 0, u8"%DEFAULT,"s + i18n::s.get("core.locale.meta.tag"));
    }
    parse_talk_file();
}



std::string cnvweight(int weight)
{
    return ""s + std::abs(weight) / 1000 + '.' + std::abs(weight) % 1000 / 100 +
        i18n::s.get("core.locale.ui.unit_of_weight");
}



std::string fltname(int category)
{
    if (auto text =
            i18n::s.get_enum_optional("core.locale.item.filter_name", category))
    {
        return *text;
    }
    else
    {
        return i18n::s.get("core.locale.item.filter_name.default");
    }
}



void quest_update_main_quest_journal()
{
    int progress;

    noteadd("@QM[" + i18n::s.get("core.locale.quest.journal.main.title") + "]");
    if (game_data.quest_flags.main_quest >= 0 &&
        game_data.quest_flags.main_quest < 30)
    {
        progress = 0;
    }
    if (game_data.quest_flags.main_quest >= 30 &&
        game_data.quest_flags.main_quest < 50)
    {
        progress = 1;
    }
    if (game_data.quest_flags.main_quest >= 50 &&
        game_data.quest_flags.main_quest < 60)
    {
        progress = 2;
    }
    if (game_data.quest_flags.main_quest >= 60 &&
        game_data.quest_flags.main_quest < 100)
    {
        progress = 3;
    }
    if (game_data.quest_flags.main_quest >= 100 &&
        game_data.quest_flags.main_quest < 110)
    {
        progress = 4;
    }
    if (game_data.quest_flags.main_quest >= 110 &&
        game_data.quest_flags.main_quest < 125)
    {
        progress = 5;
    }
    if (game_data.quest_flags.main_quest >= 125 &&
        game_data.quest_flags.main_quest < 180)
    {
        progress = 6;
    }
    if (game_data.quest_flags.main_quest >= 180 &&
        game_data.quest_flags.main_quest < 1000)
    {
        progress = 7;
    }
    s1 = i18n::s.get_enum("core.locale.quest.journal.main.progress", progress);
    talk_conv(s1, 40 - en * 4);
    buff += s1;
    noteadd(""s);
}



void append_subquest_journal(int val0)
{
    if (val0 == 0)
    {
        noteadd(""s);
        noteadd(
            "@QM[" + i18n::s.get("core.locale.quest.journal.sub.title") + "]");
    }
    p = 0;
    if (game_data.quest_flags.putit_attacks != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.putit_attacks.title");
        p = game_data.quest_flags.putit_attacks;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.putit_attacks.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.putit_attacks.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.thieves_hideout != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.thieves_hideout.title");
        p = game_data.quest_flags.thieves_hideout;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.thieves_hideout.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.thieves_hideout.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.puppys_cave != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.puppys_cave.title");
        p = game_data.quest_flags.puppys_cave;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.puppys_cave.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.nightmare != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.nightmare.title");
        p = game_data.quest_flags.nightmare;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.nightmare.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.nightmare.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.nightmare.progress", 2);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.pael_and_her_mom != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.pael_and_her_mom.title");
        p = game_data.quest_flags.pael_and_her_mom;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 4)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 5)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 6)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 7)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 8)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 9)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 10)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pael_and_her_mom.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.wife_collector != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.wife_collector.title");
        p = game_data.quest_flags.wife_collector;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.wife_collector.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.cat_house != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.cat_house.title");
        p = game_data.quest_flags.cat_house;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.cat_house.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.cat_house.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.defense_line != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.defense_line.title");
        p = game_data.quest_flags.defense_line;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.defense_line.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.defense_line.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.defense_line.progress", 2);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.novice_knight != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.novice_knight.title");
        p = game_data.quest_flags.novice_knight;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.novice_knight.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.novice_knight.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.kamikaze_attack != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.kamikaze_attack.title");
        p = game_data.quest_flags.kamikaze_attack;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.kamikaze_attack.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.kamikaze_attack.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.kamikaze_attack.progress", 2);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.mias_dream != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.mias_dream.title");
        p = game_data.quest_flags.mias_dream;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.mias_dream.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.rare_books != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.rare_books.title");
        p = game_data.quest_flags.rare_books;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.rare_books.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.pyramid_trial != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.pyramid_trial.title");
        p = game_data.quest_flags.pyramid_trial;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.pyramid_trial.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.red_blossom_in_palmia != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.red_blossom_in_palmia.title");
        p = game_data.quest_flags.red_blossom_in_palmia;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.red_blossom_in_palmia.progress",
                0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.red_blossom_in_palmia.progress",
                1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.ambitious_scientist != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.ambitious_scientist.title");
        p = game_data.quest_flags.ambitious_scientist;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p ==
            game_data.quest_flags.ambitious_scientist *
                    (game_data.quest_flags.ambitious_scientist < 6) +
                (game_data.quest_flags.ambitious_scientist == 0))
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.ambitious_scientist.progress",
                0,
                (6 - game_data.quest_flags.ambitious_scientist));
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.sewer_sweeping != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.sewer_sweeping.title");
        p = game_data.quest_flags.sewer_sweeping;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.sewer_sweeping.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.sewer_sweeping.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.joining_mages_guild != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.joining_mages_guild.title");
        p = game_data.guild.joining_mages_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.joining_mages_guild.progress",
                0,
                game_data.guild.mages_guild_quota);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.joining_thieves_guild != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.joining_thieves_guild.title");
        p = game_data.guild.joining_thieves_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.joining_thieves_guild.progress",
                0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.joining_fighters_guild != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.joining_fighters_guild.title");
        p = game_data.guild.joining_fighters_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.joining_fighters_guild.progress",
                0,
                game_data.guild.fighters_guild_quota,
                chara_refstr(game_data.guild.fighters_guild_target, 2));
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.mages_guild_quota_recurring != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.quota_mages_guild.title");
        p = game_data.guild.mages_guild_quota_recurring;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.quota_mages_guild.progress",
                0,
                game_data.guild.mages_guild_quota);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.fighters_guild_quota_recurring != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.quota_fighters_guild.title");
        p = game_data.guild.fighters_guild_quota_recurring;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.quota_fighters_guild.progress",
                0,
                game_data.guild.fighters_guild_quota,
                chara_refstr(game_data.guild.fighters_guild_target, 2));
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.guild.thieves_guild_quota_recurring != 0)
    {
        s = i18n::s.get(
            "core.locale.quest.journal.sub.quota_thieves_guild.title");
        p = game_data.guild.thieves_guild_quota_recurring;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.quota_thieves_guild.progress",
                0,
                game_data.guild.thieves_guild_quota);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.minotaur_king != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.minotaur_king.title");
        p = game_data.quest_flags.minotaur_king;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.minotaur_king.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.minotaur_king.progress", 1);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (game_data.quest_flags.little_sister != 0)
    {
        s = i18n::s.get("core.locale.quest.journal.sub.little_sister.title");
        p = game_data.quest_flags.little_sister;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(
                    "[" + i18n::s.get("core.locale.quest.journal.sub.done") +
                    "]" + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = i18n::s.get_enum(
                "core.locale.quest.journal.sub.little_sister.progress", 0);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
}



void append_quest_item_journal()
{
    noteadd(
        "[" + i18n::s.get("core.locale.quest.journal.item.old_talisman") + "]");
    if (game_data.quest_flags.main_quest >= 30)
    {
        noteadd(
            "[" +
            i18n::s.get("core.locale.quest.journal.item.letter_to_the_king") +
            "]");
    }
    if (game_data.quest_flags.magic_stone_of_fool != 0)
    {
        noteadd(
            "[" +
            i18n::s.get("core.locale.quest.journal.item.fools_magic_stone") +
            "]");
    }
    if (game_data.quest_flags.magic_stone_of_king != 0)
    {
        noteadd(
            "[" +
            i18n::s.get("core.locale.quest.journal.item.kings_magic_stone") +
            "]");
    }
    if (game_data.quest_flags.magic_stone_of_sage != 0)
    {
        noteadd(
            "[" +
            i18n::s.get("core.locale.quest.journal.item.sages_magic_stone") +
            "]");
    }
}



void parse_quest_board_text(int val0)
{
    elona_vector1<std::string> buff2;
    notesel(buffboard);
    SDIM1(buff2);
    p = instr(buffboard, 0, s + u8","s + i18n::s.get("core.locale.meta.tag"));
    buff2 = strmid(buffboard, p, instr(buffboard, p, u8"%END"s));
    notesel(buff2);
    if (noteinfo() <= 1)
    {
        buff2 = u8"no txt"s;
        return;
    }
    p = rnd(noteinfo() - 1) + 1;
    noteget(buff2, p);
    p = instr(buff2, 0, u8":"s);
    s(3) = strmid(buff2, 0, p);
    if (val0 == 2)
    {
        notesel(buff);
        return;
    }
    buff2 = strmid(buff2, p + 1, buff2(0).size() - p - 1);
    if (val0 != 2)
    {
        buff = buff2;
    }
}



std::string randomname()
{
    std::string ret;

    while (1)
    {
        ret = choice(rn1);
        if (ret.empty())
        {
            continue;
        }
        if (jp)
        {
            if (rnd(8) == 0)
            {
                ret += u8"ー";
            }
        }
        if (rnd(5))
        {
            ret += choice(rn2);
        }
        const auto length = ret.size();
        if (length < 4)
        {
            continue;
        }
        if (length < 6)
        {
            if (rnd(3))
            {
                continue;
            }
        }
        if (length < 8)
        {
            if (rnd(2))
            {
                continue;
            }
        }
        if (jp)
        {
            if (strutil::starts_with(ret, u8"ー") ||
                strutil::contains(ret, u8"ーッ"))
            {
                continue;
            }
        }
        break;
    }

    return cnven(ret);
}



std::string random_title(int prm_439)
{
    std::string ret;

    elona_vector1<std::string> randn2_at_m41;
    int rtval_at_m41 = 0;
redo:
    for (int cnt = 0; cnt < 1; ++cnt)
    {
        p_at_m41(2) = rnd(rnlist.j_size());
        p_at_m41(1) = rnd(14);
        if (rnlist(p_at_m41(1), p_at_m41(2)) == ""s)
        {
            --cnt;
            continue;
        }
    }

    if (prm_439 == 1 || prm_439 == 3)
    {
        if (rnlist(14, p_at_m41(2)) == u8"具"s)
        {
            goto redo;
        }
    }
    randn2_at_m41(0) = rnlist(p_at_m41(1), p_at_m41(2));
    randn2_at_m41(1) = rnlist(14, p_at_m41(2));
    rtval_at_m41 = -1;
    if (jp)
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (p_at_m41(1) == 10 || p_at_m41(1) == 11)
            {
                if (rnd(5) == 0)
                {
                    p_at_m41(1) = 0;
                    p_at_m41(3) = rnd(2);
                    if (p_at_m41(3) == 0)
                    {
                        randn2_at_m41 += u8"の"s;
                    }
                    break;
                }
                p_at_m41 = rnd(5);
                if (p_at_m41 == 0)
                {
                    randn2_at_m41 += u8"・オブ・"s;
                }
                if (p_at_m41 == 1)
                {
                    randn2_at_m41 = u8"ザ・"s + randn2_at_m41;
                    rtval_at_m41 = 1;
                    break;
                }
                if (p_at_m41 == 2)
                {
                    randn2_at_m41 += u8"・"s;
                }
            }
            if (p_at_m41(1) == 0 || p_at_m41(1) == 1)
            {
                randn2_at_m41 += u8"の"s;
                p_at_m41(3) = rnd(10);
                if (p_at_m41(3) == 0)
                {
                    p_at_m41(1) = 10;
                }
            }
        }
    }
    else
    {
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (p_at_m41(1) == 0 || p_at_m41(1) == 1)
            {
                if (rnd(6) == 0)
                {
                    randn2_at_m41 += u8" of"s;
                }
                else if (rnd(6) == 0)
                {
                    randn2_at_m41 = u8"the "s + randn2_at_m41;
                    rtval_at_m41 = 1;
                    break;
                }
            }
            randn2_at_m41 += u8" "s;
        }
        randn2_at_m41 = cnven(randn2_at_m41);
    }

    if (rtval_at_m41 == 1)
    {
        ret = randn2_at_m41;
        goto skip;
    }

    rtval_at_m41 = -1;

    for (int cnt = 0; cnt < 100; ++cnt)
    {
        p_at_m41(4) = rnd(rnlist.j_size());
        if (p_at_m41(4) == p_at_m41(2))
        {
            continue;
        }
        if (rnlist(14, p_at_m41(4)) == randn2_at_m41(1))
        {
            if (rnlist(14, p_at_m41(4)) != u8"万能"s)
            {
                if (randn2_at_m41(1) != u8"万能"s)
                {
                    continue;
                }
            }
        }
        if (p_at_m41(1) < 10)
        {
            p_at_m41(1) = rnd(2);
        }
        else
        {
            p_at_m41(1) = rnd(2);
            p_at_m41(1) += 10;
        }
        if (rnlist(p_at_m41(1), p_at_m41(4)) == ""s)
        {
            continue;
        }
        rtval_at_m41 = 1;
        break;
    }
    if (rtval_at_m41 == -1)
    {
        goto redo;
    }
    if (en)
    {
        rnlist(p_at_m41(1), p_at_m41(4)) =
            cnven(rnlist(p_at_m41(1), p_at_m41(4)));
    }
    randn2_at_m41 += rnlist(p_at_m41(1), p_at_m41(4));
    ret = randn2_at_m41;
    if (strlen_u(ret) >= 28)
    {
        goto redo;
    }

skip:

    if (prm_439 == 2)
    {
        if (jp)
        {
            if (rnd(5))
            {
                ret += choice(std::initializer_list<const char*>{
                    u8"団",
                    u8"チーム",
                    u8"パーティー",
                    u8"の集い",
                    u8"の軍",
                    u8"アーミー",
                    u8"隊",
                    u8"の一家",
                    u8"軍",
                    u8"の隊",
                    u8"の団",
                });
            }
        }
        else if (rnd(2))
        {
            ret = choice(std::initializer_list<const char*>{
                      u8"The army of ",
                      u8"The party of ",
                      u8"The house of ",
                      u8"Clan ",
                  }) +
                ret;
        }
        else
        {
            ret += choice(std::initializer_list<const char*>{
                u8" Clan",
                u8" Party",
                u8" Band",
                u8" Gangs",
                u8" Gathering",
                u8" House",
                u8" Army",
            });
        }
    }

    return ret;
}



std::string cheer_up_message(int hours)
{
    auto message =
        i18n::s.get_enum_optional("core.locale.ui.cheer_up_message", hours);

    if (message)
    {
        return *message;
    }

    return "";
}

void text_replace_tags_in_quest_board()
{
    while (1)
    {
        const int p0 = instr(buff, 0, u8"{"s);
        const int p1 = instr(buff, p0, u8"}"s);
        const int p2 = buff(0).size();
        if (p0 == -1)
        {
            break;
        }
        const auto tag = strmid(buff, p0 + 1, p1 - 1);
        const auto head = strmid(buff, 0, p0);
        const auto tail = strmid(buff, p0 + p1 + 1, p2 - p1 - p0);
        buff = head + replace_tag(tag) + tail;
    }
}

void text_replace_tags_in_quest_text()
{
    for (int cnt = 0; cnt < 20; ++cnt)
    {
        p(0) = instr(buff, 0, u8"{"s);
        p(1) = instr(buff, p, u8"}"s);
        p(2) = buff(0).size();
        if (p == -1)
        {
            break;
        }
        s(0) = strmid(buff, p + 1, p(1) - 1);
        s(1) = strmid(buff, 0, p);
        s(2) = strmid(buff, p + p(1) + 1, p(2) - p(1) - p);
        for (int cnt = 0; cnt < 1; ++cnt)
        {
            if (s == u8"client"s)
            {
                s = s(12);
                break;
            }
            if (s == u8"map"s)
            {
                s = s(11);
                break;
            }
            if (s == u8"ref"s)
            {
                s = s(10);
                break;
            }
            if (s == u8"you"s)
            {
                s = _kimi(3);
                break;
            }
            if (s == u8"me"s)
            {
                s = _ore(3);
                break;
            }
            if (s == u8"reward"s)
            {
                s = s(5);
                break;
            }
            if (s == u8"objective"s)
            {
                s = s(4);
                break;
            }
            if (s == u8"deadline"s)
            {
                s = nquestdate;
                break;
            }
            if (s == u8"player"s)
            {
                s = cdatan(0, 0);
                break;
            }
            if (s == u8"aka"s)
            {
                s = cdatan(1, 0);
                break;
            }
            if (s == u8"npc"s)
            {
                s = cdatan(0, tc);
                break;
            }
            if (s == u8"ある"s)
            {
                s = _aru(3);
                break;
            }
            if (s == u8"う"s)
            {
                s = _u(3);
                break;
            }
            if (s == u8"か"s)
            {
                s = _ka(3);
                break;
            }
            if (s == u8"が"s)
            {
                s = _ga(3);
                break;
            }
            if (s == u8"かな"s)
            {
                s = _kana(3);
                break;
            }
            if (s == u8"だ"s)
            {
                s = _da(3);
                break;
            }
            if (s == u8"よ"s)
            {
                s = _yo(3);
                break;
            }
            if (s == u8"た"s)
            {
                s = _ta(3);
                break;
            }
            if (s == u8"だな"s)
            {
                s = _dana(3);
                break;
            }
            if (s == u8"だろ"s)
            {
                s = _daro(3);
                break;
            }
            if (s == u8"たのむ"s)
            {
                s = _tanomu(3);
                break;
            }
            if (s == u8"る"s)
            {
                s = _ru(3);
                break;
            }
            if (s == u8"のだ"s)
            {
                s = _nda(3);
                break;
            }
            if (s == u8"な"s)
            {
                s = _na(3);
                break;
            }
            if (s == u8"くれ"s)
            {
                s = _kure(3);
                break;
            }
            s = u8"Unknown Code"s;
        }
        buff = s(1) + s + s(2);
    }
}



std::string name(int cc)
{
    if (cc == 0)
    {
        return i18n::s.get("core.locale.chara.you");
    }
    if (is_in_fov(cdata[cc]) == 0)
    {
        return i18n::s.get("core.locale.chara.something");
    }
    if (cdata.player().blind != 0 ||
        (cdata[cc].is_invisible() == 1 &&
         cdata.player().can_see_invisible() == 0 && cdata[cc].wet == 0))
    {
        return i18n::s.get("core.locale.chara.something");
    }
    if (en)
    {
        const char first = cdatan(0, cc)[0];
        if (first == '\"' || first == '<')
        {
            return cdatan(0, cc);
        }
        if (cdata[cc].has_own_name() == 0)
        {
            return u8"the "s + cdatan(0, cc);
        }
    }
    return cdatan(0, cc);
}

} // namespace elona
