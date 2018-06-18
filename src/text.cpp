#include "character.hpp"
#include "elona.hpp"
#include "enchantment.hpp"
#include "i18n.hpp"
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
    return lang(str, '[' + str + ']');
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
    if (jp)
    {
        ret = ""s + year + u8"年"s + month + u8"月"s + day + u8"日"s;
        if (show_hour)
        {
            ret += std::to_string(hour) + u8"時";
        }
    }
    else
    {
        ret = ""s + year + u8" "s + month + u8"/"s + day + u8" "s;
        if (show_hour)
        {
            ret += std::to_string(hour) + u8"h";
        }
    }

    return ret;
}



std::string cnvplaytime(int datetime_id)
{
    const int h = datetime_id / 60 / 60;
    const int m = datetime_id / 60 % 60;
    const int s = datetime_id % 60;
    return lang(
        std::to_string(h) + u8"時間" + m + u8"分" + s + u8"秒",
        std::to_string(h) + u8":" + m + u8":" + s + u8" Sec");
}



// Get rid of the job and extract the name.
// Lomias the general vendor => Lomias
std::string sncnv(const std::string& name_with_job)
{
    return name_with_job.substr(0, name_with_job.find(' ')) + ' ';
}



std::string sngeneral(const std::string& name)
{
    return lang(u8"雑貨屋の"s + name, sncnv(name) + u8"the general vendor"s);
}



std::string sninn(const std::string& name)
{
    return lang(u8"宿屋の"s + name, sncnv(name) + u8"the Innkeeper"s);
}



std::string sntrade(const std::string& name)
{
    return lang(u8"交易店の"s + name, sncnv(name) + u8"the trader"s);
}



std::string sngoods(const std::string& name)
{
    return lang(u8"何でも屋の"s + name, sncnv(name) + u8"the goods vendor"s);
}



std::string snbakery(const std::string& name)
{
    return lang(u8"パン屋の"s + name, sncnv(name) + u8"the baker"s);
}



std::string snmagic(const std::string& name)
{
    return lang(u8"魔法店の"s + name, sncnv(name) + u8"the magic vendor"s);
}



std::string snarmor(const std::string& name)
{
    return lang(u8"武具店の"s + name, sncnv(name) + u8"the blacksmith"s);
}



std::string sntrainer(const std::string& name)
{
    return lang(u8"ギルドの"s + name, sncnv(name) + u8"the trainer"s);
}



std::string snfish(const std::string& name)
{
    return lang(u8"釣具店の"s + name, sncnv(name) + u8"the fisher"s);
}



std::string snblack(const std::string& name)
{
    return lang(
        u8"ブラックマーケットの"s + name,
        sncnv(name) + u8"the blackmarket vendor"s);
}



std::string snfood(const std::string& name)
{
    return lang(u8"食品店"s + name, sncnv(name) + u8"the food vendor"s);
}



void txtsetlastword()
{
    std::vector<std::string> last_words;
    range::copy(
        fileutil::read_by_line{filesystem::dir::user()
                               / lang(u8"lastwords.txt", u8"lastwords-e.txt")},
        std::back_inserter(last_words));
    lastword = choice(last_words);
}



std::vector<std::string> txtsetwinword(int n)
{
    std::vector<std::string> ret;
    sample(
        std::vector<std::string>{
            lang(u8"遂に…！", u8"Finally!"),
            lang(u8"当然の結果だ", u8"It's a matter of course."),
            lang(u8"おぉぉぉぉ！", u8"Woooooo!"),
            lang(u8"ふっ", u8"Heh."),
            lang(u8"今日は眠れないな", u8"I can't sleep tonight."),
            lang(u8"またそんな冗談を", u8"You're kidding."),
        },
        std::back_inserter(ret),
        n);
    return ret;
}



void initialize_nefia_names()
{
    SDIM4(mapnamerd, 20, 2, 5);
    mapnamerd(0, 0) = lang(u8"はじまりの"s, u8"Beginner's "s);
    mapnamerd(1, 0) = lang(u8"安全な"s, u8"Safe "s);
    mapnamerd(0, 1) = lang(u8"冒険者の"s, u8"Adventurer's"s);
    mapnamerd(1, 1) = lang(u8"時めきの"s, u8"Exciting "s);
    mapnamerd(0, 2) = lang(u8"迷いの"s, u8"Dangerous "s);
    mapnamerd(1, 2) = lang(u8"勇者の"s, u8"Servant's "s);
    mapnamerd(0, 3) = lang(u8"死の"s, u8"Fearful "s);
    mapnamerd(1, 3) = lang(u8"闇の"s, u8"Shadow "s);
    mapnamerd(0, 4) = lang(u8"不帰の"s, u8"King's "s);
    mapnamerd(1, 4) = lang(u8"混沌の"s, u8"Chaotic "s);
    return;
}



std::string maplevel(int)
{
    if (gdata_current_map == 7)
    {
        if (gdata_current_dungeon_level != 1)
        {
            if (gdata_current_dungeon_level > 0)
            {
                return u8"B."s + (gdata_current_dungeon_level - 1);
            }
            else
            {
                return u8"L."s + (gdata_current_dungeon_level - 2) * -1;
            }
        }
    }
    if (adata(0, gdata_current_map) != 3)
    {
        if (adata(16, gdata_current_map) == 3
            || adata(16, gdata_current_map) == 8
            || adata(16, gdata_current_map) == 13
            || (mdata(6) >= 20 && mdata(6) <= 23) == 1)
        {
            return ""s
                + cnvrank(
                       (gdata_current_dungeon_level
                        - adata(17, gdata_current_map) + 1))
                + lang(u8"層"s, ""s);
        }
    }
    return "";
}


std::string mapname_dungeon(int id)
{
    int suffix_id = adata(0, id);
    std::string name = mapnamerd(
        adata(5, id), std::min(adata(17, id) / 5, int(length2(mapnamerd) - 1)));

    if (suffix_id >= 20 && suffix_id <= 23)
    {
        name += i18n::s.get_enum("core.locale.map.dungeon", suffix_id);
    }
    return name;
}

std::string mapname(int id, bool description)
{
    std::string name;
    std::string desc;

    switch (adata(16, id))
    {
    case 13:
        if (gdata_executing_immediate_quest_type == 1001)
        {
            name = i18n::s.get("core.locale.map.quest.outskirts");
        }
        if (gdata_executing_immediate_quest_type == 1010
            || gdata_executing_immediate_quest_type == 1008)
        {
            name = i18n::s.get("core.locale.map.quest.urban_area");
        }
        break;
    case 8: name = mapname_dungeon(id); break;
    default:
        name = i18n::s.get_enum_property(
            "core.locale.map.unique", "name", adata(16, id));
        auto desc_opt = i18n::s.get_enum_property_opt(
            "core.locale.map.unique", "desc", adata(16, id));
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
        if (adata(16, id) == 29)
        {
            return "";
        }
        else if (desc != ""s)
        {
            return desc;
        }
        else if (adata(0, id) >= 20)
        {
            return i18n::s.get(
                "core.locale.map.you_see_an_entrance", name, adata(17, id));
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
    s_at_m32 = i18n::s.get("core.locale.map.you_see", bdrefn(p_at_m32));
    return s_at_m32;
}



std::string txtskillchange(int id, int cc, bool increase)
{
    switch (id)
    {
    case 2:
        if (increase)
        {
            return lang(
                name(cc) + u8"は生命力の上昇を感じた。"s,
                name(cc) + your(cc) + u8" life force increases."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は生命力の衰えを感じた。"s,
                name(cc) + your(cc) + u8" life force decreases."s);
        }
    case 3:
        if (increase)
        {
            return lang(
                name(cc) + u8"はマナの向上を感じた。"s,
                name(cc) + your(cc) + u8" mana increases."s);
        }
        else
        {
            return lang(
                name(cc) + u8"はマナの衰えを感じた。"s,
                name(cc) + your(cc) + u8" mana decreases."s);
        }
    case 10:
        if (increase)
        {
            return lang(
                name(cc) + u8"はより強くなった。"s,
                name(cc) + your(cc) + u8" muscles feel stronger."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は少し贅肉が増えたような気がした。"s,
                name(cc) + your(cc) + u8" muscles soften."s);
        }
    case 11:
        if (increase)
        {
            return lang(
                name(cc) + u8"は我慢することの快感を知った。"s,
                name(cc) + u8" begin"s + _s(cc)
                    + u8" to feel good when being hit hard."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は我慢ができなくなった。"s,
                name(cc) + u8" lose"s + _s(cc) + u8" patience."s);
        }
    case 12:
        if (increase)
        {
            return lang(
                name(cc) + u8"は器用になった。"s,
                name(cc) + u8" become"s + _s(cc) + u8" dexterous."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は不器用になった。"s,
                name(cc) + u8" become"s + _s(cc) + u8" clumsy."s);
        }
    case 13:
        if (increase)
        {
            return lang(
                name(cc) + u8"は世界をより身近に感じるようになった。"s,
                name(cc) + u8" feel"s + _s(cc)
                    + u8" more in touch with the world."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は感覚のずれを感じた。"s,
                name(cc) + u8" "s + is(cc)
                    + u8" getting out of touch with the world"s);
        }
    case 14:
        if (increase)
        {
            return lang(
                name(cc) + u8"は急に色々なことを学びたくなった。"s,
                name(cc) + u8" feel"s + _s(cc) + u8" studious."s);
        }
        else
        {
            return lang(
                name(cc) + u8"の学習意欲が低下した。"s,
                name(cc) + u8" lose"s + _s(cc) + u8" curiosity."s);
        }
    case 15:
        if (increase)
        {
            return lang(
                name(cc) + u8"の意思は固くなった。"s,
                name(cc) + your(cc) + u8" will hardens."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は何でもすぐ諦める。"s,
                name(cc) + your(cc) + u8" will softens."s);
        }
    case 16:
        if (increase)
        {
            return lang(
                name(cc) + u8"は魔力の上昇を感じた。"s,
                name(cc) + your(cc) + u8" magic improves."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は魔力の衰えを感じた。"s,
                name(cc) + your(cc) + u8" magic degrades."s);
        }
    case 17:
        if (increase)
        {
            return lang(
                name(cc) + u8"は周囲の視線を心地よく感じる。"s,
                name(cc) + u8" enjoy"s + _s(cc) + u8" showing off "s + his(cc)
                    + u8" body."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は急に人前に出るのが嫌になった。"s,
                name(cc) + u8" start"s + _s(cc)
                    + u8" to avoid eyes of people."s);
        }
    case 18:
        if (increase)
        {
            return lang(
                name(cc) + u8"は周りの動きが遅く見えるようになった。"s,
                name(cc) + your(cc) + u8" speed increases."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は遅くなった。"s,
                name(cc) + your(cc) + u8" speed decreases."s);
        }
    case 19:
        if (increase)
        {
            return lang(
                name(cc) + u8"は幸運になった。"s,
                name(cc) + u8" become"s + _s(cc) + u8" lucky."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は不幸になった。"s,
                name(cc) + u8" become"s + _s(cc) + u8" unlucky."s);
        }
    default:
        if (increase)
        {
            return lang(
                name(cc) + u8"は"s
                    + i18n::_(u8"ability", std::to_string(id), u8"name")
                    + u8"の技術の向上を感じた。"s,
                name(cc) + your(cc) + u8" "s
                    + i18n::_(u8"ability", std::to_string(id), u8"name")
                    + u8" skill increases."s);
        }
        else
        {
            return lang(
                name(cc) + u8"は"s
                    + i18n::_(u8"ability", std::to_string(id), u8"name")
                    + u8"の技術の衰えを感じた。"s,
                name(cc) + your(cc) + u8" "s
                    + i18n::_(u8"ability", std::to_string(id), u8"name")
                    + u8" skill falls off."s);
        }
    }
}



std::string
foodname(int type, const std::string& ingredient_, int rank, int character_id)
{
    std::string ingredient = ingredient_;
    if (type == 1 || type == 8)
    {
        // Food created from character drops (meat and eggs)
        if (character_id == 0)
        {
            ingredient = i18n::s.get_enum_property("core.locale.food.names", type, "default_origin");
        }
        else
        {
            ingredient = chara_refstr(character_id, 2);
        }
    }
    else if (type == 5 || type == 7)
    {
        // Food that always always has a default origin (bread and noodles)
        ingredient = i18n::s.get_enum_property("core.locale.food.names", type, "default_origin");
    }
    else if (ingredient == ""s)
    {
        // No ingredient name was provided
        ingredient = i18n::s.get_enum_property("core.locale.food.names", type, "default_origin");
    }

    if (type < 1 || type > 8)
    {
        return ingredient;
    }
    else
    {
        return i18n::s.get_enum_property("core.locale.food.names",
                                         type,
                                         std::to_string(rank),
                                         ingredient);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
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
    return choice(candidates[cdata[tc].talk_type][cdata[tc].sex])
        + i18n::_(u8"ui", u8"mark", u8"_"s + mark);
}



std::string replace_tag(const std::string source)
{
    if (source == u8"ref"s && talkref == 1)
    {
        return lang(
            ""s + gdata_number_of_waiting_guests,
            ""s + gdata_number_of_waiting_guests + u8" guest"s
                + _s2(gdata_number_of_waiting_guests));
    }
    if (source == u8"you"s)
    {
        return _kimi(3);
    }
    if (source == u8"sex"s)
    {
        return i18n::_(u8"ui", u8"sex2", u8"_0");
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
        p = instr(buff, 0, u8"%DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
        buff = strmid(buff, p, instr(buff, p, u8"%END"s));
    }
    notedel(0);
    p = rnd(noteinfo());
    noteget(s, p);
    buff = s;
    text_replace_tags_in_quest_board();
    return;
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
    p = instr(buff, 0, valn + u8","s + lang(u8"JP"s, u8"EN"s));
    parse_talk_file();
    return;
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
            if (gdata_number_of_waiting_guests > 0)
            {
                talkref = 1;
                p = instr(buff, 0, u8"%MAID,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
        }
        if (cdata[tc].interest <= 0)
        {
            p = instr(buff, 0, u8"%BORED,"s + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if (tc < 16)
        {
            p = instr(buff, 0, u8"%ALLY_DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if (cdata[tc].id == 335)
        {
            p = instr(buff, 0, u8"%BITCH,"s + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if (cdata[tc].character_role == 1015)
        {
            p = instr(buff, 0, u8"%MOYER,"s + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if (cdata[tc].character_role == 17)
        {
            p = instr(buff, 0, u8"%SLAVEKEEPER,"s + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if ((cdata[tc].character_role >= 1000
             && cdata[tc].character_role < 2000)
            || cdata[tc].character_role == 2003)
        {
            if (rnd(3))
            {
                p = instr(buff, 0, u8"%SHOPKEEPER,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
        }
        if (cdata[tc].impression >= 100)
        {
            if (rnd(3) == 0)
            {
                p = instr(buff, 0, u8"%RUMOR,LOOT,"s + lang(u8"JP"s, u8"EN"s));
                break;
            }
        }
        if (adata(29, gdata_current_map))
        {
            if (gdata_current_map == 33)
            {
                if (rnd(3))
                {
                    p = instr(
                        buff,
                        0,
                        u8"%FEST,"s + gdata_current_map + u8","s
                            + lang(u8"JP"s, u8"EN"s));
                    break;
                }
            }
        }
        if (rnd(2))
        {
            p = instr(
                buff,
                0,
                u8"%PERSONALITY,"s + cdata[tc].personality + u8","s
                    + lang(u8"JP"s, u8"EN"s));
            break;
        }
        if (rnd(3))
        {
            p = instr(
                buff,
                0,
                u8"%AREA,"s + gdata_current_map + u8","s
                    + lang(u8"JP"s, u8"EN"s));
            break;
        }
    }
    if (p == -1)
    {
        p = instr(buff, 0, u8"%DEFAULT,"s + lang(u8"JP"s, u8"EN"s));
    }
    parse_talk_file();
    return;
}



std::string cnvweight(int weight)
{
    return ""s + std::abs(weight) / 1000 + '.' + std::abs(weight) % 1000 / 100
        + i18n::_(u8"ui", u8"unit_of_weight");
}



std::string fltname(int category)
{
    switch (category)
    {
    case 60001: return lang(u8"井戸", u8"well");
    case 57000: return lang(u8"食べ物", u8"food");
    case 56000: return lang(u8"杖", u8"rods");
    case 53000: return lang(u8"巻物", u8"scrolls");
    case 52000: return lang(u8"ポーション", u8"potions");
    case 64000: return lang(u8"ジャンク", u8"junks");
    case 77000: return lang(u8"鉱石", u8"ores");
    case 60000: return lang(u8"家具", u8"furniture");
    case 25000: return lang(u8"矢弾", u8"ammos");
    default: return lang(u8"不明", u8"Unknown");
    }
}



void quest_update_main_quest_journal()
{
    noteadd(lang(u8"@QM[メインクエスト]"s, u8"@QM[Main Quest]"s));
    if (gdata_main_quest_flag >= 0 && gdata_main_quest_flag < 30)
    {
        s1 = lang(
            u8"ヴェルニースの南にあるネフィアの迷宮群のひとつ《レシマス》で、何かが見つかるかもしれない。"s,
            u8"I should check the dungeon called Lesimas. It's located south of Vernis."s);
    }
    if (gdata_main_quest_flag >= 30 && gdata_main_quest_flag < 50)
    {
        s1 = lang(
            u8"致命傷を負った斥候に、パルミアのジャビ王へ書簡を渡すよう頼まれた。パルミアには、ヴェルニースから東の街道を進めば辿り着ける。"s,
            u8"The injured scout asked me to deliver a letter to the king of Palmia. Palmia is located east of Vernis."s);
    }
    if (gdata_main_quest_flag >= 50 && gdata_main_quest_flag < 60)
    {
        s1 = lang(
            u8"ジャビ王によると、仕事が欲しい時は城の図書館にいるエリステアを訪ねればいいようだ。"s,
            u8"Eristia will have some tasks for me if I want to work for Palmia. She's in the library of the castle."s);
    }
    if (gdata_main_quest_flag >= 60 && gdata_main_quest_flag < 100)
    {
        s1 = lang(
            u8"レシマスに赴き、冒険者カラムという人物を探すよう依頼された。彼は最低でもレシマスの16階より先の階層にいるらしい。"s,
            u8"Eristia asked to look for an adventurer called Karam in the dungeon of Lesimas. He was on the 16th level of the dungeon the last time he sent a report. I may have to go deeper if I am to find him."s);
    }
    if (gdata_main_quest_flag >= 100 && gdata_main_quest_flag < 110)
    {
        s1 = lang(
            u8"瀕死のカラムから得た情報を、パルミアのエリステアに伝えなければならない。"s,
            u8"I need to bring information Karam gave me to Eristia at once."s);
    }
    if (gdata_main_quest_flag >= 110 && gdata_main_quest_flag < 125)
    {
        s1 = lang(
            u8"レシマス最下層の封印を解く為に必要な三つの魔石の入手を依頼された。賢者の魔石は《灼熱の塔》に、愚者の魔石は《死者の洞窟》に、覇者の魔石は《古城》にある。"s,
            u8"I need to find 3 magic stones to break the seal of Lesimas. They can be found at the Tower of Fire, the crypt of the damned and the Ancient Castle"s);
    }
    if (gdata_main_quest_flag >= 125 && gdata_main_quest_flag < 180)
    {
        s1 = lang(
            u8"三つの魔石の力で最下層の封印を解き、レシマスの秘宝を持ち帰るようエリステアに依頼された。"s,
            u8"With 3 magic stones I have, I need to get to the deepest level of Lesimas and break the seal. Then bring back an item called Hidden Artifact of Lesimas, whatever it is."s);
    }
    if (gdata_main_quest_flag >= 180 && gdata_main_quest_flag < 1000)
    {
        s1 = lang(
            u8"第一部メインクエスト完了"s,
            u8"You have completed the main quest."s);
    }
    talk_conv(s1, 40 - en * 4);
    buff += s1;
    noteadd(""s);
    return;
}



void append_subquest_journal(int val0)
{
    if (val0 == 0)
    {
        noteadd(""s);
        noteadd(lang(u8"@QM[サブクエスト]"s, u8"@QM[Sub Quest]"s));
    }
    p = 0;
    if (gdata_putit_attacks != 0)
    {
        s = lang(u8"ぬいぐるみを守れ！ Lv6相当"s, u8"Putit attacks Lv6"s);
        p = gdata_putit_attacks;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのミシェスに、スライムの退治を頼まれた。スライムの巣窟は、ミシェスの家のすぐ南の家のようだ。"s,
                u8"Miches of Vernis asked me to investigate the house just south of her home."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ヴェルニースのミシェスに頼まれたスライムの退治を完了した。あとは報告するだけだ。"s,
                u8"I've wiped out the putit's nest. I have to visit Miches of Vernis to report it."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_thieves_hideout != 0)
    {
        s = lang(u8"お酒泥棒 Lv2相当"s, u8"Thieves' hideout Lv2"s);
        p = gdata_thieves_hideout;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのシーナが勤める酒場に、酒泥棒が頻出しているらしい。盗賊団を壊滅させてシーナに報告しよう。"s,
                u8"Bandits have been stealing things in Vernis. I need to find and destroy their hideout."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"酒樽を盗んでいたごろつき団を殲滅した。あとはヴェルニースのシーナに報告するだけだ。"s,
                u8"Those bandits are no more. All I have to do now is bring the news to Shena of Vernis."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_puppys_cave != 0)
    {
        s = lang(u8"迷子の子犬 Lv4相当"s, u8"Puppy's cave Lv4"s);
        p = gdata_puppys_cave;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのリリアンに、迷子の子犬ポピーを捜すよう頼まれた。どうやら子犬はヴェルニースのすぐ東にある洞窟にいるらしい。"s,
                u8"Rilian of Vernis asked me to find her puppy named Poppy in the puppy's cave located east of Vernis."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_nightmare != 0)
    {
        s = lang(u8"実験場のナイトメア Lv50相当"s, u8"Nightmare Lv50"s);
        p = gdata_nightmare;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヴェルニースのロイターに金になる仕事を持ちかけられた。何やら危険な仕事のようだ。万全の準備を整えてからロイターに話し掛けよう。"s,
                u8"Loyter of Vernis has a dangerous, yet highly profitable job for me. I need to prepare well before talking to him again."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"実験場の全ての敵を殲滅しなければならない。"s,
                u8"I need to eliminate all of the monsters in the test ground."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"実験を生き延びて完了させた。ヴェルニースのロイターに報告しよう。"s,
                u8"I've survived the nightmare. Now to meet Loyer of Vernis to receive the reward."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_pael_and_her_mom != 0)
    {
        s = lang(u8"エーテル病を治せ Lv20相当"s, u8"Pael and her mom Lv20"s);
        p = gdata_pael_and_her_mom;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 4)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 5)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 6)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 7)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 8)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 9)
        {
            s1 = lang(
                u8"ノイエルのパエルにエーテル抗体を渡した。母親の容態に変化があらわれるのを待とう。"s,
                u8"Pael's mother is suffering from Ether Disease and I gave Pael a potion of cure corruption in Noyel. Let's wait until the condition of her mother changes."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 10)
        {
            s1 = lang(
                u8"ノイエルのパエルの母親の容態が変わったようだ。今度見舞いにいったほうがいいかもしれない。"s,
                u8"There's a change in the condition of Pael's mother. I should go check her when I have time."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_wife_collector != 0)
    {
        s = lang(u8"嫁泥棒 Lv3相当"s, u8"Wife collector Lv3"s);
        p = gdata_wife_collector;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"カプールのラファエロに嫁を持ってくるよう頼まれた。なんという下劣な男だ。"s,
                u8"I was asked by Raphael of Port Kapul to bring my wife. What a moron."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_cat_house != 0)
    {
        s = lang(u8"猫退治 Lv25相当"s, u8"Cat house Lv25"s);
        p = gdata_cat_house;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのタムに、家の猫退治を依頼された。家は南の畑のあたりにあるそうだ。"s,
                u8"Tam of Yowyn asked me to eliminate the cats in his house. The house is located southern part of Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"タムの家の中の猫を退治した。あとはヨウィンでタムに報告するだけだ。"s,
                u8"I've freed Tam's house from the cats. To get the reward, I need to speak Tam again in Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_defense_line != 0)
    {
        s = lang(u8"防衛戦線の死闘 Lv17相当"s, u8"Defense line Lv17"s);
        p = gdata_defense_line;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのギルバート大佐に、ジューア解放軍の援護を求められた。準備が整い次第、大佐に話し掛けよう。"s,
                u8"Colonel Gilbert of Yowyn asked me to help the Juere freedom force fight the Yerles Army. I should speak to him again when I'm ready."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"イェルスの防衛軍を殲滅しなければならない。"s,
                u8"I need to destroy the Yerles Army."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"防衛線を見事に突破した。ヨウィンのギルバート大佐に報告しよう。"s,
                u8"I've won the war. Now to bring the good news to colonel Gilbert."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_novice_knight != 0)
    {
        s = lang(u8"騎士昇格試験の手伝い Lv8相当"s, u8"Novice knightLv8"s);
        p = gdata_novice_knight;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ヨウィンのアインクに騎士昇格試験の手伝いを頼まれた。ヨウィンの西にあるイークの洞窟に住むイークの首領を倒せばいいそうだ。"s,
                u8"Ainc of Yowyn asked me to help his promotion task. I need to enter the Yeek's dungeon which is located west of Yowyn and kill the chief."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"イークの首領を無事討伐した。ヨウィンのアインクに報告しよう。"s,
                u8"I've defeated the chief of Yeek. I should head back to Yowyn and report to Ainc."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_kamikaze_attack != 0)
    {
        s = lang(u8"カミカゼ特攻隊 Lv14相当"s, u8"Kamikaze attack Lv14"s);
        p = gdata_kamikaze_attack;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"カプールのアーノルドに、カミカゼ特攻隊に耐えるパルミア軍への援軍を頼まれた。準備が整い次第、アーノルドに話し掛けよう。"s,
                u8"Arnord of Port Kapul asked me to help the isolated Palmian 10th regiment from massive Kamikaze attacks. I should prepare and speak to Arnord when ready."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"パルミア軍が撤退を完了するまでの間、カミカゼ特攻隊の猛攻に耐えなければならない。パルミア軍が撤退したら、知らせが入るはずだ。"s,
                u8"I have to hold the battle line to gain time while the Palmian army retreats. A messenger will inform me when it's done."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 3)
        {
            s1 = lang(
                u8"カミカゼ特攻隊の猛攻に耐えきった。カプールのアーノルドに報告しよう。"s,
                u8"I survived the kamikaze attack. I have to bring the good news to Arnord of Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_mias_dream != 0)
    {
        s = lang(u8"ミーアの夢 Lv1相当"s, u8"Mia's dream Lv1"s);
        p = gdata_mias_dream;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"パルミアのミーアは、稀少猫シルバーキャットが欲しいらしい。なんとか捕まえて、ミーアに渡そう。"s,
                u8"Mia of Palmia wants a silver cat, a very rare cat. If I happen to capture one, I should bring it to Mia."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_rare_books != 0)
    {
        s = lang(u8"幻の絵本 Lv12相当"s, u8"Rare books Lv12"s);
        p = gdata_rare_books;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ルミエストのレントンが、レイチェルという童話作家によって描かれた絵本を探している。絵本は全部で4巻あるらしい。全て見つけたら、レントンに報告しよう。"s,
                u8"Renton of Lumiest is looking for the fairy tale books written by Rachael. I should bring it to him if I happen to find one. There're total of 4 books in the series."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_pyramid_trial != 0)
    {
        s = lang(u8"ピラミッドからの挑戦状 Lv16相当"s, u8"Pyramid trial Lv16"s);
        p = gdata_pyramid_trial;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ピラミッドに出入りする資格を得た。ピラミッドはカプールの北にあり、中には古代の秘宝が眠っているといわれている。"s,
                u8"I've got a invitation to the pyramid. The pyramid is located north of Port Kapul and it is rumored that it holds great treasure."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_red_blossom_in_palmia != 0)
    {
        s = lang(
            u8"パルミアに赤い花を Lv14相当"s, u8"Red blossom in Palmia Lv14"s);
        p = gdata_red_blossom_in_palmia;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ダルフィのノエルにパルミアの街に爆弾をしかけるように依頼された。爆弾をパルミアの宿屋の部屋にあるぬいぐるみにしかけよう。"s,
                u8"Noel of Derphy asked me to set up a bomb in Palmia. I need to place it right on the teddy bear in the inn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"見事にパルミアを壊滅させた。あとはダルフィのノエルの元に戻り、報告するだけだ。"s,
                u8"I have successfully destroyed Palmia. Now all I need to report back to Noel in Derphy."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_ambitious_scientist != 0)
    {
        s = lang(u8"生化学者の野望 Lv5相当"s, u8"Ambitious scientist Lv5"s);
        p = gdata_ambitious_scientist;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p
            == gdata_ambitious_scientist * (gdata_ambitious_scientist < 6)
                + (gdata_ambitious_scientist == 0))
        {
            s1 = lang(
                u8"カプールのイコールに、実験用の生物5体の捕獲を頼まれた。依頼品、モンスターボールに捕獲したものでなくてはならない。あと"s
                    + (6 - gdata_ambitious_scientist)
                    + u8"個の捕獲済みモンスターボールを届ける必要がある。"s,
                u8"Icolle of Port Kapul asked me to bring 5 filled monster balls. I still need to bring him "s
                    + (6 - gdata_ambitious_scientist) + u8" of them."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_sewer_sweeping != 0)
    {
        s = lang(u8"下水道大作戦 Lv23相当"s, u8"Sewer sweeping Lv23"s);
        p = gdata_sewer_sweeping;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"ルミエストのバルザックに、下水道の清掃を頼まれた。下水道の入り口は宿屋の近くにあるみたいだ。。"s,
                u8"Balzak of Lumiest wants me to sweep the entire sewer. I can find the entrance to the sewer around the inn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"下水道の大掃除を完了した。あとはルミエストのバルザックに報告するだけだ。"s,
                u8"I've finished sweeping the sewer. I need to report it to Balzak of Lumiest."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_mages_guild != 0)
    {
        s = lang(u8"魔術士ギルド審査"s, u8"Joining the Mages Guild"s);
        p = gdata_joining_mages_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"魔術士ギルドに加入するには、ルミエストのメイジギルドの納入箱に、解読済みの古書物を納入し、ギルドポイントを貯めた後、ギルドの番人に話しかけなければならない。審査をクリアするには、あと"s +
                    gdata_mages_guild_quota + u8"ギルドポイントを獲得する必要がある。"s,
                u8"To join the Mages Guild, I need to gather "s + gdata_mages_guild_quota +
                    u8" more guild points and talk to the guild guard in Lumiest. I can earn the guild points by collecting ancients books, decrypt them, and put them into the delivery box near the guild guard."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_thieves_guild != 0)
    {
        s = lang(u8"盗賊ギルド審査"s, u8"Joining the Thieves Guild"s);
        p = gdata_joining_thieves_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"盗賊ギルドに加入するには、税金を4ヶ月以上滞納した状態で、ダルフィのギルドの番人に話しかける必要がある。"s,
                u8"To join the Thieves Guild, I need to not pay tax for 4 months, that means I'll be a criminal for sure."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_joining_fighters_guild != 0)
    {
        s = lang(u8"戦士ギルド審査"s, u8"Joining the Fighters Guild"s);
        p = gdata_joining_fighters_guild;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"戦士ギルドに加入するには、"s +
                    chara_refstr(gdata_fighters_guild_target, 2) + u8"をあと"s + gdata_fighters_guild_quota +
                    u8"匹討伐してから、カプールのギルドの番人に話しかける必要がある。"s,
                u8"To join the Fighters Guild, I need to slay "s + gdata_fighters_guild_quota +
                    u8" more "s + chara_refstr(gdata_fighters_guild_target, 2) +
                    u8" and talk to the guild guard in Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_mages_guild_quota2 != 0)
    {
        s = lang(u8"魔術士ギルドノルマ"s, u8"The Mages Guild quota"s);
        p = gdata_mages_guild_quota2;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"魔術士ギルドのランクを上げるためには、ルミエストのメイジギルドの納入箱に、解読済みの古書物を納入し、ギルドポイントを貯めた後、ギルドの番人に話しかけなければならない。ランク上昇のためには、あと"s +
                    gdata_mages_guild_quota + u8"ギルドポイントを獲得する必要がある。"s,
                u8"To raise the rank in the Mages Guild, you need to gather "s +
                    gdata_mages_guild_quota +
                    u8" more guild points and talk to the guard in Lumiest. I can earn the guild points by collecting ancients books, decrypt them, and put them into the delivery box near the guild guard."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_fighters_guild_quota2 != 0)
    {
        s = lang(u8"戦士ギルドノルマ"s, u8"The Fighters Guild quota"s);
        p = gdata_fighters_guild_quota2;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"戦士ギルドのランクを上げるためには、"s +
                    chara_refstr(gdata_fighters_guild_target, 2) + u8"をあと"s + gdata_fighters_guild_quota +
                    u8"匹討伐してから、カプールのギルドの番人に話しかける必要がある。"s,
                u8"To raise the rank in the Fighters Guild, I need to slay "s +
                    gdata_fighters_guild_quota + u8" more "s + chara_refstr(gdata_fighters_guild_target, 2) +
                    u8" and talk to the guild guard in Port Kapul."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_thieves_guild_quota2 != 0)
    {
        s = lang(u8"盗賊ギルドノルマ"s, u8"The Thieves Guild quota"s);
        p = gdata_thieves_guild_quota2;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(u8"盗賊ギルドのランクを上げるためには、あと金貨"s +
                    gdata_thieves_guild_quota +
                    u8"枚分の盗品を売りさばき、ダルフィのギルドの番人に話しかける必要がある。"s,
                u8"To raise the rank in the Thieves Guild, I need to sell stolen goods worth total of "s +
                    gdata_thieves_guild_quota +
                    u8" gold pieces and talk to the guild guard in Derphy."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_minotaur_king != 0)
    {
        s = lang(u8"ミノタウロスの王 Lv24相当"s, u8"Minotaur king Lv24"s);
        p = gdata_minotaur_king;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"パルミアのコネリー少将に、ミノタウロスの首領の退治を頼まれた。ミノタウロスの巣窟は、ヨウィンの南にあるみたいだ。"s,
                u8"General Conery wants me to hunt the chief of minotaur. The nest is located south of Yowyn."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    if (val0 == 0)
    {
        if (p == 2)
        {
            s1 = lang(
                u8"ミノタウロスの首領を無事討伐した。パルミアのコネリー少将に報告しよう。"s,
                u8"I've killed the chief of minotaur. I should head back to Palmia and speak to General Conery."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    p = 0;
    if (gdata_little_sister != 0)
    {
        s = lang(u8"リトルシスター Lv30相当"s, u8"Little sister Lv30"s);
        p = gdata_little_sister;
        if (val0 == 1)
        {
            if (p >= 1000)
            {
                noteadd(lang(u8"[達成]"s, u8"[Done]"s) + s);
            }
        }
    }
    if (val0 == 0)
    {
        if (p == 1)
        {
            s1 = lang(
                u8"アクリ・テオラの謎の科学者に、リトルシスターを連れてくるよう頼まれた。捕獲するためには、ビッグダディを倒し、捕獲玉をリトルにぶつける必要がある。"s,
                u8"A strange scientist asked me to bring little sisters to her. To capture a little sister, I need to kill Big Daddy first then throw the little ball at her."s);
            talk_conv(s1, 40 - en * 4);
            buff += u8"("s + s + u8")\n"s + s1;
            noteadd(""s);
        }
    }
    return;
}



void append_quest_item_journal()
{
    noteadd(lang(u8"[古びたお守り]"s, u8"[An old talisman]"s));
    if (gdata_main_quest_flag >= 30)
    {
        noteadd(lang(u8"[ジャビ王への書簡]"s, u8"A letter to the king"s));
    }
    if (gdata_magic_stone_of_fool != 0)
    {
        noteadd(lang(u8"[愚者の魔石]"s, u8"Fool's magic stone"s));
    }
    if (gdata_magic_stone_of_king != 0)
    {
        noteadd(lang(u8"[覇者の魔石]"s, u8"King's magic stone"s));
    }
    if (gdata_magic_stone_of_sage != 0)
    {
        noteadd(lang(u8"[賢者の魔石]"s, u8"Sage's magic stone"s));
    }
    return;
}



void parse_quest_board_text(int val0)
{
    elona_vector1<std::string> buff2;
    notesel(buffboard);
    SDIM1(buff2);
    p = instr(buffboard, 0, s + u8","s + lang(u8"JP"s, u8"EN"s));
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
    return;
}



std::string randomname()
{
    std::string ret;

    while (1)
    {
        ret = rn1(rnd(length(rn1)));
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
            ret += rn2(rnd(length(rn2)));
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
            if (strutil::starts_with(ret, u8"ー")
                || strutil::contains(ret, u8"ーッ"))
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
        p_at_m41(2) = rnd(length2(rnlist));
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
        p_at_m41(4) = rnd(length2(rnlist));
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
                  })
                + ret;
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
    return i18n::_(u8"ui", u8"cheer_up_message", u8"_"s + hours);
}



void get_enchantment_description(int val0, int power, int category, bool trait)
{
    rtval(0) = 4;
    rtval(1) = 0;

    s = "";

    if (val0 / 10000 != 0)
    {
        if (trait)
            return;

        int sid = val0 % 10000;
        switch (val0 / 10000)
        {
        case 1:
            rtval = 2;
            if (power / 50 + 1 < 0)
            {
                rtval = 9;
                const auto skill_name =
                    i18n::_(u8"ability", std::to_string(sid), u8"name");
                if (category == 57000)
                {
                    s = lang(
                            skill_name + u8"を減衰させる毒素を含んでいる"s,
                            u8"has which deteriorates your "s + skill_name
                                + u8"."s)
                        + u8" ["s;
                    enchantment_print_level(power / 50);
                    s += u8"]"s;
                }
                else
                {
                    s = lang(
                        skill_name + u8"を"s + std::abs(power / 50 + 1)
                            + u8"下げる"s,
                        u8"decreases your "s + skill_name + u8" by "s
                            + std::abs(power / 50 + 1) + u8"."s);
                }
            }
            else
            {
                const auto skill_name =
                    i18n::_(u8"ability", std::to_string(sid), u8"name");
                if (category == 57000)
                {
                    s = lang(
                            skill_name + u8"を増強させる栄養をもっている"s,
                            u8"has essential nutrients to enhance your "s
                                + skill_name + u8"."s)
                        + u8" ["s;
                    enchantment_print_level(power / 50);
                    s += u8"]"s;
                }
                else
                {
                    s = lang(
                        skill_name + u8"を"s + std::abs(power / 50 + 1)
                            + u8"上げる"s,
                        u8"increases your "s + skill_name + u8" by "s
                            + std::abs(power / 50 + 1) + u8"."s);
                }
            }
            break;
        case 2:
            rtval = 3;
            if (power / 2 < 0)
            {
                rtval = 9;
                s = lang(
                    i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"への耐性を弱化する"s,
                    u8"weakens your resistance to "s
                        + i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"."s);
            }
            else
            {
                s = i18n::_(
                    u8"ability",
                    std::to_string(sid),
                    u8"enchantment_description");
                if (s == ""s)
                {
                    s = lang(
                        i18n::_(u8"ability", std::to_string(sid), u8"name")
                            + u8"への耐性を授ける"s,
                        u8"grants your resistance to "s
                            + i18n::_(
                                  u8"ability", std::to_string(sid), u8"name")
                            + u8"."s);
                }
            }
            s += u8" ["s;
            enchantment_print_level(power / 100);
            s += u8"]"s;
            break;
        case 3:
            rtval = 1;
            if (power / 50 + 1 < 0)
            {
                rtval = 9;
                s = lang(
                    i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"の技能を下げる"s,
                    u8"decreases your "s
                        + i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8" skill."s);
            }
            else
            {
                s = i18n::_(
                    u8"ability",
                    std::to_string(sid),
                    u8"enchantment_description");
                if (s == ""s)
                {
                    s = lang(
                        i18n::_(u8"ability", std::to_string(sid), u8"name")
                            + u8"の技能を上げる"s,
                        u8"improves your "s
                            + i18n::_(
                                  u8"ability", std::to_string(sid), u8"name")
                            + u8" skill."s);
                }
            }
            s += u8" ["s;
            enchantment_print_level((power / 50 + 1) / 5);
            s += u8"]"s;
            break;
        case 6:
            rtval = 8;
            if (category == 57000)
            {
                s = lang(
                        i18n::_(u8"ability", std::to_string(sid), u8"name")
                            + u8"の成長を助ける栄養をもっている"s,
                        u8"can help you exercise your "s
                            + i18n::_(
                                  u8"ability", std::to_string(sid), u8"name")
                            + u8" faster."s)
                    + u8" ["s;
                enchantment_print_level(power / 50);
                s += u8"]"s;
            }
            else
            {
                s = lang(
                    i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"を維持する"s,
                    u8"maintains "s
                        + i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"."s);
            }
            break;
        case 7:
            rtval = 4;
            s = i18n::_(
                u8"ability", std::to_string(sid), u8"enchantment_description");
            if (s == ""s)
            {
                s = lang(
                    ""s + i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8"属性の追加ダメージを与える"s,
                    u8"deals "s
                        + i18n::_(u8"ability", std::to_string(sid), u8"name")
                        + u8" damage."s);
            }
            s += u8" ["s;
            enchantment_print_level(power / 100);
            s += u8"]"s;
            break;
        case 8:
            rtval = 4;
            sid = encprocref(0, sid);
            s = lang(
                ""s + i18n::_(u8"ability", std::to_string(sid), u8"name")
                    + u8"を発動する"s,
                u8"invokes "s
                    + i18n::_(u8"ability", std::to_string(sid), u8"name")
                    + u8"."s);
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
            break;
        case 9:
            rtval = 4;
            s = lang(
                ""s + ammoname(sid) + u8"を装填できる"s,
                u8"can be loaded with "s + ammoname(sid) + u8"."s);
            s += lang(u8" [最大"s, u8" [Max "s) + power / 1000
                + lang(u8"発]"s, u8"]"s);
            break;
        }
        return;
    }

    switch (val0)
    {
    case 0: s = u8"?????"s; break;
    case 21:
        rtval = 9;
        s = lang(
            u8"ランダムなテレポートを引き起こす"s,
            u8"causes random teleport."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 45:
        rtval = 9;
        s = lang(u8"使用者の生き血を吸う"s, u8"sucks blood of the wielder."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 46:
        rtval = 9;
        s = lang(u8"あなたの成長を妨げる"s, u8"disturbs your growth."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 47:
        rtval = 9;
        s = lang(u8"魔物を呼び寄せる"s, u8"attracts monsters."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 22:
        rtval = 4;
        s = lang(
            u8"テレポートを妨害する"s, u8"prevents you from teleporting."s);
        break;
    case 23:
        rtval = 4;
        s = lang(u8"盲目を無効にする"s, u8"negates the effect of blindness."s);
        break;
    case 24:
        rtval = 4;
        s = lang(u8"麻痺を無効にする"s, u8"negates the effect of paralysis."s);
        break;
    case 25:
        rtval = 4;
        s = lang(u8"混乱を無効にする"s, u8"negates the effect of confusion."s);
        break;
    case 26:
        rtval = 4;
        s = lang(u8"恐怖を無効にする"s, u8"negates the effect of fear."s);
        break;
    case 27:
        rtval = 4;
        s = lang(u8"睡眠を無効にする"s, u8"negates the effect of sleep."s);
        break;
    case 28:
        rtval = 4;
        s = lang(u8"毒を無効にする"s, u8"negates the effect of poison."s);
        break;
    case 41:
        rtval = 4;
        s = lang(
            u8"アイテムを盗まれなくする"s, u8"protects you from thieves."s);
        break;
    case 42:
        rtval = 4;
        s = lang(
            u8"腐ったものを難なく消化させる"s,
            u8"allows you to digest rotten food."s);
        break;
    case 29:
        rtval = 4;
        s = lang(
            u8"速度を上げ、ワールドマップでの移動時間を短くする"s,
            u8"speeds up your travel progress."s);
        if (trait)
        {
            rtval(1) = power / 100;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 100);
            s += u8"]"s;
        }
        break;
    case 30:
        rtval = 4;
        s = lang(
            u8"エーテルの風からあなたを保護する"s,
            u8"protects you from Etherwind."s);
        break;
    case 31:
        rtval = 4;
        s = lang(
            u8"雷雨と雪による足止めを無効にする"s,
            u8"negates the effect of being stranded by bad weather."s);
        break;
    case 48:
        rtval = 4;
        s = lang(
            u8"異物の体内への侵入を防ぐ"s,
            u8"prevents aliens from entering your body."s);
        break;
    case 32:
        rtval = 4;
        s = lang(u8"あなたを浮遊させる"s, u8"floats you."s);
        break;
    case 33:
        rtval = 4;
        s = lang(
            u8"あなたを変異から保護する"s, u8"protects you from mutation."s);
        break;
    case 34:
        rtval = 4;
        s = lang(u8"魔法の威力を高める"s, u8"enhances your spells."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 35:
        rtval = 4;
        s = lang(
            u8"透明な存在を見ることを可能にする"s,
            u8"allows you to see invisible creatures."s);
        break;
    case 36:
        rtval = 4;
        s = lang(
            u8"攻撃対象からスタミナを吸収する"s,
            u8"absorbs stamina from an enemy."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 37:
        rtval = 4;
        s = lang(u8"全てを終結させる"s, u8"brings an end."s);
        break;
    case 38:
        rtval = 4;
        s = lang(
            u8"攻撃対象からマナを吸収する"s, u8"absorbs MP from an enemy."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 39:
        rtval = 4;
        s = lang(
            u8"完全貫通攻撃発動の機会を増やす"s,
            u8"gives you a chance to throw an absolute piercing attack."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 44:
        rtval = 4;
        s = lang(
            u8"クリティカルヒットの機会を増やす"s,
            u8"increases your chance to deliver critical hits."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 50:
        rtval = 4;
        s = lang(
            u8"追加打撃の機会を増やす"s,
            u8"increases the chance of extra melee attack."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 51:
        rtval = 4;
        s = lang(
            u8"追加射撃の機会を増やす"s,
            u8"increases the chance of extra ranged attack."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 40:
        rtval = 4;
        s = lang(u8"稀に時を止める"s, u8"occasionally stops time."s);
        if (trait)
        {
            rtval(1) = power / 100;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 100);
            s += u8"]"s;
        }
        break;
    case 43:
        rtval = 4;
        s = lang(
            u8"呪いの言葉から保護する"s, u8"protects you from cursing words."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 49:
        rtval = 4;
        s = lang(
            u8"演奏報酬の品質を上げる"s,
            u8"increases the qualitiy of reward."s);
        break;
    case 52:
        rtval = 4;
        s = lang(
            u8"被る物理ダメージを軽減する"s,
            u8"decreases physical damage you take."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 53:
        rtval = 4;
        s = lang(
            u8"被るダメージを稀に無効にする"s,
            u8"sometimes nullifies damage you take."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 54:
        rtval = 4;
        s = lang(
            u8"攻撃された時、相手に切り傷のダメージを与える"s,
            u8"deals cut damage to the attacker."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 55:
        rtval = 4;
        s = lang(u8"出血を抑える"s, u8"diminishs bleeding."s);
        break;
    case 56:
        rtval = 4;
        s = lang(
            u8"神が発する電波をキャッチする"s, u8"catches signals from God."s);
        break;
    case 57:
        rtval = 4;
        s = lang(
            u8"竜族に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to dragons."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 58:
        rtval = 4;
        s = lang(
            u8"不死者に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to undeads."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    case 59:
        rtval = 4;
        s = lang(u8"他者の信仰を明らかにする"s, u8"reveals religion."s);
        break;
    case 60:
        rtval = 4;
        s = lang(
            u8"深い音色で聴衆を酔わす"s,
            u8"makes audience drunk with haunting tones."s);
        break;
    case 61:
        rtval = 4;
        s = lang(
            u8"神に対して強力な威力を発揮する"s,
            u8"inflicts massive damage to Gods."s);
        if (trait)
        {
            rtval(1) = power / 50;
        }
        else
        {
            s += u8" ["s;
            enchantment_print_level(power / 50);
            s += u8"]"s;
        }
        break;
    }
}



std::string trim_item_description(const std::string& source, bool summary)
{
    std::string ret{source};

    while (1)
    {
        // Delete tab character.
        const auto tab_pos = ret.find('\t');
        if (tab_pos != std::string::npos)
        {
            ret.erase(tab_pos, 1);
            continue;
        }

        if (summary)
        {
            // Delete line break.
            const auto line_break_pos = ret.find('\n');
            if (line_break_pos != std::string::npos)
            {
                ret.erase(line_break_pos, 1);
                continue;
            }
            // Delete number sign and rest.
            const auto number_sign_pos = ret.find('#');
            if (number_sign_pos != std::string::npos)
            {
                ret.erase(number_sign_pos);
            }
            if (jp)
            {
                // If "ret" ends with period, delete it.
                constexpr const char* japanese_period = u8"。";
                const auto period_pos = ret.find(japanese_period);
                if (period_pos != std::string::npos
                    && period_pos + std::strlen(japanese_period) == ret.size())
                {
                    ret.erase(period_pos);
                }
            }
            else
            {
                // Replace comma with period.
                const auto comma_pos = ret.find(',');
                if (comma_pos != std::string::npos)
                {
                    ret[comma_pos] = '.';
                    continue;
                }
            }
        }
        else
        {
            // Delete number sign.
            const auto number_sign_pos = ret.find('#');
            if (number_sign_pos != std::string::npos)
            {
                ret.erase(number_sign_pos, 1);
                continue;
            }
        }
        break;
    }

    return ret;
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
    return;
}



} // namespace elona
